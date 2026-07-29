//
// Created by 114514 on 2026/7/29.
//

// You may need to build the project (run Qt uic code generator) to get "ui_bagprocessdialog.h" resolved

#include "bagprocessdialog.h"
#include "ui_bagprocessdialog.h"


bagprocessdialog::bagprocessdialog(QWidget *parent) : QDialog(parent), ui(new Ui::bagprocessdialog) {
    ui->setupUi(this);
    qRegisterMetaType<processs>("processs");
}

bagprocessdialog::~bagprocessdialog() {
    delete ui;
}

void bagprocessdialog::setComboxData(const QVector<processs>& processes) {
    ui->comboBox->clear();
    for (const auto& process : processes) {
        ui->comboBox->addItem(process.name, QVariant::fromValue(process));
    }
}

processs bagprocessdialog::current_process() const {
    processs p;
    p.id=ui->comboBox->currentData().value<processs>().id;
    p.name=ui->comboBox->currentData().value<processs>().name;
    p.defaultPrices=ui->lineEdit->text();
    return p;
}


