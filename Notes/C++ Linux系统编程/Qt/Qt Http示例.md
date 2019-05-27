```c++
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>  
 
 
QUrl url("http://www.xindelvcheng.com/");
manage = new QNetworkAccessManager(this);
QNetworkReply* reply = manage->get(QNetworkRequest(url));
connect(manage,&QNetworkAccessManager::finished,[=](){
    qDebug()<<reply->readAll();
});
```
 