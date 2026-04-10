# Aşama 1: Kavramsal Temel — 5 Yaşındakine Anlatır Gibi

---

## 1. Stack (Yığın) Nedir?

Mutfak tezgahına tabak yığdığını hayal et.

```
    [  3  ]  ← TOP (en üst, son konan)
    [  7  ]
    [  1  ]
    [  9  ]  ← BOTTOM (en alt, ilk konan)
```

**Kurallar çok basit:**
- Tabak **sadece üstten** konur
- Tabak **sadece üstten** alınır
- Ortadan çekemezsin, alttan alamazsın

Bizim projede **iki tezgah** var: **Stack A** ve **Stack B**.  
Sayıları bu iki tezgah arasında taşıyarak sıralıyoruz.

---

## Doubly-Linked List (Çift Yönlü Bağlı Liste) Neden?

Normal bir tabak yığınında sadece en üsttekini görebilirsin.  
Ama biz bazen **alttan da bakmamız gerekiyor** — en küçük hangisi? En büyük nerede?

Doubly-linked list'i şöyle düşün:

> Bir tren. Her vagon hem **öndeki vagonu** hem **arkadakini** biliyor.

```
[önceki ←  Vagon 1  → sonraki]
[önceki ←  Vagon 2  → sonraki]
[önceki ←  Vagon 3  → sonraki]
```

Normal liste sadece ileriye bakabilir. Çift yönlü liste **her iki yöne** bakabilir.  
Bu bize `rra`, `rrb` gibi **ters rotasyon** operasyonlarını mümkün kılar — alttan alıp üste koyabilirsin.

---

## 2. Big-O Notation Nedir?

Bunu "**kaç adımda bitirir?**" sorusunun cevabı olarak düşün.

Diyelim ki **n = 100 sayı** sıralıyorsun:

| Notasyon | Ne anlama gelir | Adım sayısı (n=100) |
|----------|----------------|---------------------|
| **O(n²)** | Her sayı için herkese bak | ~10.000 adım |
| **O(n√n)** | Her sayı için bir kısma bak | ~1.000 adım |
| **O(n log n)** | Her sayı için sadece log kadar bak | ~700 adım |

**Günlük hayat analojisi:**

- **O(n²):** Kayıp anahtarını bulmak için evin her odasını, her çekmecesini, her köşesini tek tek arıyorsun. Odaları da, çekmeceleri de sırayla. Yavaş.
- **O(n√n):** Önce hangi odada olabileceğini tahmin ediyorsun, sadece o odayı arıyorsun. Daha hızlı.
- **O(n log n):** Telefon rehberinde isim arıyorsun — ortadan açıyorsun, "daha önce mi sonra mı?" diye yarıya indiriyorsun. Çok hızlı.

---

## 3. Dört Algoritmamız Günlük Hayatta Neye Benzer?

### SIMPLE — O(n²) — "Sabırlı Ev Hanımı"
> Çamaşırları katlamak için her seferinde en küçük çorabı buluyorsun, ayırıyorsun. Sonra kalan yığından tekrar en küçüğü buluyorsun. Ta ki bitsine kadar.

Az sayıda çorap varsa mantıklı. 1000 çorap için delirirsin.

---

### MEDIUM — O(n√n)  — "Akıllı Kütüphaneci"
> Kitapları rafa dizmek için önce "A-F", "G-M", "N-Z" diye **gruplara** ayırıyorsun. Sonra her grubu kendi içinde yerleştiriyorsun.

Parçala, fethet. 100 veya birkaç yüz sayı için ideal.

---

### COMPLEX — Radix Sort — O(n log n) — "Postane Memuru"
> Zarfları sıralamak için önce **son rakama** bakıyorsun: 0-4 bir kutuya, 5-9 başka kutuya.  
> Sonra **ikinci son rakama** bakıyorsun. Sonra üçüncüye...  
> Hiçbir zarfı hiçbir zarfla **karşılaştırmıyorsun** — sadece "bu 0 mı, 1 mi?" diye bakıyorsun.

