# Qt中的事件

[TOC]

qt中的事件一个个虚函数，需要重写。使用方法类似回调函数，重写系统定义的类并重写回调函数。这和其他GUI界面的事件机制一致，而信号和槽机制和其他GUI框架中的消息概念一致。

## 入门

### 1. 自定义类继承控件

右键 -> 新建cpp class -> 集成QWidget

### 2. 重写需要回调的方法

#### .h中

```c++
#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = nullptr);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
};

#endif // MYLABEL_H
```

#### .cpp中

```c++
void MyLabel::enterEvent(QEvent *event){
    qDebug()<<"鼠标进入事件";
}
void MyLabel::leaveEvent(QEvent *event){
    qDebug()<<"鼠标离开事件";
}
```

## 常见鼠标事件

```c++
void mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton){
qDebug()<<"按下了左键";
    }
}
void mouseReleaseEvent(QMouseEvent *ev)
{
    QString str = QString("鼠标坐标 x:%1 y:%2").arg(ev->x()).arg(ev->y());
    qDebug()<<str;
}
void mouseMoveEvent(QMouseEvent *ev)
{
    //移动时使用buttons()并使用&来表示要求的按键按下
    if(ev->buttons() & Qt::LeftButton){
qDebug()<<"按着左键移动";
    }
}
```

> 使用mouseMoveEvent要求按键按下，如果要求悬浮有效，需要设置该控件为`this->setMouseTracking(true);`

## 定时器事件

```c++
#include "widget.h"
#include "ui_widget.h"
#include <QTimerEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    timerId1 = startTimer(1000);
    timerId2 = startTimer(2000);
}
void Widget::timerEvent(QTimerEvent *event){
    if(event->timerId == timerId)//通过计时器的编号判断是哪个计时器
    {
        static int i=0;
        ui->label->setText(QString::number(i++));
    }

}
Widget::~Widget(){delete ui;}

```

另一种计时器的使用方式，创建一个定时器定时发送timeout信号然后绑定槽函数，这种方式在遇到多个定时器的情况更好用。

```c++
QTimer * timer = new QTimer(this);
timer->start(500);
connect(timer,&QTimer::timeout,[=](){
    static int num = 0;
    ui->label->setText(QString::number(num++));
});
```

> `timer->stop()`停止定时器

## Event事件

管理事件的分发，返回true时用户处理不向下分发。项目中通常不拦截。

```
bool MyLabel::event(QEvent *e)
{
QMouseEvent *ev = static_cast<QMouseEvent *>(e);
    if(e->type() == QEvent::MouseButtonPress)
    {
    	qDebug()<<"鼠标按下事件:"<<ev->x()<<","<<ev->y();
    	return true;
    }
    // 其他事件让父类做默认处理
    return QLabel::event(e);
}
```

## 事件拦截器

需要拦截事件的控件安装事件过滤器，在event分发时间之前进行拦截

### 1. 通过父窗口给控件安装过滤器

```c++
ui->label->installEventFilter(this);
```

### 2. 重写eventFilter()方法

```c++
bool Widget::eventFilter(QObject *obj,QEvent *e){
    QMouseEvent *ev = static_cast<QMouseEvent *>(e);
    if(obj == ui->label){
        if(e->type() == QEvent::MouseButtonPress)
        {
            qDebug()<<"鼠标按下事件:"<<ev->x()<<","<<ev->y();
            return true;
        }
    }
    return QWidget::eventFilter(obj,e);
}
```

