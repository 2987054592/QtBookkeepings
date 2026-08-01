/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QToolBox *toolBox;
    QWidget *page;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButtonAdd;
    QPushButton *pushButtonDel;
    QPushButton *pushButtonModify;
    QPushButton *pushButtonDetail;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *processAdd;
    QPushButton *processUpdata;
    QPushButton *processDelete;
    QWidget *page_3;
    QGridLayout *gridLayout_12;
    QPushButton *pbtAddBag;
    QPushButton *pbtUpdataBag;
    QPushButton *pbtDelBag;
    QPushButton *pbtDetailBag;
    QWidget *page_4;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pbtAddOrder;
    QPushButton *pbtDelOrder;
    QPushButton *pbtUpdataOrder;
    QPushButton *pbtDetailorder;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_7;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_6;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_4;
    QSpinBox *spinBox;
    QPushButton *pushButtonAddSearch;
    QTableView *tableView;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonPre;
    QPushButton *pushButtonNext;
    QLabel *labelPreAndNext;
    QSpacerItem *horizontalSpacer;
    QWidget *tab_2;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QPushButton *pbtProcessSearch;
    QTableView *tableView_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pbtProcessPre;
    QPushButton *pbtProcessNext;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_4;
    QWidget *tab_3;
    QGridLayout *gridLayout_11;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_10;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_8;
    QLabel *label_5;
    QLineEdit *lineEdit_3;
    QPushButton *pbtBagSearch;
    QTableView *tableView_3;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_9;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pbtBagPre;
    QPushButton *pbtBagNext;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_6;
    QWidget *tab_4;
    QGridLayout *gridLayout_13;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_15;
    QGroupBox *groupBox_10;
    QGridLayout *gridLayout_16;
    QLabel *label_8;
    QLineEdit *lineEdit_4;
    QLabel *label_9;
    QSpinBox *spinBox_2;
    QPushButton *pbtOrderSearch;
    QTableView *OrderView;
    QGroupBox *groupBox_9;
    QGridLayout *gridLayout_14;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *pbtOrderPre;
    QPushButton *pbtOrderNext;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_8;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1595, 1132);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        toolBox = new QToolBox(splitter);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setGeometry(QRect(0, 0, 201, 921));
        verticalLayout = new QVBoxLayout(page);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButtonAdd = new QPushButton(page);
        pushButtonAdd->setObjectName(QStringLiteral("pushButtonAdd"));

        verticalLayout->addWidget(pushButtonAdd);

        pushButtonDel = new QPushButton(page);
        pushButtonDel->setObjectName(QStringLiteral("pushButtonDel"));

        verticalLayout->addWidget(pushButtonDel);

        pushButtonModify = new QPushButton(page);
        pushButtonModify->setObjectName(QStringLiteral("pushButtonModify"));

        verticalLayout->addWidget(pushButtonModify);

        pushButtonDetail = new QPushButton(page);
        pushButtonDetail->setObjectName(QStringLiteral("pushButtonDetail"));

        verticalLayout->addWidget(pushButtonDetail);

        toolBox->addItem(page, QString::fromUtf8("\345\221\230\345\267\245\351\241\265\351\235\242"));
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        page_2->setGeometry(QRect(0, 0, 201, 921));
        verticalLayout_2 = new QVBoxLayout(page_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        processAdd = new QPushButton(page_2);
        processAdd->setObjectName(QStringLiteral("processAdd"));

        verticalLayout_2->addWidget(processAdd);

        processUpdata = new QPushButton(page_2);
        processUpdata->setObjectName(QStringLiteral("processUpdata"));

        verticalLayout_2->addWidget(processUpdata);

        processDelete = new QPushButton(page_2);
        processDelete->setObjectName(QStringLiteral("processDelete"));

        verticalLayout_2->addWidget(processDelete);

        toolBox->addItem(page_2, QString::fromUtf8("\345\267\245\345\272\217\351\241\265\351\235\242"));
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        page_3->setGeometry(QRect(0, 0, 201, 921));
        gridLayout_12 = new QGridLayout(page_3);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        pbtAddBag = new QPushButton(page_3);
        pbtAddBag->setObjectName(QStringLiteral("pbtAddBag"));

        gridLayout_12->addWidget(pbtAddBag, 0, 0, 1, 1);

        pbtUpdataBag = new QPushButton(page_3);
        pbtUpdataBag->setObjectName(QStringLiteral("pbtUpdataBag"));

        gridLayout_12->addWidget(pbtUpdataBag, 1, 0, 1, 1);

        pbtDelBag = new QPushButton(page_3);
        pbtDelBag->setObjectName(QStringLiteral("pbtDelBag"));

        gridLayout_12->addWidget(pbtDelBag, 2, 0, 1, 1);

        pbtDetailBag = new QPushButton(page_3);
        pbtDetailBag->setObjectName(QStringLiteral("pbtDetailBag"));

        gridLayout_12->addWidget(pbtDetailBag, 3, 0, 1, 1);

        toolBox->addItem(page_3, QString::fromUtf8("\344\271\246\345\214\205\351\241\265\351\235\242"));
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        page_4->setGeometry(QRect(0, 0, 201, 921));
        verticalLayout_3 = new QVBoxLayout(page_4);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        pbtAddOrder = new QPushButton(page_4);
        pbtAddOrder->setObjectName(QStringLiteral("pbtAddOrder"));

        verticalLayout_3->addWidget(pbtAddOrder);

        pbtDelOrder = new QPushButton(page_4);
        pbtDelOrder->setObjectName(QStringLiteral("pbtDelOrder"));

        verticalLayout_3->addWidget(pbtDelOrder);

        pbtUpdataOrder = new QPushButton(page_4);
        pbtUpdataOrder->setObjectName(QStringLiteral("pbtUpdataOrder"));

        verticalLayout_3->addWidget(pbtUpdataOrder);

        pbtDetailorder = new QPushButton(page_4);
        pbtDetailorder->setObjectName(QStringLiteral("pbtDetailorder"));

        verticalLayout_3->addWidget(pbtDetailorder);

        toolBox->addItem(page_4, QString::fromUtf8("\350\256\242\345\215\225\351\241\265\351\235\242"));
        splitter->addWidget(toolBox);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBox_4 = new QGroupBox(tab);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        gridLayout_7 = new QGridLayout(groupBox_4);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        groupBox_3 = new QGroupBox(groupBox_4);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_6 = new QGridLayout(groupBox_3);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        label = new QLabel(groupBox_3);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_6->addWidget(label, 0, 0, 1, 1);

        lineEdit = new QLineEdit(groupBox_3);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout_6->addWidget(lineEdit, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_6->addWidget(label_4, 0, 2, 1, 1);

        spinBox = new QSpinBox(groupBox_3);
        spinBox->setObjectName(QStringLiteral("spinBox"));

        gridLayout_6->addWidget(spinBox, 0, 3, 1, 1);

        pushButtonAddSearch = new QPushButton(groupBox_3);
        pushButtonAddSearch->setObjectName(QStringLiteral("pushButtonAddSearch"));

        gridLayout_6->addWidget(pushButtonAddSearch, 0, 4, 1, 1);


        gridLayout_7->addWidget(groupBox_3, 0, 0, 1, 1);

        tableView = new QTableView(groupBox_4);
        tableView->setObjectName(QStringLiteral("tableView"));

        gridLayout_7->addWidget(tableView, 1, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_4, 0, 0, 1, 5);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        pushButtonPre = new QPushButton(tab);
        pushButtonPre->setObjectName(QStringLiteral("pushButtonPre"));
        pushButtonPre->setMaximumSize(QSize(100, 16777215));

        gridLayout_2->addWidget(pushButtonPre, 1, 1, 1, 1);

        pushButtonNext = new QPushButton(tab);
        pushButtonNext->setObjectName(QStringLiteral("pushButtonNext"));
        pushButtonNext->setMaximumSize(QSize(100, 16777215));

        gridLayout_2->addWidget(pushButtonNext, 1, 2, 1, 1);

        labelPreAndNext = new QLabel(tab);
        labelPreAndNext->setObjectName(QStringLiteral("labelPreAndNext"));

        gridLayout_2->addWidget(labelPreAndNext, 1, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 4, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_4 = new QGridLayout(tab_2);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        groupBox_2 = new QGroupBox(tab_2);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_5 = new QGridLayout(groupBox_2);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        groupBox = new QGroupBox(groupBox_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_3->addWidget(label_2, 0, 0, 1, 1);

        lineEdit_2 = new QLineEdit(groupBox);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout_3->addWidget(lineEdit_2, 0, 1, 1, 1);

        pbtProcessSearch = new QPushButton(groupBox);
        pbtProcessSearch->setObjectName(QStringLiteral("pbtProcessSearch"));

        gridLayout_3->addWidget(pbtProcessSearch, 0, 2, 1, 1);


        gridLayout_5->addWidget(groupBox, 0, 0, 1, 1);

        tableView_2 = new QTableView(groupBox_2);
        tableView_2->setObjectName(QStringLiteral("tableView_2"));

        gridLayout_5->addWidget(tableView_2, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        pbtProcessPre = new QPushButton(groupBox_2);
        pbtProcessPre->setObjectName(QStringLiteral("pbtProcessPre"));

        horizontalLayout->addWidget(pbtProcessPre);

        pbtProcessNext = new QPushButton(groupBox_2);
        pbtProcessNext->setObjectName(QStringLiteral("pbtProcessNext"));

        horizontalLayout->addWidget(pbtProcessNext);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        gridLayout_5->addLayout(horizontalLayout, 2, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_2, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        gridLayout_11 = new QGridLayout(tab_3);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        groupBox_5 = new QGroupBox(tab_3);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        gridLayout_10 = new QGridLayout(groupBox_5);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        groupBox_6 = new QGroupBox(groupBox_5);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        gridLayout_8 = new QGridLayout(groupBox_6);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        label_5 = new QLabel(groupBox_6);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_8->addWidget(label_5, 0, 0, 1, 1);

        lineEdit_3 = new QLineEdit(groupBox_6);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        gridLayout_8->addWidget(lineEdit_3, 0, 1, 1, 1);

        pbtBagSearch = new QPushButton(groupBox_6);
        pbtBagSearch->setObjectName(QStringLiteral("pbtBagSearch"));

        gridLayout_8->addWidget(pbtBagSearch, 0, 2, 1, 1);


        gridLayout_10->addWidget(groupBox_6, 0, 0, 1, 1);

        tableView_3 = new QTableView(groupBox_5);
        tableView_3->setObjectName(QStringLiteral("tableView_3"));

        gridLayout_10->addWidget(tableView_3, 1, 0, 1, 1);

        groupBox_7 = new QGroupBox(groupBox_5);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        gridLayout_9 = new QGridLayout(groupBox_7);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        horizontalSpacer_5 = new QSpacerItem(356, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_5, 0, 0, 1, 1);

        pbtBagPre = new QPushButton(groupBox_7);
        pbtBagPre->setObjectName(QStringLiteral("pbtBagPre"));

        gridLayout_9->addWidget(pbtBagPre, 0, 1, 1, 1);

        pbtBagNext = new QPushButton(groupBox_7);
        pbtBagNext->setObjectName(QStringLiteral("pbtBagNext"));

        gridLayout_9->addWidget(pbtBagNext, 0, 2, 1, 1);

        label_6 = new QLabel(groupBox_7);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_9->addWidget(label_6, 0, 3, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_6, 0, 4, 1, 1);


        gridLayout_10->addWidget(groupBox_7, 2, 0, 1, 1);


        gridLayout_11->addWidget(groupBox_5, 0, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        gridLayout_13 = new QGridLayout(tab_4);
        gridLayout_13->setObjectName(QStringLiteral("gridLayout_13"));
        groupBox_8 = new QGroupBox(tab_4);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        gridLayout_15 = new QGridLayout(groupBox_8);
        gridLayout_15->setObjectName(QStringLiteral("gridLayout_15"));
        groupBox_10 = new QGroupBox(groupBox_8);
        groupBox_10->setObjectName(QStringLiteral("groupBox_10"));
        gridLayout_16 = new QGridLayout(groupBox_10);
        gridLayout_16->setObjectName(QStringLiteral("gridLayout_16"));
        label_8 = new QLabel(groupBox_10);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_16->addWidget(label_8, 0, 0, 1, 1);

        lineEdit_4 = new QLineEdit(groupBox_10);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));

        gridLayout_16->addWidget(lineEdit_4, 0, 1, 1, 1);

        label_9 = new QLabel(groupBox_10);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_16->addWidget(label_9, 0, 2, 1, 1);

        spinBox_2 = new QSpinBox(groupBox_10);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));

        gridLayout_16->addWidget(spinBox_2, 0, 3, 1, 1);

        pbtOrderSearch = new QPushButton(groupBox_10);
        pbtOrderSearch->setObjectName(QStringLiteral("pbtOrderSearch"));

        gridLayout_16->addWidget(pbtOrderSearch, 0, 4, 1, 1);


        gridLayout_15->addWidget(groupBox_10, 0, 0, 1, 1);

        OrderView = new QTableView(groupBox_8);
        OrderView->setObjectName(QStringLiteral("OrderView"));

        gridLayout_15->addWidget(OrderView, 1, 0, 1, 1);

        groupBox_9 = new QGroupBox(groupBox_8);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        gridLayout_14 = new QGridLayout(groupBox_9);
        gridLayout_14->setObjectName(QStringLiteral("gridLayout_14"));
        horizontalSpacer_7 = new QSpacerItem(356, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_14->addItem(horizontalSpacer_7, 0, 0, 1, 1);

        pbtOrderPre = new QPushButton(groupBox_9);
        pbtOrderPre->setObjectName(QStringLiteral("pbtOrderPre"));

        gridLayout_14->addWidget(pbtOrderPre, 0, 1, 1, 1);

        pbtOrderNext = new QPushButton(groupBox_9);
        pbtOrderNext->setObjectName(QStringLiteral("pbtOrderNext"));

        gridLayout_14->addWidget(pbtOrderNext, 0, 2, 1, 1);

        label_7 = new QLabel(groupBox_9);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_14->addWidget(label_7, 0, 3, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_14->addItem(horizontalSpacer_8, 0, 4, 1, 1);


        gridLayout_15->addWidget(groupBox_9, 2, 0, 1, 1);


        gridLayout_13->addWidget(groupBox_8, 0, 0, 1, 1);

        tabWidget->addTab(tab_4, QString());
        splitter->addWidget(tabWidget);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        toolBox->setCurrentIndex(1);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        pushButtonAdd->setText(QApplication::translate("MainWindow", "\345\242\236\345\212\240\345\221\230\345\267\245", Q_NULLPTR));
        pushButtonDel->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\345\221\230\345\267\245", Q_NULLPTR));
        pushButtonModify->setText(QApplication::translate("MainWindow", "\344\277\256\346\224\271\345\221\230\345\267\245", Q_NULLPTR));
        pushButtonDetail->setText(QApplication::translate("MainWindow", "\346\237\245\347\234\213\345\221\230\345\267\245\350\257\246\346\203\205", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("MainWindow", "\345\221\230\345\267\245\351\241\265\351\235\242", Q_NULLPTR));
        processAdd->setText(QApplication::translate("MainWindow", "\345\242\236\345\212\240\345\267\245\345\272\217", Q_NULLPTR));
        processUpdata->setText(QApplication::translate("MainWindow", "\346\233\264\346\226\260\345\267\245\345\272\217", Q_NULLPTR));
        processDelete->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\345\267\245\345\272\217", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("MainWindow", "\345\267\245\345\272\217\351\241\265\351\235\242", Q_NULLPTR));
        pbtAddBag->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\344\271\246\345\214\205", Q_NULLPTR));
        pbtUpdataBag->setText(QApplication::translate("MainWindow", "\344\277\256\346\224\271\344\271\246\345\214\205", Q_NULLPTR));
        pbtDelBag->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\344\271\246\345\214\205", Q_NULLPTR));
        pbtDetailBag->setText(QApplication::translate("MainWindow", "\346\237\245\347\234\213\350\257\246\346\203\205", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page_3), QApplication::translate("MainWindow", "\344\271\246\345\214\205\351\241\265\351\235\242", Q_NULLPTR));
        pbtAddOrder->setText(QApplication::translate("MainWindow", "\346\226\260\345\242\236\350\256\242\345\215\225", Q_NULLPTR));
        pbtDelOrder->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\350\256\242\345\215\225", Q_NULLPTR));
        pbtUpdataOrder->setText(QApplication::translate("MainWindow", "\344\277\256\346\224\271\350\256\242\345\215\225", Q_NULLPTR));
        pbtDetailorder->setText(QApplication::translate("MainWindow", "\346\237\245\347\234\213\350\256\242\345\215\225", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page_4), QApplication::translate("MainWindow", "\350\256\242\345\215\225\351\241\265\351\235\242", Q_NULLPTR));
        groupBox_4->setTitle(QString());
        groupBox_3->setTitle(QString());
        label->setText(QApplication::translate("MainWindow", "\346\237\245\350\257\242", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "\346\245\274\345\261\202", Q_NULLPTR));
        pushButtonAddSearch->setText(QApplication::translate("MainWindow", "\346\220\234\347\264\242", Q_NULLPTR));
        pushButtonPre->setText(QApplication::translate("MainWindow", "\344\270\212\344\270\200\351\241\265", Q_NULLPTR));
        pushButtonNext->setText(QApplication::translate("MainWindow", "\344\270\213\344\270\200\351\241\265", Q_NULLPTR));
        labelPreAndNext->setText(QApplication::translate("MainWindow", "\345\275\223\345\211\215\344\270\272\347\254\2541\351\241\265\357\274\214\346\200\273\345\205\26110\351\241\265", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "\345\221\230\345\267\245\351\241\265\351\235\242", Q_NULLPTR));
        groupBox_2->setTitle(QString());
        groupBox->setTitle(QString());
        label_2->setText(QApplication::translate("MainWindow", "\346\237\245\350\257\242", Q_NULLPTR));
        pbtProcessSearch->setText(QApplication::translate("MainWindow", "\346\220\234\347\264\242", Q_NULLPTR));
        pbtProcessPre->setText(QApplication::translate("MainWindow", "\344\270\212\344\270\200\351\241\265", Q_NULLPTR));
        pbtProcessNext->setText(QApplication::translate("MainWindow", "\344\270\213\344\270\200\351\241\265", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "\345\275\223\345\211\215\344\270\272\347\254\2541\351\241\265\357\274\214\346\200\273\345\205\26110\351\241\265", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "\345\267\245\345\272\217\351\241\265\351\235\242", Q_NULLPTR));
        groupBox_5->setTitle(QString());
        groupBox_6->setTitle(QString());
        label_5->setText(QApplication::translate("MainWindow", "\346\237\245\350\257\242", Q_NULLPTR));
        pbtBagSearch->setText(QApplication::translate("MainWindow", "\346\220\234\347\264\242", Q_NULLPTR));
        groupBox_7->setTitle(QString());
        pbtBagPre->setText(QApplication::translate("MainWindow", "\344\270\212\344\270\200\351\241\265", Q_NULLPTR));
        pbtBagNext->setText(QApplication::translate("MainWindow", "\344\270\213\344\270\200\351\241\265", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "\345\275\223\345\211\215\344\270\272\347\254\2541\351\241\265\357\274\214\346\200\273\345\205\26110\351\241\265", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "\344\271\246\345\214\205\351\241\265\351\235\242", Q_NULLPTR));
        groupBox_8->setTitle(QString());
        groupBox_10->setTitle(QString());
        label_8->setText(QApplication::translate("MainWindow", "\346\237\245\350\257\242", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "\346\245\274\345\261\202", Q_NULLPTR));
        pbtOrderSearch->setText(QApplication::translate("MainWindow", "\346\220\234\347\264\242", Q_NULLPTR));
        groupBox_9->setTitle(QString());
        pbtOrderPre->setText(QApplication::translate("MainWindow", "\344\270\212\344\270\200\351\241\265", Q_NULLPTR));
        pbtOrderNext->setText(QApplication::translate("MainWindow", "\344\270\213\344\270\200\351\241\265", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "\345\275\223\345\211\215\344\270\272\347\254\2541\351\241\265\357\274\214\346\200\273\345\205\26110\351\241\265", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "\350\256\242\345\215\225\351\241\265\351\235\242", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
