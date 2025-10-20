---

## 🧩 **Bölüm I – Önsöz (Foreword)**

Bu bölümde, farklı programlama dillerinde klasik *“Hello, World!”* örnekleri verilmiş.

Amaç, programlamanın temellerini hatırlatmak ve dillerin çeşitliliğini göstermek.

---

### **C dili**

```c
#include <stdio.h>

int main(void)
{
    printf("hello, world\n");
    return 0;
}

```

### **ASM (Assembly)**

```nasm
cseg segment
assume cs:cseg, ds:cseg
org 100h
main proc
jmp debut
mess db 'Hello world!$'
debut:
mov dx, offset mess
mov ah, 9
int 21h
ret
main endp
cseg ends
end main

```

### **LOLCODE**

```
HAI
CAN HAS STDIO?
VISIBLE "HELLO WORLD!"
KTHXBYE

```

### **PHP**

```php
<?php
echo "Hello world!";
?>

```

### **BrainFuck**

```
++++++++++[>+++++++>++++++++++>+++>+<<<<-]
>++.>+.+++++++..+++.>++.
<<+++++++++++++++.>.+++.------.--------.>+.>.

```

### **C#**

```csharp
using System;

public class HelloWorld {
    public static void Main () {
        Console.WriteLine("Hello world!");
    }
}

```

### **HTML5**

```html
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Hello world !</title>
</head>
<body>
<p>Hello World !</p>
</body>
</html>

```

### **YASL**

```
"Hello world!"
print

```

### **OCaml**

```ocaml
let main () =
    print_endline "Hello world !"
let _ = main ()

```

---

Bu bölüm, Push_Swap projesinin teknik başlamadan önce, “kod yazmanın evrenselliğini” ve “her dilde aynı hedefe ulaşılabileceğini” göstermek amacıyla eklenmiş mizahi bir giriş niteliğinde.

---

## 🧩 **Bölüm II – Giriş (Introduction)**

**Push_Swap projesi**, basit gibi görünen ama oldukça sistematik bir **algoritma zorluk projesidir.**

Amacın: **verilen sayıları sıralamak.**

Elinde şu araçlar var:

- Bir grup **tam sayı (integer)**,
- **İki adet yığın (stack)**,
- Ve bu yığınları manipüle etmek için belirli sayıda **komut**.

🎯 **Hedef:**

`push_swap` adında bir C programı yazmak.

Bu program, kendisine verilen sayıları **en az sayıda hamleyle sıralayacak** komut listesini **hesaplayacak ve ekrana yazacak.**

> Kolay mı görünüyor?
> 
> 
> Göreceğiz…
> 

---

## 🧩 **Bölüm III – Amaçlar (Objectives)**

Bir sıralama algoritması yazmak, bir geliştiricinin kariyerindeki **önemli bir aşamadır.**

Genellikle bu, kişinin **karmaşıklık (complexity)** kavramıyla ilk kez ciddi şekilde tanıştığı noktadır.

Sıralama algoritmaları ve karmaşıklık analizi, **iş görüşmelerinde çok sık** sorulan konulardır.

Bu proje, bu konuları erken yaşta keşfetmen için harika bir fırsat sunar — çünkü gelecekte mutlaka karşına çıkacak.

---

### 🎯 **Bu projenin öğrenme hedefleri:**

- C dilinde **disiplinli ve hatasız kodlama** pratiği kazanmak,
- **Temel algoritmaları** uygulamak,
- **Zaman/maliyet karmaşıklığını (time complexity)** anlamak ve optimize etmeyi öğrenmek.

---

Sayıları sıralamak başlı başına zor değildir,

ancak **en hızlı yolu bulmak** gerçek zorluktur.

En etkili sıralama yöntemi, **sayıların dizilişine** bağlı olarak değişebilir.

Dolayısıyla senin görevin sadece sıralamak değil —

aynı zamanda **minimum sayıda işlemle sıralamak.**

---

## 🧩 **Bölüm IV – Genel Talimatlar (Common Instructions)**

Bu bölümde, **Push_Swap projesini yazarken uyman gereken tüm teknik kurallar** açıklanıyor.

---

### **Genel Kurallar**

- Projen **C diliyle** yazılmalıdır.
- Kodun **Norme (Norm kuralları)** ile tamamen uyumlu olmalıdır.
    - Eğer *bonus* dosyaların veya fonksiyonların varsa, onlar da **Norm kontrolüne dahildir**.
    - Herhangi bir Norm hatası alırsan, **projeden 0 puan** alırsın.

