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
#include <QtWidgets/QScrollArea>
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
    QWidget *main_page;
    QGridLayout *gridLayout_3;
    QTabWidget *mainTabWidget;
    QWidget *entireListTab;
    QGridLayout *gridLayout_4;
    QTableView *e_tableView;
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
    QComboBox *searchComboBox;
    QLabel *label;
    QLineEdit *toonSearchText;
    QPushButton *searchButton;
    QSpacerItem *horizontalSpacer;
    QTableView *searchTableView;
    QWidget *bookMarkTab;
    QGridLayout *gridLayout_6;
    QTableView *b_tableView;
    QWidget *toonList_page;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame;
    QGridLayout *gridLayout_14;
    QTableView *epiList_tableView;
    QFrame *frame_2;
    QGridLayout *gridLayout_15;
    QPushButton *toList_backBtn;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QWidget *webtoon_page;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout_16;
    QScrollArea *toon_scrollArea;
    QWidget *toon_scrollArea_contents;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout_17;
    QPushButton *beforeEpi_btn;
    QPushButton *backList_btn;
    QPushButton *afterEpi_btn;
    QPushButton *bookmark_add_btn;
    QPushButton *like_btn;
    QPushButton *pushButton;
    QWidget *page_2;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_sendMessage;
    QPushButton *pushButton_sendAttachment;
    QLineEdit *lineEdit_message;
    QTextBrowser *textBrowser_receivedMessages;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *logout_btn;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(895, 701);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName("gridLayout_2");
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName("stackedWidget");
        main_page = new QWidget();
        main_page->setObjectName("main_page");
        gridLayout_3 = new QGridLayout(main_page);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName("gridLayout_3");
        mainTabWidget = new QTabWidget(main_page);
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

        mainTabWidget->addTab(entireListTab, QString());
        dayTab = new QWidget();
        dayTab->setObjectName("dayTab");
        dayTab->setEnabled(true);
        gridLayout_5 = new QGridLayout(dayTab);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName("gridLayout_5");
        dayTabWidget = new QTabWidget(dayTab);
        dayTabWidget->setObjectName("dayTabWidget");
        dayTabWidget->setEnabled(true);
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
"    left: 20px;  /* \355\203\255 \353\252\251\353\241\235\354\235\264 \354\231\274\354\252\275\354\234\274\353\241\234 \354\241\260\352\270\210 \354\235\264\353\217\231 */\n"
"}"));
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        gridLayout_7 = new QGridLayout(tab_5);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName("gridLayout_7");
        tableView_mon = new QTableView(tab_5);
        tableView_mon->setObjectName("tableView_mon");
        tableView_mon->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

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
        tableView_tue->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

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
        tableView_wed->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

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
        tableView_thu->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

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
        tableView_fri->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

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
        tableView_sat->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

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
        tableView_sun->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

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
        searchComboBox = new QComboBox(searchTab);
        searchComboBox->addItem(QString());
        searchComboBox->addItem(QString());
        searchComboBox->setObjectName("searchComboBox");

        horizontalLayout->addWidget(searchComboBox);

        label = new QLabel(searchTab);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        toonSearchText = new QLineEdit(searchTab);
        toonSearchText->setObjectName("toonSearchText");

        horizontalLayout->addWidget(toonSearchText);

        searchButton = new QPushButton(searchTab);
        searchButton->setObjectName("searchButton");

        horizontalLayout->addWidget(searchButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        searchTableView = new QTableView(searchTab);
        searchTableView->setObjectName("searchTableView");
        searchTableView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

        verticalLayout->addWidget(searchTableView);

        mainTabWidget->addTab(searchTab, QString());
        bookMarkTab = new QWidget();
        bookMarkTab->setObjectName("bookMarkTab");
        gridLayout_6 = new QGridLayout(bookMarkTab);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName("gridLayout_6");
        b_tableView = new QTableView(bookMarkTab);
        b_tableView->setObjectName("b_tableView");
        b_tableView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

        gridLayout_6->addWidget(b_tableView, 0, 0, 1, 1);

        mainTabWidget->addTab(bookMarkTab, QString());

        gridLayout_3->addWidget(mainTabWidget, 0, 0, 1, 1);

        stackedWidget->addWidget(main_page);
        toonList_page = new QWidget();
        toonList_page->setObjectName("toonList_page");
        verticalLayout_3 = new QVBoxLayout(toonList_page);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        frame = new QFrame(toonList_page);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_14 = new QGridLayout(frame);
        gridLayout_14->setSpacing(6);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName("gridLayout_14");
        epiList_tableView = new QTableView(frame);
        epiList_tableView->setObjectName("epiList_tableView");

        gridLayout_14->addWidget(epiList_tableView, 0, 0, 1, 1);


        verticalLayout_3->addWidget(frame);

        frame_2 = new QFrame(toonList_page);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_15 = new QGridLayout(frame_2);
        gridLayout_15->setSpacing(6);
        gridLayout_15->setContentsMargins(11, 11, 11, 11);
        gridLayout_15->setObjectName("gridLayout_15");
        toList_backBtn = new QPushButton(frame_2);
        toList_backBtn->setObjectName("toList_backBtn");
        toList_backBtn->setMinimumSize(QSize(150, 0));

        gridLayout_15->addWidget(toList_backBtn, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_15->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_15->addItem(horizontalSpacer_3, 0, 2, 1, 1);


        verticalLayout_3->addWidget(frame_2);

        stackedWidget->addWidget(toonList_page);
        webtoon_page = new QWidget();
        webtoon_page->setObjectName("webtoon_page");
        verticalLayout_2 = new QVBoxLayout(webtoon_page);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        gridLayout_16 = new QGridLayout();
        gridLayout_16->setSpacing(6);
        gridLayout_16->setObjectName("gridLayout_16");
        toon_scrollArea = new QScrollArea(webtoon_page);
        toon_scrollArea->setObjectName("toon_scrollArea");
        toon_scrollArea->setWidgetResizable(true);
        toon_scrollArea_contents = new QWidget();
        toon_scrollArea_contents->setObjectName("toon_scrollArea_contents");
        toon_scrollArea_contents->setGeometry(QRect(0, 0, 762, 457));
        verticalLayout_4 = new QVBoxLayout(toon_scrollArea_contents);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName("verticalLayout_4");
        toon_scrollArea->setWidget(toon_scrollArea_contents);

        gridLayout_16->addWidget(toon_scrollArea, 0, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout_16);

        gridLayout_17 = new QGridLayout();
        gridLayout_17->setSpacing(6);
        gridLayout_17->setObjectName("gridLayout_17");
        beforeEpi_btn = new QPushButton(webtoon_page);
        beforeEpi_btn->setObjectName("beforeEpi_btn");

        gridLayout_17->addWidget(beforeEpi_btn, 0, 0, 1, 1);

        backList_btn = new QPushButton(webtoon_page);
        backList_btn->setObjectName("backList_btn");

        gridLayout_17->addWidget(backList_btn, 0, 1, 1, 1);

        afterEpi_btn = new QPushButton(webtoon_page);
        afterEpi_btn->setObjectName("afterEpi_btn");

        gridLayout_17->addWidget(afterEpi_btn, 0, 2, 1, 1);

        bookmark_add_btn = new QPushButton(webtoon_page);
        bookmark_add_btn->setObjectName("bookmark_add_btn");

        gridLayout_17->addWidget(bookmark_add_btn, 1, 2, 1, 1);

        like_btn = new QPushButton(webtoon_page);
        like_btn->setObjectName("like_btn");

        gridLayout_17->addWidget(like_btn, 1, 0, 1, 1);

        pushButton = new QPushButton(webtoon_page);
        pushButton->setObjectName("pushButton");

        gridLayout_17->addWidget(pushButton, 1, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout_17);

        stackedWidget->addWidget(webtoon_page);
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

        gridLayout_2->addWidget(stackedWidget, 3, 0, 1, 1);

        frame_3 = new QFrame(centralWidget);
        frame_3->setObjectName("frame_3");
        frame_3->setMinimumSize(QSize(0, 0));
        frame_3->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    border: none;\n"
"\n"
"}\n"
""));
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_3);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        logout_btn = new QPushButton(frame_3);
        logout_btn->setObjectName("logout_btn");
        logout_btn->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(logout_btn);


        gridLayout_2->addWidget(frame_3, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 895, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(toonSearchText, &QLineEdit::returnPressed, searchButton, qOverload<>(&QPushButton::click));

        stackedWidget->setCurrentIndex(0);
        mainTabWidget->setCurrentIndex(1);
        dayTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "QTCPClient", nullptr));
        mainTabWidget->setTabText(mainTabWidget->indexOf(entireListTab), QCoreApplication::translate("MainWindow", "\354\233\271\355\210\260 \354\240\204\354\262\264\353\252\251\353\241\235", nullptr));
        dayTabWidget->setTabText(dayTabWidget->indexOf(tab_5), QCoreApplication::translate("MainWindow", "\354\233\224\354\232\224\354\235\274", nullptr));
        dayTabWidget->setTabText(dayTabWidget->indexOf(tab_6), QCoreApplication::translate("MainWindow", "\355\231\224\354\232\224\354\235\274", nullptr));
        dayTabWidget->setTabText(dayTabWidget->indexOf(tab_7), QCoreApplication::translate("MainWindow", "\354\210\230\354\232\224\354\235\274", nullptr));
        dayTabWidget->setTabText(dayTabWidget->indexOf(tab_8), QCoreApplication::translate("MainWindow", "\353\252\251\354\232\224\354\235\274", nullptr));
        dayTabWidget->setTabText(dayTabWidget->indexOf(tab_9), QCoreApplication::translate("MainWindow", "\352\270\210\354\232\224\354\235\274", nullptr));
        dayTabWidget->setTabText(dayTabWidget->indexOf(tab_10), QCoreApplication::translate("MainWindow", "\355\206\240\354\232\224\354\235\274", nullptr));
        dayTabWidget->setTabText(dayTabWidget->indexOf(tab_11), QCoreApplication::translate("MainWindow", "\354\235\274\354\232\224\354\235\274", nullptr));
        mainTabWidget->setTabText(mainTabWidget->indexOf(dayTab), QCoreApplication::translate("MainWindow", "\354\232\224\354\235\274\353\263\204 \354\233\271\355\210\260", nullptr));
        searchComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "\354\240\234\353\252\251", nullptr));
        searchComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "\354\236\221\352\260\200", nullptr));

        label->setText(QString());
        searchButton->setText(QCoreApplication::translate("MainWindow", "\352\262\200\354\203\211", nullptr));
        mainTabWidget->setTabText(mainTabWidget->indexOf(searchTab), QCoreApplication::translate("MainWindow", "\354\233\271\355\210\260 \352\262\200\354\203\211", nullptr));
        mainTabWidget->setTabText(mainTabWidget->indexOf(bookMarkTab), QCoreApplication::translate("MainWindow", "\354\233\271\355\210\260 \354\246\220\352\262\250\354\260\276\352\270\260", nullptr));
        toList_backBtn->setText(QCoreApplication::translate("MainWindow", "\353\222\244\353\241\234 \352\260\200\352\270\260", nullptr));
        beforeEpi_btn->setText(QCoreApplication::translate("MainWindow", "<<\354\235\264\354\240\204\355\231\224", nullptr));
        backList_btn->setText(QCoreApplication::translate("MainWindow", "\353\252\251\353\241\235\354\234\274\353\241\234 \353\217\214\354\225\204\352\260\200\352\270\260", nullptr));
        afterEpi_btn->setText(QCoreApplication::translate("MainWindow", "\353\213\244\354\235\214\355\231\224>>", nullptr));
        bookmark_add_btn->setText(QCoreApplication::translate("MainWindow", "\354\246\220\352\262\250\354\260\276\352\270\260 \354\266\224\352\260\200", nullptr));
        like_btn->setText(QCoreApplication::translate("MainWindow", "\354\242\213\354\225\204\354\232\224", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\354\246\220\352\262\250\354\260\276\352\270\260 \353\252\251\353\241\235\354\234\274\353\241\234 \354\235\264\353\217\231", nullptr));
        pushButton_sendMessage->setText(QCoreApplication::translate("MainWindow", "Send Message", nullptr));
        pushButton_sendAttachment->setText(QCoreApplication::translate("MainWindow", "Send Attachment", nullptr));
        logout_btn->setText(QCoreApplication::translate("MainWindow", "\353\241\234\352\267\270\354\225\204\354\233\203", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
