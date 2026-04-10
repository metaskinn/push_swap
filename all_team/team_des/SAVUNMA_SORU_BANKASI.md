# Push Swap Savunma Soru Bankasi

Bu dokuman, evo ve subject kapsamina gore peer to peer degerlendirmede sorulabilecek sorularin kapsamli bir havuzudur.
Amac, hem teknik dogrulugu hem de savunma aninda hizli cevap verebilmeyi guclendirmektir.

## 1) Grup ve Proje Kurallari
1. Bu projenin neden tam olarak 2 kisiyle yapilmasi zorunlu?
Cevap: Takim calismasi ve ortak sahiplik icin.

2. Iki kisinin katkisini repoda nasil kanitliyorsunuz?
Cevap: Commit, branch ve kod izi ile.

3. README icinde kisi bazli katkilarinizi nasil ayirdiniz?
Cevap: Task dagilimi ve sorumluluklarla.

4. Ikiden fazla kisi katkisi gorunurse ne olur?
Cevap: Kural ihlali sayilir.

5. Savunmada iki kisi de yoksa sonuc ne olur?
Cevap: Ciddi puan kaybi veya gecersizlik olur.

6. Biriniz sadece kendi yazdigi kodu biliyorsa neden basarisiz sayilirsiniz?
Cevap: Cunku tum sistemi savunmak gerekir.

7. Repository nin size ait oldugunu nasil dogrulariz?
Cevap: Git gecmisi ve depo baglantisi ile.

8. Değerlendirmede neden sadece repodaki kod gecerli?
Cevap: Sadece teslim edilen kod esas alinir.

9. Lokal degisikliklerin savunmada neden anlami yok?
Cevap: Cunku dogrulama yoktur.

10. Kopya kod tespiti durumunda ne olur?
Cevap: Kopya tespitinde basarisizlik beklenir.

## 2) README Uyumlulugu
1. README ilk satiri subjectte istendigi formatta mi?
Cevap: Evet, subject formatina uyulmalı.

2. Ilk satir italic degilse neden hata sayilir?
Cevap: Cunku format ihlali kabul sorunudur.

3. Description bolumunde hangi bilgileri verdiniz?
Cevap: Proje amaci, stratejiler ve operasyonlar.

4. Instructions bolumunde derleme ve calistirma adimlari acik mi?
Cevap: Evet, adimlar net olmali.

5. Resources bolumunde hangi kaynaklari eklediniz?
Cevap: Subject, Norm, evo, test araclari.

6. AI kullanimini README de nerede, nasil acikladiniz?
Cevap: AI kullanimi seffaf belirtilmeli.

7. AI nin hangi kisimlarda kullanildigini neden belirtmek zorundasiniz?
Cevap: Etik ve izlenebilirlik icin.

8. 4 stratejiyi README de tek tek acikladiniz mi?
Cevap: Evet, 4 strateji ayri yazilmali.

9. Esik degerlerin gerekcesi README de var mi?
Cevap: Evet, deneysel gerekce yazilmali.

10. Zaman ve alan karmasikligi savunmasi README de yazili mi?
Cevap: Evet, Big O acik olmali.

## 3) Norm ve Kod Stili
1. Norminette neden mandatory kapisidir?
Cevap: 42 icin kabul kosulu oldugu icin.

2. Norm hatasi olunca neden degerlendirme durur?
Cevap: Cunku stil olmadan teslim sayilmaz.

3. Fonksiyon uzunluk limitine nasil uyuyorsunuz?
Cevap: Kisa fonksiyonlar ve helperlar ile.

4. Cok parametre sorununuzu nasil cozdunuz?
Cevap: Ortak context yapisi ile.

5. Global degisken yasaginin sebebi ne?
Cevap: Test ve debug riskleri yuzunden.

6. Header bagimliliklarini nasil yonettiniz?
Cevap: Minimum include ve katmanlama ile.

7. Include guardlari neden kritik?
Cevap: Cift include ve donguyu engeller.

8. Norm uyumu icin okunabilirlikten odun verdiginiz yer var mi?
Cevap: Asgari odun, ama okunabilirlik korunur.

9. Normu bozmadan performans optimizasyonu nasil yaptiniz?
Cevap: Yapisal optimizasyonla.

10. Norm uyumlu hata yonetimi yaklasiminiz nedir?
Cevap: Tek error yolu ve cleanup ile.

## 4) Makefile ve Derleme
1. Makefile da NAME, all, clean, fclean, re var mi?
Cevap: Evet, temel hedefler olmali.

2. Derleme flagleri neden Wall Wextra Werror?
Cevap: Uyarilar hataya donsun diye.

3. Gereksiz relink olmadigini nasil kanitlarsiniz?
Cevap: `make` tekrarinda gereksiz link olmamali.

4. Obj klasorune ayri derleme neden iyi?
Cevap: Temizlik ve ayrik derleme icin.

5. Incremental build nasil calisiyor?
Cevap: Sadece degisen dosyalar derlenir.

6. Header degisince ilgili dosyalar yeniden derleniyor mu?
Cevap: Evet, dependency dogruysa derlenir.

7. Libft kullaniyorsaniz nasil linkliyorsunuz?
Cevap: Ayrı derleyip baglarsiniz.

8. clean ile fclean farki nedir?
Cevap: clean objeleri, fclean her seyi siler.

9. re neden clean + all degil de fclean + all olmali?
Cevap: re tam sifir kurulum olmali.

10. Bonus target ne zaman gerekli?
Cevap: Bonus istenirse gerekir.

## 5) Arguman Parsing ve Hata Yonetimi
1. Girdi formatini nasil parse ediyorsunuz?
Cevap: Tek string ve coklu arguman olarak.

2. Tirnakli tek arguman ve coklu argumani ayni anda destekliyor musunuz?
Cevap: Evet, ikisi de desteklenir.

3. Bos string girdisinde ne yapiyorsunuz?
Cevap: Hata verip durdururuz.

