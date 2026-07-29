//
// Created by 114514 on 2026/7/28.
//

// You may need to build the project (run Qt uic code generator) to get "ui_EmployeeDialog.h" resolved

#include "employeedialog.h"
#include "ui_EmployeeDialog.h"


EmployeeDialog::EmployeeDialog(QWidget *parent) : QDialog(parent), ui(new Ui::EmployeeDialog) {
    ui->setupUi(this);


}

EmployeeDialog::~EmployeeDialog() {
    delete ui;
}

QString EmployeeDialog::getName() {
    return ui->lineEdit->text();
}

int EmployeeDialog::getFloor() {
    return ui->spinBox->value();
}

void EmployeeDialog::setDefaultValues(const employee& e) {
    ui->lineEdit->setText(e.name);
    ui->spinBox->setValue(e.floor);
}

void EmployeeDialog::clear() {
    ui->lineEdit->clear();
    ui->spinBox->setValue(0);
}


