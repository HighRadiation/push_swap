# 📄 Stack Operasyonları Dokümantasyonu

**Dosyalar:** `src/stack_ops/*/*.c`  
**Amaç:** 42'nin tanımladığı 11 stack manipulation işlemi.

---

## 📋 İçindekiler

1. [Genel Bakış](#genel-bakış)
2. [Swap Operasyonları](#swap-operasyonları)
3. [Push Operasyonları](#push-operasyonları)
4. [Rotate Operasyonları](#rotate-operasyonları)
5. [Reverse Rotate Operasyonları](#reverse-rotate-operasyonları)
6. [Kullanım Stratejileri](#kullanım-stratejileri)

---

## Genel Bakış

Push_swap projesinde kullanılabilecek **11 adet** operasyon vardır:

| Kategori | Operasyonlar | Açıklama |
|----------|--------------|----------|
| **Swap** | sa, sb, ss | En üstteki 2 elemanı değiştirir |
| **Push** | pa, pb | Bir stack'ten diğerine taşır |
| **Rotate** | ra, rb, rr | Yukarı kaydırır (↑) |
| **Reverse Rotate** | rra, rrb, rrr | Aşağı kaydırır (↓) |

### Ortak Özellikler:

✅ Her operasyon stdout'a ismini yazdırır  
✅ Geçersiz durumda hiçbir şey yapmaz  
✅ Stack'i yerinde değiştirir  
✅ O(1) karmaşıklığı (çok hızlı!)

---

## Swap Operasyonları

### 🔹 sa (swap a)

**Dosya:** `src/stack_ops/swap/sa.c`

**İşlem:** Stack A'nın en üstteki 2 elemanını yer değiştirir.

#### Kod:

```c
static void	swap(t_stack **stack)
{
	t_stack	*first;
	t_stack	*second;

	// En az 2 eleman yoksa hiçbir şey yapma
	if (!*stack || !(*stack)->next)
		return ;
	
	first = *stack;
	second = first->next;
	
	// Yerlerini değiştir
	first->next = second->next;
	second->next = first;
	*stack = second;
}

void	sa(t_stack **stack_a)
{
	swap(stack_a);
	write(1, "sa\n", 3);  // Operasyonu yazdır
}
```

#### Görsel:

```
Before: [1, 2, 3, 4]
         ↓  ↓
After:  [2, 1, 3, 4]

Output: "sa\n"
```

#### Kullanım:

```c
t_stack *stack_a = /* [3, 2, 1] */;
sa(&stack_a);  // [2, 3, 1]
```

#### Edge Cases:

```c
// 0 eleman
sa(&NULL);  // Hiçbir şey yapmaz, yazdırmaz

// 1 eleman
sa(&[42]);  // Hiçbir şey yapmaz, ama "sa\n" yazdırır
```

---

### 🔹 sb (swap b)

**Dosya:** `src/stack_ops/swap/sb.c`

**İşlem:** Stack B için aynı swap işlemi.

#### Görsel:

```
Before B: [5, 6, 7]
           ↓  ↓
After B:  [6, 5, 7]

Output: "sb\n"
```

---

### 🔹 ss (swap both)

**Dosya:** `src/stack_ops/swap/ss.c`

**İşlem:** `sa` ve `sb`'yi aynı anda yapar.

#### Kod:

```c
void	ss(t_stack **stack_a, t_stack **stack_b)
{
	swap(stack_a);  // A'yı swap
	swap(stack_b);  // B'yi swap
	write(1, "ss\n", 3);  // Tek satır yazdır!
}
```

#### Avantaj:

**Hamle Tasarrufu!**

```c
// ❌ 2 hamle:
sa(&stack_a);  // "sa"
sb(&stack_b);  // "sb"

// ✅ 1 hamle:
ss(&stack_a, &stack_b);  // "ss"
```

#### Görsel:

```
Before A: [1, 2, 3]    Before B: [4, 5, 6]
After  A: [2, 1, 3]    After  B: [5, 4, 6]

Output: "ss\n"
```

---

## Push Operasyonları

### 🔹 pa (push to a)

**Dosya:** `src/stack_ops/push/pa.c`

**İşlem:** Stack B'nin en üst elemanını Stack A'nın başına taşır.

#### Kod:

```c
static void	push(t_stack **dest, t_stack **src)
{
	t_stack	*tmp;

	// Source boşsa hiçbir şey yapma
	if (!*src)
		return ;
	
	// Source'un en üstünü al
	tmp = *src;
	*src = (*src)->next;
	
	// Dest'in başına ekle
	tmp->next = *dest;
	*dest = tmp;
}

void	pa(t_stack **stack_a, t_stack **stack_b)
{
	push(stack_a, stack_b);
	write(1, "pa\n", 3);
}
```

#### Görsel:

```
Before:
A: [1, 2]
B: [3, 4]

pa

After:
A: [3, 1, 2]  ← 3 B'den geldi
B: [4]

Output: "pa\n"
```

#### Stack Diyagramı:

```
     B          A
    ┌─┐
    │3│─────────→  ┌─┐
    └─┘            │3│
    ┌─┐            ├─┤
    │4│            │1│
    └─┘            ├─┤
                   │2│
                   └─┘
```

#### Edge Cases:

```c
// B boş
A: [1, 2]  B: []
pa
A: [1, 2]  B: []  // Değişmez

// A boş
A: []  B: [3, 4]
pa
A: [3]  B: [4]  // Çalışır
```

---

### 🔹 pb (push to b)

**Dosya:** `src/stack_ops/push/pb.c`

**İşlem:** Stack A'dan Stack B'ye push.

#### Görsel:

```
Before:
A: [1, 2, 3]
B: [4]

pb

After:
A: [2, 3]
B: [1, 4]  ← 1 A'dan geldi

Output: "pb\n"
```

---

## Rotate Operasyonları

**Rotate:** Stack'i yukarı kaydırır (↑). En üstteki eleman en alta gider.

### 🔹 ra (rotate a)

**Dosya:** `src/stack_ops/rotate/ra.c`

**İşlem:** Stack A'yı yukarı döndürür.

#### Kod:

```c
static void	rotate(t_stack **stack)
{
	t_stack	*first;
	t_stack	*last;

	// En az 2 eleman yoksa hiçbir şey yapma
	if (!*stack || !(*stack)->next)
		return ;
	
	// İlk ve son elemanları al
	first = *stack;
	last = stack_last(*stack);
	
	// İlk elemanı ayır
	*stack = first->next;
	first->next = NULL;
	
	// İlk elemanı sona ekle
	last->next = first;
}

void	ra(t_stack **stack_a)
{
	rotate(stack_a);
	write(1, "ra\n", 3);
}
```

#### Görsel:

```
Before: [1, 2, 3, 4]
         ↓
After:  [2, 3, 4, 1]
                 ↑
1 en üstten en alta gitti

Output: "ra\n"
```

#### Circular Gösterim:

```
    1
   ↗ ↘
  4   2
   ↖ ↙
    3

ra yapınca saat yönünde döner:
    2
   ↗ ↘
  1   3
   ↖ ↙
    4
```

---

### 🔹 rb (rotate b)

**Dosya:** `src/stack_ops/rotate/rb.c`

**İşlem:** Stack B'yi yukarı döndürür.

```
Before B: [5, 6, 7, 8]
After  B: [6, 7, 8, 5]

Output: "rb\n"
```

---

### 🔹 rr (rotate both)

**Dosya:** `src/stack_ops/rotate/rr.c`

**İşlem:** `ra` ve `rb`'yi aynı anda yapar.

#### Kod:

```c
void	rr(t_stack **stack_a, t_stack **stack_b)
{
	rotate(stack_a);
	rotate(stack_b);
	write(1, "rr\n", 3);  // Tek satır!
}
```

#### Avantaj:

```c
// ❌ 2 hamle:
ra(&stack_a);
rb(&stack_b);

// ✅ 1 hamle:
rr(&stack_a, &stack_b);
```

#### Görsel:

```
Before A: [1, 2, 3]    Before B: [4, 5, 6]
After  A: [2, 3, 1]    After  B: [5, 6, 4]

Output: "rr\n"
```

---

## Reverse Rotate Operasyonları

**Reverse Rotate:** Stack'i aşağı kaydırır (↓). En alttaki eleman en üste gelir.

### 🔹 rra (reverse rotate a)

**Dosya:** `src/stack_ops/reverse_rotate/rra.c`

**İşlem:** Stack A'yı aşağı döndürür.

#### Kod:

```c
static void	reverse_rotate(t_stack **stack)
{
	t_stack	*last;
	t_stack	*second_last;

	// En az 2 eleman yoksa hiçbir şey yapma
	if (!*stack || !(*stack)->next)
		return ;
	
	// Son ve sondan bir önceki elemanı bul
	second_last = *stack;
	while (second_last->next->next)
		second_last = second_last->next;
	
	last = second_last->next;
	
	// Son elemanı ayır
	second_last->next = NULL;
	
	// Son elemanı başa ekle
	last->next = *stack;
	*stack = last;
}

void	rra(t_stack **stack_a)
{
	reverse_rotate(stack_a);
	write(1, "rra\n", 4);
}
```

#### Görsel:

```
Before: [1, 2, 3, 4]
                 ↓
After:  [4, 1, 2, 3]
         ↑
4 en alttan en üste geldi

Output: "rra\n"
```

#### ra vs rra:

```
        ra              rra
[1,2,3,4] → [2,3,4,1]   [1,2,3,4] → [4,1,2,3]
   ↓                       ↑
yukarı döndür          aşağı döndür
```

---

### 🔹 rrb (reverse rotate b)

**Dosya:** `src/stack_ops/reverse_rotate/rrb.c`

**İşlem:** Stack B'yi aşağı döndürür.

```
Before B: [5, 6, 7, 8]
After  B: [8, 5, 6, 7]

Output: "rrb\n"
```

---

### 🔹 rrr (reverse rotate both)

**Dosya:** `src/stack_ops/reverse_rotate/rrr.c`

**İşlem:** `rra` ve `rrb`'yi aynı anda yapar.

#### Kod:

```c
void	rrr(t_stack **stack_a, t_stack **stack_b)
{
	reverse_rotate(stack_a);
	reverse_rotate(stack_b);
	write(1, "rrr\n", 4);  // Tek satır!
}
```

#### Görsel:

```
Before A: [1, 2, 3]    Before B: [4, 5, 6]
After  A: [3, 1, 2]    After  B: [6, 4, 5]

Output: "rrr\n"
```

---

## Kullanım Stratejileri

### 1. Hamle Tasarrufu

**ss, rr, rrr kullan!**

```c
// Kötü (2 hamle):
sa(&a);
sb(&b);

// İyi (1 hamle):
ss(&a, &b);
```

### 2. Rotate Yönü Seçimi

**En kısa yolu seç!**

```c
Stack: [1, 2, 3, 4, 5]
Target: 5'i en üste getir

Option 1: ra × 4
Option 2: rra × 1  ← Daha iyi!

if (pos <= size/2)
    ra kullan
else
    rra kullan  // Daha az hamle
```

### 3. Push Stratejisi

**Küçük sayıları B'ye gönder**

```c
// sort_small stratejisi
while (size > 3)
{
    push_min_to_b();  // En küçüğü B'ye
}
sort_three(a);
while (b)
    pa();  // B'yi geri al (sıralı gelir!)
```

### 4. Radix Sort'ta Kullanım

**Bit'e göre ayır**

```c
if (bit == 0)
    pb();  // B'ye gönder
else
    ra();  // A'da tut, döndür
```

---

## 📊 Operasyon Özeti

| Operasyon | Stack A | Stack B | Output | Kullanım |
|-----------|---------|---------|--------|----------|
| sa | Swap | - | "sa" | 2 eleman |
| sb | - | Swap | "sb" | Nadir |
| ss | Swap | Swap | "ss" | Hamle tasarrufu |
| pa | ← B | Pop | "pa" | B'den geri al |
| pb | Pop | ← A | "pb" | A'dan B'ye gönder |
| ra | Rotate ↑ | - | "ra" | Döndür |
| rb | - | Rotate ↑ | "rb" | Döndür |
| rr | Rotate ↑ | Rotate ↑ | "rr" | İkisini birden |
| rra | Rev ↓ | - | "rra" | Ters döndür |
| rrb | - | Rev ↓ | "rrb" | Ters döndür |
| rrr | Rev ↓ | Rev ↓ | "rrr" | İkisini birden |

---

## 🎯 Önemli Notlar

1. **Her operasyon** stdout'a yazdırır
2. **ss, rr, rrr** hamle tasarrufu sağlar
3. **NULL kontrolü** her fonksiyonda var
4. **Edge case'ler** handle edilir (0-1 eleman)
5. **O(1) karmaşıklık** - çok hızlı!

---

## 💡 Debug İpuçları

### Test Kodu:

```c
void test_operations(void)
{
	t_stack *a = NULL;
	t_stack *b = NULL;
	
	// Stack oluştur
	stack_add_back(&a, stack_new(1));
	stack_add_back(&a, stack_new(2));
	stack_add_back(&a, stack_new(3));
	
	printf("Initial A: ");
	print_stack(a);
	
	// Test operasyonlar
	sa(&a);
	printf("After sa: ");
	print_stack(a);
	
	pb(&a, &b);
	printf("After pb - A: ");
	print_stack(a);
	printf("After pb - B: ");
	print_stack(b);
	
	ra(&a);
	printf("After ra: ");
	print_stack(a);
	
	// Temizlik
	free_stack(&a);
	free_stack(&b);
}
```

### Checker ile Test:

```bash
# Manuel test
echo -e "sa\npb\npb\nss\npa\npa" | ./checker_OS 3 2 1

# push_swap ile
ARG="3 2 1"; ./push_swap $ARG | ./checker_OS $ARG
```

---

## 📚 Bağlantılı Dosyalar

- `sort_small.c` → sa, ra, rra, pa, pb kullanır
- `sort_large.c` → ra, pa, pb kullanır (radix)
- `push_swap.c` → sa kullanır (2 eleman için)

---

## 🎓 Savunma Hazırlığı

### Sorulabilecek Sorular:

**1. sa ne yapar?**
> Stack A'nın en üstteki 2 elemanını yer değiştirir.

**2. pa ve pb farkı nedir?**
> pa: B'den A'ya, pb: A'dan B'ye taşır.

**3. Neden ss, rr, rrr var?**
> Hamle tasarrufu için. 2 hamle yerine 1 hamle.

**4. ra ve rra farkı?**
> ra: yukarı döndürür (↑), rra: aşağı döndürür (↓)

**5. Hangisi daha hızlı: ra mı rra mı?**
> İkisi de O(1), ama duruma göre daha az hamle gerektiren seçilir.

---

**Hazırlayan:** boksuz  
**Tarih:** 14 Ekim 2025  
**Proje:** push_swap @ 42 Istanbul

