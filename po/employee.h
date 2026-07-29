//
// Created by 114514 on 2026/7/26.
//

#ifndef BOOKKEEPINGS_EMPLOYEE_H
#define BOOKKEEPINGS_EMPLOYEE_H

#include <QString>

class employee {
public:
    int id;
    QString name;
    int floor;
    explicit employee() : id(0), name(), floor(0) {}
};


#endif //BOOKKEEPINGS_EMPLOYEE_H
