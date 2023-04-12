#include "notifications.h"

notifications::notifications(QObject* parent) : QObject{parent}
{
    connect(&manager, &QNetworkAccessManager::encrypted, this, &notifications::encrypted);
}

void notifications::post(QString& mes)
{
    QNetworkRequest *request = new QNetworkRequest(QUrl(notifications::url + mes));
    request->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QByteArray *data = new QByteArray();
    QNetworkReply *reply = manager.post(*request, *data);

    connect(reply, &QNetworkReply::readyRead, this, &notifications::readyRead);
}

void notifications::readyRead()
{
    qInfo() << "notifications::readyRead() called";
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if(reply){
        qInfo() << reply->readAll();
    }else{
        qInfo() << "nothing to read";
    }
}

void notifications::encrypted(QNetworkReply *reply)
{
    Q_UNUSED(reply);
    qInfo() << "notifications::encrypted called";
}
