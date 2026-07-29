//
// Created by 114514 on 2026/7/28.
//

#include "ProcessDao.h"

#include <QSqlError>
#include <QVariant>
#include <QVector>
QSqlDatabase ProcessDao::db;
Result<QString> ProcessDao::init() {
    if (!db.isOpen()) {
        db=QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("bookkeepings.db");
    }
    if(!db.open()){
        return Result<QString>::error("数据库打开失败");
    }
    return Result<QString>::success("数据库初始化成功");
}

Result<QString> ProcessDao::addProcess(const processs &p) {
    init();
    QSqlQuery query;
    const QString sql="INSERT INTO process (process_name) VALUES (:name)";
    query.prepare(sql);
    query.bindValue(":name",QVariant(p.name));
    if (query.exec()) {
        return Result<QString>::success("添加工序成功");
    }else {
        const QString errorText = query.lastError().text();
        if (errorText.contains("unique",Qt::CaseInsensitive)) {
            return Result<QString>::error("工序名称已存在");
        }else {
            return Result<QString>::error("添加工序失败");
        }
    }
}

Result<QString> ProcessDao::deleteProcess(const processs &p) {
}

Result<QString> ProcessDao::updateProcess(const processs &p) {
    init();
    QSqlQuery query;
    const QString sql="UPDATE process SET process_name=:name WHERE id=:id";
    query.prepare(sql);
    query.bindValue(":name",QVariant(p.name));
    query.bindValue(":id",QVariant(p.id));
    if (query.exec()) {
        return Result<QString>::success("修改工序成功");
    }else {
        const QString errorText = query.lastError().text();
        if (errorText.contains("unique",Qt::CaseInsensitive)) {
            return Result<QString>::error("工序名称已存在");
        }else {
            return Result<QString>::error("修改工序失败");
        }
    }
}

Result<QueryPage<QVector<processs>>> ProcessDao::getProcesses(int currPage, int pageSize, const QString &name) {
    init();
    QSqlQuery query;
    QString countSql="SELECT COUNT(*) FROM process WHERE 1=1";
    if (!name.isEmpty() && !name.isNull()) {
        countSql+=" AND process_name LIKE :name";
    }
    query.prepare(countSql);
    if (!name.isEmpty() && !name.isNull()) {
        query.bindValue(":name","%"+name+"%");
    }
    query.exec();
    query.next();
    int totalRecord=query.value(0).toInt();
    int totalPage = (totalRecord + pageSize - 1) / pageSize;
    int offset=(currPage-1)*pageSize;

    QString sql="SELECT * FROM process";
    if (name.isNull() || name.isEmpty()) {
        sql+=" ORDER BY id LIMIT :pageSize OFFSET :offset";
    }else {
        sql+=" WHERE process_name LIKE :name ORDER BY id LIMIT :pageSize OFFSET :offset";
    }
    query.prepare(sql);
    if (!name.isNull() && !name.isEmpty()) {
        query.bindValue(":name",QVariant("%"+name+"%"));
    }
    query.bindValue(":pageSize",pageSize);
    query.bindValue(":offset",offset);
    if (query.exec()) {
        QVector<processs> processes;
        while (query.next()) {
            processs p;
            p.id=query.value("id").toInt();
            p.name=query.value("process_name").toString();
            processes.append(p);
        }
        return Result<QueryPage<QVector<processs>>>::success(QueryPage<QVector<processs>>(processes,totalRecord,totalPage));
    }else {
        return Result<QueryPage<QVector<processs>>>::error("查询工序失败");
       }

}
