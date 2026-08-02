//
// Created by 114514 on 2026/7/29.
//

#include "bagDao.h"

#include <qset.h>

#include "DatabaseManager.h"

#include <QVariant>
#include <QSqlError>
#include <QSqlQuery>

#include "BagProcessDao.h"

Result<QString> bagDao::addBag(const Bag &bag) {
    if (!DatabaseManager::isOpen()) {
        DatabaseManager::initialize();
    }

    QSqlQuery sql_query(DatabaseManager::getDatabase());
    QString sql="INSERT INTO bag(name,image_path) VALUES(:name,:image_path)";
    sql_query.prepare(sql);
    sql_query.bindValue(":name",QVariant(bag.name));
    sql_query.bindValue(":image_path",QVariant(bag.imagePath));
    if (sql_query.exec()) {
        // 返回插入行的主键 ID
        QVariant lastId = sql_query.lastInsertId();
        return Result<QString>::success(lastId.toString());
    }else {
        const QString error=sql_query.lastError().text();
        if (error.contains("unique",Qt::CaseInsensitive)) {
            return Result<QString>::error("书包名称已存在");
        }else {
            return Result<QString>::error("书包添加失败"+error);
        }
    }
}

Result<QString> bagDao::deleteBag(const int &bagId) {
    if (!DatabaseManager::isOpen()) {
        DatabaseManager::initialize();
    }
    QSqlQuery sql_query(DatabaseManager::getDatabase());
    QString sql="DELETE FROM bag WHERE id=:id";
    sql_query.prepare(sql);
    sql_query.bindValue(":id",QVariant(bagId));
    if (sql_query.exec()) {
        return Result<QString>::success("删除背包成功");
    }else {
        return Result<QString>::error("删除背包失败");
    }
}

Result<QString> bagDao::updateBag(const Bag &bag) {
    if (!DatabaseManager::isOpen()) {
        DatabaseManager::initialize();
    }
    QSqlQuery sql_query(DatabaseManager::getDatabase());
    QString sql="UPDATE bag SET name=:name,image_path=:image_path WHERE id=:id";
    sql_query.prepare(sql);
    sql_query.bindValue(":name",QVariant(bag.name));
    sql_query.bindValue(":image_path",QVariant(bag.imagePath));
    sql_query.bindValue(":id",QVariant(bag.id));
    if (sql_query.exec()) {
        BagProcessDao::DeleteBagProcessByBagId(bag.id);
        for (auto &process:bag.processList) {
            Result<QString> update_bag_process = BagProcessDao::addBagProcess(process);
            if (!update_bag_process.isOk) {
                return Result<QString>::error("更新背包工序失败"+update_bag_process.message);
            }
        }
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
    if (!DatabaseManager::isOpen()) {
        DatabaseManager::initialize();
    }
    QSqlQuery sql_query(DatabaseManager::getDatabase());
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

Result<Bag> bagDao::getBag(const int id) {
    if (!DatabaseManager::isOpen()) {
        DatabaseManager::initialize();
    }
    QSqlQuery sql_query(DatabaseManager::getDatabase());
    QString sql="SELECT * FROM bag WHERE id=:id";
    sql_query.prepare(sql);
    sql_query.bindValue(":id",QVariant(id));
    if (sql_query.exec()) {
        if (sql_query.next()) {
            Bag bag;
            bag.id=sql_query.value("id").toInt();
            bag.name=sql_query.value("name").toString();
            bag.imagePath=sql_query.value("image_path").toString();
            const Result<QVector<BagProcess>> process_result=BagProcessDao::queryProcessListByBagId(id);
            if (process_result.isOk) {
                bag.processList=process_result.data;
            }else {
                return Result<Bag>::error("查询工序失败");
            }
            return Result<Bag>::success(bag);
        } else {
            return Result<Bag>::error("背包不存在");
        }
    } else {
        return Result<Bag>::error("查询背包失败");
    }
}

QVector<Bag> bagDao::getAllBag() {
    if (!DatabaseManager::isOpen()) {
        DatabaseManager::initialize();
    }
    QString sql="SELECT * FROM bag";
    QSqlQuery sql_query(DatabaseManager::getDatabase());
    sql_query.prepare(sql);
    if (sql_query.exec()) {
        QVector<Bag> bags;
        while (sql_query.next()) {
            Bag bag;
            bag.id=sql_query.value("id").toInt();
            bag.name=sql_query.value("name").toString();
            bag.imagePath=sql_query.value("image_path").toString();
            bags.append(bag);
        }
        return bags;
    } else {
        return QVector<Bag>();
    }
}

QVector<Bag> bagDao::getBagByids(const QSet<int> &set) {
    if (!DatabaseManager::isOpen()) {
        DatabaseManager::initialize();
    }
    QSqlQuery sql_query(DatabaseManager::getDatabase());
    QString placeholder;
    for (int i=0;i<set.size();i++) {
        placeholder+=QString(":id%1").arg(i);
        if (i<set.size()-1) {
            placeholder+=",";
        }
    }
    QString sql="SELECT * FROM bag WHERE id IN ("+placeholder+")";
    sql_query.prepare(sql);
    int i=0;
    for (int id:set) {
        sql_query.bindValue(QString(":id%1").arg(i),QVariant(id));
        i++;
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
        return bags;
    } else {
        return QVector<Bag>();
        
    }
}
