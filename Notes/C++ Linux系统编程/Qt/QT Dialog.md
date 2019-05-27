# Qt中的对话框
[TOC]
## 模态对话框和非模态对话框
当打开对话框后不能对其他窗口进行操作的为模态对话框，否则为非模态对话框；
### 1. 弹出模态对话框
```c++
connect(ui->actionnew,&QAction::triggered,this,[=](){
    QDialog dlg(this);
    dlg.exec();//阻塞
});
```
### 2.弹出非模态对话框
```c++
QDialog *dlg2 = new QDialog(this);
dlg2->resize(200,100);
dlg2->show();
// 设置对话框关闭时释放对象
dlg2->setAttribute(Qt::WA_DeleteOnClose);
```
>非模态的对话框不会阻塞，如果在栈上申请空间会一闪而过。
## 标准对话框
Qt为了简化开发内置的对话框

### 1. QMessageBox

```c++
// 问题
QMessageBox::question(this,"提问","是否？",QMessageBox::Save|QMessageBox::Cancel,QMessageBox::Save);
// 信息
QMessageBox::information(this,"提示","Qt程序");
// 警告
QMessageBox::warning(this,"警告","警告信息");
// 错误
QMessageBox::critical(this,"错误","错误信息");
```

通过返回值来确定在弹出的对话框点击的是哪个按钮（确定|退出）

```c++
if(QMessageBox::Save==QMessageBox::question(this,"提问","是否？",QMessageBox::Save|QMessageBox::Cancel,QMessageBox::Save))
{
qDebug()<<"保存";
}
```

### 2. QColorDialog

颜色选择对话框

```c++
QColor color= QColorDialog::getColor();
int red = color.red();
int green = color.green();
int blue = color.blue();
qDebug()<<red<<"\t"<<green<<"\t"<<blue;
```



### 3. QFileDialog

文件对话框

```c++
QString filePath = QFileDialog::getOpenFileName(this,"打开文件","~","(*.txt *.png)");
```