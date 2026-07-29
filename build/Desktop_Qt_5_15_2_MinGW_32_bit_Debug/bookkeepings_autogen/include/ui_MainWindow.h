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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
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
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QPushButton *pushButtonPre;
    QPushButton *pushButtonNext;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonAddSearch;
    QLineEdit *lineEdit;
    QTableView *tableView;
    QLabel *label;
    QLabel *labelPreAndNext;
    QWidget *tab_2;
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
        page->setGeometry(QRect(0, 0, 421, 991));
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
        page_2->setGeometry(QRect(0, 0, 421, 991));
        toolBox->addItem(page_2, QStringLiteral("Page 2"));
        splitter->addWidget(toolBox);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButtonPre = new QPushButton(tab);
        pushButtonPre->setObjectName(QStringLiteral("pushButtonPre"));
        pushButtonPre->setMaximumSize(QSize(100, 16777215));

        gridLayout_2->addWidget(pushButtonPre, 3, 2, 1, 1);

        pushButtonNext = new QPushButton(tab);
        pushButtonNext->setObjectName(QStringLiteral("pushButtonNext"));
        pushButtonNext->setMaximumSize(QSize(100, 16777215));

        gridLayout_2->addWidget(pushButtonNext, 3, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 3, 5, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 3, 1, 1, 1);

        pushButtonAddSearch = new QPushButton(tab);
        pushButtonAddSearch->setObjectName(QStringLiteral("pushButtonAddSearch"));

        gridLayout_2->addWidget(pushButtonAddSearch, 0, 5, 1, 2);

        lineEdit = new QLineEdit(tab);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout_2->addWidget(lineEdit, 0, 1, 1, 1);

        tableView = new QTableView(tab);
        tableView->setObjectName(QStringLiteral("tableView"));

        gridLayout_2->addWidget(tableView, 1, 0, 1, 6);

        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        labelPreAndNext = new QLabel(tab);
        labelPreAndNext->setObjectName(QStringLiteral("labelPreAndNext"));

        gridLayout_2->addWidget(labelPreAndNext, 3, 4, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());
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

        toolBox->setCurrentIndex(0);
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
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("MainWindow", "Page 2", Q_NULLPTR));
        pushButtonPre->setText(QApplication::translate("MainWindow", "\344\270\212\344\270\200\351\241\265", Q_NULLPTR));
        pushButtonNext->setText(QApplication::translate("MainWindow", "\344\270\213\344\270\200\351\241\265", Q_NULLPTR));
        pushButtonAddSearch->setText(QApplication::translate("MainWindow", "\346\220\234\347\264\242", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\346\237\245\350\257\242", Q_NULLPTR));
        labelPreAndNext->setText(QApplication::translate("MainWindow", "\345\275\223\345\211\215\344\270\272\347\254\2541\351\241\265\357\274\214\346\200\273\345\205\26110\351\241\265", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "\345\221\230\345\267\245\351\241\265\351\235\242", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
