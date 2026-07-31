//
// Created by 114514 on 2026/7/30.
//
#include <QComboBox>
#include "ComboxDelegate.h"
ComboxDelegate::ComboxDelegate(QObject *parent) : QStyledItemDelegate(parent) {
}

QWidget * ComboxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
    const QModelIndex &index) const {
    auto *m_combo=new QComboBox(parent);
    for (auto &employee:m_employees) {
        m_combo->addItem(employee.name,QVariant(employee.id));
    }
    return m_combo;
}

void ComboxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    int comboIndex = comboBox->findText(value);

    if (comboIndex >= 0) {
        comboBox->setCurrentIndex(comboIndex);
    }
}

void ComboxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    model->setData(index, comboBox->currentData(Qt::UserRole), Qt::UserRole);
    model->setData(index, comboBox->currentText(), Qt::EditRole);
}

void ComboxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
    const QModelIndex &index) const {
    editor->setGeometry(option.rect);
}

void ComboxDelegate::setData(const QVector<employee> &employees) {
    m_employees=employees;
}
