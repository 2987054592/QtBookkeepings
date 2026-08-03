//
// Created by 114514 on 2026/8/3.
//

#include "MyBarChart.h"

MyBarChart::MyBarChart(QWidget *parent) : QCustomPlot(parent) {
    xAxis->setTickLabelRotation(30);
}

CategoryType MyBarChart::type1() const {
    return type;
}

void MyBarChart::setType(CategoryType type) {
    this->type = type;
    if (type==CategoryType::Employee) {
        xAxis->setLabel("员工");
        yAxis->setLabel("金额");
    }else {
        xAxis->setLabel("书包编号");
        yAxis->setLabel("数量");
    }

    replot();
}

void MyBarChart::setData(const QVector<QString> &labels, const QVector<double> &values) {
    clearPlottables();
    bars = new QCPBars(xAxis, yAxis);
    QVector<double> ticks;
    for (int i = 0; i < labels.size(); i++) {
        ticks.append(i);
    }
    bars->setData(ticks,values);
    bars->setBrush(QColor(70,130,180));

    QSharedPointer<QCPAxisTickerText> ticker(new QCPAxisTickerText());
    for (int i=0;i<labels.size();i++) {
        ticker->addTick(i,labels[i]);
    }
    xAxis->setTicker(ticker);

    rescaleAxes();

    clearItems();
    for (int i=0;i<labels.size();i++) {
        QCPItemText *text = new QCPItemText(this);
        text->position->setCoords(i,values[i]);
        text->setText(QString::number(values[i]));
        text->setFont(QFont(font().family(), 8));
        text->setPadding(QMargins(2, 2, 2, 2));
        text->setPositionAlignment(Qt::AlignBottom | Qt::AlignHCenter);
    }


    xAxis->setRange(-0.5,labels.size()-0.5);
    yAxis->setRange(0,*std::ranges::max_element(values)*1.2);

    replot();


}
