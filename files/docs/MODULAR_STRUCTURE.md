# Push Swap - Modüler Klasör Yapısı

## 📁 Proje Yapısı

```
push_swap/
├── include/                 # Header dosyaları
│   ├── push_swap.h         # Ana header (tüm modülleri içerir)
│   ├── stack_ops.h         # Stack operasyonları (sa, sb, pa, pb, ra, rb, rra, rrb)
│   ├── utils.h             # Yardımcı fonksiyonlar
│   ├── ft_string.h         # String işlemleri (ft_split, ft_strlen, ft_isdigit)
│   └── parsing.h           # Argüman parsing ve validasyon
│
├── src/                    # Kaynak kodlar
│   ├── main.c              # Ana program
│   │
│   ├── parsing/            # Argüman parsing modülü
│   │   ├── parse_arguments.c     # Argüman parsing (tek/çoklu, "" desteği)
│   │   ├── validation_utils.c    # Validasyon fonksiyonları
│   │   ├── create_stack.c        # Stack oluşturma
│   │   └── parse_input.c         # Ekstra parsing utilities
│   │
│   ├── push_swap/          # Sıralama algoritmaları
│   │   ├── push_swap.c     # Ana sıralama mantığı
│   │   ├── sort_small.c    # Küçük sayılar için sıralama (3-5 eleman)
│   │   └── sort_large.c    # Büyük sayılar için sıralama
│   │
│   ├── stack_ops/          # Stack operasyonları
│   │   ├── swap/           # Swap operasyonları
│   │   │   ├── sa.c
│   │   │   ├── sb.c
│   │   │   └── ss.c
│   │   ├── push/           # Push operasyonları
│   │   │   ├── pa.c
│   │   │   └── pb.c
│   │   ├── rotate/         # Rotate operasyonları
│   │   │   ├── ra.c
│   │   │   ├── rb.c
│   │   │   └── rr.c
│   │   └── reverse_rotate/ # Reverse rotate operasyonları
│   │       ├── rra.c
│   │       ├── rrb.c
│   │       └── rrr.c
│   │
│   └── utils/              # Yardımcı fonksiyonlar
│       ├── utils.c         # Genel utilities (ft_atoi, error_exit)
│       ├── validation.c    # Stack validasyon (duplicates, index)
│       ├── min_max.c       # Min/max bulma fonksiyonları
│       │
│       ├── array/          # Stack/dizi operasyonları
│       │   ├── stack_new.c
│       │   ├── stack_add_back.c
│       │   ├── stack_add_front.c
│       │   ├── stack_last.c
│       │   ├── stack_size.c
│       │   └── free_stack.c
│       │
│       └── string/         # String işlemleri
│           ├── ft_split.c
│           ├── ft_strlen.c
│           └── ft_isdigit.c
│
├── Makefile                # Derleme ayarları
└── README.md               # Bu dosya
```

## 🎯 Modüler Tasarım Prensipleri

### 1. **Modül Ayrımı**
Her modül kendi sorumluluğuna odaklanır:
- **parsing/**: Argüman işleme ve validasyon
- **push_swap/**: Sıralama algoritmaları
- **stack_ops/**: Stack operasyonları (sa, pb, ra, vb.)
- **utils/**: Genel yardımcı fonksiyonlar

### 2. **Header Organizasyonu**
- `push_swap.h`: Ana header, tüm modülleri birleştirir
- `stack_ops.h`: Stack operasyon prototipleri
- `utils.h`: Utility fonksiyon prototipleri
- `ft_string.h`: String işlemleri
- `parsing.h`: Parsing fonksiyonları

### 3. **Bağımlılık Yönetimi**
Her modül sadece ihtiyacı olan header'ları include eder.

## 🚀 Kullanım

### Derleme
```bash
make          # Derle
make clean    # Object dosyalarını sil
make fclean   # Tüm derleme çıktılarını sil
make re       # Temiz derleme
```

### Çalıştırma

**Normal argümanlar:**
```bash
./push_swap 4 2 1 3
```

**Tırnak içinde argümanlar (ft_split kullanılır):**
```bash
./push_swap "4 2 1 3"
```

Her iki format da desteklenir!

## 🔧 Özellikler

✅ Modüler ve temiz klasör yapısı
✅ ft_split ile "" içindeki argüman desteği
✅ Tek veya çoklu argüman desteği
✅ Integer overflow kontrolü
✅ Duplicate kontrol
✅ Hata yönetimi
✅ Memory leak kontrolü (tüm malloc'lar free edilir)

## 📝 Notlar

- Tüm kodlar 42 Norm standardına uygundur
- Makefile `-Wall -Wextra -Werror` ile derler
- Memory leak yok (valgrind ile test edilebilir)
- Modüler yapı sayesinde kolay test edilebilir ve genişletilebilir

---
**Geliştirici:** boksuz
**Tarih:** 20 Ekim 2025