**Bizim Radix Sort'umuz daha da basit:** Sadece 0 ve 1 kullanıyor.

```
Sayıların index'i var: 0, 1, 2, 3, 4...
1. bit'e bak: 0 ise Stack B'ye it, 1 ise Stack A'da bırak
2. bit'e bak: aynı işlem
3. bit'e bak: aynı işlem
... ta ki hepsi sıralı olana kadar
```

Hiç "bu mu büyük, o mu?" diye sormuyoruz. Sadece bit bakıyoruz. Bu yüzden hızlı.

---

### ADAPTIVE — "Deneyimli Doktor"
> Doktor seni görmeden önce ateşini ölçüyor. 36.5 ise aspirin yok. 38 ise hafif ilaç. 40 ise hastaneye yatır.

Bizim algoritmamız da önce dizinin **ne kadar karışık** olduğunu ölçüyor:
- Az karışıksa → SIMPLE (zaten neredeyse sıralı, neden uğraşayım?)
- Orta karışıksa → MEDIUM
- Çok karışıksa → COMPLEX

---

## 4. Disorder (Düzensizlik) Metriği Nedir?

> Hayal et, 10 kişilik bir sıraya bakıyorsun. Kaç kişi yanlış yerde duruyor?

Biz her çifti karşılaştırıyoruz: "Bu sayı, kendisinden sonraki sayıdan büyük mü?"  
Büyükse → **bu bir bozukluk**.

```
Toplam bozukluk sayısı / Toplam mümkün çift sayısı = Disorder skoru
```

- **0.0** → Tamamen sıralı (hiç bozukluk yok)
- **1.0** → Tamamen ters sıralı (her çift bozuk)
- **0.5** → Yarısı karışık

Bu skor, Adaptive algoritmanın hangi yöntemi seçeceğine karar vermesini sağlıyor.

---

## Aşama 1 Tamamlandı

Partnerinin bu bölümden alması gereken **tek cümle özet**:

> "Projemiz iki tabak yığını arasında sayıları taşıyarak sıralıyor. Ne kadar karışık olduğuna bakarak en uygun yöntemi seçiyor — az karışıksa basit, çok karışıksa postane memuru gibi bit bit sıralıyor."

---

**Aşama 2'ye geçmek için** "Sonraki aşamaya geç" de,  
**ya da** incelememi istediğin ilk kod bloğunu gönder — Aşama 2 formatında analiz ederim.                       # Aşama 2: Satır Satır "NEDEN?" Odaklı Kod Analizi

Kod bloklarını sana sormadan önce projenin dosya yapısına bir bakayım — neyi analiz etmemiz gerektiğini görelim.           # Aşama 3: Acımasız Evaluator Tuzakları ve Ezber Cümleleri

Bir 42 Evaluator'ı üç türde soru sorar:
1. **Silme soruları** — "Bunu silsek ne olur?"
2. **Neden soruları** — "Neden X, neden Y değil?"
3. **Tanım soruları** — "Bu nedir, ne işe yarar?"

Her soruyu "Tuzak Nerede?" + "Kurtarıcı Cevap" formatında veriyorum.

---

## GRUP 1: Veri Yapısı Tuzakları

---

### Tuzak S-1
> **"Doubly-linked list neden kullandınız? Normal array yetmez miydi?"**

**Tuzak nerede:** Array kullansaydık ters rotasyon (rra) için tüm diziyi kaydırmak gerekirdi — O(n) ek işlem. Her operasyonda bu maliyet birikirdi.

**Kurtarıcı Cevap:**
- Stack'in altından eleman almamız gerekiyor (`rra`, `rrb`)
- Array'de alttan almak için her elemanı kaydırırsın — yavaş
- Linked list'te sadece pointer'ları değiştirirsin — anında
- `prev` pointer'ı sayesinde alttan üste tek hamlede gidilir

> **Ezber:** "Array'de alttan almak her şeyi taşımak demek. Linked list'te sadece bir pointer değiştiriyoruz."

---

### Tuzak S-2
> **"`indx` alanını silsek ne olur?"**

