# Push Swap — To-Do List


## 1. Temel düzen
- [x] `push_swap.h` dosyasını yeniden düzenle
- [x] İsimlendirmeyi sabitle (`t_node`, `t_stack`, `t_ctx`, `do_sa` gibi)
- [x] Klasör yapısını netleştir
- [x] Makefile'ı düzenle

## 2. Veri yapıları
- [x] `t_node` oluştur
- [x] `t_stack` oluştur
- [x] `t_strategy` enum oluştur
- [x] `t_op` enum oluştur
- [x] `t_bench` oluştur
- [x] `t_ctx` oluştur

## 3. Parser
- [x] `main(int argc, char **argv)` yaz
- [x] Flag parser yaz (`--simple`, `--medium`, `--complex`, `--adaptive`, `--bench`)
- [x] Tek string ve çoklu arg parse desteği ekle
- [x] Token doğrulama yap
- [x] `ft_atol` güvenli çalışsın
- [x] Duplicate kontrolü ekle
- [x] `stack a` oluştur
- [x] Hatalarda sadece `Error\n` yazdır

## 4. Stack katmanı
- [ ] `node_new`
- [ ] `node_add_back`
- [ ] `node_add_front`
- [ ] `stack_clear`
- [ ] `stack_is_sorted`
- [ ] `find_min_pos`
- [ ] `find_max_pos`

## 5. Operation motoru
### Sessiz işlemler
- [ ] `swap_stack`
- [ ] `push_stack`
- [ ] `rotate_stack`
- [ ] `reverse_rotate_stack`

### Yazdıran wrapper'lar
- [ ] `do_sa`
- [ ] `do_sb`
- [ ] `do_ss`
- [ ] `do_pa`
- [ ] `do_pb`
- [ ] `do_ra`
- [ ] `do_rb`
- [ ] `do_rr`
- [ ] `do_rra`
- [ ] `do_rrb`
- [ ] `do_rrr`

## 6. Yardımcılar
- [ ] `stack_to_array`
- [ ] `assign_indexes`
- [ ] `compute_disorder`
- [ ] `is_sorted`

## 7. Small sort
- [ ] `sort_2`
- [ ] `sort_3`
- [ ] `sort_4`
- [ ] `sort_5`

## 8. Algoritmalar
- [ ] `radix`
- [ ] `insertion`
- [ ] `chunk`
- [ ] `adaptive`

## 9. Bench
- [ ] Op sayaçlarını tut
- [ ] `total_ops` hesapla
- [ ] Disorder yazdır
- [ ] Strategy adını yazdır
- [ ] Çıktıyı `stderr`'e bas

## 10. Test
- [ ] Hatalı input testleri
- [ ] Sorted input testleri
- [ ] Reverse sorted testleri
- [ ] Random 10 / 100 / 500 testleri
- [ ] Leak testleri

## 11. Bonus
- [ ] `checker` yaz
- [ ] README'yi tamamla

---

## Kısa çalışma sırası
1. Header + struct
2. Parser
3. Stack
4. Operations
5. Small sort
6. Radix
7. Insertion
8. Chunk
9. Adaptive
10. Bench
11. Test + checker + README
