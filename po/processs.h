//
// Created by 114514 on 2026/7/28.
//

#ifndef BOOKKEEPINGS_PROCESSS_H
#define BOOKKEEPINGS_PROCESSS_H

#include <qmetatype.h>
#include <QString>
class processs {
public:
    QString name;
    int id;
    QString defaultPrices;
};

Q_DECLARE_METATYPE(processs)
#endif //BOOKKEEPINGS_PROCESSS_H
