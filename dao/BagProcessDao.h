//
// Created by 114514 on 2026/7/29.
//

#ifndef BOOKKEEPINGS_BAGPROCESSDAO_H
#define BOOKKEEPINGS_BAGPROCESSDAO_H

#include <QSqlQuery>

#include "po/BagProcess.h"
#include "po/QueryPage.h"
#include "po/Result.h"

class BagProcessDao {
public:
    static Result<QString> addBagProcess(const BagProcess& bagProcess);
    static Result<QString> deleteBagProcess(const BagProcess& bagProcess);
    static Result<QString> updateBagProcess(const BagProcess& bagProcess);
    static Result<QueryPage<QVector<BagProcess>>> queryBagProcess(int currPage,int pageSize,int bagId,int processId);
private:
    static Result<QString> initData();
    static QSqlDatabase db;
};


#endif //BOOKKEEPINGS_BAGPROCESSDAO_H
