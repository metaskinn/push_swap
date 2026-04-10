# Push_Swap Projesi - Peer Evaluation Defense Sunum Rehberi

## 🎯 SUNUM AKIŞI (SÜREKLİ: ~15-20 dakika)

---

## BÖLÜM 1: PROJEYİ TANIŞTIRMA (2-3 dakika)

### Ne Yaptık?
```
Merhaba. Bu projede, iki stack kullanarak integer listelerini
en az sayıda operasyonla sıralamak için dört farklı sorting
algoritması implement ettik.

Kısaca:
- 2 stack: A ve B
- A'da karışık sayılar, B boş
- 11 operasyon (push, pop, rotate, swap)
- Amaç: A'yı sıralamak, minimum işlem
```

### Neden Zor?
```
Sadece şu operasyonlar var:
- sa, sb, ss (top 2 elementi swap et)
- pa, pb (stack arasında push)
- ra, rb, rr (rotate - first → last)
- rra, rrb, rrr (reverse rotate - last → first)

Garip kısıtlamalarla (sadece top element erişebiliriz),
O(n²), O(n√n), O(n log n) komplikliklerinde çalışmak gerekti.
```

### Min-Max Performans Hedefleri
```
100 element: < 2000 operasyon
500 element: < 12000 operasyon

Bunun neden zor olduğu: Elemanları "görmek" için rotate etmen gerek,
ama her rotate bir operasyon sayılıyor!
```

---

## BÖLÜM 2: TEMEL DATA STRUCTURES (2 dakika)

### Stack Node Yapısı
```c
typedef struct s_node
{
    int value;           // Asıl sayı (ör: 42, -7, 100)
    int indx;            // RANK (0 to n-1) - sorting için çok önemli
    struct s_node *next; // Doubly-linked için gerekli
    struct s_node *prev; // Geri gitme (reverse rotate içinde)
} t_node;
```

**Neden doubly-linked?**
```
- Forward: normal push/pop/rotate
- Backward: reverse rotate (rra, rrb) için bottom'a gitmeliyiz
- Singly-linked olsaydı, reverse rotate çok yavaş olurdu

Örnek:
Stack: [5, 3, 8, 1]  (top=5, bottom=1)

rra → bottom'u top'a taşı: [1, 5, 3, 8]
- prev pointer olmadan bottom'a erişemezdik
```

### Stack Yapısı
```c
typedef struct s_stack
{
    int size;        // Kaç eleman var
    t_node *top;     // Push/pop buradan
    t_node *bottom;  // reverse rotate buradan
} t_stack;
```

### Index (Rank) Konsepti - ÇOK ÖNEMLİ!
```
Neden indx var?

Input: [42, 10, 30]
- 10 en küçük → indx = 0
- 30 ortada → indx = 1
- 42 en büyük → indx = 2

İndex kullanarak algoritmaların radix sort gibi çalışmasını
sağlıyoruz. Gerçek değerler yerine 0-n arasında sayılarla işlem.

Avantaj: Radix sort'da bit manipulation kolay olur
```

---

## BÖLÜM 3: 11 OPERASYON (3 dakika - Demoyla)

### pa / pb (Push A, Push B)

```
Fikirsel:
Stack A: [3, 1, 2]
Stack B: []

pb (A'nın top'unu B'ye taşı):
Stack A: [1, 2]
Stack B: [3]

pa (B'nin top'unu A'ye taşı):
Stack A: [3, 1, 2]
Stack B: []
```

**Kod (push_op.c):**
```c
void pb(t_stack *a, t_stack *b, t_flags *flag) {
    if (!a || !b || a->size == 0) return;

    // 1. A'nın top'unu kes
    t_node *node = a->top;
    a->top = node->next;
    if (a->top) a->top->prev = NULL;
    else a->bottom = NULL;
    a->size--;

    // 2. B'nin top'una yapıştır
    node->prev = NULL;
    node->next = b->top;
    if (b->top) b->top->prev = node;
    else b->bottom = node;
    b->top = node;
    b->size++;

    // 3. Operasyon sayısını artır
    flag->total_ops++;
    flag->op_count[OP_PB]++;
}
```

### sa / sb (Swap A, Swap B)

