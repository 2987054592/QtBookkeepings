//
// Created by 114514 on 2026/7/30.
//

#ifndef BOOKKEEPINGS_ORDER_H
#define BOOKKEEPINGS_ORDER_H
#include <QString>
#include <QDate>
class order {
public:
    int id = 0;
    QString name;
    QDate date;
    int bagId = 0;
    int floor = 0;
};


#endif //BOOKKEEPINGS_ORDER_H
