//
// Created by 114514 on 2026/7/29.
//

#include "BagProcessDao.h"
#include "DatabaseManager.h"

#include <QVariant>
#include <QSqlError>
#include <QVector>
#include <QSqlQuery>

Result<QString> BagProcessDao::addBagProcess(const BagProcess& bagProcess) {
    if (!DatabaseManager::isOpen()) {
        DatabaseManager::initialize();
    }
    QSqlQuery sql_query(DatabaseManager::getDatabase());
    QString sql;
    sql="INSERT INTO process_bag (bag_id,process_id,default_price) VALUES (:bag_id,:process_id,:default_price)";
    sql_query.prepare(sql);
    sql_query.bindValue(":bag_id",QVariant(bagProcess.bagId));
    sql_query.bindValue(":process_id",QVariant(bagProcess.processId));
    sql_query.bindValue(":default_price",QVariant(bagProcess.defaultPrices));
    if (sql_query.exec()) {
        return Result<QString>::success("书包工序添加成功");
    }else {
        QString text=sql_query.lastError().text();
        if (text.contains("unique",Qt::CaseInsensitive)) {
            return Result<QString>::error("书包工序添加失败，该工序已存在");
        }
        return Result<QString>::error("书包工序添加失败"+text);
    }

}

Result<QString> BagProcessDao::deleteBagProcess(const BagProcess& bagProcess) {
    return Result<QString>::success("暂未实现");
}

Result<QString> BagProcessDao::updateBagProcess(const BagProcess& bagProcess) {
    if (!DatabaseManager::isOpen()) {
        DatabaseManager::initialize();
    }
    QSqlQuery sql_query(DatabaseManager::getDatabase());
    QString sql;
    sql="UPDATE process_bag SET default_price=:default_price WHERE bag_id=:bag_id AND process_id=:process_id";
    sql_query.prepare(sql);
    sql_query.bindValue(":bag_id",QVariant(bagProcess.bagId));
    sql_query.bindValue(":process_id",QVariant(bagProcess.processId));
    sql_query.bindValue(":default_price",QVariant(bagProcess.defaultPrices));
    if (sql_query.exec()) {
        return Result<QString>::success("更新工序成功");
    }else {
        return Result<QString>::error("更新工序失败");
    }
}

Result<QueryPage<QVector<BagProcess>>> BagProcessDao::queryBagProcess(int currPage, int pageSize, const int bagId,
    const int processId) {
    if (!DatabaseManager::isOpen()) {
        DatabaseManager::initialize();
    }
    QSqlQuery sql_query(DatabaseManager::getDatabase());
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
    sql+=" ORDER BY id LIMIT :pageSize OFFSET :offset";
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
            bagProcess.defaultPrices = sql_query.value("default_price").toLongLong();
            bagProcesses.append(bagProcess);
        }
        return Result<QueryPage<QVector<BagProcess>>>::success(QueryPage<QVector<BagProcess>>(bagProcesses,totalCount,totalSize));
    } else {
        return Result<QueryPage<QVector<BagProcess>>>::error("查询工序失败");
    }


}

Result<QVector<BagProcess>> BagProcessDao::queryProcessListByBagId(int bagId) {
    if (!DatabaseManager::isOpen()) {
        DatabaseManager::initialize();
    }
    QSqlQuery sql_query(DatabaseManager::getDatabase());
    QString sql="SELECT * FROM process_bag WHERE bag_id=:bag_id";
    sql_query.prepare(sql);
    sql_query.bindValue(":bag_id",QVariant(bagId));
    if (sql_query.exec()) {
        QVector<BagProcess> processList;
        while (sql_query.next()) {
            BagProcess bagProcess;
            bagProcess.id=sql_query.value("id").toInt();
            bagProcess.bagId=sql_query.value("bag_id").toInt();
            bagProcess.processId=sql_query.value("process_id").toInt();
            bagProcess.defaultPrices = sql_query.value("default_price").toLongLong();
            processList.append(bagProcess);
        }
        return Result<QVector<BagProcess>>::success(processList);
    } else {
        return Result<QVector<BagProcess>>::error("查询工序失败");
    }
}

void BagProcessDao::DeleteBagProcessByBagId(int id) {
    if (!DatabaseManager::isOpen()) {
        DatabaseManager::initialize();
    }
    QSqlQuery sql_query(DatabaseManager::getDatabase());
    QString sql="DELETE FROM process_bag WHERE bag_id=:bag_id";
    sql_query.prepare(sql);
    sql_query.bindValue(":bag_id",QVariant(id));
    sql_query.exec();
}
