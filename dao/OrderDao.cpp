//
// Created by 114514 on 2026/7/30.
//

#include "OrderDao.h"

#include <QVariant>
#include <QSqlError>
#include "DatabaseManager.h"

Result<QString> OrderDao::addOrder(const order &order) {
    if (!DatabaseManager::isOpen()) {
        DatabaseManager::initialize();
    }
    QSqlQuery query(DatabaseManager::getDatabase());
    const QString sql="INSERT INTO `order` (name,time,bag_id,floor) VALUES (:name,:time,:bag_id,:floor)";
    query.prepare(sql);
    query.bindValue(":name",QVariant(order.name));
    query.bindValue(":time",QVariant(order.date));
    query.bindValue(":bag_id",QVariant(order.bagId));
    query.bindValue(":floor",QVariant(order.floor));
    if (!query.exec()) {
        QString error=query.lastError().text();
        if (error.contains("unique",Qt::CaseInsensitive)) {
            return Result<QString>::error(("订单名称已存在"));
        } else {
            return Result<QString>::error(error);
        }
    }
        return Result<QString>::success("订单添加成功");

}

Result<QString> OrderDao::deleteOrder(const order &order) {
}

Result<QString> OrderDao::updateOrder(const order &order) {
}

Result<QueryPage<QVector<order>>> OrderDao::queryOrderPage(const int &currPage, const int &pageSize,
    const QString &name) {
}
