# Qt文件操作
 
## 入门
 
[TOC]
 
### 1. 使用QFile文件读取
 
Qt中可以使用QFIle进行文件读写，而Java中的File只能代表一个文件，读写要用流
 
```c++
QFile file("/home/zhangweizhen/Documents/baidu.sh");
file.open(QFileDevice::ReadOnly);
QByteArray data = file.readAll();
 
ui->label->setText(data);
```
 
qt默认支持utf-8，非要转码使用
 
```c++
QTextCodec *codec = QTextCodec::codecForName("gbk");
codec->toUnicode(array);
```
 
一行行读取
 
```c++
while(file.atEnd())
{
      QByteArray line = file.readLine();
}
```
 
### 2. 文件写入
 
```c++
file.open(QFileDevice::Append);
file.write("追加内容");
file.close();
```
 
## 文件信息
 
通过QFileInfo类
 
### 1. 示例
 
```c++
QFileInfo fileInfo("D:/pic.png");
qDebug()<<"文件后缀名:"<<fileInfo.suffix();
qDebug()<<"最后修改日期:"<<fileInfo.lastModified().toString("yyyy-MM-dd HH:mm:ss");
```
 
###  2. 其他API
 
- `size()`获取文件大小
- `fileName()`获取文件名称
- `filePath()`获取文件路径
 
## 使用流进行文件读写
 
使用方式和java中较相似，传入一个File对流进行操作。Qt的流分两种，文本流和数据流，小文件用文本流，大文件用数据流。概念类似Java中的字符流和字节流。
 
### 1. 使用文本流写入
 
```c++
QFile file("test.txt");
file.open(QFileDevice::WriteOnly);
QTextStream stream(&file);
stream<<"Hello!";
file.close();
```
 
*猜测*：使用流的方式FIle也相当于一个句柄，感觉直接使用QFile进项操作底层也是使用流的API
 
### 2. 使用文本流读出
 
```c++
file.open(QFileDevice::ReadOnly);
QString str;
stream.readAll(); //使用重载的>>读取遇到空格就会结束
qDebug()<<str;
```
 
### 3.  使用数据流读写
 
使用数据流时存储到硬盘上的是二进制数据。
 
```c++
QFile file("test.txt");
file.open(QFileDevice::WriteOnly);
QDataStream stream(&file);
stream<<QString("Hello!")<<123456; //内部存储为两个数据块，需要使用对应的数据格式读两次
file.close();
 
file.open(QFileDevice::ReadOnly);
QString str;
int num;
stream>>str>>num;
qDebug()<<str<<num;
```
 
> 存储到磁盘的数据是`    H e l l o ! �@`这样的二进制数据