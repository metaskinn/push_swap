# Push Swap — To-Do List


## 1. Temel düzen
- [ ] `push_swap.h` dosyasını yeniden düzenle
- [ ] İsimlendirmeyi sabitle (`t_node`, `t_stack`, `t_ctx`, `do_sa` gibi)
- [ ] Klasör yapısını netleştir
- [ ] Makefile'ı düzenle

## 2. Veri yapıları
- [ ] `t_node` oluştur
- [ ] `t_stack` oluştur
- [ ] `t_strategy` enum oluştur
- [ ] `t_op` enum oluştur
- [ ] `t_bench` oluştur
- [ ] `t_ctx` oluştur

## 3. Parser
- [ ] `main(int argc, char **argv)` yaz
- [ ] Flag parser yaz (`--simple`, `--medium`, `--complex`, `--adaptive`, `--bench`)
- [ ] Tek string ve çoklu arg parse desteği ekle
- [ ] Token doğrulama yap
- [ ] `ft_atol` güvenli çalışsın
- [ ] Duplicate kontrolü ekle
- [ ] `stack a` oluştur
- [ ] Hatalarda sadece `Error\n` yazdır

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
