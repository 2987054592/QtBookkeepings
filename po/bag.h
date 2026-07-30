//
// Created by 114514 on 2026/7/29.
//

#ifndef BOOKKEEPINGS_BAG_H
#define BOOKKEEPINGS_BAG_H
#include <QString>
#include <QVector>

#include "BagProcess.h"
#include "processs.h"

class Bag {
public:
    ~Bag();
    int id;
    QString name;
    QString imagePath;
    QVector<BagProcess> processList;

};


#endif //BOOKKEEPINGS_BAG_H