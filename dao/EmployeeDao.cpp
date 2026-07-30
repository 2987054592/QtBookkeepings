//
// Created by 114514 on 2026/7/28.
//

#include "EmployeeDao.h"
#include "DatabaseManager.h"

#include <QVariant>
#include <QSqlError>
#include <QSqlQuery>

EmployeeDao::EmployeeDao() {
}

Result<QString> EmployeeDao::addEmployee(employee &e) {
    if (!DatabaseManager::isOpen()) {
        DatabaseManager::initialize();
    }
    QSqlQuery query(DatabaseManager::getDatabase());
    query.prepare("INSERT INTO employee (employee_name,floor) VALUES (:name, :floor)");
    query.bindValue(":name",QVariant(e.name));
    query.bindValue(":floor",QVariant(e.floor));
    if (query.exec()) {
        return Result<QString>::success("添加员工成功");
    }else {
        QString errorText = query.lastError().text();
        if (errorText.contains("unique",Qt::CaseInsensitive)) {
            return Result<QString>::error("员工姓名已存在");
        }else {
            return Result<QString>::error("添加员工失败");
        }
    }
}

Result<QString> EmployeeDao::deleteEmployee(employee &e) {
    return Result<QString>::error("暂未实现");
}

Result<QString> EmployeeDao::updateEmployee(employee &e) {
    if (!DatabaseManager::isOpen()) {
        DatabaseManager::initialize();
    }
    QSqlQuery query(DatabaseManager::getDatabase());
    query.prepare("UPDATE employee SET employee_name=:name, floor=:floor WHERE id=:id");
    query.bindValue(":name",QVariant(e.name));
    query.bindValue(":floor",QVariant(e.floor));
    query.bindValue(":id",QVariant(e.id));

    if (query.exec()) {
        return Result<QString>::success("修改员工成功");
    }else {
        QString errorText = query.lastError().text();
        if (errorText.contains("unique",Qt::CaseInsensitive)) {
            return Result<QString>::error("员工姓名已存在");
        }else {
            return Result<QString>::error("修改员工失败");
        }
    }
}

Result<QueryPage<QVector<employee>>> EmployeeDao::getEmployees(int currPage, int pageSize, const QString& name, const int floor) {
    if (!DatabaseManager::isOpen()) {
        DatabaseManager::initialize();
    }
    QSqlQuery query(DatabaseManager::getDatabase());
    QString countSql="SELECT COUNT(*) FROM employee WHERE 1=1";
    if (!name.isEmpty() && !name.isNull()) {
        countSql+=" AND employee_name LIKE :name";
    }if (floor!=0) {
        countSql+=" AND floor=:floor";
    }
    query.prepare(countSql);
    if (floor!=0) {
        query.bindValue(":floor",floor);
    }
    if (!name.isEmpty() && !name.isNull()) {
        query.bindValue(":name","%"+name+"%");
    }

    query.exec();
    query.next();
    int totalRecord=query.value(0).toInt();
    int totalSize=(totalRecord + pageSize - 1) / pageSize;
    QString sql="SELECT * FROM employee WHERE 1=1";

    if (!name.isEmpty() && !name.isNull()) {
        sql+=" AND employee_name LIKE :name";
    }
    if (floor!=0) {
        sql+=" AND floor=:floor";
    }
    sql+=" ORDER BY id LIMIT :pageSize OFFSET :offset";
    query.prepare(sql);
    if (floor!=0) {
        query.bindValue(":floor",floor);
    }
    if (!name.isEmpty() && !name.isNull()) {
        query.bindValue(":name","%"+name+"%");
    }
    query.bindValue(":pageSize",pageSize);
    query.bindValue(":offset",(currPage-1)*pageSize);


    if (query.exec()) {
        QVector<employee> employees;
        while (query.next()) {
            employee e;
            e.id=query.value("id").toInt();
            e.name=query.value("employee_name").toString();
            e.floor=query.value("floor").toInt();
            employees.append(e);
        }
        return Result<QueryPage<QVector<employee>>>::success(QueryPage<QVector<employee>>(QVector<employee>(employees),totalRecord,totalSize));
    } else {
        return Result<QueryPage<QVector<employee>>>::error("获取员工失败");
    }
}
