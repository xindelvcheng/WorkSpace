# 样式和主题
安卓中样式和主题是同一种文件，作用类似CSS
## Style入门
样式一般作用在控件上
### 1.在values/styles.xml中添加style节点
```
<?xml version="1.0" encoding="utf-8"?>
<resources>

    <style name="my_styles">
        <item name="android:layout_width">match_parent</item>
        <item name="android:layout_height">wrap_content</item>
    </style>
</resources>
```
### 2.指定控件的style属性
```
<TextView
    style="@style/my_styles"
    android:text="文本"/>
```
## Theme入门
主题一般作用在Activity或Application节点下
### 1.在values/styles.xml中添加style节点
```
<style name="my_theme">
    <item name="android:background">#FF0000</item>
</style>
```
### 2.在清单文件中配置主题
```
android:theme="@style/my_theme">
```
>在valus下新建my_style.xml放样式同样有效