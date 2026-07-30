//
// Created by 114514 on 2026/7/29.
//

#ifndef BOOKKEEPINGS_BAGDAO_H
#define BOOKKEEPINGS_BAGDAO_H
#include "po/Result.h"
#include "po/bag.h"
#include "po/QueryPage.h"

class bagDao {
public:
   static Result<QString> addBag(const Bag& bag);
   static Result<QString> deleteBag(const Bag &bag);
   static Result<QString> updateBag(const Bag &bag);
   static Result<QueryPage<QVector<Bag>>> queryBagPage(const int &currPage,const int &pageSize,const QString &name);

   static Result<Bag> getBag(int id);
};


#endif //BOOKKEEPINGS_BAGDAO_H