//
// Created by 114514 on 2026/7/29.
//

#ifndef BOOKKEEPINGS_BAGDIALOG_H
#define BOOKKEEPINGS_BAGDIALOG_H

#include <QDialog>
#include <QVector>

#include "po/processs.h"
#include "bagprocessdialog.h"
#include "po/bag.h"

QT_BEGIN_NAMESPACE


namespace Ui {
    class BagDialog;
}

QT_END_NAMESPACE
#include <QStandardItemModel>
class BagDialog : public QDialog {
    Q_OBJECT

public:
    explicit BagDialog(QWidget *parent = nullptr);

    ~BagDialog() override;

    Bag getBag();
    QVector<processs> getProcessRow();
private slots:
    void addMoreProcess();
    void chooseImage();
private:
    Ui::BagDialog *ui;
    QStandardItemModel *model;
    QVector<processs> row;
    bagprocessdialog *dialog=nullptr;
    QString m_path;
};


#endif //BOOKKEEPINGS_BAGDIALOG_H