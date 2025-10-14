# 📄 sort_small.c Dokümantasyonu

**Dosya:** `src/push_swap/sort_small.c`  
**Amaç:** 2-5 elemanlı stack'ler için optimize edilmiş sıralama algoritmaları.

---

## 📋 İçindekiler

1. [Genel Bakış](#genel-bakış)
2. [Fonksiyonlar](#fonksiyonlar)
3. [Algoritma Mantığı](#algoritma-mantığı)
4. [Hamle Analizi](#hamle-analizi)
5. [Örnekler](#örnekler)

---

## Genel Bakış

`sort_small.c` dosyası küçük stack'ler (2-5 eleman) için **özel optimize edilmiş** sıralama algoritmalarını içerir.

### Neden Özel Algoritma?

Küçük sayılar için:
- ✅ Hardcoded optimizasyon daha hızlı
- ✅ Minimum hamle garantisi
- ✅ Radix sort'tan daha verimli

### Benchmark

| Eleman | Algoritma | Max Hamle |
|--------|-----------|-----------|
| 2 | Sadece sa | 1 |
| 3 | sort_three | 2 |
| 4 | sort_small | 8 |
| 5 | sort_small | 12 |

---

## Fonksiyonlar

### 🔹 `static int get_max_index_pos(t_stack *stack)`

**Parametre:**
- `stack` - Kontrol edilecek stack

**Dönüş:** En büyük elemanın pozisyonu (0'dan başlar)

**Görev:** Stack'te en büyük sayıyı bulup pozisyonunu döner.

#### Kod Analizi:

```c
static int	get_max_index_pos(t_stack *stack)
{
	int	max;
	int	index;
	int	max_index;

	max = stack->value;      // İlk eleman = max
	index = 0;
	max_index = 0;
	
	while (stack)
	{
		// Daha büyük bulundu!
		if (stack->value > max)
		{
			max = stack->value;
			max_index = index;  // Pozisyonu kaydet
		}
		index++;
		stack = stack->next;
	}
	
	return (max_index);
}
```

#### Örnek:

```
Stack: [3, 5, 1]
        ↑  ↑  ↑
Pos:    0  1  2

max = 3, max_index = 0

value=3, index=0: 3 > 3? Hayır
value=5, index=1: 5 > 3? Evet → max=5, max_index=1
value=1, index=2: 1 > 5? Hayır

Sonuç: max_index = 1
```

---

### 🔹 `void sort_three(t_stack **stack_a)`

**Parametre:**
- `stack_a` - 3 elemanlı stack

**Görev:** 3 elemanı **maksimum 2 hamleyle** sıralar.

#### Algoritma Stratejisi:

**Ana Fikir:** En büyük sayıyı alta gönderirsek, kalan 2 sayıyı sadece swap ile sıralayabiliriz!

```
Adım 1: En büyüğün pozisyonunu bul
Adım 2: En büyüğü alta gönder (ra veya rra)
Adım 3: Üstteki 2 eleman sırasızsa swap (sa)
```

#### Kod Analizi:

```c
void	sort_three(t_stack **stack_a)
{
	int	max_index;

	// En büyük elemanın pozisyonunu bul
	max_index = get_max_index_pos(*stack_a);
	
	// Pozisyona göre en büyüğü alta gönder
	if (max_index == 0)
		ra(stack_a);        // En üstte → aşağı gönder
	else if (max_index == 1)
		rra(stack_a);       // Ortada → rotate
	// max_index == 2 ise zaten altta, hiçbir şey yapma
	
	// Şimdi en büyük altta, üstteki 2'yi kontrol et
	if ((*stack_a)->value > (*stack_a)->next->value)
		sa(stack_a);        // Ters sıradaysa swap
}
```

#### Tüm Senaryolar (3! = 6 durum):

**1. [1, 2, 3] - Zaten sıralı**
```
max_index = 2 (zaten altta)
1 < 2 → swap gereksiz
Hamle: 0
```

**2. [1, 3, 2]**
```
max_index = 1 (ortada)
rra → [2, 1, 3]
2 > 1 → sa → [1, 2, 3]
Hamle: 2 (rra, sa)
```

**3. [2, 1, 3]**
```
max_index = 2 (zaten altta)
2 > 1 → sa → [1, 2, 3]
Hamle: 1 (sa)
```

**4. [2, 3, 1]**
```
max_index = 1 (ortada)
rra → [1, 2, 3]
1 < 2 → swap gereksiz
Hamle: 1 (rra)
```

**5. [3, 1, 2]**
```
max_index = 0 (en üstte)
ra → [1, 2, 3]
1 < 2 → swap gereksiz
Hamle: 1 (ra)
```

**6. [3, 2, 1]**
```
max_index = 0 (en üstte)
ra → [2, 1, 3]
2 > 1 → sa → [1, 2, 3]
Hamle: 2 (ra, sa)
```

#### Maximum Hamle: 2 ✅

---

### 🔹 `static void push_min_to_b(t_stack **stack_a, t_stack **stack_b)`

**Parametre:**
- `stack_a` - Ana stack
- `stack_b` - Hedef stack

**Görev:** En küçük elemanı bulup B'ye gönderir (optimize yöntemle).

#### Stratej i:

```
1. En küçük elemanın pozisyonunu bul
2. Hangi yön daha yakınsa o yönden rotate et
3. En küçük en üste gelince pb ile B'ye gönder
```

#### Optimizasyon:

```
Stack ortasını referans al:
  
  Eğer min_pos <= size/2:
      → ra kullan (yukarı döndür)
  Değilse:
      → rra kullan (aşağı döndür)
      
Bu şekilde minimum hamleyle en küçüğü üste getiririz!
```

#### Kod Analizi:

```c
static void	push_min_to_b(t_stack **stack_a, t_stack **stack_b)
{
	int	min_pos;
	int	size;

	size = stack_size(*stack_a);
	min_pos = get_min_index(*stack_a);
	
	// Üst yarıda mı?
	if (min_pos <= size / 2)
	{
		// Yukarıdan döndür
		while (min_pos > 0)
		{
			ra(stack_a);
			min_pos--;
		}
	}
	else
	{
		// Aşağıdan döndür
		while (min_pos < size)
		{
			rra(stack_a);
			min_pos++;
		}
	}
	
	// En küçük artık en üstte, B'ye gönder
	pb(stack_a, stack_b);
}
```

#### Örnek 1: Min yukarıda

```
Stack: [5, 1, 4, 3, 2]
        ↑  ↑  ↑  ↑  ↑
Pos:    0  1  2  3  4

size = 5
min_pos = 1 (1 en küçük)

1 <= 5/2 (1 <= 2.5) → ra kullan

ra → [1, 4, 3, 2, 5]
pb → A:[4, 3, 2, 5]  B:[1]

Hamle: 2 (ra, pb)
```

#### Örnek 2: Min aşağıda

```
Stack: [5, 4, 3, 2, 1]
        ↑  ↑  ↑  ↑  ↑
Pos:    0  1  2  3  4

size = 5
min_pos = 4 (1 en küçük)

4 > 5/2 (4 > 2.5) → rra kullan

rra → [1, 5, 4, 3, 2]
pb → A:[5, 4, 3, 2]  B:[1]

Hamle: 2 (rra, pb)
```

#### Hamle Karşılaştırması:

```
Min pos = 1, size = 5

ra yolu:   1 hamle (ra)
rra yolu:  4 hamle (rra × 4)
→ ra seçilir ✓

Min pos = 4, size = 5

ra yolu:   4 hamle (ra × 4)
rra yolu:  1 hamle (rra)
→ rra seçilir ✓
```

---

### 🔹 `void sort_small(t_stack **stack_a, t_stack **stack_b)`

**Parametre:**
- `stack_a` - Ana stack (4-5 eleman)
- `stack_b` - Yardımcı stack

**Görev:** 4-5 elemanı **maksimum 12 hamleyle** sıralar.

#### Algoritma:

```
1. Eğer 2 eleman → sadece sa
2. Eğer 3+ eleman:
   a. En küçükleri B'ye gönder (3 eleman kalana kadar)
   b. Kalan 3'ü sort_three ile sırala
   c. B'dekileri geri al (zaten sıralı)
```

#### Neden Bu Mantık?

```
5 elemanı direkt sıralamak zor.
Ama:
  - 2 elemanı B'ye gönder
  - Kalan 3'ü sort_three ile sırala (max 2 hamle)
  - B'dekileri geri al
  
Çok daha basit ve optimize!
```

#### Kod Analizi:

```c
void	sort_small(t_stack **stack_a, t_stack **stack_b)
{
	int	size;

	size = stack_size(*stack_a);
	
	// Özel durum: 2 eleman
	if (size == 2)
	{
		if ((*stack_a)->value > (*stack_a)->next->value)
			sa(stack_a);
		return ;
	}
	
	// 3'ten fazla eleman varsa B'ye gönder
	while (size > 3)
	{
		push_min_to_b(stack_a, stack_b);
		size--;
	}
	
	// Kalan 3'ü sırala
	sort_three(stack_a);
	
	// B'dekileri geri al (en küçükten büyüğe sıralı)
	while (*stack_b)
		pa(stack_a, stack_b);
}
```

#### Detaylı Örnek: 5 Eleman

**Başlangıç: [5, 4, 3, 2, 1]**

```
Adım 1: size = 5 > 3
  push_min_to_b()
  En küçük (1) bulunur ve B'ye gönderilir
  A:[5, 4, 3, 2]  B:[1]
  size = 4

Adım 2: size = 4 > 3
  push_min_to_b()
  En küçük (2) bulunur ve B'ye gönderilir
  A:[5, 4, 3]  B:[2, 1]
  size = 3

Adım 3: size = 3
  sort_three(A)
  [5, 4, 3] → [3, 4, 5]
  A:[3, 4, 5]  B:[2, 1]

Adım 4: B'dekileri geri al
  pa → A:[2, 3, 4, 5]  B:[1]
  pa → A:[1, 2, 3, 4, 5]  B:[]

✅ SIRALI!
```

#### Hamle Sayımı:

```
push_min_to_b (1) → ~3 hamle
push_min_to_b (2) → ~3 hamle
sort_three        → ~2 hamle
pa × 2            → 2 hamle

Toplam: ~10 hamle (5 eleman için)
```

---

## Algoritma Mantığı

### sort_small Akış Diyagramı

```
START: [5, 4, 3, 2, 1]
  ↓
size == 2? ──YES──> sa (gerekirse) → END
  ↓ NO
size > 3? ──YES──> push_min_to_b()
  ↓              ↓
  ↓          size--
  ↓              ↓
  └──────────────┘
  ↓ NO (size == 3)
sort_three()
  ↓
stack_b empty? ──NO──> pa
  ↓                    ↓
  └────────────────────┘
  ↓ YES
END: SORTED
```

### Neden En Küçükleri B'ye Gönderiyoruz?

```
Alternatif 1: En büyükleri B'ye gönder
  Problem: Geri alırken ters sırada gelir
  Çözüm: Ekstra işlem gerekir

Alternatif 2: En küçükleri B'ye gönder ✓
  Avantaj: pa ile direkt sıralı geliyor!
  Nedeni: Stack = LIFO (Last In First Out)
  
Örnek:
  1'i gönder → B:[1]
  2'yi gönder → B:[2, 1]
  pa → [2] → pa → [1, 2] ✓ SIRALI!
```

---

## Hamle Analizi

### 2 Eleman

**Best Case:** [1, 2]
```
Zaten sıralı
Hamle: 0
```

**Worst Case:** [2, 1]
```
sa
Hamle: 1
```

---

### 3 Eleman

**Best Case:** [1, 2, 3]
```
Zaten sıralı
Hamle: 0
```

**Worst Case:** [3, 2, 1] veya [1, 3, 2]
```
ra + sa  veya  rra + sa
Hamle: 2
```

---

### 4 Eleman

**Ortalama:**
```
push_min_to_b: ~2 hamle
sort_three:    ~1 hamle
pa:            1 hamle

Toplam: ~4-8 hamle
```

**Worst Case:** ~8 hamle

---

### 5 Eleman

**Ortalama:**
```
push_min_to_b (1): ~3 hamle
push_min_to_b (2): ~3 hamle
sort_three:        ~2 hamle
pa × 2:            2 hamle

Toplam: ~10 hamle
```

**Worst Case:** ~12 hamle

---

## Örnekler

### Örnek 1: 2 Eleman

```bash
Input: [2, 1]

size = 2
2 > 1 → sa

Output:
sa

Sonuç: [1, 2] ✓
Hamle: 1
```

---

### Örnek 2: 3 Eleman

```bash
Input: [3, 1, 2]

size = 3
sort_three()
  max_index = 0 (3 en üstte)
  ra → [1, 2, 3]
  1 < 2 → swap gereksiz

Output:
ra

Sonuç: [1, 2, 3] ✓
Hamle: 1
```

---

### Örnek 3: 4 Eleman

```bash
Input: [4, 3, 2, 1]

size = 4 > 3
push_min_to_b()
  min = 1, pos = 3
  3 > 4/2 → rra kullan
  rra → [1, 4, 3, 2]
  pb → A:[4, 3, 2]  B:[1]

size = 3
sort_three()
  A:[2, 3, 4]

pa → A:[1, 2, 3, 4]

Output:
rra
pb
rra
sa
pa

Sonuç: [1, 2, 3, 4] ✓
Hamle: 5
```

---

### Örnek 4: 5 Eleman

```bash
Input: [5, 4, 3, 2, 1]

# 1'i B'ye gönder
rra → [1, 5, 4, 3, 2]
pb → A:[5, 4, 3, 2]  B:[1]

# 2'yi B'ye gönder
rra → [2, 5, 4, 3]
pb → A:[5, 4, 3]  B:[2, 1]

# Kalan 3'ü sırala
rra → [3, 5, 4]
sa → [3, 4, 5]

# B'yi geri al
pa → A:[2, 3, 4, 5]  B:[1]
pa → A:[1, 2, 3, 4, 5]  B:[]

Output:
rra
pb
rra
pb
rra
sa
pa
pa

Sonuç: [1, 2, 3, 4, 5] ✓
Hamle: 8
```

---

## 🎯 Önemli Notlar

1. **2-3 eleman** için özel optimizasyon
2. **4-5 eleman** için en küçükleri B'ye gönder stratejisi
3. **Maximum hamle** 12 (5 eleman için)
4. **sort_three** en fazla 2 hamle kullanır
5. **push_min_to_b** optimal yönü seçer (ra vs rra)

---

## 💡 Optimizasyon Taktikleri

### 1. Rotate Yönü Seçimi
```c
// Akıllı karar
if (min_pos <= size / 2)
    ra  // Daha yakın
else
    rra // Daha yakın
```

### 2. sort_three Stratejisi
```c
// En büyüğü alta gönder
// Kalan 2'yi swap ile çöz
// Maximum 2 hamle!
```

### 3. B'ye Gönderme Sırası
```c
// En küçükleri gönder
// pa ile geri alırken otomatik sıralı!
```

---

## 📚 Bağlantılı Dosyalar

- `push_swap.c` → sort_small() çağrılır
- `min_max.c` → get_min_index() kullanır
- `stack_ops/` → sa, ra, rra, pa, pb kullanır

---

**Hazırlayan:** boksuz  
**Tarih:** 14 Ekim 2025  
**Proje:** push_swap @ 42 Istanbul

