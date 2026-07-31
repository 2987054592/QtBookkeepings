//
// Created by 114514 on 2026/7/30.
//

#ifndef BOOKKEEPINGS_ORDERDIALOG_H
#define BOOKKEEPINGS_ORDERDIALOG_H

#include <QDialog>
#include <QStandardItemModel>

#include "orderprocessdialog.h"
#include "customDelegateImage/ComboxDelegate.h"
#include "po/bag.h"
#include "po/order.h"
#include "po/Result.h"


QT_BEGIN_NAMESPACE

namespace Ui {
    class OrderDialog;
}

QT_END_NAMESPACE

class OrderDialog : public QDialog {
    Q_OBJECT

public:
    explicit OrderDialog(QWidget *parent = nullptr);

    ~OrderDialog() override;
    void setBagList(const QVector<Bag>& bags);
    order getOrder();
    void setOrder(const order &order);
private:
    Ui::OrderDialog *ui;
    Result<QString> loadProcess(int index);
    QStandardItemModel *model;
    ComboxDelegate *comboxDelegate;
    OrderProcessDialog *orderProcessDialog=nullptr;
    int m_orderId=0;
private slots:
    void AddMoreProcess();
    void AllNumber();
    void DeleteProcess();
};


#endif //BOOKKEEPINGS_ORDERDIALOG_H