---

### **Hatalar ve bellek yönetimi**

- Fonksiyonların **beklenmedik şekilde kapanmamalıdır**
    
    (örneğin: segmentation fault, bus error, double free, vb.).
    
    - Eğer bu tür hatalar oluşursa, proje **çalışmıyor** kabul edilir ve **0 puan** verilir.
- **Heap belleği (malloc/free)** doğru şekilde yönetilmelidir.
    - Bellek sızıntıları (memory leaks) **kabul edilmez**.

---

### **Derleme (Makefile) kuralları**

- Proje, aşağıdaki bayraklarla derlenmelidir:
    - `Wall -Wextra -Werror`
    
    ve **cc** derleyicisi kullanılmalıdır.
    
- Makefile **gereksiz yeniden derleme (relink)** yapmamalıdır.
- Makefile içinde en az şu kurallar olmalıdır:
    
    ```
    $(NAME)
    all
    clean
    fclean
    re
    
    ```
    

---

### **Bonus kuralları**

- Eğer bonus kısmı ekleyeceksen, Makefile içinde ayrıca bir `bonus` kuralı olmalıdır.
    
    Bu kural, **bonus için eklenen tüm header, library veya fonksiyonları** dahil etmelidir.
    
- Bonus dosyaları şu formatta olmalıdır:
    
    `_bonus.c` veya `_bonus.h`
    
- **Zorunlu (mandatory)** ve **bonus** bölümler **ayrı ayrı değerlendirilecektir.**

---

### **Libft kullanımı**

- Eğer projen **libft** kullanmaya izin veriyorsa:
    - `libft`’nin kaynak dosyalarını ve Makefile’ını **“libft” adlı bir klasöre** kopyalamalısın.
    - Proje Makefile’ı önce libft’yi derlemeli, sonra push_swap’i derlemelidir.

---

### **Test programları**

- Test programları yazmak **zorunlu değildir** ancak **şiddetle tavsiye edilir.**
    - Kendi kodunu test etmek, hata bulmak ve savunma sırasında test göstermek için çok faydalıdır.
    - Savunma sırasında, **kendi testlerini veya değerlendirici arkadaşının testlerini** kullanabilirsin.

---

### **Teslim (Submission)**

- Çalışmanı **atanan Git deposuna (repo)** yüklemelisin.
    - Sadece **repo’daki dosyalar** değerlendirilecektir.
- Eğer proje **Deepthought** tarafından otomatik değerlendiriliyorsa,
    - Peer değerlendirmelerinden sonra yapılacaktır.
    - Eğer herhangi bir aşamada hata oluşursa, değerlendirme **hemen durdurulur.**

---

Harika 👌

Şimdi **Bölüm V – Yapay Zekâ Talimatları (AI Instructions)** kısmının Türkçe çevirisi geliyor 👇

---

## 🧩 **Bölüm V – Yapay Zekâ Talimatları (AI Instructions)**

Bu bölüm, projeni yaparken **yapay zekâ (AI)** araçlarını nasıl doğru şekilde kullanman gerektiğini açıklıyor.

(Örneğin: ChatGPT, Copilot, vs.)

---

### 🎯 **Bağlam (Context)**

Öğrenme sürecin boyunca **yapay zekâ araçları birçok farklı konuda yardımcı olabilir.**

Zaman ayırarak bu araçların neler yapabildiğini ve **nasıl destek sağlayabileceklerini** keşfetmelisin.

Ama — **her zaman dikkatli yaklaş!**

AI’dan gelen bir yanıtın:

- Sorusunun doğru anlaşıldığından,
- Üretilen cevabın tamamen doğru olduğundan
    
    asla **%100 emin olamazsın.**
    

Bu nedenle, **arkadaşlarınla fikir alışverişi** yapmak, **yanlış anlamaları** ve **görmediğin hataları** fark etmek için çok değerlidir.

---

### 💡 **Ana Mesaj (Main Message)**

☑️ AI’ı **tekrarlayan veya sıkıcı işleri azaltmak** için kullan.

☑️ Kodlama ve kod dışı konularda **iyi “prompt” yazma becerisi** geliştir — bu ileride iş hayatında çok faydalı olacak.

☑️ AI sistemlerinin nasıl çalıştığını öğren — böylece **yanlılık (bias)** ve **etik riskleri** önceden fark edebilirsin.

