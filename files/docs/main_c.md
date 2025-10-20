# 📄 main.c Dokümantasyonu

**Dosya:** `src/main.c`  
**Amaç:** Programın giriş noktası. Argümanları parse eder, stack oluşturur ve push_swap'i çağırır.

---

## 📋 İçindekiler

1. [Genel Bakış](#genel-bakış)
2. [Fonksiyonlar](#fonksiyonlar)
3. [Akış Diyagramı](#akış-diyagramı)
4. [Hata Yönetimi](#hata-yönetimi)
5. [Örnekler](#örnekler)

---

## Genel Bakış

`main.c` dosyası projenin başlangıç noktasıdır. Şu görevleri yerine getirir:

1. ✅ Komut satırı argümanlarını kontrol eder
2. ✅ Argümanların geçerliliğini doğrular
3. ✅ Stack A'yı oluşturur
4. ✅ Duplicate kontrolü yapar
5. ✅ push_swap fonksiyonunu çağırır
6. ✅ Memory'i temizler

---

## Fonksiyonlar

### 🔹 `static t_stack *create_stack(int argc, char **argv)`

**Parametre:**
- `argc` - Argüman sayısı (program adı dahil)
- `argv` - Komut satırı argümanları dizisi

**Dönüş:** 
- Başarılıysa: Oluşturulan stack'in başını gösteren pointer
- Hata varsa: error_exit() çağrılır, program sonlanır

#### Görev:

Stack A'yı oluşturur ve argümanları sırayla ekler.

#### Adım Adım İşleyiş:

```c
1. stack_a = NULL ile başla
2. i = 1'den başla (argv[0] program adıdır)
3. Her argüman için:
   a. ft_atoi() ile string'i int'e çevir
   b. stack_new() ile yeni node oluştur
   c. Eğer malloc başarısız:
      - Mevcut stack'i temizle (free_stack)
      - error_exit() çağır
   d. stack_add_back() ile stack'e ekle
4. Oluşturulan stack'i döndür
```

#### Kod Analizi:

```c
static t_stack	*create_stack(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*new_node;
	int		i;
	int		value;

	stack_a = NULL;      // Boş stack ile başla
	i = 1;               // argv[0] program adı, 1'den başla
	while (i < argc)
	{
		value = ft_atoi(argv[i]);           // String → Int
		new_node = stack_new(value);        // Yeni node oluştur
		if (!new_node)                      // Malloc başarısız?
		{
			free_stack(&stack_a);           // Memory temizle
			error_exit();                   // Hata ver
		}
		stack_add_back(&stack_a, new_node); // Stack'e ekle
		i++;
	}
	return (stack_a);    // Oluşturulan stack'i döndür
}
```

#### Örnek Kullanım:

```bash
./push_swap 3 2 1
```

**İşlem:**
1. argc = 4, argv = ["./push_swap", "3", "2", "1"]
2. i=1: "3" → 3 → stack: [3]
3. i=2: "2" → 2 → stack: [3, 2]
4. i=3: "1" → 1 → stack: [3, 2, 1]
5. Return stack

**Görsel:**
```
argv[1]="3"  →  [3]
argv[2]="2"  →  [3] → [2]
argv[3]="1"  →  [3] → [2] → [1]
```

#### Hata Senaryoları:

**1. Malloc Hatası:**
```c
// Eğer new_node NULL dönerse:
free_stack(&stack_a);  // Önceki node'ları temizle
error_exit();          // "Error\n" + exit(1)
```

**2. ft_atoi Hatası:**
```c
// ft_atoi içinde INT overflow kontrolü var
"2147483648" → INT_MAX aşımı → error_exit()
```

---

### 🔹 `int main(int argc, char **argv)`

**Parametre:**
- `argc` - Argüman sayısı
- `argv` - Komut satırı argümanları

**Dönüş:** 
- 0: Başarılı
- 1: Hata (error_exit ile)

#### Görev:

Programın ana akışını yönetir.

#### Adım Adım İşleyiş:

```
1. Argüman sayısı kontrolü
   → argc < 2 ise: Hiçbir şey yapmadan çık (return 0)

2. Argüman validasyonu
   → check_args(argv) çağır
   → Geçersizse: error_exit()

3. Stack oluşturma
   → create_stack() çağır
   → NULL dönerse: error_exit()

4. Duplicate kontrolü
   → has_duplicates() çağır
   → Varsa: stack'i free et + error_exit()

5. Stack B'yi initialize et
   → stack_b = NULL

6. Sıralama işlemi
   → push_swap(&stack_a, &stack_b) çağır

7. Temizlik
   → free_stack(&stack_a)
   → free_stack(&stack_b)

8. Başarılı çıkış
   → return 0
```

#### Kod Analizi:

```c
int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	// 1. Argüman kontrolü
	if (argc < 2)
		return (0);  // Hiçbir şey yapmadan çık

	// 2. Argüman validasyonu
	if (!check_args(argv))
		error_exit();  // "Error\n" + exit(1)

	// 3. Stack oluşturma
	stack_a = create_stack(argc, argv);
	if (!stack_a)
		error_exit();

	// 4. Duplicate kontrolü
	if (has_duplicates(stack_a))
	{
		free_stack(&stack_a);  // Memory leak önleme
		error_exit();
	}

	// 5. Stack B initialize
	stack_b = NULL;

	// 6. Sıralama
	push_swap(&stack_a, &stack_b);

	// 7. Temizlik
	free_stack(&stack_a);
	free_stack(&stack_b);

	return (0);  // Başarılı çıkış
}
```

---

## Akış Diyagramı

```
START
  ↓
argc < 2? ──YES──> return 0
  ↓ NO
check_args() ──FAIL──> error_exit()
  ↓ PASS
create_stack() ──NULL──> error_exit()
  ↓ SUCCESS
has_duplicates() ──YES──> free_stack() → error_exit()
  ↓ NO
stack_b = NULL
  ↓
push_swap(&stack_a, &stack_b)
  ↓
free_stack(&stack_a)
free_stack(&stack_b)
  ↓
return 0
  ↓
END
```

---

## Hata Yönetimi

### ✅ Memory Leak Önleme

**Önemli:** Her hata durumunda mutlaka `free_stack()` çağrılır!

```c
// ❌ YANLIŞ:
if (has_duplicates(stack_a))
    error_exit();  // stack_a leak eder!

// ✅ DOĞRU:
if (has_duplicates(stack_a))
{
    free_stack(&stack_a);  // Önce temizle
    error_exit();           // Sonra çık
}
```

### 🔴 Hata Tipleri ve Çıktıları

| Durum | Kontrol | Çıktı |
|-------|---------|-------|
| Argüman yok | `argc < 2` | (Hiçbir şey) |
| Geçersiz karakter | `check_args()` | "Error\n" |
| INT overflow | `ft_atoi()` | "Error\n" |
| Duplicate sayı | `has_duplicates()` | "Error\n" |
| Malloc hatası | `stack_new()` | "Error\n" |

### 📝 error_exit() Fonksiyonu

```c
void error_exit(void)
{
    write(2, "Error\n", 6);  // stderr'e yaz
    exit(1);                 // Programı sonlandır
}
```

**Özellikler:**
- ✅ stderr (fd=2) kullanır
- ✅ Tam olarak "Error\n" yazar
- ✅ exit(1) ile sonlanır

---

## Örnekler

### 📌 Örnek 1: Normal Kullanım

```bash
./push_swap 3 2 1
```

**Akış:**
1. argc = 4 ✓
2. check_args(["./push_swap", "3", "2", "1"]) → 1 ✓
3. create_stack() → [3, 2, 1] ✓
4. has_duplicates([3, 2, 1]) → 0 ✓
5. push_swap() → Sıralama işlemleri
6. free_stack() → Memory temiz
7. return 0 ✓

**Çıktı:**
```
sa
rra
```

---

### 📌 Örnek 2: Argüman Yok

```bash
./push_swap
```

**Akış:**
1. argc = 1 → argc < 2 ✓
2. return 0
3. Hiçbir şey yazdırılmaz

**Çıktı:** (boş)

---

### 📌 Örnek 3: Geçersiz Argüman

```bash
./push_swap 1 abc 3
```

**Akış:**
1. argc = 4 ✓
2. check_args() kontrolü:
   - "1" → geçerli ✓
   - "abc" → geçersiz ✗
   - return 0
3. error_exit() çağrılır

**Çıktı:**
```
Error
```
(stderr'e yazılır)

---

### 📌 Örnek 4: Duplicate Sayı

```bash
./push_swap 1 2 3 2 5
```

**Akış:**
1. argc = 6 ✓
2. check_args() → 1 ✓
3. create_stack() → [1, 2, 3, 2, 5] ✓
4. has_duplicates() kontrolü:
   - 2 iki kere var ✗
   - return 1
5. free_stack([1, 2, 3, 2, 5])
6. error_exit()

**Çıktı:**
```
Error
```

---

### 📌 Örnek 5: INT Overflow

```bash
./push_swap 2147483648
```

**Akış:**
1. argc = 2 ✓
2. check_args(["./push_swap", "2147483648"]) → 1 ✓
3. create_stack() çağrılır:
   - ft_atoi("2147483648") çalışır
   - INT_MAX (2147483647) aşıldı ✗
   - error_exit() çağrılır

**Çıktı:**
```
Error
```

---

### 📌 Örnek 6: Negatif Sayılar

```bash
./push_swap -5 -2 -10 3
```

**Akış:**
1. argc = 5 ✓
2. check_args() → 1 ✓ (negatif geçerli)
3. create_stack() → [-5, -2, -10, 3] ✓
4. has_duplicates() → 0 ✓
5. push_swap() → Sıralama
6. return 0 ✓

**Çıktı:**
```
sa
pb
pb
...
```

---

### 📌 Örnek 7: Zaten Sıralı

```bash
./push_swap 1 2 3 4 5
```

**Akış:**
1. argc = 6 ✓
2. check_args() → 1 ✓
3. create_stack() → [1, 2, 3, 4, 5] ✓
4. has_duplicates() → 0 ✓
5. push_swap() çağrılır:
   - is_sorted([1,2,3,4,5]) → 1 ✓
   - Hiçbir işlem yapılmaz
6. return 0 ✓

**Çıktı:** (boş - zaten sıralı)

---

## 💡 İpuçları

### Memory Yönetimi
```c
// Her zaman free_stack kullan
free_stack(&stack_a);
free_stack(&stack_b);

// stack_b boş olsa bile güvenle çağrılabilir
// Fonksiyon içinde NULL kontrolü var
```

### Hata Kontrolü
```c
// Argüman validasyonu önemli
if (!check_args(argv))
    error_exit();

// Duplicate kontrolünden önce free unutma
if (has_duplicates(stack_a))
{
    free_stack(&stack_a);  // MUTLAKA!
    error_exit();
}
```

### Test Senaryoları
```bash
# Temel testler
./push_swap                    # Hiçbir şey
./push_swap 42                 # Tek eleman
./push_swap 1 2 3              # Zaten sıralı
./push_swap 3 2 1              # Ters sıralı

# Hata testleri
./push_swap abc                # Geçersiz
./push_swap 1 1                # Duplicate
./push_swap 2147483648         # Overflow
./push_swap -2147483649        # Underflow
./push_swap ""                 # Boş string
```

---

## 🎯 Önemli Notlar

1. **argc < 2:** Hiçbir çıktı vermeden sonlanır (hata değil)
2. **error_exit:** Her zaman stderr'e yazar
3. **Memory Leak:** Valgrind ile test edilmeli
4. **NULL Kontrolü:** create_stack NULL dönebilir
5. **free_stack:** NULL pointer için güvenli

---

## 📚 Bağlantılı Dosyalar

- `validation.c` → check_args(), ft_atoi(), error_exit()
- `stack_new.c` → stack_new()
- `stack_add_back.c` → stack_add_back()
- `free_stack.c` → free_stack()
- `push_swap.c` → push_swap()

---

**Hazırlayan:** boksuz  
**Tarih:** 14 Ekim 2025  
**Proje:** push_swap @ 42 Istanbul

