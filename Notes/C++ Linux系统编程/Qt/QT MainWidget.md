# Qt中的QMainWindow
[TOC]
QMainWindow主窗口类，包含一个菜单栏，多个工具栏，多个锚接固件（浮动窗口），一个状态栏和一个中心部件。 ## 菜单栏
```
// 创建菜单栏 QMenuBar *bar = menuBar(); this->setMenuBar(bar); QMenu *fileMenu = bar->addMenu("文件"); QMenu *editMenu = bar->addMenu("编辑"); QAction *newAction = fileMenu->addAction("新建"); // 添加分割线 fileMenu->addSeparator(); QAction *openAction = fileMenu->addAction("打开");

9
 
1
// 创建菜单栏
2
QMenuBar
 
*
bar
 
=
 
menuBar
();
3
this
->
setMenuBar
(
bar
);
4
QMenu
 
*
fileMenu
 
=
 
bar
->
addMenu
(
"文件"
);
5
QMenu
 
*
editMenu
 
=
 
bar
->
addMenu
(
"编辑"
);
6
QAction
 
*
newAction
 
=
 
fileMenu
->
addAction
(
"新建"
);
7
// 添加分割线
8
fileMenu
->
addSeparator
();
9
QAction
 
*
openAction
 
=
 
fileMenu
->
addAction
(
"打开"
);


```
## 工具栏
```
QToolBar *toolBar = new QToolBar(this); addToolBar(Qt::LeftToolBarArea,toolBar); // 只允许工具栏左侧或后侧停靠 toolBar->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea); // 不允许浮动 toolBar->setFloatable(false); // 设置移动（总开关） toolBar->setMovable(false); // 添加菜单项 toolBar->addAction(newAction); toolBar->addAction(openAction);

11
 
1
QToolBar
 
*
toolBar
 
=
 
new
 
QToolBar
(
this
);
2
addToolBar
(
Qt::LeftToolBarArea
,
toolBar
);
3
// 只允许工具栏左侧或后侧停靠
4
toolBar
->
setAllowedAreas
(
Qt::LeftToolBarArea
 
|
 
Qt::RightToolBarArea
);
5
// 不允许浮动
6
toolBar
->
setFloatable
(
false
);
7
// 设置移动（总开关）
8
toolBar
->
setMovable
(
false
);
9
// 添加菜单项
10
toolBar
->
addAction
(
newAction
);
11
toolBar
->
addAction
(
openAction
);
```


## 状态栏
```
QStatusBar *sBar = statusBar(); setStatusBar(sBar); QLabel *label = new QLabel("提示信息",this); //添加到左下角 sBar->addWidget(label);  QLabel *label2 = new QLabel("警告",this); //添加到右下角 sBar->addPermanentWidget(label2);


x
1
QStatusBar
 
*
sBar
 
=
 
statusBar
();
2
setStatusBar
(
sBar
);
3
QLabel
 
*
label
 
=
 
new
 
QLabel
(
"提示信息"
,
this
);
4
//添加到左下角
5
sBar
->
addWidget
(
label
);
6
7
QLabel
 
*
label2
 
=
 
new
 
QLabel
(
"警告"
,
this
);
8
//添加到右下角
9
sBar
->
addPermanentWidget
(
label2
);
```


## 使用UI设计 ### 1. 设计
（1）添加子菜单项时不能输入中文，是因为这时会生成默认类名，先输入英文然后在属性面板修改Text属性即可
（2）可以在Action Editor窗口看到添加的Action，将其拖动到菜单栏上可以快捷添加快捷方式
（3）ToolBar各种属性如停靠，浮动都可以在属性面板修改 ### 2.代码
使用ui->的方式找到控件
```
ui->actionnew->setIcon(QIcon("/home/zhangweizhen/Pictures/test.jpg"));

1
 
1
ui
->
actionnew
->
setIcon
(
QIcon
(
"/home/zhangweizhen/Pictures/test.jpg"
));
```
这里使用的是绝对路径，若要添加资源文件，将其复制到工程目录右键“添加新文件”，选择资源文件，然后为资源文件取名，这里为res


进入资源编辑界面

添加->前缀，添加->文件 选中要添加的资源文件

索引资源文件：格式：:":前缀文件名"

如
```
ui->actionnew->setIcon(QIcon(":/test.jpg"));


1
 
1

```