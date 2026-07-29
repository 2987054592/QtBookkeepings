//
// Created by 114514 on 2026/7/26.
//

#ifndef BOOKKEEPINGS_MAINWINDOW_H
#define BOOKKEEPINGS_MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include <QStandardItemModel>
#include "dialog/employeedialog.h"
#include "dialog/bag.h"


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


    Ui::MainWindow *ui;
    QStandardItemModel *employeeModel;
    QStandardItemModel *processModel;
    QStandardItemModel *bagModel;

    EmployeeDialog *employee_dialog=nullptr;
    BagDialog *bagDialog=nullptr;

private slots:
    void addEmployee();
    void deleteEmployee();
    void updateEmployee();
    void searchEmployee();


    void addProcess();
    void deleteProcess();
    void updateProcess();
    void searchProcess();


    void addBag();
    void searchBag();
};


#endif //BOOKKEEPINGS_MAINWINDOW_H