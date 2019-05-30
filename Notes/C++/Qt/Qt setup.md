- Ubuntu下安装Qt
>[下载Qt](http://download.qt.io/archive/qt/)  
```
2.直接运行可执行文件安装Qt
2.安装openGL
sudo apt-get install mesa-common-dev 

sudo apt-get install libglu1-mesa-dev -y
```


编译出错
```
1.Could not determine which "make" command to run. Check the "make" step in the build configuration.
sudo apt-get install cmake g++

然后在”选型“里的”构建和运行“这一项，对”构建套件 Kit“进行重新设置。


2.cannot find -lGL

sudo apt-get install libgl1-mesa-dev
```