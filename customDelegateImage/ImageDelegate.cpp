//
// Created by 114514 on 2026/7/29.
//

#include "ImageDelegate.h"

#include <QNetworkReply>
#include <QSslConfiguration>
#include <QSslSocket>

ImageDelegate::ImageDelegate(QObject *parent) : QStyledItemDelegate(parent),
                                                nam(new QNetworkAccessManager(this)) {
}

void ImageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QString path=index.data(Qt::DisplayRole).toString();
    if (path.isEmpty()) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }
    QPixmap pixmap=fetchPixmap(path);
    if (pixmap.isNull()) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }

    pixmap = pixmap.scaled(option.rect.size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    const int x = option.rect.x()+(option.rect.width()-pixmap.width())/2;
    const int y = option.rect.y()+(option.rect.height()-pixmap.height())/2;
    painter->drawPixmap(x,y,pixmap);

}

QSize ImageDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return QSize(60,60);
}

QPixmap ImageDelegate::fetchPixmap(const QString &urls) const {
    const QUrl url(urls);
    if (urlCache.contains(url)) {
        return urlCache.value(url);
    }
    if (pending.contains(url)) {
        return QPixmap();
    }
    pending.insert(url);

    QNetworkRequest req(url);
    QSslConfiguration ssl = QSslConfiguration::defaultConfiguration();
    ssl.setPeerVerifyMode(QSslSocket::VerifyNone);   // 与本项目其它请求保持一致
    req.setSslConfiguration(ssl);

    QNetworkReply *reply = nam->get(req);
    connect(reply, &QNetworkReply::finished, this, [this, reply, url]() {
        if (reply->error() == QNetworkReply::NoError) {
            QPixmap pm;
            if (pm.loadFromData(reply->readAll())) {
                urlCache.insert(url, pm);
                emit const_cast<ImageDelegate *>(this)->imageLoaded();
            }
        }
        reply->deleteLater();
    });
    return QPixmap();
}

