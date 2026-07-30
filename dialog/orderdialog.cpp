//
// Created by 114514 on 2026/7/30.
//

// You may need to build the project (run Qt uic code generator) to get "ui_OrderDialog.h" resolved

#include "orderdialog.h"
#include "ui_OrderDialog.h"
#include "dao/BagProcessDao.h"
#include "dao/EmployeeDao.h"
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
    order.name=ui->lineEdit->text();
    order.date=ui->dateEdit->date();
    order.floor=ui->spinBox->value();
    return order;
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
        processItem->setEditable(false);
        QStandardItem *priceItem = new QStandardItem(QString::number(defaultPrices,'f',2));
        QStandardItem *countItem = new QStandardItem("");
        QStandardItem *employeeItem = new QStandardItem("");

        model->appendRow({idItem,processItem,priceItem,countItem,employeeItem});
    }
    ui->OrderDetailView->setItemDelegateForColumn(4,comboxDelegate);
    return Result<QString>::success("查询工序成功");
}
