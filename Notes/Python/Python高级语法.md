## Python函数的本质

在Python中，函数其实是一个对象

```
f = abs
print(f.__name__)
print(f(-123)) # 调用abs()
```

```
abs
123
```

由于 f 可以被调用，所以，f 被称为可调用对象。 所有的函数都是可调用对象。 一个类实例也可以变成一个可调用对象，只需要实现一个特殊方法__call__()

```
class A():
    def __call__(self):
        print("调用类对象")
a = A()
#调用类对象
a()
```

可以看出python中一切皆对象

## 网络上常用的base64解码

```
import base64
img = base64.b64decode(img_src[23:])  # 前面是data:image/jpeg;base61,
```

## with语法

```
# 使用with()需要定义两个方法
class A():
    def __enter__(self):
        print("进入with时被调用")
    def __exit__(self,exc_type,exc_value,exc_tb):
        print("离开with时被调用")
```

## Lambda表达式

```
add = lambda x,y:x+y
print(add(1,2))
```

```
3
```

### 字典按照值排序

```
import random
dictionary = {random.randint(0,10):random.randint(0,10) for _ in range(10)}
sorted(dictionary.items(),key=lambda dictionary:dictionary[1])
```

```
[(5, 3), (4, 3), (3, 5), (6, 6), (10, 6), (0, 6), (2, 9)]
```

## Map函数

```python
list(map(lambda x:x*2,li))
```

map()是 Python 内置的高阶函数，它接收一个函数 f 和一个 list，并通过把函数 f 依次作用在 list 的每个元素上，得到一个新的 list 并返回。