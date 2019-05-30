```
import pandas as pd
import numpy as np
```



### 创建Series

In [12]:

```
a = pd.Series(range(10))
b = pd.Series({"username":"Ha","password":"123"})
print(a)
print("·"*20)
print(b)
```



```
0    0
1    1
2    2
3    3
4    4
5    5
6    6
7    7
8    8
9    9
dtype: int64
····················
username     Ha
password    123
dtype: object
```



### 索引

In [14]:

```
a = pd.Series(range(5),list("abcde"))
```

In [16]:

```
a["b"]
```

Out[16]:

```
1
```

In [17]:

```
a[1] #对1维的Series，通过索引和位置都可以
```

Out[17]:

```
1
```

In [18]:

```
a[:3]
```

Out[18]:

```
a    0
b    1
c    2
dtype: int64
```

In [21]:

```
a[[1,3]] #a[["b","d"]]
```

Out[21]:

```
b    1
d    3
dtype: int64
```

In [26]:

```
a[["b","f"]]
```



```
c:\program files\python36\lib\site-packages\pandas\core\series.py:851: FutureWarning: 
Passing list-likes to .loc or [] with any missing label will raise
KeyError in the future, you can use .reindex() as an alternative.

See the documentation here:
https://pandas.pydata.org/pandas-docs/stable/indexing.html#deprecate-loc-reindex-listlike
  return self.loc[key]
```

Out[26]:

```
b    1.0
f    NaN
dtype: float64
```



Series对象本质上由两个数组构成，一个数组构成对象的键，一个数组构成对象的值



### DataFrame

In [31]:

```
df = pd.DataFrame(np.arange(20).reshape(4,5))
df
```

Out[31]:

|      |    0 |    1 |    2 |    3 |    4 |
| ---: | ---: | ---: | ---: | ---: | ---: |
|    0 |    0 |    1 |    2 |    3 |    4 |
|    1 |    5 |    6 |    7 |    8 |    9 |
|    2 |   10 |   11 |   12 |   13 |   14 |
|    3 |   15 |   16 |   17 |   18 |   19 |

In [34]:

```
df = pd.DataFrame([{"name":"XiaoMing","age":"20"},{"name":"xiaohong","age":15},{"name":"XiaoHua"}])
df
```

Out[34]:

|      |  age |     name |
| ---: | ---: | -------: |
|    0 |   20 | XiaoMing |
|    1 |   15 | xiaohong |
|    2 |  NaN |  XiaoHua |

In [38]:

```
df.info()
```



```
<class 'pandas.core.frame.DataFrame'>
RangeIndex: 5999 entries, 0 to 5998
Data columns (total 2 columns):
0       5999 non-null int64
LZGZ    5999 non-null object
dtypes: int64(1), object(1)
memory usage: 93.8+ KB
```

In [39]:

```
df.describe()
```

Out[39]:

|       |           0 |
| ----: | ----------: |
| count | 5999.000000 |
|  mean | 3000.000000 |
|   std | 1731.906464 |
|   min |    1.000000 |
|   25% | 1500.500000 |
|   50% | 3000.000000 |
|   75% | 4499.500000 |
|   max | 5999.000000 |

In [41]:

```
df.sort_values(by="col_name",ascending=True)
```

In [44]:

```
# 方括号写数字，表示对行进行操作（结果是一个DataFrame），写字符串表示对列进行操作 （结果是一个Series）
df[:10] # 取前10行
```

Out[44]:

|      |    0 | LZGZ |
| ---: | ---: | ---: |
|    0 |    1 | ELCC |
|    1 |    2 | WKQZ |
|    2 |    3 | EAAS |
|    3 |    4 | KFRK |
|    4 |    5 | OZLY |
|    5 |    6 | PBGN |
|    6 |    7 | LCKK |
|    7 |    8 | IPIV |
|    8 |    9 | WTTQ |
|    9 |   10 | UGNG |



### 除了直接[]外，pandas提供了优化过的选择方式，可以同时对行列进行选择

- df.loc 通过标签索引数据
- df.iloc 通过位置获取数据
  注意，使用loc[row,col]的方式选中行和列，“[]”是闭合的，和np[1:2]无法选中第二行不同

In [56]:

```
df = pd.DataFrame(np.arange(12).reshape(3,4),index=list("abc"),columns=list("vxyz"))
df.loc["a","x"] #a行x列，这种取法和numpy中的切片一样了
print(df.loc["a",:])
```



```
v    0
x    1
y    2
z    3
Name: a, dtype: int32
```

In [58]:

```
df.loc[["a","b"]]# == df.loc[["a","b"],:]
```

Out[58]:

|      |    v |    x |    y |    z |
| ---: | ---: | ---: | ---: | ---: |
|    a |    0 |    1 |    2 |    3 |
|    b |    4 |    5 |    6 |    7 |

In [59]:

```
df.iloc[[0,1]]
```

Out[59]:

|      |    v |    x |    y |    z |
| ---: | ---: | ---: | ---: | ---: |
|    a |    0 |    1 |    2 |    3 |
|    b |    4 |    5 |    6 |    7 |

In [61]:

```
df.iloc[:,[2,1]] # 调整列的顺序
```

Out[61]:

|      |    y |    x |
| ---: | ---: | ---: |
|    a |    2 |    1 |
|    b |    6 |    5 |
|    c |   10 |    9 |



### 布尔索引

In [65]:

```
df[(df["v"]>5)&(df["v"]<10)]
df[(df["v"]<5)|(df["v"]>10)]
```

Out[65]:

|      |    v |    x |    y |    z |
| ---: | ---: | ---: | ---: | ---: |
|    c |    8 |    9 |   10 |   11 |



### Pandas读取外部数据

In [67]:

```
df = pd.read_csv("./labels.csv")
# df = pd.read_clipboard() # 从剪切板获取数据
print(df.head())
print("*"*100)
print(df.tail())
```



```
   0  LZGZ
0  1  ELCC
1  2  WKQZ
2  3  EAAS
3  4  KFRK
4  5  OZLY
****************************************************************************************************
         0  LZGZ
5994  5995  TKKM
5995  5996  ZIRO
5996  5997  ZQWQ
5997  5998  QWDQ
5998  5999  USNP
```



### 字符串方法

In [71]:

```
df.iloc[:,1].str.split("C").head()
```

Out[71]:

```
0    [EL, , ]
1      [WKQZ]
2      [EAAS]
3      [KFRK]
4      [OZLY]
Name: LZGZ, dtype: object
```

In [75]:

```
df.iloc[:,1].str.contains("W").head(10)
```

Out[75]:

```
0    False
1     True
2    False
3    False
4    False
5    False
6    False
7    False
8     True
9    False
Name: LZGZ, dtype: bool
```



### 数据缺失处理

In [78]:

```
df.dropna(axis=0,how="all").head() # 按行删除全为NaN的记录
```

Out[78]:

```
3000.0
```

In [ ]:

```
df.fillna(0) # NaN的记录填充为0
df.fillna(df.["Count"].mean()) # 填充NaN为均值 （Pandas计算均值的时候是不会计算NaN的，和numpy不同，因此如果被填充了0应该df[df==0]=np.nan）
```