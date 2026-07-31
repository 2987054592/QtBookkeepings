//
// Created by 114514 on 2026/7/30.
//

#ifndef BOOKKEEPINGS_ORDERDETAIL_H
#define BOOKKEEPINGS_ORDERDETAIL_H
#include <QString>

class orderDetail {
public:
    int id;
    int processId;
    mutable int orderId;
    qint64 real_price;
    int real_quantity;
    int employeeId;
};


#endif //BOOKKEEPINGS_ORDERDETAIL_H
