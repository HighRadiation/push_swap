# 📄 validation.c Dokümantasyonu

**Dosya:** `src/utils/validation.c`  
**Amaç:** Input validasyonu, parsing ve hata yönetimi fonksiyonları.

---

## 📋 İçindekiler

1. [Genel Bakış](#genel-bakış)
2. [Fonksiyonlar](#fonksiyonlar)
3. [Kullanım Örnekleri](#kullanım-örnekleri)
4. [Hata Senaryoları](#hata-senaryoları)

---

## Genel Bakış

`validation.c` dosyası projenin input kontrolü ve validasyon işlemlerini yönetir:

✅ String → Integer dönüşümü  
✅ Argüman validasyonu  
✅ Duplicate (tekrar) kontrolü  
✅ Index atama (radix sort için)  
✅ Hata yönetimi

---

## Fonksiyonlar

### 🔹 `void ft_putstr(char *str)`

**Parametre:**
- `str` - Yazdırılacak string

**Dönüş:** void (hiçbir şey döndürmez)

**Görev:** String'i stdout'a yazar.

#### Kod:

```c
void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);  // Her karakteri tek tek yaz
		i++;
	}
}
```

#### Özellikler:

- ✅ `write()` fonksiyonu kullanır
- ✅ NULL terminator'a kadar yazar
- ✅ Newline eklemez
- ✅ stdout'a (fd=1) yazar

#### Kullanım:

```c
ft_putstr("Hello");      // "Hello" yazdırır
ft_putstr("World\n");    // "World\n" yazdırır
```

---

### 🔹 `void error_exit(void)`

**Parametre:** Yok

**Dönüş:** void (program sonlanır)

**Görev:** Hata mesajı yazdırıp programı sonlandırır.

#### Kod:

```c
void	error_exit(void)
{
	write(2, "Error\n", 6);  // stderr'e yaz
	exit(1);                 // exit code 1 ile çık
}
```

#### Özellikler:

- ✅ stderr'e (fd=2) yazar
- ✅ Tam olarak "Error\n" çıktısı
- ✅ exit(1) ile sonlanır
- ✅ Tüm hata durumlarında çağrılır

#### Ne Zaman Çağrılır:

```c
// Geçersiz argüman
if (!check_args(argv))
    error_exit();

// INT overflow
if (result > INT_MAX || result < INT_MIN)
    error_exit();

// Duplicate sayı
if (has_duplicates(stack))
    error_exit();

// Malloc hatası
if (!new_node)
    error_exit();
```

---

### 🔹 `static int ft_isspace(char c)`

**Parametre:**
- `c` - Kontrol edilecek karakter

**Dönüş:** 
- 1: Whitespace karakteri
- 0: Whitespace değil

**Görev:** Karakterin boşluk karakteri olup olmadığını kontrol eder.

#### Kod:

```c
static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}
```

#### Kontrol Edilen Karakterler:

| Karakter | ASCII | Açıklama |
|----------|-------|----------|
| ` ` (space) | 32 | Boşluk |
| `\t` | 9 | Tab |
| `\n` | 10 | Newline |
| `\v` | 11 | Vertical tab |
| `\f` | 12 | Form feed |
| `\r` | 13 | Carriage return |

#### Kullanım:

```c
ft_isspace(' ')   → 1
ft_isspace('\t')  → 1
ft_isspace('a')   → 0
ft_isspace('1')   → 0
```

---

### 🔹 `static int ft_isdigit(char c)`

**Parametre:**
- `c` - Kontrol edilecek karakter

**Dönüş:**
- 1: Rakam
- 0: Rakam değil

**Görev:** Karakterin rakam olup olmadığını kontrol eder.

#### Kod:

```c
static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}
```

#### Kullanım:

```c
ft_isdigit('0')  → 1
ft_isdigit('5')  → 1
ft_isdigit('9')  → 1
ft_isdigit('a')  → 0
ft_isdigit('-')  → 0
```

---

### 🔹 `int ft_atoi(const char *str)`

**Parametre:**
- `str` - Çevrilecek string

**Dönüş:** Integer değer

**Görev:** String'i integer'a çevirir, overflow kontrolü yapar.

#### Kod Analizi:

```c
int	ft_atoi(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;

	// 1. Baştaki boşlukları atla
	while (ft_isspace(str[i]))
		i++;

	// 2. İşaret kontrolü
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}

	// 3. Rakamları oku
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		
		// 4. Overflow kontrolü
		if (result * sign > INT_MAX || result * sign < INT_MIN)
			error_exit();
		
		i++;
	}

	return ((int)(result * sign));
}
```

#### Adım Adım İşleyiş:

**Örnek 1:** `"  -123"`
```
1. Boşlukları atla:     "  -123"
                          ↑
2. İşaret oku:          "-123"
                         ↑
   sign = -1
   
3. Rakam oku:           "123"
                        ↑
   result = 0
   result = 0 * 10 + 1 = 1
   result = 1 * 10 + 2 = 12
   result = 12 * 10 + 3 = 123
   
4. İşaret uygula:       123 * -1 = -123

Sonuç: -123
```

**Örnek 2:** `"2147483648"` (INT_MAX + 1)
```
1. İşaret yok, sign = 1
2. Rakamları oku:
   result = 2147483648
   
3. Overflow kontrolü:
   2147483648 > INT_MAX (2147483647)
   → error_exit() çağrılır
   → "Error\n" + exit(1)
```

#### Overflow/Underflow Koruması:

```c
INT_MAX =  2147483647
INT_MIN = -2147483648

// Overflow testi
"2147483648"  → error_exit()
"3000000000"  → error_exit()

// Underflow testi
"-2147483649" → error_exit()
"-3000000000" → error_exit()

// Geçerli
"2147483647"  → 2147483647 ✓
"-2147483648" → -2147483648 ✓
```

#### Neden `long` Kullanılır:

```c
long result;  // Overflow tespit etmek için
```

`int` yerine `long` kullanılır çünkü:
- INT_MAX aşımını tespit edebilmek için
- Hesaplama sırasında overflow olmaması için
- Son aşamada `(int)` cast yapılır

---

### 🔹 `int check_args(char **argv)`

**Parametre:**
- `argv` - Komut satırı argümanları

**Dönüş:**
- 1: Tüm argümanlar geçerli
- 0: En az bir argüman geçersiz

**Görev:** Tüm argümanların sayı olup olmadığını kontrol eder.

#### Kod Analizi:

```c
int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 1;  // argv[0] program adı, 1'den başla
	while (argv[i])
	{
		j = 0;
		
		// İşaret varsa atla
		if (argv[i][j] == '-' || argv[i][j] == '+')
			j++;
		
		// İşaretten sonra rakam yoksa geçersiz
		if (!argv[i][j])
			return (0);
		
		// Tüm karakterlerin rakam olduğunu kontrol et
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
		
		i++;
	}
	
	return (1);  // Hepsi geçerli
}
```

#### Test Senaryoları:

**✅ Geçerli Argümanlar:**
```c
"123"     → 1 (geçerli)
"-456"    → 1 (geçerli)
"+789"    → 1 (geçerli)
"0"       → 1 (geçerli)
"-2147483648" → 1 (geçerli)
```

**❌ Geçersiz Argümanlar:**
```c
"abc"     → 0 (harf var)
"12a34"   → 0 (ortada harf)
"12 34"   → 0 (boşluk var)
"+"       → 0 (sadece işaret)
"-"       → 0 (sadece işaret)
""        → 0 (boş string)
"--5"     → 0 (çift işaret)
"5-"      → 0 (sonra işaret)
```

#### Örnek Kullanım:

```c
char *args[] = {"./push_swap", "1", "2", "3", NULL};

if (check_args(args))
    printf("Geçerli!\n");  // Bu çalışır
else
    error_exit();
```

---

### 🔹 `int has_duplicates(t_stack *stack)`

**Parametre:**
- `stack` - Kontrol edilecek stack

**Dönüş:**
- 1: Duplicate var
- 0: Duplicate yok

**Görev:** Stack'te tekrar eden sayı olup olmadığını kontrol eder.

#### Kod Analizi:

```c
int	has_duplicates(t_stack *stack)
{
	t_stack	*tmp;
	t_stack	*current;

	current = stack;
	
	// Her eleman için
	while (current)
	{
		tmp = current->next;  // Sonraki elemanlarla karşılaştır
		
		// Kendinden sonraki tüm elemanları kontrol et
		while (tmp)
		{
			// Aynı değer bulundu!
			if (current->value == tmp->value)
				return (1);
			
			tmp = tmp->next;
		}
		
		current = current->next;
	}
	
	return (0);  // Duplicate yok
}
```

#### Algoritma:

**Nested Loop (İç İçe Döngü):**
```
For her eleman:
    Kendinden sonraki tüm elemanlarla karşılaştır
    Eğer aynı değer varsa → return 1
    
Hiç eşleşme yoksa → return 0
```

#### Görsel Örnek:

**Stack: [3, 1, 4, 1, 5]**

```
Adım 1: current=3
  Compare: 3 vs 1 → ✗
  Compare: 3 vs 4 → ✗
  Compare: 3 vs 1 → ✗
  Compare: 3 vs 5 → ✗

Adım 2: current=1
  Compare: 1 vs 4 → ✗
  Compare: 1 vs 1 → ✓ BULUNDU!
  return 1
```

**Stack: [1, 2, 3, 4, 5]**

```
Tüm karşılaştırmalar yapılır
Hiç eşleşme yok
return 0
```

#### Karmaşıklık:

- **Zaman:** O(n²)
- **Alan:** O(1)

n² yavaş gibi görünse de:
- Input küçük (max ~500)
- Tek sefer çağrılır
- Sorun olmaz

---

### 🔹 `void index_stack(t_stack **stack)`

**Parametre:**
- `stack` - Indexlenecek stack (pointer to pointer)

**Dönüş:** void

**Görev:** Her elemanın index değerini belirler (0'dan n-1'e kadar).

#### Index Nedir?

Sayıları normalize eder:
- **En küçük sayı** → index 0
- **İkinci küçük** → index 1
- **En büyük sayı** → index (n-1)

#### Neden Gerekli?

**Radix sort** algoritması index'ler üzerinde çalışır.

#### Kod Analizi:

```c
void	index_stack(t_stack **stack)
{
	t_stack	*current;
	t_stack	*compare;
	int		index;

	current = *stack;
	
	// Her eleman için
	while (current)
	{
		index = 0;
		compare = *stack;
		
		// Kendinden küçük kaç eleman var?
		while (compare)
		{
			if (current->value > compare->value)
				index++;  // Kendinden küçük bulundu
			
			compare = compare->next;
		}
		
		current->index = index;  // Index'i ata
		current = current->next;
	}
}
```

#### Algoritma Mantığı:

```
Her eleman için:
    counter = 0
    Tüm stack'i dolaş:
        Eğer kendinden küçük eleman varsa:
            counter++
    
    Bu elemanın index'i = counter
```

#### Detaylı Örnek:

**Stack values: [5, 2, 8, 1]**

```
Eleman: 5
  5 > 2 → index++  (index=1)
  5 > 1 → index++  (index=2)
  Sonuç: index=2

Eleman: 2
  2 > 1 → index++  (index=1)
  Sonuç: index=1

Eleman: 8
  8 > 5 → index++  (index=1)
  8 > 2 → index++  (index=2)
  8 > 1 → index++  (index=3)
  Sonuç: index=3

Eleman: 1
  Hiçbirinden küçük değil
  Sonuç: index=0
```

**Sonuç:**
```
Values:  [5,  2,  8,  1]
Indices: [2,  1,  3,  0]
```

#### Sıralama Karşılaştırması:

| Değer | Sıralı Pozisyon | Index |
|-------|-----------------|-------|
| 1 | 1. (en küçük) | 0 |
| 2 | 2. | 1 |
| 5 | 3. | 2 |
| 8 | 4. (en büyük) | 3 |

#### Negatif Sayılar:

**Values: [-5, 3, -2, 0]**

```
-5: En küçük        → index=0
-2: 2. küçük        → index=1
 0: 3. küçük        → index=2
 3: En büyük        → index=3

Result:
Values:  [-5,  3, -2,  0]
Indices: [ 0,  3,  1,  2]
```

#### Karmaşıklık:

- **Zaman:** O(n²)
- **Alan:** O(1)

#### Kullanım:

```c
// main.c içinde
if (size > 5)
{
    index_stack(&stack_a);  // Önce index'le
    sort_large(&stack_a, &stack_b);  // Sonra radix sort
}
```

---

## Kullanım Örnekleri

### Örnek 1: Normal Validasyon

```c
char *argv[] = {"./push_swap", "3", "2", "1", NULL};

// 1. Argüman kontrolü
if (!check_args(argv))
    error_exit();  // Geçmez

// 2. Stack oluştur
t_stack *stack = create_stack(4, argv);

// 3. Duplicate kontrolü
if (has_duplicates(stack))
{
    free_stack(&stack);
    error_exit();  // Geçmez
}

// 4. Index atama
index_stack(&stack);

// Stack:
// Value:  3 → 2 → 1
// Index:  2 → 1 → 0
```

### Örnek 2: Geçersiz Input

```c
char *argv[] = {"./push_swap", "1", "abc", "3", NULL};

if (!check_args(argv))
    error_exit();  // ÇALIŞIR - "abc" geçersiz
```

### Örnek 3: Duplicate

```c
char *argv[] = {"./push_swap", "1", "2", "1", NULL};

if (!check_args(argv))
    error_exit();  // Geçer (sayılar geçerli)

t_stack *stack = create_stack(4, argv);

if (has_duplicates(stack))
{
    free_stack(&stack);
    error_exit();  // ÇALIŞIR - 1 iki kere
}
```

### Örnek 4: Overflow

```c
char *argv[] = {"./push_swap", "2147483648", NULL};

if (!check_args(argv))
    error_exit();  // Geçer (rakamlar geçerli)

// Ama create_stack içinde:
ft_atoi("2147483648");  // error_exit() çağrılır
```

---

## Hata Senaryoları

### 1. Geçersiz Karakterler

```bash
./push_swap 1 2a 3
```
→ check_args() 0 döner → error_exit()

### 2. Boş String

```bash
./push_swap ""
```
→ check_args() 0 döner → error_exit()

### 3. Sadece İşaret

```bash
./push_swap + - 1
```
→ check_args() 0 döner → error_exit()

### 4. INT Overflow

```bash
./push_swap 2147483648
```
→ ft_atoi() içinde error_exit()

### 5. Duplicate

```bash
./push_swap 1 2 3 2 5
```
→ has_duplicates() 1 döner → error_exit()

---

## 🎯 Önemli Notlar

1. **error_exit()** her zaman stderr'e yazar
2. **ft_atoi()** overflow kontrolü yapar
3. **check_args()** sadece format kontrolü yapar (INT_MAX kontrol etmez)
4. **has_duplicates()** O(n²) ama yeterince hızlı
5. **index_stack()** radix sort için şart

---

## 📚 Bağlantılı Dosyalar

- `main.c` → check_args(), has_duplicates() kullanır
- `push_swap.c` → index_stack() kullanır
- `sort_large.c` → index değerlerini kullanır

---

**Hazırlayan:** boksuz  
**Tarih:** 14 Ekim 2025  
**Proje:** push_swap @ 42 Istanbul