4. Sayi olmayan tokeni nasil tespit ediyorsunuz?
Cevap: Karakter kontrolu ile.

5. Int tasmasini nasil tespit ediyorsunuz?
Cevap: Range ve overflow kontrolu ile.

6. +42 ve -42 formatlarini kabul ediyor musunuz?
Cevap: Evet, kabul edilir.

7. Basinda sifir olan 0042 gecerli mi?
Cevap: Sayisal olarak gecerli kabul edilir.

8. Isaret tek basina gelirse ne yapiyorsunuz?
Cevap: Tek basina isaret gecerli degil.

9. Duplicate kontrolunu nasil yapiyorsunuz?
Cevap: Tum degerleri karsilastiririz.

10. Duplicate kontrolu hangi karmasiklikta?
Cevap: O(n^2).

11. Hata aninda tam olarak nereye yaziyorsunuz?
Cevap: stderr uzerinden `Error\n`.

12. Error mesaji neden sadece Error ve newline olmali?
Cevap: Subject bunu bekler.

13. Hata aninda allocated bellekleri nasil temizliyorsunuz?
Cevap: Parse cleanup ile.

14. No args durumunda neden hic cikti vermiyorsunuz?
Cevap: Sessiz cikis beklenir.

15. Flag ile sayi ayrimini nasil yapiyorsunuz?
Cevap: Once flag, sonra sayi.

16. Bilinmeyen flag geldiginde davranis ne?
Cevap: Hata verir.

17. Flaglerin sirasi degisse yine calisiyor mu?
Cevap: Dogru sirada ise calisir.

18. Hem bench hem strateji flagi verilirse ne oluyor?
Cevap: Bench acilir, secim korunur.

19. Cifte strateji flagi verilirse ne oluyor?
Cevap: Kabul edilmez.

20. Parser tasariminizin en zayif noktasi ne?
Cevap: Coklu giris ve cleanup.

## 6) Operasyonlar ve Stack Mantigi
1. sa ne zaman no-op olur?
Cevap: Yeterli eleman yoksa.

2. sb ne zaman no-op olur?
Cevap: Aynisi B icin.

3. ss yi iki ayri swap yerine neden kullanirsiniz?
Cevap: Tek hamlede iki swap.

4. pa ve pb bos stackte ne yapmali?
Cevap: No-op olmali.

5. ra ve rb davranisi nedir?
Cevap: Top elemani alta tasir.

6. rra ve rrb davranisi nedir?
Cevap: Alt elemani ustte tasir.

7. rr ve rrr ne zaman avantajli?
Cevap: Iki rotate yerine tek adim.

8. Operasyon fonksiyonlariniz stack boyutunu nasil guncelliyor?
Cevap: Size alanini gunceller.

9. Tek elemanli stackte rotate davranisi nedir?
Cevap: No-op olur.

10. Cift yonlu liste kullaniyorsaniz pointer guvenligini nasil sagliyorsunuz?
Cevap: Prev/next baglarini dikkatle.

11. Array tabanli stack ile linked list arasinda ne sectiniz, neden?
Cevap: Linked list; rotate daha kolay.

12. Top of stack temsiliniz nedir?
Cevap: Bas dugum top’tur.

13. Operasyonlarin dogrulugunu nasil test ettiniz?
Cevap: Checker ve random testlerle.

14. Her op yazdirildiginda sayaclar nasil artiyor?
Cevap: Her op kendi sayacini artirir.

15. Operasyon yazdirma ve uygulama neden tek noktadan yapilmali?
Cevap: Tutarlilik icin.

## 7) Basit Strateji O n kare
1. Simple algoritmaniz tam olarak hangi yontem?
Cevap: Min bul, B ye at, geri getir.

2. Neden O n kare oldugunu nasil savunuyorsunuz?
Cevap: Her tur tam tarama yaptigi icin.

3. En kotu durumda kac operasyon bekliyorsunuz?
Cevap: Kucuk n icin kabul edilebilir.

4. Kucuk n icin neden bazen daha iyi sonuc veriyor?
Cevap: Sabit maliyet dusuk kalir.

5. 3 eleman icin ozel durumunuz var mi?
Cevap: Evet, kucuk durumlar icin.

6. 5 eleman icin ozel durumunuz var mi?
Cevap: Evet, 5 ve altinda.

7. Min extraction yapiyorsaniz rotate yonunu nasil seciyorsunuz?
Cevap: En kisa rotation secilir.

8. Her turda hedef elemani nasil buluyorsunuz?
Cevap: Min konumu taranir.

9. Bu stratejide op sayisini azaltan kritik optimizasyon nedir?
Cevap: Kisa rotation.

10. Simple stratejinin en kotu input ornegi nedir?
Cevap: Ters sirali buyuk diziler.

## 8) Orta Strateji O n kok n
1. Medium algoritmaniz chunk tabanliysa chunk sayisini nasil seciyorsunuz?
Cevap: Eleman sayisina gore sabit chunk.

2. Neden O n kok n iddiasinda bulunuyorsunuz?
Cevap: Chunk ve geri toplama denge saglar.

3. Chunk sinirlari nasil hesaplanıyor?
Cevap: Normalize index araliklari ile.

4. Normalize index kullanimi neden kolaylik saglar?
Cevap: Karsilastirmayi kolaylastirir.

5. B stackine atarken rb veya rrb kararini nasil veriyorsunuz?
Cevap: B de dengeye gore.

6. Geri toplama asamasinda max elemani nasil buluyorsunuz?
Cevap: Maksimumu bulup tepeye cekeriz.

7. Chunk buyuklugu buyurse ne olur?
Cevap: Verim dusar.

8. Chunk buyuklugu kuculurse ne olur?
Cevap: Turlar artar.

9. Neden bu strateji 100 ve 500 testinde iyi denge saglar?
Cevap: 100/500 icin iyi denge.

10. Medium stratejinin zayif kaldigi input tipleri neler?
Cevap: Asiri duzgun ya da asiri dağinik input.

