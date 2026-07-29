//
// Created by 114514 on 2026/7/28.
//

#ifndef BOOKKEEPINGS_EMPLOYEEDIALOG_H
#define BOOKKEEPINGS_EMPLOYEEDIALOG_H

#include <QDialog>
#include "po/employee.h"


QT_BEGIN_NAMESPACE

namespace Ui {
    class EmployeeDialog;
}

QT_END_NAMESPACE

class EmployeeDialog : public QDialog {
    Q_OBJECT

public:
    explicit EmployeeDialog(QWidget *parent = nullptr);

    ~EmployeeDialog() override;
    QString getName();
    int getFloor();
    void setDefaultValues(const employee& e);
    void clear();
private:
    Ui::EmployeeDialog *ui;

};


#endif //BOOKKEEPINGS_EMPLOYEEDIALOG_H
