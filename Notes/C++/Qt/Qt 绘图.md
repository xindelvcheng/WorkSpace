# QT 绘图
[TOC]
## 入门

### 绘图是一个事件

通过重写回调函数paintEvent的方式使用，需要设置一个绘图设备，可以使用this

```c++
void Widget::paintEvent(QPaintEvent*){
    QPainter painter(this);
    
    QPen pen(QColor(255,0,0));
    painter.setPen(pen);
    pen.setWidth(3);
    
    painter.drawLine(0,0,100,100);
}
```

### 其他API

椭圆

```c++
painter.drawEllipse(QPoint(100,100),144,144);
```

字体

```c++
painter.drawText(QRect(90,90,150,150),"你好！");
```

设置笔风格

```c++
pen.setStyle(Qt::DotLine);
```

笔刷填充封闭图形

```c++
QBrush brush(QColor(255,0,0));
painter.setBrush(brush);
```

> 笔刷同样可以设置风格

## 高级设置

抗锯齿

```c++
painter.setRenderHint(QPainter::Antialiasing);
```

移动painter

```c++
paint.translate(QPoint(100,0));
```

保存和取出paint的位置

```c++
painter.save();
painter.restore();
```

## 使用painter画图

```c++
painter.drawPixmap(10,100,QPixmap("path"));
```

## 手动调用绘图事件

```c++
update();
```

## 其他绘图设备
### 1. QPixmap

对显示作优化

```c++
QPixmap pix(300,300);
pix.fill(Qt::white);
QPainter painter(&pix);

QPen pen(QColor(255,0,0));
painter.setPen(pen);

painter.drawEllipse(QPoint(150,150),100,100);

pix.save("./line.png");
```

### 2. QImage

对像素级操作优化

```c++
QImage img;
img.load("path");

for(int i = 0; i< 50;i++){
    for(int j = 0; j< 50;j++){
        QRgb value = qRgb(255,0,0);
        img.setPixel(i,j,value);
    }
}

QPainter painter(this);
painter.drawImage(QPoint(0,0),img);
```

### 3. QPicture

用于存储绘图操作

```c++
//存储
pic.save("paint.xxx");//存储的不是图片而是绘图指令，所以后缀名任意
//重现
pic.load("paint.xxx");
painter.drawPicture(0,0,pic);
```

