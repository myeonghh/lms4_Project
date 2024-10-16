/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout_3;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_4;
    QTableView *tableView;
    QWidget *tab_2;
    QGridLayout *gridLayout_5;
    QTabWidget *tabWidget_2;
    QWidget *tab_5;
    QWidget *tab_6;
    QWidget *tab_3;
    QLineEdit *lineEdit;
    QWidget *tab_4;
    QWidget *page_2;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_sendMessage;
    QPushButton *pushButton_sendAttachment;
    QLineEdit *lineEdit_message;
    QTextBrowser *textBrowser_receivedMessages;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1051, 687);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName("gridLayout_2");
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName("stackedWidget");
        page = new QWidget();
        page->setObjectName("page");
        gridLayout_3 = new QGridLayout(page);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName("gridLayout_3");
        tabWidget = new QTabWidget(page);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setStyleSheet(QString::fromUtf8("QTabWidget::pane {\n"
"    background-color: white;\n"
"    border: 2px solid black;\n"
"	border-radius:8px\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    background: white;\n"
"    border: 3px solid black;\n"
"    border-radius: 8px; \n"
"    padding: 10px;\n"
"	margin-right: 10px;\n"
"	margin-bottom: 5px;\n"
"	min-width: 100px;  \n"
"    min-height: 30px;  \n"
"	color: black;\n"
"	font-size: 16px;\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"    background: gray;\n"
"	color: white;\n"
"	font-weight: bold;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QTabWidget::tab-bar {  /* \355\203\255 \353\262\204\355\212\274\354\235\204 \352\260\220\354\213\270\353\212\224 \353\260\224 */\n"
"    left: 20px;  /* \355\203\255 \353\252\251\353\241\235\354\235\264 \354\231\274\354\252\275\354\234\274\353\241\234 \354\241\260\352\270\210 \354\235\264\353\217\231 */\n"
"}"));
        tab = new QWidget();
        tab->setObjectName("tab");
        gridLayout_4 = new QGridLayout(tab);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName("gridLayout_4");
        tableView = new QTableView(tab);
        tableView->setObjectName("tableView");

        gridLayout_4->addWidget(tableView, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        gridLayout_5 = new QGridLayout(tab_2);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName("gridLayout_5");
        tabWidget_2 = new QTabWidget(tab_2);
        tabWidget_2->setObjectName("tabWidget_2");
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        tabWidget_2->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName("tab_6");
        tabWidget_2->addTab(tab_6, QString());

        gridLayout_5->addWidget(tabWidget_2, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        lineEdit = new QLineEdit(tab_3);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(490, 30, 113, 25));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        tabWidget->addTab(tab_4, QString());

        gridLayout_3->addWidget(tabWidget, 0, 0, 1, 1);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        layoutWidget = new QWidget(page_2);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(0, 380, 735, 58));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_sendMessage = new QPushButton(layoutWidget);
        pushButton_sendMessage->setObjectName("pushButton_sendMessage");
        pushButton_sendMessage->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(pushButton_sendMessage, 1, 0, 1, 1);

        pushButton_sendAttachment = new QPushButton(layoutWidget);
        pushButton_sendAttachment->setObjectName("pushButton_sendAttachment");
        pushButton_sendAttachment->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(pushButton_sendAttachment, 1, 1, 1, 1);

        lineEdit_message = new QLineEdit(layoutWidget);
        lineEdit_message->setObjectName("lineEdit_message");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_message->sizePolicy().hasHeightForWidth());
        lineEdit_message->setSizePolicy(sizePolicy);
        lineEdit_message->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(lineEdit_message, 0, 0, 1, 2);

        textBrowser_receivedMessages = new QTextBrowser(page_2);
        textBrowser_receivedMessages->setObjectName("textBrowser_receivedMessages");
        textBrowser_receivedMessages->setGeometry(QRect(0, 16, 735, 358));
        textBrowser_receivedMessages->setStyleSheet(QString::fromUtf8(""));
        stackedWidget->addWidget(page_2);

        gridLayout_2->addWidget(stackedWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1051, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);
        tabWidget->setCurrentIndex(1);
        tabWidget_2->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "QTCPClient", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "\354\233\271\355\210\260 \354\240\204\354\262\264\353\252\251\353\241\235", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_5), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_6), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "\354\232\224\354\235\274\353\263\204 \354\233\271\355\210\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "\354\233\271\355\210\260 \352\262\200\354\203\211", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainWindow", "\354\233\271\355\210\260 \354\246\220\352\262\250\354\260\276\352\270\260", nullptr));
        pushButton_sendMessage->setText(QCoreApplication::translate("MainWindow", "Send Message", nullptr));
        pushButton_sendAttachment->setText(QCoreApplication::translate("MainWindow", "Send Attachment", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
