# Matplotlib
 
[TOC]
 
## 入门
 
### 1. 基本绘图
 
在jupyter notebook中设置`％matplotlib inline`，准备好数据（x和y都为数字列表），调用一些api进行绘图
 
#### （1）折线图
 
```python
import matplotlib.pyplot as plt

plt.plot(x_data,y_data)
plt.show()
```
 
#### （2）散点图
 
```python
plt.scatter(x_data,y_data)
plt.show()
```
 
#### （3）条形图
 
离散的数据项进行数量统计，频率统计
 
```python
plt.bar(x_data,y_data，width=0.3)
# plt.bar(x_data,y_data,height=0.3) 横向条形图
plt.show()
```
 
> 需要绘制多个条形图时，需要依次将对比的第n组数据的横坐标后移width*n个距离，xticks使用中间的那个
 
#### （4）直方图
 
统计连续变化的数据项，参数也与其他统计图不同，只需要x_data和分组数
 
组数的计算:
$$
组数=\frac{极差}{组距}=\frac{max-min}{bin\_width}
$$
100以内数据5-12组，更多的数据根据数据离散程度选择组距计算出组数
 
```python
plt.hist(x_data,3)
plt.show()
```
 
 
 
### 2. 中文图示
 
使用`fc-list :lang=zh`查看支持中文的字体文件，复制到项目目录fonts文件夹中
 
```python
import random
from matplotlib import pyplot as plt
from matplotlib import font_manager
 
my_font = font_manager.FontProperties(fname="fonts/NotoSansCJK-Bold.ttc")
 
x = range(0,120)
y = [random.randint(20,35) for i in range(120)]
 
plt.figure(figsize=(20,8),dpi=80)
plt.plot(x,y)
 
_xtick_labels = ["10点{}分".format(i) for i in range(60)]
_xtick_labels += ["11点{}分".format(i) for i in range(60)]
plt.xticks(list(x)[::3],_xtick_labels[::3],rotation=45,fontproperties=my_font)
plt.show()
```
 
### 3. 设置描述信息
 
#### （1）x轴标签
 
```python
plt.xticks(x_data,["当日{}点".format(x) for x in x_data],fontproperties=my_font,rotation=45)
 
plt.xlabel("时间",fontproperties=my_font)
plt.ylabel("温度",fontproperties=my_font)
plt.title("气温变化图",fontproperties=my_font)
```
 
> x_data是一个数字列表，实际是横坐标，如果要显示文字的类别，需要使用`x_ticks()`将其对应替换为字符串
 
#### （2）图例
 
```python
plt.scatter(x_data,y_data,label="气温")
plt.legend(loc="upper left",prop=my_font)
plt.show()
```
 
#### （3）网格
 
```python
plt.grid(alpha=0.3)
```
 
 
 
###  4. 保存图片
 
```python
plt.savefig("./fig.png")
```
 
> 这句代码要在`plt.show()`之前，否则在 `plt.show()` 后调用了 `plt.savefig()` ，`plt.show()` 后实际上已经创建了一个新的空白的图片（坐标轴），调用 `plt.savefig()` 会保存一张空白图片。