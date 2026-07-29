//
// Created by 114514 on 2026/7/29.
//

#include "BagProcessDao.h"

#include <QVariant>
#include <QSqlError>
#include <QVector>
QSqlDatabase BagProcessDao::db;
Result<QString> BagProcessDao::addBagProcess(const BagProcess& bagProcess) {
    initData();
    QSqlQuery sql_query;
    QString sql;
    sql="INSERT INTO process_bag (bag_id,process_id,default_prices) VALUES (:bag_id,:process_id,:default_prices)";
    sql_query.prepare(sql);
    sql_query.bindValue(":bag_id",QVariant(bagProcess.bagId));
    sql_query.bindValue(":process_id",QVariant(bagProcess.processId));
    sql_query.bindValue(":default_prices",QVariant(bagProcess.defaultPrices));
    if (sql_query.exec()) {
        return Result<QString>::error("添加工序成功");
    }else {
        QString text=sql_query.lastError().text();
        if (text.contains("unique",Qt::CaseInsensitive)) {
            return Result<QString>::error("添加工序失败，该工序已存在");
        }
        return Result<QString>::error("添加工序失败");
    }

}

Result<QString> BagProcessDao::deleteBagProcess(const BagProcess& bagProcess) {
    return Result<QString>::success();
}

Result<QString> BagProcessDao::updateBagProcess(const BagProcess& bagProcess) {
    initData();
    QSqlQuery sql_query;
    QString sql;
    sql="UPDATE process_bag SET default_prices=:default_prices WHERE bag_id=:bag_id AND process_id=:process_id";
    sql_query.prepare(sql);
    sql_query.bindValue(":bag_id",QVariant(bagProcess.bagId));
    sql_query.bindValue(":process_id",QVariant(bagProcess.processId));
    sql_query.bindValue(":default_prices",QVariant(bagProcess.defaultPrices));
    if (sql_query.exec()) {
        return Result<QString>::success("更新工序成功");
    }else {
        return Result<QString>::error("更新工序失败");
    }
}

Result<QueryPage<QVector<BagProcess>>> BagProcessDao::queryBagProcess(int currPage, int pageSize, const int bagId,
    const int processId) {
    QSqlQuery sql_query;
    QString countSql="SELECT COUNT(*) FROM process_bag WHERE 1=1";
    if (bagId!=0) {
        countSql+=" AND bag_id=:bag_id";
    }
    if (processId!=0) {
        countSql+=" AND process_id=:process_id";
    }
    sql_query.prepare(countSql);
    if (bagId!=0) {
        sql_query.bindValue(":bag_id",QVariant(bagId));
    }
    if (processId!=0) {
        sql_query.bindValue(":process_id",QVariant(processId));
    }
    sql_query.exec();
    sql_query.next();
    int totalCount=sql_query.value(0).toInt();
    int totalSize=(totalCount + pageSize - 1) / pageSize;
    QString sql = "SELECT * FROM process_bag WHERE 1=1";
    if (bagId!=0) {
        sql+=" AND bag_id=:bag_id";
    }
    if (processId!=0) {
        sql+=" AND process_id=:process_id";
    }
    int offset=(currPage-1)*pageSize;
    sql+="ORDER BY id LIMIT :pageSize OFFSET :offset";
    sql_query.prepare(sql);
    sql_query.bindValue(":offset",QVariant(offset));
    sql_query.bindValue(":pageSize",QVariant(pageSize));
    if (bagId!=0) {
        sql_query.bindValue(":bag_id",QVariant(bagId));
    }
    if (processId!=0) {
        sql_query.bindValue(":process_id",QVariant(processId));
    }
    if (sql_query.exec()) {
        QVector<BagProcess> bagProcesses;
        while (sql_query.next()) {
            BagProcess bagProcess;
            bagProcess.id=sql_query.value("id").toInt();
            bagProcess.bagId=sql_query.value("bag_id").toInt();
            bagProcess.processId=sql_query.value("process_id").toInt();
            bagProcess.defaultPrices=sql_query.value("default_prices").toString();
            bagProcesses.append(bagProcess);
        }
        return Result<QueryPage<QVector<BagProcess>>>::success(QueryPage<QVector<BagProcess>>(bagProcesses,totalCount,totalSize));
    } else {
        return Result<QueryPage<QVector<BagProcess>>>::error("查询工序失败");
    }


}

Result<QString> BagProcessDao::initData() {
    if (!db.isOpen()) {
        db=QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("bookkeepings.db");
    }
    if(!db.open()){
        return Result<QString>::error("数据库打开失败");
    }
    return Result<QString>::success("数据库初始化成功");
}

