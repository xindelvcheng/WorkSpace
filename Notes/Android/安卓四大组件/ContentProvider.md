# ContentProvider 内容提供者
ContentProvider是不同应用程序之间进行数据交换的标准API
## 入门：跨应用数据库访问
### 1.自定义类继承ContentProvider
```
public class AccountProvider extends ContentProvider {

    private static final UriMatcher sURIMatcher = new UriMatcher(UriMatcher.NO_MATCH);

    private static final int QUERYSUCCESS = 1;

    static
    {
        sURIMatcher.addURI("com.xindelvcheng.provider"/*要和清单文件中authorities配置一样*/, "query", QUERYSUCCESS);
    }

    private MySqliteHelper openHelper;

    @Override
    public boolean onCreate() {
        openHelper = new MySqliteHelper(getContext());
        return false;
    }

    @Override
    public Cursor query(Uri uri, String[] projection, String selection, String[] selectionArgs, String sortOrder) {
        int code = sURIMatcher.match(uri);
        if (code == QUERYSUCCESS/*match the uri defined*/) {
            SQLiteDatabase database = openHelper.getWritableDatabase();
            return database.query("info", projection, selection, selectionArgs, null, null, sortOrder);
        } else {
            throw new IllegalArgumentException("参数异常");
        }
    }

    @Override
    public String getType(Uri uri) {return null;}
    @Override
    public Uri insert(Uri uri, ContentValues values) {return null;}
    @Override
    public int delete(Uri uri, String selection, String[] selectionArgs) {return 0;}
    @Override
    public int update(Uri uri, ContentValues values, String selection, String[] selectionArgs) {return 0;}
}
```
>URI类比Javaweb开发中SpingMVC使用的请求映射里使用的相对路径
### 2.在AndroidManifest.xml文件中配置
```
<provider
    android:authorities="com.xindelvcheng.provider"
    android:name=".AccountProvider"
    android:exported="true"/>
```
>exporeted介绍
android:exported 是Android中的四大组件 Activity，Service，Provider，Receiver 四大组件中都会有的一个属性。 
作用：是否支持其它应用调用当前组件。默认值：如果包含有intent-filter 默认值为true; 没有intent-filter默认值为false
### 3.在其他应用中使用内容解析者获取数据
```
public void click(View view) {
    //通过上下文获取内容解析器
    ContentResolver resolver = getContentResolver();
    Uri uri = Uri.parse("content://com.xindelvcheng.provider/query");
    Cursor cursor = resolver.query(uri, null, null, null, null);
    StringBuffer sb = new StringBuffer();
    if (cursor != null && cursor.getCount() != 0) {
        while(cursor.moveToNext()) {
            sb.append(String.format("name:%s\tmoney:%s", cursor.getString(1), cursor.getString(2)+"\n"));
        }
    }
    cursor.close();
    tv1.setText(sb.toString());
}
```
## 应用场景
内容提供者使用的不多，主要是读取系统提供的数据，如短信，联系人。
## 案例：读取短信
```
ContentResolver resolver = getContentResolver();
Uri uri = Uri.parse("content://sms/");
Cursor cursor = resolver.query(uri, new String[]{"address","date","body"}, null, null, null);
StringBuffer sb = new StringBuffer();
if (cursor != null && cursor.getCount() != 0) {
    while(cursor.moveToNext()) {
        sb.append(String.format("address:%s\tdate:%s\tbody%s", cursor.getString(0), cursor.getString(1), cursor.getString(2))).append("\n");
    }
}
cursor.close();
tv1.setText(sb.toString());
```
## 内容观察者
如果内容提供者当有人使用内容解析者查询或修改了它提供的数据时发出一条消息，便可以设置一个内容观察者监视这个变化
### 1.在ContentProvider的query等方法里操作完成后添加代码发出消息
```
getContext().getContentResolver().notifyChange(uri,null);
```
### 2.注册一个内容观察者监视内容提供者数据的情况
```
getContentResolver().registerContentObserver(Uri.parse("content://sms"),
        true/*只要以制定的uri开头而不必完全相同*/,
        new ContentObserver(new Handler()) {
    @Override
    public void onChange(boolean selfChange) {
        Toast.makeText(MainActivity.this, "内容发生了改变", Toast.LENGTH_SHORT).show();
        super.onChange(selfChange);
    }
});
```