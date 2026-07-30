//
// Created by 114514 on 2026/7/26.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_MainWindow.h"
#include <qdebug.h>
#include <QMessageBox>
#include <QInputDialog>
#include <QSqlError>
#include <memory>
#include <QFileDialog>

#include "dao/bagDao.h"
#include "dao/BagProcessDao.h"
#include "dao/EmployeeDao.h"
#include "dao/ProcessDao.h"
#include "po/processs.h"
#include "po/bag.h"
#include "po/BagProcess.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    initData();
    connect(ui->toolBox,&QToolBox::currentChanged,ui->tabWidget,&QTabWidget::setCurrentIndex);
    connect(ui->tabWidget,&QTabWidget::currentChanged,ui->toolBox,&QToolBox::setCurrentIndex);

    connect(ui->pushButtonPre,&QPushButton::clicked,this,[=]() {
        if (employeePagination.currentPage>1) {
            employeePagination.currentPage--;
            searchEmployee();
        }
    });
    connect(ui->pushButtonNext,&QPushButton::clicked,this,[=]() {
        if (employeePagination.currentPage<employeePagination.totalPages) {
            employeePagination.currentPage++;
            searchEmployee();
        }

    });



    connect(ui->pushButtonAdd,&QPushButton::clicked,this,&MainWindow::addEmployee);
    connect(ui->pushButtonDel,&QPushButton::clicked,this,&MainWindow::deleteEmployee);
    connect(ui->pushButtonModify,&QPushButton::clicked,this,&MainWindow::updateEmployee);
    connect(ui->pushButtonAddSearch,&QPushButton::clicked,this,&MainWindow::searchEmployee);
    connect(ui->tableView,&QTableView::doubleClicked,this,&MainWindow::updateEmployee);


    connect(ui->processAdd,&QPushButton::clicked,this,&MainWindow::addProcess);
    connect(ui->processDelete,&QPushButton::clicked,this,&MainWindow::deleteProcess);
    connect(ui->processUpdata,&QPushButton::clicked,this,&MainWindow::updateProcess);
    connect(ui->pbtProcessSearch,&QPushButton::clicked,this,&MainWindow::searchProcess);
    connect(ui->tableView_2,&QTableView::doubleClicked,this,&MainWindow::updateProcess);

    connect(ui->pbtProcessPre,&QPushButton::clicked,this,[=]() {
        if (processPagination.currentPage>1) {
            processPagination.currentPage--;
            searchProcess();
        }
    });
    connect(ui->pbtProcessNext,&QPushButton::clicked,this,[=]() {
        if (processPagination.currentPage<processPagination.totalPages) {
            processPagination.currentPage++;
            searchProcess();
        }

    });

    connect(ui->pbtAddBag,&QPushButton::clicked,this,&MainWindow::addBag);
    connect(ui->pbtBagSearch,&QPushButton::clicked,this,&MainWindow::searchBag);
    connect(ui->pbtDetailBag,&QPushButton::clicked,this,&MainWindow::getDetailBag);
    connect(ui->tableView_3,&QTableView::doubleClicked,this,&MainWindow::updateBag);
    connect(ui->pbtUpdataBag,&QPushButton::clicked,this,&MainWindow::updateBag);



    ui->tableView_3->setItemDelegateForColumn(2,new ImageDelegate(this));
    ui->tableView_3->verticalHeader()->setDefaultSectionSize(60);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::initData() {
    employeeModel = new QStandardItemModel(this);
    processModel = new QStandardItemModel(this);
    bagModel = new QStandardItemModel(this);

    QStringList employeeStr;
    employeeStr<<"ID"<<"姓名"<<"楼层";
    employeeModel->setHorizontalHeaderLabels(employeeStr);

    QStringList processStr;
    processStr<<"ID"<<"名称";
    processModel->setHorizontalHeaderLabels(processStr);

    QStringList bagStr;
    bagStr<<"ID"<<"名称"<<"图片";
    bagModel->setHorizontalHeaderLabels(bagStr);

    // 先设置 model
    ui->tableView->setModel(employeeModel);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView_2->setModel(processModel);
    ui->tableView_2->verticalHeader()->hide();
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView_3->setModel(bagModel);
    ui->tableView_3->verticalHeader()->hide();
    ui->tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);

    searchEmployee();
    searchProcess();
    searchBag();
}