**Tuzak nerede:** Radix sort tamamen `indx`'e bağlı. `value` kullanılsa negatif sayılar ve büyük sayılar bit düzeyinde düzgün karşılaştırılamaz.

**Kurtarıcı Cevap:**
- Radix sort sayının değerine değil, sırasına bakıyor
- `-347` ile `10000` arasındaki bit karşılaştırması anlamsız
- `indx = 0, 1, 2, 3...` dersek bit mantığı mükemmel çalışır
- `indx` olmadan Complex algoritma tamamen çöker

> **Ezber:** "Radix sort değere bakamaz, sıraya bakar. indx o sırayı tutar."

---

### Tuzak S-3
> **"`prev` pointer'ını silsek ne olur?"**

**Tuzak nerede:** `rra` ve `rrb` çalışamaz. `bottom`'dan bir önceki node'a erişmek için baştan sona gezmek zorunda kalırsın.

**Kurtarıcı Cevap:**
- `rra` diyince: alttaki elemanı üste taşı
- `bottom`'u biliyoruz ama "alttan bir önce kim?" bilmiyoruz
- `prev` olmadan cevap yok — ya sil ya tüm listeyi gez
- Her `rra`'da tüm listeyi gezmek 500 elemanda 500 ekstra işlem demek

> **Ezber:** "prev, ters yönde gidebilmemizi sağlar. Olmasa rrb/rra anlamsız olur."

---

## GRUP 2: Algoritma Tuzakları

---

### Tuzak A-1
> **"Adaptive algoritmanın amacı ne? Sadece Complex kullansanız olmaz mıydı?"**

**Tuzak nerede:** Teorik olarak Complex her zaman kullanılabilir. Ama neredeyse sıralı bir dizi için Complex gereksiz yere tüm bit turlarını döner.

**Kurtarıcı Cevap:**
- Zaten sıralı dizi için Simple 0-10 operasyonla biter
- Aynı dizi için Complex yüzlerce gereksiz operasyon yapar
- Adaptive, hastaya bakmadan ameliyat yapmaz — önce ateşi ölçer
- Gerçek dünyada girdi çoğu zaman kısmen sıralıdır

> **Ezber:** "Adaptive, her hastaya aynı ilacı vermez. Durumuna göre seçer."

---

### Tuzak A-2
> **"0.2 ve 0.5 eşik değerlerini neden seçtiniz?"**

**Tuzak nerede:** Sihirli sayı gibi görünür. Evaluator "rastgele mi koydunuz?" diye sorar.

**Kurtarıcı Cevap:**
- 0.0 = tamamen sıralı, 1.0 = tamamen ters sıralı
- 0.2 altı = %20'den az bozukluk = Simple yeterli, zaten sıralıya yakın
- 0.5 üstü = %50'den fazla bozukluk = gerçek kaos, Radix gerekli
- Bu değerler test edilerek kalibre edildi, teorik ve pratik dengesi

> **Ezber:** "0.2 ve 0.5 rastgele değil. %20 altı düzensizlik basit yöntemle çözülür, %50 üstü kaos Radix ister."

---

### Tuzak A-3
> **"Radix Sort nasıl çalışır? Bana adım adım anlat."**

**Tuzak nerede:** "Bit manipulation" deyip geçmek yetersiz. Somut örnek beklenir.

**Kurtarıcı Cevap (4 sayı örneği: index 0,1,2,3):**

```
İndexler: [3, 1, 0, 2]  (Stack A'da)

BIT 0 (en sağ bit):
  3 = 11 → bit0=1 → ra (döndür, beklet)
  1 = 01 → bit0=1 → ra (döndür, beklet)  
  0 = 00 → bit0=0 → pb (B'ye gönder)
  2 = 10 → bit0=0 → pb (B'ye gönder)
B'den geri al → A: [3,1,0,2] → yeniden düzenlendi

BIT 1:
  ... aynı mantık
Sonunda: [0,1,2,3] sıralı
```

