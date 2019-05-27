# Numpy
 
## 入门
 
[TOC]
 
### 1. 创建数组
 
```python
import numpy as np
data = np.arange(20).reshape(4,5)
 
a = np.array([0,1,2,3,4,5])
b = np.array(range(6))
c = np.arange(6)
```
 
### 2.  数据操作
 
```python
a.dtype #获取a中数据的类型
a.astype("float32") #改变a中数据类型
np.round(a,2) #保留两位小数
```
 
### 3. 随机函数
 
```python
np.random.randint(1,100,10) # 在1-100之间随机生成10个数
```
 
 
 
## 基本概念
 
### 1. 数组形状
 
**维度是数据组织形式**
 
shape中有几个数，数组就是几维的，哪怕是[10,1]也是2维的，(10,)才是1维的。对向量而言，一个向量有几个元素就是几维，a = [1,2,3]是三维的。
 
```python
a = np.arange(10)
print(a.shape)
a = np.arange(10).reshape(2,5) # 也可以传入元组a.reshape((2,5))
print(a.shape)
a = np.arange(20).reshape(2,2,5)
a.flatten() # 将数据变成1维
```
 
### 2.  广播
 
如果两个数组的后缘维度（从末尾开始算起的维度）的轴长度相同或其中一方的长度为1，则认为他们是广播兼容的。广播会在缺失或长度为1 的维度进行
如(4,3,2)和(3,2)
 
```python
array([[10, 12, 14, 16, 18],
       [20, 22, 24, 26, 28]])
print(a+2)
```
 
### 3. NaN和INF
 
```python
print(np.count_nonzero(a!=a)) # 用nan!=nan来统计nan的个数，结果和np.isnan(a)一样
 
# nan和任何值计算结果都为nan
a = np.arange(20,dtype=float).reshape(4,5)
a[2,2]=np.nan
print(np.sum(a,axis=0)) # axis=？,在结果中那个维度就消失了，如(2,3,4),axis=1,则结果为(2,4)
```
 
 
 
## 矩阵操作
 
### 1.  转置
 
```python
a.transpose()
a.T
a.swapaxes(1,0)
```
 
### 2. 索引和切片
 
```python
a = np.arange(30).reshape(5,6)
a_row1 = a[0]
# 取多行
a_row_2_end = a[2:]
# 取不连读的多行
a_sub = a[[1,2,4]]
print(a_sub)
```
 
通用选取形式：a[row,col]
 
```python
a[[0,1,2],[1,2,3]] #取多个不相邻的点(0,0),(1,2),(2,3) ，逗号前是行，逗号后是列
```
 
###  3. 数据筛选 布尔索引
 
```python
a = np.arange(30).reshape(5,6)
print(a>10)
a[a>10]=1 # 将a中大于10的数改为1
np.where(a<10,0,10) # 三元运算符，相当于a[?]=0 if t<10 else 10
np.clip(0,10) # a[?]=0 if a[?]<0;a[?]=10 if a[?]>10;else a[?]=a[?]
```
 
### 4. 统计
 
需要注意的是参数`axis`，默认为None在所有维度上进行运算。当指定了在某个维度进行运算，其他维度不变，如果不设置`keepdims=True`那个运算的维度会消失，设置保持维度后其维度变成1。
 
- np.sum()
- np.mean() #平均值
- np.median() # 中值
- np.max()
- np.min()
- np.ptp() # 极值（最大值和最小值之差）
- np.std() # 标准差
 
```python
In [1]: import numpy as np
 
In [2]: data = np.arange(20).reshape(4,5)
 
In [3]: data.sum(axis=0)
Out[3]: array([30, 34, 38, 42, 46])
 
In [4]: data.sum(axis=1)
Out[4]: array([10, 35, 60, 85])
 
In [5]: data.sum(axis=1,keepdims=True)
Out[5]:
array([[10],
       [35],
       [60],
       [85]])
 
In [6]: data.sum(axis=1,keepdims=True).shape
Out[6]: (4, 1)
 
In [7]: data.sum(axis=1).shape
Out[7]: (4,)
```
 
 
 
### 5. 拼接
 
- np.vstack()
 
竖直拼接 (在每一列拼接)
 
- np.hstack()
 
水平拼接（在每一行拼接）
 
```python
a = np.arange(20).reshape(4,5)
b = np.arange(100,120).reshape(4,5)
print("vstack:")
print(np.vstack((a,b)))
print("hstack:")
print(np.hstack((a,b)))
```
 
### 6. 行交换和列交换
 
```python
a = np.arange(20).reshape(4,5)
print(a)
a[[1,2],:]=a[[2,1],:] #交换第二行和第三行
print(a)
```
 
###  7. 其他常用api
 
```python
# 获取最大最小值的位置
np.argmax()
np.argmin()
# 创建一个全为0的数组
np.zeros()
# 创建一个全为1的数组
np.ones()
# 创建一个n阶单位矩阵
np.eye(3)
 
# 随机函数
np.random.seed(10) # 随机种子，指定后每次产生的随机数都相同
np.random.rand(2,3) # 均匀分布 取值[0,1)
np.random.randn(2,3) # 标准正态分布
np.random.uniform(0,10,(2,3))
np.random.normal(0,0.1,(2,3))
```
 
## 数组的运算
 
###  1. 矩阵乘法
 
```python
np.dot(a,b)
```
 
### 2. 矩阵内积
 
```python
np.multiply(a,b)
a*b
```
 
## 复制和视图
 
深拷贝和浅拷贝
 
- a = b
  完全不复制
- a = b[:]
  视图，前面交换两列用到了，创建新的对象但相互影响
- a = b.copy()
  复制，a、b互不影响
 
## 文件读写
 
### 1. 读取
 
```python
np.loadtxt(fname, dtype, comments='#', delimiter=None, converters=None, skiprows=0, usecols=None, unpack=False)
# skiprows 跳过哪些行（如第一行可能是名字）
# usecols 使用哪些列
# unpack 是否转置，转置之后可以x, y, z = loadtxt(...)这样的语法
```
 
### 2. 写入
 
```python
np.savetxt(frame,array,fmt='%.18e,delimiter=None')
# frame：文件，字符串或产生器，可以是.gz或.bz2的压缩文件
# array：存入文件的数组
# fmt：写入文件的格式，如：%d,%.2f,%.18e（保留18位的科学计数法）
# delimiter：分割字符串，默认是任何空格
```
 