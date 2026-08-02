//
// Created by 114514 on 2026/8/2.
//

#ifndef BOOKKEEPINGS_OSSCLIENT_H
#define BOOKKEEPINGS_OSSCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

// 阿里云 OSS 客户端（V4 签名，HMAC-SHA256，纯 Qt 实现，不依赖官方 SDK）
//
// 适用场景：记账软件把凭证图片上传到 OSS，公共读 bucket 下按 URL 直接展示，并支持删除。
//   - putObject()    上传本地文件 / 内存数据（PUT Object），异步
//   - deleteObject() 删除对象（DELETE Object），异步
//   - publicUrl()    生成公共读访问 URL（无需签名）
//
// 说明：
//   - 新建的 bucket 只能使用 V4 签名（V1 签名已下线），因此这里全部走 V4。
//   - AccessKey 会以明文留在程序里，请务必使用 RAM 子账号并只授权该 bucket 的最小权限，
//     不要把主账号 AK 写死进来。
//   - 这个类自持 QNetworkAccessManager，按请求各自处理响应；不要和 NetworkManager
//     （JSON 后端接口用）混用。
class OSSClient : public QObject {
    Q_OBJECT
public:
    explicit OSSClient(const QString &endpoint,           // 例如 "oss-cn-hangzhou.aliyuncs.com"
                       const QString &accessKeyId,
                       const QString &accessKeySecret,
                       const QString &bucketName,
                       const QString &region = QString(), // 空则从 endpoint 自动推断（如 cn-hangzhou）
                       QObject *parent = nullptr);

    // 上传本地文件，异步，完成后发 uploadFinished(objectKey, success, error)
    void putObject(const QString &objectKey, const QString &filePath,
                   const QString &contentType = QString());

    // 上传内存数据，异步，完成后发 uploadFinished(objectKey, success, error)
    void putObject(const QString &objectKey, const QByteArray &data,
                   const QString &contentType = QString());

    // 删除对象，异步，完成后发 deleteFinished(objectKey, success, error)
    void deleteObject(const QString &objectKey);

    // 公共读 bucket 下对象的直接访问 URL（无需签名，可直接用于展示）
    QString publicUrl(const QString &objectKey) const;

    // 按 RFC3986 编码对象路径（保留 '/'，URL 与签名共用同一份编码，避免对不上）
    static QByteArray percentEncodePath(const QString &path);

signals:
    void uploadFinished(const QString &objectKey, bool success, const QString &error = QString());
    void deleteFinished(const QString &objectKey, bool success, const QString &error = QString());

private:
    // HMAC-SHA256（QCryptographicHash 只提供裸 SHA256，HMAC 需手写）
    static QByteArray hmacSha256(const QByteArray &key, const QByteArray &message);

    // 计算 V4 签名并写入请求头（Authorization / x-oss-date / x-oss-content-sha256 / Content-MD5 等）
    void applyAuthV4(QNetworkRequest &req, const QString &verb,
                     const QString &objectKey, const QByteArray &body,
                     const QString &contentType);

    // 构造请求 URL：https://<bucket>.<endpoint>/<key>
    QUrl buildUrl(const QString &objectKey) const;

    // 从 endpoint 推断 region，例如 oss-cn-hangzhou.aliyuncs.com -> cn-hangzhou
    QString inferRegion() const;

    // 清洗 endpoint：去掉 https:// 等协议头、路径、多余的 bucket 前缀
    //   https://oss-cn-beijing.aliyuncs.com         -> oss-cn-beijing.aliyuncs.com
    //   https://javazou.oss-cn-beijing.aliyuncs.com -> oss-cn-beijing.aliyuncs.com
    QString sanitizeEndpoint(const QString &raw) const;

    // 从回复里提取 OSS 错误信息（响应体是 XML）
    QString ossErrorMessage(QNetworkReply *reply) const;

    // 从文件名猜 content-type（图片常见类型）
    static QString guessContentType(const QString &fileName);

    QString endpoint;
    QString accessKeyId;
    QString accessKeySecret;
    QString bucketName;
    QString region;

    QNetworkAccessManager *nam = nullptr;
};

#endif //BOOKKEEPINGS_OSSCLIENT_H
