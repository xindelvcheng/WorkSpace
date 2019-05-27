
# Keras




## 入门




### 1. 线性回归




```python

import keras

import numpy as np

import matplotlib.pyplot as plt




from keras.models import Sequential

from keras.layers import Dense




model = Sequential()

model.add(Dense(units=1,input_dim=1))

model.compile(optimizer='sgd',loss='mse')




for e in range(3000):

    cost = model.train_on_batch(x_data,y_data)

    if (e+1)%500==0:

        print('epoch:{},cost:{}'.format(e+1,cost ))

W,b = model.layers[0].get_weights()

print("w:{},b:{}".format(W,b ))




y_pred = model.predict(x_data)




plt.scatter(x_data,y_data)

plt.plot(x_data,y_pred,"r-",lw=3)

plt.show()

```





