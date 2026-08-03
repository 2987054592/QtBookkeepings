//
// Created by 114514 on 2026/8/3.
//

#ifndef BOOKKEEPINGS_MYBARCHART_H
#define BOOKKEEPINGS_MYBARCHART_H
#include <qcustom/qcustomplot.h>

#include "enums/CategoryType.h"

class MyBarChart : public QCustomPlot {
    Q_OBJECT
    public:
    explicit MyBarChart(QWidget *parent = nullptr);
    CategoryType type;

    CategoryType type1() const;

    void setType(CategoryType type);

    void setData(const QVector<QString> &labels, const QVector<double> &values);
private:
    QCPBars *bars;
};


#endif //BOOKKEEPINGS_MYBARCHART_H
