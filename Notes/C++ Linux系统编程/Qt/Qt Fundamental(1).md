# Qt Fundamental

[TOC]

## 入门
### 1. 项目结构
-   主程序 main.cpp
```
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); //相当于flask中的app
    MainWindow w;
    w.show(); //窗口默认不会弹出
    return a.exec(); //进入一个死循环，让程序不会一闪而过
}
```
-   项目文件 .pro
```

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets # Qt5才有widgets

TARGET = demo1 # 生成项目名
TEMPLATE = app # 模板为应用程序

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui
```
>SOURCES、HEADERS、FORMS等都是系统自动生成的
>
>-   头文件 mainwindow.h
```
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT //定义了这个宏就可以使用信号和槽

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
```
-   源文件 mainwindow.cpp
```
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), //语法，初始化列表，不是继承
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
```

### 2. 设置窗口属性
```
this->move(100,100);
this->setWindowTitle("Qt标题");
this->resize(1920,1080);
this->setFixedSize(1920,1080);  //窗口创建后不能拉伸
```
>Qt中的坐标系  
(0,0) → ;x  
 ; ; ;↓  
 ; ; ;y
### 3. 创建一个按钮
```
QPushButton *btn = new QPushButton();
btn->setParent(this);
btn->setText("Hello")
```
可以使用btn的有参构造函数指定文本和父窗体。Qt中的控件都是QWidget，也可以使用`move(x,y)`,`resize(w,h)`方法
### 4. 绑定槽函数
右键控件->转到槽
### 5. 获取UI
```
ui->lineEdit->setText("Hello!");
```
和Android通过id不同，这里可以直接获取UI里的对象，它们都在自动生成的ui_mainwindow中
### 6. 日志
QDebug
```
qDebug()<<"Hello!"<<endl;
```
### 7. 对象树
指定了父窗体的控件（Children表）会依次在父窗体关闭时调用析构函数，不用手动释放
## QtCreate快捷键
-   F1 按两次进入帮助
-   Ctrl+i 自动对其
-   Ctrl+Shift+up/down 整行移动
-   F4 同名.h .cpp文件切换

## 信号与槽
### 1. 简介
#### Unix signal
产生者（键盘等）-> 绑定signal(SIGNAL（信号id）,func) -> 接受者 .c中的func函数
#### 信号与槽
产生者（按钮等）-> 绑定connect() -> 接受者（可以为当前对象，槽：专门处理信号的特殊函数）
### 2. 绑定过程
#### 在MainWindow.h文件中申明槽函数，槽函数的形参和返回值要和信号相同
```
private slots:
    void on_pushButton_2_clicked(bool);
```
#### 在MainWindow.cpp中实现槽函数
```
void MainWindow::on_pushButton_2_clicked(bool)
{
    this->close();
}
```
#### 使用函数指针绑定
```
connect(ui->pushButton_2,&QPushButton::clicked,this,&QWidget::close);
```
#### 使用宏绑定
```
QObject::connect(ui->pushButton_2, SIGNAL(clicked(bool)),
                 this,  SLOT(on_pushButton_2_clicked(bool)));
```
### 3. 自定义信号和槽
#### 自定义信号
```
/**
  自定义信号
  - 需要写到signals下
  - 返回值必须是void
  - 只需要申明，不需要实现
  - 信号可以有参数，可以重载
  */
signals:
    void signal();  
```
#### 发出自定义信号
使用关键字**emit**
```
emit a.signal();
```
#### 自定义槽函数
```
/**
  自定义槽函数
  - 可以写到public slots下，高版本可以写到public下或全局函数
  - 返回值是void
  - 需要申明，也需要实现
  - 可以有参数，可以重载
  */
public slots:
    void slot();
};
```
#### 绑定信号与槽
```
A a;
B b;
connect(&a,&A::signal,&b,&B::slot);
```
#### 发出信号
```
A a;
B b;
void (A::*signal)(QString) = &A::signal;
void (B::*slot)(QString) = &B::slot;
connect(&a,signal,&b,slot);
emit a.signal("zhangsan");
```
#### 绑定信号和信号
语法和绑定信号和槽一样
#### 断开信号和槽
参数和绑定信号和槽完全一样
### 4. 总结：
-   信号参数和槽函数参数类型要一一对应，但信号参数可以多于槽函数参数，反之不可以
-   信号参数和槽函数是多对多的关系
-   QT使用宏的方式连接信号和槽编译不检查，不推荐使用
## API
### 类型转换

#### QString转int

```c++
QString text = ui->label->text();
text.toInt()//可以传入一个用于判断转换是否成成功的值，可以指定进制，还有toDouble()等方法
char *str = q.toUtf8().data();
```
#### int转QString

```c++
QString str = QString::number(1);
```



### 格式化输出字符串

```
QString i;           // current file's number
QString total;       // number of files to process
QString fileName;    // current file's name

QString status = QString("Processing file %1 of %2: %3")
              .arg(i).arg(total).arg(fileName);
```
## Lambda表达式
C++中的Lambda表达式是一个匿名函数
### 1. 格式
```
[](){}
```
函数体写在{}中
### 2. 外部传参在[]中指定
`[]`中为空在Lambda表达式内看不到自己所在作用范围内的局部变量
- "=":外部变量值传递

  >加了mutable关键字`[]()mutable{}`才能修改值传递的值
-   "&":外部变量引用传递
-   最常见的形式使用=，例子：无参信号调用有参槽函数
    ```
    connect(btn,&QPushButton::clicked,this,[=](){
        zt->hungry("参数");
    };
    ```
### 3. 返回值
```
int ret = []()->int{return 1000;}();
```
### 4. 在信号与槽中使用Lambda表达式