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

is_blank() {
  local s="${1-}"
  [[ -z "$(printf '%s' "$s" | tr -d '[:space:]')" ]]
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
- Prefer no scope unless clearly useful
- lowercase only
- no emoji
- no trailing period
- subject must not be empty
- keep the full header short
- output only the commit message, nothing else
PROMPT
}

sanitize_line() {
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
    s/^[-*•]\s*//;
    s/^"(.*)"$/$1/;
    s/^'\''(.*)'\''$/$1/;
    s/^`(.*)`$/$1/;
  '
}

fallback_message() {
  local first
  first="$(git diff --cached --name-only | head -n 1 || true)"

  case "$first" in
    *.md|docs/*)
      printf 'docs: update documentation'
      ;;
    Makefile|*.mk|.github/*)
      printf 'chore: update build workflow'
      ;;
    tests/*|test/*|*_test.*|*.spec.*)
      printf 'test: update test files'
      ;;
    "")
      printf 'chore: update staged files'
      ;;
    *)
      printf 'chore: update staged files'
      ;;
  esac
}

canonicalize_message() {
  local raw="$1"
  local clean type scope subject prefix max allowed

  clean="$(printf '%s' "$raw" | sanitize_line)"
  is_blank "$clean" && return 1

  if [[ "$clean" =~ ^([a-z]+)(\(([a-z0-9._/-]+)\))?!?:[[:space:]]+(.+)$ ]]; then
    type="${BASH_REMATCH[1]}"
    scope="${BASH_REMATCH[3]:-}"
    subject="${BASH_REMATCH[4]}"
  else
    type="chore"
    scope=""
    subject="$clean"
  fi

  subject="$(printf '%s' "$subject" | sanitize_line | sed 's/\.$//')"
  is_blank "$subject" && return 1

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

  if (( ${#prefix} + ${#subject} > max )) && [[ -n "$scope" ]]; then
    scope=""
    prefix="$type: "
    allowed=$((max - ${#prefix}))
  fi

  if (( ${#prefix} + ${#subject} > max )); then
    subject="${subject:0:$allowed}"
    subject="$(printf '%s' "$subject" | sed 's/[[:space:]]*$//')"
  fi

  is_blank "$subject" && return 1

  if [[ -n "$scope" ]]; then
    printf '%s(%s): %s' "$type" "$scope" "$subject"
  else
    printf '%s: %s' "$type" "$subject"
  fi
}

extract_first_useful_line() {
  local file="$1"
  local line cleaned

  while IFS= read -r line; do
    cleaned="$(printf '%s' "$line" | sanitize_line)"
    if ! is_blank "$cleaned"; then
      printf '%s' "$cleaned"
      return 0
    fi
  done < "$file"

  return 1
}

generate_message_once() {
  local prompt tmpfile pid raw result

  prompt="$(build_prompt)"
  tmpfile="$(mktemp /tmp/ai-commit-output.XXXXXX)"

  (
    copilot \
      -p "$prompt" \
      -s \
      --no-ask-user \
      --allow-tool='shell(git:*)' \
      2>/dev/null
  ) > "$tmpfile" &
  pid=$!

  spinner "$pid"
  wait "$pid" || true
  printf "\r\033[K✓ Commit mesajı hazır.\n" >&2

  raw="$(extract_first_useful_line "$tmpfile" || true)"
  rm -f "$tmpfile"

  is_blank "$raw" && return 1

  result="$(canonicalize_message "$raw" || true)"
  is_blank "$result" && return 1

  printf '%s' "$result"
}

generate_message() {
  local tries=0
  local msg=""

  while (( tries < 3 )); do
    tries=$((tries + 1))
    msg="$(generate_message_once || true)"
    if ! is_blank "$msg"; then
      printf '%s' "$msg"
      return 0
    fi
    echo "Uygun mesaj üretilemedi, tekrar deneniyor... ($tries/3)" >&2
  done

  fallback_message
}

edit_message() {
  local initial="$1"
  local tmp edited fixed

  tmp="$(mktemp /tmp/ai-commit-msg.XXXXXX)"
  printf "%s\n" "$initial" > "$tmp"

  "${EDITOR:-nano}" "$tmp"

  edited="$(tr -d '\r' < "$tmp" | sed '/^[[:space:]]*$/d' | head -n 1 || true)"
  rm -f "$tmp"

  fixed="$(canonicalize_message "$edited" || true)"
  if is_blank "$fixed"; then
    fixed="$(fallback_message)"
  fi
  printf '%s' "$fixed"
}

confirm_loop() {
  local msg="$1"
  local answer edited

  while true; do
    if is_blank "$msg"; then
      msg="$(fallback_message)"
    fi

    echo
    echo "Önerilen commit mesajı:"
    echo "  $msg"
    echo
    echo "[y] commit et   [e] düzenle   [r] yeniden üret   [p] değişiklik özeti   [n] iptal"
    read -r -p "> " answer

    case "${answer:-y}" in
      y|Y)
        COMMIT_MSG="$(canonicalize_message "$msg" || true)"
        if is_blank "${COMMIT_MSG:-}"; then
          COMMIT_MSG="$(fallback_message)"
        fi
        return 0
        ;;
      e|E)
        edited="$(edit_message "$msg" || true)"
        if is_blank "$edited"; then
          msg="$(fallback_message)"
        else
          msg="$edited"
        fi
        ;;
      r|R)
        msg="$(generate_message || true)"
        if is_blank "$msg"; then
          msg="$(fallback_message)"
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

  msg="$(generate_message || true)"
  if is_blank "$msg"; then
    msg="$(fallback_message)"
  fi

  COMMIT_MSG=""
  confirm_loop "$msg" || exit 1

  if is_blank "${COMMIT_MSG:-}"; then
    COMMIT_MSG="$(fallback_message)"
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