## 9) Karmasik Strateji O n log n
1. Complex algoritmaniz radix ise binary radix mi?
Cevap: Evet, binary radix.

2. Neden O n log n oldugunu push_swap modelinde aciklayin.
Cevap: Bit basina tur oldugu icin.

3. Bit sayisini nasil buluyorsunuz?
Cevap: En buyuk indeksin bit uzunlugu.

4. Her bit turunda pa pb orani nasil degisiyor?
Cevap: 0 bit B ye, 1 bit A ya.

5. Neden radix stabilite benzeri bir etki gerektirir?
Cevap: Sirayi bozmamak icin.

6. Negatif sayilarla radix nasil calisir?
Cevap: Normalize indeksle sorun azalir.

7. Normalize edilmis index kullanimi neden kritik?
Cevap: Pozitif siralama saglar.

8. Radixte erken cikis optimizasyonu var mi?
Cevap: Sadece zaten siraliysa azalir.

9. Radix neden bazen mediumdan fazla op uretebilir?
Cevap: Bit turlari sabit maliyetlidir.

10. Complex stratejide en iyi ve en kotu input farki nedir?
Cevap: En iyi: az tur, en kotu: tam tarama.

## 10) Adaptive Strateji
1. Adaptive tam olarak hangi metrikle karar veriyor?
Cevap: Disorder orani ile.

2. Disorder degeri ne zaman olculuyor?
Cevap: Stack kurulduktan sonra.

3. Esik degerler neden 0.2 ve 0.5?
Cevap: Low/medium/high ayrimi icin.

4. Esikleri deneysel mi teorik mi belirlediniz?
Cevap: Deneysel, bench tabanli.

5. n etkisini esik seciminde dikkate aldiniz mi?
Cevap: Evet, ama esas metrik disorder.

6. n kucukken neden baska karar daha iyi olabilir?
Cevap: Sabit maliyet daha etkili olur.

7. Disorder dusuk ama n cok buyukken neden simple secmiyorsunuz?
Cevap: Cunku simple pahali kalir.

8. Disorder orta ama complex daha iyi ciktigi durum oldu mu?
Cevap: Evet, olur.

9. Yanlis strateji secen bir karsi ornek verin.
Cevap: Dusuk disorderda simple yanlis secim olur.

10. Adaptive kararini iyilestirmek icin hangi ek metrik eklenebilir?
Cevap: N ve LIS gibi metrikler.

11. Inversion disinda run-length veya LIS metriklerini dusundunuz mu?
Cevap: Dusunulebilir.

12. Adaptive deterministik mi, ayni girdide her zaman ayni secim mi yapar?
Cevap: Evet, deterministik olmalidir.

13. Strateji secim maliyeti toplam sureyi nasil etkiler?
Cevap: Kucuk tutulmali.

14. Karar mekanizmasi bozulursa fallback nedir?
Cevap: Dogru parser/flag davranisi.

15. Flag ile zorlanan stratejide adaptive tamamen bypass oluyor mu?
Cevap: Evet, zorlaninca bypass olur.

## 11) Disorder Hesabi
1. Disorder formulu nedir?
Cevap: Inversion / toplam pair.

2. Total pair neden n carpi n eksi 1 bolu 2?
Cevap: Tum ikili karsilastirma sayisi.

3. Sorted dizide disorder neden 0?
Cevap: Inversion yok.

4. Reverse sorted dizide disorder neden 1?
Cevap: Tum pair ters.

5. Disorder yuzdeye cevrimi nasil yapiliyor?
Cevap: `* 100` ile.

6. Float hassasiyeti sorun olur mu?
Cevap: Kucuk yuvarlama olabilir.

7. n 0 veya n 1 durumunda bolme hatasini nasil onluyorsunuz?
Cevap: Tanimli guvenli donus gerekir.

8. Disorder O n kare hesaplandigi icin buyuk n de maliyet ne?
Cevap: Buyuk n de pahali.

9. Approximate disorder dusundunuz mu?
Cevap: Evet, ama tam hesaplama kullandik.

10. Disorder hesaplamasi bench aciksa mi her zaman mi?
Cevap: Bench disinda da hesaplanabilir.

## 12) Bench Modu
1. Bench ciktilari neden stderr e yazilmali?
Cevap: Cunku stdout operasyon akisidir.

2. Stdout neden sadece operasyon akisi olmali?
Cevap: Checker bozulmasin diye.

3. Bench acikken checker pipe neden bozulmamali?
Cevap: Rapor stderr e ayrilir.

4. Benchte strateji adi ve karmasiklik nasil yaziliyor?
Cevap: Ad, complexity, disorder.

5. Toplam op sayisi nereden geliyor?
Cevap: Sayaç toplamindan.

6. Her op tipinin sayaçlari nasil tutuluyor?
Cevap: Her op kendi sayacini artirir.

7. Sayaçlar ile toplam op uyumunu nasil garanti ediyorsunuz?
Cevap: Tek kaynakli sayaç mantigi ile.

8. Bench formatiniz sabit mi?
Cevap: Evet, sabit format iyi.

9. Bench aktifken performans etkisi ne kadar?
Cevap: Kucuk ama olculur.

10. Benchte disorder kac basamak gosteriliyor?
Cevap: Iki ondalik yeterli.

11. Bench acik ama input zaten sorted ise cikti ne olmali?
Cevap: Sifir operasyon veya rapor.

12. Benchte secilen strateji, zorlanan flag ile uyumlu mu?
Cevap: Evet, bozmamali.

## 13) Dogruluk Testleri
1. Neden once checker ile dogruluk sonra op sayisi bakilir?
Cevap: Once dogruluk, sonra performans.

2. Sorted inputta neden 0 islem beklenir?
Cevap: Cunku zaten sirali.

3. 3 eleman testleri neden kritik?
Cevap: Boundary case icin.

4. 5 eleman testleri neden kritik?
Cevap: Kucuk boyut mantigi icin.

