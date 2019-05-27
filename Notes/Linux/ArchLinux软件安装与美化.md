# ArchLinux使用
 
## 软件
 
### 1. 刷新软件库
 
```bash
pacman -Syy
```
 
### 2. 安装桌面环境
 
```bash
pacman deepin
```
 
### 3. 使用工具
 
命令行补全工具
 
```bash
pacman -S bash-completion
```
 
网络
 
```bash
pacman -S networkmanager
systemctl enable NetworkManager
systemctl start NetworkManager
```
 
### 4. 添加用户
 
```bash
useradd -m -g users -G wheel -s /bin/bash zhang
passwd zhang
```
 
然后使用visudo修改提权文件去掉wheel前的注释
 