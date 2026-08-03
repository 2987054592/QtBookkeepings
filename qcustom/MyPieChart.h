//
// Created by 114514 on 2026/8/3.
//

#ifndef BOOKKEEPINGS_MYPIECHART_H
#define BOOKKEEPINGS_MYPIECHART_H
#include <qcustom/qcustomplot.h>

#include "enums/CategoryType.h"


class MyPieChart : public QCustomPlot {
    Q_OBJECT
    public:
    explicit MyPieChart(QWidget *parent = nullptr);
    CategoryType type;

    CategoryType type1() const;

    void setType(CategoryType type);

    void setData(const QVector<QString> &labels, const QVector<double> &values);
protected:
    void mouseMoveEvent(QMouseEvent *event) override;
private:
    QCPBars *bars;
    QVector<QString> m_labels;
    QVector<double> m_values;
};


#endif //BOOKKEEPINGS_MYPIECHART_H
