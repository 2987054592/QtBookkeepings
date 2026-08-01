//
// Created by 114514 on 2026/7/30.
//

#ifndef BOOKKEEPINGS_ORDERDEATILDAO_H
#define BOOKKEEPINGS_ORDERDEATILDAO_H

#include <QString>

#include "po/orderDetail.h"
#include "po/Result.h"
#include <QSqlQuery>

#include "dialog/employeesalarydialog.h"
#include "po/QueryPage.h"

class OrderDeatilDao {
public:
    static Result<QString> addOrderDetail(const orderDetail &orderDetail);
    static Result<QVector<orderDetail>> getOrderDetailList(int orderId);
    static Result<QString> deleteByOrderId(int orderId);

    static Result<QMap<int,QVector<orderDetail>>> getOrderDetailListByOrderIds(const QSet<int> & set,int id);

    static Result<QueryPage<QMap<int,QVector<orderDetail>>>> getOrderDetailListByEmployeeId(int current_page, int page_size, int id);

    static Result<bool> getorderDetailByProcessId(int process_id);

    static Result<bool> IsEmployeeUsed(int employee_id);
};



#endif //BOOKKEEPINGS_ORDERDEATILDAO_H