void MainWindow::addEmployee() {
    employee e;
    if (employee_dialog==nullptr) {
        employee_dialog=new EmployeeDialog(this);
    }
    employee_dialog->clear();
    int r=employee_dialog->exec();
    if (r!=QDialog::Accepted) {
        return;
    }
    e.name=employee_dialog->getName();
    e.floor=employee_dialog->getFloor();
    if (e.name.isEmpty() || e.name.isNull()) {
        return;
    }
    Result<QString> result=EmployeeDao::addEmployee(e);
    if (!result.isOk) {
        QMessageBox::critical(this,"错误",result.message);
        return;
    }
    QMessageBox::information(this,"成功","添加员工成功");
    searchEmployee();
}

void MainWindow::deleteEmployee() {
    // QModelIndex index = ui->tableView->currentIndex();
    // if (!index.isValid()) {
    //     QMessageBox::warning(this,"警告","请选择要删除的员工");
    //     return;
    // }
    // int id = index.data().toInt();
    // QSqlQuery query;
    // query.prepare("DELETE FROM employee WHERE id=:id");
    // query.bindValue(":id",id);
    // if (query.exec()) {
    //     QMessageBox::information(this,"成功","删除员工成功");
    //     loadPage(currentPage);
    // }else {
    //     QMessageBox::critical(this,"错误","删除员工失败");
    // }
}

void MainWindow::updateEmployee() {
    QModelIndex index = ui->tableView->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this,"警告","请选择要修改的员工");
        return;
    }
    QString name = index.sibling(index.row(),1).data().toString();
    int id=index.sibling(index.row(),0).data().toInt();
    int floor=index.sibling(index.row(),2).data().toInt();
    if (employee_dialog==nullptr) {
        employee_dialog=new EmployeeDialog(this);
    }
    employee e;
    e.id=id;
    e.name=name;
    e.floor=floor;
    employee_dialog->setDefaultValues(e);
    int r=employee_dialog->exec();
    if (r!=QDialog::Accepted) {
        return;
    }
    QString newName=employee_dialog->getName();
    int newFloor=employee_dialog->getFloor();
    if (newName.isEmpty()) {
        return;
    }
    e.id=id;
    e.name=newName;
    e.floor=newFloor;
    Result<QString> result=EmployeeDao::updateEmployee(e);
    if (!result.isOk) {
        QMessageBox::critical(this,"错误",result.message);
        return;
    }
    QMessageBox::information(this,"成功","修改员工成功");
    searchEmployee();
}

void MainWindow::searchEmployee() {
    QString name=ui->lineEdit->text();
    int floor=ui->spinBox->value();
    Result<QueryPage<QVector<employee>>> query_page = EmployeeDao::getEmployees(employeePagination.currentPage, pageSize, name, floor);
    if (!query_page.isOk) {
        QMessageBox::critical(this,"错误",query_page.message);
    }
    QVector<employee> list=query_page.data.data;
    employeePagination.totalRecords=query_page.data.total;
    employeePagination.totalPages  =query_page.data.totalPages;
    ui->labelPreAndNext->setText(QString("当前页：%1/%2,共%3条记录").arg(employeePagination.currentPage).arg(employeePagination.totalPages).arg(employeePagination.totalRecords));
    employeeModel->removeRows(0,employeeModel->rowCount());
    for (const auto& emp:list) {
        QList<QStandardItem *> row;
        row.append(new QStandardItem(QString::number(emp.id)));
        row.append(new QStandardItem(emp.name));
        row.append(new QStandardItem(QString::number(emp.floor)));
        employeeModel->appendRow(row);
    }
}

void MainWindow::addProcess() {
    processs p;
    QString name=QInputDialog::getText(this,"添加工序","请输入工序名称");
    if (name.isEmpty() || name.isNull()) {
        return;
    }
    p.name=name;
    Result<QString> result=ProcessDao::addProcess(p);
    if (!result.isOk) {
        QMessageBox::critical(this,"错误",result.message);
        return;
    }
    QMessageBox::information(this,"成功","添加工序成功");
    searchProcess();
}


void MainWindow::deleteProcess() {
}

