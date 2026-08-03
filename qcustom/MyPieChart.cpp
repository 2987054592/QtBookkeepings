//
// Created by 114514 on 2026/8/3.
//

#include "MyPieChart.h"

MyPieChart::MyPieChart(QWidget *parent) : QCustomPlot(parent) {
}

CategoryType MyPieChart::type1() const {
    return type;
}

void MyPieChart::setType(CategoryType type) {
    this->type = type;

}

void MyPieChart::setData(const QVector<QString> &labels, const QVector<double> &values) {
    clearPlottables();
    m_labels=labels;
    m_values=values;

    double total=0;
    for (double v:values) {
        total+=v;
    }
    QCPBars *previous=nullptr;
    for (int i=0;i<labels.size();i++) {
        QCPBars *bar = new QCPBars(xAxis, yAxis);
        if (previous)
            bar->moveAbove(previous);
        QColor color;
        color.setHsv((i*360/values.size())%360,150,150);
        bar->setBrush(color);
        QVector<double> x={0};
        QVector<double> y={values[i]};
        bar->setData(x,y);
        bar->setWidth(0.5);
        previous=bar;
    }
    xAxis->setRange(-1, 1);
    xAxis->setVisible(false);
    yAxis->setRange(0, total * 1.1);

    replot();
    setMouseTracking(true);
}

void MyPieChart::mouseMoveEvent(QMouseEvent *event) {
    double x =xAxis->pixelToCoord(event->pos().x());
    double y =yAxis->pixelToCoord(event->pos().y());
    if (qAbs(x)>0.5) {
        QToolTip::hideText();
        return;
    }
    double currentSum=0;
    for (int i=0;i<m_values.size();i++) {
        currentSum+=m_values[i];
        if (currentSum>=y) {
            QString tip =QString("%1:%2").arg(m_labels[i]).arg(m_values[i]);
            QToolTip::showText(event->globalPos(),tip);
            return;
        }
    }

    QToolTip::hideText();
    QCustomPlot::mouseMoveEvent(event);
}