5. Random testlerde ayni seed kullanmanin faydasi ne?
Cevap: Tekrarlanabilirlik icin.

6. 100 sayida 2000 alti hedefini nasil tutturuyorsunuz?
Cevap: Dogru strateji secimi ile.

7. 500 sayida 12000 alti hedefini nasil tutturuyorsunuz?
Cevap: Buyukte uygun strateji ile.

8. En iyi ve en kotu test sonuclarinizi raporlayin.
Cevap: Checker, op sayisi, ortalama.

## 1) Grup ve Proje Kurallari
1. Bu projenin neden tam olarak 2 kisiyle yapilmasi zorunlu?
Cevap: Takim calismasi ve ortak sahiplik icin.

2. Iki kisinin katkisini repoda nasil kanitliyorsunuz?
Cevap: Commit, branch ve kod izi ile.

3. README icinde kisi bazli katkilarinizi nasil ayirdiniz?
Cevap: Task dagilimi ve sorumluluklarla.

4. Ikiden fazla kisi katkisi gorunurse ne olur?
Cevap: Kural ihlali sayilir.

5. Savunmada iki kisi de yoksa sonuc ne olur?
Cevap: Ciddi puan kaybi veya gecersizlik olur.

6. Biriniz sadece kendi yazdigi kodu biliyorsa neden basarisiz sayilirsiniz?
Cevap: Cunku tum sistemi savunmak gerekir.

7. Repository nin size ait oldugunu nasil dogrulariz?
Cevap: Git gecmisi ve depo baglantisi ile.

8. Değerlendirmede neden sadece repodaki kod gecerli?
Cevap: Sadece teslim edilen kod esas alinir.

9. Lokal degisikliklerin savunmada neden anlami yok?
Cevap: Cunku dogrulama yoktur.

10. Kopya kod tespiti durumunda ne olur?
Cevap: Kopya tespitinde basarisizlik beklenir.

## 2) README Uyumlulugu
1. README ilk satiri subjectte istendigi formatta mi?
Cevap: Evet, subject formatina uyulmalı.

2. Ilk satir italic degilse neden hata sayilir?
Cevap: Cunku format ihlali kabul sorunudur.

3. Description bolumunde hangi bilgileri verdiniz?
Cevap: Proje amaci, stratejiler ve operasyonlar.

4. Instructions bolumunde derleme ve calistirma adimlari acik mi?
Cevap: Evet, adimlar net olmali.

5. Resources bolumunde hangi kaynaklari eklediniz?
Cevap: Subject, Norm, evo, test araclari.

6. AI kullanimini README de nerede, nasil acikladiniz?
Cevap: AI kullanimi seffaf belirtilmeli.

7. AI nin hangi kisimlarda kullanildigini neden belirtmek zorundasiniz?
Cevap: Etik ve izlenebilirlik icin.

8. 4 stratejiyi README de tek tek acikladiniz mi?
Cevap: Evet, 4 strateji ayri yazilmali.

9. Esik degerlerin gerekcesi README de var mi?
Cevap: Evet, deneysel gerekce yazilmali.

10. Zaman ve alan karmasikligi savunmasi README de yazili mi?
Cevap: Evet, Big O acik olmali.

## 3) Norm ve Kod Stili
1. Norminette neden mandatory kapisidir?
Cevap: 42 icin kabul kosulu oldugu icin.

2. Norm hatasi olunca neden degerlendirme durur?
Cevap: Cunku stil olmadan teslim sayilmaz.

3. Fonksiyon uzunluk limitine nasil uyuyorsunuz?
Cevap: Kisa fonksiyonlar ve helperlar ile.

4. Cok parametre sorununuzu nasil cozdunuz?
Cevap: Ortak context yapisi ile.

5. Global degisken yasaginin sebebi ne?
Cevap: Test ve debug riskleri yuzunden.

6. Header bagimliliklarini nasil yonettiniz?
Cevap: Minimum include ve katmanlama ile.

7. Include guardlari neden kritik?
Cevap: Cift include ve donguyu engeller.

8. Norm uyumu icin okunabilirlikten odun verdiginiz yer var mi?
Cevap: Asgari odun, ama okunabilirlik korunur.

9. Normu bozmadan performans optimizasyonu nasil yaptiniz?
Cevap: Yapisal optimizasyonla.

10. Norm uyumlu hata yonetimi yaklasiminiz nedir?
Cevap: Tek error yolu ve cleanup ile.

## 4) Makefile ve Derleme
1. Makefile da NAME, all, clean, fclean, re var mi?
Cevap: Evet, temel hedefler olmali.

2. Derleme flagleri neden Wall Wextra Werror?
Cevap: Uyarilar hataya donsun diye.

3. Gereksiz relink olmadigini nasil kanitlarsiniz?
Cevap: `make` tekrarinda gereksiz link olmamali.

4. Obj klasorune ayri derleme neden iyi?
Cevap: Temizlik ve ayrik derleme icin.

5. Incremental build nasil calisiyor?
Cevap: Sadece degisen dosyalar derlenir.

6. Header degisince ilgili dosyalar yeniden derleniyor mu?
Cevap: Evet, dependency dogruysa derlenir.

7. Libft kullaniyorsaniz nasil linkliyorsunuz?
Cevap: Ayrı derleyip baglarsiniz.

8. clean ile fclean farki nedir?
Cevap: clean objeleri, fclean her seyi siler.

9. re neden clean + all degil de fclean + all olmali?
Cevap: re tam sifir kurulum olmali.

10. Bonus target ne zaman gerekli?
Cevap: Bonus istenirse gerekir.

## 5) Arguman Parsing ve Hata Yonetimi
1. Girdi formatini nasil parse ediyorsunuz?
Cevap: Tek string ve coklu arguman olarak.

2. Tirnakli tek arguman ve coklu argumani ayni anda destekliyor musunuz?
Cevap: Evet, ikisi de desteklenir.

3. Bos string girdisinde ne yapiyorsunuz?
Cevap: Hata verip durdururuz.

