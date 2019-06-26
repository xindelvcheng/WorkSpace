# Termux

## 使用ssh连接

### 1. 安装ssh服务

### 2. 开启sshd

```bash
$ sshd
```

### 3. 外部连接

```bash
$ ssh u0_a299@ip:8022
```

## 安装完整的Linux

### 1. Ubuntu

```bash
$ pkg install proot
$ pkg install wget
$ wget https://raw.githubusercontent.com/Neo-Oli/termux-ubuntu/master/ubuntu.sh
$ bash ubuntu.sh
```

### 2. Arch

```bash
$ pkg install proot
$ pkg install wget
$ wget https://raw.githubusercontent.com/sdrausty/TermuxArch/master/setupTermuxArch.sh
$ bash setupTermuxArch.sh
```

### 3. Centos

```bash
$ pkg install proot
$ pkg install wget
$ wget https://raw.githubusercontent.com/nmilosev/termux-fedora/master/termux-fedora.sh $ bash termux-fedora.sh
```

### 4. Kali

```bash
$ pkg install proot
$ pkg install wget
$ wget https://raw.githubusercontent.com/sdrausty/TermuxArch/master/setupTermuxArch.sh
$ bash setupTermuxArch.sh
```



其他见<https://baijiahao.baidu.com/s?id=1607384881189668585&wfr=spider&for=pc>