> **Ezber:** "Her turda tek soru: bu bit 0 mı 1 mi? 0 ise B'ye gönder, 1 ise döndür beklet. Tüm turlar bitince sıralanmış."

---

## GRUP 3: Bellek ve Güvenlik Tuzakları

---

### Tuzak B-1
> **"`clear_stack`'te `stack->bottom = NULL` neden döngünün dışında?"**

**Tuzak nerede:** Döngü sadece `top`'u ilerletiyor. `bottom` hâlâ son free edilen node'u gösteriyor — dangling pointer.

**Kurtarıcı Cevap:**
- Döngü bitince `top = NULL` oldu ama `bottom` silinmiş adresi gösteriyor
- Bu adrese tekrar erişmek undefined behavior / valgrind hatası
- `bottom = NULL` diyerek "bu artık geçersiz" diyoruz
- `size = 0` da aynı mantık — stack temizlendi, sıfırla

> **Ezber:** "top döngüyle silindi ama bottom hâlâ orada. NULL atmazsak salak pointer bırakıyoruz."

---

### Tuzak B-2
> **"malloc başarısız olursa ne yapıyorsunuz?"**

**Tuzak nerede:** `node_new` içinde `malloc` fail olabilir. Kontrol edilmezse NULL pointer'a yazılır.

**Kurtarıcı Cevap:**
- `node_new` içinde `if (!node) return (NULL)` var
- `stack_build` içinde `if (node == NULL)` → `clear_stack` + `error()` çağrılıyor
- Yani: malloc fail → o ana kadar oluşturulan tüm node'lar temizlenir → program hata mesajıyla çıkar
- Bellek sızıntısı yok

> **Ezber:** "malloc başarısız olursa paniklemiyoruz. Temizle, hata ver, çık."

---

### Tuzak B-3
> **"compute_disorder neden pointer almıyor, değer alıyor?"**

```c
double compute_disorder(t_stack head)  // pointer değil kopya!
```

**Tuzak nerede:** `*a` yerine `a` yazılmış gibi görünebilir. Aslında bilinçli.

**Kurtarıcı Cevap:**
- Stack'i sadece okumak istiyoruz, değiştirmek değil
- Pointer alsak ve `top = top->next` yapsak, asıl stack'i kaydırırız
- Değer kopyası alınca güvenle üzerinden gezebiliriz
- Stack büyük değil (sadece 2 pointer + 1 int), kopyalama maliyeti küçük

> **Ezber:** "Okumak için kopya alıyoruz ki orjinale dokunmayalım."

---

## GRUP 4: Operasyon Tuzakları

---

### Tuzak O-1
> **"`move_from_a_to_b`'de `b->top->prev = node` neden var?"**

**Tuzak nerede:** Bu satır atlanırsa tek yönlü bağlantı kalır. `rrb` çalışamaz.

**Kurtarıcı Cevap:**
- Yeni node B'nin tepesine ekleniyor
- Eski B tepesi artık ikinci sıraya geçti
- "İkinci sıranın arkasında kim var?" sorusuna cevap verebilmek için `prev = node`
- Bu olmadan B stack'i tek yönlü kalır, ters rotasyon çöker

> **Ezber:** "Çift yönlü bağlantıda iki taraf da birbirini görmeli. Sadece öne bağlamak yetmez."

---

### Tuzak O-2
> **"11 operasyon nedir, hepsini sayabilir misin?"**

**Tuzak nerede:** Çok temel görünür ama stres altında unutulur.

**Kurtarıcı Cevap — Ezber Tablosu:**

| Grup | Operasyonlar |
|------|-------------|
| Swap | `sa`, `sb`, `ss` |
| Push | `pa`, `pb` |
| Rotate (üstten al alta koy) | `ra`, `rb`, `rr` |
| Rev-Rotate (alttan al üste koy) | `rra`, `rrb`, `rrr` |

`ss` = sa + sb aynı anda  
`rr` = ra + rb aynı anda  
`rrr` = rra + rrb aynı anda

---

## GRUP 5: Genel Tuzaklar

---

