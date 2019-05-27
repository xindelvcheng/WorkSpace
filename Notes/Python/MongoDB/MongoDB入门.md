# MongoDB入门

[TOC]

## 非关系型数据库

不需要考虑数据之间一对一一对多多对多等关系，存成一个大字典。易扩展每条记录格式不需要一致，大数据下不需要多表查询IO压力比较小。缺点是重复的数据很多，占用空间大。

## Mongodb安装

```bash
$ sudo apt install mongodb
```

## Mongodb概念

| SQL术语/概念 | MongoDB术语/概念 | 解释/说明                           |
| ------------ | ---------------- | ----------------------------------- |
| database     | database         | 数据库                              |
| table        | collection       | 数据库表/集合                       |
| row          | document         | 数据记录行/文档                     |
| column       | field            | 数据字段/域                         |
| index        | index            | 索引                                |
| table joins  |                  | 表连接,MongoDB不支持                |
| primary key  | primary key      | 主键,MongoDB自动将_id字段设置为主键 |



## 使用

命令行输入`mongo`

### 1. 查看数据库

```bash
$ show dbs
$ show databases
```

### 2. 新建数据库

使用use，如果数据库不存在，则创建数据库，否则切换到指定数据库。

```bash
$ use DATABASE_NAME
```

### 3. 查看当前所在数据库

```bash
$ db
```

> 使用use选择数据库后db代表当前数据库

### 4. 删除数据库

```bash
$ db.dropDatabase()
```

### 5. 创建表

```bash
> use test
switched to db test
> db.createCollection("runoob")
{ "ok" : 1 }
```

### 6. 插入数据

```
>db.col.insert({title: 'MongoDB 教程', 
    description: 'MongoDB 是一个 Nosql 数据库',
    by: '菜鸟教程',
    url: 'http://www.runoob.com',
    tags: ['mongodb', 'database', 'NoSQL'],
    likes: 100
})
```

这里的col是collection不是column

### 7. 查看所有数据

```
> db.col.find()
{ "_id" : ObjectId("56064886ade2f21f36b03134"), "title" : "MongoDB 教程", "description" : "MongoDB 是一个 Nosql 数据库", "by" : "菜鸟教程", "url" : "http://www.runoob.com", "tags" : [ "mongodb", "database", "NoSQL" ], "likes" : 100 }
> 
```

### 8.修改数据

```
>db.col.update({'title':'MongoDB 教程'},{$set:{'title':'MongoDB'}})
WriteResult({ "nMatched" : 1, "nUpserted" : 0, "nModified" : 1 })   # 输出信息
> db.col.find().pretty()
{
        "_id" : ObjectId("56064f89ade2f21f36b03136"),
        "title" : "MongoDB",
        "description" : "MongoDB 是一个 Nosql 数据库",
        "by" : "菜鸟教程",
        "url" : "http://www.runoob.com",
        "tags" : [
                "mongodb",
                "database",
                "NoSQL"
        ],
        "likes" : 100
}
>
```



### 9. 删除记录

```
>db.col.remove({'title':'MongoDB 教程'})
WriteResult({ "nRemoved" : 2 })           # 删除了两条数据
```

### 10. 查询

```
> db.col.find({"by":"菜鸟教程", "title":"MongoDB 教程"}).pretty()
```

类似于 WHERE 语句：`WHERE by='菜鸟教程' AND title='MongoDB 教程'`，pretty() 方法以格式化的方式来显示所有文档。