4. Sayi olmayan tokeni nasil tespit ediyorsunuz?
Cevap: Karakter kontrolu ile.

5. Int tasmasini nasil tespit ediyorsunuz?
Cevap: Range ve overflow kontrolu ile.

6. +42 ve -42 formatlarini kabul ediyor musunuz?
Cevap: Evet, kabul edilir.

7. Basinda sifir olan 0042 gecerli mi?
Cevap: Sayisal olarak gecerli kabul edilir.

8. Isaret tek basina gelirse ne yapiyorsunuz?
Cevap: Tek basina isaret gecerli degil.

9. Duplicate kontrolunu nasil yapiyorsunuz?
Cevap: Tum degerleri karsilastiririz.

10. Duplicate kontrolu hangi karmasiklikta?
Cevap: O(n^2).

11. Hata aninda tam olarak nereye yaziyorsunuz?
Cevap: stderr uzerinden `Error\n`.

12. Error mesaji neden sadece Error ve newline olmali?
Cevap: Subject bunu bekler.

13. Hata aninda allocated bellekleri nasil temizliyorsunuz?
Cevap: Parse cleanup ile.

14. No args durumunda neden hic cikti vermiyorsunuz?
Cevap: Sessiz cikis beklenir.

15. Flag ile sayi ayrimini nasil yapiyorsunuz?
Cevap: Once flag, sonra sayi.

16. Bilinmeyen flag geldiginde davranis ne?
Cevap: Hata verir.

17. Flaglerin sirasi degisse yine calisiyor mu?
Cevap: Dogru sirada ise calisir.

18. Hem bench hem strateji flagi verilirse ne oluyor?
Cevap: Bench acilir, secim korunur.

19. Cifte strateji flagi verilirse ne oluyor?
Cevap: Kabul edilmez.

20. Parser tasariminizin en zayif noktasi ne?
Cevap: Coklu giris ve cleanup.

## 6) Operasyonlar ve Stack Mantigi
1. sa ne zaman no-op olur?
Cevap: Yeterli eleman yoksa.

2. sb ne zaman no-op olur?
Cevap: Aynisi B icin.

3. ss yi iki ayri swap yerine neden kullanirsiniz?
Cevap: Tek hamlede iki swap.

4. pa ve pb bos stackte ne yapmali?
Cevap: No-op olmali.

5. ra ve rb davranisi nedir?
Cevap: Top elemani alta tasir.

6. rra ve rrb davranisi nedir?
Cevap: Alt elemani ustte tasir.

7. rr ve rrr ne zaman avantajli?
Cevap: Iki rotate yerine tek adim.

8. Operasyon fonksiyonlariniz stack boyutunu nasil guncelliyor?
Cevap: Size alanini gunceller.

9. Tek elemanli stackte rotate davranisi nedir?
Cevap: No-op olur.

10. Cift yonlu liste kullaniyorsaniz pointer guvenligini nasil sagliyorsunuz?
Cevap: Prev/next baglarini dikkatle.

11. Array tabanli stack ile linked list arasinda ne sectiniz, neden?
Cevap: Linked list; rotate daha kolay.

12. Top of stack temsiliniz nedir?
Cevap: Bas dugum top’tur.

13. Operasyonlarin dogrulugunu nasil test ettiniz?
Cevap: Checker ve random testlerle.

14. Her op yazdirildiginda sayaclar nasil artiyor?
Cevap: Her op kendi sayacini artirir.

15. Operasyon yazdirma ve uygulama neden tek noktadan yapilmali?
Cevap: Tutarlilik icin.

## 7) Basit Strateji O n kare
1. Simple algoritmaniz tam olarak hangi yontem?
Cevap: Min bul, B ye at, geri getir.

2. Neden O n kare oldugunu nasil savunuyorsunuz?
Cevap: Her tur tam tarama yaptigi icin.

3. En kotu durumda kac operasyon bekliyorsunuz?
Cevap: Kucuk n icin kabul edilebilir.

4. Kucuk n icin neden bazen daha iyi sonuc veriyor?
Cevap: Sabit maliyet dusuk kalir.

5. 3 eleman icin ozel durumunuz var mi?
Cevap: Evet, kucuk durumlar icin.

6. 5 eleman icin ozel durumunuz var mi?
Cevap: Evet, 5 ve altinda.

7. Min extraction yapiyorsaniz rotate yonunu nasil seciyorsunuz?
Cevap: En kisa rotation secilir.

8. Her turda hedef elemani nasil buluyorsunuz?
Cevap: Min konumu taranir.

9. Bu stratejide op sayisini azaltan kritik optimizasyon nedir?
Cevap: Kisa rotation.

10. Simple stratejinin en kotu input ornegi nedir?
Cevap: Ters sirali buyuk diziler.

## 8) Orta Strateji O n kok n
1. Medium algoritmaniz chunk tabanliysa chunk sayisini nasil seciyorsunuz?
Cevap: Eleman sayisina gore sabit chunk.

2. Neden O n kok n iddiasinda bulunuyorsunuz?
Cevap: Chunk ve geri toplama denge saglar.

3. Chunk sinirlari nasil hesaplanıyor?
Cevap: Normalize index araliklari ile.

4. Normalize index kullanimi neden kolaylik saglar?
Cevap: Karsilastirmayi kolaylastirir.

5. B stackine atarken rb veya rrb kararini nasil veriyorsunuz?
Cevap: B de dengeye gore.

6. Geri toplama asamasinda max elemani nasil buluyorsunuz?
Cevap: Maksimumu bulup tepeye cekeriz.

7. Chunk buyuklugu buyurse ne olur?
Cevap: Verim dusar.

8. Chunk buyuklugu kuculurse ne olur?
Cevap: Turlar artar.

9. Neden bu strateji 100 ve 500 testinde iyi denge saglar?
Cevap: 100/500 icin iyi denge.

10. Medium stratejinin zayif kaldigi input tipleri neler?
Cevap: Asiri duzgun ya da asiri dağinik input.

