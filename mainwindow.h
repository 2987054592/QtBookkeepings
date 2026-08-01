//
// Created by 114514 on 2026/7/26.
//

#ifndef BOOKKEEPINGS_MAINWINDOW_H
#define BOOKKEEPINGS_MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include "customDelegateImage/ImageDelegate.h"
#include "dialog/employeedialog.h"
#include "dialog/bag.h"
#include "dialog/employeesalarydialog.h"
#include "dialog/orderdialog.h"


QT_BEGIN_NAMESPACE
struct PaginationState {
    int currentPage=1;
    int totalRecords=0;
    int totalPages=0;
};
namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;
private:


    void initData();
private:
    int pageSize=10;

    PaginationState employeePagination;
    PaginationState processPagination;
    PaginationState bagPagination;
    PaginationState orderPagination;


    Ui::MainWindow *ui;
    QStandardItemModel *employeeModel;
    QStandardItemModel *processModel;
    QStandardItemModel *bagModel;
    QStandardItemModel *orderModel;

    EmployeeDialog *employee_dialog=nullptr;
    OrderDialog *orderDialog=nullptr;
    BagDialog *bagDialog=nullptr;
    EmployeeSalaryDialog *employeeSalaryDialog=nullptr;

private slots:
    void addEmployee();
    void deleteEmployee();
    void updateEmployee();
    void searchEmployee();
    void getDetailEmployee();


    void addProcess();
    void updateProcess();
    void searchProcess();
    void deleteProcess();


    void addBag();
    void searchBag();
    void getDetailBag();
    void updateBag();
    void deleteBag();

    void addOrder();
    void searchOrder();
    void updateOrder();
    void deleteOrder();

};


#endif //BOOKKEEPINGS_MAINWINDOW_H