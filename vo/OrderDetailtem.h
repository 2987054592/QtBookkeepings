//
// Created by 114514 on 2026/7/31.
//

#ifndef BOOKKEEPINGS_ORDERDETAILTEM_H
#define BOOKKEEPINGS_ORDERDETAILTEM_H
#include <qglobal.h>
#include <QString>


class OrderDetailtem {
public:
    int detailId;
    int processId;
    QString processName;
    qint64 real_price;
    int real_quantity;
    qint64 total_price;
};


#endif //BOOKKEEPINGS_ORDERDETAILTEM_H
