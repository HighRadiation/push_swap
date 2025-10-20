# 🎯 Push Swap

İki stack kullanarak sayıları en az operasyonla sıralayan bir algoritma projesi.

**42 Istanbul** | **boksuz** | **2025**

---

## 📁 Proje Yapısı

```
push_swap/
│
├── 📁 include/          # Header dosyaları
│   ├── push_swap.h      # Ana header
│   ├── stack_ops.h      # Stack operasyonları
│   ├── utils.h          # Yardımcı fonksiyonlar
│   ├── ft_string.h      # String işlemleri
│   └── parsing.h        # Argüman parsing
│
├── 📁 src/              # Kaynak kodlar
│   ├── main.c
│   ├── parsing/         # Argüman işleme (ft_split desteği)
│   ├── push_swap/       # Sıralama algoritmaları
│   ├── stack_ops/       # Stack operasyonları (sa, pa, ra, vb.)
│   └── utils/           # Yardımcı fonksiyonlar
│
├── 📁 docs/             # Tüm dökümantasyon
│   ├── INDEX.md         # Dökümantasyon indeksi
│   ├── README_TR.md     # ⭐ Türkçe detaylı açıklama
│   └── ...              # Diğer dökümantasyon dosyaları
│
├── Makefile
└── README.md            # Bu dosya
```

## 🚀 Hızlı Başlangıç

### Derleme
```bash
make          # Derle
make clean    # Object dosyalarını sil
make fclean   # Tüm derleme çıktılarını sil
make re       # Temiz derleme
```

### Kullanım

**Normal argümanlar:**
```bash
./push_swap 4 2 1 3
```

**Tırnak içinde argümanlar (ft_split ile parse edilir):**
```bash
./push_swap "4 2 1 3"
```

Her iki format da desteklenir! ✨

## 📚 Dökümantasyon

Detaylı dökümantasyon için:
- **[docs/README_TR.md](docs/README_TR.md)** - Türkçe detaylı açıklama (BURADAN BAŞLA!)
- **[docs/INDEX.md](docs/INDEX.md)** - Tüm dökümantasyon indeksi

## ✨ Özellikler

✅ Modüler ve temiz kod yapısı  
✅ ft_split ile çift tırnak desteği  
✅ Integer overflow kontrolü  
✅ Duplicate sayı kontrolü  
✅ Memory leak yok  
✅ 42 Norm uyumlu  

---

**Daha fazla bilgi için `docs/` klasörüne bakın!**
