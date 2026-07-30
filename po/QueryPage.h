//
// Created by 114514 on 2026/7/28.
//

#ifndef BOOKKEEPINGS_QUERYPAGE_H
#define BOOKKEEPINGS_QUERYPAGE_H
#include <QVector>
template <typename T>
class QueryPage {
public:
     QueryPage(T data,int total,int totalPages) : data(data), total(total), totalPages(totalPages) {}
     QueryPage() : data(T()), total(0), totalPages(0) {}
    static QueryPage<T> empty() {
        return QueryPage<T>(T(),0,0);
    }
    T data;
    int total;
    int totalPages;
};


#endif //BOOKKEEPINGS_QUERYPAGE_H
