# Push_Swap Defense - Practice Session Rehberi

Sunum öncesi **3 cıl practice session** yapın!

---

## SESSION 1: Algoritmaları Anlatış (30 min)

### Adım 1: SIMPLE (5 min)
```
1. Whiteboard'a [5, 3, 1, 4, 2] yaz
2. "Şu array'i SIMPLE ile sort edelim"
3. Adım adım:
   - Min find: 1
   - Rotate: 3 adım (bottom'dan)
   - pb
   - Min find: 2
   - Rotate: ...
4. Output operations'ları yaz
5. Total ops say

Practice: 3-4 farklı array dene
```

### Adım 2: MEDIUM (8 min)
```
1. [1, 5, 2, 4, 3] al
2. "Index assign: 1→0, 2→1, 3→2, 4→3, 5→4"
3. "Chunk = 15 (limit = 14)"
4. Push chunks:
   - Scan: 1(0)≤14 ✓
   - pb
   - Continue...
5. Push back from B
   - Find max (5)
   - Rotate to top
   - pa
   - Repeat

Bu görsel olarak (diagram) anlaması gerekir!
```

### Adım 3: COMPLEX - Radix (10 min) ⭐ İŞİN ZORU
```
1. [1, 5, 2, 4, 3] take
2. Index: [0, 4, 1, 3, 2]
3. Max bits = 3 (log2(5))
4. BIT 0 (LSB):
   - 0 = 000 → bit0=0 → pb
   - 4 = 100 → bit0=0 → pb
   - 1 = 001 → bit0=1 → ra
   - 3 = 011 → bit0=1 → ra
   - 2 = 010 → bit0=0 → pb
   - pa pa pa (B'den tüm geri)

5. BIT 1:
   - ... (tekrar)

6. BIT 2:
   - ... (final sort)

Binary aktarma zorabilir! Practice et!
```

### Adım 4: ADAPTIVE (7 min)
```
1. Disorder hesapla
   - "Hangi arrayler 0.2'den az?"
   - "Hangi arrayler 0.5'den fazla?"

2. Threshold açıkla
   - "<0.2 → SIMPLE" (neden? scan zaten adında)
   - "0.2-0.5 → MEDIUM"
   - "≥0.5 → COMPLEX"

3. 3-4 array için: disorder tahmin → algorithm seç
```

---

## SESSION 2: Code Reading (30 min)

### Goal: Kritik 4 fonksiyonu adım adım trace et

```c
1. simple_sort()
   - find_min_index() detaylı oku
   - rotate_simple() logic'i
   - while loops

2. medium.c
   - assign_indices()
   - push_chunks_to_b() kompleks
   - push_back_to_a()

3. complex.c
   - complex_assign_indices()
   - complex_max_bits_for_size() bit logic
   - complex_run_radix_pass() main loop

4. adaptive_sort()
   - compute_disorder() formula
   - threshold decision
```

### Practice:
```bash
# Her function'ı GDB ile step-through et
gdb ./push_swap
(gdb) break simple_sort
(gdb) run --simple 5 4 3 2 1
(gdb) step  # Her satırda dur
(gdb) print a->size, a->top->value  # Stack state kontrol et

# Veya manuel trace:
# Kod file'ı aç, input'u paper'a yaz,
# her line'ı execute et paper'da
```

---

## SESSION 3: Live Simulation (30 min)

### 3-4 mini scenario

**Scenario 1: Sorted Input**
```
Input: 1 2 3 4 5
Disorder: 0%
Algorithm: SIMPLE (adaptive chooses)
Expected: 0 operations
Test: ./push_swap 1 2 3 4 5 | wc -l
      Should be 0
```

**Scenario 2: Nearly Sorted**
```
Input: 1 2 4 3 5
Disorder: 1/10 = 10%
Algorithm: SIMPLE
Expected: ~20-30 ops
Test: ./push_swap 1 2 4 3 5
Verify: ./checker confirms OK
```

**Scenario 3: Moderately Chaotic**
```
Input: 3 1 4 2 5
Disorder: 4/10 = 40%
Algorithm: MEDIUM
Expected: ~15-25 ops
Test: ./push_swap 3 1 4 2 5
Output: count ops, strategies correct?
```

**Scenario 4: Completely Reversed**
```
Input: 5 4 3 2 1
Disorder: 100%
Algorithm: COMPLEX
Expected: ~15-25 ops
Test: ./push_swap --bench --complex 5 4 3 2 1 2>&1
Check: Disorder% correct? Strategy correct?
```

---

## EVALUATION ROOM SETUP (Fiziksel)

Sunum sırasında ihtiyacın olacak:

```
☐ Laptop (code + compile test)
☐ Whiteboard + marker (diagram)
☐ Eller (gestures - important!)
☐ Ses (clear pronunciation)
☐ Bakış iletişimi (evaluator'a)

Not take: Telefon, notes (memory test)
```

---

## PRACTICE SCRIPT (Sesli)

Sunum sırasında **şunları söyle** (word-for-word):

