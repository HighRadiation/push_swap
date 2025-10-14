# Header Dosyaları Dokümantasyonu

## 📁 include/push_swap.h

### Amaç
Ana header dosyası. Stack yapısını ve temel fonksiyonları tanımlar.

### İçerik

#### 1. Include'lar
```c
#include <stdlib.h>   // malloc, free için
#include <unistd.h>   // write için
#include "stack_ops.h"
#include "utils.h"
```

#### 2. Stack Yapısı
```c
typedef struct s_stack
{
    int             value;   // Sayının değeri
    int             index;   // Sıralı indexi (radix sort için)
    struct s_stack  *next;   // Sonraki node
}   t_stack;
```

**Neden linked list?**
- Push/pop işlemleri O(1)
- Dinamik boyut
- Stack mantığına uygun

**Index nedir?**
- Sayıları 0'dan n-1'e normalize eder
- Örnek: [5, 2, 8] → index: [1, 0, 2]
- Radix sort için gerekli

#### 3. Stack Temel Fonksiyonlar

**stack_new(int value)**
- Yeni bir node oluşturur
- Malloc ile yer ayırır
- Value'yu atar, index -1, next NULL

**stack_add_back(t_stack **stack, t_stack *new)**
- Yeni node'u stack'in sonuna ekler
- Stack boşsa, new ilk eleman olur

**stack_add_front(t_stack **stack, t_stack *new)**
- Yeni node'u stack'in başına ekler
- Stack operasyonlarında kullanılır

**stack_size(t_stack *stack)**
- Stack'teki eleman sayısını döner
- NULL ise 0 döner

**stack_last(t_stack *stack)**
- Stack'in son elemanını döner
- rotate işlemlerinde kullanılır

**free_stack(t_stack **stack)**
- Tüm stack'i free eder
- Memory leak'i önler

#### 4. Sıralama Fonksiyonları

**sort_three(t_stack **stack_a)**
- 3 elemanlı stack'i sıralar
- En optimize yöntemle

**sort_small(t_stack **stack_a, t_stack **stack_b)**
- 2-5 elemanlı stack'ler için
- Hardcoded optimizasyon

**sort_large(t_stack **stack_a, t_stack **stack_b)**
- 5+ elemanlı stack'ler için
- Radix sort veya başka algoritma

#### 5. Yardımcı Fonksiyonlar

**is_sorted(t_stack *stack)**
- Stack sıralı mı kontrol eder
- Zaten sıralıysa işlem yapmayız

**push_swap(t_stack **stack_a, t_stack **stack_b)**
- Ana mantık
- Hangi algoritmayı kullanacağına karar verir

---

## 📁 include/stack_ops.h

### Amaç
Tüm stack operasyonlarını tanımlar. 42'nin verdiği 11 komut.

### İçerik

#### Forward Declaration
```c
typedef struct s_stack  t_stack;
```
Circular dependency önlemek için.

#### Swap Operasyonları
**sa** - Stack A'nın en üstteki 2 elemanını değiştirir
- "sa" yazdırır
- En az 2 eleman olmalı

**sb** - Stack B için aynı
- "sb" yazdırır

**ss** - Her ikisini birden yapar
- "ss" yazdırır
- sa + sb'yi tek seferde yapar (hamle tasarrufu)

#### Push Operasyonları
**pa** - Stack B'den A'ya push
- "pa" yazdırır
- B boş olmamalı
- B'nin en üstünü al, A'nın başına koy

**pb** - Stack A'dan B'ye push
- "pb" yazdırır
- A boş olmamalı

#### Rotate Operasyonları (Yukarı)
**ra** - Stack A'yı yukarı döndür
- "ra" yazdırır
- En üstteki eleman en alta gider
- Örnek: [1,2,3] → [2,3,1]

**rb** - Stack B için aynı

**rr** - Her ikisini birden
- "rr" yazdırır
- ra + rb

#### Reverse Rotate Operasyonları (Aşağı)
**rra** - Stack A'yı aşağı döndür
- "rra" yazdırır
- En alttaki eleman en üste gelir
- Örnek: [1,2,3] → [3,1,2]

**rrb** - Stack B için aynı

**rrr** - Her ikisini birden
- "rrr" yazdırır
- rra + rrb

### Kullanım Mantığı
- Her operasyon stdout'a komut adını yazdırır
- Checker bu komutları okuyup doğrular
- Minimum hamle için ss, rr, rrr kullanmak önemli

---

## 📁 include/utils.h

### Amaç
Yardımcı fonksiyonları tanımlar. Parsing, validation, min/max bulma.

### İçerik

#### 1. Temel String İşlemleri

**ft_atoi(const char *str)**
- String'i integer'a çevirir
- Negatif sayıları destekler
- Hata varsa error_exit çağırır

**ft_putstr(char *str)**
- String yazdırır
- write(1, ...) kullanır
- Newline eklemez

