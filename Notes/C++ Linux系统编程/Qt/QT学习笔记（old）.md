# QT学习笔记

[TOC]

## 从QT空白项目到一个窗口
创建一个空白项目
1.  新建C++源文件`main.cpp`,引入`QApplication`和`QWidget`头文件,添加以下代码
    ```
    int main(int argc, char *argv[])
    {
        QApplication a(argc, argv);
        Widget w;
        w.setWindowTitle("QT window");
        w.show();
        return a.exec();
    }
    ```
    >C++没有像C#中那样的“属性”，也不是像Java那样严格的get/set封装,所以获取属性直接用`object.value`,设置属性使用`setValue`
2. QTDemo1.pro中添加`QT += widgets gui`

   >Qt中的类都以Q开头
## 组件
以PushButton为例
### 1. PushBotton
-   代码示例   
    ```
    QPushButton button;
    button.setText("一个按钮");
    button.setParent(&w);
    ```

    >这里都是传指针，所以后面直接new返回一个窗口指针作参数  
    >C++的类的实例化不是只能A a = new A(),QT中往往都是A a;从Java转过来非常别扭,就像是空指针一样。
-   所有的组件都继承自QWidget，都是窗口，可以调用show()方法显示，或者由父类显示时一并显示。
-   如果不指定父窗口，各窗口/组件都是独立的。
-   和WPF不一样，QT是子窗口设定父窗口，而WPF是父窗口指定子控件。但是Qt中设定布局的时候是父窗口设定布局:`w.setLayout(&layout);`
### 2. LineEdit
-   密码框：`edit.setEchoMode(QLineEdit::Password);`
-   获取文本：`edit.text();`
-   占位符：`edit.setPlaceholderText("输入密码");`
- 自动补全提示：`QCompleter completer(QStringList()<<"abc"<<"123"<<"000");`
  - 设置全匹配`completer.setFilterMode(Qt::MatchContains);`

    >C++中的枚举类型是同命名空间下不需要枚举名的，不像Java中需要EnumName.element

## 布局
### QVBoxLayout
```
QVBoxLayout layout;
layout.addWidget(&button);
layout.addWidget(&edit);
w.setLayout(&layout);
```
### QHBoxLayout
```
……
layout.addStretch();//弹簧
layout.addSpacing(20);//空格
……
```
>加入了Layout中的窗口不需要指定父窗口
>Layout并不是一个窗口。  
### QGridLayout
```
QGridLayout layout;
layout.addWidget(&button,0,0);
layout.setColumnStretch(2,1);
layout.addWidget(&edit,0,1);
layout.addWidget(new QPushButton("QString"),1,0);
layout.addWidget(new QPushButton("Hello"),1,1);
w.setLayout(&layout);
```
>C++中new会返回一个指针  
>`layout.setColumnStretch(2,1)`在第2列放置比重为1的弹簧  
### 布局的嵌套
```
QGridLayout layout;
QLineEdit* password;
layout.setColumnStretch(3,1);
layout.setRowStretch(4,1);
layout.setColumnStretch(0,1);
layout.setRowStretch(0,1);
layout.addWidget(new QLabel("用户名"),1,1);
layout.addWidget(new QLineEdit(),1,2);
layout.addWidget(new QLabel("密码"),2,1);
layout.addWidget(password = new QLineEdit(),2,2);

QHBoxLayout* hBox;
layout.addLayout(hBox = new QHBoxLayout,3,2);
hBox->addStretch(1);
hBox->addWidget(new QPushButton("登陆"));
password->setEchoMode(QLineEdit::Password);
w.setLayout(&layout);

w.show();
```
> expected type-specifier before 'Label'这样的错误可能是没有引入头文件造成的，报的错不知道是什么东西
### 其他控件
```
#include <QLabel> //显示文字，图片
#include <QPushButton> //按钮
#include <QLineEdit> //单行
#include <QComboBox> //下拉框
#include <QCheckBox>
#include <QRadioButton>
#include <QTextEdit> //多行，富文本
#include <QTextBrowser> //只读文本框
#include <QGroupBox> //只是一个框，里面放布局
#include <QSlider> //进度条
#include <QSpinBox> //数值进度条
#include <QDateEdit>
#include <QTimeEdit>
#include <QDateTimeEdit>
```
>QT的控件**支持HTML格式**（继承自Widget），如`new QLabel("<h1>LabelText</h1>")`和`button->setStyleSheet("QPushButton {font:bold 17px;color:red}")`  
>QComboBox可以使用`setEditable(true)`可以编辑，也可以使用`setCompleter(combo->model())`设置自动补全
## 信号和槽
### 以PushButton为例
```
QObject::connect(&button,SIGNAL(clicked(bool)),&w,SLOT(close());
```
### Lambda表达式
在.pro文件中添加`CONFIG += C++11`
```
connect(label,&QLabel::linkActivated,[](QString str){
        qDebug()<<str;
    });
```