🗺️ Push_swap Yol Haritası (Tamamlandı)

### Aşama 1: Teori ve Temeller

push_swap projesi bizden tam olarak ne istiyor? Stack (Yığın) mantığı nedir?
Big-O notasyonu nedir ve bu projede bizim için neden hayati öneme sahip?
Verileri tutmak için Dizi (Array) mi kullanmalıyız yoksa Bağlı Liste (Linked List) mi?


### Aşama 2: Girdi (Input) Kontrolü ve Ayrıştırma (Parsing)

Programımıza dışarıdan gelen sayıları (argc ve argv) nasıl alacağız?
Hata yönetimi: Gelen şey gerçekten bir sayı mı? INT_MIN ve INT_MAX sınırlarını taşıyor mu? Mükerrer (tekrar eden) sayı var mı?
Bellek sızıntısı (memory leak) oluşturmadan bu sayıları nasıl yöneteceğiz?


### Aşama 3: Veri Yapısının (Data Structure) İnşası

Yol haritamızın 1. aşamasında seçeceğimiz yapıya göre, Stack A'yı ilk sayı dizisiyle doldurma işlemi.
Bellek tahsisleri (malloc) ve temizleme (free) fonksiyonlarının yazılması.


### Aşama 4: Temel Kurallar ve İşlemler (Operations)

Oyunu kurallarına göre oynayacağımız hareketleri kodlama aşaması.
Swap (Yer Değiştirme): sa, sb, ss
Push (İtme): pa, pb
Rotate (Döndürme): ra, rb, rr
Reverse Rotate (Ters Döndürme): rra, rrb, rrr


### Aşama 5: Küçük Çaplı Sıralamalar (Micro Sorts)

2 ve 3 sayılık algoritmalar. (En efektif ve hardcoded şekilde çözüldü).
4 ve 5 sayılık algoritmalar. (B stack'ini depo gibi kullanarak A'nın alt ucuna adapte ettik).


### Aşama 6: Ana Algoritma ve Büyük Sayılar (Macro Sorts)

100 ve 500 sayılık zorlu testler için Big-O karmaşıklığını "Adaptive (Uyarlanabilir)" bir mimariyle çözmek.
- **Her şeyi birbirine bağlayan merkez:** Sayıların değerinden bağımsız `assign_rank_indexes` indeksleme (0... N-1 rank) altyapısı kuruldu.
- **Radix Sort:** Bitsel tabanda hatasız sıralayıcı testleri gerçekleştirildi.
- **Medium Chunks (Butterfly):** 500 ve 100 sayı testlerinde limitleri yıkıp geçmek için (5500 limitini 4700 civarıyla şampiyon kapattık) parçalı-hedef arayan zeki `sort_medium_chunks` algoritması tamamen entegre edildi. Adaptive sistem array uzunluklarına bakarak kusursuz rotalar çiziyor.


### Aşama 7: Optimizasyon, Benchmark ve Güvenlik Testleri

Norminette ile son kontroller tamamen sıfır hatayla atlatıldı (V4.1 pass).
Valgrind / Leaks ile %100 hafıza güvenliği onayı alındı.
- Benchmark Sistemi `bench_final.rb` ile stres testleri yapıldı. Proje teslim için kusursuzlaştı.
