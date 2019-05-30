# Linux系统入门
## 软件包的安装
### apt-get
```
$ sudo apt-get install python3-pip
$ sudo apt-get update //更新源，/etc/apt/sources.list
```
### dpkg
```
$ sudo dpkg -i xxx.deb
$ sudo dpkg -r xxx.deb
```
### 源码安装
1.检测环境自动创建makefile文件
```
$ ./configure
```
2.生成可执行文件
```
$ make
```
3.安装到系统环境变量目录
```
$ sudo make install
```

## 常用命令
-   file 查看文件类型
```
$ file ls
ls: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked,
interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 3.2.0, BuildID[sha1]=9567f9a28e66f4d7ec4baf31cfbf68d0410f0ae6, stripped
```
-   env 查看系统环境变量
-   chsh -s /bin/bash 修改系统默认shell
-   ln -s /media/zhangweizhen/Tutorial 生成一个Tutorial快捷方式