# Pytorch

## 入门

### 1. 变量

Tensor，Variable，Parameter

- Pytorch中Tensor和numpy中ndarry的使用方式类似，可以通过`from_numpy()`和`.numpy()x`相互转换。

- Variable是Tensor的封装，包含`.data`：内部的Tensor，`.grad`：梯度，`.grad_fn`：得到的途径

- Parameter是Varible的封装，默认requires_grad=True

### 2. 自动求导

先使用`.zero_grad`清零梯度，调用`.backward`即可

### 3. 使用Sequential和Module定义模型

#### Sequential

```python
seq_net    =    nn.Sequential(
    nn.Linear(2,4),
    nn.Tanh(),
    nn.Linear(4,1)
)
```

#### Model

```python
class module_net(nn.Module):
    def __init__(self,    num_input,    num_hidden,    num_output):
        super(module_net,    self).__init__()
        self.layer1    = nn.Linear(num_input,    num_hidden)
        self.layer2    = nn.Tanh()
        self.layer3    = nn.Linear(num_hidden,    num_output)
 
    def forward(self, x):
        x = self.layer1(x)
        x =    self.layer2(x)
        x =    self.layer3(x)
        return x
```

### 4. 损失函数

```python
criterion = nn.BCEWithLogitsLoss()
```

### 5. 优化器

```python
optimizer = optim.SGD(net.parameters(),1.)
optimizer = torch.optim.Adam(net.parameters(),lr=1e-3) #使用自适应优化算法需要更小的学习率
```

### 6. 训练模板

```python
for e in range(10000):
    out    = net(Variable(x))
    loss = criterion(out, Variable(y))
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()
    if    (e + 1)    % 1000    ==    0:
        print('epoch:    {},    loss:    {}'.format(e+1,    loss.data[0]))
```

 

### 7. 模型的保存与加载

#### 保存

```python
torch.save(net.state_dict(),'path.pth')
```

#### 加载

需要实例化一个模型对象

```python
net.load_state_dict(torch.load('path.pth'))
```

##  数据处理

### 1. 数据加载

使用torch提供的工具类DataLoader定义一个数据迭代器，可以不用一次性将数据读入内存

```python
from torch.utils.data import DataLoader
 
train_set = DataLoader(train_set,batch_size=64,shuffle=True)
img,label = next(iter(train_set))
```

> img的形状为[64,784],label的形状为[64]（不知道为什么并不是[64,1]）

> 出现`DataLoader' object does not support indexing`错误，是因为迭代了已经迭代完成的迭代器，考虑复制时忘了将test_set改为train_set

## 卷积神经网络

使用`Conv2d(in_channels, out_channels, kernel_size, stride=1, padding=0, dilation=1, groups=1, bias=True)`像普通的FC一样使用它

## 循环神经网络
### 1.API

#### LSTM

##### Define:

```python
self.lstm = torch.nn.LSTM(input_size,hidden_size,num_layers,batch_first=True)
self.lstm = torch.nn.LSTM(input_size, hidden_size, num_layers, batch_first=True, bidirectional=True) # BiRNN
```

##### Outputs:

```python
# "y" is the output tensor of shape(batch_size,sequence_length,hidden_size*num_direction)
# "h0"、"c0" are all output tensors of shape(num_layers*num_direction,batch_size,hidden_size)
y,(h0,c0) = self.lstm(x,(h0,c0)) 
```


### 2.词嵌入矩阵
使用` nn.Embedding `定义一个嵌入层
```python
embeds = nn.Embedding(100,50) # 共100个单词，每个使用50个维度表示
embeds.weight.data = torch.ones(100,50) # 载入下载的已经训练好的词嵌入矩阵
single_word_embedding = embeds(torch.LongTensor([50])) # 取序号为50的单词的向量，注意这里需要的是一个封装了序号的LongTensor
```

## GPU加速

### 1. 使用

#### 兼容写法

```python
device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
model.to(device)
tensor.to(device)
```

#### 测试的简易写法

```python
model.cuda() # <-> model.cpu()
tensor.cuda()
```



### 2. 报错

1. `RuntimeError: reduce failed to synchronize: device-side assert triggered`这种CUDA通用错误没有什么用，将设备改成CPU查看错误。
2. `CUDA error: device-side assert triggered`，重新运行所有代码