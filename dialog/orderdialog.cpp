//
// Created by 114514 on 2026/7/30.
//

// You may need to build the project (run Qt uic code generator) to get "ui_OrderDialog.h" resolved

#include "orderdialog.h"

#include <QMessageBox>

#include "ui_OrderDialog.h"
#include "dao/BagProcessDao.h"
#include "dao/EmployeeDao.h"
#include "dao/OrderDeatilDao.h"
#include "dao/ProcessDao.h"



OrderDialog::OrderDialog(QWidget *parent) : QDialog(parent), ui(new Ui::OrderDialog) {
    ui->setupUi(this);
    connect(ui->comboBox,qOverload<int
        >(&QComboBox::currentIndexChanged),this,&OrderDialog::loadProcess);

    model=new QStandardItemModel(this);
    ui->OrderDetailView->setModel(model);
    model->setHorizontalHeaderLabels({"ID", "工序", "金额","数量","人员"});
    ui->OrderDetailView->setEditTriggers(QAbstractItemView::DoubleClicked);
    comboxDelegate=new ComboxDelegate(this);

    auto employees = EmployeeDao::getEmployees(1,100000,"",0);

    comboxDelegate->setData(employees.data.data);

    connect(ui->pbtNumberAll,&QPushButton::clicked,this,&OrderDialog::AllNumber);
    connect(ui->pbtMoreProcess,&QPushButton::clicked,this,&OrderDialog::AddMoreProcess);
    connect(ui->pbtDelProcess,&QPushButton::clicked,this,&OrderDialog::DeleteProcess);
}

OrderDialog::~OrderDialog() {
    delete ui;
}

void OrderDialog::setBagList(const QVector<Bag>& bags) {
    ui->comboBox->clear();
    for (auto &bag:bags) {
        ui->comboBox->addItem(bag.name,QVariant(bag.id));
    }
}

order OrderDialog::getOrder() {
    order order;
    const QVariant current_data = ui->comboBox->currentData();
    order.bagId=current_data.toInt();
    order.date=ui->dateEdit->date();
    order.floor=ui->spinBox->value();
    order.name=ui->lineEditOrderName->text();
    order.id=m_orderId;


    QVector<orderDetail> orderDetailList;
    for (int r=0;r<model->rowCount();r++) {
        orderDetail orderDetail;
        orderDetail.id=model->index(r,0).data().toInt();
        orderDetail.processId=model->index(r,1).data(Qt::UserRole).toInt();
        orderDetail.real_price = qRound64(model->index(r,2).data().toDouble() * 1000);
        orderDetail.real_quantity=model->index(r,3).data().toInt();
        orderDetail.employeeId=model->index(r,4).data(Qt::UserRole).toInt();
        orderDetailList.append(orderDetail);
    }
    order.orderDetailList=orderDetailList;
    return order;
}

void OrderDialog::setOrder(const order &order) {

    ui->dateEdit->setDate(order.date);
    ui->spinBox->setValue(order.floor);
    ui->lineEditOrderName->setText(order.name);
    m_orderId=order.id;
    //获取和订单相关的工序
    QVector<orderDetail> list = order.orderDetailList;
    QSet<int> processIds;
    QSet<int> employeeIds;
    for (auto &e:list) {
        processIds.insert(e.processId);
        employeeIds.insert(e.employeeId);
    }
    QMap<int,QString> process_map;
    QMap<int,QString> employee_map;

    auto result = ProcessDao::getByIds(processIds);
    if (!result.isOk) {
        QMessageBox::critical(this,"错误",result.message);
        return;
    }
    for (const processs &process:result.data) {
        process_map[process.id]=process.name;
    }

    auto employee_result = EmployeeDao::getByIds(employeeIds);
    if (!employee_result.isOk) {
        QMessageBox::critical(this,"错误",employee_result.message);
        return;
    }
    for (const employee &employee:employee_result.data) {
        employee_map[employee.id]=employee.name;
    }


    ui->comboBox->setCurrentIndex(ui->comboBox->findData(order.bagId));
    model->clear();
    model->setHorizontalHeaderLabels({"ID", "工序", "金额","数量","人员"});
    ui->OrderDetailView->setEditTriggers(QAbstractItemView::DoubleClicked);
    for (auto & detail:order.orderDetailList) {
        QStandardItem *idItem = new QStandardItem(QString::number(detail.id));
        idItem->setEditable(false);
        QStandardItem *processItem = new QStandardItem(process_map[detail.processId]);
        processItem->setData(detail.processId,Qt::UserRole);
        processItem->setEditable(false);
        QStandardItem *priceItem = new QStandardItem(QString::number(detail.real_price/1000.00,'f',2));
        priceItem->setEditable(false);
        QStandardItem *countItem = new QStandardItem(QString::number(detail.real_quantity));
        countItem->setEditable(true);
        QStandardItem *employeeItem = new QStandardItem(employee_map[detail.employeeId]);
        employeeItem->setData(detail.employeeId,Qt::UserRole);
        model->appendRow({idItem,processItem,priceItem,countItem,employeeItem});
        ui->OrderDetailView->setItemDelegateForColumn(4,comboxDelegate);
    }




}



