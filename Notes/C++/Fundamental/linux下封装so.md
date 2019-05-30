- 编写动态链接库 b.c
- 编写头文件a.h
- 编写主文件a.c
```
[root@admin temp]# gcc -shared -o lib1.so a.o
[root@admin temp]# ls
1.c  1.h  2.c  a.o  lib1.so
[root@admin temp]# gcc -c 1.c
[root@admin temp]# gcc 1.c
/tmp/ccS02A5g.o: In function `main':
1.c:(.text+0xf): undefined reference to `mymax'
collect2: error: ld returned 1 exit status
[root@admin temp]# gcc -c 1.c -o 1.0
[root@admin temp]# ls
1.0  1.c  1.h  2.c  a.o  lib1.so
[root@admin temp]# gcc -o main.out 1.0 -L. -l1
[root@admin temp]# ls
1.0  1.c  1.h  2.c  a.o  lib1.so  main.out
[root@admin temp]# ./main.out
20
```