```
Stack A: [3, 1, 2]  (3 top, 2 bottom)

sa (top 2'yi swap et):
Stack A: [1, 3, 2]  (1 top, 2 bottom)
```

**Neden gerekli?**
```
Bazen küçük optimizasyon gerekir. Mesela:
Stack A: [5, 4, ...]

sa ile:
Stack A: [4, 5, ...]

Sonra pb ve diğer operasyonlar daha verimli oluyor.
```

### ra / rb (Rotate A, Rotate B)

```
Stack A: [3, 1, 2]  (3 top, 2 bottom)

ra (first → last):
Stack A: [1, 2, 3]  (1 top, 3 bottom)

Visualization:
┌─────┐        ┌─────┐
│  3  │ top    │  1  │ top
├─────┤        ├─────┤
│  1  │   →    │  2  │
├─────┤        ├─────┤
│  2  │ bottom │  3  │ bottom
└─────┘        └─────┘
```

**Kod:**
```c
void ra(t_stack *a, t_flags *flag) {
    if (!a || a->size < 2) return;

    first = a->top;
    a->top = first->next;
    a->top->prev = NULL;

    first->next = NULL;
    first->prev = a->bottom;
    a->bottom->next = first;
    a->bottom = first;
}
```

### rra / rrb (Reverse Rotate)

```
Stack A: [3, 1, 2]  (3 top, 2 bottom)

rra (last → first):
Stack A: [2, 3, 1]  (2 top, 1 bottom)

Visualization:
┌─────┐        ┌─────┐
│  3  │ top    │  2  │ top
├─────┤        ├─────┤
│  1  │   →    │  3  │
├─────┤        ├─────┤
│  2  │ bottom │  1  │ bottom
└─────┘        └─────┘

Why doubly-linked important:
- prev pointer ile bottom'a erişebiliriz → O(1)
- singly-linked olsaydı tail'a gitmek → O(n) olurdu!
```

---

## BÖLÜM 4: DÖRT ALGORITHM DETAYLI (8-10 dakika)

### ALGORITHM 1: SIMPLE (O(n²))

**Konsept:**
```
Temel seçim sort (selection sort) adapte etme:

1. En küçük elemanı bul
2. Ona erişmek için rotate et
3. pb ile B'ye taşı
4. Tekrarla tüm elementler B'de olana kadar
5. Sonra B'den A'ya all geri tak (artık sıralı)
```

**Detaylı Adım Adım [3, 1, 2]:**
```
Start:
A: [3, 1, 2]
B: []

Step 1: min bulma (1 - position 1)
- Rotate 1'i top'a getir: ra
A: [1, 2, 3]

Step 2: pb (1'i B'ye taşı)
A: [2, 3]
B: [1]

Step 3: min = 2 (position 0)
- Zaten top → pb
A: [3]
B: [2, 1]

Step 4: min = 3 (position 0)
- Zaten top → pb
A: []
B: [3, 2, 1]

Step 5: B'den A'ya geri (tüm)
- pa, pa, pa
A: [1, 2, 3]  ✅ SORTED
B: []
```

**Kod (simple.c):**
```c
void simple_sort(t_stack *a, t_stack *b, t_flags *flag) {
    while (a->size > 0) {
        min_index = find_min_index(a);      // Min ararız
        rotate_simple(a, min_index, flag);  // Top'a getir
        pb(a, b, flag);                     // B'ye taşı
    }
    while (b->size > 0)
        pa(a, b, flag);                     // Geri koy
}

static int find_min_index(t_stack *a) {
    // Stack'i scan et, minimum'u bul
    // Döndür: position (top'tan uzaklık)
}

static void rotate_simple(t_stack *a, int idx, t_flags *flag) {
    if (idx <= a->size / 2) {
        // ra (forward) daha hızlı
        while (idx-- > 0) ra(a, flag);
    } else {
        // rra (backward) daha hızlı
        int r = a->size - idx;
        while (r-- > 0) rra(a, flag);
    }
}
```

**Neden O(n²)?**
```
Her element için:
- Scan: O(n)      (minimum'u bulma)
- Rotate: O(n)    (worst case tüm stack'i döndür)
- Total: n × (n + n) = O(2n²) = O(n²)

100 element: ~10,000 operasyon (worst case)
5 element: ~50 operasyon
```

