//
// Created by 114514 on 2026/7/31.
//

#ifndef BOOKKEEPINGS_EMPLOYEESALARYDIALOG_H
#define BOOKKEEPINGS_EMPLOYEESALARYDIALOG_H

#include <QDialog>

#include "po/employee.h"
#include "vo/EmployeeSalary.h"


QT_BEGIN_NAMESPACE

namespace Ui {
    class EmployeeSalaryDialog;
}

QT_END_NAMESPACE

class EmployeeSalaryDialog : public QDialog {
    Q_OBJECT

public:
    explicit EmployeeSalaryDialog(QWidget *parent = nullptr);

    ~EmployeeSalaryDialog() override;

    void setEmployee(const employee & employee);
private:
    Ui::EmployeeSalaryDialog *ui;
    //获取组装对应的信息
    QVector<EmployeeSalary> employeeSalaryList;
};


#endif //BOOKKEEPINGS_EMPLOYEESALARYDIALOG_H