## 9) Karmasik Strateji O n log n
1. Complex algoritmaniz radix ise binary radix mi?
Cevap: Evet, binary radix.

2. Neden O n log n oldugunu push_swap modelinde aciklayin.
Cevap: Bit basina tur oldugu icin.

3. Bit sayisini nasil buluyorsunuz?
Cevap: En buyuk indeksin bit uzunlugu.

4. Her bit turunda pa pb orani nasil degisiyor?
Cevap: 0 bit B ye, 1 bit A ya.

5. Neden radix stabilite benzeri bir etki gerektirir?
Cevap: Sirayi bozmamak icin.

6. Negatif sayilarla radix nasil calisir?
Cevap: Normalize indeksle sorun azalir.

7. Normalize edilmis index kullanimi neden kritik?
Cevap: Pozitif siralama saglar.

8. Radixte erken cikis optimizasyonu var mi?
Cevap: Sadece zaten siraliysa azalir.

9. Radix neden bazen mediumdan fazla op uretebilir?
Cevap: Bit turlari sabit maliyetlidir.

10. Complex stratejide en iyi ve en kotu input farki nedir?
Cevap: En iyi: az tur, en kotu: tam tarama.

## 10) Adaptive Strateji
1. Adaptive tam olarak hangi metrikle karar veriyor?
Cevap: Disorder orani ile.

2. Disorder degeri ne zaman olculuyor?
Cevap: Stack kurulduktan sonra.

3. Esik degerler neden 0.2 ve 0.5?
Cevap: Low/medium/high ayrimi icin.

4. Esikleri deneysel mi teorik mi belirlediniz?
Cevap: Deneysel, bench tabanli.

5. n etkisini esik seciminde dikkate aldiniz mi?
Cevap: Evet, ama esas metrik disorder.

6. n kucukken neden baska karar daha iyi olabilir?
Cevap: Sabit maliyet daha etkili olur.

7. Disorder dusuk ama n cok buyukken neden simple secmiyorsunuz?
Cevap: Cunku simple pahali kalir.

8. Disorder orta ama complex daha iyi ciktigi durum oldu mu?
Cevap: Evet, olur.

9. Yanlis strateji secen bir karsi ornek verin.
Cevap: Dusuk disorderda simple yanlis secim olur.

10. Adaptive kararini iyilestirmek icin hangi ek metrik eklenebilir?
Cevap: N ve LIS gibi metrikler.

11. Inversion disinda run-length veya LIS metriklerini dusundunuz mu?
Cevap: Dusunulebilir.

12. Adaptive deterministik mi, ayni girdide her zaman ayni secim mi yapar?
Cevap: Evet, deterministik olmalidir.

13. Strateji secim maliyeti toplam sureyi nasil etkiler?
Cevap: Kucuk tutulmali.

14. Karar mekanizmasi bozulursa fallback nedir?
Cevap: Dogru parser/flag davranisi.

15. Flag ile zorlanan stratejide adaptive tamamen bypass oluyor mu?
Cevap: Evet, zorlaninca bypass olur.

## 11) Disorder Hesabi
1. Disorder formulu nedir?
Cevap: Inversion / toplam pair.

2. Total pair neden n carpi n eksi 1 bolu 2?
Cevap: Tum ikili karsilastirma sayisi.

3. Sorted dizide disorder neden 0?
Cevap: Inversion yok.

4. Reverse sorted dizide disorder neden 1?
Cevap: Tum pair ters.

5. Disorder yuzdeye cevrimi nasil yapiliyor?
Cevap: `* 100` ile.

6. Float hassasiyeti sorun olur mu?
Cevap: Kucuk yuvarlama olabilir.

7. n 0 veya n 1 durumunda bolme hatasini nasil onluyorsunuz?
Cevap: Tanimli guvenli donus gerekir.

8. Disorder O n kare hesaplandigi icin buyuk n de maliyet ne?
Cevap: Buyuk n de pahali.

9. Approximate disorder dusundunuz mu?
Cevap: Evet, ama tam hesaplama kullandik.

10. Disorder hesaplamasi bench aciksa mi her zaman mi?
Cevap: Bench disinda da hesaplanabilir.

## 12) Bench Modu
1. Bench ciktilari neden stderr e yazilmali?
Cevap: Cunku stdout operasyon akisidir.

2. Stdout neden sadece operasyon akisi olmali?
Cevap: Checker bozulmasin diye.

3. Bench acikken checker pipe neden bozulmamali?
Cevap: Rapor stderr e ayrilir.

4. Benchte strateji adi ve karmasiklik nasil yaziliyor?
Cevap: Ad, complexity, disorder.

5. Toplam op sayisi nereden geliyor?
Cevap: Sayaç toplamindan.

6. Her op tipinin sayaçlari nasil tutuluyor?
Cevap: Her op kendi sayacini artirir.

7. Sayaçlar ile toplam op uyumunu nasil garanti ediyorsunuz?
Cevap: Tek kaynakli sayaç mantigi ile.

8. Bench formatiniz sabit mi?
Cevap: Evet, sabit format iyi.

9. Bench aktifken performans etkisi ne kadar?
Cevap: Kucuk ama olculur.

10. Benchte disorder kac basamak gosteriliyor?
Cevap: Iki ondalik yeterli.

11. Bench acik ama input zaten sorted ise cikti ne olmali?
Cevap: Sifir operasyon veya rapor.

12. Benchte secilen strateji, zorlanan flag ile uyumlu mu?
Cevap: Evet, bozmamali.

## 13) Dogruluk Testleri
1. Neden once checker ile dogruluk sonra op sayisi bakilir?
Cevap: Once dogruluk, sonra performans.

2. Sorted inputta neden 0 islem beklenir?
Cevap: Cunku zaten sirali.

3. 3 eleman testleri neden kritik?
Cevap: Boundary case icin.

4. 5 eleman testleri neden kritik?
Cevap: Kucuk boyut mantigi icin.