```
"Merhaba. Bu push_swap projesi, iki stack kullanarak
integer arrayini 11 operasyonla minimum sayıda işlemle
sıralayan bir programdır.

Veri yapısı olarak doubly-linked list kullandık çünkü
reverse rotate operasyonunun O(1) olması kritik.

Dört farklı algoritma var:
1. SIMPLE - selection sort style, O(n²)
2. MEDIUM - chunk-based, O(n√n)
3. COMPLEX - radix sort, O(n log n)
4. ADAPTIVE - disorder ölçüp optimal seçimi yapıyor

Algoritmaları örnek bir input üzerinden gösterelim..."

(Whiteboard çıkar, [3, 1, 4, 2] yaz)

"Input: 3 1 4 2

Adım 1: Index assign (rank):
1→0, 2→1, 3→2, 4→3
Sonra: [3(2), 1(0), 4(3), 2(1)]

Adım 2: Disorder hesapla
Inversions: (3,1), (3,2), (4,2) = 3
Total pairs: 6
Disorder: 3/6 = 0.5 → COMPLEX algorithm seçilir

Adım 3: Radix sort - bit by bit...
 Bit 0: ...
 Bit 1: ...
 Final: [1, 2, 3, 4] ✅

İşte bu kadar! Sorular?"
```

---

## HÄUFIG ERRORS (Hata yapma olasılıklarını düşür)

### ❌ YAPMA:
1. Tüm 1000 satır kodu oku
2. "Basit, algoritma herkes biliyor" deme
3. Disorder formula'yı unnut
4. Radix sort'un nasıl çalıştığını explain edememe
5. Partner'ı mention etmeme
6. Performance hedefleri unnutma
7. Code trace edememe (tam detay)
8. "Edge case nedir?" sorusuna "bilinmiyor" deme

### ✅ YAP:
1. Conceptual explanation + code example
2. Algoritmaların trade-off'larını söyle
3. Disorder'a göre algorithm seçme mantığı
4. Radix sort bit manipulation detaylı
5. Partner'ın katkısını vurgula (bölüne bölüne)
6. "100 element <2000 ops guaranteed" söyle
7. Whiteboard trace et, paper'a bakma
8. "Meşe ağacı algoritmıştır, bu şekilde secure" falan eğer pattern varsa biliyorsunuz

---

## EVALUATOR TRICKS (Nasıl impress etsin?)

### Evaluator sorum: "Sorted array'de ne oluyor?"
**Kötü cevap:** "Hiç işlem yapılmıyor"
**İyi cevap:** "Disorder = 0 detected, adaptive simple() seçer, O(n) scan → all sorted detected → 0 pb/pa operation, sadece identity check"

### Evaluator sorum: "500 element'te kaç op?"
**Kötü:** "Hmm, bilmiyorum, ~5000?"
**İyi:** "Adaptive disorder measure eder. Random input ≈ 50% disorder → complex radix seçer. log₂(500) = 9 passes, her pass ~n+n ops = 9*1000 = 9000 theoretical, optimizations ile 2-3k"

### Evaluator sorum: "Neden this chunk size?"
**Kötü:** "Random seçtik"
**İyi:** "Empirical testing. 100 element için 15, 500+ için 36. Trade-off: chunk çok büyük → too many ops, çok küçük → too many rotations"

---

## TIME MANAGEMENT

| Part | Allocated | Notes |
|------|-----------|-------|
| Intro | 2 min | Hızlı, punchy |
| Structures | 2 min | Minimal, focus algorithms |
| Operations | 2 min | Just overview, not detailed |
| Algorithms | **12 min** | ⭐ CORE, 3 min each |
| Benchmark | 1 min | Quick show |
| Demo | 4 min | Live trace |
| Code Q&A | 5 min | Why/how questions |
| **TOTAL** | **~30 min** | **STRICT** |

**RULE: Zaman terse kalmayın, önceden dönersiniz!**

---

## MENTAL PREP (Sunum gece öncesi)

- [ ] 8 saat uyu
- [ ] Kahvaltı et
- [ ] Yoga/breathing (nervilik gitmek için)
- [ ] 1 kez daha review (script + code)
- [ ] Whiteboard marker test et
- [ ] Laptop battery full
- [ ] Öğle vakti: açık havada yürü (mental reset)

---

## SUNUM GÜNÜNÜN SABAHI

```
9:00 - Kahvaltı (protein-rich)
9:30 - Derin nefes al (5 min)
9:40 - Code bir kez daha compile ve test et
10:00 - Evaluator ofisine git
10:15 - Selam, tanışı, rahat ol
10:20 - START!
```

---

## POST-DEFENSE

Evaluator feedback:
- Dinle, not al
- Savun değil, explain etti
- "Haklısınız, sonraki sefere şöyle yapacağız" tarzı
- Mütekabelyen iyi değerlendirme için teşekkür et

---

## 🎯 FINAL CHECKLIST (Defense başlamadan 5 min)

```
☐ Laptop açılı, push_swap binary compiled
☐ Terminal temiz, cd push_swap'e ready
☐ Whiteboard marker + eraser ready
☐ Benchmarks output'ı biliyorum (böylece cevap hızlı)
☐ 4 algoritmayl describe edebiliyorum
☐ Partner'ın katkısı ağızda
☐ Breathing: 5 deep breaths
☐ Gözler açık, tersiz, confident
☐ BAŞLA!
```

---

**GOOD LUCK! YOU'VE GOT THIS! 🚀**

