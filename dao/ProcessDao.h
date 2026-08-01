//
// Created by 114514 on 2026/7/28.
//

#ifndef BOOKKEEPINGS_PROCESSDAO_H
#define BOOKKEEPINGS_PROCESSDAO_H
#include "po/processs.h"
#include "po/QueryPage.h"
#include "po/Result.h"

class ProcessDao {
public:
    static Result<QString> addProcess(const processs &p);
    static Result<QString> deleteProcess(int id);
    static Result<QString> updateProcess(const processs &p);
    static Result<QueryPage<QVector<processs>>> getProcesses(int currPage,int pageSize,const QString& name);

    static Result<QVector<processs>> getByIds(const QSet<int> & set);


};


#endif //BOOKKEEPINGS_PROCESSDAO_H