☑️ **Ekip çalışması** becerilerini güçlendirmeye devam et.

☑️ **Sadece tamamen anladığın ve sorumluluğunu alabildiğin** AI çıktısını kullan.

---

### ⚙️ **Öğrenci Kuralları (Learner Rules)**

- AI araçlarını kullanmadan önce, **nasıl çalıştıklarını araştırmalısın.**
    
    Böylece onları **etik bir biçimde** kullanabilir ve **tarafsız sonuçlar** elde edebilirsin.
    
- Bir problemle karşılaştığında, **önce kendin düşünmelisin.**
    
    Bu, **daha net, detaylı ve doğru prompt’lar** yazmana yardımcı olur.
    
- AI’nın ürettiği her şeyi **sistematik olarak kontrol etme alışkanlığı** edin.
    
    (Gözden geçir, sorgula, test et!)
    
- Her zaman **akran değerlendirmesi (peer review)** al —
    
    kendi onayına **tek başına güvenme.**
    

---

### 📘 **Bu aşamadan beklenen kazanımlar (Phase Outcomes)**

- Genel amaçlı ve alan odaklı **prompt yazma becerilerini** geliştir.
- AI araçlarını **etkili şekilde kullanarak üretkenliğini artır.**
- **Hesaplamalı düşünme (computational thinking)**, **problem çözme**, **uyum sağlama** ve **iş birliği** yeteneklerini güçlendir.

---

### 💬 **Yorumlar ve Örnekler (Comments and Examples)**

- Sık sık sınavlarda veya değerlendirmelerde **gerçek anlayışını** göstermen istenir.
    
    Bu yüzden, AI’ya güvenmek yerine **teknik ve iletişim becerilerini** kendin geliştirmeye devam et.
    
- Düşüncelerini açıklamak veya bir konuyu arkadaşlarınla tartışmak, **eksik noktalarını fark etmeni** sağlar.
    
    Yani **akran öğrenmesini** öncelik haline getir.
    
- AI araçları genellikle **senin özel bağlamına hâkim değildir**
    
    ve **genel cevaplar** üretir.
    
    Oysa seninle aynı ortamda çalışan arkadaşların, **daha uygun ve doğru içgörüler** sunabilir.
    
- AI çoğu zaman **“en olası cevabı”** üretir.
    
    Ancak akranların **farklı bakış açıları** getirerek daha iyi bir sonuç elde etmene yardım edebilir.
    

---

### ✅ **İyi uygulama örnekleri**

**Doğru kullanım:**

> “AI’a ‘Bir sıralama fonksiyonunu nasıl test ederim?’ diye soruyorum.
> 
> 
> Bana birkaç fikir veriyor, deniyorum.
> 
> Sonra sonucu bir arkadaşım ile gözden geçiriyoruz ve yöntemi birlikte iyileştiriyoruz.”
> 

**Yanlış kullanım:**

> “AI’a tüm fonksiyonu yazdırıyorum, kopyalayıp projeme yapıştırıyorum.
> 
> 
> Savunma sırasında ne yaptığını anlatamıyorum, projeyi kaybediyorum.”
> 

---

**Bir başka örnek:**

**Doğru kullanım:**

> “AI bana bir parser tasarlamada yardımcı oluyor.
> 
> 
> Daha sonra arkadaşım ile adım adım mantığını tartışıyoruz.
> 
> İki hatayı fark ediyoruz ve kodu daha iyi hâle getiriyoruz.”
> 

**Yanlış kullanım:**

> “Copilot projemin önemli bir kısmını otomatik yazıyor.
> 
> 
> Derleniyor ama kodun nasıl çalıştığını açıklayamıyorum.
> 
> Savunmada mantığını anlatamadığım için kalıyorum.”
> 

---

Bu bölümün özü:

➡️ AI seni hızlandırabilir ama **senin yerine düşünemez.**

42’de amaç, **anlamak ve açıklayabilmek** —

sadece “çalıştırmak” değil.

---

## 🧩 **Bölüm VI – Zorunlu Kısım (Mandatory Part)**

---

### **VI.1 – Kurallar (The Rules)**

Elinde iki yığın (stack) var:

- **Stack A**
- **Stack B**

---

### 🧩 Başlangıç Durumu:

- **Stack A**, rastgele sıralanmış **benzersiz (unique)** negatif veya pozitif tamsayılar içerir.
- **Stack B** ise **boştur.**

