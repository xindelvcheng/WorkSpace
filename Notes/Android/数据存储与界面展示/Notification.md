# Android中的通知
## 入门
### 获取通知管理者
```
NotificationManager ns = (NotificationManager) getSystemService(NOTIFICATION_SERVICE);
```
### 发消息
```
Notification noti = new Notification.Builder(this)
        .setContentTitle("标题")
        .setContentText("内容")
        .setSmallIcon(R.mipmap.ic_launcher)
        .setLargeIcon(BitmapFactory.decodeResource(getResources(), R.mipmap.ic_launcher))
        .build();

noti.defaults = Notification.DEFAULT_ALL; //震动，呼吸灯
noti.flags = Notification.FLAG_NO_CLEAR; //通知无法被清除

ns.notify(10,noti); //发送id为10的通知
```
>这里的写法是链式调用，说明这些函数都返回对象自身
### 取消通知
```
ns.cancel(10);
```
### 兼容低版本的写法，带绑定事件
```
//兼容低版本的写法   使用过时的方法 
Notification notification = new  Notification(R.drawable.ic_launcher, "我接收到了一条通知", System.currentTimeMillis());
//来一条通知 设置一下震动   让呼吸灯亮 
notification.defaults = Notification.DEFAULT_ALL;

//设置通知不让清除
notification.flags = Notification.FLAG_NO_CLEAR;


//创建意图对象
Intent intent = new Intent();
//实现拨打电话的功能 
intent.setAction(Intent.ACTION_CALL);
intent.setData(Uri.parse("tel:"+119));
PendingIntent pendingIntent = PendingIntent.getActivity(this, 1, intent, Intent.FLAG_ACTIVITY_NEW_TASK);
//点击通知对应的业务逻辑
notification.setLatestEventInfo(this, "标题", "内容", pendingIntent);

//发出通知
nm.notify(10, notification);
```
### 通知能够提升进程的优先级为前台进程
```
startForeground(id,notification);
```