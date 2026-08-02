//
// Created by 114514 on 2026/8/2.
//

#ifndef BOOKKEEPINGS_NETWORKMANAGER_H
#define BOOKKEEPINGS_NETWORKMANAGER_H
#include "QObject"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
class NetworkManager : public QObject{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);
    QNetworkAccessManager* GetNetworkAccessManagers() const { return networkAccessManagers; }
    void get(const QString &url);
    void post(const QString &url, const QJsonObject &data);
signals:
    void replyFinished(const QJsonObject &respond);
    void requestError(const QString &error);
private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *networkAccessManagers;
};


#endif //BOOKKEEPINGS_NETWORKMANAGER_H
