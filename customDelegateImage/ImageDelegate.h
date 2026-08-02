//
// Created by 114514 on 2026/7/29.
//

#ifndef BOOKKEEPINGS_IMAGEDELEGATE_H
#define BOOKKEEPINGS_IMAGEDELEGATE_H
#include <QNetworkAccessManager>
#include <QStyledItemDelegate>
#include <QPainter>
class ImageDelegate : public QStyledItemDelegate{
    Q_OBJECT
public:
    ImageDelegate(QObject* parent=nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
private:
    QPixmap fetchPixmap(const QString &url) const;
    QNetworkAccessManager *nam;
    mutable QHash<QUrl, QPixmap> urlCache;
    mutable QSet<QUrl> pending;
    signals:
    void imageLoaded();
};


#endif //BOOKKEEPINGS_IMAGEDELEGATE_H
