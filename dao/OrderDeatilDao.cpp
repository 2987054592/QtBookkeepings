//
// Created by 114514 on 2026/7/30.
//

#include "OrderDeatilDao.h"

#include <qset.h>
#include <QVariant>
#include <QSqlError>
#include "DatabaseManager.h"
#include <QVector>
Result<QString> OrderDeatilDao::addOrderDetail(const orderDetail &orderDetail) {
   if (!DatabaseManager::isOpen()) {
      DatabaseManager::initialize();
   }
   QString sql = "INSERT INTO order_detail (process_id,order_id,real_price,real_quantity,employee_id) VALUES (:process_id,:order_id,:real_price,:real_quantity,:employee_id)";
   QSqlQuery query(DatabaseManager::getDatabase());
   query.prepare(sql);
   query.bindValue(":process_id",QVariant(orderDetail.processId));
   query.bindValue(":order_id",QVariant(orderDetail.orderId));
   query.bindValue(":real_price",QVariant(orderDetail.real_price));
   query.bindValue(":real_quantity",QVariant(orderDetail.real_quantity));
   query.bindValue(":employee_id",QVariant(orderDetail.employeeId));
   if (!query.exec()) {
      return Result<QString>::error(query.lastError().text());
   }
   return Result<QString>::success(QString::number(orderDetail.id));
}

Result<QVector<orderDetail>> OrderDeatilDao::getOrderDetailList(int orderId) {
   if (!DatabaseManager::isOpen()) {
      DatabaseManager::initialize();
   }
   QString sql = "SELECT * FROM order_detail WHERE order_id=:order_id";
   QSqlQuery query(DatabaseManager::getDatabase());
   query.prepare(sql);
   query.bindValue(":order_id",QVariant(orderId));
   if (!query.exec()) {
      return Result<QVector<orderDetail>>::error(query.lastError().text());
   }
   QVector<orderDetail> orderDetailList;
   while (query.next()) {
      orderDetail orderDetail;
      orderDetail.id=query.value("id").toInt();
      orderDetail.processId=query.value("process_id").toInt();
      orderDetail.orderId=query.value("order_id").toInt();
      orderDetail.real_price=query.value("real_price").toLongLong();
      orderDetail.real_quantity=query.value("real_quantity").toInt();
      orderDetail.employeeId=query.value("employee_id").toInt();
      orderDetailList.append(orderDetail);
   }
   return Result<QVector<orderDetail>>::success(orderDetailList);
}

Result<QString> OrderDeatilDao::deleteByOrderId(int orderId) {
   if (!DatabaseManager::isOpen()) {
      DatabaseManager::initialize();
   }
   QString sql = "DELETE FROM order_detail WHERE order_id=:order_id";
   QSqlQuery query(DatabaseManager::getDatabase());
   query.prepare(sql);
   query.bindValue(":order_id",QVariant(orderId));
   if (!query.exec()) {
      return Result<QString>::error(query.lastError().text());
   }
   return Result<QString>::success(QString::number(orderId));
}

Result<QMap<int,QVector<orderDetail>>> OrderDeatilDao::getOrderDetailListByOrderIds(const QSet<int> &set,int employeeId) {
   if (!DatabaseManager::isOpen()) {
      DatabaseManager::initialize();
   }
   QSqlQuery query(DatabaseManager::getDatabase());
   QString placeHolders;
   for (int i=0;i<set.size();i++) {
      placeHolders+=QString(":order_id%1").arg(i);
      if (i<set.size()-1) {
         placeHolders+=",";
      }
   }
   QString sql="SELECT * FROM order_detail WHERE employee_id=:employee_id AND order_id IN ("+placeHolders+")";
   query.prepare(sql);
   query.bindValue(":employee_id",QVariant(employeeId));
   int i=0;
   for (int id:set) {
      query.bindValue(QString(":order_id%1").arg(i),QVariant(id));
      i++;
   }
   if (!query.exec()) {
      return Result<QMap<int,QVector<orderDetail>>>::error(query.lastError().text());
   }
   QMap<int,QVector<orderDetail>> orderDetailMap;
   while (query.next()) {
      orderDetail orderDetail;
      orderDetail.id=query.value("id").toInt();
      orderDetail.processId=query.value("process_id").toInt();
      orderDetail.orderId=query.value("order_id").toInt();
      orderDetail.real_price=query.value("real_price").toLongLong();
      orderDetail.real_quantity=query.value("real_quantity").toInt();
      orderDetail.employeeId=query.value("employee_id").toInt();
      orderDetailMap[orderDetail.orderId].append(orderDetail);
   }
   return Result<QMap<int,QVector<orderDetail>>>::success(orderDetailMap);
}

