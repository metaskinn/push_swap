# Push_Swap: Sifirdan ve Cok Detayli Takim Ici Anlatim

Bu dokumanin hedefi su: projeyi hic bilmeyen bir kisi, sadece bunu okuyarak koda
girdiginde kaybolmadan ilerleyebilsin.

Bu anlatimda:

- Ne yaptigimizi,
- Hangi dosyanin neden var oldugunu,
- Algoritmalarin gercekte nasil isledigini,
- Nerelerde hata cikabilecegini,
- Nasil test ve debug yapilacagini

adim adim anlatacagiz.

## 1) Projenin temel fikri

Push_swap'ta hedef, verilen tam sayi listesini artan siraya getirecek bir komut listesi
uretmektir.

Buradaki kritik nokta: Program "sirali listeyi direkt yazmaz". Bunun yerine stack
operasyonlarini (sa, pb, ra gibi) satir satir yazar. Checker da bu komutlari uygular
ve sonuc dogru mu diye kontrol eder.

Yani bu bir "komut uretme" projesidir.

## 2) Oyunun kurallari: izinli operasyonlar

Elimizde iki stack var: a ve b.

Operasyon gruplari:

- Swap:
   - sa: a stack'inin ustteki iki elemanini degistir
   - sb: b stack'inin ustteki iki elemanini degistir
   - ss: sa + sb birlikte
- Push:
   - pa: b'nin ustunden alip a'ya koy
   - pb: a'nin ustunden alip b'ye koy
- Rotate:
   - ra: a'da top en alta gider
   - rb: b'de top en alta gider
   - rr: ra + rb birlikte
- Reverse rotate:
   - rra: a'da bottom en uste gelir
   - rrb: b'de bottom en uste gelir
   - rrr: rra + rrb birlikte

Bu 11 operasyon disinda hareket yok.

## 3) Veri modeli: niye linked list?

Kod: include/stack.h

Node:

- value: gercek integer degeri
- indx: algoritmalarin kullandigi siralama index'i (rank)
- next, prev: cift bagli liste baglari

Stack:

- top: stack'in ustu
- bottom: stack'in alti
- size: eleman sayisi

Neden cift bagli liste?

- top'tan pop/push kolay
- bottom'a erisim kolay
- rotate ve reverse rotate pointer oynatarak O(1) duzeyinde yapilabiliyor

## 4) Programin genel yasam dongusu

Kod: src/main.c

Main akis:

1. read_args
2. stackleri olustur
3. a stack'ini inputtan kur
4. disorder oranini hesapla
5. secilen algoritmayi kos
6. bench modunda rapor bas
7. bellek temizle

Buradan cok net su sonucu cikiyor:

- Parse ve validation gecmeden algoritma asamasina gecilmiyor.
- Hangi algoritma kosarsa kossun tek cikis noktasi operasyon satirlari.

## 5) Parse katmani detay

Ilgili dosyalar:

- src/parser/flags.c
- src/parser/parse.c
- src/parser/split.c
- src/parser/atol.c
- src/utils/parse_helpers.c
- src/utils/checks.c

### 5.1 Flag mantigi

Desteklenen flagler:

- --simple
- --medium
- --complex
- --adaptive
- --bench

Kurallar:

- Varsayilan algoritma adaptive
- Bir algoritma secildikten sonra ikinci algoritma flagi gelirse hata
- --bench tek basina algoritma secmez, ek moddur

### 5.2 Arguman birlestirme mantigi

Kod, su tip girisleri ele aliyor:

- ./push_swap 3 2 1
- ./push_swap "3 2 1"

Whitespace'in karmasik oldugu durumlarda da kontrol var. Bos token veya edge space
yanlis pattern olunca error() ile cikiyor.

### 5.3 Sayi kontrolu

Kontroller:

- karakter kontrolu (sadece +/- ve rakam)
- int araligi
- duplicate yasak

Hata olursa:

- stderr'e Error
- exit(1)

