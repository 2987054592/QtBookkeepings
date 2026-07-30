//
// Created by 114514 on 2026/7/30.
//

#ifndef BOOKKEEPINGS_ORDERDAO_H
#define BOOKKEEPINGS_ORDERDAO_H
#include <QSqlQuery>

#include "po/order.h"
#include "po/QueryPage.h"
#include "po/Result.h"

class OrderDao {
public:
    static Result<QString> addOrder(const order &order);
    static Result<QString> deleteOrder(const order &order);
    static Result<QString> updateOrder(const order &order);
    static Result<QueryPage<QVector<order>>> queryOrderPage(const int &currPage,const int &pageSize,const QString &name);
};


#endif //BOOKKEEPINGS_ORDERDAO_H