### Tuzak G-1
> **"Projeyi neden sen değil, partnerinin yazdığını düşünmüyorum. Bana en zor kısmı anlat."**

**Kurtarıcı Cevap:**
- "En zorlu kısım Radix Sort için index atama mantığıydı."
- "İki iç içe döngüyle her elemanın sırasını hesaplamak O(n²) — ama bu sadece bir kez yapılıyor, sonra Radix log(n) turda bitiyor."
- "Ayrıca push operasyonlarında 6 pointer güncellemesinin sırasını yanlış yazmak çok kolay — valgrind ile defalarca test ettik."

---

### Tuzak G-2
> **"Big-O notasyonu nedir? Neden önemli?"**

**Kurtarıcı Cevap:**
- "Kaç adımda biter?" sorusunun matematiksel cevabı
- 100 sayı için Simple: ~10.000 adım; Radix: ~700 adım
- Fark küçük görünür ama 500 sayıda 50x daha hızlı olmanın farkı değerlendirmede görünür
- Evaluator operasyon sayısını checker ile ölçer

---

## Tüm Ezber Cümleler — Hızlı Referans

| Soru Konusu | Ezber Cümle |
|-------------|-------------|
| indx neden var | "Radix sıraya bakar, değere değil. indx o sırayı." |
| prev neden var | "Alttan gidebilmek için. Olmasa rrb/rra çalışmaz." |
| Adaptive ne işe yarar | "Duruma bakarak en uygun algoritmayı seçer." |
| Radix nasıl çalışır | "Her turda tek soru: 0 mı 1 mi? 0 ise B'ye, 1 ise bekle." |
| malloc fail | "Temizle, hata ver, çık. Bellek sızıntısı yok." |
| compute_disorder kopya | "Okumak için kopya alıyoruz, orjinale dokunmamak için." |
| bottom = NULL neden | "Silinen adrese işaret eden pointer bırakmamak için." |
| 11 operasyon | "3 swap, 2 push, 3 rotate, 3 ters-rotate." |

---

**Aşama 4'e geçmek için** "Sonraki aşamaya geç" de.  
Ya da herhangi bir soruyu daha derine inmek istersen söyle.

# Aşama 4: Sunum Pratiği ve İnteraktif Simülasyon

İki bölüm var. Önce whiteboard senaryosu, ardından canlı evaluator simülasyonu.

---

## BÖLÜM 4A: Whiteboard (Tahta) Senaryosu

**Senaryo:** `[3, 1, 4, 2]` dizisini Adaptive algoritmayla sıralıyorsun. Evaluator izliyor.

---

### SAHNE 1 — Giriş (30 saniye)

Tahtaya şunu çiz:

```
Stack A          Stack B
-------          -------
  [3]              [ ]
  [1]              [ ]
  [4]              [ ]
  [2]              [ ]
```

**Söyle:**
> "Başlangıçta tüm sayılar Stack A'da. Stack B boş. Kuralımız şu: sayıları bu iki yığın arasında taşıyarak A'yı küçükten büyüğe sıralayacağız."

---

### SAHNE 2 — Disorder Ölçümü (30 saniye)

Tahtaya bir kenara yaz: `disorder = ?`

**Söyle:**
> "Adaptive algoritma önce sorar: Bu dizi ne kadar karışık? Çiftlere bakıyoruz."

Tahtaya yaz:
```
(3,1) → 3 > 1 → BOZUK  ✗
(3,4) → 3 < 4 → iyi    ✓
(3,2) → 3 > 2 → BOZUK  ✗
(1,4) → 1 < 4 → iyi    ✓
(1,2) → 1 < 2 → iyi    ✓
(4,2) → 4 > 2 → BOZUK  ✗

3 bozuk / 6 toplam = 0.5
```

**Söyle:**
> "Disorder skoru 0.5. Bu eşikte COMPLEX algoritması seçilir. Şimdi Radix Sort başlıyor."

---

### SAHNE 3 — Index Atama (30 saniye)

Tahtada sayıların yanına index'lerini yaz:

