//
// Created by 114514 on 2026/7/30.
//

#ifndef BOOKKEEPINGS_ORDERDAO_H
#define BOOKKEEPINGS_ORDERDAO_H
#include <QSqlQuery>

#include "enums/TimeRangeType.h"
#include "po/employee.h"
#include "po/order.h"
#include "po/QueryPage.h"
#include "po/Result.h"

class OrderDao {
public:
    static Result<QString> addOrder(const order &order);
    static Result<QString> deleteOrder(const int& id);
    static Result<QString> updateOrder(const order &order);
    static Result<QueryPage<QVector<order>>> queryOrderPage(const int &currPage,const int &pageSize,const QString &name,const int &floor);

    static Result<order> getOrder(int id);

    static Result<QMap<QString,QVector<order>>> getOrderByOrderIds(const QSet<int> &orderIds);

    static Result<bool> getByBagId(int bag_id);

    static Result<QVector<order>> getOrderByTime(const TimeRange & time);
};


#endif //BOOKKEEPINGS_ORDERDAO_H
