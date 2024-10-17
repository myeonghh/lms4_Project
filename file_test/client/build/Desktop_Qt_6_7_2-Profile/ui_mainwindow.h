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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
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
    QTabWidget *mainTabWidget;
    QWidget *entireListTab;
    QGridLayout *gridLayout_4;
    QTableView *e_tableView;
    QFrame *detailView_frame;
    QVBoxLayout *verticalLayout_2;
    QTableView *e_detailTableView;
    QPushButton *e_back_btn;
    QWidget *dayTab;
    QGridLayout *gridLayout_5;
    QTabWidget *dayTabWidget;
    QWidget *tab_5;
    QGridLayout *gridLayout_7;
    QTableView *tableView_mon;
    QWidget *tab_6;
    QGridLayout *gridLayout_8;
    QTableView *tableView_tue;
    QWidget *tab_7;
    QGridLayout *gridLayout_9;
    QTableView *tableView_wed;
    QWidget *tab_8;
    QGridLayout *gridLayout_10;
    QTableView *tableView_thu;
    QWidget *tab_9;
    QGridLayout *gridLayout_11;
    QTableView *tableView_fri;
    QWidget *tab_10;
    QGridLayout *gridLayout_12;
    QTableView *tableView_sat;
    QWidget *tab_11;
    QGridLayout *gridLayout_13;
    QTableView *tableView_sun;
    QWidget *searchTab;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QLabel *label;
    QLineEdit *toonSearchText;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QTableView *tableView_2;
    QWidget *bookMarkTab;
    QGridLayout *gridLayout_6;
    QTableView *b_tableView;
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
        mainTabWidget = new QTabWidget(page);
        mainTabWidget->setObjectName("mainTabWidget");
        mainTabWidget->setStyleSheet(QString::fromUtf8("#mainTabWidget QTabWidget::pane {\n"
"    background-color: white;\n"
"    border: 2px solid black;\n"
"	border-radius:8px\n"
"}\n"
"\n"
"#mainTabWidget QTabBar::tab {\n"
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
"#mainTabWidget QTabBar::tab:selected {\n"
"    background: gray;\n"
"	color: white;\n"
"	font-weight: bold;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QTabWidget::tab-bar {  /* \355\203\255 \353\262\204\355\212\274\354\235\204 \352\260\220\354\213\270\353\212\224 \353\260\224 */\n"
"    left: 20px;  /* \355\203\255 \353\252\251\353\241\235\354\235\264 \354\231\274\354\252\275\354\234\274\353\241\234 \354\241\260\352\270\210 \354\235\264\353\217\231 */\n"
"}"));
        entireListTab = new QWidget();
        entireListTab->setObjectName("entireListTab");
        gridLayout_4 = new QGridLayout(entireListTab);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName("gridLayout_4");
        e_tableView = new QTableView(entireListTab);
        e_tableView->setObjectName("e_tableView");
        QFont font;
        font.setFamilies({QString::fromUtf8("Ubuntu")});
        font.setPointSize(13);
        font.setBold(false);
        e_tableView->setFont(font);
        e_tableView->setStyleSheet(QString::fromUtf8(""));
        e_tableView->setFrameShape(QFrame::Shape::StyledPanel);
        e_tableView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        e_tableView->setTextElideMode(Qt::TextElideMode::ElideMiddle);
        e_tableView->setGridStyle(Qt::PenStyle::SolidLine);
        e_tableView->setSortingEnabled(false);

        gridLayout_4->addWidget(e_tableView, 0, 0, 1, 1);

        detailView_frame = new QFrame(entireListTab);
        detailView_frame->setObjectName("detailView_frame");
        detailView_frame->setMinimumSize(QSize(0, 0));
        detailView_frame->setStyleSheet(QString::fromUtf8("#detailView_frame QFrame {\n"
"    border: none;\n"
"	padding:0px;\n"
"}"));
        detailView_frame->setFrameShape(QFrame::Shape::StyledPanel);
        detailView_frame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_2 = new QVBoxLayout(detailView_frame);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        e_detailTableView = new QTableView(detailView_frame);
        e_detailTableView->setObjectName("e_detailTableView");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Ubuntu")});
        e_detailTableView->setFont(font1);
        e_detailTableView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

        verticalLayout_2->addWidget(e_detailTableView);

        e_back_btn = new QPushButton(detailView_frame);
        e_back_btn->setObjectName("e_back_btn");

        verticalLayout_2->addWidget(e_back_btn);


        gridLayout_4->addWidget(detailView_frame, 0, 1, 1, 1);

        mainTabWidget->addTab(entireListTab, QString());
        dayTab = new QWidget();
        dayTab->setObjectName("dayTab");
        gridLayout_5 = new QGridLayout(dayTab);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName("gridLayout_5");
        dayTabWidget = new QTabWidget(dayTab);
        dayTabWidget->setObjectName("dayTabWidget");
        dayTabWidget->setStyleSheet(QString::fromUtf8("#dayTabWidget QTabWidget::pane {\n"
"    background-color: white;\n"
"    border: 2px solid black;\n"
"	border-radius:8px\n"
"}\n"
"\n"
"#dayTabWidget QTabBar::tab {\n"
"    background: lightblue;\n"
"    border: 3px solid black;\n"
"    border-radius: 8px; \n"
"    padding: 10px;\n"
"	margin-right: 10px;\n"
"	margin-bottom: 5px;\n"
"	min-width: 65px;  \n"
"    min-height: 20px;  \n"
"	color: black;\n"
"	font-size: 16px;\n"
"}\n"
"\n"
"#dayTabWidget QTabBar::tab:selected {\n"
"    background: darkblue;\n"
"	color: white;\n"
"	font-weight: bold;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QTabWidget::tab-bar {  /* \355\203\255 \353\262\204\355\212\274\354\235\204 \352\260\220\354\213\270\353\212\224 \353\260\224 */\n"
"    left: 130px;  /* \355\203\255 \353\252\251\353\241\235\354\235\264 \354\231\274\354\252\275\354\234\274\353\241\234 \354\241\260\352\270\210 \354\235\264\353\217\231 */\n"
"}"));
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        gridLayout_7 = new QGridLayout(tab_5);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName("gridLayout_7");
        tableView_mon = new QTableView(tab_5);
        tableView_mon->setObjectName("tableView_mon");

        gridLayout_7->addWidget(tableView_mon, 0, 0, 1, 1);

        dayTabWidget->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName("tab_6");
        gridLayout_8 = new QGridLayout(tab_6);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName("gridLayout_8");
        tableView_tue = new QTableView(tab_6);
        tableView_tue->setObjectName("tableView_tue");

        gridLayout_8->addWidget(tableView_tue, 0, 0, 1, 1);

        dayTabWidget->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName("tab_7");
        gridLayout_9 = new QGridLayout(tab_7);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName("gridLayout_9");
        tableView_wed = new QTableView(tab_7);
        tableView_wed->setObjectName("tableView_wed");

        gridLayout_9->addWidget(tableView_wed, 0, 0, 1, 1);

        dayTabWidget->addTab(tab_7, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName("tab_8");
        gridLayout_10 = new QGridLayout(tab_8);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName("gridLayout_10");
        tableView_thu = new QTableView(tab_8);
        tableView_thu->setObjectName("tableView_thu");

        gridLayout_10->addWidget(tableView_thu, 0, 0, 1, 1);

        dayTabWidget->addTab(tab_8, QString());
        tab_9 = new QWidget();
        tab_9->setObjectName("tab_9");
        gridLayout_11 = new QGridLayout(tab_9);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName("gridLayout_11");
        tableView_fri = new QTableView(tab_9);
        tableView_fri->setObjectName("tableView_fri");

        gridLayout_11->addWidget(tableView_fri, 0, 0, 1, 1);

        dayTabWidget->addTab(tab_9, QString());
        tab_10 = new QWidget();
        tab_10->setObjectName("tab_10");
        gridLayout_12 = new QGridLayout(tab_10);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName("gridLayout_12");
        tableView_sat = new QTableView(tab_10);
        tableView_sat->setObjectName("tableView_sat");

        gridLayout_12->addWidget(tableView_sat, 0, 0, 1, 1);

        dayTabWidget->addTab(tab_10, QString());
        tab_11 = new QWidget();
        tab_11->setObjectName("tab_11");
        gridLayout_13 = new QGridLayout(tab_11);
        gridLayout_13->setSpacing(6);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName("gridLayout_13");
        tableView_sun = new QTableView(tab_11);
        tableView_sun->setObjectName("tableView_sun");

        gridLayout_13->addWidget(tableView_sun, 0, 0, 1, 1);

        dayTabWidget->addTab(tab_11, QString());

        gridLayout_5->addWidget(dayTabWidget, 0, 0, 1, 1);

        mainTabWidget->addTab(dayTab, QString());
        searchTab = new QWidget();
        searchTab->setObjectName("searchTab");
        verticalLayout = new QVBoxLayout(searchTab);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        comboBox = new QComboBox(searchTab);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        horizontalLayout->addWidget(comboBox);

        label = new QLabel(searchTab);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        toonSearchText = new QLineEdit(searchTab);
        toonSearchText->setObjectName("toonSearchText");

        horizontalLayout->addWidget(toonSearchText);

        pushButton = new QPushButton(searchTab);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        tableView_2 = new QTableView(searchTab);
        tableView_2->setObjectName("tableView_2");

        verticalLayout->addWidget(tableView_2);

        mainTabWidget->addTab(searchTab, QString());
        bookMarkTab = new QWidget();
        bookMarkTab->setObjectName("bookMarkTab");
        gridLayout_6 = new QGridLayout(bookMarkTab);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName("gridLayout_6");
        b_tableView = new QTableView(bookMarkTab);
        b_tableView->setObjectName("b_tableView");

        gridLayout_6->addWidget(b_tableView, 0, 0, 1, 1);

        mainTabWidget->addTab(bookMarkTab, QString());

        gridLayout_3->addWidget(mainTabWidget, 0, 0, 1, 1);

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
        mainTabWidget->setCurrentIndex(2);
        dayTabWidget->setCurrentIndex(6);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "QTCPClient", nullptr));
        e_back_btn->setText(QCoreApplication::translate("MainWindow", "\353\222\244\353\241\234 \352\260\200\352\270\260", nullptr));
        mainTabWidget->setTabText(mainTabWidget->indexOf(entireListTab), QCoreApplication::translate("MainWindow", "\354\233\271\355\210\260 \354\240\204\354\262\264\353\252\251\353\241\235", nullptr));
        dayTabWidget->setTabText(dayTabWidget->indexOf(tab_5), QCoreApplication::translate("MainWindow", "\354\233\224\354\232\224\354\235\274", nullptr));
        dayTabWidget->setTabText(dayTabWidget->indexOf(tab_6), QCoreApplication::translate("MainWindow", "\355\231\224\354\232\224\354\235\274", nullptr));
        dayTabWidget->setTabText(dayTabWidget->indexOf(tab_7), QCoreApplication::translate("MainWindow", "\354\210\230\354\232\224\354\235\274", nullptr));
        dayTabWidget->setTabText(dayTabWidget->indexOf(tab_8), QCoreApplication::translate("MainWindow", "\353\252\251\354\232\224\354\235\274", nullptr));
        dayTabWidget->setTabText(dayTabWidget->indexOf(tab_9), QCoreApplication::translate("MainWindow", "\352\270\210\354\232\224\354\235\274", nullptr));
        dayTabWidget->setTabText(dayTabWidget->indexOf(tab_10), QCoreApplication::translate("MainWindow", "\355\206\240\354\232\224\354\235\274", nullptr));
        dayTabWidget->setTabText(dayTabWidget->indexOf(tab_11), QCoreApplication::translate("MainWindow", "\354\235\274\354\232\224\354\235\274", nullptr));
        mainTabWidget->setTabText(mainTabWidget->indexOf(dayTab), QCoreApplication::translate("MainWindow", "\354\232\224\354\235\274\353\263\204 \354\233\271\355\210\260", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "\354\240\234\353\252\251", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "\354\236\221\352\260\200", nullptr));

        label->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "\352\262\200\354\203\211", nullptr));
        mainTabWidget->setTabText(mainTabWidget->indexOf(searchTab), QCoreApplication::translate("MainWindow", "\354\233\271\355\210\260 \352\262\200\354\203\211", nullptr));
        mainTabWidget->setTabText(mainTabWidget->indexOf(bookMarkTab), QCoreApplication::translate("MainWindow", "\354\233\271\355\210\260 \354\246\220\352\262\250\354\260\276\352\270\260", nullptr));
        pushButton_sendMessage->setText(QCoreApplication::translate("MainWindow", "Send Message", nullptr));
        pushButton_sendAttachment->setText(QCoreApplication::translate("MainWindow", "Send Attachment", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