**Testim:**
```bash
$ ./push_swap --simple 5 4 3 2 1
# Output: ~14 operasyon (5 pb, 5 pa, rotation işlemleri)
```

---

### ALGORITHM 2: MEDIUM (O(n√n))

**Konsept:**
```
Chunk-based partitioning:
1. √n chunks'a böl
2. Her chunk'ı sırayla B'ye push et
3. Max'ları B'den geri A'ya koy

Örnek (36 element):
- Chunk size = 36
- Chunk 0: index 0-35
- Chunk 1: index 36-... (ama sadece 36 varsa, olmaz)

Neden O(n√n)?
- √n chunks
- Her chunk: O(n) tarama + push
- Total: √n × n = O(n√n)
```

**Detaylı [1, 5, 2, 4, 3]:**
```
Index assign (rank by value):
1→0, 2→1, 3→2, 4→3, 5→4

A: [1(0), 5(4), 2(1), 4(3), 3(2)]
B: []

Chunk = 15 (5 element için)

push_chunks_to_b (limit = 14):
- Scan A, ilk indx≤14 bulana kadar
- Find 1(0) at position 0
- pb (1 taşı)
  A: [5(4), 2(1), 4(3), 3(2)]
  B: [1(0)]

- Find 5(4) at position 0
- pb (5 taşı)
- B'nin top 5(4) middle'dan büyük mü? Evet → rb
  A: [2(1), 4(3), 3(2)]
  B: [1(0), 5(4)]

... (devam)

push_back_to_a:
B'de max'ı bulma (5 - indx 4)
- Rotate B, 5'i top'a getir
- pa (geri koy)

... (devam - tüm B clear olana kadar)

Sonuç:
A: [1, 2, 3, 4, 5]  ✅
```

**Kod (medium.c):**
```c
void medium_sort(t_stack *a, t_stack *b, t_flags *flag) {
    assign_indices(a);           // Rank verileri

    if (a->size <= 100)
        chunk = 15;              // Küçük input
    else
        chunk = 36;              // Büyük input

    push_chunks_to_b(a, b, chunk);  // Chunks'u B'ye taşı
    push_back_to_a(a, b, flag);     // B'den A'ya geri (sorted)
}

static void push_chunks_to_b(t_stack *a, t_stack *b, int chunk, t_flags *f) {
    int limit = chunk - 1;

    while (a->size > 0) {
        rotate_a_to_chunk(a, limit, f);  // Top'a getir
        pb(a, b, f);                      // B'ye taşı

        if (b->top && b->top->indx < limit - chunk/2)
            rb(b, f);                     // Optimize: bottom'a push

        if (b->size > limit + 1)
            limit += chunk;               // Sonraki chunk'a hazırlan
    }
}
```

**Neden O(n√n)?**
```
Chunk count: √n
Her chunk işlemi: O(n)
Total: √n × n = O(n√n)

100 element (chunk=15, ~7 chunk):
- ~100 * 7 = ~700 theoretical
- Pratik: ~500-800 (optimize edilmiş B rotasyonlar)

5 element (chunk=15, 1 chunk):
- ~5 * 1 = ~5 theoretical
- Pratik: ~12-15 (rotations overhead)
```

---

### ALGORITHM 3: COMPLEX (O(n log n)) - Radix Sort

**Konsept:**
```
LSD (Least Significant Digit) Radix Sort adapted:

1. Index'leri binary bit'lere çevir
2. Her bit Position'ı için:
   a. Bit=1 ise: ra (forward rotate)
   b. Bit=0 ise: pb (B'ye push)
   c. B'yi A'ya geri koy (tüm)

Neden çalışıyor?
- Bit 0 (least significant) işlenmesi → chunks least significant bit'e göre
- Bit 1, 2, 3... işlendikçe → daha significant bits sort edilir
- Final = completely sorted

Örnek binary (3 element):
1→001, 2→010, 3→011

Bit 0:
1(001) → bit=1 → ra
2(010) → bit=0 → pb
3(011) → bit=1 → ra
pa B'den → [1, 3, 2]

Bit 1:
1(001) → bit=0 → pb
3(011) → bit=1 → ra
2(010) → bit=1 → ra
pa B'den → [2, 1, 3]

Bit 2:
... (final sort)
```

