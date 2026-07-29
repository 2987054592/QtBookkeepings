//
// Created by 114514 on 2026/7/29.
//

// You may need to build the project (run Qt uic code generator) to get "ui_bag.h" resolved

#include "bag.h"
#include "ui_bag.h"
#include "dao/bagDao.h"
#include "dao/ProcessDao.h"
#include <QFileDialog>


BagDialog::BagDialog(QWidget *parent) : QDialog(parent), ui(new Ui::BagDialog) {
    ui->setupUi(this);
    resize(1200,1000);
    model=new QStandardItemModel(this);
    ui->tableView->setModel(model);
    QStringList str;
    str<<"ID"<<"工序"<<"默认金额";
    model->setHorizontalHeaderLabels(str);

    ui->tableView->verticalHeader()->hide();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui->pbtAddProcess,&QPushButton::clicked,this,&BagDialog::addMoreProcess);
    connect(ui->pbtBagAddImage,&QPushButton::clicked,this,&BagDialog::chooseImage);
}

BagDialog::~BagDialog() {
    delete ui;
}

Bag BagDialog::getBag() {
    Bag bag;
    bag.name=ui->BagNameLine->text();
    bag.imagePath=m_path;
    if (bag.imagePath.isEmpty()) {
        return bag;
    }
    return bag;
}

QVector<processs> BagDialog::getProcessRow() {
    return row;
}

void BagDialog::addMoreProcess() {
    if (dialog == nullptr) {
        dialog=new bagprocessdialog(this);
    }
    Result<QueryPage<QVector<processs>>> processes = ProcessDao::getProcesses(1,100000,"");
    dialog->setComboxData(processes.data.data);
    if (dialog->exec() == QDialog::Accepted) {
        processs process=dialog->current_process();
        row.append(process);
        model->appendRow({new QStandardItem(QString::number(process.id)),new QStandardItem(process.name),new QStandardItem(process.defaultPrices)});
    }

}

void BagDialog::chooseImage() {
    m_path=QFileDialog::getOpenFileName(this,"选择图片","","选择图片(*.jpg *.png *.gif)");
    if (m_path.isEmpty()) {
        return;
    }
    ui->BagImage->setPixmap(QPixmap(m_path));
    ui->BagImage->setFixedHeight(200);
    ui->BagImage->setFixedWidth(200);
    ui->BagImage->setScaledContents(true);
}
