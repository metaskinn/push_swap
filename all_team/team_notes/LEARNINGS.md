<!-- Ne işe yarar?
Projede öğrendiğiniz şeyleri yazarsınız.
Sonra tekrar bakınca çok işe yarar (özellikle sınav/defense öncesi) -->

## 2026-02-21 -_metaskin_

### argc ve argv Nedir?  -_metaskin_

- argc (Argument Count): Bize (programın adı da dahil olmak üzere) toplam kaç tane argüman girildiğini söyler.
- argv (Argument Vector): Girilen argümanları kelime kelime string (char *) olarak tutan bir metin dizisidir. (Unutma, terminalden girdiğimiz sayılar bize int olarak değil, "4" sembolü yani metin olarak gelir).

---

### 3 Temel Girdi (Input) Kontrol Kuralı:  -_metaskin_

1. "Bunlar Gerçekten Bir Sayı Mı?" Kuralı (Sadece Rakam ve İşaret)
Bize verilen şey 123a veya hello olabilir.
Bir string içinde sadece rakamlar ('0' - '9') ve belki en başta sadece bir tane eksi ('-') veya artı ('+') işareti bulunmasına izin vermeliyiz. Boşlukları ve diğer tüm karakterleri reddetmeliyiz.

2. "Sınırları Taşıyor Mu?" Kuralı (Integer Overflow)
C dilinde kullanacağımız int veri tipinin bir kapasitesi vardır (genellikle -2147483648 ile 2147483647 arası).
Test eden kişi, programımıza 999999999999999 değerini verip çökertmeye çalışacak. Eğer bunu kontrol etmeden direkt int yapısına koymaya çalışırsak overflow (taşma) dediğimiz şey olur ve sayı saçma sapan eksi bir değere döner. Bunu baştan saptamalıyız. (Kendi yazacağımız ve bu sınırları denetleyen özel bir ft_atol (long dönen atoi) ile halledeceğiz).

3. "Kopya (Tekrar Eden) Var Mı?" Kuralı (Duplicates)
push_swap kuralı gereği sıralanacak sayı dizisinde birbirinin aynısı iki sayı (örneğin: 1 5 3 5 9) olamaz.
Tüm geçerli sayıları aldıktan sonra, içlerinde kopya olup olmadığını birbirleriyle karşılaştırarak tek tek kontrol etmeliyiz.
Eğer bu 3 kuraldan herhangi biri ihlal edilirse, programımız derhal çalışmayı durdurmalı ve terminale Standart Hata (Standard Error) çıktısına tam olarak şu kelimeyi basmalıdır: Error\n (Sadece "Error", başka hiçbir açıklama veya ek kelime olmadan ve sonunda yeni satıra geçerek).

---

### Sayıları Parçalamak: `split` Mantığı -_metaskin_
- Argümanlar iki şekilde gelebilir:
  1. Yana yana normal şekilde: `./push_swap 4 2 1` (Bunda her sayı ayrı `argv[1]`, `argv[2]` vs. içindedir).
  2. Tek bir tırnak içinde blok olarak: `./push_swap "4 2 1"` (Bunda hepsi sadece `argv[1]` içindedir).
- Eğer `argc == 2` ise (yani blok olarak gelmişse), tek bir boşluğa (' ') göre sayıları kelimelere bölmesi (parse etmesi) için kendi yazdığımız `split` fonksiyonumuzu (`ft_split`'in libft'siz hali) kullanacağız.

---

### Boş Argüman Tuzağı (Subject Kuralı) -_metaskin_
- Eğer `push_swap` isimli programımız hiçbir argüman (sayı) verilmeden terminalden çalıştırılırsa, *Error* basmamalıdır! Sadece hiçbir şey yapmadan temizce kapanıp çıkmalıdır. Bu bir Norm/Subject kuralıdır. (Error sadece "verilen şey" hatalıysa basılır, verilmeyen şeyde hata sayılmaz).

---

### Neden Dizi (Array) Değil de Çift Yönlü Bağlı Liste (Doubly Linked List)? -_metaskin_
- **Array (Dizi) Sorunu:** Array kullansaydık ilk elemanı yığından (stack) çıkardığımızda, arkasında kalan yüzlerce elemanı tek tek birer adım öne kaydırmak (shift) zorunda kalırdık. Bu da programı çok yavaşlatır ve Big-O zaman karmaşıklığını (O(N)) çok attırırdı!
- **Bağlı Liste (Linked List) Çözümü:** Linked list sayesinde sadece pointer'ları (bağlantı iplerini) değiştirerek bir elemanı anında koparıp yerini değiştirebiliyoruz. Hiçbir kaydırma işlemi gerekmiyor (O(1)).
- **Neden Çift Yönlü (Doubly):** Node (düğüm) yapımızın içinde sadece bir sonrakini (`next_node`) değil, bir öncekini (`prev_node`) de takip ediyoruz. Bu sayede listeyi tersten okumak (özellikle `rra`, `rrb` gibi listenin en altındaki elemanı en üste çıkartma hamlelerinde) inanılmaz kolay ve hızlı oluyor.