🎯 **Amaç:**

Stack A’daki sayıları **artan sırada (ascending order)** sıralamak.

Bunu yapmak için aşağıdaki **sınırlı komut setini** kullanabilirsin:

---

### 🔹 **Temel İşlemler (Operations)**

| Komut | Açıklama |
| --- | --- |
| **sa (swap a)** | Stack A’nın en üstteki iki elemanını yer değiştirir. (Eğer 1 veya 0 eleman varsa, hiçbir şey yapmaz.) |
| **sb (swap b)** | Stack B’nin en üstteki iki elemanını yer değiştirir. (Eğer 1 veya 0 eleman varsa, hiçbir şey yapmaz.) |
| **ss** | `sa` ve `sb` işlemlerini aynı anda yapar. |
| **pa (push a)** | Stack B’nin en üst elemanını alıp Stack A’nın üstüne koyar. (Eğer B boşsa hiçbir şey yapmaz.) |
| **pb (push b)** | Stack A’nın en üst elemanını alıp Stack B’nin üstüne koyar. (Eğer A boşsa hiçbir şey yapmaz.) |
| **ra (rotate a)** | Stack A’daki tüm elemanları bir yukarı kaydırır; en üstteki eleman en alta gider. |
| **rb (rotate b)** | Stack B’de aynı işlemi yapar. |
| **rr** | `ra` ve `rb` işlemlerini aynı anda yapar. |
| **rra (reverse rotate a)** | Stack A’daki tüm elemanları bir aşağı kaydırır; en alttaki eleman en üste gelir. |
| **rrb (reverse rotate b)** | Stack B’de aynı işlemi yapar. |
| **rrr** | `rra` ve `rrb` işlemlerini aynı anda yapar. |

