#!/usr/bin/env bash
set -euo pipefail

require_cmd() {
  command -v "$1" >/dev/null 2>&1 || {
    echo "Eksik komut: $1"
    exit 1
  }
}

is_git_repo() {
  git rev-parse --is-inside-work-tree >/dev/null 2>&1
}

current_branch() {
  git branch --show-current
}

has_upstream() {
  git rev-parse --abbrev-ref --symbolic-full-name '@{u}' >/dev/null 2>&1
}

cleanup_spinner() {
  tput cnorm 2>/dev/null || true
}

trap cleanup_spinner EXIT

spinner() {
  local pid="$1"
  local delay=0.08
  local frames=('⠋' '⠙' '⠹' '⠸' '⠼' '⠴' '⠦' '⠧' '⠇' '⠏')

  tput civis 2>/dev/null || true

  while kill -0 "$pid" 2>/dev/null; do
    for frame in "${frames[@]}"; do
      printf "\r%s Commit mesajı üretiliyor..." "$frame" >&2
      sleep "$delay"
      kill -0 "$pid" 2>/dev/null || break
    done
  done

  printf "\r\033[K" >&2
  tput cnorm 2>/dev/null || true
}

preview_changes() {
  echo
  echo "Staged dosyalar:"
  git diff --cached --name-status || true
  echo
  echo "Özet:"
  git diff --cached --stat || true
  echo
}

build_prompt() {
  cat <<'PROMPT'
Write exactly one Conventional Commit message in plain text for the staged changes.

Rules:
- Format: <type>(<scope>): <subject> or <type>: <subject>
- Allowed types: feat, fix, refactor, chore, docs, test, perf, ci, build, style, revert
- Prefer no scope unless it is clearly useful
- lowercase only
- no emoji
- no trailing period
- keep the full header short
- output only the commit message, nothing else
PROMPT
}

