# ArchLinux安装
 
[TOC]
 
 
## 网络
 
 
### 1. WIFI
 
 
```bash
wifi-menu
```
 
 
### 2. 有线
 
 
```bash
systemctl enable dhcpcd
systemctl restart dhcpcd
```
 
 
## 时间设置
 
 
```bash
timedatectl status
timedatectl set-ntp true
```
 
 
## 更新源
 
 
```bash
vim /etc/pacman.d/mirrorlist
```
 
> ArchLinux默认加载最上面的源，所以找到中国的源剪切到最上面
 
## 磁盘分区
 
 
### 1. 建立分区表
 
 
查看磁盘信息
 
 
```bash
lsblk
```
 
 
建立分区表
 
 
```bash
parted
mktable
gpt
quit
```
 
 
### 2. 分区
 
 
```bash
cfdisk /dev/sda
```
 
 
而后是图形化操作，上下选择分区，左右选择选项，在空闲块上new并指定大小（使用10G或300m指定），已分区的使用Type指定EFI或swap类型。
 
 
### 3. 格式化
 
 
```bash
mkfs.vfat /dev/sda3
mkfs.ext4 /dev/sda1
mkfs.ext4 /dev/sda2
mkswap -f /dev/sda4
swapon /dev/sda4
```
 
 
### 4. 挂载
 
 
```bash
mount /dev/sda1 /mnt
mkdir /mnt/home
mount /dev/sda2 /mnt/home
mkdir /mnt/boot
mkdir /mnt/boot/EFI
mount /dev/sda3 /mnt/boot/EFI
```
 
 
## 安装ArchLinux
 
 
### 1. 安装基础包，设置开机自动挂载
 
 
```bash
pacstrap /mnt base
pacstrap /mnt base-devel
genfstab -U /mnt >> /mnt/etc/fstab
```
 
 
> pac就是package（软件包），strap的意思是用带子捆扎，pacstrap意思就是打好包的软件，在arch系统这是一个脚本文件的名称，它的作用就是安装arch基本系统。pac是package manager的意思吗？
 
 
### 2. 切换环境
 
 
```bash
arch-chroot /mnt
passwd root
```
 
 
### 3. 设置时区和语言
 
 
#### 时区
 
 
```bash
ln -sf /usr/share/zoneinfo/Asia/Beijing /etc/localtime
hwclock --systohc
```
 
 
#### 语言
 
 
（1）打开en_US.UTF-8 UTF-8的注释
 
 
```bash
vim /etc/locale.gen
---
locale-gen
```
 
 
（2）编辑/etc/locale.conf
 
 
```bash
LANG=en_US.UTF-8
LANG=zh_CN.UTF-8
```
 
 
### 4. 安装软件
 
 
```bash
pacman -S vim
pacman -S iw wpa_supplicant dialog
pacman -S intel-ucode
pacmac -S grub efibootmgr
```
 
 
### 5. 引导的设置
 
 
```bash
grub-install --target=x86_64-efi --efi-directory=/boot/EFI --bootloader-id=grub
grub-mkconfig -o /boot/grub/grub.cfg
```
 
 
#### 6. 重启
 
 
```bash
exit
umount -R /mnt
reboot
```