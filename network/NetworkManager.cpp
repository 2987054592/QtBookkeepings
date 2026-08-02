//
// Created by 114514 on 2026/8/2.
//

#include "NetworkManager.h"

#include "dao/BagProcessDao.h"
#include <QJsonDocument>
NetworkManager::NetworkManager(QObject *parent) : QObject(parent){
    networkAccessManagers = new QNetworkAccessManager(this);
    connect(networkAccessManagers,&QNetworkAccessManager::finished,this,&NetworkManager::onReplyFinished);
}

void NetworkManager::get(const QString &url) {
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 忽略SSL错误（仅用于测试）
    request.setAttribute(QNetworkRequest::RedirectPolicyAttribute, true);
    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(config);

    networkAccessManagers->get(request);
}

void NetworkManager::post(const QString &url, const QJsonObject &data) {
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setAttribute(QNetworkRequest::RedirectPolicyAttribute, true);
    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(config);
    QByteArray dataJson = QJsonDocument(data).toJson();
    networkAccessManagers->post(request,dataJson);
}


void NetworkManager::onReplyFinished(QNetworkReply *reply) {
    if (reply->error()!=QNetworkReply::NoError) {
        emit requestError(reply->errorString());
        reply->deleteLater();
        return;
    }
    QByteArray respondData = reply->readAll();
    qDebug() << "[NetworkManager] 响应数据:" << respondData;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(respondData);
    if (jsonDoc.isObject()) {
        qDebug() << "[NetworkManager] 发送replyFinished信号";
        emit replyFinished(jsonDoc.object());
    }else {
        qDebug() << "[NetworkManager] JSON解析失败或不是对象";
        emit requestError("响应数据格式错误");
    }
    reply->deleteLater();
}
