```
import tkinter
```

In [4]:

```
root = tkinter.Tk()
root.title('Quit button')

btn = tkinter.Button(root, text="Quit", width=8,
    command=root.destroy) # 这里使用root.quit() 会卡死
btn.pack(pady=10) # pack是布局管理，

root.geometry("300x250+300+300") # 窗口宽高，窗口位置
root.mainloop()
```

In [2]:

```
import tkinter

root = tkinter.Tk()
root.title('Centered window')

win_width = 300
win_height = 250 

screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()

start_x = int((screen_width/2) - (win_width/2))
start_y = int((screen_height/2) - (win_height/2))

root.geometry('{}x{}+{}+{}'.format(win_width, win_height, 
    start_x, start_y))
root.mainloop()
```

In [8]:

```
from tkinter import *
 
top = Tk()
L1 = Label(top, text="网站名")
L1.pack( side = LEFT)
E1 = Entry(top, bd =5)
E1.pack(side = RIGHT)
 
top.mainloop()
```

In [14]:

```
from tkinter import *
root = Tk()
 
#按扭调用的函数，
def reg():
    User = e_user.get()
    Pwd = e_pwd.get()
    len_user = len(User)
    len_pwd = len(Pwd)
    if User=='111' and Pwd == '222':
        l_msg['text']='登陆成功'
    else:
        l_msg['text']='用户名或密码错误'
        e_user.delete(0,len_user)
        e_pwd.delete(0,len_pwd)
 
#第一行，用户名标签及输入框
l_user =Label(root,text='用户名：')
l_user.grid(row=0,sticky=W)
e_user =Entry(root)
e_user.grid(row=0,column=1,sticky=E)
 
#第二行，密码标签及输入框
l_pwd = Label(root,text='密码：')
l_pwd.grid(row=1,sticky=W)
e_pwd = Entry(root)
e_pwd['show']='*'
e_pwd.grid(row=1,column=1,sticky=E)
 
#第三行登陆按扭，command绑定事件
b_login = Button(root,text='登陆',command=reg)
b_login.grid(row=2,column=1,sticky=E)
 
#登陆是否成功提示
l_msg = Label(root,text='')
l_msg.grid(row=3)
 
root.mainloop()
```

In [ ]:

```
 
```