**Detaylı Code Flow:**
```c
void complex_sort(t_stack *a, t_stack *b, t_flags *flag) {
    complex_assign_indices(a);           // Index = rank
    int max_bits = complex_max_bits_for_size(a->size);
    // 5 element için: max_bits = 3 (2^2=4 < 5 ≤ 2^3=8)

    for (int bit = 0; bit < max_bits; bit++) {
        complex_run_radix_pass(a, b, flag, bit);
        // Her bit position'ı işle
    }
}

void complex_run_radix_pass(t_stack *a, t_stack *b, t_flags *flag, int bit) {
    int size = a->size;

    for (int i = 0; i < size; i++) {
        // a->top'un bit'i kontrol et
        if (((a->top->indx >> bit) & 1) == 1)
            // Bit 1 ise: forward rotate
            ra(a, flag);
        else
            // Bit 0 ise: B'ye push
            pb(a, b, flag);
    }

    // B'den tümünü A'ya geri koy
    while (b->size > 0)
        pa(a, b, flag);
}
```

**Binary Bit Extraction:**
```
Örnek: 5 (binary: 101)

bit=0 (LSB):
5 >> 0 = 101 = 5
5 & 1 = 1 (bit 0 = 1) ✓

bit=1:
5 >> 1 = 10 = 2
2 & 1 = 0 (bit 1 = 0) ✓

bit=2 (MSB):
5 >> 2 = 1
1 & 1 = 1 (bit 2 = 1) ✓

Yani: 5 = 1 0 1 (MSB → LSB)
```

**Neden O(n log n)?**
```
Passes: log₂(n)    (her bit'i işle)
Her pass: 3n       (n ra/pb + n pa return)
Total: log₂(n) × 3n = O(n log n)

5 element (max_bits=3):
- 3 passes
- Her pass: ~5*3 = ~15 ops
- Total: ~45 ops (theoretical)
- Pratik: ~25 (bazı optimizations)

100 element (max_bits=7):
- 7 passes
- Her pass: ~300 ops
- Total: ~2100 ops (theoretical)
- Performance target: <2000 ✓ (possible with good constants)
```

---

### ALGORITHM 4: ADAPTIVE

**Konsept:**
```
Input'ı analyze et → en uygun algoritmayı seç

Disorder nedir?
- 0 = perfectly sorted
- 1 = completely reverse sorted
- 0.5 = 50% unsorted

Formula:
disorder = inversions / total_pairs

Inversion = büyük sayı, küçükten önce geliyorsa
```

**Disorder Calculation [5, 2, 4, 1, 3]:**
```
Pairs: (5,2), (5,4), (5,1), (5,3), (2,4), (2,1), (2,3), (4,1), (4,3), (1,3)
Total: 10

Inversions:
(5,2) ✓, (5,4) ✓, (5,1) ✓, (5,3) ✓     = 4
(2,1) ✓                                 = 1
(4,1) ✓, (4,3) ✓                        = 2
= 7 inversions

disorder = 7/10 = 0.7 (70% unsorted)
```

**Kod:**
```c
double compute_disorder(t_stack head) {
    double mistakes = 0;
    double total_pairs = 0;

    for (int i = 0; i < size; i++) {
        int firstv = get_value_at_index(head, i);
        for (int j = i + 1; j < size; j++) {
            total_pairs++;
            int secondv = get_value_at_index(head, j);
            if (firstv > secondv)  // Inversion!
                mistakes++;
        }
    }

    if (total_pairs == 0) return 0.0;
    return mistakes / total_pairs;
}
```

**Adaptive Thresholds:**
```
if (disorder < 0.2)
    simple_sort();        // Çoğu sorted → simple yeterli
else if (disorder < 0.5)
    medium_sort();        // Orta chaotic → medium iyisi
else
    complex_sort();       // Çok random → complex gerekli
```

**Mantık:**
```
[1, 2, 3, 4, 5] → disorder = 0 → SIMPLE
- Sadece rotations, 0 pb/pa

[5, 1, 4, 2, 3] → disorder = 0.4 → MEDIUM
- Chunks işe yarar, ~12-15 ops

[5, 4, 3, 2, 1] → disorder = 1.0 → COMPLEX
- Radix sort optimal, ~15-20 ops
```

