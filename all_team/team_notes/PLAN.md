# Push Swap Plan

## Aşama 1 — Temel yapı
- `push_swap.h` dosyasını yeniden düzenle
- struct ve enum yapılarını belirle
- klasör ve dosya düzenini netleştir
- Makefile'ı temel kurallarla hazırla

## Aşama 2 — Parser
- flag parse kısmını yaz
- argümanları tokenize et
- sayı doğrulaması yap
- duplicate kontrolü ekle
- stack `a` oluştur

## Aşama 3 — Stack ve operasyonlar
- linked list stack yapısını tamamla
- temel stack yardımcılarını yaz
- `sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr` işlemlerini yaz
- operation yazdırma mantığını ekle

## Aşama 4 — Yardımcı fonksiyonlar
- `is_sorted`
- `stack_to_array`
- `assign_indexes`
- `compute_disorder`
- min / max / position yardımcıları

## Aşama 5 — Küçük sıralamalar
- `sort_2`
- `sort_3`
- `sort_4`
- `sort_5`

## Aşama 6 — Algoritmalar
- simple: insertion
- complex: radix
- medium: chunk
- adaptive: disorder'a göre seçim

## Aşama 7 — Bench
- operation sayaçları
- total operation sayısı
- strategy bilgisi
- disorder çıktısı
- `stderr` bench çıktısı

## Aşama 8 — Test
- parser hata testleri
- küçük input testleri
- random input testleri
- checker ile doğrulama
- leak ve crash kontrolü

## Aşama 9 — Bonus ve son düzen
- checker bonus
- README
- norm düzeltmeleri
- final performans testleri

## Kısa çalışma sırası
1. Header + parser
2. Stack + operations
3. Helpers + small sort
4. Radix
5. Insertion
6. Chunk
7. Adaptive
8. Bench
9. Test + checker + README
