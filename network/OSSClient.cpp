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

// ----------------------------------------------------------------------------
// 构造
// ----------------------------------------------------------------------------
OSSClient::OSSClient(const QString &endpoint, const QString &accessKeyId,
                     const QString &accessKeySecret, const QString &bucketName,
                     const QString &region, QObject *parent) :
    QObject(parent), endpoint(endpoint), accessKeyId(accessKeyId),
    accessKeySecret(accessKeySecret), bucketName(bucketName), region(region) {
    this->endpoint = sanitizeEndpoint(endpoint);
    if (this->region.isEmpty())
        this->region = inferRegion();
    nam = new QNetworkAccessManager(this);
}

// ----------------------------------------------------------------------------
// HMAC-SHA256（QCryptographicHash 只提供裸 SHA256，HMAC 需自行拼 inner/outer pad）
// ----------------------------------------------------------------------------
QByteArray OSSClient::hmacSha256(const QByteArray &key, const QByteArray &message) {
    const int blockSize = 64;
    QByteArray k = key;
    if (k.size() > blockSize)
        k = QCryptographicHash::hash(k, QCryptographicHash::Sha256);
    k = k.leftJustified(blockSize, '\0');   // 不足 64 字节右侧补 0

    QByteArray oPad = k, iPad = k;
    for (int i = 0; i < blockSize; ++i) {
        oPad[i] = static_cast<char>(k[i] ^ 0x5c);
        iPad[i] = static_cast<char>(k[i] ^ 0x36);
    }
    QByteArray inner = QCryptographicHash::hash(iPad + message, QCryptographicHash::Sha256);
    QByteArray outer = QCryptographicHash::hash(oPad + inner, QCryptographicHash::Sha256);
    return outer;
}

// ----------------------------------------------------------------------------
// RFC3986 路径编码：保留 '/'，其余非保留字符全部百分号编码
// ----------------------------------------------------------------------------
QByteArray OSSClient::percentEncodePath(const QString &path) {
    return QUrl::toPercentEncoding(path, "/");
}

// ----------------------------------------------------------------------------
// 从 endpoint 推断 region
//   oss-cn-hangzhou.aliyuncs.com        -> cn-hangzhou
//   oss-cn-hangzhou-internal.aliyuncs.com -> cn-hangzhou
//   oss.aliyuncs.com                     -> cn-hangzhou（默认华东1）
// 也可以直接在构造函数里显式传 region。
// ----------------------------------------------------------------------------
QString OSSClient::inferRegion() const {
    QString host = endpoint;
    const QString suffix = ".aliyuncs.com";
    if (host.endsWith(suffix))
        host.chop(suffix.size());
    if (host == "oss")
        return "cn-beijing";
    if (host.startsWith("oss-"))
        return host.mid(4).remove("-internal");
    return "cn-beijing";
}

// ----------------------------------------------------------------------------
// 清洗 endpoint
//   去掉协议头、路径；若用户把整个 bucket 域名当 endpoint 传了，把 "bucket." 前缀剥掉
// ----------------------------------------------------------------------------
QString OSSClient::sanitizeEndpoint(const QString &raw) const {
    QString e = raw.trimmed();
    if (e.startsWith("https://", Qt::CaseInsensitive))
        e = e.mid(8);
    else if (e.startsWith("http://", Qt::CaseInsensitive))
        e = e.mid(7);
    const int slash = e.indexOf('/');
    if (slash >= 0)
        e = e.left(slash);
    const QString prefix = bucketName + ".";
    if (e.startsWith(prefix))
        e = e.mid(prefix.size());
    return e;
}

// ----------------------------------------------------------------------------
// URL 构造：https://<bucket>.<endpoint>/<key>（virtual-hosted 风格）
// ----------------------------------------------------------------------------
QUrl OSSClient::buildUrl(const QString &objectKey) const {
    const QString host = bucketName + "." + endpoint;
    const QString urlStr = "https://" + host + "/" + QString::fromUtf8(percentEncodePath(objectKey));
    // 用字符串构造 QUrl，QUrl 不会把已有的 %XX 再编码一遍
    return QUrl(urlStr);
}

