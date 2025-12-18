# Libft

Libft, C dilinde temel string ve bellek (memory) işlemleri ile çeşitli yardımcı fonksiyonların yeniden implemente edildiği bir kütüphanedir. Bu proje, 42 okulu müfredatına uygundur ve standart C fonksiyonlarının bazılarını kendi başına sıfırdan yazmanı sağlar.

## İçerik

### Karakter Kontrol Fonksiyonları

- `ft_isalpha`   : Karakterin alfabetik olup olmadığını kontrol eder.
- `ft_isdigit`   : Karakterin rakam olup olmadığını kontrol eder.
- `ft_isalnum`   : Karakterin alfabetik veya rakam olup olmadığını kontrol eder.
- `ft_isascii`   : Karakterin ASCII aralığında olup olmadığını kontrol eder.
- `ft_isprint`   : Karakterin yazdırılabilir olup olmadığını kontrol eder.
- `ft_toupper`   : Küçük harfi büyüğe çevirir.
- `ft_tolower`   : Büyük harfi küçüğe çevirir.

### String ve Bellek Fonksiyonları

- `ft_strlen`    : String uzunluğunu döner.
- `ft_memset`    : Belleği belirtilen değerle doldurur.
- `ft_bzero`     : Belleği sıfırlar.
- `ft_memcpy`    : Belleği kopyalar (overlap yoksa).
- `ft_memmove`   : Belleği güvenli şekilde kopyalar (overlap destekler).
- `ft_strlcpy`   : Stringi güvenli şekilde kopyalar (buffer taşmasını önler).
- `ft_strlcat`   : Stringleri güvenli şekilde birleştirir (buffer taşmasını önler).
- `ft_strdup`    : Stringin bir kopyasını oluşturur.
- `ft_calloc`    : Bellek ayırır ve sıfırlar.

### Arama ve Karşılaştırma Fonksiyonları

- `ft_strchr`    : String içinde karakter arar (ilk geçtiği yer).
- `ft_strrchr`   : String içinde karakter arar (son geçtiği yer).
- `ft_strncmp`   : İki stringi belirli uzunlukta karşılaştırır.
- `ft_memchr`    : Bellekte karakter arar.
- `ft_memcmp`    : Bellek bloklarını karşılaştırır.
- `ft_strnstr`   : String içinde substring arar.

### Diğer Fonksiyonlar

- `ft_atoi`      : Stringi tam sayıya çevirir.
- `ft_substr`    : Stringin belirli bir indeksinden itibaren alt string oluşturur.
- `ft_strjoin`   : İki stringi birleştirir.
- `ft_strtrim`   : Stringin başından ve sonundan belirli karakterleri kırpar.
- `ft_split`     : Stringi verilen ayırıcıya göre böler.
- `ft_itoa`      : Tam sayıyı stringe çevirir.
- `ft_strmapi`   : Her karaktere fonksiyon uygulayarak yeni string oluşturur.
- `ft_striteri`  : Her karakter üzerinde fonksiyon uygular (in-place).
- `ft_putchar_fd`: Karakteri belirtilen dosya tanımlayıcısına yazar.
- `ft_putstr_fd` : Stringi belirtilen dosya tanımlayıcısına yazar.
- `ft_putendl_fd`: Stringi yazıp sonuna yeni satır ekler.
- `ft_putnbr_fd` : Tam sayıyı belirtilen dosya tanımlayıcısına yazar.

### ft_printf

Bu kütüphane, standart `printf` fonksiyonunun özel bir implementasyonunu da içerir:

- `ft_printf`    : Format destekli çıktı fonksiyonu
  - **Desteklenen format belirteçleri:**
    - `%c` : Tek karakter yazdırır
    - `%s` : String yazdırır
    - `%p` : Pointer adresini hexadecimal formatta yazdırır
    - `%d` / `%i` : Signed decimal integer yazdırır
    - `%u` : Unsigned decimal integer yazdırır
    - `%x` : Hexadecimal (küçük harf) yazdırır
    - `%X` : Hexadecimal (büyük harf) yazdırır
    - `%%` : Literal '%' karakteri yazdırır

**Kullanım örneği:**
```c
ft_printf("Hello %s! Number: %d, Hex: %x\n", "World", 42, 255);
// Çıktı: Hello World! Number: 42, Hex: ff
```

## Makefile Nedir?

**Makefile**, projedeki kaynak dosyaların nasıl derleneceğini ve birleştirileceğini tanımlayan bir yapılandırma dosyasıdır; `make` komutuyla otomatik derleme sürecini yönetir.

### Makefile Hedefleri

```bash
make        # Kütüphaneyi derle (libft.a oluşturur)
make clean  # Object dosyalarını (.o) temizle
make fclean # Tüm derleme çıktılarını temizle (libft.a dahil)
make re     # Temizle ve yeniden derle (fclean + all)
```

## Proje Detayları

- **Kullanılan Dosyalar:** `Makefile`, `libft.h`, `ft_*.c`
- Tüm dosyalar proje ana klasöründe yer almalı.
- Kod, Norm kurallarına uygun olmalıdır. (Norm hatası = 0 puan)
- Global değişken kullanımı yasak. Yardımcı fonksiyonlar `static` olmalıdır.
- Derleme flag'leri: `-Wall -Wextra -Werror`
- Kütüphane, ar arşivi (`libft.a`) olarak oluşturulmalı.
- Makefile `wildcard` kullanır (yeni dosyalar otomatik algılanır).
- Libtool kullanımı yasak.
- `malloc` ile ayrılan bellek mutlaka `free` edilmelidir.
- Segfault, double free veya crash kabul edilmez.
- `libft.a` proje kökünde olmalıdır.
- Sadece git’e gönderilen dosyalar değerlendirilir.

### Sistem ve Test Notları

- Bazı fonksiyonlar (`strlcpy`, `strlcat`, `bzero`) GNU C Kütüphanesinde (glibc) standart değildir.
- Linux/glibc ortamında test için `<bsd/string.h>` dahil edilip, `-lbsd` ile derleme gerekebilir.

## Lisans

Bu proje 42 okulu eğitim amaçlıdır ve açık kaynak lisansı ile dağıtılabilir. Kendi geliştirmelerinizi yaparken kaynak göstermeniz önerilir.

---

42 Network — libft  
Hazırlayan: [HighRadiation](https://github.com/HighRadiation)