---

## 2026-02-23 (Gece Oturumu Öğretileri) -_metaskin_

### Linter (Uyarı Sistemi) Savaşları ve 42 Header Kültürü
- **Öğrenilen:** VS Code'daki C/C++ eklentisi (clangd), dosyaların içinde kullanılan her şey için spesifik (`unistd.h`, `stdlib.h`) kütüphanelerin eklenmesini ister (IWYU uyarısı).
- **42 Farkı:** Oysa bizim 42 standartlarında yapmamız gereken kod kirliliğini önlemek için sadece `push_swap.h` eklemektir. Ana dizine `.clangd` konumlandırıp uyarıyı kapattık.

### Makefile İle Mimariyi Güçlendirmek: `VPATH`
- **Öğrenilen:** Proje büyüyünce modüler bir `src/` mimarisi kurduk. Makefile'ın iç içe klasörlerdeki `.c`'leri otomatik bulması için `VPATH = src/:src/error:src/stack...` metodunu öğrendik. `.o` kirliliğini `$(OBJ_DIR)%.o: %.c` kuralıyla bitirdik.

### Micro Sort (3 Eleman) Optimizasyonu
- **Öğrenilen:** 3 sayıyı sadece **2 hamle** kuralına oturttuk: En büyüğü bul, tepeye yakınsa `ra` ile; dibe yakınsa `rra` ile en aşağı fırlat. Üstte kalan iki sayıyı `sa` ile kıyasla.

### Gizli "Long Overflow" Tuzağı (Çok Uzun Argümanlar)
- **Öğrenilen:** `44444...` gibi 30 basamaklı yazılan sayılar `long` değişkeni bile patlatarak başa sarar. `while` içinde `res = res * 10` ilerlerken *border cross* anında döngüyü `return` ile patlattık.

---

## 2026-02-24 (Büyük Algoritma Devrimi) -_metaskin_

### Ranking & İndeksleme Mantığı Neden Şarttı?
- Normal sayılarımız `-40, 500, 1` gibi uçuk aralıklarda geldiği için matematiksel sınır algoritmaları kurmak zordu. Listenin tümünü okuduktan sonra her sayıya sıralamadaki "Derecesini/Sırasını" basan `assign_rank_indexes.c` yazdık. Ortaya çıkan yepyeni `[0'dan N-1'e]` Index dizilimi, tüm Complex algoritmaların beyni oldu.

### Matematiksel Çözüm: Radix Sort
- **Öğrenilen:** O(N.logN) hızında şaheser. İndeks verimizi alıp 2'ye (binary) çevirdik. Sadece son bitine bakıyoruz: Eğer `1` ise Yığın A'da kendi etrafında dön (`ra`), eğer `0` ise Yığın B'ye şutla (`pb`). Sonra B'den geri çek. Her Döngüde bit kaydır (`>> 1`). Sıralama muazzam, fakat **sorun:** Base-2 kullandığı için 500 elemanlık listeyi her zaman teorik maksimum olan `~6800` civarında operasyonda bitiriyor (5500 için yetersiz).

### Zirve Performansı: Range-Based (Butterfly / Medium Chunks)
- 42'nin 5500 limitini parçalamak için Chunks Range yöntemine geçtik. Parçaları (`chunk_size`) belirliyoruz. Örneğin; gelen sayının indexi parça limitindeyse `pb` yapıyoruz, limitin daha da alt yarımındaysa `pb` ardından `rb` ile B'nin dibine gizliyoruz. (Kelebek formasyonu).
- **Hedef Bulma Hilesi (Lookahead):**
  - Chunks, parçaları aktardıktan sonra en karmaşık iş B'den A'ya doğru sayıyı geri çekmektir (Geriye sayarak). Stack B içinde en yüksek sayıyı bulmaya (`find_target_pos`) çalışırken bazen çok fazla tur attığı oluyordu.
  - O müthiş performans zıplamasını şurada bulduk: Eğer aradığımız sayı `(target)` ve hedefin 1 eksiği sayı `(target - 1)` ikisi de B'nin içindeyse; aralarından **"HANGİSİ DAHA YAKINSA (Daha az rotate istiyorsa)"** önce onu `pa` ile A yığınına attık. Asıl hedef geride kalınca o da çıkıp geldiğinde, onları sadece bir `sa` atarak yer değiştirdik! 
  - Bu muhteşem Look-ahead manevrası ile operasyonları **5600 lerden 4700 lere (-%16 Kazanç)** indirdik! Ve `100` elemanlı testte `545` rakamı ile 700 sınırını paramparça ettik.

### 42 Norminette ve "Too Many Functions" Savaşı
- Dosya başına max 5 fonksiyon yetmediğinde inatlaşmak yerine `find_target_pos` gibi her şeyin içinde çalışan minik iteratörleri `src/stack` altında kendilerine ait `.c` dosyalarına kopardık. Satır sayısı aşımını (80'i) ise argüman listesini `\n` ve *Tab* ile aşağı indirerek çözdük.
