# BroadcastReceiver
广播接收者，类似注册监听事件机制
## 入门
### 一.创建一个类继承BroadcastReceiver，并重写onReceive方法，该方法在注册的事件发生时被调用
```
public class OutGoingCallReceiver extends BroadcastReceiver {
    @Override
    public void onReceive(Context context, Intent intent) {
        System.out.println(getResultData());//获取广播的数据
        setResultData("110");
    }
}
```
### 二.在AndroidManifest.xml中注册Receiver并注册事件（主要是在IntentFilter中添加action）
```
<receiver android:name=".OutGoingCallReceiver">
    <intent-filter >
        <action android:name="android.intent.action.NEW_OUTGOING_CALL" />
    </intent-filter>
</receiver>
```
### 三.添加所监听事件所需要的权限
```
<uses-permission android:name="android.permission.PROCESS_OUTGOING_CALLS" /><!--外拨电话事件-->
``` 

## 一个Receiver可以配置监听多个事件
在AndroidManifest.xml中配置多个action
```
<intent-filter >
    <action android:name="android.intent.action.MEDIA_MOUNTED" /><!--SD卡挂载事件-->
    <action android:name="android.intent.action.MEDIA_UNMOUNTED" /><!--SD卡卸载事件-->
    <data android:scheme="file" />
</intent-filter>
```
>SD挂载和卸载事件是唯二需要配data的事件，另一个是应用的安装与卸载，它们的scheme都是固定的
```
<action android:name="android.intent.action.PACKAGE_INSTALL" /><!--这个事件是预留的，实际无效-->
<action android:name="android.intent.action.PACKAGE_ADDED" /><!--应用安装事件-->
<action android:name="android.intent.action.PACKAGE_REMOVED" /><!--应用卸载事件-->
<data android:scheme="package" />
```

在回调方法中使用intent.getAction()判断是哪个事件
```
@Override
public void onReceive(Context context, Intent intent) {
    System.out.println(getResultData());
    setResultData("110");
    if ("android.intent.action.MEDIA_MOUNTED" .equals(intent.getAction()) ) {
        System.out.println("SD挂载");
    } else if ("android.intent.action.MEDIA_UNMOUNTED".equals(intent.getAction())) {
        System.out.println("SD卸载");
    }
}
```
## 收到短信广播
注册的事件是不能提示的
```
<action android:name="android.provider.Telephony.SMS_RECEIVED" />
```
在回调函数里
```
Object objects[] = (Object[])intent.getExtras().get("pdus");
for(Object obj:Objects){
    SmsMessage smsMessage = SmsMessage.createFromPdu((byte[]) obj);
    String messageBody = smsMessage.getMessageBody();
}
```
## 在BroadcastReceiver中开启Activity
不能直接开启，要先开启任务栈
```
intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
context.startActivity(intent);
```
## 自定义广播
类似发送信号，发送消息
### 1.无序广播
#### 发送无序广播
```
Intent intent = new Intent();
intent.setAction("com.xindelvcheng.sendDisorderBroadcast");
intent.putExtra("name", "哈哈！");
sendBroadcast(intent);
```
#### 接收，和接收系统广播一样  
清单文件
```
<receiver android:name=".DisOrderReceiver">
    <intent-filter>
        <action android:name="com.xindelvcheng.sendDisorderBroadcast" />
    </intent-filter>
</receiver>
```
广播接收者
```
public class DisOrderReceiver extends BroadcastReceiver {
    @Override
    public void onReceive(Context context, Intent intent) {
        String name = intent.getStringExtra("name");
        Toast.makeText(context,name,Toast.LENGTH_SHORT).show();
    }
}
```
### 2.有序广播
按优先级一级级获取广播
#### 发送有序广播
```
sendOrderedBroadcast(intent,null,new FinalReceiver(),null,1,"哈哈",null);
```
FinalReceiver是定义的广播接收者，但是不需要在清单文件中配置，它是广播最终的接收者（哪怕广播在中途被终止）
#### 接收
AndroidManifest.xml，指定指定时间的多个接受者和它们的优先级，建议从-1000 ~ 1000，值越大权限优先级越高
```
<receiver android:name=".OrderReceiver1">
    <intent-filter android:prioity="1000">
        <action android:name="com.xindelvcheng.sendOrderBroadcast" />
    </intent-filter>
</receiver>
<receiver android:name=".OrderReceiver2">
    <intent-filter android:prioity="100">
        <action android:name="com.xindelvcheng.sendOrderBroadcast" />
    </intent-filter>
</receiver>
<receiver android:name=".OrderReceiver3">
    <intent-filter android:prioity="-1000">
        <action android:name="com.xindelvcheng.sendOrderBroadcast" />
    </intent-filter>
</receiver>
```
广播接收者
```
public class DisOrderReceiver extends BroadcastReceiver {
    @Override
    public void onReceive(Context context, Intent intent) {
        String info = getResultData();
        setResultData("haha");
        // abortBroadcast(); 截停广播
    }
}
```
### 3.有序广播和无序广播的区别
有序广播可以被中止，可以被修改；无序广播不能被中止，不能被修改
>系统定义的广播事件有无序的也有有序的

## 特殊的广播接收者
操作特别频繁的事件，如锁屏解锁，电池电量变化这样的事件，在清单文件中注册是无效的
### 注册广播接收者的两种方式
1. 使用代码动态注册
```
@Override
protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);
    receiver = new DisOrderReceiver();
    IntentFilter filter = new IntentFilter();
    // 添加要注册的action
    filter.addAction("android.intent.action.SCREEN_OFF");
    filter.addAction("android.intent.action.SCREEN_ON");
    registerReceiver(receiver, filter);
}

@Override
protected void onDestroy() {
    super.onDestroy();
    unregisterReceiver(receiver);
}
```
>在Activity的onCreate()中注册广播接收者后如果不在onDestroy()中取消注册，会报一个Activity泄露错误
2. 在AndroidManifest.xml中静态注册