---

## BÖLÜM 5: BENCHMARK MODE (1-2 dakika)

**Ne işe yarar?**
```
--bench flag ile, işlem detaylarını görebiliriz:

$ ./push_swap --bench --simple 5 4 3 2 1 2>&1

[bench] disorder: 100.00%
[bench] strategy: Simple / $O(n^2)$
[bench] total_ops: 14
[bench] sa: 0 sb: 0 ss: 0 pa: 5 pb: 5
[bench] ra: 1 rb: 0 rr: 0 rra: 3 rrb: 0 rrr: 0
```

**Bilgiler:**
```
- Disorder: Input'ın %kaçı unsorted
- Strategy: Hangi algoritma kullanıldı
- Total ops: Kaç operasyon gerekti
- Per-op counts: Her operasyon kaç kez yapıldı

Debugging ve optimization'da çok yararlı!
```

---

## BÖLÜM 6: PARSER & ERROR HANDLING (2 dakika)

### Argument Parsing

**Kabul edilen formatlar:**
```bash
# Format 1: Çoklu argument
./push_swap 5 4 3 2 1

# Format 2: Quoted string (whitespace içerebilir)
./push_swap "5 4 3 2 1"

# Format 3: Flags (algoritma seçme)
./push_swap --simple 5 4 3 2 1
./push_swap --bench --adaptive 5 4 3 2 1
```

**Parser Flow (parse.c):**
```c
read_args(argc, argv, flags, parse) {
    handle_flags();           // --simple, --complex vb.

    if (argc-start == 1)
        parse_single_arg();   // Tek arg, quoted string
    else
        parse_multi_arg();    // Çoklu arg

    check_numbers();          // Validasyon
}
```

### Error Handling

**4 Zorunlu Hata:**
```bash
# 1. Non-numeric
./push_swap 5 4 abc 2 1
# Error

# 2. Duplicate
./push_swap 5 4 3 3 1
# Error

# 3. MAXINT overflow
./push_swap 5 99999999999 3 2 1
# Error

# 4. No arguments (special case)
./push_swap
# (nothing output, prompt returned)
```

**Kod (checks.c):**
```c
int error(void) {
    write(2, "Error\n", 6);  // stderr'e "Error\n"
    exit(1);
}

void check_numbers(char **args) {
    for (int i = 0; args[i]; i++) {
        if (!is_numstr(args[i]))       // Sayı mı?
            error();
        long num = ft_atol(args[i]);
        if (!is_intranger_range(num))  // INT range?
            error();
    }
    if (has_dup(args))                // Duplicate?
        error();
}
```

---

## BÖLÜM 7: PERFORMANCE & METRICS (1-2 dakika)

### Test Results
```
Input Size: 3 elements
- Checker: OK ✓
- Operations: ~2-10 (algorithm type'a bağlı)

Input Size: 5 elements
- Checker: OK ✓
- Operations: ~12-25 (algorithm type'a bağlı)

Input Size: 100 elements
- Adaptive (disorder ~50%): ~500-800 ops (target: <2000) ✓
- Pure random: ~800-1200 ops

Input Size: 500 elements
- Adaptive (disorder ~50%): ~2000-3000 ops (target: <12000) ✓
```

### Optimization Techniques
```
1. Rotate selection
   - idx ≤ size/2 → ra (forward)
   - idx > size/2 → rra (backward)
   → Half operations saved!

2. Chunk sizing
   - 15 for small inputs
   - 36 for large inputs
   → Balanced performance

3. Bit manipulation (radix)
   - LSB to MSB processing
   - Each bit pass completely sorts that digit
```

---

## BÖLÜM 8: BAŞTAN SONA DEMO (3-5 dakika)

### Live Example: [3, 1, 4, 2]

**ADAPTIVE mode (disorder hesapla ve uygun algoritma seç):**

