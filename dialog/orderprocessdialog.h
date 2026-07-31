//
// Created by 114514 on 2026/7/31.
//

#ifndef BOOKKEEPINGS_ORDERPROCESSDIALOG_H
#define BOOKKEEPINGS_ORDERPROCESSDIALOG_H

#include <QDialog>

#include "po/employee.h"
#include "po/orderDetail.h"
#include "po/processs.h"


QT_BEGIN_NAMESPACE

namespace Ui {
    class OrderProcessDialog;
}

QT_END_NAMESPACE

class OrderProcessDialog : public QDialog {
    Q_OBJECT

public:
    explicit OrderProcessDialog(QWidget *parent = nullptr);

    ~OrderProcessDialog() override;
    void setDataEmployee(const QVector<employee>& employees);
    void setDataProcess(const QVector<processs>& processes);
    orderDetail getOrderDetail();
private:
    Ui::OrderProcessDialog *ui;
};


#endif //BOOKKEEPINGS_ORDERPROCESSDIALOG_H
