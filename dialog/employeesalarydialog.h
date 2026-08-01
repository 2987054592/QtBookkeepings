//
// Created by 114514 on 2026/7/31.
//

#ifndef BOOKKEEPINGS_EMPLOYEESALARYDIALOG_H
#define BOOKKEEPINGS_EMPLOYEESALARYDIALOG_H

#include <QDialog>
#include <QStandardItemModel>

#include "po/employee.h"



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
private slots:
    void prevPage();
    void nextPage();
private:
    void loadSalary();
    int m_employeeId=0;
    QString m_employeeName;


    Ui::EmployeeSalaryDialog *ui;
    int currentPage=1;
    int pageSize=10;
    QStandardItemModel *model;

};


#endif //BOOKKEEPINGS_EMPLOYEESALARYDIALOG_H
