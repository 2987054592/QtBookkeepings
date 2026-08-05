//
// Created by 114514 on 2026/8/2.
//

#ifndef BOOKKEEPINGS_OSSCLIENT_H
#define BOOKKEEPINGS_OSSCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "alibabacloud/oss2/ClientConfiguration.h"
#include "alibabacloud/oss2/OSSClient.h"
#include "alibabacloud/oss2/credentials/CredentialsProvider.h"

class OSSClient : public QObject {
    Q_OBJECT
public:
    explicit OSSClient(const QString &endpoint,           // 例如 "oss-cn-hangzhou.aliyuncs.com"
                       const QString &bucketName,
                       const QString &region, // 空则从 endpoint 自动推断（如 cn-hangzhou）
                       QObject *parent = nullptr);


    QString putData(const QString filePath);
    void deleteData(const QString url);

private:
     alibabacloud::oss2::OSSClient *client=nullptr;
     QString bucketName;
     QString region;
};

#endif //BOOKKEEPINGS_OSSCLIENT_H
