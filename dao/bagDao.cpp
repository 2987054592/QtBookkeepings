//
// Created by 114514 on 2026/7/29.
//

#include "bagDao.h"

#include <QVariant>
#include <QSqlError>
QSqlDatabase bagDao::db;
Result<QString> bagDao::addBag(const Bag &bag) {
    initData();
    QSqlQuery sql_query;
    QString sql="INSERT INTO bag(name,image_path) VALUES(:name,:image_path)";
    sql_query.bindValue(":name",QVariant(bag.name));
    sql_query.bindValue(":image_path",QVariant(bag.imagePath));
    if (sql_query.exec()) {
        return Result<QString>::success("添加成功");
    }else {
        const QString error=sql_query.lastError().text();
        if (error.contains("unique",Qt::CaseInsensitive)) {
            return Result<QString>::error("名称已存在");
        }else {
            return Result<QString>::error("添加失败");
        }
    }
}

Result<QString> bagDao::deleteBag(const Bag &bag) {
}

Result<QString> bagDao::updateBag(const Bag &bag) {
    initData();
    QSqlQuery sql_query;
    QString sql="UPDATE bag SET name=:name,image_path=:image_path WHERE id=:id";
    sql_query.bindValue(":name",QVariant(bag.name));
    sql_query.bindValue(":image_path",QVariant(bag.imagePath));
    sql_query.bindValue(":id",QVariant(bag.id));
    if (sql_query.exec()) {
        return Result<QString>::success("更新成功");
    }else {
        const QString error=sql_query.lastError().text();
        if (error.contains("unique",Qt::CaseInsensitive)) {
            return Result<QString>::error("名称已存在");
        }else {
            return Result<QString>::error("更新失败");
        }
    }
}

Result<QueryPage<QVector<Bag>>> bagDao::queryBagPage(const int &currPage, const int &pageSize, const QString &name) {
    initData();
    QSqlQuery sql_query;
    QString countSql="SELECT COUNT(*) FROM bag WHERE 1=1";
    if (!name.isNull() && !name.isEmpty()) {
        countSql+=" AND name LIKE :name";
    }
    sql_query.prepare(countSql);

    if (!name.isEmpty() && !name.isNull()) {
        sql_query.bindValue(":name",QVariant("%"+name+"%"));
    }
    sql_query.exec();
    sql_query.next();
    int totalCount=sql_query.value(0).toInt();
    int totalSize=(totalCount + pageSize - 1) / pageSize;
    int offset=(currPage-1)*pageSize;

    QString sql="SELECT * FROM bag WHERE 1=1";
    if (!name.isEmpty()&& !name.isNull()) {
        sql+=" AND name LIKE :name";
    }
    sql+=" ORDER BY id LIMIT :pageSize OFFSET :offset";
    sql_query.prepare(sql);
    sql_query.bindValue(":pageSize",QVariant(pageSize));
    sql_query.bindValue(":offset",QVariant(offset));
    if (!name.isEmpty()) {
        sql_query.bindValue(":name",QVariant("%"+name+"%"));
    }
    if (sql_query.exec()) {
        QVector<Bag> bags;
        while (sql_query.next()) {
            Bag bag;
            bag.id=sql_query.value("id").toInt();
            bag.name=sql_query.value("name").toString();
            bag.imagePath=sql_query.value("image_path").toString();
            bags.append(bag);
        }
        return Result<QueryPage<QVector<Bag>>>::success(QueryPage<QVector<Bag>>(bags,totalCount,totalSize));
    } else {
        return Result<QueryPage<QVector<Bag>>>::error("查询背包失败");
    }

}

Result<QString> bagDao::initData() {
    if (!db.isOpen()) {
        db=QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("bookkeepings.db");
    }
    if(!db.open()){
        return Result<QString>::error("数据库打开失败");
    }
    return Result<QString>::success("数据库初始化成功");
}