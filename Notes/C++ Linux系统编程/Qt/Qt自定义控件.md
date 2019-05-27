
# Qt自定义控件

## 入门

### 设计自定义控件样式

直接添加cpp没有ui设计界面。右键新文件 -> Qt设计师界面类 -> Widget





而后进行设计，添加控件和调整大小

### 添加自定义控件
拖拽一个Widget到设计面板中，右键“提升为”->“提升的类名称”->“全局包含”->“添加”->“提升”


此时这个拖入的Widget类名已经发生了变化,从Widget变成了自定义的类名SmallWidget

### 在smallwidget.cpp中编写代码设置这些控件的配合
```

connect
(
ui
->
spinBox
,
signal
,
ui
->
horizontalSlider
,&
QSlider
::
setValue
);
connect
(
ui
->
horizontalSlider
,&
QSlider
::
valueChanged
,
ui
->
spinBox
,&
QSpinBox
::
setValue
);
```
### 编写自定义控件特有方法
在.h public中声明，在.cpp中实现
```

void
 
SmallWidget
::
 
setValue
(
int
 
value
){
    
ui
->
spinBox
->
setValue
(
value
);
}
```

