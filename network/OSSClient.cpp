//
// Created by 114514 on 2026/8/2.
//

#include "OSSClient.h"

#include <QUrl>
#include <QFile>
#include <QFileInfo>
#include <QDateTime>
#include <QCryptographicHash>
#include <QRegularExpression>
#include <QSslConfiguration>
#include <QSslSocket>
#include <quuid.h>
OSSClient::OSSClient(const QString &endpoint, const QString &bucketName,
                     const QString &region, QObject *parent) :
    QObject(parent) {
    auto conf = alibabacloud::oss2::ClientConfiguration::loadDefault();
    this->region = region;
    conf.region = region.toStdString();
    conf.endpoint = endpoint.toStdString();
    conf.credentialsProvider = std::make_shared<alibabacloud::oss2::EnvironmentVariableCredentialsProvider>();

    this->bucketName = bucketName;

    client = new alibabacloud::oss2::OSSClient(conf);

}

QString OSSClient::putData(const QString filePath) {
    QString  objectKey = QUuid::createUuid().toString();
    objectKey = objectKey.mid(1, objectKey.length() - 2);
    objectKey+=filePath.section('.',-1);
    auto outcome = client->putObjectFromFile(
        alibabacloud::oss2::models::PutObjectRequest()
        .setBucket(bucketName.toStdString())
        .setKey(objectKey.toStdString()),
        filePath.toStdString()
        );
    QString url =QString("https://%1.%2.aliyuncs.com/%3").arg(bucketName).arg("oss-"+region).arg(objectKey);
    return url;
}

void OSSClient::deleteData(const QString url) {
    QString key = url.section('/',-1);
    client->deleteObject(
        alibabacloud::oss2::models::DeleteObjectRequest()
        .setBucket(bucketName.toStdString())
        .setKey(key.toStdString()));
}

