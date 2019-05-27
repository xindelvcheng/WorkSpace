# Pygame Fundamental
## 入门
### 1. 游戏最小开发框架
```
import pygame
import sys
 
pygame.init()
screen = pygame.display.set_mode((600, 400))
pygame.display.set_caption("Pygame游戏之旅")
 
while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
        pygame.display.update()
```
### 2. 载入图像
```
import pygame
import sys
 
pygame.init()
size = width, height = 600, 400
speed = [1, 1]
BLACK = 0, 0, 0
 
screen = pygame.display.set_mode(size)
pygame.display.set_caption("Pygame移动")
ball = pygame.image.load("ball.png")  # 返回了Surface对象，pygame中载入的图片用它表示
ball_rect = ball.get_rect()  # 获得一个和图像相切的矩形，可以设置长宽和位置
 
while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
    ball_rect = ball_rect.move(speed[0], speed[1])
    if ball_rect.left < 0 or ball_rect.right > width:
        speed[0] = -speed[0]
    if ball_rect.top < 0 or ball_rect.bottom > height:
        speed[1] = -speed[1]
 
    screen.fill(BLACK)
    screen.blit(ball,ball_rect) #把图像绘制到矩形上,ball_rect可以换成一个(0,0)这样包含x，y的元组   
    pygame.display.update()
```
### 3. 控制时间进度
设置fclock.tick(fps)帧率
```
import pygame
import sys
 
pygame.init()
size = width, height = 600, 400
speed = [1, 1]
BLACK = 0, 0, 0
fps = 300
 
screen = pygame.display.set_mode(size)
pygame.display.set_caption("Pygame移动")
ball = pygame.image.load("ball.png")  # 返回了Surface对象，pygame中载入的图片用它表示
ball_rect = ball.get_rect()  # 获得一个和图像相切的矩形，可以设置长宽和位置
fclock = pygame.time.Clock()
 
while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
    ball_rect = ball_rect.move(speed[0], speed[1])
    if ball_rect.left < 0 or ball_rect.right > width:
        speed[0] = -speed[0]
    if ball_rect.top < 0 or ball_rect.bottom > height:
        speed[1] = -speed[1]
 
    screen.fill(BLACK)
    screen.blit(ball,ball_rect) #把图像绘制到矩形上
    pygame.display.update()
    fclock.tick(fps)
```
## 事件监听
### 1. 关闭窗口和键盘事件监听
```
while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_w:
                print("w is pressed")
```
### 2. 窗口事件
```
event.type == pygame.VIDEORESIZE:
            size = width, height = event.size[0], event.size[1]
            screen = pygame.display.set_mode(size, pygame.RESIZABLE)
```
## API
### 显示
#### 屏幕模式
```
pygame.display.set_mode(r=(0,0),flags=0))
```
r 分辨率，(width,height)
flags 控制显示类型，使用|组合使用，常用显示标签如下：
pygame.RESIZABLE 窗口大小可调
pygame.NOFRAME 窗口没有便捷显示
pygame.FULLSCREEN 全屏显示
>设置了对应的屏幕模式，要对应改变代码内容（不会自适应，如大小可调不会影响小球运行范围）
#### 屏幕信息函数
```
pygame.display.Info()
```
返回VideoInfo对象，包含当前屏幕参数，调用set_mode()之后则为游戏窗口信息
-   current_w: 当前显示模式或窗口像素宽度
-   current_h: 当前显示模式或窗口像素高度
#### 标题和图标函数
```
pygame.display.set_caption()  //设置标题
title,icontitle = pygame.display.get_caption() //返回当前设置窗口的标题及小标题内容
pygame.display.set_icon(surface) //设置图标
```
#### 屏幕感知
```
pygame.display.get_active()
```
当窗口显示（非图标化）时显示True，否则显示False。该函数可以判断当前游戏窗口是否被最小化
#### 屏幕刷新
display.set_mode()创建的screen对象只是一个内存中的屏幕数据对象，需要使用update将其绘制到屏幕上
```
pygame.display.update() //更新
pygame.display.flip() //重绘
```
每一次调用update方法之前，需要将所有的游戏图像重新绘制一遍，首先要绘制背景，遮挡住原来所有的东西，否则会留下残影
## 事件
### 1. 事件处理机制简介
pygame的事件本质上是一种封装后的数据类型（对象），是pygame的一个类，表示事件类型，事件类型只有属性没有方法
### 2. 键盘事件
####   键盘按下事件 pygame.event.KEYDOWN
事件返回信息：
-   event.key 按下按键名 ：K_A,K_B
-   event.mod 按键修饰符按位或运算组合值，此时键盘是否按下了Shift，CAPS：KMOD_SHIFT,KMOD_CAPS 
```
event.mod = KMOD_ALT | KMOD_SHIFT
```
-   event.unicode 平台行，不推荐使用
####   键盘释放事件 pygame.event.KEYUP
-   event.key 按下按键名 ：K_A,K_B
-   event.mod 按键修饰符组合值
#### 使用键盘模块
与事件监听for循环并列，与键盘按下和抬起事件不同，这个是监听键盘按着的模块
```
keys_pressed = pygame.key.get_pressed()
if keys_pressed[pygame.K_RIGHT]:
    print("向右移动") # 只要按着"→"就会一直打印
```
### 3. 鼠标事件
#### 鼠标移动事件
pygame.event.MOUSEMOTION
-   event.pos 鼠标当前坐标值(x,y)，相对于窗口左上角
-   event.rel 鼠标相对运行距离(x,y),相对于上次鼠标移动事件
-   event.buttons 鼠标按钮状态(a,b,b)，对应于鼠标的三个键，鼠标移动时按下的键对应位置为1
#### 鼠标移动事件
pygame.event.MOUSEMOTION
-   event.pos 鼠标当前坐标值(x,y)，相对于窗口左上角
-   event.rel 鼠标相对运行距离(x,y),相对于上次鼠标移动事件
-   event.buttons 鼠标按钮状态(a,b,c)，对应于鼠标的三个键，鼠标移动时按下的键对应位置为1
#### 鼠标键释放事件
pygame.event.MOUSEBUTTONUP
-   event.pos 鼠标当前坐标值(x,y)，相对于窗口左上角
-   event.buttons 鼠标按钮状态(a,b,c)，对应于鼠标的三个键
#### 鼠标键按下事件
pygame.event.MOUSEBUTTONDOWN
-   event.pos 鼠标当前坐标值(x,y)，相对于窗口左上角
-   event.buttons 鼠标按下键编号n，取值为整数，左键为1，右键为3，设备相关（有些复杂的鼠标可能返回任一个整数）
```
while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
        if event.type == pygame.MOUSEBUTTONDOWN:
            print("Click position:\t",event.pos[0],event.pos[1],"Click button:\t",event.button)
        pygame.display.update()
 
```
### 4. 事件处理重要函数
#### 处理事件
-   pygame.event.get() 
从事件队列中获得事件列表，即获得所有队列中的事件随即从队列中删除它们。可以增加参数以获得某类或某些类事件:pygame.event.get(type),pygame.event.get(typelist)
-   pygame.event.poll() 
从事件队列中获取一个事件，随机将其从事件队列中删除，如果事件队列为空，则返回event.NOEVENT类型
-   pygame.event.clear() 
删除所有事件
#### 操作事件队列
pygame事件队列仅能存储128个事件
-   pygame.event.set_blocked(type or typelist) 
控制哪些类型事件**不允许**被保存到事件队列中
-   pygame.event.get_blocked(type or typelist) 
控制哪些类型事件**允许**被保存到事件队列中
-   pygame.event.set_allowed(type) 
测试某类型事件是否被禁止，若type类型事件被禁止，返回True
#### 生成事件
-   pygame.event.post(Event)
产生一个事件，并将其放入事件队列
-   pygame.event.Event(type,dict)
创建一个给定类型的事件，其中，事件的属性和值采用字典类型复制，属性名采用字符串形式，如果创建已有事件，属性需要一致
```
fps = 1
fclock = pygame.time.Clock()
 
 
while True:
    uevent = pygame.event.Event(pygame.KEYDOWN,{"unicode":123,"key":pygame.K_SPACE,"mod":pygame.KMOD_ALT})
    pygame.event.post(uevent)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
        if event.type == pygame.KEYDOWN:
            print(event.unicode,event.key,event.mod)
        pygame.display.update()
    fclock.tick(fps)
```
#### 定时器
pygame.time.set_timer()设置定时器，每隔一段时间执行一些动作。它创建一个事件，可以在事件队列中捕获
```
set_timer(eventId,milliseconds)
```
eventId可以使用常量USEREVENT
 
