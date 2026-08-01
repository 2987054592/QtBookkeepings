//
// Created by 114514 on 2026/7/31.
//

// You may need to build the project (run Qt uic code generator) to get "ui_EmployeeSalaryDialog.h" resolved

#include "employeesalarydialog.h"

#include <QMessageBox>

#include "ui_EmployeeSalaryDialog.h"
#include "dao/OrderDao.h"
#include "dao/OrderDeatilDao.h"
#include "dao/ProcessDao.h"
#include "vo/EmployeeMonthSalary.h"
#include "vo/OrderDetailtem.h"


EmployeeSalaryDialog::EmployeeSalaryDialog(QWidget *parent) : QDialog(parent), ui(new Ui::EmployeeSalaryDialog) {
    ui->setupUi(this);
    model=new QStandardItemModel(this);
    ui->treeView->setModel(model);
    ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->pushButtonPre,&QPushButton::clicked,this,&EmployeeSalaryDialog::prevPage);
    connect(ui->pushButtonNext,&QPushButton::clicked,this,&EmployeeSalaryDialog::nextPage);
}

EmployeeSalaryDialog::~EmployeeSalaryDialog() {
    delete ui;
}

void EmployeeSalaryDialog::setEmployee(const employee &employee) {
    model->clear();
    model->setHorizontalHeaderLabels({"月份","姓名","工资"});
    ui->label->setText(QString("员工:%1的工资详情").arg(employee.name));
    m_employeeId=employee.id;
    m_employeeName=employee.name;
    loadSalary();
}

void EmployeeSalaryDialog::prevPage() {
    if (currentPage>1) {
        currentPage--;
        loadSalary();
    }
}

void EmployeeSalaryDialog::nextPage() {
    if (currentPage<totalPages) {
        currentPage++;
        loadSalary();
    }
}

void EmployeeSalaryDialog::loadSalary() {
    //根据员工id通过OrderDetailDao获取该员工的所有信息（分页查询）
    //key为订单id,value为订单详情列表
    const auto & orderDetailInfoMap = OrderDeatilDao::getOrderDetailListByEmployeeId(currentPage,pageSize,m_employeeId);
    if (!orderDetailInfoMap.isOk) {
        QMessageBox::critical(this,"错误",orderDetailInfoMap.message);
        return;
    }
    model->clear();
    model->setHorizontalHeaderLabels({"月份/订单名称","工序名称","单价","数量","金额"});


    //再根据查出来的订单id查询订单
    const auto & orderIds = orderDetailInfoMap.data.data.keys().toSet();
    //key为月份,value为订单列表
    const auto & OrderMap = OrderDao::getOrderByOrderIds(orderIds);
    if (!OrderMap.isOk) {
        QMessageBox::critical(this,"错误",OrderMap.message);
        return;
    }

    totalRecords=OrderMap.data.size();
    totalPages=(totalRecords+pageSize-1)/pageSize;
    for (auto it=OrderMap.data.begin();it!=OrderMap.data.end();it++) {
        EmployeeMonthSalary month_salary;
        month_salary.month=it.key();
        month_salary.totalSalary=0;

        QVector<order> orders=it.value();
        QStandardItem *monthItem=new QStandardItem(month_salary.month);
        monthItem->setFont(QFont("",-1,QFont::Bold));
        QStandardItem *monthTotal=new QStandardItem("");
        model->appendRow({monthItem,new QStandardItem("空"),new QStandardItem("空"),new QStandardItem("空"),monthTotal});

        for (const order &o:orders) {
            EmployeeOrderSummary summary;
            summary.orderId=o.id;
            summary.orderName=o.name;
            summary.orderDate=o.date;
            summary.totalPrice=0;
            summary.details=orderDetailInfoMap.data.data.value(o.id);

            QStandardItem *orderNameItem=new QStandardItem(summary.orderName);
            QStandardItem *orderTotalItem=new QStandardItem(QString::number(summary.totalPrice));
            monthItem->appendRow({orderNameItem,new QStandardItem("空"),new QStandardItem("空"),new QStandardItem("空"),orderTotalItem});

            const auto & order_details = orderDetailInfoMap.data.data.value(o.id);
            QSet<int> processId;
            for (const auto& od:order_details) {
                processId.insert(od.processId);
            }
            const auto & processList = ProcessDao::getByIds(processId);
            if (!processList.isOk) {
                QMessageBox::critical(this,"错误",processList.message);
                return;
            }


            QMap<int,QString> processNameMap;
            for (const auto& od:processList.data) {
                processNameMap[od.id]=od.name;
            }
            for (const auto &od:order_details) {
                qint64 amount=static_cast<qint64>(od.real_price)*od.real_quantity;
                summary.totalPrice+=amount;

                QStandardItem *processNameItem=new QStandardItem(processNameMap[od.processId]);
                QStandardItem *processPriceItem=new QStandardItem(QString::number(od.real_price/1000.0,'f',2));
                QStandardItem *processQuantityItem=new QStandardItem(QString::number(od.real_quantity));
                QStandardItem *processTotalItem=new QStandardItem(QString::number(amount/1000.0,'f',2));
                orderNameItem->appendRow({new QStandardItem("空"),processNameItem,processPriceItem,processQuantityItem,processTotalItem});

            }
            orderTotalItem->setText(QString::number(summary.totalPrice/1000.0,'f',2));
            month_salary.orders.append(summary);
            month_salary.totalSalary+=summary.totalPrice;

        }

        monthTotal->setText(QString::number(month_salary.totalSalary/1000.0,'f',2));
    }
    ui->labelPage->setText(QString("当前页：%1/%2,共%3条记录").arg(currentPage).arg(totalPages).arg(totalRecords));
    ui->treeView->expandAll();
}
