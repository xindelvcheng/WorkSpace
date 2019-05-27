# Layout Qt中的布局和控件
[TOC]
## 入门：使用UI设置界面
1.拖拽控件到窗口上

2.拖拽Widget到窗口上，点击水平布局或垂直布局（不推荐直接使用布局，而是使用容器） 

3.添加弹簧（没有在布局中时弹簧无效），如果需要固定长度的弹簧，修改为sizeType为Fixed

4.需要修改点击“打破布局”按钮

5.几行几列的布局可以使用栅格布局（如用户名和密码和它们的输入框）

6.设置窗口的最大宽度高度和最小宽度高度为同一个值可以让窗口不能缩放

## 常用控件
### 1. QPushButton
按钮
#### （1）. 拖拽按钮到窗口上

#### （2）. 设置Icon
点击Icon -> 选择资源
￼

### 2. ToolButton
多用于显示图片
￼
### 3. RadioButton

单选框，同一组放在容器GroupBox中

### 4. CheckBox

复选框

```c++
connect(ui->checkBox,&QCheckBox::stateChanged,this,[](int status){
qDebug()<<status;//选中为2，不选中为0，tristatus半选中状态
});
```

### 5. ListWidget

像Android中的ListView

```c++
QListWidgetItem *item =new QListWidgetItem("哈哈啊哈哈哈");
item->setTextAlignment(Qt::AlignHCenter); //设置文字居中
ui->listWidget->addItem(item);

QStringList sl;//相当于List<string>
sl<<"一二三四五"<<"六七八九十";
ui->listWidget->addItems(sl);
```

### 6. TreeWidget

树状目录

```c++
ui->treeWidget->setHeaderLabels(QStringList()<<"文件夹");
QTreeWidgetItem *rootDir = new QTreeWidgetItem(QStringList()<<"/");
ui->treeWidget->addTopLevelItem(rootDir);

QTreeWidgetItem *rootBin = new QTreeWidgetItem(QStringList()<<"bin");
QTreeWidgetItem *rootUsr = new QTreeWidgetItem(QStringList()<<"usr");
rootDir->addChild(rootBin);
rootDir->addChild(rootUsr);
```

### 7. TableWidget

表格

```c++
// 设置列
QStringList list;
list<<"事件"<<"地点"<<"时间";
ui->tableWidget->setColumnCount(list.size());
ui->tableWidget->setHorizontalHeaderLabels(list);
// 设置行
ui->tableWidget->setRowCount(5);
// 按位置添加记录
ui->tableWidget->setItem(0,0,new QTableWidgetItem("事件1"));
// 插入一个空行
ui->tableWidget->insertRow(0);
// 判断是否有某个元素
bool isExist = ui->tableWidget->findItems("字符串",Qt::MatchExactly).empty();
// 删除一行记录
int row = ui->tableWidget->findItems("字符串",Qt::MatchExactly).first()->row();
ui->tableWidget->removeRow(row);
```

## 其它控件
### 1. ScrollArea



滚动
### 2.ToolBox

￼分组
右键“插入页”添加新的标签页
### 3. TabWidget

右键“插入页”添加新的标签页

### 4. StackedWidget
像Android中的Fragment，需要自己添加按钮通过`setCurrentIndex()`来切换不同的页面。

>如果控件显示不全，查看是否是因为没有设置布局

### 5.Combo Box

下拉框，通过`addItem()`来添加选项

### 6.Label

label不仅可以显示文字，还可以显示图片和gif

#### 显示图片

```c++
ui->labelImage->setPixmap(QPixmap(":/Image/test.png"));
```

#### 显示动图

```c++
QMovie *movie = new QMovie(":/Image/test.gif");
ui->labelMoview->setMovie(moviw);
movie->start();
```

> 需要引入头文件<QMovie>