## 色彩与绘图
### 1. 色彩表达
#### pygame.Color类
-   pygame.Color()支持RGB或RGBA，A可选。Color类可以用色彩名字，RGBA值，HTML色彩格式等方式定义，如
Color("grey)或Color(190,190,190,255)或Color("#BEBEBEFF")
>alpha通道表示不透明度，取值0-255，alpha通道值越大，不透明度越高，255表示不透明
-   pygame.Color.r 获取Color类的红色值
-   pygame.Color.g 获取Color类的绿色值
-   pygame.Color.b 获取Color类的蓝色值
-   pygame.Color.a 获取Color类的alpha色值
-   pygame.Color.normalize 将RGBA各通道值归一到0-1之间
### 2. 图形绘制机制
#### pygame.draw
绘制图形:
-   pygame.draw.rect(Surface,color,Rect,width=0) 矩形
    ```
    """
    Surface 矩形的绘制屏幕（screen对象）
    Color 矩形的绘制颜色
    Rect 绘制区域
    width=0 绘制边缘的宽度，默认为0表示填充
    """
    pygame.draw.rect(screen,pygame.Color(255,255,255),(100,100,200,100),0)
    ```
    >坐标系：窗口左上角为(0,0)，从左向右为x轴正方向，从上到下为y轴正方向，Rect对象位置为左上角，width为水平宽度，height为垂直高度
-   line() 直线
-   polygon()多边形
-   ellipse() 椭圆
-   circle() 圆形
#### pygame.Rect
任何绘制图形pygame都是用一个包裹它的矩形来表示
-   Rect类有很多属性，如x,y,w,h,size,width,height,top,left,bottom,right,topleft...center,centerx,centery等等
-   Rect也提供了很多方法,如copy(),move(),inflate()
### 3. 文字绘制
import pygame.freetype
#### 定义字体
#### 将文字绘制到屏幕上
render_to(self, surf, dest, text, fgcolor=None, bgcolor=None, style=None, rotation=0, size=0)
-   surf:绘制字体的平面，Surface对象
-   dest:在平面中的具体位置,(x,y)
-   text:绘制的文字内容
-   fgcolor：文字颜色
-   bgcolor：背景颜色
-   rotation：逆时针的旋转角度，取值0-359，部分字体可旋转
-   size：文字大小
```
f1 = pygame.freetype.Font("C://Windows//Fonts//msyh.ttc", 36)
f1rect = f1.render_to(screen, (200, 160), "Test", pygame.Color("red"), pygame.Color("blue"), size=50)
```
render(text, fgcolor=None, bgcolor=None, style=STYLE_DEFAULT, rotation=0, size=0) -> (Surface, Rect)
Return rendered text as a surface 
需要使用screen.blit(surf,(100,100))将返回的Surface对象绘制到屏幕上
### 4. 总结
#### Surface
图层，用于表示绘制效果，如果不被绘制在主图层上不会显示
#### Rect
对应于当前**当前主图层**的某个具体区域
#### 主图层
-   由pygame.display.set_mode()生成的Surface对象，唯一能被显示的图层。
-   **在主图层上绘制其他图层使用blit(ball,ballrect)方法**,第一个参数是其他图层对应的Surface对象，第二个参数则是主图层上的区域