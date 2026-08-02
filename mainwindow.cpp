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
#include "dao/OrderDao.h"
#include "dao/OrderDeatilDao.h"
#include "dao/ProcessDao.h"
#include "network/NetworkManager.h"
#include "network/OSSClient.h"
#include "po/processs.h"
#include "po/bag.h"
#include "po/BagProcess.h"
#include "po/order.h"
#include <quuid.h>

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
    connect(ui->pushButtonDetail,&QPushButton::clicked,this,&MainWindow::getDetailEmployee);
    


    connect(ui->processAdd,&QPushButton::clicked,this,&MainWindow::addProcess);
    connect(ui->processUpdata,&QPushButton::clicked,this,&MainWindow::updateProcess);
    connect(ui->pbtProcessSearch,&QPushButton::clicked,this,&MainWindow::searchProcess);
    connect(ui->tableView_2,&QTableView::doubleClicked,this,&MainWindow::updateProcess);
    connect(ui->processDelete,&QPushButton::clicked,this,&MainWindow::deleteProcess);

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
    connect(ui->pbtDelBag,&QPushButton::clicked,this,&MainWindow::deleteBag);

    connect(ui->pbtBagPre,&QPushButton::clicked,this,[=]() {
        if (bagPagination.currentPage>1) {
            bagPagination.currentPage--;
            searchBag();
        }
    });
    connect(ui->pbtBagNext,&QPushButton::clicked,this,[=]() {
        if (bagPagination.currentPage<bagPagination.totalPages) {
            bagPagination.currentPage++;
            searchBag();
        }
    });


    ui->tableView_3->setItemDelegateForColumn(2,new ImageDelegate(this));
    ui->tableView_3->verticalHeader()->setDefaultSectionSize(60);

    connect(ui->pbtAddOrder,&QPushButton::clicked,this,&MainWindow::addOrder);
    connect(ui->pbtOrderSearch,&QPushButton::clicked,this,&MainWindow::searchOrder);
    connect(ui->pbtUpdataOrder,&QPushButton::clicked,this,&MainWindow::updateOrder);
    connect(ui->OrderView,&QTableView::doubleClicked,this,&MainWindow::updateOrder);
    connect(ui->pbtDetailorder,&QPushButton::clicked,this,&MainWindow::updateOrder);

    connect(ui->pbtOrderPre,&QPushButton::clicked,this,[=]() {
        if (orderPagination.currentPage>1) {
            orderPagination.currentPage--;
            searchOrder();
        }
    });
    connect(ui->pbtOrderNext,&QPushButton::clicked,this,[=]() {
        if (orderPagination.currentPage<orderPagination.totalPages) {
            orderPagination.currentPage++;
            searchOrder();
        }
    });
    connect(ui->pbtDelOrder,&QPushButton::clicked,this,&MainWindow::deleteOrder);
    networkManager = new NetworkManager(this);
    networkManager->get("https://zj.v.api.aa1.cn/api/wenan-zl/?type=json");
    connect(networkManager,&NetworkManager::replyFinished,this,[=](const QJsonObject &respond) {
        ui->labelLI->setText(respond.value("msg").toString());
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::initData() {
    employeeModel = new QStandardItemModel(this);
    processModel = new QStandardItemModel(this);
    bagModel = new QStandardItemModel(this);
    orderModel = new QStandardItemModel(this);

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


    QStringList orderStr;
    orderStr<<"ID"<<"名称"<<"时间"<<"书包名称"<<"楼层"<<"书包图片";
    orderModel->setHorizontalHeaderLabels(orderStr);

    ui->OrderView->setModel(orderModel);
    ui->OrderView->verticalHeader()->hide();
    ui->OrderView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->OrderView->setItemDelegateForColumn(5,new ImageDelegate(this));
    ui->OrderView->verticalHeader()->setDefaultSectionSize(60);

    ossClient=new OSSClient("https://oss-cn-beijing.aliyuncs.com",
                          "LTAI5t6cSShvhLFZaZe8EBmM",          // RAM 子账号 AK
                          "DMzps5zVDriEQaHDkoKvJ9i5yBOdNV",              // 千万别用主账号
                          "javazou",
                          "cn-beijing");
    connect(ossClient,&OSSClient::uploadFinished,this,[=](const QString &key,bool ok,const QString &message) {
        if (ok) {
            QMessageBox::information(this,"成功","上传成功");
        } else {
            QMessageBox::critical(this,"错误",message);
        }
    });


    searchEmployee();
    searchProcess();
    searchBag();
    searchOrder();
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
    const int &row = ui->tableView->currentIndex().row();
    if (row<0) {
        QMessageBox::warning(this,"警告","请选择要删除的员工");
        return;
    }
    if (QMessageBox::No==QMessageBox::warning(this,"警告","确认删除员工吗？",QMessageBox::Yes|QMessageBox::No,QMessageBox::No)) {
        return;
    }
    int employeeId=employeeModel->item(row,0)->text().toInt();

    const auto & result = OrderDeatilDao::IsEmployeeUsed(employeeId);
    if (!result.isOk){
        QMessageBox::critical(this,"错误",result.message);
        return;
    }
    if (result.data) {
        QMessageBox::warning(this,"警告","该员工已被使用，不能删除");
        return;
    }
    Result<QString> results=EmployeeDao::deleteEmployee(employeeId);
    if (!result.isOk) {
        QMessageBox::critical(this,"错误",results.message);
        return;
    }
    QMessageBox::information(this,"成功","删除员工成功");
    employeeModel->removeRow(row);
    searchEmployee();


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

void MainWindow::deleteProcess() {
    QModelIndex index = ui->tableView_2->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this,"警告","请选择要删除的工序");
        return;
    }
    if (QMessageBox::No==QMessageBox::question(this,"确认","确认删除该工序吗？",QMessageBox::Yes|QMessageBox::No)) {
        return;
    }


    int processId=processModel->item(index.row(),0)->text().toInt();
    const auto & result = OrderDeatilDao::getorderDetailByProcessId(processId);
    if (!result.isOk) {
        QMessageBox::critical(this,"错误",result.message);
        return;
    }
    if (result.data) {
        QMessageBox::warning(this,"警告","该工序已被订单引用，不能删除");
        return;
    }
    const auto & by_process_id = BagProcessDao::deleteByProcessId(processId);
    if (!by_process_id.isOk) {
        QMessageBox::critical(this,"错误",by_process_id.message);
        return;
    }
    const auto & delete_result = ProcessDao::deleteProcess(processId);
    if (!delete_result.isOk) {
        QMessageBox::critical(this,"错误",delete_result.message);
        return;
    }
    QMessageBox::information(this,"成功","删除工序成功");
    processModel->removeRow(index.row());
    searchProcess();

}



void MainWindow::addBag() {
    if (bagDialog==nullptr) {
        bagDialog=new BagDialog(this);
    }
    bagDialog->clear();
    if (bagDialog->exec() == QDialog::Accepted) {
        Bag bag = bagDialog->getBag();
        if (bag.name.isEmpty()|| bag.name.isNull()) {
            QMessageBox::warning(this,"警告","请输入背包名称");
            return;
        }
        const Result<QString> add_bag = bagDao::addBag(bag);
        if (!add_bag.isOk) {
            QMessageBox::critical(this,"错误",add_bag.message);
            return;
        }
        bag.id=add_bag.data.toInt();
        for (const auto& process:bag.processList) {
            BagProcess bagProcess;
            bagProcess.bagId=bag.id;
            bagProcess.processId=process.processId;
            bagProcess.defaultPrices=process.defaultPrices;
            const Result<QString> result = BagProcessDao::addBagProcess(bagProcess);
            if (!result.isOk) {
                QMessageBox::critical(this,"错误",result.message);
                return;
            }
        }
        const QString uuid=QUuid::createUuid().toString();
        ossClient->putObject("qtImage/"+uuid+".jpg",bag.imagePath);
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
    ui->label_6->setText(QString("当前页：%1/%2,共%3条记录").arg(bagPagination.currentPage).arg(bagPagination.totalPages).arg(bagPagination.totalRecords));
}
// 查看背包详情加修改背包
void MainWindow::getDetailBag() {
    QModelIndex index = ui->tableView_3->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this,"警告","请选择要查看的背包");
        return;
    }
    const int id=index.sibling(index.row(),0).data().toInt();
    const Result<Bag> bag_result = bagDao::getBag(id);
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

void MainWindow::deleteBag() {
    const int &row = ui->tableView_3->currentIndex().row();
    int bagId = bagModel->item(row,0)->text().toInt();
    if (row<0) {
        QMessageBox::warning(this,"警告","请选择要删除的背包");
        return;
    }
    if (QMessageBox::No==QMessageBox::warning(this,"警告","确认删除背包吗？",QMessageBox::Yes|QMessageBox::No)) {
        return;
    }
    const auto & by_bag_id = OrderDao::getByBagId(bagId);
    if (!by_bag_id.isOk) {
        QMessageBox::critical(this,"错误",by_bag_id.message);
        return;
    }
    if (by_bag_id.data) {
        QMessageBox::warning(this,"警告","该背包下有订单，不能删除");
        return;
    }
    const auto & delete_by_bag_id = BagProcessDao::deleteByBagId(bagId);
    if (!delete_by_bag_id.isOk) {
        QMessageBox::critical(this,"错误",delete_by_bag_id.message);
        return;
    }
    const auto & delete_bag = bagDao::deleteBag(bagId);
    if (!delete_bag.isOk) {
        QMessageBox::critical(this,"错误",delete_bag.message);
        return;
    }

    QMessageBox::information(this,"成功","删除背包成功");
    bagModel->removeRow(row);
    searchBag();
}
void MainWindow::addOrder() {
    if (orderDialog==nullptr) {
        orderDialog=new OrderDialog(this);
    }
    const QVector<Bag> bagList=bagDao::getAllBag();
    orderDialog->setBagList(bagList);
    if (orderDialog->exec()==QDialog::Accepted) {
        const order order = orderDialog->getOrder();
        if (order.name.isEmpty()|| order.name.isNull()) {
            QMessageBox::warning(this,"警告","请输入订单名称");
            return;
        }
        const Result<QString> result = OrderDao::addOrder(order);
        if (!result.isOk) {
            QMessageBox::critical(this,"错误",result.message);
            return;
        }
        order.id=result.data.toInt();
        for (auto& orderDetail:order.orderDetailList) {
            orderDetail.orderId=order.id;
            const Result<QString> add_result = OrderDeatilDao::addOrderDetail(orderDetail);
            if (!add_result.isOk) {
                QMessageBox::critical(this,"错误",add_result.message);
                return;
            }
        }
        QMessageBox::information(this,"成功","添加订单成功");
        searchOrder();
    }
}

void MainWindow::searchOrder() {
    const QString name=ui->lineEdit_4->text();
    const int floor = ui->spinBox_2->value();
    Result<QueryPage<QVector<order>>> query_order_page = OrderDao::queryOrderPage(orderPagination.currentPage,pageSize,name,floor);
    if (!query_order_page.isOk) {
        QMessageBox::critical(this,"错误",query_order_page.message);
        return;
    }
    orderPagination.totalPages=query_order_page.data.totalPages;
    orderPagination.totalRecords=query_order_page.data.total;
    QVector<order> list=query_order_page.data.data;
    orderModel->removeRows(0,orderModel->rowCount());

    QSet<int> bagIdSet;
    for (const auto& order:list) {
        bagIdSet.insert(order.bagId);
    }
    QVector<Bag> bagList=bagDao::getBagByids(bagIdSet);
    QMap<int,Bag> bagMap;
    for (const auto& bag:bagList) {
        bagMap.insert(bag.id,bag);
    }
    for (const auto& order:list) {
        QList<QStandardItem *> row;
        row.append(new QStandardItem(QString::number(order.id)));
        row.append(new QStandardItem(order.name));
        row.append(new QStandardItem(QVariant(order.date).toString()));
        row.append(new QStandardItem(bagMap[order.bagId].name));
        row.append(new QStandardItem(QString::number(order.floor)));
        row.append(new QStandardItem(bagMap[order.bagId].imagePath));
        orderModel->appendRow(row);
    }
    ui->label_7->setText(QString("当前页：%1/%2,共%3条记录").arg(orderPagination.currentPage).arg(orderPagination.totalPages).arg(orderPagination.totalRecords));
}

void MainWindow::updateOrder() {
    //根据当前订单的id获取订单的所有信息
    const QModelIndex & index = ui->OrderView->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this,"警告","请选择要更新的订单");
        return;
    }
    const int id=index.sibling(index.row(),0).data().toInt();
    const Result<order> order_result = OrderDao::getOrder(id);
    if (!order_result.isOk) {
        QMessageBox::warning(this,"警告","订单不存在");
        return;
    }
    order currentOrder=order_result.data;
    const auto & result = OrderDeatilDao::getOrderDetailList(currentOrder.id);
    currentOrder.orderDetailList=result.data;
    //把信息回显到dialog中
    if (orderDialog==nullptr) {
        orderDialog=new OrderDialog(this);
    }
    const QVector<Bag> bagList=bagDao::getAllBag();
    orderDialog->setBagList(bagList);
    orderDialog->setOrder(currentOrder);
    int r=orderDialog->exec();
    //获取dialog中的所有信息
    if (r==QDialog::Accepted) {
        const order newOrder = orderDialog->getOrder();
        //更新主信息
        const Result<QString> results = OrderDao::updateOrder(newOrder);
        if (!results.isOk) {
            QMessageBox::critical(this,"错误",results.message);
            return;
        }
        OrderDeatilDao::deleteByOrderId(newOrder.id);
        for (auto& orderDetail:newOrder.orderDetailList) {
            orderDetail.orderId=newOrder.id;
            const Result<QString> add_result = OrderDeatilDao::addOrderDetail(orderDetail);
            if (!add_result.isOk) {
                QMessageBox::critical(this,"错误",add_result.message);
                return;
            }
        }
        QMessageBox::information(this,"成功","更新订单成功");

        searchOrder();
        return;
    }


}