Result<QueryPage<QMap<int, QVector<orderDetail>>>> OrderDeatilDao::getOrderDetailListByEmployeeId(int current_page,
   int page_size, int id) {
   if (!DatabaseManager::isOpen()) {
      DatabaseManager::initialize();
   }
   QSqlQuery query(DatabaseManager::getDatabase());
   QString countSql="SELECT COUNT(DISTINCT order_id) FROM order_detail WHERE employee_id=:employee_id";
   query.prepare(countSql);
   query.bindValue(":employee_id",QVariant(id));
   if (!query.exec()) {
      return Result<QueryPage<QMap<int, QVector<orderDetail>>>>::error(query.lastError().text());
   }
   int totalCount=0;
   if (query.next()) {
      totalCount=query.value(0).toInt();
   }
   int totalPage=(totalCount+page_size-1)/page_size;

   QString orderDetailSql=R"(
   SELECT DISTINCT od.order_id FROM order_detail od
   LEFT JOIN `order` o ON od.order_id=o.id
   WHERE od.employee_id=:employee_id
   ORDER BY od.order_id
   LIMIT :pageSize OFFSET :offset
   )";
   query.prepare(orderDetailSql);
   query.bindValue(":employee_id",QVariant(id));
   query.bindValue(":pageSize",QVariant(page_size));
   query.bindValue(":offset",QVariant((current_page-1)*page_size));
   if (!query.exec()) {
      return Result<QueryPage<QMap<int, QVector<orderDetail>>>>::error(query.lastError().text());
   }
   QSet<int> orderIdSet;
   while (query.next()) {
      orderIdSet.insert(query.value(0).toInt());
   }
   const auto & OrderDetailMap = getOrderDetailListByOrderIds(orderIdSet,id);
   if (!OrderDetailMap.isOk) {
      return Result<QueryPage<QMap<int, QVector<orderDetail>>>>::error(OrderDetailMap.message);
   }
   return Result<QueryPage<QMap<int,QVector<orderDetail>>>>::success(QueryPage<QMap<int,QVector<orderDetail>>>(OrderDetailMap.data,totalCount,totalPage));
}

Result<bool> OrderDeatilDao::getorderDetailByProcessId(int process_id) {
   if (!DatabaseManager::isOpen()) {
      DatabaseManager::initialize();
   }
   QSqlQuery query(DatabaseManager::getDatabase());
   QString sql="SELECT COUNT(*) FROM order_detail WHERE process_id=:process_id";
   query.prepare(sql);
   query.bindValue(":process_id",QVariant(process_id));
   if (!query.exec()) {
      return Result<bool>::error(query.lastError().text());
   }
   if (query.next()) {
      return Result<bool>::success(query.value(0).toInt()>0);
   }
   return Result<bool>::error("查询失败");
}

Result<bool> OrderDeatilDao::IsEmployeeUsed(int employee_id) {
   if (!DatabaseManager::isOpen()) {
      DatabaseManager::initialize();
   }
   QSqlQuery query(DatabaseManager::getDatabase());
   QString sql="SELECT COUNT(*) FROM order_detail WHERE employee_id=:employee_id";
   query.prepare(sql);
   query.bindValue(":employee_id",QVariant(employee_id));
   if (!query.exec()) {
      return Result<bool>::error(query.lastError().text());
   }
   if (query.next()) {
      return Result<bool>::success(query.value(0).toInt()>0);
   }
   return Result<bool>::error("查询失败");
}
