# Git Günlük Çalışma Akışı

## Her Gün Sabah

```bash
cd push_swap                          # Proje klasörüne gir
git checkout main                     # Main branch'e geç
git pull origin main                  # Main'in en güncel halini al
git checkout alex                     # Kendi branch'ine geç
git merge main                        # Main'deki güncel değişiklikleri kendi branch'ine ekle
```

## Kod Yazdıktan Sonra

```bash
git status                            # Hangi dosyaların değiştiğini kontrol et
git add .                             # Tüm değişiklikleri ekle
git commit -m "Yaptigin degisiklik"   # Yaptığın işi açıklayan commit oluştur
git push origin alex                  # Kendi branch'indeki değişiklikleri GitHub'a gönder
```

## İş Bitince Main'e Aktar

```bash
git checkout main                     # Tekrar main branch'e geç
git pull origin main                  # Önce main'i yine güncelle
git merge alex                        # Kendi branch'indeki değişiklikleri main'e birleştir
git push origin main                  # Main'in yeni halini GitHub'a gönder
```

## Devam Etmek İçin Tekrar Branch'e Dön

```bash
git checkout alex                     # Yeni işlere kendi branch'inde devam et
```