void MainWindow::deleteOrder() {
    const int & row = ui->OrderView->currentIndex().row();
    if (row<0) {
        QMessageBox::warning(this,"警告","请选择要删除的订单");
        return;
    }
    if (QMessageBox::No==QMessageBox::warning(this,"警告","确认删除吗？",QMessageBox::Yes|QMessageBox::No)) {
        return;
    }
    const int orderId=orderModel->item(row,0)->text().toInt();
    const auto & deleteOrderDetail = OrderDeatilDao::deleteByOrderId(orderId);
    if (!deleteOrderDetail.isOk) {
        QMessageBox::critical(this,"错误",deleteOrderDetail.message);
        return;
    }
    const auto & delete_order = OrderDao::deleteOrder(orderId);
    if (!delete_order.isOk) {
        QMessageBox::critical(this,"错误",delete_order.message);
        return;
    }
    QMessageBox::information(this,"成功","删除订单成功");
    orderModel->removeRow(row);
    searchOrder();
}

void MainWindow::getDetailEmployee() {
    //获取当前的员工
    const QModelIndex & index = ui->tableView->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this,"警告","请选择要查看的员工");
        return;
    }
    const int employeeId=index.sibling(index.row(),0).data().toInt();
    const Result<QVector<employee>> & result = EmployeeDao::getByIds(QSet<int>{employeeId});
    if (!result.isOk) {
        QMessageBox::warning(this,"警告","员工不存在");
        return;
    }
    const employee & data = result.data.first();
    if (employeeSalaryDialog==nullptr) {
        employeeSalaryDialog=new EmployeeSalaryDialog(this);
    }
    employeeSalaryDialog->setEmployee(data);
    employeeSalaryDialog->exec();


}
