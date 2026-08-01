//
// Created by 114514 on 2026/7/29.
//

#ifndef BOOKKEEPINGS_BAGPROCESSDAO_H
#define BOOKKEEPINGS_BAGPROCESSDAO_H

#include <qlist.h>
#include <QSqlQuery>

#include "po/bag.h"
#include "po/BagProcess.h"
#include "po/processs.h"
#include "po/QueryPage.h"
#include "po/Result.h"

class BagProcessDao {
public:
    static Result<QString> addBagProcess(const BagProcess& bagProcess);
    static Result<QString> updateBagProcess(const BagProcess& bagProcess);
    static Result<QueryPage<QVector<BagProcess>>> queryBagProcess(int currPage,int pageSize,int bagId,int processId);

    static Result<QVector<BagProcess>> queryProcessListByBagId(int bagId);

    static void DeleteBagProcessByBagId(int id);

    static Result<QString> deleteByBagId(int bag_id);

    static Result<QString> deleteByProcessId(int process_id);
};


#endif //BOOKKEEPINGS_BAGPROCESSDAO_H