5. Random testlerde ayni seed kullanmanin faydasi ne?
Cevap: Tekrarlanabilirlik icin.

6. 100 sayida 2000 alti hedefini nasil tutturuyorsunuz?
Cevap: Dogru strateji secimi ile.

7. 500 sayida 12000 alti hedefini nasil tutturuyorsunuz?
Cevap: Buyukte uygun strateji ile.

8. En iyi ve en kotu test sonuclarinizi raporlayin.
Cevap: Checker, op sayisi, ortalama.

9. Hangi strateji 100de daha iyi, neden?
Cevap: Orta boyutta medium.

10. Hangi strateji 500de daha iyi, neden?
Cevap: Buyuk boyutta complex.

11. Checker OK verip yine de optimize olmama durumu nasil analiz edilir?
Cevap: Checker + performans analizi.

12. Tester scriptlerinizi savunmada nasil kullanirsiniz?
Cevap: Regresyon ve benchmark icin.

## 14) Performans ve Kompleksite Savunmasi
1. Big O ile gercek op sayisi farkini aciklayin.
Cevap: Big O teori, op sayisi pratik.

2. Asimptotik olarak iyi algoritma neden kucuk n de kaybedebilir?
Cevap: Sabit maliyet ve n kucuklugu.

3. Sabit katsayilar seciminizi nasil etkiledi?
Cevap: Strateji secimini etkiledi.

4. Op modelinde maliyetlerin esit oldugunu varsayiyor musunuz?
Cevap: Evet, benzer agirlik varsayilir.

5. rr ve rrr kullanimi katsayilari nasil dusurur?
Cevap: Iki adimi teke indirir.

6. Rotate yonu secimi toplam maliyeti nasil etkiler?
Cevap: Kisa yol secimi maliyeti dusurur.

7. Normalizasyonun performans katkisi nedir?
Cevap: Siralamayi sadeleştirir.

8. Arama operasyonlarinda cache etkisini onemsiyor musunuz?
Cevap: Evet, ama ikinci planda.

9. Fonksiyon cagrisi maliyeti bu projede onemli mi?
Cevap: Var, ama ana konu degil.

10. Mikro optimizasyon yerine hangi makro kararlari sectiniz?
Cevap: Strateji ve chunk kararlari.

## 15) Bellek ve Guvenlik
1. Program bitmeden tum heap bellegi temizleniyor mu?
Cevap: Evet, temizlenmeli.

2. Hata yolunda bellek kacagi olmamasi nasil garanti?
Cevap: Her error yolunda cleanup.

3. Cift free riskini nasil engellediniz?
Cevap: Tek sahiplik ve free disiplini.

4. Null kontrolu yaptiginiz kritik yerler neresi?
Cevap: Allocation ve baglanti noktalarinda.

5. Liste manipule ederken dangling pointer riski nerede?
Cevap: Node baglari guncellenirken.

6. Parserda ara yapilari nasil serbest birakiyorsunuz?
Cevap: Zamaninda free edilir.

7. Benchmark modu ek bellek kullaniyor mu?
Cevap: Hafif tutulmalidir.

8. Checker tarafinda stdin okuma buffer yonetimi nasil?
Cevap: Satir bazli ve dogrulamalı.

9. Beklenmeyen inputta neden segfault olmaz?
Cevap: Null ve input kontrolleri var.

10. Leaks veya valgrind ciktiniz ne diyor?
Cevap: Temiz cikis beklenir.

## 16) Checker Bonus Sorulari
1. Checker instruction parseriniz satir sonunu nasil ele aliyor?
Cevap: Satir sonunu komut sonu kabul eder.

2. Gecersiz komutta tam olarak ne yapiyorsunuz?
Cevap: Gecersiz komutta hata/KO.

3. Komut oncesi veya sonrasi bosluk neden hata olmali?
Cevap: Format bozulur.

4. EOF geldiğinde checker akisi nasil biter?
Cevap: Input bitince degerlendirme biter.

5. A sorted ve B bos ise neden OK?
Cevap: Hedef durum budur.

6. Diger tum durumlarda neden KO?
Cevap: Diger tum durumlar hata ya da KO.

7. Checkerda duplicate ve out of range kontrolu push_swap ile ayni mi?
Cevap: Temel kontrol benzer, akis farkli.

8. Checker ile push_swap ortak parser kullanmak dogru mu?
Cevap: Tam ortak parser iyi degil.

9. Checker performansi buyuk instruction akisinda nasil?
Cevap: Hafif ve line-by-line olmali.

10. Checkerda bellek sizintisini nasil test ettiniz?
Cevap: Valgrind ile.

## 17) Canli Kod Degisikligi Sorulari
1. Count only bayragi nereye eklenmeli?
Cevap: Flag ve yazdirma katmanina.

2. Mevcut yazdirma akisinda en az degisiklikle nasil eklenir?
Cevap: Tek kosul ekleyerek.

3. Count only aktifken op ler neden yazdirilmamali?
Cevap: Cunku stdout temiz kalmali.

4. Count only aktifken strateji ve checker uyumu nasil korunur?
Cevap: Strateji ayni, cikti modu farkli.

5. Count only bench ile birlikte calisirsa format ne olmali?
Cevap: stderr rapor, stdout sayim.

6. Parserda yeni flag cakismlarini nasil yoneteceksiniz?
Cevap: Bayrak catisma kontrolu ile.

7. Degisiklikten sonra hangi 5 hizli testi kosarsiniz?
Cevap: No-args, sorted, invalid, bench.

8. Bu degisikligi 10 dakikada nasil planlarsiniz?
Cevap: Once kontrol, sonra test.

9. Hata durumunda count only davranisi ne?
Cevap: Hata yine Error vermeli.

10. Bu ozelligi geri alinabilir sekilde nasil eklersiniz?
Cevap: Feature flag arkasinda.

## 18) Tuzak Sorular
1. Neden her zaman en az operasyonu urettiginizi iddia etmiyorsunuz?
Cevap: Mutlak optimum hedeflenmez.

