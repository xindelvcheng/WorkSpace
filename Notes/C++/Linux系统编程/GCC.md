# GCC编译器使用入门
## 常用参数
-   **-v/--version** GCC版本
-   **-E** 预编译生成.i文件
-   **-S** 汇编生成.s文件
-   <font color=red>**-c** 编译生成二进制.o文件，参数位置不固定</font>
-   **不写参数** 链接生成可执行文件
-   <font color=red>**-I** 指定包含头文件的include文件夹位置，当.h文件不在源文件同一文件下时</font>
-   <font color=red>**-o** 指定生成的文件名</font>
-   **-g** gdb调试时需要添加
> QT开发时有Debug和Release模式，两者链接的dll是不同的，加了d的dll要大不少
-   **-D** 编译时临时添加宏定义
```
//在程序中不定义宏DEBUG
#ifdef DEBUG
printf("log")
#endif
//编译时
$ gcc source.c -D DEBUG
```
在开发过程中有很多pringf打印日志，但是其是IO操作会降低效率，开发时都可以这样直接变相消除
-   **-Wall** 添加警告信息
-   **-On** 优化代码，n为优化级别，1,2,3依次增高


## C语言源代码项目结构
-   root
    -   include 头文件
    -   src 源代码
    -   lib 库文件


## 动态库和静态库
不提供源代码，而是提供头文件和二进制文件，别人一样可以使用  
### 静态库
#### 静态库的创建
```
$ vim head.h
$ vim a.c
$ vim b.c
$ vim head.h 
$ gcc -c a.c b.c
$ ls
a.c  a.o  b.c  b.o  head.h
$ ar rcs libtest.a a.o b.o
$ ls
a.c  a.o  b.c  b.o  head.h  libtest.a
$ nm libtest.a 

a.o:
0000000000000000 T add

b.o:
0000000000000000 T sub
```
#### 静态库的使用
```
$ vim main.c
$ gcc main.c -L . -l test
```
-L 静态库所在路径  
-l 静态库名称（静态库文件名除了lib和.a的中间部分
### 动态库
#### 动态库的创建
```
$ gcc a.c b.c -c -fpic
$ gcc a.o b.o -shared -o libtest.so
$ gcc *.o -shared -o libtest.so
```
>gcc的很多命令参数位置是无所谓的，不过-o后面应该接要生成的文件名；-L和-l指定路径，和路径间有没有空格无所谓
#### 动态库的使用
```
$ vim main.c
$ gcc main.c -L . -l test
```
由于动态库的加载机制，.so文件不在系统环境变量目录下是找不到的
```
$ ldd a.out 
	linux-vdso.so.1 (0x00007ffe0c19f000)
	libtest.so => not found
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fddbdc02000)
	/lib64/ld-linux-x86-64.so.2 (0x00007fddbe1f5000)

```
临时添加.so文件到环境变量中
```
$ export LD_LIBRARY_PATH = $LD_LIBRARY_PATH:/home/zhangweizhen/temp
```
永久添加可以添加到~/.bashrc或/etc/profile或者使用Linux的函数来加载动态库