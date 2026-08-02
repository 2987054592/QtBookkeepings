//
// Created by 114514 on 2026/7/29.
//

#ifndef BOOKKEEPINGS_BAGDIALOG_H
#define BOOKKEEPINGS_BAGDIALOG_H

#include <QDialog>
#include <QVector>

#include "po/processs.h"
#include "bagprocessdialog.h"
#include "network/NetworkManager.h"
#include "network/OSSClient.h"
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

    void setBag(const Bag &bag);
    void clear();
private slots:
    void addMoreProcess();
    void chooseImage();
    void deleteProcess();
    void updateProessPrice();
private:
    Ui::BagDialog *ui;
    QStandardItemModel *model;
    QVector<BagProcess> row;
    bagprocessdialog *dialog=nullptr;
    QString m_path;
    int m_bagId;
    NetworkManager *networkManager;
    OSSClient *ossClient;
};


#endif //BOOKKEEPINGS_BAGDIALOG_H