2. Subject en kucuk liste diyor, gercekte optimal bulmak neden zor?
Cevap: Arama uzayi buyuk.

3. NP zorlugunda bir problem oldugunu biliyor musunuz?
Cevap: Evet, zor bir problem alanidir.

4. Stratejiniz deterministik degilse neden?
Cevap: Normalde deterministiktir.

5. Ayni inputta farkli output normal mi?
Cevap: Farkli flag/strateji ile olabilir.

6. rr yerine ra rb yazmak neden bazen ayni degil?
Cevap: Ayri op sayisi maliyeti artirir.

7. Sadece checker OK almak neden yeterli degil?
Cevap: Performans da degerlendirilir.

8. Complexity iddiasi koddan bagimsiz nasil test edilir?
Cevap: Gercek test ve benchmark ile.

9. Subjectte izinli fonksiyonlar disina cikarsaniz ne olur?
Cevap: Kurallara aykiri olur.

10. Undefined behavior u nasil engelliyorsunuz?
Cevap: Siki dogrulama ve pointer disiplini.

## 19) Hizli Sozlu Quiz
1. sa ile ra farki tek cumle?
Cevap: sa swap, ra rotate.

2. pb ne yapar?
Cevap: A dan B ye tasir.

3. rrr neyin kombinasyonu?
Cevap: rra + rrb.

4. Disorder 100 yuzde hangi dizilim?
Cevap: Ters sirali dizi.

5. Default strateji hangisi?
Cevap: Adaptive.

6. Bench nereye yazilir?
Cevap: stderr.

7. Error nereye yazilir?
Cevap: stderr.

8. No args davranisi?
Cevap: Sessiz cikis.

9. Duplicate durumda cikti?
Cevap: Error.

10. 42 tek elemanli inputta cikti?
Cevap: Cikti yok.

11. 0 1 2 3 zaten siraliysa kac op?
Cevap: 0.

12. Complex algoritmanizin adi?
Cevap: Radix.

13. Medium algoritmanizin ana fikri?
Cevap: Chunk bazli.

14. Simple algoritmanizin ana fikri?
Cevap: Min extraction.

15. Adaptive karar girdisi hangi metrik?
Cevap: Disorder.

## 20) En Zor Teorik Soru Seti
1. Su esitligi bench verinle coz ve crossover n bul:
Cevap: Bench verisiyle crossover bulunur.

2. Eger crossover 0.5 disorder ustunde cikiyorsa neden 0.5 esigi kullaniyorsun?
Cevap: Esikler deneysel tutulur.

3. Disorder ayni kalirken n artarsa neden strateji degismeli?
Cevap: n buyudukce sabit maliyet degisir.

4. Op modeli ve CPU zamani neden birebir ayni degil?
Cevap: CPU zamani ek etkiler tasir.

5. Ayni Big O sinifinda iki algoritmanin katsayi etkisini gercek veriyle kanitla.
Cevap: Gercek veriyle tablolanir.

6. Adaptive kararinda sadece inversion oranina bakmanin eksigi ne?
Cevap: Inversion tek basina yetmez.

7. Hangi ek ozelliklerle karar sinirlarini dinamik yaparsin?
Cevap: N, LIS, chunk sinyalleri.

8. Offline tuning ve online tuning farki nedir?
Cevap: Offline esik, online calisma anı.

9. Strateji seciminde overfitting nasil olusur?
Cevap: Tek dagilima fazla uyum.

10. Savunmada tek bir anti ornekle karar modelini nasil curutursun?
Cevap: Karsi ornekle maliyet gostermek.

## 21) Savunma Prova Sorulari
1. Kodunuzda en gurur duydugunuz fonksiyon hangisi, neden?
Cevap: En dengeli helper fonksiyon.

2. En riskli fonksiyon hangisi, neden?
Cevap: Pointer degistiren operasyonlar.

3. Bir bug bulunsa ilk nereden debug edersiniz?
Cevap: Parserdan baslarim.

4. Checker KO verdi, nasil kok nedeni bulursunuz?
Cevap: Input ve son stack durumunu bakarim.

5. Op sayisi birden artti, hangi metrikleri once incelersiniz?
Cevap: Strategy, chunk ve rotate.

6. Memory leak cikti, hangi yolaklardan suphelenirsiniz?
Cevap: Parse/split/stack temizligi.

7. Parser bugi ile algoritma bugini nasil ayirirsiniz?
Cevap: Hata mi algoritma mi ayrimi.

8. Kisa surede performans kazanimi icin neyi degistirirsiniz?
Cevap: Strateji secimi ve rotation.

9. Simdi yeniden yazsaniz neyi farkli yaparsiniz?
Cevap: Daha moduler ayirmak.

10. Bu projeden ogrendigin en kritik ders ne?
Cevap: Dogruluk ve performans dengesi.

## 22) Degerlendiriciye Sormaniz Gereken Karsilikli Sorular
1. Strateji seciminde op sayisi mi yoksa tutarlilik mi daha agir degerleniyor?
Cevap: Ikisi de onemli.

2. Benchmarkta format esnekligi siniri nedir?
Cevap: Sabit ve okunabilir format.

3. Bonus checker de hangi hata durumlari olmazsa olmaz?
Cevap: Gecersiz komut ve final durum.

4. Canli kod degisikliginde hangi kapsam bekleniyor?
Cevap: Kucuk ama etkili degisiklik.

5. Perf hedefinde ortalama mi tekil kosu mu esas?
Cevap: Tekil ve ortalama birlikte.

## Kullanim Plani
1. Her gun 20 soru secip sozlu cevap verin.
2. Zor sorulari not alip README ve kodla baglayin.
3. 100 ve 500 testlerinden gercek bench verisi toplayip sayisal savunma hazirlayin.
4. Iki kisi capraz sorgu yapin, herkes tum modulleri anlatabilsin.
5. Son prova: 10 dakika canli degisiklik ve hizli regresyon testi.
