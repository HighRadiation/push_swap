# push_swap nedir?
	- Sıralama algoritması projesi – klasik "sort" fonksiyonu yazmak değil, "stack" mantığıyla ve kısıtlı hamlelerle sıralamak.
	- Sana bir dizi (örneğin, 3 2 1 6 8) verilir. Elinde iki boş stack var:
		stack A (başlangıçta tüm sayılar burada)
		stack B (başlangıçta boş).
	Sadece belirli komutları kullanarak (push, swap, rotate, reverse rotate) stack A'yı küçükten büyüğe sıralayacaksın.

## Amaç
	- Yani, sana bir dizi (örneğin, 3 2 1 6 8) verilir. Elinde iki boş stack var: stack A (başlangıçta tüm sayılar burada) ve stack B (başlangıçta boş). Sadece belirli komutları kullanarak (push, swap, rotate, reverse rotate) stack A'yı küçükten büyüğe sıralayacaksın.

## Nasıl yani?
	- Kullanılan araçlar:
	-     İki stack (A ve B).
	-     Sadece belirli komutlar:
	-         sa - stack A'nın en üstteki iki elemanını değiştirir (swap).
	-         sb - stack B için aynı.
	-         ss - ikisini birlikte swap.
	-         pa - stack B'nin en üstünden stack A'ya push.
	-         pb - stack A'nın en üstünden stack B'ye push.
	-         ra - stack A'yı yukarı döndür (rotate).
	-         rb - stack B için aynı.
	-         rr - ikisini birlikte rotate.
	-         rra - stack A'yı aşağı döndür (reverse rotate).
	-         rrb - stack B için aynı.
	-         rrr - ikisini birlikte reverse rotate.
	Zorluk:
    	- Sadece yukarıdaki komutlar ile, verilen diziyi mümkün olan en az hamleyle sıralamak.
    	- Kendi algoritmanı tasarlamak, optimize etmek ve memory leak olmadan kodlamak.

## Nasıl Başlanmalı
	- Proje gereksinimlerini oku ve anla
		Kuralları, kullanılacak komutları, Norme gereksinimini ve hata/memory leak kurallarını gözden geçir.

	- Stack (yığın) veri yapısı tasarımı
    	Linked list mi, array mi kullanacağına karar ver.
    	Stack A ve Stack B için temel struct’ları oluştur.

	- Temel stack fonksiyonlarını yaz
		Eleman ekle/çıkar (push/pop)
    	Swap, rotate, reverse rotate işlemlerini kodla.
    	Fonksiyonları küçük testlerle doğrula.

	- Input parsing ve validasyon
    	Komut satırından gelen argümanları (sayıları) al.
    	Hatalı giriş, tekrar eden sayı, integer overflow kontrolü yaz.

	- Komut fonksiyonlarını yaz
		sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb, rrr fonksiyonlarını kodla.

	- Küçük testler ile temel fonksiyonları dene
	    Stack üzerinde işlemleri elle veya otomatik testlerle kontrol et.

	- Sıralama algoritmasını seç ve planla
    	Küçük diziler için brute force veya özel algoritma.
	    Büyük diziler için optimize (ör: radix sort, quicksort türevi).

	- Algoritmanın mantığını kağıtta veya pseudocode ile yaz
		 Adım adım hangi işlemleri yapacağını planla.

	- Ana algoritmayı kodla
		En az hamleyle sıralama yapacak şekilde kodunu geliştir.

	-Makefile oluştur ve kuralları ekle
    	Wall -Wextra -Werror bayrakları ile derlenmeli.
    	all, clean, fclean, re kuralları bulunmalı.

	-Libft entegrasyonu (gerekiyorsa)
		Libft klasörünü ekle, Makefile’da önce onu derle.

	-Memory leak ve hata testleri yap
    	Valgrind ile memory leak kontrolü.
    	Yanlış inputlarla programı test et.

	-Norme ve stil kontrolü yap
		Kodun Norme’ye uygun mu, isimlendirme ve fonksiyon uzunluğu kurallarına dikkat et.

	-Peer review ve savunma provası
		Kodunu arkadaşına göster, birlikte gözden geçirin.
    	Algoritma mantığını açıklamayı pratik et.

	- Kendi test programlarını yaz (isteğe bağlı ama tavsiye edilir)
    	Farklı inputlar ile algoritmanın doğruluğunu ve performansını ölç.

# Ekstra İpuçları
    - Her adımda küçük kod parçalarını test etmeden ilerleme!
    - Kodunu açıklayan kısa notlar tut (savunma için faydalı olur).
    - Hataları görüp düzeltmek için sık sık peer review al























