//
// Created by 114514 on 2026/7/29.
//

// You may need to build the project (run Qt uic code generator) to get "ui_bag.h" resolved

#include "bag.h"
#include "ui_bag.h"
#include "dao/bagDao.h"
#include "dao/ProcessDao.h"
#include <QFileDialog>
#include <QInputDialog>
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
    connect(ui->tableView,&QTableView::doubleClicked,this,&BagDialog::updateProessPrice);
    networkManager=new NetworkManager(this);
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
    if (m_path.isEmpty()) {
        // if (!m_path.isEmpty()) {
        //     ui->BagImage->setPixmap(QPixmap(m_path));
        //     ui->BagImage->setFixedHeight(200);
        //     ui->BagImage->setFixedWidth(200);
        //     ui->BagImage->setScaledContents(true);
        // }
        //return;
    }
    QNetworkAccessManager *nam = new QNetworkAccessManager(this);
    QNetworkReply *reply = nam->get(QNetworkRequest(QUrl(bag.imagePath)));
    connect(reply,&QNetworkReply::finished,this,[=]() {
        if (reply->error()==QNetworkReply::NoError) {
            QPixmap pm;
            if (pm.loadFromData(reply->readAll())) {
                ui->BagImage->setPixmap(pm);
                ui->BagImage->setFixedHeight(200);
                ui->BagImage->setFixedWidth(200);
                ui->BagImage->setScaledContents(true);
            }
        }
        reply->deleteLater();
        nam->deleteLater();
    });
    ui->BagNameLine->setText(bag.name);
    row=bag.processList;
    model->clear();
    model->setHorizontalHeaderLabels({"ID", "工序", "默认金额"});

    QSet<int> processIds;
    for (const BagProcess &process:row) {
        processIds.insert(process.processId);
    }
    Result<QVector<processs>> result = ProcessDao::getByIds(processIds);

    QMap<int,QString> process_map;
    for (const processs &process:result.data) {
        process_map[process.id]=process.name;
    }
    for (const BagProcess &process:row) {
        double defaultPrices = process.defaultPrices/1000.00;
        model->appendRow({new QStandardItem(QString::number(process.id)),new QStandardItem(process_map.value(process.processId)),new QStandardItem(QString::number(defaultPrices,'f',2))});
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
        double defaultPrices = bag_process.defaultPrices/1000.00;
        model->appendRow({new QStandardItem(QString::number(bag_process.bagId)),new QStandardItem(process.name),new QStandardItem(QString::number(defaultPrices,'f',2))});
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

void BagDialog::updateProessPrice() {
    QModelIndex current_index = ui->tableView->currentIndex();
    if (!current_index.isValid()) {
        QMessageBox::warning(this,"警告","请选择要更新的工序");
        return;
    }
    double pricesPrice=current_index.sibling(current_index.row(),2).data().toDouble();
    QString NewPricesPrice=QInputDialog::getText(this,"更新工序金额","请输入新的工序金额",QLineEdit::Normal,QString::number(pricesPrice,'f',2));
    if (NewPricesPrice.isEmpty()) {
        return;
    }
    double newPricesPrice=NewPricesPrice.toDouble();
    model->setItem(current_index.row(),2,new QStandardItem(QString::number(newPricesPrice,'f',2)));

    newPricesPrice*=1000.00;
    row[current_index.row()].defaultPrices=newPricesPrice;

}