void MainWindow::updateProcess() {
    QModelIndex index = ui->tableView_2->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this,"警告","请选择要修改的工序");
        return;
    }
    QString name = index.sibling(index.row(),1).data().toString();
    int id=index.sibling(index.row(),0).data().toInt();
    QString newName=QInputDialog::getText(this,"修改工序","请输入新的工序名称",QLineEdit::Normal,name);
    if (newName.isEmpty() || newName==name) {
        return;
    }
    processs p;
    p.id=id;
    p.name=newName;
    Result<QString> result=ProcessDao::updateProcess(p);
    if (!result.isOk) {
        QMessageBox::critical(this,"错误",result.message);
        return;
    }
    QMessageBox::information(this,"成功","修改工序成功");
    searchProcess();
}

void MainWindow::searchProcess() {
    QString name=ui->lineEdit_2->text();
    Result<QueryPage<QVector<processs>>> query_page = ProcessDao::getProcesses(processPagination.currentPage, pageSize, name);
    if (!query_page.isOk) {
        QMessageBox::critical(this,"错误",query_page.message);
    }
    QVector<processs> list=query_page.data.data;
    processPagination.totalRecords=query_page.data.total;
    processPagination.totalPages=query_page.data.totalPages;
    ui->label_3->setText(QString("当前页：%1/%2,共%3条记录").arg(processPagination.currentPage).arg(processPagination.totalPages).arg(processPagination.totalRecords));
    processModel->removeRows(0,processModel->rowCount());
    for (const auto& p:list) {
        QList<QStandardItem *> row;
        row.append(new QStandardItem(QString::number(p.id)));
        row.append(new QStandardItem(p.name));
        processModel->appendRow(row);
    }
}

void MainWindow::addBag() {
    if (bagDialog==nullptr) {
        bagDialog=new BagDialog(this);
    }
    bagDialog->clear();
    if (bagDialog->exec() == QDialog::Accepted) {
        Bag bag = bagDialog->getBag();

        const Result<QString> add_bag = bagDao::addBag(bag);
        if (!add_bag.isOk) {
            QMessageBox::critical(this,"错误",add_bag.message);
            return;
        }
        bag.id=add_bag.data.toInt();
        for (const auto& process:bag.processList) {
            BagProcess bagProcess;
            bagProcess.bagId=bag.id;
            bagProcess.processId=process.id;
            bagProcess.defaultPrices=process.defaultPrices;
            const Result<QString> result = BagProcessDao::addBagProcess(bagProcess);
            if (!result.isOk) {
                QMessageBox::critical(this,"错误",result.message);
                return;
            }
        }
        QMessageBox::information(this,"成功","添加背包成功");
        searchBag();
    }
}

void MainWindow::searchBag() {
    const QString name=ui->lineEdit_3->text();
    Result<QueryPage<QVector<Bag>>> query_page = bagDao::queryBagPage(bagPagination.currentPage,pageSize,name);
    if (!query_page.isOk) {
        QMessageBox::critical(this,"错误",query_page.message);
        return;
    }
    bagPagination.totalPages=query_page.data.totalPages;
    bagPagination.totalRecords=query_page.data.total;
    QVector<Bag> list=query_page.data.data;
    bagModel->removeRows(0,bagModel->rowCount());
    for (const auto& bag:list) {
        QList<QStandardItem *> row;
        row.append(new QStandardItem(QString::number(bag.id)));
        row.append(new QStandardItem(bag.name));
        row.append(new QStandardItem(bag.imagePath));
        bagModel->appendRow(row);
    }
}

void MainWindow::getDetailBag() {
    QModelIndex index = ui->tableView_3->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this,"警告","请选择要查看的背包");
        return;
    }
    const int id=index.sibling(index.row(),0).data().toInt();
    Result<Bag> bag_result = bagDao::getBag(id);
    if (!bag_result.isOk) {
        QMessageBox::warning(this,"警告","背包不存在");
        return;
    }
    if (bagDialog==nullptr) {
        bagDialog=new BagDialog(this);
    }
    bagDialog->setBag(bag_result.data);
    if (bagDialog->exec()==QDialog::Accepted) {
        const Bag bag = bagDialog->getBag();
        const Result<QString> result = bagDao::updateBag(bag);
        if (!result.isOk) {
            QMessageBox::critical(this,"错误",result.message);
            return;
        }
        QMessageBox::information(this,"成功","更新背包成功");
        searchBag();
    }

}

void MainWindow::updateBag() {
    getDetailBag();
}