// ----------------------------------------------------------------------------
// OSS V4 签名（OSS4-HMAC-SHA256）
//   签名要求来自阿里云官方文档：
//     - CanonicalRequest 的 URI 必须带 bucket 名（/bucket/key）
//     - AdditionalHeaders 只列 host；content-type / content-md5 / x-oss-* 自动参与签名
//     - payload 使用 UNSIGNED-PAYLOAD，请求头带 x-oss-content-sha256: UNSIGNED-PAYLOAD
// ----------------------------------------------------------------------------
void OSSClient::applyAuthV4(QNetworkRequest &req, const QString &verb,
                            const QString &objectKey, const QByteArray &body,
                            const QString &contentType) {
    const QDateTime nowUtc = QDateTime::currentDateTimeUtc();
    const QString dateStr = nowUtc.toString("yyyyMMdd");                 // 20260802
    const QString dateTimeStr = nowUtc.toString("yyyyMMdd'T'HHmmss'Z'"); // 20260802T153045Z

    // ---- 1. CanonicalRequest ----
    const QString canonicalUri = "/" + bucketName + "/" + QString::fromUtf8(percentEncodePath(objectKey));
    const QString canonicalQueryString;   // 上传/删除没有子资源，为空

    // 参与签名的头：小写名、值去首尾空格，按名字典序（QMap 自带排序）
    QMap<QString, QString> headersToSign;
    headersToSign.insert("host", bucketName + "." + endpoint);
    headersToSign.insert("x-oss-date", dateTimeStr);
    headersToSign.insert("x-oss-content-sha256", "UNSIGNED-PAYLOAD");
    if (!contentType.isEmpty())
        headersToSign.insert("content-type", contentType);
    const QByteArray contentMd5 = verb == "PUT" && !body.isEmpty()
        ? QCryptographicHash::hash(body, QCryptographicHash::Md5).toBase64()
        : QByteArray();
    if (!contentMd5.isEmpty())
        headersToSign.insert("content-md5", QString::fromLatin1(contentMd5));

    QString canonicalHeaders;
    for (auto it = headersToSign.begin(); it != headersToSign.end(); ++it)
        canonicalHeaders += it.key() + ":" + it.value().trimmed() + "\n";

    // AdditionalHeaders：只有 host（content-type/content-md5/x-oss-* 自动参与，不能写进来）
    const QString signedHeaders = "host";

    const QString canonicalRequest = verb + "\n"
                                   + canonicalUri + "\n"
                                   + canonicalQueryString + "\n"
                                   + canonicalHeaders + "\n"       // 上面每行头已带 \n，这里补一个空行
                                   + signedHeaders + "\n"
                                   + "UNSIGNED-PAYLOAD";

    // ---- 2. StringToSign ----
    const QByteArray hashedCanonical =
        QCryptographicHash::hash(canonicalRequest.toUtf8(), QCryptographicHash::Sha256).toHex();
    const QString scope = dateStr + "/" + region + "/oss/aliyun_v4_request";
    const QString stringToSign = "OSS4-HMAC-SHA256\n"
                               + dateTimeStr + "\n"
                               + scope + "\n"
                               + QString::fromLatin1(hashedCanonical);

    // ---- 3. 派生签名密钥（与 AWS SigV4 类似，但初始串是 "aliyun_v4"+SK） ----
    const QByteArray dateKey = hmacSha256(("aliyun_v4" + accessKeySecret).toUtf8(), dateStr.toUtf8());
    const QByteArray dateRegionKey = hmacSha256(dateKey, region.toUtf8());
    const QByteArray dateRegionServiceKey = hmacSha256(dateRegionKey, QByteArray("oss"));
    const QByteArray signingKey = hmacSha256(dateRegionServiceKey, QByteArray("aliyun_v4_request"));

    // ---- 4. 签名与 Authorization ----
    const QByteArray signature = hmacSha256(signingKey, stringToSign.toUtf8()).toHex();
    const QString authorization = "OSS4-HMAC-SHA256 Credential=" + accessKeyId + "/" + scope
                                + ", AdditionalHeaders=" + signedHeaders
                                + ", Signature=" + QString::fromLatin1(signature);

    // ---- 5. 写入请求头 ----
    req.setRawHeader("Date", nowUtc.toString("ddd, dd MMM yyyy hh:mm:ss 'GMT'").toUtf8());
    req.setRawHeader("x-oss-date", dateTimeStr.toUtf8());
    req.setRawHeader("x-oss-content-sha256", "UNSIGNED-PAYLOAD");
    req.setRawHeader("Authorization", authorization.toUtf8());
    if (!contentType.isEmpty())
        req.setHeader(QNetworkRequest::ContentTypeHeader, contentType);
    if (!contentMd5.isEmpty())
        req.setRawHeader("Content-MD5", contentMd5);
}

