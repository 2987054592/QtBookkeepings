//
// Created by 114514 on 2026/7/26.
//

#ifndef BOOKKEEPINGS_EMPLOYEE_H
#define BOOKKEEPINGS_EMPLOYEE_H

#include <QString>
#include <QMetaType>
class employee {
public:
    int id = 0;
    QString name;
    int floor;
    explicit employee() : id(0), name(), floor(0) {}
};
Q_DECLARE_METATYPE(employee)

#endif //BOOKKEEPINGS_EMPLOYEE_H