Result<QString> OrderDialog::loadProcess(int index) {
    Q_UNUSED(index);

    const QVariant current_data = ui->comboBox->currentData();
    int bagId=current_data.toInt();
    auto query_process_list_by_bag_id = BagProcessDao::queryProcessListByBagId(bagId);
    if (!query_process_list_by_bag_id.isOk) {
        return Result<QString>::error(query_process_list_by_bag_id.message);
    }
    model->clear();
    model->setHorizontalHeaderLabels({"ID", "工序", "金额","数量","人员"});
    ui->OrderDetailView->verticalHeader()->hide();
    QSet<int> processIds;
    for (const BagProcess &process:query_process_list_by_bag_id.data) {
        processIds.insert(process.processId);
    }

    auto result = ProcessDao::getByIds(processIds);
    if (!result.isOk) {
        return Result<QString>::error(result.message);
    }
    QMap<int,QString> process_map;
    for (const processs &process:result.data) {
        process_map[process.id]=process.name;
    }


    for (const BagProcess &process:query_process_list_by_bag_id.data) {
        double defaultPrices = process.defaultPrices/1000.00;

        QStandardItem *idItem = new QStandardItem(QString::number(process.id));
        idItem->setEditable(false);
        QStandardItem *processItem = new QStandardItem(process_map[process.processId]);
        processItem->setData(process.processId,Qt::UserRole);

        processItem->setEditable(false);
        QStandardItem *priceItem = new QStandardItem(QString::number(defaultPrices,'f',2));
        QStandardItem *countItem = new QStandardItem("");
        QStandardItem *employeeItem = new QStandardItem("");
        employeeItem->setData(0,Qt::UserRole);

        model->appendRow({idItem,processItem,priceItem,countItem,employeeItem});
    }
    ui->OrderDetailView->setItemDelegateForColumn(4,comboxDelegate);

    return Result<QString>::success("查询工序成功");
}

void OrderDialog::AddMoreProcess() {
     if (orderProcessDialog==nullptr) {
        orderProcessDialog = new OrderProcessDialog(this);
     }
    auto processes = ProcessDao::getProcesses(1,100000,"");
    auto employee= EmployeeDao::getEmployees(1,100000,"",0);
     orderProcessDialog->setDataProcess(processes.data.data);
     orderProcessDialog->setDataEmployee(employee.data.data);
     if (orderProcessDialog->exec()==QDialog::Accepted) {
        orderDetail orderDetail = orderProcessDialog->getOrderDetail();
         QMap<int,QString> process_map;
         for (const processs &process:processes.data.data) {
            process_map[process.id]=process.name;
         }
         QMap<int,QString> employee_map;
         for (auto &e:employee.data.data) {
             employee_map[e.id]=e.name;
         }
         QStandardItem *employeeItem = new QStandardItem(employee_map[orderDetail.employeeId]);
         employeeItem->setData(orderDetail.employeeId,Qt::UserRole);
         QStandardItem *processItem = new QStandardItem(process_map[orderDetail.processId]);
         processItem->setData(orderDetail.processId,Qt::UserRole);
        model->appendRow({new QStandardItem(QString::number(orderDetail.processId)),processItem,new QStandardItem(QString::number(orderDetail.real_price/1000.00,'f',2)),new QStandardItem(QString::number(orderDetail.real_quantity)),employeeItem});
     }
}

void OrderDialog::AllNumber() {
    QString number=ui->lineEdit_3->text();
    if (number.isEmpty()|| number.isNull()) {
        QMessageBox::warning(this,"警告","请输入数量");
        return;
    }
    for (int i=0;i<model->rowCount();i++) {
        model->item(i,3)->setText(number);
    }
}

void OrderDialog::DeleteProcess() {
    model->removeRow(ui->OrderDetailView->currentIndex().row());
}
