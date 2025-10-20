# Push Swap

Bu proje, iki stack kullanarak sayıları sıralama algoritması geliştirme projesidir.

## Dosya Yapısı

```
push_swap/
│
├── 📁 include/
│   ├── 📄 push_swap.h
│   ├── 📄 stack_ops.h
│   └── 📄 utils.h
│
├── 📁 src/
│   └── 📁 push_swap/
│		└── push_swap.c
│		└── sort_large.c
│		└── sort_small.c
│	└── 📁 stack_ops
│		└── push.c
│		└── reverse_rotable.c
│		└── rotate.c
│		└── swap.c
│	└── 📁 utils
│		└── array.c
│		└── min_max.c
│		└── validation.c
│
├── 📄 Makefile
└── 📄 push_swap (executable)
```

## Derleme

```bash
make
```

## Kullanım

```bash
./push_swap [sayılar]
```

## Temizlik

```bash
make clean    # Object dosyalarını sil
make fclean   # Tüm dosyaları sil
make re       # Yeniden derle
```
