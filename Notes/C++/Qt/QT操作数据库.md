# QT操作数据库
 
QT中数据库的操作非常直观，都是直接执行sql语句。
 
## 入门
 
### 1. 在.pro文件中添加组件
 
```c++
QT       += core gui sql
```
 
### 2. 需要一个库文件libmysql.dll
 
在mysql的安装目录lib下可以找到（参考C:\Program Files\MySQL\MySQL Server 8.0\lib\libmysql.dll）,复制到qt的编译环境中（参考C:\Qt\Qt5.12.1\5.12.1\msvc2017_64\bin）。另外，QT的运行环境也要换成MSVC2017_64，不能使用32位，否则会报`QSqlDatabase: QMYSQL driver not loaded`的错误。
 
### 3.  编写代码
 
```c++
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
 
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("root");
    db.setDatabaseName("test");
 
    if(!db.open())
    {
        return;
    }
 
    QSqlQuery query;
    //创建表
    query.exec("create table tutorials_tbl(   tutorial_id INT NOT NULL AUTO_INCREMENT,   tutorial_title VARCHAR(100) NOT NULL,   tutorial_author VARCHAR(40) NOT NULL,   submission_date DATE,   PRIMARY KEY ( tutorial_id ));");
    // 插入数据
    query.exec("INSERT INTO tasks(subject,start_date,end_date,description)VALUES ('任务-4','2017-03-01','2017-03-02','Description 4')");
    // 删除数据
    query.exec(QString("delete from tasks where task_id=%1").arg("4"));
    // 查询数据
    query.exec("select * from tasks");
 
    while (query.next()) {
        int taskId = query.value(0).toInt();
        QString taskName = query.value(1).toString();
        QString taskEnd = query.value("end_date").toString();//使用序号和字段名称都有效
 
        qDebug()<<taskId<<"\t"<<taskName<<"\t"<<taskEnd;
    }
 
 
    // 开启事务
    QSqlDatabase::database().transaction();//单例模式获取上面创建的数据库
    // 提交事务
    QSqlDatabase::database().commit();
    // 回滚事务
    QSqlDatabase::database().rollback();
}
 
MainWindow::~MainWindow()
{
    delete ui;
}
```