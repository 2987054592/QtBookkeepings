//
// Created by 114514 on 2026/7/29.
//

#ifndef BOOKKEEPINGS_IMAGEDELEGATE_H
#define BOOKKEEPINGS_IMAGEDELEGATE_H
#include <QStyledItemDelegate>
#include <QPainter>
class ImageDelegate : public QStyledItemDelegate{
public:
    ImageDelegate(QObject* parent=nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};


#endif //BOOKKEEPINGS_IMAGEDELEGATE_H
