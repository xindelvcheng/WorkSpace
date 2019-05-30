### 创建数组

In [2]:

```
import numpy as np
a = np.array([0,1,2,3,4,5])
b = np.array(range(6))
c = np.arange(6)
```

In [3]:

```
a.dtype #获取a中数据的类型
a.astype("float32") #改变a中数据类型
np.round(a,2) #保留两位小数
```

Out[3]:

```
array([0., 1., 2., 3., 4., 5.], dtype=float32)
```



### 数组的形状

In [16]:

```
a = np.arange(10)
print(a.shape)
print(type(a.shape))
a = np.arange(10).reshape(2,5) # 也可以传入元组a.reshape((2,5))
print(a.shape)
a = np.arange(20).reshape(2,2,5) #shape中有几个数，数组就是几维的，哪怕是[10,1]也是2维的，(10,)才是1维的
a.flatten() # 将数据变成1维
```



```
(10,)
<class 'tuple'>
(2, 5)
(20,)
```



### 广播

In [18]:

```
a = np.arange(10).reshape(2,5)
a+2
a/2
a+ np.arange(10,20).reshape(2,5)
```

Out[18]:

```
array([[10, 12, 14, 16, 18],
       [20, 22, 24, 26, 28]])
```



如果两个数组的后缘维度（从末尾开始算起的维度）的轴长度相同或其中一方的长度为1，则认为他们是广播兼容的。广播会在缺失或长度为1 的维度进行 如(3,3,2)和(3,2)



### numpy读取写入文件

In [ ]:

```
np.loadtxt(fname, dtype, comments='#', delimiter=None, converters=None, skiprows=0, usecols=None, unpack=False)
# skiprows 跳过哪些行（如第一行可能是名字）
# usecols 使用哪些列
# unpack 是否转置
```



### 转置

In [5]:

```
a.transpose()

a.T

a.swapaxes(1,0)
```

Out[5]:

```
array([[ 0,  6, 12, 18],
       [ 1,  7, 13, 19],
       [ 2,  8, 14, 20],
       [ 3,  9, 15, 21],
       [ 4, 10, 16, 22],
       [ 5, 11, 17, 23]])
```



### 索引和切片

In [15]:

```
a = np.arange(30).reshape(5,6)
a_row1 = a[0]
# 取多行
a_row_2_end = a[2:]
# 取不连读的多行
a_sub = a[[1,2,4]]
print(a_sub)
```



```
[[ 6  7  8  9 10 11]
 [12 13 14 15 16 17]
 [24 25 26 27 28 29]]
```

In [19]:

```
a = np.arange(30).reshape(5,6)
# a[row,col]
print(a[:,1])
print("*"*100)
print(a[1:3,1:3]) # 取出来的值是int64类型
a[[0,1,2],[1,2,3]] #取多个不相邻的点(0,0),(1,2),(2,3) >>>逗号前是行，逗号后是列
```



```
[ 1  7 13 19 25]
****************************************************************************************************
7
```



### 布尔索引

In [24]:

```
a = np.arange(30).reshape(5,6)
print(a>10)
a[a>10]=1 # 将a中大于10的数改为1
np.where(a<10,0,10) # 三元运算符，相当于a[?]=0 if t<10 else 10
np.clip(0,10) # a[?]=0 if a[?]<0;a[?]=10 if a[?]>10;else a[?]=a[?]
```



```
[[False False False False False False]
 [False False False False False  True]
 [ True  True  True  True  True  True]
 [ True  True  True  True  True  True]
 [ True  True  True  True  True  True]]
```

Out[24]:

```
array([[ 0,  0,  0,  0,  0,  0],
       [ 0,  0,  0,  0, 10, 10],
       [10, 10, 10, 10, 10, 10],
       [10, 10, 10, 10, 10, 10],
       [10, 10, 10, 10, 10, 10]])
```



### nan和inf

In [5]:

```
a = np.nan
b = np.inf
print(type(a))
print(type(b))
```



```
<class 'float'>
<class 'float'>
```

In [8]:

```
# nan!=nan
a = np.arange(20,dtype=float).reshape(4,5)
a[2,2]=np.nan
a[3,1]=np.nan
print(np.count_nonzero(a!=a)) # 用nan!=nan来统计nan的个数，结果和np.isnan(a)一样
print("*"*100)
print(a)
```



```
2
****************************************************************************************************
[[ 0.  1.  2.  3.  4.]
 [ 5.  6.  7.  8.  9.]
 [10. 11. nan 13. 14.]
 [15. nan 17. 18. 19.]]
```

In [13]:

```
# nan和任何值计算结果都为nan
a = np.arange(20,dtype=float).reshape(4,5)
a[2,2]=np.nan
print(np.sum(a,axis=0)) # axis=？,在结果中那个维度就消失了，如(2,3,4),axis=1,则结果为(2,4)
```



```
[30. 34. nan 42. 46.]
```

In [ ]:

```
 
```