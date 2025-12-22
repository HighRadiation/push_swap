boksuz deneme1 main
╰─$ valgrind ./push_swap "2147483647 -2147483649"
==1742155== Memcheck, a memory error detector
==1742155== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==1742155== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==1742155== Command: ./push_swap 2147483647\ -2147483649
==1742155==
==1742155== Invalid free() / delete / delete[] / realloc()
==1742155==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==1742155==    by 0x4014A5: free_errors (in /home/boksuz/Desktop/deneme1/push_swap)
==1742155==    by 0x40134D: process_args (in /home/boksuz/Desktop/deneme1/push_swap)
==1742155==    by 0x40127F: stack_init (in /home/boksuz/Desktop/deneme1/push_swap)
==1742155==    by 0x4011AB: main (in /home/boksuz/Desktop/deneme1/push_swap)
==1742155==  Address 0x4a9e0a0 is 0 bytes inside a block of size 11 free'd
==1742155==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==1742155==    by 0x401387: process_args (in /home/boksuz/Desktop/deneme1/push_swap)
==1742155==    by 0x40127F: stack_init (in /home/boksuz/Desktop/deneme1/push_swap)
==1742155==    by 0x4011AB: main (in /home/boksuz/Desktop/deneme1/push_swap)
==1742155==  Block was alloc'd at
==1742155==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==1742155==    by 0x402693: word_dup (in /home/boksuz/Desktop/deneme1/push_swap)
==1742155==    by 0x4024E7: ft_split (in /home/boksuz/Desktop/deneme1/push_swap)
==1742155==    by 0x40125E: stack_init (in /home/boksuz/Desktop/deneme1/push_swap)
==1742155==    by 0x4011AB: main (in /home/boksuz/Desktop/deneme1/push_swap)
==1742155==
Error
==1742155==
==1742155== HEAP SUMMARY:
==1742155==     in use at exit: 0 bytes in 0 blocks
==1742155==   total heap usage: 4 allocs, 5 frees, 63 bytes allocated
==1742155==
==1742155== All heap blocks were freed -- no leaks are possible
==1742155==
==1742155== For lists of detected and suppressed errors, rerun with: -s
==1742155== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
