//
// Created by 114514 on 2026/7/28.
//

#ifndef BOOKKEEPINGS_EMPLOYEEDAO_H
#define BOOKKEEPINGS_EMPLOYEEDAO_H

#include "po/employee.h"
#include <QVector>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "po/Result.h"
#include "po/QueryPage.h"
class EmployeeDao {
public:
    EmployeeDao();

    static Result<QString> initDatabase();
    static Result<QString> addEmployee(employee &e);
    static Result<QString> deleteEmployee(employee &e);
    static Result<QString> updateEmployee(employee &e);
    static Result<QueryPage<QVector<employee>>> getEmployees(int currPage,int pageSize,const QString& name,int floor);
private:
    static QSqlDatabase db;
};


#endif //BOOKKEEPINGS_EMPLOYEEDAO_H
