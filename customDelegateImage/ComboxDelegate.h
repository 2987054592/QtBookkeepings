//
// Created by 114514 on 2026/7/30.
//

#ifndef BOOKKEEPINGS_COMBOXDELEGATE_H
#define BOOKKEEPINGS_COMBOXDELEGATE_H

#include <QVector>
#include <QStyledItemDelegate>

#include "po/employee.h"

class ComboxDelegate : public QStyledItemDelegate {
    Q_OBJECT
private:
    QVector<employee> m_employees;

public:
    ComboxDelegate(QObject *parent = nullptr);
    // editing
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;

    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const Q_DECL_OVERRIDE;

    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setData(const QVector<employee> &employees);
};


#endif //BOOKKEEPINGS_COMBOXDELEGATE_H
