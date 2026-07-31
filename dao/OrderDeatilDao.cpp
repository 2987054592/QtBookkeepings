//
// Created by 114514 on 2026/7/30.
//

#include "OrderDeatilDao.h"

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
