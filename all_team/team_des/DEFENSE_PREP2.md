# PUSH_SWAP DEFENSE PREPARATION

## 1. ALGORITHM AÇIKLAMALARI

### Simple (O(n²))
"Basit strateji: Her bilinmeyen sayıyı buluyoruz, stack A'nın başına döndürüyoruz, 
sonra stack B'ye itiyoruz. Veritabanı küçükse hızlı, çünkü n sayı için n² işlem yapabiliriz. 
Düzensizlik 0.2'den aşağıysa genellikle daha az toplam işlem gerekir."

### Medium (O(n√n))
"Sayıları √n boyutundaki parçalara böleriz. Stack A'yı tarayıp parça parça B'ye aktarırız, 
sonra en büyük değerleri geri A'ya koyarız. Basitlik ve verimliliğin dengesi - 
yaklaşık n√n işlem. Orta düzensizlik (0.2-0.5) için iyi."

### Complex (O(n log n))
"Radix sort kullanırız. Her bit pozisyonu için sayıları böleriz (0 veya 1 biti), 
sırasını değiştiririz. log(n) geçişten sonra tamamen sıralanır. 
Yüksek düzensizlik (>0.5) için en verimli."

### Adaptive
"Önce düzensizliği ölçeriz (0=sıralı, 1=ters). Sonra seçeriz:
- < 0.2: Simple kullan
- 0.2-0.5: Medium kullan
- >= 0.5: Complex kullan
Giriş şekline göre en verimli algoritmayi otomatik seçer."

---

## 2. CANLI GÖREV SİMÜLASYONU: --count-only Bayrağı

**Zaman limiti: 10 dakika**

### Aşamalar:
1. parser.h: struct s_flags'a `int count_only;` ekle
2. flags.c: `are_flags()` ve `apply_flag()` fonksiyonlarına --count-only desteği ekle
3. main.c: output kısmında count-only kontrolü yap ve sayıyı yazdır

### Test komutları:
```bash
./push_swap --count-only 3 2 1          # Çıktı: 10
./push_swap --count-only --simple 5 4 3 2 1  # Çıktı: 14
```

---

## 3. PERFORMANS HEDEFLERI

**100 sayı:**
- < 700: ⭐ MÜKEMMELk
- < 1500: ✓ İYİ
- < 2000: ○ GEÇER

**500 sayı:**
- < 5500: ⭐ MÜKEMMEL
- < 8000: ✓ İYİ
- < 12000: ○ GEÇER

---

## 4. SIK SORULAR VE CEVAPLAR

**S: Neden 4 algoritma?**
C: Farklı giriş şekillerine göre farklı algoritmalar daha verimlidir. 
Adaptive otomatik en iyisini seçer.

**S: Düzensizlik ne?**
C: Sayıların ne kadar karışık olduğu. 0=sıralı, 100=ters sıralı. 
Birkaç ters çifti sayarak hesaplarız.

**S: Radix sort nasıl çalışır?**
C: Bit bit işleriz. Her geçişte 0-bit ve 1-bit sayıları ayırırız. 
log(n) geçişten sonra sıralanır.

**S: Performance farkı?**
C: Simple: 700-1000 ops, Medium: 500-800 ops, Complex: 600-900 ops
(değişiyor - bundan dolayı Adaptive seçer)

---

## 5. CRITICAL CHECKLIST (Evo.md'den)

✅ ZORUNLU:
- No segfaults/crashes
- Norm: ✓ All pass
- Compilation: make/clean/fclean/re all work
- Error handling: non-numeric, duplicates, MAXINT overflow, no params
- Flags: --simple, --medium, --complex, --adaptive
- Identity: sorted input = no output
- 3-5 numbers: checker confirms OK
- 100 numbers: < 2000 ops
- 500 numbers: < 12000 ops
- Live code: --count-only in 10 min

✅ GIT:
- 2 contributor: metaskin + asobolev
- README: "This activity has been created..."

---

## 6. SON ANDAKİ KONTROL LİSTESİ

Önce:
```bash
# DEFENSE ÖNCÜ 15 DAKİKA
make clean && make              # Derle
make test                       # Test çalıştır (24/24 görmeli)
git shortlog -sne HEAD          # 2 contributor doğrula
sed -n '1p' README.md           # README ilk satırı kontrol
./push_swap --count-only 3 2 1  # count-only test
```

Defense sırasında:
- Sessiz dinle, soru sorun anlamadıysan
- README'yi göster "This activity..."
- Tüm flag'leri çalıştır
- Algoritmaları KENDİ KELİMELERİN İLE aç
- --count-only demo yap

---

## 7. ÖNEMLİ NOKTALAR

- **Test sonu:** Hep 24/24 PASSED görmelisin
- **Performance:** Şu an ~800 ops (100 num) ve ~6700 ops (500 num) - MÜKEMMEL
- **Contributors:** Tam 2 kişi, kalıcı olarak git'e yazılı
- **Norm:** Tüm dosyalar %100 pass
- **Fonksiyon:** Hiçbir crash, error veya memory leak yok

**Beklenen not: 75-100 puan** (Her şey mükemmel)

---

## DEFENSE SONRASI

1. Ekip arkadaşını github/main'daki yeni state'ten clone alması için uyar
2. Sonrası hep main'den çalış (merge sonrası)
3. Yeni feature'lar için yeni branch aç, PR yap

**GİT AKIŞI**:
```
meltem branch'ında geliştir
→ git push origin meltem
→ github'dan PR aç ya da
→ git checkout main; git merge meltem; git push origin main
```

---

### BAŞARILAR! 🎉