**error_exit(void)**
- "Error\n" yazdırır stderr'e
- exit(1) ile çıkar
- Tüm hatalar burada

#### 2. Validation Fonksiyonları

**check_args(char **argv)**
- Argümanları kontrol eder
- Sayı mı değil mi?
- INT_MIN ve INT_MAX arasında mı?
- Boş string var mı?
- Return: 1 OK, 0 HATA

**has_duplicates(t_stack *stack)**
- Stack'te tekrar eden sayı var mı?
- Return: 1 varsa, 0 yoksa

**index_stack(t_stack **stack)**
- Her elemanın index'ini belirler
- En küçük sayı = 0, en büyük = n-1
- Radix sort için gerekli

#### 3. Min/Max Fonksiyonları

**get_min(t_stack *stack)**
- Stack'teki en küçük değeri döner
- Tüm stack'i dolaşır

**get_max(t_stack *stack)**
- Stack'teki en büyük değeri döner

**get_min_index(t_stack *stack)**
- En küçük sayının stack'teki pozisyonunu döner
- 0'dan başlar (top = 0)
- Rotate için hangi yöne döneceğimize karar vermede kullanılır

---

## 🔧 Makefile Düzeltmeleri

### Yapılan Değişiklikler

#### 1. Değişken Adı Tutarsızlığı Düzeltildi
```makefile
# ÖNCE (YANLIŞ):
OBJ = $(SRC:.c=.o)
$(NAME): $(OBJS)    # ❌ OBJS tanımlı değil

# SONRA (DOĞRU):
OBJ = $(SRC:.c=.o)
$(NAME): $(OBJ)     # ✅ OBJ kullanılıyor
```

#### 2. Clean Kuralı Düzeltildi
```makefile
# ÖNCE:
clean:
    rm -f $(OBJS)   # ❌

# SONRA:
clean:
    rm -f $(OBJ)    # ✅
```

### Makefile Mantığı

**all**
- Default hedef
- $(NAME) compile eder

**$(NAME)**
- Tüm .o dosyalarını linker
- push_swap executable'ı oluşturur

**%.o: %.c**
- Her .c dosyasını .o'ya compile eder
- -I include ile header'ları bulur

**clean**
- Object dosyalarını siler
- Source'lar kalır

**fclean**
- Executable'ı siler
- clean + binary

**re**
- fclean + all
- Sıfırdan derleme

### Kullanım
```bash
make           # Derle
make clean     # .o'ları temizle
make fclean    # Her şeyi temizle
make re        # Yeniden derle
```

---

## 📊 Dosya Yapısı Özeti

```
include/
├── push_swap.h    → Ana tanımlar, struct, fonksiyonlar
├── stack_ops.h    → 11 stack operasyonu (sa, pb, rra...)
└── utils.h        → Yardımcı fonksiyonlar

src/
├── main.c         → Program başlangıcı
├── push_swap/
│   ├── push_swap.c     → Ana mantık
│   ├── sort_small.c    → 2-5 eleman sıralama
│   └── sort_large.c    → 5+ eleman sıralama
├── stack_ops/
│   ├── swap.c          → sa, sb, ss
│   ├── push.c          → pa, pb
│   ├── rotate.c        → ra, rb, rr
│   └── reverse_rotate.c → rra, rrb, rrr
└── utils/
    ├── validation.c    → Input kontrolü
    ├── array.c         → Stack işlemleri
    └── min_max.c       → Min/max bulma

Makefile           → Derleme kuralları
```

---

## ⚠️ Önemli Notlar

### Norm Kuralları
- Her fonksiyon max 25 satır
- Max 4 parametre
- Her dosya max 5 fonksiyon
- Her satır max 80 karakter
- Tab kullan, space değil
- Snake_case isimlendirme

### Memory Management
- Her malloc için free olmalı
- Hata durumunda tüm stack free edilmeli
- Valgrind ile test yapılmalı

### Error Handling
- Hatalı input → "Error\n" + exit(1)
- Duplicate sayı → Error
- Sayı değil → Error
- INT overflow → Error

### Test Senaryoları
```bash
./push_swap 2 1 3        # 3 eleman
./push_swap 5 4 3 2 1    # 5 eleman
./push_swap 42           # 1 eleman (hiçbir şey yapma)
./push_swap 1 2 3        # Zaten sıralı (hiçbir şey yapma)
./push_swap abc          # Error
./push_swap 1 1          # Error (duplicate)
```

---

## 🎯 Sıradaki Adımlar

1. ✅ Header dosyaları tamam
2. ⏳ Stack operasyonlarını kodla (swap.c'den başla)
3. ⏳ Yardımcı fonksiyonları yaz
4. ⏳ Sıralama algoritmalarını implement et
5. ⏳ main.c'yi yaz
6. ⏳ Test et

---

**Hazırlayan:** boksuz
**Tarih:** 14 Ekim 2025
**Proje:** push_swap - 42 Istanbul

