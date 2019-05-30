# ListView的使用
## 一. ListView入门
### 1.在布局中添加ListView
```
<ListView
        android:id="@+id/lv"
        android:layout_width="match_parent"
        android:layout_height="match_parent" />
```
>宽高应该设置为match_parente而不是wrap_content，否则将调用更多次getView()
### 2.定义列表适配器，继承BaseAdapter
```
private class MyListAdapter extends BaseAdapter {

    //决定要显示几个item
    @Override
    public int getCount() {return 100;}
    //不用重写
    @Override
    public Object getItem(int position) {return null;}
    //不用重写
    @Override
    public long getItemId(int position) {return 0;}
    //设置每一个item是什么view，当条目显示时被调用
    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        TextView tv = new TextView(getApplicationContext());
        tv.setText("哈哈"+position);
        return tv;
    }
}
```
>使用缓存,convertView表示划出屏幕的那个item
```
@Override
        public View getView(int position, View convertView, ViewGroup parent) {
            TextView tv = null;
            if (convertView == null) {
                tv = new TextView(getApplicationContext());
            } else {
                tv= (TextView) convertView;
            }
            tv.setText("哈哈"+position);
            System.out.println("哈哈"+position);
            return tv;
        }
```
### 3.指定适配器
```
ListView lv = (ListView)findViewById(R.id.lv);
lv.setAdapter(new MyListAdapter());
```
## ListView展示数据的原理
和javaweb类似采用MVC,Adapter(C)把JavaBean(M)的数据展示到View(V)上
## 二. 自定义View美化ListView
### 1. 创建LayoutResourceFile item
```
<?xml version="1.0" encoding="utf-8"?>
<RelativeLayout xmlns:android="http://schemas.android.com/apk/res/android"
    android:layout_width="match_parent" android:layout_height="match_parent">
    <ImageView
        android:id="@+id/iv1"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:src="@mipmap/ic_launcher"/>
    <TextView
        android:id="@+id/tv_title"
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:layout_toRightOf="@id/iv1"
        android:singleLine="true"
        android:text="哈哈你好啊大家福利卡时间的反复看了圣诞节福利卡三等奖"
        android:textColor="#000000"
        android:textSize="20sp"
        android:ellipsize="end"/>
    <TextView
        android:id="@+id/tv_content"
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:layout_toRightOf="@id/iv1"
        android:layout_below="@id/tv_title"
        android:maxLines="2"
        android:ellipsize="end"
        android:text="    第三方了跨时代李慧娟开放老加班是感受对方过后的市政府"/>
</RelativeLayout>
```
### 2.将layout转换为view，放入重写的Adapter类的getView()方法中
```
public View getView(int position, View convertView, ViewGroup parent) {
    View v = null;
    if (convertView == null) {
        v =View.inflate(getApplicationContext(), R.layout.item, null);
    } else {
        v= convertView;
    }
    return v;
}
```
### 3.打气筒（inflate）的几种获取方法
```
View.inflate(getApplicationContext(), R.layout.item, null);

LayoutInflater.from(getApplicationContext()).inflate(R.layout.item, null);

LayoutInflater inflater = (LayoutInflater) getSystemService(LAYOUT_INFLATER_SERVICE);
inflater.inflate(R.layout.item, null);
```
## 三.对于简单的需求使用ArrayAdapter
### 1.每一个item只有一个TextView，使用ArrayAdapter
```
String[] objects = {"haha", "lala", "你好", "再见"};
ArrayAdapter<String> arrayAdapter = new ArrayAdapter<String>(getApplicationContext(), R.layout.item_2, R.id.textView,objects);
lv.setAdapter(arrayAdapter);
```
### 2.SimpleAdapter
使用一个Map封装一条数据，实际用POJO更好，所以它用的少
>BaseAdapter用的最多
## 四. 滚动视图
让没有滚动功能显示不完文本的TextView具有滚动功能，它只能有一个子控件，但可以包含一个布局，布局里再包含多个控件
```
<ScrollView
    android:layout_width="match_parent"
    android:layout_height="wrap_content">
    <TextView
        android:layout_width="match_parent"
        android:layout_height="match_parent"
        android:text="LongText"/>
</ScrollView>
```

## 五. 绑定事件
### 绑定条目点击事件
```
lv1.setOnItemClickListener(new AdapterView.OnItemClickListener() {
    @Override
    public void onItemClick(AdapterView<?> parent/*ListView*/, View view/*Item*/, int position/*被点击条目的位置*/, long id) {
        Toast.makeText(getApplicationContext(),position,Toast.LENGTH_SHORT).show();
    }
});
```