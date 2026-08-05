//
// Created by 114514 on 2026/7/31.
//

// You may need to build the project (run Qt uic code generator) to get "ui_OrderProcessDialog.h" resolved

#include "orderprocessdialog.h"
#include "ui_OrderProcessDialog.h"


OrderProcessDialog::OrderProcessDialog(QWidget *parent) : QDialog(parent), ui(new Ui::OrderProcessDialog) {
    ui->setupUi(this);

}

OrderProcessDialog::~OrderProcessDialog() {
    delete ui;
}

void OrderProcessDialog::setDataEmployee(const QVector<employee> &employees) {
    ui->comboBoxEmployee->clear();
    for (auto &employee : employees) {
        ui->comboBoxEmployee->addItem(employee.name,employee.id);
    }
}

void OrderProcessDialog::setDataProcess(const QVector<processs> &processes) {
    ui->comboBoxProcess->clear();
    for (auto &process : processes) {
        ui->comboBoxProcess->addItem(process.name,process.id);
    }
}

orderDetail OrderProcessDialog::getOrderDetail() {
    orderDetail orderDetail;
    orderDetail.employeeId = ui->comboBoxEmployee->currentData().toInt();
    orderDetail.processId = ui->comboBoxProcess->currentData().toInt();
    orderDetail.real_price = ui->lineEditPrice->text().toDouble()*1000;
    orderDetail.real_quantity = ui->lineEditNumber->text().toInt();
    return orderDetail;
}
