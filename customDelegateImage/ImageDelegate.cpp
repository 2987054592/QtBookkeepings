//
// Created by 114514 on 2026/7/29.
//

#include "ImageDelegate.h"

ImageDelegate::ImageDelegate(QObject *parent) : QStyledItemDelegate(parent) {
}

void ImageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QString path=index.data(Qt::DisplayRole).toString();
    if (path.isEmpty()) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }
    QPixmap pixmap(path);
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

