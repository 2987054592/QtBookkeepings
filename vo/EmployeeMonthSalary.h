//
// Created by 114514 on 2026/7/31.
//

#ifndef BOOKKEEPINGS_EMPLOYEEMONTHSALARY_H
#define BOOKKEEPINGS_EMPLOYEEMONTHSALARY_H
#include <QString>

#include "EmployeeOrderSummary.h"

class EmployeeMonthSalary {
public:
    QString month;
    QVector<EmployeeOrderSummary> orders;
    qint64 totalSalary;

};


#endif //BOOKKEEPINGS_EMPLOYEEMONTHSALARY_H