## 6) Stack olusturma ve temizlik

Kod: src/utils/stack.c

Fonksiyonlar:

- create_stack: bos stack baslatir
- node_new: yeni node ayirir
- stack_add_back: sona ekler
- stack_build: parse edilen stringleri node'a cevirip a'ya yukler
- clear_stack: tum node'lari free eder

Burada hata senaryosu dusunulmus: malloc fail olursa clear yapip error() cagiriyor.

## 7) Operasyonlarin gercek davranisi

Kod: src/ops/*

Her operasyon uc isi birden yapiyor:

1. Veri yapisini degistirir
2. total_ops ve op_count sayaclarini gunceller
3. enabled aciksa komut adini stdout'a basar

Bu tasarim guzel cunku:

- Algoritma kodu sadece sa/pb/ra gibi cagrilar yapiyor
- Yazdirma/sayma detayi operasyon katmaninda toplaniyor

### 7.1 Kisa mini ornek

Baslangic:

- a: [3, 1, 2]
- b: []

pb:

- a: [1, 2]
- b: [3]

ra:

- a: [2, 1]

pa:

- a: [3, 2, 1]
- b: []

Burada goruldugu gibi komutlarin etkisi tamamen pointer manipule ederek oluyor.

## 8) Disorder metrigi (adaptive'in kalbi)

Kod: src/algorithms/disorder.c

Amac: Girisin ne kadar bozuk oldugunu 0 ile 1 arasinda oranlamak.

Yontem:

- Tum (i, j), i < j ciftleri gezilir
- a[i] > a[j] ise inversion sayilir
- disorder = inversions / toplam_cift

Yorum:

- 0.0: sirali
- 0.1: az bozuk
- 0.6: hayli bozuk
- 1.0'a yakin: terse yakin

Bu deger adaptive secimde dogrudan kullaniliyor.

## 9) Algoritmalarin ayrintili isleyisi

### 9.1 Simple sort

Kod: src/algorithms/simple.c

Mantik:

1. a icinde min elemanin pozisyonunu bul
2. O pozisyona gore en az adimla top'a getir
    - ustteyse ra
    - alttaysa rra
3. pb ile min'i b'ye gonder
4. a bosalana kadar devam
5. en sonda b'den pa pa pa ile geri getir

Neden calisiyor?

- b'ye hep o anki minimum gittigi icin b'nin ustunde daha buyukler birikir
- pa ile geri donunce a artan duzende kurulur

Karma siklik:

- min bulma + donderme dongusu nedeniyle O(n^2) karakter

### 9.2 Medium sort (chunk tabanli)

Kod: src/algorithms/medium.c ve src/algorithms/medium_helper.c

Asamalar:

1. Her elemana rank/index ata
2. chunk boyutu sec (n <= 100 ise 15, aksi 36)
3. a icinde "su anki chunk limitine" uygun elemani bul
4. onu en kisa yoldan top'a cek, pb yap
5. b'de gerekirse rb ile dagilimi duzelt
6. a bitince b'deki max index'i top'a alip pa ile geri yukle

Neden index kullaniyoruz?

- Gercek degerler yerine 0..n-1 rank'lariyla dusunmek bit/chunk kararlarini kolaylastirir.

Neden geri donuste max seciliyor?

- b'den a'ya her seferinde en buyugu almak, a'yi dogrudan dogru sirada biriktirir.

### 9.3 Complex sort (radix tabanli)

Kod: src/algorithms/complex.c ve src/algorithms/complex_helper.c

Asamalar:

1. Index atama
2. max bit sayisini hesaplama
3. Her bit icin pass:
    - bit 1 ise ra
    - bit 0 ise pb
4. Pass sonu b'den pa ile geri alma

Bu yapi LSD radix'in stack versiyonudur.

Onemli not:

- Kodda a->size <= 500 ise complex, medium'a geri donuyor.
- Yani burada pratik bir hibrit tercih var.

### 9.4 Adaptive sort

Kod: src/algorithms/adaptive.c

Esikler:

- disorder < 0.2 -> simple
- 0.2 <= disorder < 0.5 -> medium
- disorder >= 0.5 -> complex

Bu, "tek algoritma her seye iyi degildir" fikrine dayaniyor.

## 10) Basit bir dry-run (adim adim hissetmek icin)

Ornek input: 4 1 3 2

Simple bakisla dusunelim:

1. min=1, top'a cek, pb
2. kalan a: 4 3 2, min=2, top'a cek, pb
3. kalan a: 4 3, min=3, pb
4. kalan a: 4, pb
5. b'den pa pa pa pa

Sonuc: a artan olur.

Bu dry-run mantigi, koddaki while dongulerini zihinde canlandirmayi kolaylastirir.

## 11) Benchmark sistemi ne ise yariyor?

Kod: src/utils/bench.c

--bench acikken:

- Komutlar stdout'a gitmeye devam eder (checker bozulmasin diye)
- Benchmark raporu stderr'e gider

Rapor icerigi:

- disorder yuzdesi
- strateji adi
- complexity etiketi
- total operasyon
- tek tek operasyon sayaclari

Boylece iki seyi ayni anda gorursun:

- dogruluk (checker OK/KO)
- maliyet (kac op)

## 12) Dosya haritasi: hangi dosyaya hangi soruyla gidilir?

- Program nereden basliyor: src/main.c
- Nasil parse ediyor: src/parser/parse.c
- Flag nasil seciliyor: src/parser/flags.c
- Error niye geliyor: src/utils/checks.c
- Stack nasil tutuluyor: src/utils/stack.c
- Operasyon gercegi ne: src/ops/*.c
- Disorder nasil olculuyor: src/algorithms/disorder.c
- Algoritma secimi: src/algorithms/selector.c ve adaptive.c
- Medium geri toplama: src/algorithms/medium_helper.c
- Complex radix pass: src/algorithms/complex_helper.c
- Bench rapor: src/utils/bench.c

## 13) En sik yapilan hatalar

1. Duplicate kontrolunu atlamak
2. Int siniri tasmasini eksik yakalamak
3. Operasyon fonksiyonunda prev/next bagini bozuk guncellemek
4. While dongulerinde size degisimi oldugunu unutmak
5. Stdout/stderr karmasini bozup checker'i kirma

## 14) Debug checklist

Bir hata oldugunda su sirayla git:

1. Input parse dogru mu?
2. Ilk stack dogru kurulmus mu?
3. Her op sonrasi a ve b beklenen durumda mi?
4. total_ops ve op_count artiyor mu?
5. Komut ciktilari checker ile OK veriyor mu?
6. Bench raporu mantikli mi?

## 15) Calistirma komutlari

Temel:

```bash
make
./push_swap 2 1 3 6 5 8
./push_swap --simple 5 4 3 2 1
./push_swap --medium 4 67 3 87 23
./push_swap --complex 4 67 3 87 23
./push_swap --adaptive 4 67 3 87 23
```

Checker:

```bash
./push_swap 3 2 1 | ./checker_Mac 3 2 1
```

Bench:

```bash
./push_swap --bench --adaptive 5 4 3 2 1 2> bench.txt | ./checker_Mac 5 4 3 2 1
cat bench.txt
```

## 16) Takim arkadasina nasil anlatilmali? (kisa konusma plani)

1. Once oyunun kurallari (11 op)
2. Sonra veri yapisi (a/b stack ve node)
3. Sonra main akis
4. Sonra sadece simple'i canli anlat
5. Sonra medium/complex farkini goster
6. En son adaptive esik mantigi + bench

Bu sirayla anlatirsan kisi hem "ne" yaptigini hem "neden" yaptigini anlar.

## 17) Son ozet

- Bu proje bir sorting degil, komut planlama projesi.
- Parse ve validation katmani, algoritmadan once guvenlik kapisi.
- Operasyon katmani, tum hareketin mekanik motoru.
- Algoritma katmani, hangi stratejiyle daha az op yapacagini seciyor.
- Adaptive, disorder ile input'a gore strateji degistiriyor.
- Bench, performansi sayisal olarak gorunur yapiyor.

Bu dokumani bitiren biri, kodu ilk kez acsa bile dosyalari hangi sirayla okuyacagini,
hangi fonksiyonun neden var oldugunu ve test ederken nereye bakacagini bilir.

## 18) Dosya dosya fonksiyon rehberi

Bu bolum, "hangi dosyada hangi fonksiyon ne is yapiyor?" sorusuna hizli cevap vermek
icin hazirlandi.

### 18.1 main.c

- `main`: Tum akisi baslatir. Arguman okur, stack kurar, disorder hesaplar, algoritmayi
   calistirir, gerekiyorsa benchmark basar ve temizlik yapar.

### 18.2 parser/flags.c

- `default_flag`: Flag yapisini sifirlar ve varsayilan degerleri kurar.
- `are_flags`: Gelen string flag mi diye kontrol eder.
- `apply_flag`: Tek tek flagleri yorumlar, algoritma secimi ve bench modunu ayarlar.
- `handle_flags`: argv icinde flagleri soldan saga tarar, ilk sayi argumanina kadar gider.

Bu dosyanin isi, programin hangi modda calisacagini belirlemektir.

### 18.3 parser/parse.c

- `parse_joined_args`: Birden fazla argv parcasini tek string yapip sonra split eder.
- `parse_single_arg`: Tek string icindeki sayilari split eder.
- `parse_multi_arg`: Birden fazla argumanin nasil yorumlanacagina karar verir.
- `check_numbers`: Sayi formati, range ve duplicate kontrolunu yapar.
- `read_args`: Tüm parse isinin ana giris noktasi.

Burada mantik sunudur: once format, sonra sayi dogrulugu, sonra duplicate kontrolu.

### 18.4 parser/split.c

- `is_wspace`: Whitespace karakteri mi diye bakar.
- `get_wordcount`: String icinde kac token oldugunu sayar.
- `free_split`: split sonucunu temizler.
- `next_token`: Siradaki kelimeyi ayiklar.
- `split`: Girilen stringi bosluklara gore diziye ayirir.

Bu bolum, tek string icine yazilmis sayilari ayirmak icin kullanilir.

### 18.5 parser/atol.c

- `parse_number`: Rakamlarin tek tek long degere cevrilmesini yapar.
- `ft_atol`: Stringi tam sayiya cevirir, sign ve whitespace'i kontrol eder.

Bu dosya, "char dizisi"nden guvenli sayi okuma katmanidir.

### 18.6 utils/checks.c

- `error`: Error basar ve programi durdurur.
- `is_intranger_range`: Sayi int araliginda mi diye bakar.
- `is_numstr`: String sadece sayi formunda mi diye kontrol eder.
- `has_dup`: Ayni sayi iki kere var mi diye bakar.

Bu dosya hata kapisidir. Burada yakalanmayan hatayi algoritma duzeyinde yakalamaya
calismak dogru degildir.

### 18.7 utils/stack.c

- `create_stack`: Bos stack baslatir.
- `clear_stack`: Tum node'lari free eder.
- `node_new`: Yeni node olusturur.
- `stack_add_back`: Stack'in sonuna node ekler.
- `stack_build`: Parse edilen argumanlardan a stack'ini kurar.

Bu dosya veri yapisinin kurulum ve yikim sorumlulugunu tasir.

### 18.8 ops/swap_op.c

- `sa`: a'daki ilk iki elemani degistirir.
- `sb`: b'deki ilk iki elemani degistirir.
- `ss`: iki stack icin swap'i ayni anda yapar.

Swap islemi, ustteki iki elemanin yerini degistirir; siralama oncesi veya local duzeltme
icin kullanilir.

### 18.9 ops/push_op.c

- `pa`: b'nin ustundeki node'u alip a'ya koyar.
- `pb`: a'nin ustundeki node'u alip b'ye koyar.

Push islemi algoritmalarin ana tasima aracidir. Simple, medium ve complex'in hepsinde
merkez rol oynar.

### 18.10 ops/rotate_op.c

- `ra`: a stack'ini yukari dondurur, top altta biter.
- `rb`: b stack'ini yukari dondurur.
- `rr`: iki stack'i ayni anda rotate eder.

Rotate, bir elemani tepeye getirmek yerine stack'i cevirme yoludur. Genelde hedef
eleman top'a yakinse kullanilir.

### 18.11 ops/reverse_rotate_op.c

- `rra`: a stack'ini ters yonde cevirir, bottom uste gelir.
- `rrb`: b stack'ini ters yonde cevirir.
- `rrr`: iki stack'i ayni anda ters rotate eder.

Reverse rotate, hedef eleman stack'in alt tarafina daha yakinse daha ucuz olur.

### 18.12 algorithms/disorder.c

- `get_value_at_index`: Belirli index'teki degeri okur.
- `count_inversions`: Tek bir elemanin kac inversion'a sebep oldugunu hesaplar.
- `compute_disorder`: Tum liste icin disorder oranini uretir.

Bu dosyanin cikardigi oran adaptive secimin tek girdisidir.

### 18.13 algorithms/simple.c

- `find_min_index`: En kucuk sayinin stack icindeki yerini bulur.
- `rotate_simple`: Min elemani en az hamleyle top'a getirir.
- `simple_sort`: Tum diziyi minimumlari tek tek ayirarak siralar.

Simple algoritmasinin ana fikri, her turda kalan listenin en kucugunu ayirma ve kenara
alma mantigidir.

### 18.14 algorithms/medium.c

- `assign_indices`: Her node'a rank/index verir.
- `find_in_chunk_pos`: Belirli chunk icindeki ilk uygun elemanin pozisyonunu bulur.
- `rotate_a_to_chunk`: O elemana en kisa yoldan ulasir.
- `push_chunks_to_b`: a'daki elemanlari chunk chunk b'ye tasir.
- `medium_sort`: Medium stratejinin ana girişi.

Medium algoritmasinin mantigi, rastgele bozuk listeyi kucuk parcalara ayirip kontrol
edilebilir bloklar halinde tasimaktir.

### 18.15 algorithms/medium_helper.c

- `find_max_pos`: b icindeki en buyuk index'in yerini bulur.
- `push_back_to_a`: b'den max'lari sirayla cekip a'yi tekrar kurar.

Medium algoritmasinda ikinci asama budur: b'deki yapiyi ters sirada degil, en buyukten
baslayarak geri almak.

### 18.16 algorithms/complex.c

- `complex_sort`: Radix tabanli ana algoritmadir. Gerekirse medium'a fallback yapar.

### 18.17 algorithms/complex_helper.c

- `complex_assign_indices`: Complex icin indexleri hazirlar.
- `complex_max_bits_for_size`: Kaç bit taranacagini hesaplar.
- `complex_run_radix_pass`: Tek bir bit gecisini calistirir.

Complex algoritmasinda her pass, bit bazli eleme mantigiyla calisir.

### 18.18 algorithms/adaptive.c

- `adaptive_sort`: Disorder oranina bakip uygun algoritmayi secer.

Bu dosya, programin "hangi durumda hangi stratejiyi kullanacagiz?" karar merkezidir.

### 18.19 algorithms/selector.c

- `run_selected_algo`: Flagte secilen stratejiyi ilgili fonksiyona yollar.

Bu fonksiyon bir dispatcher gibi calisir; algoritma secimini tek yerde toplar.

### 18.20 utils/bench.c

- `strategy_name`: Strateji adini metin olarak verir.
- `strategy_complexity`: Stratejiye karsilik complexity etiketi uretir.
- `print_op_counts`: Operasyon sayaclarini basar.
- `print_disorder_percent`: Disorder oranini yuzde olarak yazdirir.
- `print_benchmark`: Tum bench raporunu toplu halde basar.

Bu bolum, performans sonucunu okunur hale getirir.

## 19) Algoritma gidiş mantığı: kodda ne zaman ne oluyor?

Bu kisim, fonksiyon isimlerinden bagimsiz olarak programin zihinsel modelidir.

### 19.1 Ortak is akisi

Her algoritma su genel sirayi takip eder:

1. Elindeki stack'in durumunu analiz et.
2. Hangi elemanin hangi stack'e gitmesi gerektigine karar ver.
3. En az hamleyle o elemani top'a getir.
4. `pa` veya `pb` ile transfer et.
5. Gerekirse rotate ile duzeltme yap.
6. Bircok durumda ikinci stack'i gecici depo gibi kullan.
7. Son asamada a stack'ini tamamen sirali hale getir.

### 19.2 Simple akisi

Simple'da karar mekanizmasi cok basit:

- Kalan listenin en kucugunu bul.
- Top'a getir.
- Kenara al.

Bu, insanin elde kartlari kucukten buyuge ayirma davranisina benzer.

### 19.3 Medium akisi

Medium'da ana fikir:

- "Tum listeyi tek seferde halletmeye calisma."
- Onu parcalara bol.
- Her parcayi kontrollu sekilde b'ye tasiyip sonra geri kur.

Bu strateji, simple'a gore daha az gereksiz hareket uretir.

### 19.4 Complex akisi

Complex'te karar mekanizmasi:

- Degerlerin kendisine degil, index'in bitlerine bak.
- Her bit turunda listeyi iki gruba ayir.
- Sonra gruplari tekrar birlestir.

Bu, sayilari insan gibi tek tek karsilastirmak yerine binary bilginin duzeninden faydalanir.

### 19.5 Adaptive akisi

Adaptive'de ilk soru su:

- Bu input ne kadar bozuk?

Sonra cevaplara gore strateji secilir. Yani adaptive aslinda bir algoritma degil,
algoritma secme katmanidir.

## 20) Kisa ornekler uzerinden ne goruyoruz?

### 20.1 Tam sirali liste

Ornek: 1 2 3 4

- Disorder 0'a yakindir.
- Simple zaten bir sey yapmadan cikabilir.
- Adaptive bunu gorur ve minimum maliyetli yolu tercih eder.

### 20.2 Ters sirali liste

Ornek: 5 4 3 2 1

- Disorder cok yuksektir.
- Adaptive buyuk ihtimalle complex secimine gider.
- Chunk veya radix yapilari bu tip girdi icin daha verimlidir.

### 20.3 Kismen bozuk orta boy liste

Ornek: 4 67 3 87 23

- Ne tam sirali ne de tamamen ters.
- Medium mantigi bu tip inputta iyi calisir.

## 21) Bu projeyi okurken akilda tutulmasi gereken ana fikirler

- Kodsuz siralama yok, sadece operasyon var.
- Operasyonlar hem veri yapisini hem ciktisini hem sayaclari etkiliyor.
- Algoritmalarin hepsi a ve b arasinda tasima yaparak calisiyor.
- Index, gercek deger yerine siralama kararini kolaylastiriyor.
- Adaptive, bozukluk oranina bakarak dogru stratejiyi seciyor.

## 22) Bu dosyayi nasil kullanmali?

Takim arkadasin kodu acinca su rotayi izlesin:

1. Once 1-4. bolumleri okusun.
2. Sonra 5-8 ile input ve operasyon mantigini anlasin.
3. Ardindan 9-10 ile algoritma akisini takip etsin.
4. En son 18 ve 19 ile dosya dosya fonksiyonlara baksin.

Bu sirayla giderse proje "karmaşık C kodu" olmaktan cikip, parcalara ayrilmis bir
komut sistemi olarak gorunur.