// ----------------------------------------------------------------------------
// 上传：文件
// ----------------------------------------------------------------------------
void OSSClient::putObject(const QString &objectKey, const QString &filePath,
                          const QString &contentType) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        emit uploadFinished(objectKey, false, "无法打开文件: " + filePath);
        return;
    }
    const QByteArray data = file.readAll();
    const QString type = contentType.isEmpty() ? guessContentType(filePath) : contentType;
    putObject(objectKey, data, type);
}

// ----------------------------------------------------------------------------
// 上传：内存数据（PUT Object，异步）
// ----------------------------------------------------------------------------
void OSSClient::putObject(const QString &objectKey, const QByteArray &data,
                          const QString &contentType) {
    QNetworkRequest req;
    req.setUrl(buildUrl(objectKey));
    req.setHeader(QNetworkRequest::ContentLengthHeader, data.size());

    // 与项目现有网络代码一致：本机/内网环境证书链可能不全，先忽略 SSL 校验便于调试
    QSslConfiguration ssl = QSslConfiguration::defaultConfiguration();
    ssl.setPeerVerifyMode(QSslSocket::VerifyNone);
    req.setSslConfiguration(ssl);

    applyAuthV4(req, "PUT", objectKey, data, contentType);

    QNetworkReply *reply = nam->put(req, data);
    connect(reply, &QNetworkReply::finished, this, [this, reply, objectKey]() {
        const bool ok = (reply->error() == QNetworkReply::NoError);
        const QString err = ok ? QString() : ossErrorMessage(reply);
        reply->deleteLater();
        emit uploadFinished(objectKey, ok, err);
    });
}

// ----------------------------------------------------------------------------
// 删除（DELETE Object，异步）
// ----------------------------------------------------------------------------
void OSSClient::deleteObject(const QString &objectKey) {
    QNetworkRequest req;
    req.setUrl(buildUrl(objectKey));

    QSslConfiguration ssl = QSslConfiguration::defaultConfiguration();
    ssl.setPeerVerifyMode(QSslSocket::VerifyNone);
    req.setSslConfiguration(ssl);

    applyAuthV4(req, "DELETE", objectKey, QByteArray(), QString());

    QNetworkReply *reply = nam->deleteResource(req);
    connect(reply, &QNetworkReply::finished, this, [this, reply, objectKey]() {
        const bool ok = (reply->error() == QNetworkReply::NoError);
        const QString err = ok ? QString() : ossErrorMessage(reply);
        reply->deleteLater();
        emit deleteFinished(objectKey, ok, err);
    });
}

// ----------------------------------------------------------------------------
// 公共读 bucket 的直接访问 URL
// ----------------------------------------------------------------------------
QString OSSClient::publicUrl(const QString &objectKey) const {
    return "https://" + bucketName + "." + endpoint + "/" + QString::fromUtf8(percentEncodePath(objectKey));
}

// ----------------------------------------------------------------------------
// 从 OSS 的 XML 错误响应里提取 Message
// ----------------------------------------------------------------------------
QString OSSClient::ossErrorMessage(QNetworkReply *reply) const {
    const QByteArray body = reply->readAll();
    static const QRegularExpression re("<Message>(.*?)</Message>");
    const QRegularExpressionMatch m = re.match(QString::fromUtf8(body));
    if (m.hasMatch())
        return m.captured(1);
    if (!body.isEmpty())
        return reply->errorString() + " | " + QString::fromUtf8(body.left(200));
    return reply->errorString();
}

// ----------------------------------------------------------------------------
// 从文件名猜 content-type
// ----------------------------------------------------------------------------
QString OSSClient::guessContentType(const QString &fileName) {
    const QString ext = QFileInfo(fileName).suffix().toLower();
    if (ext == "jpg" || ext == "jpeg") return "image/jpeg";
    if (ext == "png") return "image/png";
    if (ext == "gif") return "image/gif";
    if (ext == "bmp") return "image/bmp";
    if (ext == "webp") return "image/webp";
    if (ext == "svg") return "image/svg+xml";
    if (ext == "pdf") return "application/pdf";
    return "application/octet-stream";
}