🔗 Daha fazla bilgi için: [Stack (abstract data type)](https://en.wikipedia.org/wiki/Stack_(abstract_data_type))

---

### **VI.2 – Örnek (Example)**

Aşağıdaki örnek, bu komutların etkisini göstermek için verilmiştir.

(Burada yığınlar **sağdan büyüyormuş gibi** düşünülür.)

---

### 🔹 Başlangıç durumu:

```
a: 2 1 3 6 5 8
b: _

```

### 🔹 `sa` komutunu uygula:

```
a: 1 2 3 6 5 8
b: _

```

### 🔹 `pb pb pb` komutlarını uygula:

```
a: 6 5 8
b: 3 2 1

```

### 🔹 `ra rb` (veya `rr`) komutu:

```
a: 5 8 6
b: 2 1 3

```

### 🔹 `rra rrb` (veya `rrr`) komutu:

```
a: 6 5 8
b: 3 2 1

```

### 🔹 `sa` komutu:

```
a: 5 6 8
b: 3 2 1

```

### 🔹 `pa pa pa` komutları:

```
a: 1 2 3 5 6 8
b: _

```

✅ Sonuç:

Stack A artık **12 adımda sıralanmış** durumda.

> Peki sen daha az adımda yapabilir misin?
> 

---

### **VI.3 – “push_swap” Programı**

| Özellik | Açıklama |
| --- | --- |
| **Program adı:** | `push_swap` |
| **Teslim edilecek dosyalar:** | `Makefile`, `*.h`, `*.c` |
| **Makefile kuralları:** | `NAME`, `all`, `clean`, `fclean`, `re` |
| **Argüman:** | Stack A (tamsayı listesi) |
| **İzin verilen fonksiyonlar:** | `read`, `write`, `malloc`, `free`, `exit`, ve **kendi yazdığın `ft_printf` veya eşdeğeri** |
| **Libft kullanımı:** | Evet, kullanılabilir. |
| **Açıklama:** | Yığınları sıralar. |

---

### ⚙️ **Proje kuralları**

- Makefile **yeniden derleme (relink)** yapmamalı.
- **Global değişkenler yasaktır.**
- Program `push_swap`, argüman olarak **Stack A’yı** (sayı listesini) almalıdır.
    - **İlk argüman**, yığının **en üstündeki eleman** olmalıdır. (Sıralamaya dikkat!)
- Program, yığını sıralamak için **gerekli en kısa komut listesini** yazmalıdır.
- Her komut bir satıra yazılmalı ve **yalnızca `\n`** ile ayrılmalıdır.
- Amaç: **En az işlem sayısıyla sıralamak.**
- Değerlendirme sırasında, işlem sayın **belirli bir limite göre** kontrol edilecektir.
    - Limit aşılırsa veya sıralama hatalıysa → **puan = 0.**
- Eğer program **hiç parametre almazsa**, hiçbir şey yazmadan çıkmalıdır.
- Hatalı durumlarda (örnek: sayı olmayan argüman, int sınırlarını aşma, tekrar eden sayılar)
    
    → `"Error\n"` yazmalı (stderr’e).
    

---

### 💻 **Kullanım Örnekleri**

```
$> ./push_swap 2 1 3 6 5 8
sa
pb
pb
pb
sa
pa
pa
pa

$> ./push_swap 0 one 2 3
Error

```

---

### 🔹 **push_swap + checker birlikte**

Projede bir “checker” programı verilir.

Bu program, `push_swap` çıktısını kontrol eder.

Örnek:

```bash
$> ARG="4 67 3 87 23"; ./push_swap $ARG | wc -l
6

$> ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker_OS $ARG
OK

```

Eğer `checker_OS` **“KO”** yazarsa,

ürettiğin komut dizisi **yığını doğru sıralamamış** demektir.

`checker_OS` dosyasının açıklaması, belgenin **Bonus Kısmı**nda yer alır.

---

### **VI.4 – Benchmark (Performans Testi)**

Projeni tamamlamak için **belirli sınırlar içinde sıralama yapman gerekir.**

### 🔹 **Maksimum puan (100%) ve bonus uygunluğu için:**

- 100 rastgele sayıyı **700 hamleden az** sürede sırala.
- 500 rastgele sayıyı **5500 hamleden az** sürede sırala.

### 🔹 **Minimum geçer puan (yaklaşık 80%) için:**

Aşağıdaki kombinasyonlardan biri yeterlidir:

| 100 sayı | 500 sayı |
| --- | --- |
| < 1100 işlem | < 8500 işlem |
| < 700 işlem | < 11500 işlem |
| < 1300 işlem | < 5500 işlem |

> Tüm bu limitler değerlendirme sırasında otomatik olarak kontrol edilir.
> 

---

💡 **Not:**

Bonus kısmını yapmak istiyorsan, önce **tüm benchmark testlerini en yüksek düzeyde** başarıyla geçmelisin.

Aksi takdirde bonus değerlendirilmez.

---

Harika 👏

Şimdi geldik **Bölüm VII – Bonus Kısım (Bonus Part)** ve **Bölüm VIII – Teslim & Peer Değerlendirme** bölümlerine.

Bu kısımlar kısa ama projeyi tamamlamak için çok önemli.

İşte tam Türkçe çevirileri 👇

---

## 🧩 **Bölüm VII – Bonus Kısım (Bonus Part)**

Bu proje oldukça basit yapıda olduğu için, **fazladan özellik (bonus)** ekleme imkânı sınırlıdır.

Ancak — neden **kendi “checker” programını** yazmayasın?

---

### 💡 **Bonus’un Amacı**

“Checker” programı sayesinde:

- `push_swap` tarafından üretilen komutların,
- Gerçekten **yığını doğru şekilde sıralayıp sıralamadığını**
    
    kendin kontrol edebilirsin.
    

---

### ⚠️ **Önemli Not:**

Bonus kısmı **yalnızca** zorunlu kısmı **mükemmel şekilde tamamladıysan** değerlendirilecektir.

> “Mükemmel” demek:
> 
> - Zorunlu kısmın **tüm testleri eksiksiz geçmesi**,
> - **Tüm benchmark limitlerini** aşmadan sonuç vermesi,
> - **Hiçbir hata içermemesi** anlamına gelir.

Eğer zorunlu kısmın **her yönüyle tamamen doğrulanmamışsa**,

bonus **hiç değerlendirilmez.**

---

## 🧩 **Bölüm VII.1 – “Checker” Programı**

| Özellik | Açıklama |
| --- | --- |
| **Program adı:** | `checker` |
| **Teslim edilecek dosyalar:** | `*.h`, `*.c` |
| **Makefile kuralı:** | `bonus` |
| **Argüman:** | Stack A (tamsayı listesi) |
| **İzin verilen fonksiyonlar:** | `read`, `write`, `malloc`, `free`, `exit`, kendi yazdığın `ft_printf` veya eşdeğeri |
| **Libft kullanımı:** | Evet |
| **Açıklama:** | Sıralama komutlarını çalıştırır ve sonucu doğrular |

---

### ⚙️ **Görev Tanımı**

1. `checker` adlı bir program yazmalısın.
    - Argüman olarak `stack a` alır (tamsayı listesi).
    - İlk argüman yığının **en üstündeki eleman** olmalıdır.
    - Argüman verilmezse, program **hiçbir şey yazmadan kapanır.**
2. Program, **standart girişten (stdin)** sıralama komutlarını okur.
    - Her komut bir satırda (`\n` ile biter) olmalıdır.
3. Komutların hepsini okuduktan sonra,
    
    program bu komutları sırayla **stack a** ve **stack b** üzerinde uygular.
    
4. Komutların sonunda:
    - Eğer `stack a` **artan sıradaysa** ve `stack b` **boşsa**, ekrana `"OK\n"` yaz.
    - Aksi durumda `"KO\n"` yaz.
5. Eğer hata oluşursa (örnek:
    - argümanlar sayı değilse,
    - int sınırını aşıyorsa,
    - tekrar eden sayılar varsa,
    - geçersiz bir komut yazılmışsa),
        
        o zaman `"Error\n"` yazılmalıdır (**stderr’e**).
        

---

### 💻 **Örnek Kullanımlar**

```
$> ./checker 3 2 1 0
rra
pb
sa
rra
pa
OK

$> ./checker 3 2 1 0
sa
rra
pb
KO

$> ./checker 3 2 one 0
Error

$> ./checker "" 1
Error

```

---

### 🧠 **Not:**

Kendi “checker” programını yazarken,

42’nin sağladığı `checker_OS` programıyla **tam olarak aynı davranışı** kopyalaman gerekmiyor.

Ancak:

- **Tüm hata durumlarını** doğru yönetmen **zorunludur.**
- Argümanları nasıl ayrıştıracağın (parse edeceğin) tamamen sana kalmış.

---

## 🧩 **Bölüm VIII – Teslim ve Peer Değerlendirme (Submission and Peer-Evaluation)**

---

### 📦 **Teslim (Submission)**

Çalışmanı her zamanki gibi **atanan Git deposuna** yükle.

- Sadece **repo içindeki dosyalar** değerlendirmede dikkate alınır.
- Dosya isimlerinin doğruluğunu iki kez kontrol et!

Proje otomatik doğrulama (program) ile kontrol edilmeyecekse,

dosyalarını istediğin gibi organize edebilirsin.

Ancak:

- Zorunlu dosyaları teslim etmelisin,
- Ve tüm proje gereksinimlerine uymalısın.

---

### 🧩 **Savunma (Defence) sırasında özel durumlar**

Değerlendirme sırasında, bazen senden **küçük bir değişiklik yapman** istenebilir.

Bu, şu tür şeyler olabilir:

- Bir fonksiyonda birkaç satırı değiştirmek,
- Küçük bir özellik eklemek,
- Bir veri yapısını genişletmek,
- Veya sadece bir çıktıyı farklı formatta göstermek.

---

Bu adım, senin **gerçekten anladığını** test etmek içindir.

Yani savunmada, sadece “çalışan” bir kod değil,

aynı zamanda **neden öyle çalıştığını açıklayabilen** bir geliştirici olman beklenir.

---

### 💡 **Örnek:**

Değerlendirici senden şu tür şeyler isteyebilir:

- “Bu fonksiyona küçük bir özellik ekle.”
- “Şu çıktıyı değiştir.”
- “Bu yapıya yeni bir alan ekle.”

Bu değişiklikler:

- Herhangi bir geliştirme ortamında yapılabilir,
- Genellikle **birkaç dakika içinde tamamlanabilir.**

Ama bazı durumlarda, belirli bir süre sınırı da verilebilir.

---

### 🎓 **Amaç:**

Bu adım, **projeyi gerçekten anladığını kanıtlaman** içindir.

Eğer kodu AI, Copilot veya başka bir araçla yazdıysan ama mantığını bilmiyorsan —

bu aşamada hemen fark edilir.

---

## ✅ **Sonuç**

Push_Swap projesi:

- C dilinde **iki yığınla çalışan bir sıralama algoritması**,
- Hem **optimizasyon** (en az hamleyle sıralama)
- Hem de **doğru mantık kurma** becerilerini test eder.

Bonus olarak **checker** eklersen:

- Kendi algoritmanı test edebilir,
- Savunmada çok daha güçlü bir izlenim bırakabilirsin.

---