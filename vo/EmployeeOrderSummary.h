//
// Created by 114514 on 2026/7/31.
//

#ifndef BOOKKEEPINGS_EMPLOYEEORDERSUMMARY_H
#define BOOKKEEPINGS_EMPLOYEEORDERSUMMARY_H
#include <QString>
#include <QDate>
#include <QVector>

#include "po/orderDetail.h"

class EmployeeOrderSummary {
public:
    int orderId;
    QString orderName;
    QDate orderDate;
    QVector<orderDetail> details;
    qint64 totalPrice;
};


#endif //BOOKKEEPINGS_EMPLOYEEORDERSUMMARY_H
