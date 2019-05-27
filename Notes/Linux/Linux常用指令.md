# Linux常用命令

[TOC]

## 系统管理

### 1. 查询端口占用

```bash
$ netstat -apn |grep 8088
```

### 2. 向服务器传输文件

```bash
$ scp ./wechat.py root@120.77.251.152:/root/Desktop/ #-r 传递文件夹
```

## 日常使用

### 1. 建立软连接（快捷方式）

```bash
$ ln -s [文件名] [软连接名]
$ ln -s /media/zhangweizhen/新加卷/Tutorials
```

### 2. 网络下载

```bash
$ curl -LO http://download.tensorflow.org/example_images/flower_photos.tgz
下载，-L更随重定向
```

### 3. 层级查找文件

```bash
# 按文件查找
$ find /etc -name profile
```

### 4. 解压文件

```bash
$ unzip -O cp936 xxx.zip
```

### 5. 查找命令所在位置

```bash
$ which python3
```

 

## 开发环境

### 1.创建数据库

```sql
create database ihome default charset=utf8；
```

## 磁盘管理

### 1. 查看磁盘空间

```bash
df -h
```
### 2.查看目录大小
```bash
查看/etc目录总大小
$ du -sh /etc
查看/etc下所有目录大小
$ du -h /etc 
```
### 挂载命令


显示挂载的设备


```bash
$ mount -l
```


挂载


```bash
$ mkdir /mnt/cdrom
$ mount /dev/cdrom /mnt/cdrom
$ mount -o remount,ew /
```


卸载


```bash
$ unmount /mnt/cdrom 
```


> 卸载时可以指定挂载点或设备文件名


查看U盘设备文件名并挂载


```bash
$ fdisk -l
$ mount -t vfat /dev/sdb1 /mnt/usb
```
> systs,proc是内存的挂载点，tempfs、devpts等是临时挂载点
### fdisk分区命令


#### 1.分区要点


- 主分区最多4个
- 扩展分区最多1个，且扩展分区不能格式化也不能存储数据只能用于包含逻辑分区
- 逻辑分区分区号从5开始
- 主分区+扩展分区最多4个
- 一般是一个主分区(分区号为1)和一个扩展分区(分区号为2)


查看硬盘和分区情况


```bash
$ fdisk -l
```


> fdisk命令不能知道硬盘是否被挂载，要知道是否被挂载要使用`df`或`mount`命令


#### 2. 分区命令


```bash
$ fdisk /dev/sdb
```


#### 3. 交互指令


- n：新建分区
- l：显示已知的文件系统类型，82位Linux swap分区，83为Linux分区
- m：显示帮助
- d：删除分区
- w：保存退出
- q：不保存退出
- p：显示分区列表


> 可能需要按Ctrl+Backspace删除


#### 4. 分区过程


```bash
命令(输入 m 获取帮助)：n
Partition type:
   p   primary (1 primary, 0 extended, 3 free)
   e   extended
Select (default p): p
分区号 (2-4，默认 2)：2
起始 扇区 (83884032-83886079，默认为 83884032)：
将使用默认值 83884032
Last 扇区, +扇区 or +size{K,M,G} (83884032-83886079，默认为 83886079)：+10G
值超出范围。
Last 扇区, +扇区 or +size{K,M,G} (83884032-83886079，默认为 83886079)： 
```


> 默认按扇区分配不符合习惯，可以使用`+10G`这样的方式来指定分区大小


重新读取分区表(分区之后最好执行一遍)


```bash
$ partprobe
```


#### 5. 格式化分区


```bash
$ mkfs -t ext4 /dev/sdb1
```


#### 6. 新建空目录挂载分区


```bash
$ mkdir /disk1
$ mkdir /disk2
$ mount /dev/sdb1 /disk1
$ mount /dev/sdb5 /disk2
```


### 自动挂载


#### 1. /etc/fstab文件


自动挂载/dev/sdb1到/disk1目录，每天自动备份，fsck优先级为2


```bash
/dev/sdb1 /disk1 ext4 defaults 1 2
```


按照/etc/fstab文件的内容自动挂载，如有错误会报错


```bash
$ mount -a
```

## 重定向

### 1. 输入/覆盖

```python
$ echo "text" > newFile.txt
```

### 2. 追加

```bash
$ cat ~/.bash_profile >> ~/.zshrc
```

