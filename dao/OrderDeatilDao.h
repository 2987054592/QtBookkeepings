//
// Created by 114514 on 2026/7/30.
//

#ifndef BOOKKEEPINGS_ORDERDEATILDAO_H
#define BOOKKEEPINGS_ORDERDEATILDAO_H

#include <QString>

#include "po/orderDetail.h"
#include "po/Result.h"
#include <QSqlQuery>
class OrderDeatilDao {
public:
    static Result<QString> addOrderDetail(const orderDetail &orderDetail);
    static Result<QVector<orderDetail>> getOrderDetailList(int orderId);
    static Result<QString> deleteByOrderId(int orderId);
};



#endif //BOOKKEEPINGS_ORDERDEATILDAO_H
