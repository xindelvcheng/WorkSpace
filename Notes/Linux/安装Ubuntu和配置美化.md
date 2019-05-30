### 1. 安装
使用English安装，安装简体中文语言包,使用`root密码sudo passwd`设置

### 2. 更换软件源

### 3. 删除不必要的软件
```
sudo apt-get remove libreoffice-common  
sudo apt-get remove unity-webapps-common  
sudo apt-get remove thunderbird totem rhythmbox empathy brasero simple-scan gnome-mahjongg aisleriot gnome-mines cheese transmission-common gnome-orca webbrowser-app gnome-sudoku  landscape-client-ui-install
sudo apt-get remove onboard deja-dup 
```

### 4. 安装日常软件
 - 
```
sudo apt install -f
sudo apt-get install wps-office  
```
>禁用Ctrl + Space 切换输入法
>- 点击任务栏搜狗图标选择设置
>- 高级》》Fcitx》》打开Fcitx配置界面》》选择全局配置选项卡》》更改切换激活/非激活输入法

 - 安装谷歌浏览器
```
sudo wget http://www.linuxidc.com/files/repo/google-chrome.list -P /etc/apt/sources.list.d/  
wget -q -O - https://dl.google.com/linux/linux_signing_key.pub  | sudo apt-key add -
sudo apt-get update
sudo apt-get install google-chrome-stable
```
 - 安装Texlive
   1. 为了使用图形化安装界面，需要安装perl的tk组件
   `sudo apt install perl-tk`
   2. 挂载Texlive2017.iso
   3. 以GUI打开
   `sudo ./install-tl -gui`
   4. 安装
   5. 配置环境变量
   ```
    sudo vim /etc/profile
   
    #texlive
    export PATH=$PATH:/usr/local/texlive/2017/bin/x86_64-linux
    ```

### 5. 美化
- 安装flatabulous-theme主题
```
sudo add-apt-repository ppa:noobslab/themes
sudo apt-get update
sudo apt-get install flatabulous-theme
```

- 安装mac主题 
 ```
 sudo add-apt-repository ppa:noobslab/macbuntu
 sudo apt-get update
 sudo apt-get install macbuntu-os-icons-lts-v7
 sudo apt-get install macbuntu-os-ithemes-lts-v7
 ```
 - 管理软件
 ```
sudo apt install unity-tweak-tool
```

### 6. 驱动
- 声卡驱动
```
sudo apt install pavucontrol  
```

>配置耳机
![image](https://img-blog.csdn.net/20170315142644222?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvdzU5ODc1MzQ2OA==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)

### 7. 搭建开发环境
- ### Common
```
sudo apt install git

git config --global user.name "xindelvcheng"
git config --global user.email "2604627950@qq.com"

git config --list
```

- ### Java
- ### Python


### 其他

- ### Ubuntu快捷键
  - 多桌面
    >设置》》外观》》打开工作区
   
    ```
    Ctrl + Shift + Alt + 上下左右   将当前窗口移动到其他工作区 
    Ctrl + Alt + 上下左右           切换工作区
    Super + S                      显示所有工作区
    ```
  - 窗口
  ```
  Alt + F4                          关闭当前页面
  ```