# 📄 min_max.c Dokümantasyonu

**Dosya:** `src/utils/min_max.c`  
**Amaç:** Stack'te minimum ve maksimum değer bulma fonksiyonları.

---

## 📋 İçindekiler

1. [Genel Bakış](#genel-bakış)
2. [Fonksiyonlar](#fonksiyonlar)
3. [Kullanım Örnekleri](#kullanım-örnekleri)
4. [Performans Analizi](#performans-analizi)

---

## Genel Bakış

`min_max.c` dosyası stack içindeki min/max değerleri bulmak için kullanılır:

✅ En küçük değeri bulur  
✅ En büyük değeri bulur  
✅ En küçük elemanın pozisyonunu bulur

**Kullanım Alanları:**
- `sort_small.c` - En küçük elemanı bulmak için
- Rotate yönü kararı - ra mı rra mı kullanılacak?

---

## Fonksiyonlar

### 🔹 `int get_min(t_stack *stack)`

**Parametre:**
- `stack` - Kontrol edilecek stack

**Dönüş:** Stack'teki en küçük değer

**Görev:** Stack'i dolaşıp en küçük değeri bulur.

#### Kod Analizi:

```c
int	get_min(t_stack *stack)
{
	int	min;

	// Stack boşsa 0 döndür
	if (!stack)
		return (0);
	
	// İlk elemanı min olarak ata
	min = stack->value;
	
	// Stack'i dolaş
	while (stack)
	{
		// Daha küçük bulursan güncelle
		if (stack->value < min)
			min = stack->value;
		
		stack = stack->next;
	}
	
	return (min);
}
```

#### Algoritma Mantığı:

```
1. İlk elemanı minimum olarak işaretle
2. Stack'teki her eleman için:
   - Eğer current < min:
       min = current
3. Minimum değeri döndür
```

#### Örnek 1: Normal Stack

```
Stack: [5, 2, 8, 1, 3]

Adım 1: min = 5
Adım 2: 2 < 5  → min = 2
Adım 3: 8 < 2  → hayır
Adım 4: 1 < 2  → min = 1
Adım 5: 3 < 1  → hayır

Sonuç: 1
```

#### Örnek 2: Negatif Sayılar

```
Stack: [3, -5, 2, -10, 0]

Adım 1: min = 3
Adım 2: -5 < 3   → min = -5
Adım 3: 2 < -5   → hayır
Adım 4: -10 < -5 → min = -10
Adım 5: 0 < -10  → hayır

Sonuç: -10
```

#### Örnek 3: Tek Eleman

```
Stack: [42]

min = 42
Döngü çalışmaz (next = NULL)

Sonuç: 42
```

#### Örnek 4: Boş Stack

```
Stack: NULL

if (!stack) → return 0

Sonuç: 0
```

#### Karmaşıklık:

- **Zaman:** O(n) - Tüm stack'i dolaşır
- **Alan:** O(1) - Sadece min değişkeni

---

### 🔹 `int get_max(t_stack *stack)`

**Parametre:**
- `stack` - Kontrol edilecek stack

**Dönüş:** Stack'teki en büyük değer

**Görev:** Stack'i dolaşıp en büyük değeri bulur.

#### Kod Analizi:

```c
int	get_max(t_stack *stack)
{
	int	max;

	// Stack boşsa 0 döndür
	if (!stack)
		return (0);
	
	// İlk elemanı max olarak ata
	max = stack->value;
	
	// Stack'i dolaş
	while (stack)
	{
		// Daha büyük bulursan güncelle
		if (stack->value > max)
			max = stack->value;
		
		stack = stack->next;
	}
	
	return (max);
}
```

#### Algoritma Mantığı:

```
1. İlk elemanı maksimum olarak işaretle
2. Stack'teki her eleman için:
   - Eğer current > max:
       max = current
3. Maksimum değeri döndür
```

#### Örnek 1: Normal Stack

```
Stack: [5, 2, 8, 1, 3]

Adım 1: max = 5
Adım 2: 2 > 5  → hayır
Adım 3: 8 > 5  → max = 8
Adım 4: 1 > 8  → hayır
Adım 5: 3 > 8  → hayır

Sonuç: 8
```

#### Örnek 2: Negatif Sayılar

```
Stack: [-5, -2, -10, -1]

Adım 1: max = -5
Adım 2: -2 > -5  → max = -2
Adım 3: -10 > -2 → hayır
Adım 4: -1 > -2  → max = -1

Sonuç: -1
```

#### Karmaşıklık:

- **Zaman:** O(n)
- **Alan:** O(1)

---

### 🔹 `int get_min_index(t_stack *stack)`

**Parametre:**
- `stack` - Kontrol edilecek stack

**Dönüş:** En küçük elemanın pozisyonu (0'dan başlar)

**Görev:** En küçük elemanın stack'te hangi pozisyonda olduğunu bulur.

#### Neden Gerekli?

**Rotate yönüne karar vermek için!**

```
Stack size: 10
Min position: 3

Eğer pos < size/2 (3 < 5):
    → ra kullan (yukarı döndür, 3 hamle)
Eğer pos >= size/2:
    → rra kullan (aşağı döndür, daha az hamle)
```

#### Kod Analizi:

```c
int	get_min_index(t_stack *stack)
{
	int	min;
	int	index;
	int	min_index;

	// Stack boşsa 0 döndür
	if (!stack)
		return (0);
	
	// İlk elemanı min olarak işaretle
	min = stack->value;
	index = 0;
	min_index = 0;
	
	// Stack'i dolaş
	while (stack)
	{
		// Daha küçük bulursan hem min hem de index'i güncelle
		if (stack->value < min)
		{
			min = stack->value;
			min_index = index;  // Bu pozisyonu kaydet
		}
		
		index++;  // Pozisyon sayacı
		stack = stack->next;
	}
	
	return (min_index);
}
```

#### Algoritma Mantığı:

```
1. İlk elemanı min olarak işaretle, pozisyon = 0
2. Her eleman için:
   - Eğer daha küçük bulursan:
       min = yeni değer
       min_index = mevcut pozisyon
   - Pozisyon sayacını artır
3. min_index'i döndür
```

#### Detaylı Örnek:

```
Stack: [5, 2, 8, 1, 3]
        ↑  ↑  ↑  ↑  ↑
Pos:    0  1  2  3  4

Başlangıç:
  min = 5
  min_index = 0
  index = 0

Adım 1: value=5, index=0
  5 < 5? Hayır
  index = 1

Adım 2: value=2, index=1
  2 < 5? Evet
  min = 2
  min_index = 1
  index = 2

Adım 3: value=8, index=2
  8 < 2? Hayır
  index = 3

Adım 4: value=1, index=3
  1 < 2? Evet
  min = 1
  min_index = 3  ← BULUNDU!
  index = 4

Adım 5: value=3, index=4
  3 < 1? Hayır
  index = 5

Sonuç: min_index = 3
```

#### Görsel Gösterim:

```
Stack: [5, 2, 8, 1, 3]
Positions: 
  0: 5
  1: 2
  2: 8
  3: 1  ← EN KÜÇÜK (return 3)
  4: 3
```

#### Rotate Kararı Örneği:

**Stack: [5, 2, 8, 1, 3, 9, 7, 4, 6]**

```
Size: 9
Min (1) position: 3

Karar:
  3 < 9/2 (3 < 4.5)
  → ra kullan (yukarı döndür)
  
Hamle sayısı:
  ra 3 kere → 3 hamle
  vs
  rra 6 kere → 6 hamle
  
→ ra daha verimli!
```

**Stack: [5, 2, 8, 9, 7, 4, 6, 1, 3]**

```
Size: 9
Min (1) position: 7

Karar:
  7 >= 9/2 (7 >= 4.5)
  → rra kullan (aşağı döndür)
  
Hamle sayısı:
  ra 7 kere → 7 hamle
  vs
  rra 2 kere → 2 hamle
  
→ rra daha verimli!
```

#### Kullanım Örneği (sort_small.c):

```c
static void	push_min_to_b(t_stack **stack_a, t_stack **stack_b)
{
	int	min_pos;
	int	size;

	size = stack_size(*stack_a);
	min_pos = get_min_index(*stack_a);  // ← BURADA KULLANILIR
	
	// Optimum yönü seç
	if (min_pos <= size / 2)
	{
		// Yukarıdan daha yakın → ra kullan
		while (min_pos > 0)
		{
			ra(stack_a);
			min_pos--;
		}
	}
	else
	{
		// Aşağıdan daha yakın → rra kullan
		while (min_pos < size)
		{
			rra(stack_a);
			min_pos++;
		}
	}
	
	pb(stack_a, stack_b);  // En küçüğü B'ye gönder
}
```

#### Karmaşıklık:

- **Zaman:** O(n)
- **Alan:** O(1)

---

## Kullanım Örnekleri

### Örnek 1: Basit Kullanım

```c
t_stack *stack = create_stack(...);  // [5, 2, 8, 1, 3]

int min = get_min(stack);            // 1
int max = get_max(stack);            // 8
int min_pos = get_min_index(stack);  // 3

printf("Min: %d\n", min);            // Min: 1
printf("Max: %d\n", max);            // Max: 8
printf("Min Position: %d\n", min_pos); // Min Position: 3
```

### Örnek 2: Negatif Sayılar

```c
// Stack: [-10, -5, -2, -15, 0]

get_min(stack);       // -15
get_max(stack);       // 0
get_min_index(stack); // 3
```

### Örnek 3: Tek Eleman

```c
// Stack: [42]

get_min(stack);       // 42
get_max(stack);       // 42
get_min_index(stack); // 0
```

### Örnek 4: İki Eleman

```c
// Stack: [10, 5]

get_min(stack);       // 5
get_max(stack);       // 10
get_min_index(stack); // 1
```

---

## Performans Analizi

### Karmaşıklık Tablosu

| Fonksiyon | Zaman | Alan | Döngü Sayısı |
|-----------|-------|------|--------------|
| get_min | O(n) | O(1) | 1 |
| get_max | O(n) | O(1) | 1 |
| get_min_index | O(n) | O(1) | 1 |

### Optimizasyon

**Neden her seferinde yeniden hesaplanıyor?**

Çünkü:
1. Stack sürekli değişiyor (push, pop, rotate)
2. Min/max cache'lemek daha karmaşık olurdu
3. n küçük olduğu için O(n) kabul edilebilir

**Alternatif:** Min/max heap veri yapısı kullanılabilir ama:
- Push_swap için overkill
- Norm limitlerini aşar
- Gereksiz karmaşıklık

### Çağrı Sıklığı

```c
// sort_small içinde
while (size > 3)
{
    push_min_to_b(...);  // Her seferinde get_min_index çağrılır
    size--;
}
```

5 elemanlı stack için:
- 2 kere çağrılır
- Toplam: 2n işlem
- Hala O(n)

---

## Edge Cases (Uç Durumlar)

### 1. Boş Stack

```c
t_stack *stack = NULL;

get_min(stack);       // 0
get_max(stack);       // 0
get_min_index(stack); // 0
```

**Not:** Çağrıda stack NULL kontrolü yapılmalı!

### 2. Tüm Elemanlar Aynı

```c
// Stack: [5, 5, 5, 5]

get_min(stack);       // 5
get_max(stack);       // 5
get_min_index(stack); // 0 (ilk 5'in pozisyonu)
```

### 3. Sıralı Stack

```c
// Stack: [1, 2, 3, 4, 5]

get_min(stack);       // 1
get_max(stack);       // 5
get_min_index(stack); // 0 (en başta)
```

### 4. Ters Sıralı Stack

```c
// Stack: [5, 4, 3, 2, 1]

get_min(stack);       // 1
get_max(stack);       // 5
get_min_index(stack); // 4 (en sonda)
```

### 5. INT_MIN ve INT_MAX

```c
// Stack: [-2147483648, 0, 2147483647]

get_min(stack);       // -2147483648 (INT_MIN)
get_max(stack);       // 2147483647 (INT_MAX)
get_min_index(stack); // 0
```

---

## 🎯 Önemli Notlar

1. **NULL Kontrolü:** Her fonksiyon stack NULL ise 0 döner
2. **Tek Geçiş:** Her fonksiyon stack'i sadece 1 kere dolaşır
3. **Değişmez:** Stack'i değiştirmez, sadece okur
4. **Pozisyon:** get_min_index 0'dan başlar (top = 0)
5. **Rotate Optimizasyonu:** min_pos ile en kısa yol seçilir

---

## 🔧 Debug İpuçları

### Test Kodu:

```c
void	print_min_max(t_stack *stack)
{
	printf("Min: %d\n", get_min(stack));
	printf("Max: %d\n", get_max(stack));
	printf("Min Index: %d\n", get_min_index(stack));
	printf("Stack Size: %d\n", stack_size(stack));
}
```

### Manuel Test:

```c
// Stack: [7, 2, 9, 1, 5]

Expected:
  Min: 1
  Max: 9
  Min Index: 3
  Size: 5

Actual:
  get_min(stack) → 1 ✓
  get_max(stack) → 9 ✓
  get_min_index(stack) → 3 ✓
```

---

## 📚 Bağlantılı Dosyalar

- `sort_small.c` → get_min_index() kullanır
- `push_swap.c` → Dolaylı olarak kullanılır
- `stack_size.c` → Rotate kararında birlikte kullanılır

---

## 💡 İyileştirme Önerileri

### Mevcut Durum: ✅ Yeterli

```c
// Her çağrıda O(n)
get_min_index(stack);  // n işlem
```

### Alternatif 1: Cache (Uygun Değil)

```c
// Stack değiştikçe cache güncellenmeli
// Çok karmaşık, gereksiz
```

### Alternatif 2: Sorted Array (Uygun Değil)

```c
// Her işlemde O(log n) insert
// Stack yapısına uygun değil
```

**Sonuç:** Mevcut implementasyon push_swap için optimal! 🎯

---

**Hazırlayan:** boksuz  
**Tarih:** 14 Ekim 2025  
**Proje:** push_swap @ 42 Istanbul

