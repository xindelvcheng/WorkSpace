# Scikit-Learn入门
 
[TOC]
 
## 安装
 
```bash
$ pip install scikit-learn
import sklearn
```
 
## 入门
 
### 1. 特征抽取
 
在sklearn.feature_extraction中，将文本，字符串转为数据
 
#### (1). DictVectorizer字典特征数据抽取
 
字典字符串类别转one-hot，数值型回归。
 
```python
from sklearn.feature_extraction import DictVectorizer
 
dict = DictVectorizer(sparse=False)
data = dict.fit_transform(
    [{'city': '合肥', 'temperature': 30}, {'city': '六安', 'temperature': 20}, {'city': '北京', 'temperature': 25}])
print(dict.get_feature_names())
print(data)
```
 
>['city=六安', 'city=北京', 'city=合肥', 'temperature']
>[[ 0.  0.  1. 30.]
> [ 1.  0.  0. 20.]
> [ 0.  1.  0. 25.]]
 
#### (2). text.CountVectorizer 文本特征值化
 
所有文章的单词one-hot
 
```python
from sklearn.feature_extraction.text import CountVectorizer
 
dict = CountVectorizer()
data = dict.fit_transform(["Life is too short", "Life is too long"])
print(data.toarray())
```
 
中文:
 
```python
import jieba
" ".join(list(jieba.cut(str)))
```
 
#### (3). text.TfidfVectorizer 单词重要性
 
tf:出现次数
 
idf:log(总文档数量/单词出现文档数)
 
### 2. 特征预处理
 
在sklearn.preprocessing中
 
#### (1). 归一化
 
让数据影响程度差不多，错误数据影响大
 
```python
data = MinMaxScaler().fit_transform([[1,2,3],[3,2,1]])
```
 
#### (2). 标准化
 
常用
 
```python
data = StandardScaler().fit_transform([[1,2,3],[3,2,1]])
```
 
### 3. 缺失值处理
 
```python
sklearn.preprocessing.Imputer(missing_values='NaN',strategy='mean',aixs=0) # 0是列，1是行
replace("?",np.nan)
```
 
### 4. 数据降维
 
#### (1). 数据选择
 
在feature_selection中
 
VarianceThreshold（threshold=0.0):删除方差低于threshold的特征，大体都相同的特征没有意义
 
#### (2). 主成分分析(PCA)
 
```python
from sklearn.decomposition import PCA
 
pca = PCA(n_components=0.9) #保留数据成分
pca.fit_transform(data)
```
 
## 机器学习
 
### 1. ScikitLearn数据集
 
#### (1). sklearn.datasets
 
- datasets.load_*() #小数据集
- datasets.fetch_*(data_home=None) #大数据集，默认下载到家目录
 
返回的是datasets.base.Bunch(类字典)
 
- data:[n_samples*n_features]
- target:[n_samples]
- DESCT:描述
- feature_names:特征名
- target_names:标签名
 
> 使用Scikit-Learn数据集需要注意其基本导入语法from sklearn.datasets import _
 
#### (2). 数据集分割
 
```python
x_train,x_test,y_train,y_test = sklearn.model_selection.train_test_split(x,y,test_size=0.25)
```
 
## 2. 机器学习算法实现（Estimator）
 
#### (1). 一般步骤
 
- 调用`fit(x_train,y_train)`
- 输入测试集的数据
  - `y_predict = predict(x_test)`
  - 预测的准确率:`score(x_test,y_test)`
 
#### (2).  K近邻
 
需要标准化
 
```python
knn = sklearn.neighbors.KNeighborsClassifier(n_neighbors=5)
knn.fit(x_train,y_train)
 
y_predict = knn.predict(x_test)
correct = knn.score(x_test,y_test)
```
 
- k值很小：容易受异常点异常
- k值很大：容易受类别影响
- 性能很差