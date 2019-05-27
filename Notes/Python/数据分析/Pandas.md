# Pandas
 
## 入门
 
### 1. 创建Series
 
**Series可以看做一个定长的有序字典**,index可以看做key，value就是values
 
```
a = pd.Series(range(10))
b = pd.Series({"username":"Ha","password":"123"}) # 传入一个字典，指定索引
c = pd.Series(range(10),index=range(10,20)) # 指定索引
 
a.values # a中的数据，ndarray类型
a.index # a中的索引 Index类型
 
a["index"] # 取值
"index" in a # index是否在a中
```
 
### 2. 创建DataFrame
 
DataFrame像是一张表，可以通过二维的ndarray创建
 
```python
df1 = pd.DataFrame({"username":["Ha","la","ya"],"password":[1,2,3]}) #通过字典创建DataFrame，不指定索引，键为表头，一个值列表为一列
df2 = pd.DataFrame(np.arange(20).reshape(4,5)) # 通过二维数据创建表，不指定表头和索引
"""
Out[21]:
    0   1   2   3   4
0   0   1   2   3   4
1   5   6   7   8   9
2  10  11  12  13  14
3  15  16  17  18  19
"""
df2 = pd.DataFrame(np.arange(20).reshape(4,5),index=["第{}行".format(i) for i in range(4)],columns=["第{}列".format(i) for i in range(5)]) # 指定表头和索引
df2.index # 取表头
df2.columns # 取索引
df2.values # 取数据
df2.describe() # 数理统计
df2.T # 转置
df2.sort_values(by="第1列") # 一列中的数据排序
df2.sort_index(axis=1) # 按表头排序
```
 
### 3. 定位数据
 
使用方式和字典和列表有点像，使用`[]`
 
#### （1）iloc[行(index),列(index)]
 
```python
df2.iloc[[0],[0]] # 第0行第0列（DataFrame）
df2.iloc[0,0] # 第0行第0列（numpy.int32)
```
 
#### （2）loc[行，列]
 
通过标签选择
 
```python
df2.loc[:,["第1列","第2列"]]
```
#### （3）query
 
类似sql。
 
```python
df  = df.query("x>1.0 & x<1.25 & y>2.5 & y<2.75")
```
 
### 4.NaN处理
 
-     dropna (axis=0, how='any')
-     fillna (value=0.0)
### 5.读取和写入数据
#### （1）读取
` df = pd.read_csv( "df.csv" )   `
#### （2）写入
` df.to_csv( "df.csv" ) `
### 6.合并
` pd.concat([df,df2],ignore_index= True ) `或`pd.merge(df,df2,on=["id","name"],how="outer")`
 
### 7. 交叉表
 
推荐系统中会用到
 
```python
pd.crosstab(mt['user_id'],mt['user_id'])
```
 
## 数据处理
 
### 1. 时间戳
 
```python
time_value = pd.to_datatime(df['time'],unit='s')
time_value = pd.DatatimeIndex(time_value) # 转字典
```
 
### 2. 添加列
 
```python
df.loc['day'] = time_value.day
df['day'] = time_value.day # 复制一份day数据给df
```
 
> DataFrame用起来像字典
 
### 3. 删除列
 
```python
df = df.drop(['time'],axis=1) # pandas中1表示列
```
 
### 4. 分组和聚合
 
```python
grouped = df.groupby(by="Country")
df.groupby(by="Country").count().reset_index() # reset_index将分组用的字段返回数据中重新生成从1开始的id
```
 
得到的是DataFrameGroupBy对象，可以遍历和使用聚合方法。
 
- 遍历时每一个对象都是一个元组，第一个值为分组的值，第二个是分到组里的DataFrame
- 聚合方法:`grouped.count()`如果数据没有缺失，每一个字段都会统计到一样的值。可以选一个没有缺失的字段`grouped["col"].count()`
 
### 5. 包含
 
`df = df[df['place_id']].isin(counted.place_id)`
 
### 6. 使用字符串方法
 
对Series.str使用字符串方法`df.city.str.contains("六安")`