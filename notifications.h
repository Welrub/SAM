#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H

#include <QObject>
#include <QDebug>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

class notifications : public QObject
{
    Q_OBJECT
public:
    explicit notifications(QObject* parent  = nullptr);

signals:

public slots:
    void post(QString& mes);

private slots:
    void readyRead();

    void	encrypted(QNetworkReply *reply);

private:
    QNetworkAccessManager manager;
    const QString url = "https://api.telegram.org/bot<bot_id>/sendMessage?chat_id=<chat_id>&text=";
};

#endif // NOTIFICATIONS_H
