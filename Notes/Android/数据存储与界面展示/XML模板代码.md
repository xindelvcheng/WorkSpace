# XML的生成
```
try {
    //[1]获取xml序列化实例
    XmlSerializer serializer = Xml.newSerializer();
    //[2]设置序列化参数

    File file = new File(Environment.getExternalStorageDirectory().getPath(), "smsBackUp.xml");
    FileOutputStream fos = new FileOutputStream(file);
    serializer.setOutput(fos, "utf-8");

    //[3]开始写xml文档开头
    serializer.startDocument("utf-8", true);
    //[4]开始写根节点
    serializer.startTag(null, "smss");
    //[5]由于短信数据库 系统也通过内容提供者给暴露出来了了 所以我们只需要通过内容解析者去操作数据库
    Uri uri = Uri.parse("content://sms/");
    Cursor cursor = getContentResolver().query(uri, new String[]{"address", "date", "body"}, null, null, null);
    while (cursor.moveToNext()) {
        String address = cursor.getString(0);
        String date = cursor.getString(1);
        String body = cursor.getString(2);

        //[6]写sms节点

        serializer.startTag(null, "sms");
        //[7]写address节点
        serializer.startTag(null, "address");
        serializer.text(address);
        serializer.endTag(null, "address");


        //[8]写body节点
        serializer.startTag(null, "body");
        serializer.text(body);
        serializer.endTag(null, "body");


        //[9]写date节点
        serializer.startTag(null, "date");
        serializer.text(date);
        serializer.endTag(null, "date");


        serializer.endTag(null, "sms");


    }


    serializer.endTag(null, "smss");
    serializer.endDocument();


} catch (Exception e) {
    e.printStackTrace();
}
```
# XML的解析
```
public static List<User> parserXml(InputStream in) throws Exception {

    List<User> UserLists = null;
    User user = null;
    // [1]获取xml的解析器
    XmlPullParser parser = Xml.newPullParser();
    // [2]设置解析器 要解析的内容
    parser.setInput(in, "utf-8");
    // [3]获取解析的事件类型
    int type = parser.getEventType();
    // [4]不停的向下解析
    while (type != XmlPullParser.END_DOCUMENT) {
        // [5]具体判断一下解析的是开始节点 还是结束节点
        switch (type) {
            case XmlPullParser.START_TAG: // 解析开始节点
                //[6]具体判断一下解析的是哪个开始标签 
                if ("channel".equals(parser.getName())) {
                    UserLists = new ArrayList<User>();
                } else if ("UserList".equals(parser.getName())) {
                    user = new User();
                } else if ("name".equals(parser.getName())) {
                    user.setName(parser.nextText());
                } else if ("age".equals(parser.getName())) {
                    user.setAge(parser.nextText());
                }
                break;

            case XmlPullParser.END_TAG: // 解析结束标签,把javabean添加到 集合
                if ("UserList".equals(parser.getName())) {
                    UserLists.add(user);
                }
                break;
        }
        // 不停的向下解析
        type = parser.next();
    }
    return UserLists;
}
```