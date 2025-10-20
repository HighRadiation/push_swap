# 📄 Stack Utility Fonksiyonları Dokümantasyonu

**Dosyalar:** `src/utils/array/*.c`  
**Amaç:** Stack veri yapısı yönetimi için yardımcı fonksiyonlar.

---

## 📋 İçindekiler

1. [Genel Bakış](#genel-bakış)
2. [stack_new.c](#stack_newc)
3. [stack_add_back.c](#stack_add_backc)
4. [stack_add_front.c](#stack_add_frontc)
5. [stack_last.c](#stack_lastc)
6. [stack_size.c](#stack_sizec)
7. [free_stack.c](#free_stackc)

---

## Genel Bakış

Stack utility fonksiyonları, linked list tabanlı stack veri yapısını yönetir:

✅ Node oluşturma  
✅ Node ekleme (başa/sona)  
✅ Stack bilgisi (boyut, son eleman)  
✅ Memory yönetimi (free)

### Stack Yapısı:

```c
typedef struct s_stack
{
    int             value;   // Sayının değeri
    int             index;   // Normalize index (radix için)
    struct s_stack  *next;   // Sonraki node
}   t_stack;
```

### Linked List Görseli:

```
stack_a:  [3] → [2] → [1] → NULL
           ↑                 ↑
         head              last
```

---

## stack_new.c

### `t_stack *stack_new(int value)`

**Parametre:**
- `value` - Yeni node'un değeri

**Dönüş:** 
- Başarılı: Yeni node pointer'ı
- Hata: NULL

**Görev:** Yeni bir stack node'u oluşturur.

#### Kod:

```c
t_stack	*stack_new(int value)
{
	t_stack	*new;

	// Malloc ile yer ayır
	new = (t_stack *)malloc(sizeof(t_stack));
	if (!new)
		return (NULL);  // Malloc başarısız
	
	// Değerleri ata
	new->value = value;
	new->index = -1;     // Henüz atanmadı
	new->next = NULL;    // Son eleman
	
	return (new);
}
```

#### Özellikler:

- ✅ `malloc()` kullanır
- ✅ NULL kontrolü yapar
- ✅ Index başlangıçta -1
- ✅ next başlangıçta NULL

#### Kullanım:

```c
t_stack *node = stack_new(42);
if (!node)
{
    // Malloc hatası
    error_exit();
}

// node->value = 42
// node->index = -1
// node->next = NULL
```

#### Memory:

```
Malloc:
┌──────────┐
│ value: 42│
│ index: -1│
│ next: NULL│
└──────────┘
    ↑
  node
```

#### Hata Durumu:

```c
// Eğer malloc başarısız olursa
t_stack *node = stack_new(42);
if (!node)
{
    // node = NULL
    // İşleme devam edilmemeli!
    free_stack(&existing_stack);
    error_exit();
}
```

---

## stack_add_back.c

### `void stack_add_back(t_stack **stack, t_stack *new)`

**Parametre:**
- `stack` - Stack'in başı (pointer to pointer)
- `new` - Eklenecek node

**Dönüş:** void

**Görev:** Yeni node'u stack'in sonuna ekler.

#### Kod:

```c
void	stack_add_back(t_stack **stack, t_stack *new)
{
	t_stack	*last;

	// new NULL ise hiçbir şey yapma
	if (!new)
		return ;
	
	// Stack boşsa, new ilk eleman olur
	if (!*stack)
	{
		*stack = new;
		return ;
	}
	
	// Stack'in sonunu bul
	last = stack_last(*stack);
	
	// Son elemanın next'ine new'i ekle
	last->next = new;
}
```

#### Senaryolar:

**1. Boş Stack'e Ekleme:**
```
Before: stack = NULL

stack_add_back(&stack, node1)

After:  stack = [1] → NULL
```

**2. Dolu Stack'e Ekleme:**
```
Before: stack = [1] → [2] → NULL

stack_add_back(&stack, node3)

After:  stack = [1] → [2] → [3] → NULL
```

#### Kullanım (main.c'de):

```c
t_stack *stack_a = NULL;

// Argümanları sırayla ekle
stack_add_back(&stack_a, stack_new(3));  // [3]
stack_add_back(&stack_a, stack_new(2));  // [3]->[2]
stack_add_back(&stack_a, stack_new(1));  // [3]->[2]->[1]
```

#### Karmaşıklık:

- **Zaman:** O(n) - Son elemanı bulmak için
- **Alan:** O(1)

---

## stack_add_front.c

### `void stack_add_front(t_stack **stack, t_stack *new)`

**Parametre:**
- `stack` - Stack'in başı
- `new` - Eklenecek node

**Dönüş:** void

**Görev:** Yeni node'u stack'in başına ekler.

#### Kod:

```c
void	stack_add_front(t_stack **stack, t_stack *new)
{
	// new NULL ise hiçbir şey yapma
	if (!new)
		return ;
	
	// new'in next'ini mevcut stack'e bağla
	new->next = *stack;
	
	// Stack'in başını new yap
	*stack = new;
}
```

#### Görsel:

**Before:**
```
stack:  [1] → [2] → [3] → NULL
```

**İşlem:**
```c
t_stack *new_node = stack_new(0);
stack_add_front(&stack, new_node);
```

**After:**
```
stack:  [0] → [1] → [2] → [3] → NULL
         ↑
        new
```

#### Kullanım (push operasyonlarında):

```c
// pa fonksiyonu içinde
static void push(t_stack **dest, t_stack **src)
{
    t_stack *tmp = *src;
    *src = (*src)->next;
    
    // Destination'ın başına ekle
    stack_add_front(dest, tmp);  // ← BURADA KULLANILIR
}
```

#### Karmaşıklık:

- **Zaman:** O(1) - Çok hızlı!
- **Alan:** O(1)

#### add_back vs add_front:

| İşlem | add_back | add_front |
|-------|----------|-----------|
| Zaman | O(n) | O(1) |
| Kullanım | Stack oluşturma | Push operasyonları |
| Avantaj | Sıralı ekleme | Çok hızlı |

---

## stack_last.c

### `t_stack *stack_last(t_stack *stack)`

**Parametre:**
- `stack` - Stack

**Dönüş:** Stack'in son elemanı (veya NULL)

**Görev:** Stack'in son node'unu bulup döndürür.

#### Kod:

```c
t_stack	*stack_last(t_stack *stack)
{
	// Stack boşsa NULL döndür
	if (!stack)
		return (NULL);
	
	// Son elemanı bul
	while (stack->next)
		stack = stack->next;
	
	// Son eleman (next'i NULL olan)
	return (stack);
}
```

#### Örnek:

```c
// Stack: [1] → [2] → [3] → NULL

t_stack *last = stack_last(stack);

// last->value = 3
// last->next = NULL
```

#### Kullanım (rotate'de):

```c
// ra fonksiyonu içinde
static void rotate(t_stack **stack)
{
    t_stack *first = *stack;
    t_stack *last = stack_last(*stack);  // ← BURADA KULLANILIR
    
    *stack = first->next;
    first->next = NULL;
    last->next = first;  // İlk elemanı sona ekle
}
```

#### Karmaşıklık:

- **Zaman:** O(n)
- **Alan:** O(1)

---

## stack_size.c

### `int stack_size(t_stack *stack)`

**Parametre:**
- `stack` - Stack

**Dönüş:** Stack'teki eleman sayısı

**Görev:** Stack'i dolaşıp eleman sayısını sayar.

#### Kod:

```c
int	stack_size(t_stack *stack)
{
	int	size;

	size = 0;
	
	// Stack'i baştan sona dolaş
	while (stack)
	{
		size++;
		stack = stack->next;
	}
	
	return (size);
}
```

#### Örnekler:

```c
// Stack: [1] → [2] → [3] → NULL
stack_size(stack);  // 3

// Stack: [42] → NULL
stack_size(stack);  // 1

// Stack: NULL
stack_size(stack);  // 0
```

#### Kullanım:

```c
// push_swap.c içinde
void push_swap(t_stack **stack_a, t_stack **stack_b)
{
    int size = stack_size(*stack_a);  // ← BURADA
    
    if (size == 2)
        sa(stack_a);
    else if (size == 3)
        sort_three(stack_a);
    // ...
}
```

#### Karmaşıklık:

- **Zaman:** O(n)
- **Alan:** O(1)

---

## free_stack.c

### `void free_stack(t_stack **stack)`

**Parametre:**
- `stack` - Free edilecek stack (pointer to pointer)

**Dönüş:** void

**Görev:** Stack'teki tüm node'ları sırayla free eder.

#### Kod:

```c
void	free_stack(t_stack **stack)
{
	t_stack	*tmp;

	// Stack NULL veya boşsa hiçbir şey yapma
	if (!stack || !*stack)
		return ;
	
	// Her node'u sırayla free et
	while (*stack)
	{
		tmp = (*stack)->next;  // Sonraki'yi kaydet
		free(*stack);          // Mevcut'i free et
		*stack = tmp;          // Sonraki'ye geç
	}
	
	// Stack'i NULL yap
	*stack = NULL;
}
```

#### Algoritma:

```
While stack boş değilse:
    1. Sonraki node'u tmp'ye kaydet
    2. Mevcut node'u free et
    3. stack'i tmp yap (bir sonraki'ye geç)

Son: stack = NULL
```

#### Görsel:

**Before:**
```
stack:  [1] → [2] → [3] → NULL
```

**free_stack(&stack) çalışırken:**
```
Adım 1:
tmp = [2] → [3] → NULL
free([1])
stack = [2] → [3] → NULL

Adım 2:
tmp = [3] → NULL
free([2])
stack = [3] → NULL

Adım 3:
tmp = NULL
free([3])
stack = NULL
```

**After:**
```
stack: NULL
(Tüm node'lar free edildi)
```

#### Kullanım (main.c'de):

```c
int main(int argc, char **argv)
{
    t_stack *stack_a = create_stack(argc, argv);
    t_stack *stack_b = NULL;
    
    push_swap(&stack_a, &stack_b);
    
    // Temizlik!
    free_stack(&stack_a);  // ← BURADA
    free_stack(&stack_b);  // ← BURADA
    
    return (0);
}
```

#### Önemli Notlar:

1. **NULL Güvenli:**
```c
free_stack(NULL);       // Sorun yok
free_stack(&empty);     // empty=NULL, sorun yok
```

2. **Pointer to Pointer:**
```c
// ❌ YANLIŞ:
free_stack(stack_a);

// ✅ DOĞRU:
free_stack(&stack_a);
```

3. **Memory Leak Önleme:**
```c
// Her malloc için bir free!
t_stack *stack = create_stack(...);
// ... işlemler ...
free_stack(&stack);  // MUTLAKA!
```

#### Karmaşıklık:

- **Zaman:** O(n) - Tüm node'ları dolaşır
- **Alan:** O(1)

---

## 💡 Kullanım Örnekleri

### Örnek 1: Stack Oluşturma

```c
t_stack *stack = NULL;

// 3 eleman ekle
stack_add_back(&stack, stack_new(1));
stack_add_back(&stack, stack_new(2));
stack_add_back(&stack, stack_new(3));

// Stack: [1] → [2] → [3] → NULL

printf("Size: %d\n", stack_size(stack));  // 3

free_stack(&stack);  // Temizlik
```

### Örnek 2: Push İşlemi

```c
t_stack *stack_a = /* ... */;
t_stack *stack_b = NULL;

// A'nın en üstünü al
t_stack *tmp = stack_a;
stack_a = stack_a->next;

// B'nin başına ekle
stack_add_front(&stack_b, tmp);
```

### Örnek 3: Rotate İşlemi

```c
// Stack: [1] → [2] → [3] → NULL

t_stack *first = stack;
t_stack *last = stack_last(stack);

// İlk elemanı ayır
stack = first->next;

// İlk elemanı sona ekle
first->next = NULL;
last->next = first;

// Stack: [2] → [3] → [1] → NULL
```

---

## 🎯 Önemli Notlar

1. **stack_new()** malloc kullanır, NULL kontrolü şart
2. **add_front()** O(1), **add_back()** O(n)
3. **free_stack()** her zaman çağrılmalı (memory leak önleme)
4. **Pointer to pointer** kullanımına dikkat
5. **NULL kontrolü** her fonksiyonda yapılıyor

---

## 📊 Karmaşıklık Özeti

| Fonksiyon | Zaman | Alan | Kullanım |
|-----------|-------|------|----------|
| stack_new | O(1) | O(1) | Node oluştur |
| stack_add_back | O(n) | O(1) | Sona ekle |
| stack_add_front | O(1) | O(1) | Başa ekle |
| stack_last | O(n) | O(1) | Son eleman |
| stack_size | O(n) | O(1) | Boyut |
| free_stack | O(n) | O(1) | Temizlik |

---

## 🔧 Debug İpuçları

### Print Stack:

```c
void print_stack(t_stack *stack)
{
    printf("Stack: ");
    while (stack)
    {
        printf("[%d]", stack->value);
        if (stack->next)
            printf(" → ");
        stack = stack->next;
    }
    printf(" → NULL\n");
}
```

### Memory Leak Kontrolü:

```bash
# Valgrind ile test
valgrind --leak-check=full ./push_swap 3 2 1

# Beklenen:
# "All heap blocks were freed -- no leaks are possible"
```

---

## 📚 Bağlantılı Dosyalar

- `main.c` → stack_new(), stack_add_back(), free_stack()
- `stack_ops/` → stack_add_front(), stack_last()
- `push_swap.c` → stack_size()

---

**Hazırlayan:** boksuz  
**Tarih:** 14 Ekim 2025  
**Proje:** push_swap @ 42 Istanbul

