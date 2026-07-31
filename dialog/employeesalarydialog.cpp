//
// Created by 114514 on 2026/7/31.
//

// You may need to build the project (run Qt uic code generator) to get "ui_EmployeeSalaryDialog.h" resolved

#include "employeesalarydialog.h"
#include "ui_EmployeeSalaryDialog.h"


EmployeeSalaryDialog::EmployeeSalaryDialog(QWidget *parent) : QDialog(parent), ui(new Ui::EmployeeSalaryDialog) {
    ui->setupUi(this);
}

EmployeeSalaryDialog::~EmployeeSalaryDialog() {
    delete ui;
}

void EmployeeSalaryDialog::setEmployee(const employee &employee) {
    //根据员工id通过OrderDao获取该员工的所有信息（分页查询）

    //根据获取的订单信息，再到OrderdetailDao获取订单详情信息

    //最终组装信息
}
