//
// Created by 114514 on 2026/8/3.
//

#ifndef BOOKKEEPINGS_WORKER_H
#define BOOKKEEPINGS_WORKER_H
#include <QObject>
#include <QVector>

#include "enums/CategoryType.h"
#include "enums/TimeRangeType.h"

struct ChartData {
    //柱状图数据
    QVector<QString> barLabels;
    QVector<double> barValues;
    //饼图数据
    QVector<QString> pieLabels;
    QVector<double> pieValues;

};
Q_DECLARE_METATYPE(ChartData)
class worker : public QObject {
    Q_OBJECT
    public:
    explicit worker(QObject *parent = nullptr);
public slots:
    void doFetchData(const CategoryType& categoryType, const TimeRangeType& timeRangeType);
signals:
    void dataFetched(const ChartData &data);
};


#endif //BOOKKEEPINGS_WORKER_H
