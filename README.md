# push_swap

42 okulu algoritma projesi. Rastgele sayılardan oluşan bir stack'i, sınırlı komut seti (`push`, `swap`, `rotate`, `reverse rotate`) ve minimum hamle sayısıyla sıralar.

## Kullanım

```bash
make
./push_swap 4 67 3 87 23
```

## Checker

Hamlelerin doğruluğunu test etmek için:

```bash
./push_swap 4 67 3 87 23 | ./checker 4 67 3 87 23
```

## Algoritma

- Küçük diziler (≤5 eleman): önceden tanımlı hamle setleri
- Büyük diziler: Radix sort tabanlı yaklaşım
- Hedef: 100 elemanlı dizide ~700 hamlenin altı

## Yapı

| Klasör/Dosya | Açıklama |
|---|---|
| `libft/` | Yardımcı fonksiyon kütüphanesi |
| `operations/` | push/swap/rotate işlemleri |
| `utils/` | Parsing ve yardımcı fonksiyonlar |
| `checker/` | Hamle doğrulama programı |
| `radix_sort.c` | Radix sort implementasyonu |

## Lisans

MIT
