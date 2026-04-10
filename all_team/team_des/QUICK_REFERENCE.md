# Push_Swap - Quick Reference Card (Defense Cheat Sheet)

Pocket'ta taşı, sunum sırasında hızlıca referans al!

---

## 🎯 SUNUM YAPISI (Sıra önemli!)

```
1. MERHABA (30 sec)
   "2 stack, 11 operasyon, integer sorting"

2. VERİ YAPILARI (1 min)
   "t_node (value, indx, next, prev)"
   "Why doubly-linked? Reverse rotate O(1)"

3. 11 OPERASYON (1 min - 2-3 demo)
   "pa/pb: push between stacks"
   "ra/rra: rotate vs reverse-rotate"
   "sa/sb: swap top 2"

4. 4 ALGORITHMS (10 min) ⭐ EN ÖNEMLİ
   a) SIMPLE: scan + rotate + pb, O(n²)
   b) MEDIUM: chunks, √n complexity
   c) COMPLEX: radix sort, O(n log n)
   d) ADAPTIVE: disorder → algorithm choose

5. BENCHMARK MODE (1 min)
   "Show: disorder%, strategy, ops count"

6. DEMO (5 min)
   ./push_swap --adaptive 3 1 4 2

7. Q&A (5-10 min)
```

---

## 🔑 KEY CONCEPTS

### Data Structure
```
┌─ node ─────────────┐
│ value: 42          │
│ indx: 2  (RANK!)   │  ← LSD Radix için kritik
│ next ──→           │     Index = sorted order'da pozisyon
│ prev ←──           │     Doubly-linked = O(1) reverse rotate
└────────────────────┘

Stack:
┌─ top   ─────────┐
│  node1          │ ← Push/pop buradan
│  node2          │ ← Rotations bu seviyede
└─ bottom        ─┘ ← Reverse rotate buradan
```

### Index (Rank) - ÇOK ÖNEMLİ!
```
Input:  [42, 10, 30]
Index:  [2,  0,  1]
        (sorted order'da pozisyon)

Neden? Radix sort'da binary bit'lerle işlem yapabilmek için
```

### 11 Operations (Kod satırı seviyesi)
```
pa/pb  → move top from B to A / A to B
sa/sb  → swap top 2 elements in A / B
ss     → both sa ve sb (1 op)
ra/rb  → rotate up (first→last)
rr     → both ra ve rb (1 op)
rra/rrb → rotate down (last→first) - doubly-linked kullanız!
rrr    → both rra ve rrb (1 op)
```

---

## 🧠 4 ALGORITHMS (Temel Akış)

### SIMPLE (O(n²))
```
While (a->size > 0):
  Find min in A
  Rotate to top
  pb (B'ye taşı)
While (b->size > 0):
  pa (A'ye geri - şimdi sıralı)

Worst: n*(n+n) = O(n²)
5 element: ~25-50 ops
```

### MEDIUM (O(n√n))
```
For each chunk (size ~15):
  While element in chunk exists at top:
    Rotate to top
    pb
    If in bottom half: rb (optimize)
Back to A (max'lardan):
  Find max in B
  Rotate to top
  pa

√n chunks * n per chunk = O(n√n)
100 element: ~500-800 ops
```

### COMPLEX (O(n log n)) - Radix
```
For bit=0 to log2(n):
  For each element in A:
    if (element.indx >> bit) & 1:
      ra (bit = 1)
    else:
      pb (bit = 0)
  pa all from B back to A

Each bit fully processes that digit
log(n) passes * 3n per pass = O(n log n)
5 element: ~15-25 ops
```

### ADAPTIVE
```
disorder = count_inversions / total_pairs
if disorder < 0.2:   simple()
elif disorder < 0.5: medium()
else:                complex()
```

---

## 📊 PERFORMANCE TABLE

| Input | Algorithm | Target | Est. Ops | Status |
|-------|-----------|--------|----------|--------|
| 3 | Simple | <5 | 5-10 | ✅ |
| 5 | Adaptive | <15 | 12-25 | ✅ |
| 100 | Adaptive | <2000 | 500-800 | ✅ |
| 500 | Adaptive | <12000 | 2k-3k | ✅ |

---

## 💻 DEMO COMMANDS

```bash
# Temel test
./push_swap 3 1 4 2

# Strategy-specific
./push_swap --simple 5 4 3 2 1
./push_swap --medium 5 4 3 2 1
./push_swap --complex 5 4 3 2 1
./push_swap --adaptive 5 4 3 2 1

# Benchmark
./push_swap --bench --adaptive 5 4 3 2 1 2>&1

# Checker
ARG="3 2 1"; ./push_swap $ARG | ./checker_Mac $ARG

# Disorder check
./push_swap --bench --simple 1 2 3 4 5 2>&1 | grep disorder
./push_swap --bench --simple 5 4 3 2 1 2>&1 | grep disorder
```

---

## ⚠️ SORULARA HAZIR CEVAPLAR

**"Neden doubly-linked?"**
→ Reverse rotate O(1) için, O(n) olmaması için

**"Neden adaptive?"**
→ Input shape'ine göre optimize, nearly-sorted 0 ops olabilir

**"Radix sort nasıl?"**
→ Bit by bit, LSB→MSB, her pass bir "digit"i sorts

**"Performance guarantee?"**
→ Thresholds empirically tested, adaptive seçim optimal

**"Memory leaks?"**
→ Valgrind clean, tüm malloc'lar freed

---

## ✅ DEFENSE CHECKLIST (İçinde tut!)

```
PRE-DEFENSE:
☐ Code compile ediliyor
☐ 24 test pass ediyor
☐ README contributors detailed
☐ 4 algorithms anlatılacak ready
☐ Demo 3-5 eksiklik var
☐ Partner katkısı biliyorum
☐ Q&A cevapları hazır

DURING:
☐ Whiteboard/paper diagram var
☐ Ses net, tempo orta
☐ Code trace et (full oku değil)
☐ Neden soruları var
☐ Göz iletişimi
☐ Partner'ı katılım sağla

AFTER:
☐ Hata soru sor önce dinle
☐ Açıkla + justify
☐ Emin değilsen "araştırırız" de
☐ Teşekkür et
```

---

## 🎓 BAŞARILI DEFENSE İPUÇLARI

1. **Başla basit** → karmaşık
2. **Diagram çiz** → zihinsel model yarat
3. **Code trace** → abstract değil gerçek
4. **Partner konuş** → single point of failure değil
5. **Hata sorularına hazır** → "bilmiyorum" daha iyi "uydurma"
6. **Performance metric göster** → slick görün
7. **Edge cases söyle** → thorough görün
8. **Tempo tuttur** → ne çabuk ne çok yavaş

---

## 🚀 BAŞLA!

```
EVALUATOR: "Projeyi anlatır mısınız?"

SEN: "Tabii. İki stack ve 11 operasyonla integerleri
      sıralıyoruz. Dört farklı sort algoritması yaptık:
      simple O(n²), medium O(n√n), complex O(n log n),
      ve adaptive disorder-based seçim.

      Veri yapısı olarak doubly-linked list kullandık
      çünkü reverse rotate O(1) olması gerekti.

      Adım adım anlatayım..."

(Whiteboard'a diagram çiz)
(Kod file'ı aç, trace et)
(./push_swap --adaptive 3 1 4 2 çalıştır, output göster)
(Benchmark göster)
```

---

**❗ EN ÖNEMLİ: Hızlı konuşma, kafa karıştırma, merakını duyar etme!**

**🎯 HEDEFİN: Evaluator'u impress et, değil sadece accept ettir!**

**✨ BAŞARILAR! 🚀**
