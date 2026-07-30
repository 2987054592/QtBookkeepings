//
// Created by 114514 on 2026/7/29.
//

// You may need to build the project (run Qt uic code generator) to get "ui_bag.h" resolved

#include "bag.h"
#include "ui_bag.h"
#include "dao/bagDao.h"
#include "dao/ProcessDao.h"
#include <QFileDialog>
#include <QMessageBox>

BagDialog::BagDialog(QWidget *parent) : QDialog(parent), ui(new Ui::BagDialog) {
    ui->setupUi(this);
    resize(1200,1000);
    model=new QStandardItemModel(this);
    ui->tableView->setModel(model);

    ui->tableView->verticalHeader()->hide();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui->pbtAddProcess,&QPushButton::clicked,this,&BagDialog::addMoreProcess);
    connect(ui->pbtBagAddImage,&QPushButton::clicked,this,&BagDialog::chooseImage);
    connect(ui->pbtDelProcess,&QPushButton::clicked,this,&BagDialog::deleteProcess);

}

BagDialog::~BagDialog() {
    delete ui;
}

Bag BagDialog::getBag() {
    Bag bag;
    bag.name=ui->BagNameLine->text();
    bag.imagePath=m_path;
    bag.processList=row;
    bag.id=m_bagId;
    if (bag.imagePath.isEmpty()) {
        return bag;
    }
    return bag;
}

void BagDialog::setBag(const Bag &bag) {
    ui->BagImage->clear();
    m_path=bag.imagePath;
    m_bagId=bag.id;
    if (!m_path.isEmpty()) {
        ui->BagImage->setPixmap(QPixmap(m_path));
        ui->BagImage->setFixedHeight(200);
        ui->BagImage->setFixedWidth(200);
        ui->BagImage->setScaledContents(true);
    }
    ui->BagNameLine->setText(bag.name);
    row=bag.processList;
    model->clear();
    model->setHorizontalHeaderLabels({"ID", "工序", "默认金额"});
    Result<QueryPage<QVector<processs>>> processes = ProcessDao::getProcesses(1,100000,"");
    if (!processes.isOk) {
        return;
    }
    const QVector<processs> & processses = processes.data.data;
    QMap<int,QString> process_map;
    for (const processs &process:processses) {
        process_map[process.id]=process.name;
    }
    for (const BagProcess &process:row) {
        model->appendRow({new QStandardItem(QString::number(process.bagId)),new QStandardItem(process_map.value(process.processId)),new QStandardItem(process.defaultPrices)});
    }
}

void BagDialog::clear() {

        model->clear();
        model->setHorizontalHeaderLabels({"ID", "工序", "默认金额"});
        row.clear();
        m_bagId = 0;
        m_path.clear();
        ui->BagNameLine->clear();
        ui->BagImage->clear();

}


void BagDialog::addMoreProcess() {
    if (dialog == nullptr) {
        dialog=new bagprocessdialog(this);
    }

    Result<QueryPage<QVector<processs>>> processes = ProcessDao::getProcesses(1,100000,"");
    dialog->setComboxData(processes.data.data);
    if (dialog->exec() == QDialog::Accepted) {
        processs process=dialog->current_process();
        BagProcess bag_process;
        bag_process.bagId=m_bagId;
        bag_process.processId=process.id;
        bag_process.defaultPrices=dialog->current_defaultPrices();
        row.append(bag_process);
        model->appendRow({new QStandardItem(QString::number(bag_process.bagId)),new QStandardItem(process.name),new QStandardItem(bag_process.defaultPrices)});
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

void BagDialog::deleteProcess() {
    QModelIndex current_index = ui->tableView->currentIndex();
    if (!current_index.isValid()) {
        QMessageBox::warning(this,"警告","请选择要删除的工序");
        return;
    }
    const int row_index=current_index.row();
    row.removeAt(row_index);
    model->removeRow(row_index);
}
