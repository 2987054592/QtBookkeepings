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
        return Result<QString>::success(QString::number(query.lastInsertId().toInt()));

}

Result<QString> OrderDao::deleteOrder(const order &order) {
}

Result<QString> OrderDao::updateOrder(const order &order) {
    if (!DatabaseManager::isOpen()) {
        DatabaseManager::initialize();
    }
    QSqlQuery query(DatabaseManager::getDatabase());
    const QString sql="UPDATE `order` SET name=:name,time=:time,bag_id=:bag_id,floor=:floor WHERE id=:id";
    query.prepare(sql);
    query.bindValue(":name",QVariant(order.name));
    query.bindValue(":time",QVariant(order.date));
    query.bindValue(":bag_id",QVariant(order.bagId));
    query.bindValue(":floor",QVariant(order.floor));
    query.bindValue(":id",QVariant(order.id));
    if (!query.exec()) {
        const QString error=query.lastError().text();
        if (error.contains("unique",Qt::CaseInsensitive)) {
            return Result<QString>::error("订单名称已存在");
        }
        return Result<QString>::error(error);
    }
    return Result<QString>::success("更新订单成功");
}

Result<QueryPage<QVector<order>>> OrderDao::queryOrderPage(const int &currPage, const int &pageSize,
    const QString &name, const int &floor) {
    if (!DatabaseManager::isOpen()) {
        DatabaseManager::initialize();
    }
    QSqlQuery query(DatabaseManager::getDatabase());
    int totalRecord=0;
    int totalPage=0;
    QString sql="SELECT COUNT(*) FROM `order` WHERE 1=1 ";
    if (!name.isNull() && !name.isEmpty()) {
        sql+=" AND name LIKE :name";
    }
    if (floor!=0){
        sql+=" AND floor=:floor";
    }
    query.prepare(sql);
    if (!name.isNull() && !name.isEmpty()) {
        query.bindValue(":name",QVariant("%"+name+"%"));
    }
    if (floor!=0){
        query.bindValue(":floor",QVariant(floor));
    }
    if (!query.exec()) {
        return Result<QueryPage<QVector<order>>>::error("查询订单失败");
    }
    if (query.next()) {
        totalRecord=query.value(0).toInt();
        totalPage=(totalRecord+pageSize-1)/pageSize;
    }

    sql="SELECT * FROM `order` WHERE 1=1 ";
    if (!name.isNull() && !name.isEmpty()) {
        sql+=" AND name LIKE :name";
    }
    if (floor!=0) {
        sql+=" AND floor=:floor";
    }
    sql+=" ORDER BY id LIMIT :pageSize OFFSET :offset";
    query.prepare(sql);
    if (!name.isNull() && !name.isEmpty()) {
        query.bindValue(":name",QVariant("%"+name+"%"));
    }
    if (floor!=0) {
        query.bindValue(":floor",QVariant(floor));
    }
    int offset=(currPage-1)*pageSize;
    query.bindValue(":pageSize",pageSize);
    query.bindValue(":offset",offset);
    if (!query.exec()) {
        return Result<QueryPage<QVector<order>>>::error("查询订单失败");
    }
    QVector<order> orders;
    while (query.next()) {
        order o;
        o.id=query.value("id").toInt();
        o.date=query.value("time").toDate();
        o.bagId=query.value("bag_id").toInt();
        o.floor=query.value("floor").toInt();
        o.name=query.value("name").toString();
        orders.append(o);

    }
    return Result<QueryPage<QVector<order>>>::success(QueryPage<QVector<order>>(orders,totalRecord,totalPage));
}

Result<order> OrderDao::getOrder(int id) {
    if (!DatabaseManager::isOpen()) {
        DatabaseManager::initialize();
    }
    QSqlQuery query(DatabaseManager::getDatabase());
    const QString sql="SELECT * FROM `order` WHERE id=:id";
    query.prepare(sql);
    query.bindValue(":id",QVariant(id));
    if (!query.exec()) {
        return Result<order>::error("查询订单失败");
    }
    if (query.next()) {
        order o;
        o.id=query.value("id").toInt();
        o.date=query.value("time").toDate();
        o.bagId=query.value("bag_id").toInt();
        o.floor=query.value("floor").toInt();
        o.name=query.value("name").toString();
        return Result<order>::success(o);
    }
    return Result<order>::error("订单不存在");
}
