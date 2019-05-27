### Linux常用指令
- ls
- cp  
    - [-r] 递归的复制文件夹  
    - /cp 覆盖不提示
- cat 
    - [-n] 显示行号
    - `cat -n /etc/profile | more`   
    more是基于vi的，也可以使用Ctrl + F向下翻页，Ctrl + B向上翻页。less命令也可以用来查看文本
>用户信息存放在/etc/passwd下，口令存放在/etc/shadow中，组信息存放在/etc/group中
- <font color= "red" size="5">\<和<<</font>  
重定向和追加
- echo

`echo $PATH`输出环境变量
- head & <font color= "red" size="5">tail</font>
    - head查看文档前十行 [-n]制定查看前几行
    - <font color="red">tail -f 文件,实时追踪文件更新,多用于查看日志</font>
- ln -s [文件名] [软连接名]
软连接
-   curl -LO http://download.tensorflow.org/example_images/flower_photos.tgz
下载，-L更随重定向
- history  
查看历史指令，使用`history 10`查看最近十条指令，使用`！[序号]`来执行制定序号的历史指令
- date  
`date +"%Y-%m-%d %H:%M:%S"`显示时间  
`date -s "2018-5-15 11:32:27"`设置系统时间
- cal  
`cal 2018`显示一整年日历
- <font color="red" size="5">find</font>
查找文件
    - find [dic] -name [*filename]
    `find /etc -name profile` 可以搜索目录及子目录
    - find [dic] -user [*username]
    `find /etc -user root`按文件的拥有者搜索
    - find [dic] -size [【+,-,n】*M]按文件大小搜索
- locale 定位文件
    1. 使用`updatedb`创建索引库
    2. 使用`locate filename` 快速定位文件
- grep 搜索，常与管道一起使用  
    - [-n]显示行号
    - [-i]忽略大小写  
    `cat /etc/profile | grep -ni PATH`
- gzip/gunzip/zip/unzip  
`zip xxx.zip demo1.py demo2.c`
    - r 压缩目录
    - d 解压到目录
- tar打包和解压 
    - 打包并压缩`tar -zcvf demo.tar.gz 1.py 2.java 3.c`
        >对整个文件夹同样命令`tar -zcvf home.tar.gz /home/`

    - 解压`tar -zxvf demo.tar.gz -C [destination]`
- chown 改变文件所有者
`chown root /etc/profile`  
`chown -R /etc` 递归地改变文件夹下所有的文件和文件夹
`chown newowner:newgroup filename`同时改变文件的所有者和所有组
- chgrp 改变文件所有组
`chgrp 组名 文件名`
- usermod 改变用户配置  
`usermod -g 组名`改变用户组名  
>`usermod -d 文件夹名`改变用户登录家目录  
>Linux中目录也是一种特殊文件(Linux中一切皆文件)，大小为4096

- chmod 修改权限  
`chmod u=rwx,g=rw,o=r filename`  
常用：`chmod 754 filename`等价于上面  
`chmod o+w filename`
- chgrp 改变文件所在组  
chgrp newgroup filename
- crontab 任务调度  
    - 参数  
`crontab -e` 设定  
`crontab -l`查询  
`crontab -r`删除
    - 格式  
*　　*　　*　　*　　*　　command  
分　时　&nbsp;&nbsp;日　&nbsp;月　&nbsp;&nbsp;周　&nbsp;&nbsp;命令

- lsblk(老师不离开)
`lsblk [-f]`查看硬盘挂载情况
>Linux下无论多少块硬盘，都是使用挂载到目录的方式
- df -lh 查看磁盘使用情况
- du -ach 查看目录占用磁盘   

- 磁盘管理实例
    - 查看/home下文件个数  
    `ls -l /home | grep "^-" | wc -l`
    - 查看/home下文件和其子文件夹下文件总数  
    `ls -lR /home | grep "^-" | wc -l`
- ps/top 进程管理   
    - `ps -aux`   查看所有进程  
`ps -ef`    查看父进程  
    - top是一个交互动态监控进程管理界面，按u设定监控用户，按k和pid杀死进程

- kill杀死进程
`kill -9 pid`强制杀死进程
>`kill gedit`支持通配符  
`pstree -pu` 查看进程树
- service/systemctl(CentOs7.0之后)服务管理
[-start / stop /restart /reload /status]  
`service iptables status`查看防火墙状态
- chkconfig 给每个服务各个运行级别设置
- netstat 网络管理
`netstat -anp`
- rpm 包管理  
`rpm -qa | grep firefox`
-   解压文件
```
unzip -O cp936 xxx.zip
```