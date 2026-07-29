//
// Created by 114514 on 2026/7/29.
//

#ifndef BOOKKEEPINGS_BAG_H
#define BOOKKEEPINGS_BAG_H
#include <QString>
#include <QVector>

#include "processs.h"

class Bag {
public:
    ~Bag();
    int id;
    QString name;
    QString imagePath;
    QVector<processs> processList;

};


#endif //BOOKKEEPINGS_BAG_H