sanitize_raw_text() {
  perl -CS -Mutf8 -pe '
    s/\e\[[0-9;?]*[ -\/]*[@-~]//g;
    s/\r//g;
    s/[\x{200B}\x{200C}\x{200D}\x{2060}\x{FEFF}]//g;
    s/\x{00A0}/ /g;
    s/[\p{Cc}\p{Cf}]//g;
    s/[“”]/"/g;
    s/[‘’]/'\''/g;
    s/^\s+//;
    s/\s+$//;
    s/\s+/ /g;
    s/^"(.*)"$/$1/;
    s/^'\''(.*)'\''$/$1/;
  '
}

canonicalize_message() {
  local raw="$1"
  local clean type scope subject prefix max allowed

  clean="$(printf '%s' "$raw" | sanitize_raw_text)"

  if [[ "$clean" =~ ^([a-z]+)(\(([a-z0-9._/-]+)\))?!?:[[:space:]]+(.+)$ ]]; then
    type="${BASH_REMATCH[1]}"
    scope="${BASH_REMATCH[3]:-}"
    subject="${BASH_REMATCH[4]}"
  else
    type="chore"
    scope=""
    subject="$clean"
  fi

  subject="$(
    printf '%s' "$subject" | perl -CS -Mutf8 -pe '
      s/\x{00A0}/ /g;
      s/[\x{200B}\x{200C}\x{200D}\x{2060}\x{FEFF}]//g;
      s/[\p{Cc}\p{Cf}]//g;
      s/^\s+//;
      s/\s+$//;
      s/\.$//;
      s/\s+/ /g;
    '
  )"

  type="$(printf '%s' "$type" | tr '[:upper:]' '[:lower:]')"
  scope="$(printf '%s' "$scope" | tr '[:upper:]' '[:lower:]')"

  if [[ -n "$scope" ]]; then
    prefix="$type($scope): "
  else
    prefix="$type: "
  fi

  max=72
  allowed=$((max - ${#prefix}))

  if (( allowed < 8 )); then
    scope=""
    prefix="$type: "
    allowed=$((max - ${#prefix}))
  fi

  if (( ${#prefix} + ${#subject} > max )); then
    if [[ -n "$scope" ]]; then
      scope=""
      prefix="$type: "
      allowed=$((max - ${#prefix}))
    fi
  fi

  if (( ${#prefix} + ${#subject} > max )); then
    subject="${subject:0:$allowed}"
    subject="$(printf '%s' "$subject" | sed 's/[[:space:]]*$//')"
  fi

  if [[ -n "$scope" ]]; then
    printf '%s(%s): %s' "$type" "$scope" "$subject"
  else
    printf '%s: %s' "$type" "$subject"
  fi
}

generate_message() {
  local prompt tmpfile pid result

  prompt="$(build_prompt)"
  tmpfile="$(mktemp /tmp/ai-commit-output.XXXXXX)"

  if [[ -n "${AI_COMMIT_MODEL:-}" ]]; then
    (
      copilot \
        -p "$prompt" \
        -s \
        --no-ask-user \
        --allow-tool='shell(git:*)' \
        --model "${AI_COMMIT_MODEL}" \
        2>/dev/null
    ) > "$tmpfile" &
  else
    (
      copilot \
        -p "$prompt" \
        -s \
        --no-ask-user \
        --allow-tool='shell(git:*)' \
        2>/dev/null
    ) > "$tmpfile" &
  fi

  pid=$!
  spinner "$pid"
  wait "$pid"
  printf "\r\033[K✓ Commit mesajı hazır.\n" >&2

  result="$(sed '/^[[:space:]]*$/d' "$tmpfile" | head -n 1)"
  rm -f "$tmpfile"

  canonicalize_message "$result"
}

edit_message() {
  local initial="$1"
  local tmp edited

  tmp="$(mktemp /tmp/ai-commit-msg.XXXXXX)"
  printf "%s\n" "$initial" > "$tmp"

  "${EDITOR:-nano}" "$tmp"

  edited="$(tr -d '\r' < "$tmp" | sed '/^[[:space:]]*$/d' | head -n 1)"
  rm -f "$tmp"

  canonicalize_message "$edited"
}

confirm_loop() {
  local msg="$1"
  local answer edited

  while true; do
    echo
    echo "Önerilen commit mesajı:"
    echo "  $msg"
    echo
    echo "[y] commit et   [e] düzenle   [r] yeniden üret   [p] değişiklik özeti   [n] iptal"
    read -r -p "> " answer

    case "${answer:-y}" in
      y|Y)
        COMMIT_MSG="$(canonicalize_message "$msg")"
        return 0
        ;;
      e|E)
        edited="$(edit_message "$msg")"
        if [[ -z "$edited" ]]; then
          echo "Boş mesaj olmaz."
        else
          msg="$edited"
        fi
        ;;
      r|R)
        msg="$(generate_message)"
        if [[ -z "$msg" ]]; then
          echo "Commit mesajı üretilemedi."
          return 1
        fi
        ;;
      p|P)
        preview_changes
        ;;
      n|N)
        echo "İptal edildi."
        return 1
        ;;
      *)
        echo "Geçersiz seçim."
        ;;
    esac
  done
}

main() {
  require_cmd git
  require_cmd copilot
  require_cmd perl

  if ! is_git_repo; then
    echo "Burası bir git reposu değil."
    exit 1
  fi

  local branch msg

  branch="$(current_branch)"

  if [[ -n "${AI_COMMIT_ONLY_BRANCH:-}" && "$branch" != "$AI_COMMIT_ONLY_BRANCH" ]]; then
    echo "Yanlış branch'tesin. Şu an: $branch | İzin verilen: $AI_COMMIT_ONLY_BRANCH"
    exit 1
  fi

  git add -A

  if git diff --cached --quiet; then
    echo "Staged değişiklik yok."
    exit 1
  fi

  preview_changes

  msg="$(generate_message)"

  if [[ -z "$msg" ]]; then
    echo "Commit mesajı üretilemedi."
    exit 1
  fi

  COMMIT_MSG=""
  confirm_loop "$msg" || exit 1

  if [[ -z "$COMMIT_MSG" ]]; then
    echo "Boş commit mesajı."
    exit 1
  fi

  echo
  echo "Kullanılacak commit mesajı:"
  echo "  $COMMIT_MSG"
  echo
  echo "Commit atılıyor..."
  git commit -m "$COMMIT_MSG"

  echo
  echo "Push atılıyor..."
  if has_upstream; then
    git push
  else
    git push -u origin "$branch"
  fi
}

main "$@"