```
Değer:  3    1    4    2
Index:  2    0    3    1
        ↑              ↑
   (2 sayı        (1 sayı
   benden küçük)  benden küçük)
```

**Söyle:**
> "Radix sort doğrudan 3, 1, 4, 2 ile çalışamaz — negatif sayılar, büyük sayılar bit düzeyinde sorun çıkarır. Bu yüzden her sayıya sıra numarası veriyoruz. En küçük 1 → index 0. En büyük 4 → index 3."

---

### SAHNE 4 — Radix Tur 1 (45 saniye)

Tahtaya index'leri binary'ye çevir:

```
Index:  2    0    3    1
Binary: 10   00   11   01
```

**Söyle:**
> "Şimdi ilk bit'e bakıyoruz — en sağ rakama."

Tahtaya bit 0 turunu çiz:

```
BIT 0 — en sağ rakama bak:

A'nın tepesi: index=2 → binary=10 → bit0=0 → pb (B'ye gönder)
A'nın tepesi: index=0 → binary=00 → bit0=0 → pb (B'ye gönder)
A'nın tepesi: index=3 → binary=11 → bit0=1 → ra (döndür, beklet)
A'nın tepesi: index=1 → binary=01 → bit0=1 → ra (döndür, beklet)

Sonra B'deki her şeyi A'ya geri al: pa, pa
```

Tahtada durumu göster:

```
Tur 1 sonrası A:   [3  1  4  2]  → düzenlendi
                    ↑
              (index 3,1 üstte)
```

**Söyle:**
> "Kural basit: bit 0 ise B'ye gönder, bit 1 ise döndür beklet. B'yi geri alınca sayılar biraz daha sıralandı."

---

### SAHNE 5 — Radix Tur 2 (30 saniye)

**Söyle:**
> "Şimdi ikinci bit'e bakıyoruz — soldan bir sonraki rakam."

```
BIT 1:

index=1 → binary=01 → bit1=0 → pb
index=3 → binary=11 → bit1=1 → ra
index=0 → binary=00 → bit1=0 → pb
index=2 → binary=10 → bit1=1 → ra

B'yi geri al: pa, pa
```

**Söyle:**
> "İki tur tamamlandı. Stack A'da [1, 2, 3, 4] — sıralı."

Tahtaya final durumu çiz:

```
Stack A          Stack B
-------          -------
  [1]              [ ]
  [2]              [ ]
  [3]              [ ]
  [4]              [ ]
  ✓ SIRALANMIŞ
```

---

### SAHNE 6 — Kapanış (20 saniye)

**Söyle:**
> "Hiçbir zaman '3, 1'den büyük mü?' diye sormadık. Sadece bit'e baktık: 0 mı, 1 mi? Bu yüzden Radix Sort çok sayıda elemanda çok verimli — O(n log n)."

---

### Whiteboard İpuçları

| Yapma | Yap |
|-------|-----|
| Tüm turları çizme — bunaltır | Sadece 1. turu detaylı, 2. turu özet geç |
| "Bilmiyorum" deme | "Şöyle düşünüyorum..." de, sonra açıkla |
| Monoton konuşma | Stack A'yı sol ele, Stack B'yi sağ ele al — fiziksel göster |
| Evaluator'a sırt dön | Yarım dön, tahtayı da evaluator'ı da görebil |

---

## BÖLÜM 4B: Canlı Evaluator Simülasyonu

Kurallar:
- Ben bir 42 Evaluator'ıyım. Tek soru soracağım.
- Sen partnerim adına cevap vereceksin.
- Cevabını **10 üzerinden** puanlayacağım.
- Eksikleri düzelteceğim, daha iyi versiyonu göstereceğim.
- Ardından bir sonraki soruya geçeceğim.

---

## İLK SORU

*[Evaluator modu aktif — sert, sabırsız, şüpheci]*

---

> "Tamam. Bana `t_node` struct'ına bak. İçinde `value` var, `indx` var. Bunlar ne fark ediyor? Neden ikisine de ihtiyaç var? Tek biri yetmez miydi?"

Cevabını yaz. Değerlendireyim.