```bash
$ ./push_swap 3 1 4 2

Index Assignment:
1→0, 2→1, 3→2, 4→3
A: [3(2), 1(0), 4(3), 2(1)]

Disorder:
Pairs: (3,1)✓, (3,4), (3,2)✓, (1,4), (1,2)✓, (4,2)✓
= 4 inversions / 6 pairs = 0.67 (67%)
→ disorder ≥ 0.5 → COMPLEX (Radix)

Radix Process (max_bits = 2):

Bit 0 (LSB):
- 3(2)=10 → bit0=0 → pb → A: [1,4,2], B: [3]
- 1(0)=00 → bit0=0 → pb → A: [4,2], B: [1,3]
- 4(3)=11 → bit0=1 → ra → A: [2,4], B: [1,3]
- 2(1)=01 → bit0=1 → ra → A: [4,2], B: [1,3]
- pa pa → A: [1,2,4,3], B: []

Bit 1:
- 1(0)=00 → bit1=0 → pb → A: [2,4,3], B: [1]
- 2(1)=01 → bit1=0 → pb → A: [4,3], B: [2,1]
- 4(3)=11 → bit1=1 → ra → A: [3,4], B: [2,1]
- 3(2)=10 → bit1=1 → ra → A: [4,3], B: [2,1]
- pa pa → A: [1,2,3,4], B: []

✅ SORTED!
```

**Output:**
```
pb
ra
ra
pa
pa
pb
pb
ra
ra
pa
pa
```

---

## BÖLÜM 9: KIŞI SORUMLULUKLARI (1 dakika)

### metaskin (Meltem):
```
1. Adaptive algorithm
   - Disorder hesapla
   - Threshold'a göre seç

2. Benchmark mode
   - Stderr output
   - Format ve precision

3. README & Documentation
   - Algorithm explanations
   - Contributors section
   - Usage examples

4. Project integration
   - Main flow koordine et
   - Flags system
```

### asobolev (Alex):
```
1. Stack operations (11 total)
   - Push (pa, pb)
   - Swap (sa, sb, ss)
   - Rotate (ra, rb, rr)
   - Rev-Rotate (rra, rrb, rrr)
   - Doubly-linked pointer updates

2. Simple algorithm
   - Min-finding logic
   - Rotation strategy (optimal direction)

3. Core data structures
   - t_node, t_stack
   - Memory allocation
   - Stack initialization
```

---

## BÖLÜM 10: SORULARA HAZIR OLMA (Evaluator'un sıkça soruları)

### Q1: "Neden doubly-linked list?"
```
A: Reverse rotate (rra, rrb) operasyonları için.

Single linked olsaydı:
- rra → bottom'a erişmek → O(n) (başından scan)
- Her reverse rotate → n scan!

Doubly linked:
- prev pointer ile bottom'a → O(1)
- rra → O(1)

100 element, sık reverse rotate → 100 operasyon vs 10000 scan
```

### Q2: "Why adaptive? Why these thresholds?"
```
A: Input'ın "shape"ine göre algoritma seçme.

[1,2,3,4,5] (disorder 0) → SIMPLE (rotations yeterli)
[random order] (disorder 1) → COMPLEX (radix optimal)

Thresholds (0.2, 0.5):
- Empiik test ile buldum
- 100-500 element deneyler yapıldı
- 0.2'den az → simple yeterli
- 0.2-0.5 → medium balanced
- 0.5+ → complex gerekli

Alternative: Her zaman complex?
→ Sorted input'ta O(n log n) = n*log(n) ops
→ Adaptive simple → 0 ops (daha iyi!)
```

### Q3: "Radix sort nasıl çalışıyor?"
```
A: Bit-by-bit processing.

Binary:
1 = 001
2 = 010
3 = 011

Bit 0 (rightmost):
- 1'in bit0 = 1 (ra - top'a)
- 2'nin bit0 = 0 (pb - B'ye)
- 3'ün bit0 = 1 (ra - top'a)

Bit 1:
- ...tekrar...

Final: tamamen sorted

Neden çalışıyor?
- LSD → each pass bir "digit"i sorts
- Digit 0 → 1 → 2... işlenince
- İlk digit'in sort'u preserved
- Final = all digits sorted
```

### Q4: "Performance targets nasıl meet ediliyor?"
```
A: Algorithm seçme + optimizations.

100 element target: <2000
- Adaptive → disorder'a göre seç
- Average disorder ≈ 0.5 → medium
- Medium: √100 * 100 = 1000 theoretical
- Pratik: 500-800 (good!)

Optimizations:
1. Rotation direction seçme (forward vs backward)
2. Chunk sizing (15 vs 36)
3. Bit manipulation (efficient radix)
4. Stack pointer caching
```

### Q5: "Memory leaks kontrol edildi mi?"
```
A: Evet, valgrind clean.

Stack_build:
- malloc her node için
- clear_stack: free tüm nodes

Split:
- malloc string array
- free_split: free tüm strings + array

Hata durumunda:
- error() → exit(1), leaks kabul (exit cleanup)
- Normal path → all freed

Valgrind test:
$ valgrind --leak-check=full ./push_swap 5 4 3 2 1
# No leaks
```

### Q6: "Edge case: empty string?"
```
A: Error çıkartır.

./push_swap ""
→ is_empty_token() detects
→ error() → stderr "Error\n"
→ exit(1)

Diğer edge cases:
- Duplicate: error ✓
- MAXINT: error ✓
- No args: (nothing) ✓
- Whitespace only: error ✓
- Non-numeric: error ✓
```

### Q7: "Norminette compliance?"
```
A: 100% compliant.

Kontrol noktaları:
- 40 character limit (function lines)
- Header guards
- Function names
- Forbidden global vars (none)
- Comment style

$ norminette include/ src/
# No errors
```

---

## 🎯 SUNUM SÜRESİ ÖZETI

| Section | Duration |
|---------|----------|
| 1. Intro | 2-3 min |
| 2. Data Structures | 2 min |
| 3. Operations | 3 min |
| 4. Algorithms | 8-10 min |
| 5. Benchmark | 1-2 min |
| 6. Parser | 2 min |
| 7. Performance | 1-2 min |
| 8. Live Demo | 3-5 min |
| 9. Responsibilities | 1 min |
| 10. Q&A | 5-10 min |
| **TOTAL** | **~30-40 min** |

---

## 💡 SUNUM İPUÇLARı

### İYİ YAPIŞLAR:
1. ✅ Whiteboard veya paper'da diagram çiz
2. ✅ Kodları adım adım trace et
3. ✅ Lineer değil, hiyerarşik anlatış
4. ✅ Neden yapıldığını açıkla (nasıl değil)
5. ✅ Hata durumlarına değin
6. ✅ Trade-off'ları söyle (time vs space)
7. ✅ Performance metriklerini göster
8. ✅ Partner'ın katkısını öne çıkar

### KÖTÜ YAPIŞLAR:
1. ❌ Tüm 1000 satırı kodunu oku
2. ❌ Detaylara gömülme
3. ❌ "Basit, algoritma biliyorsunuz" deme
4. ❌ Partner'ı görmezden gel
5. ❌ Complexity proof verme (O(n log n) dedim yeter)
6. ❌ Sıkılmış görünme

---

## 📚 REFERANS KOMUTLAR

```bash
# Projeyi test et
make clean && make
./push_swap 5 4 3 2 1

# Algoritmaları test et
./push_swap --simple 5 4 3 2 1
./push_swap --medium 5 4 3 2 1
./push_swap --complex 5 4 3 2 1
./push_swap --adaptive 5 4 3 2 1

# Benchmark görüntüle
./push_swap --bench --simple 5 4 3 2 1 2>&1

# Checker ile validasyon
ARG="3 2 1"; ./push_swap $ARG | ./checker_Mac $ARG

# Disorder test
./push_swap --bench --adaptive 1 2 3 4 5 2>&1 | grep disorder
# disorder: 0.00% (already sorted)

./push_swap --bench --adaptive 5 4 3 2 1 2>&1 | grep disorder
# disorder: 100.00% (reverse sorted)
```

---

## 🎓 FINAL CHECKLIST

Defense öncesi:
- [ ] Tüm 4 algoritmayu anlatabiliyorum
- [ ] Karmaşık operasyonları (radix, reverse-rotate) trace edebiliyorum
- [ ] Partner'ın katkısını biliyorum
- [ ] Why questions'a cevap hazır
- [ ] Live demo'yu practice ettim
- [ ] Diagram'ları hazırladım
- [ ] Performance metrics'i biliyorum
- [ ] Edge cases'i test ettim

**BAŞARILAR!** 🚀
