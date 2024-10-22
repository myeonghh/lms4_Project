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
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *title_label;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *logout_btn;
    QStackedWidget *mainStackedWidget;
    QWidget *user_main_page;
    QGridLayout *gridLayout_3;
    QTabWidget *user_mainTabWidget;
    QWidget *foodCategoryTab;
    QGridLayout *gridLayout_4;
    QFrame *frame_6;
    QGridLayout *gridLayout_9;
    QPushButton *chicken_btn;
    QFrame *frame_7;
    QGridLayout *gridLayout_10;
    QPushButton *pizza_btn;
    QFrame *frame_8;
    QGridLayout *gridLayout_11;
    QPushButton *kFood_btn;
    QFrame *frame_9;
    QGridLayout *gridLayout_12;
    QPushButton *jFood_btn;
    QFrame *frame_10;
    QGridLayout *gridLayout_13;
    QPushButton *cFood_btn;
    QFrame *frame_11;
    QGridLayout *gridLayout_14;
    QPushButton *cafe_btn;
    QWidget *shopSearchTab;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *shopSearchText;
    QPushButton *shopSearchButton;
    QSpacerItem *horizontalSpacer;
    QTableView *searchTableView;
    QWidget *orderStateTab;
    QGridLayout *gridLayout_6;
    QTableView *b_tableView;
    QWidget *shopBookmarkTab;
    QGridLayout *gridLayout_5;
    QTableView *tableView;
    QWidget *shopList_page;
    QVBoxLayout *verticalLayout_6;
    QTableView *shopList_tableView;
    QFrame *frame_12;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_6;
    QWidget *menuList_page;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame;
    QVBoxLayout *verticalLayout_5;
    QLabel *menu_shopTitle;
    QTableView *menu_tableView;
    QTableView *basket_tableView;
    QFrame *frame_2;
    QGridLayout *gridLayout_15;
    QPushButton *toshop_backBtn;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *oder_btn;
    QWidget *shop_main_page;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *shopTabWidget;
    QWidget *shop_orderWait_tab;
    QGridLayout *gridLayout;
    QTableView *orderWait_tableView;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *total_sales_text;
    QPushButton *order_accept_btn;
    QPushButton *order_deny_btn;
    QWidget *shop_orderAccept_tab;
    QGridLayout *gridLayout_7;
    QTableView *orderAccept_tableView;
    QWidget *rider_main_page;
    QGridLayout *gridLayout_8;
    QFrame *frame_5;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QTableView *deliWait_tableView;
    QTableView *deliAccept_tableView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(899, 712);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName("gridLayout_2");
        frame_3 = new QFrame(centralWidget);
        frame_3->setObjectName("frame_3");
        frame_3->setMinimumSize(QSize(0, 50));
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_3);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        title_label = new QLabel(frame_3);
        title_label->setObjectName("title_label");
        title_label->setMinimumSize(QSize(500, 0));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        title_label->setFont(font);
        title_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(title_label);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        logout_btn = new QPushButton(frame_3);
        logout_btn->setObjectName("logout_btn");

        horizontalLayout_2->addWidget(logout_btn);


        gridLayout_2->addWidget(frame_3, 0, 0, 1, 1);

        mainStackedWidget = new QStackedWidget(centralWidget);
        mainStackedWidget->setObjectName("mainStackedWidget");
        user_main_page = new QWidget();
        user_main_page->setObjectName("user_main_page");
        gridLayout_3 = new QGridLayout(user_main_page);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName("gridLayout_3");
        user_mainTabWidget = new QTabWidget(user_main_page);
        user_mainTabWidget->setObjectName("user_mainTabWidget");
        user_mainTabWidget->setStyleSheet(QString::fromUtf8("#mainTabWidget QTabWidget::pane {\n"
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
"    min-height: 24px;  \n"
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
        foodCategoryTab = new QWidget();
        foodCategoryTab->setObjectName("foodCategoryTab");
        gridLayout_4 = new QGridLayout(foodCategoryTab);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName("gridLayout_4");
        frame_6 = new QFrame(foodCategoryTab);
        frame_6->setObjectName("frame_6");
        frame_6->setFrameShape(QFrame::Shape::StyledPanel);
        frame_6->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_9 = new QGridLayout(frame_6);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName("gridLayout_9");
        chicken_btn = new QPushButton(frame_6);
        chicken_btn->setObjectName("chicken_btn");

        gridLayout_9->addWidget(chicken_btn, 0, 0, 1, 1);


        gridLayout_4->addWidget(frame_6, 0, 0, 1, 1);

        frame_7 = new QFrame(foodCategoryTab);
        frame_7->setObjectName("frame_7");
        frame_7->setFrameShape(QFrame::Shape::StyledPanel);
        frame_7->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_10 = new QGridLayout(frame_7);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName("gridLayout_10");
        pizza_btn = new QPushButton(frame_7);
        pizza_btn->setObjectName("pizza_btn");

        gridLayout_10->addWidget(pizza_btn, 0, 0, 1, 1);


        gridLayout_4->addWidget(frame_7, 0, 1, 1, 1);

        frame_8 = new QFrame(foodCategoryTab);
        frame_8->setObjectName("frame_8");
        frame_8->setFrameShape(QFrame::Shape::StyledPanel);
        frame_8->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_11 = new QGridLayout(frame_8);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName("gridLayout_11");
        kFood_btn = new QPushButton(frame_8);
        kFood_btn->setObjectName("kFood_btn");

        gridLayout_11->addWidget(kFood_btn, 0, 0, 1, 1);


        gridLayout_4->addWidget(frame_8, 0, 2, 1, 1);

        frame_9 = new QFrame(foodCategoryTab);
        frame_9->setObjectName("frame_9");
        frame_9->setFrameShape(QFrame::Shape::StyledPanel);
        frame_9->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_12 = new QGridLayout(frame_9);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName("gridLayout_12");
        jFood_btn = new QPushButton(frame_9);
        jFood_btn->setObjectName("jFood_btn");

        gridLayout_12->addWidget(jFood_btn, 0, 0, 1, 1);


        gridLayout_4->addWidget(frame_9, 1, 0, 1, 1);

        frame_10 = new QFrame(foodCategoryTab);
        frame_10->setObjectName("frame_10");
        frame_10->setFrameShape(QFrame::Shape::StyledPanel);
        frame_10->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_13 = new QGridLayout(frame_10);
        gridLayout_13->setSpacing(6);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName("gridLayout_13");
        cFood_btn = new QPushButton(frame_10);
        cFood_btn->setObjectName("cFood_btn");

        gridLayout_13->addWidget(cFood_btn, 0, 0, 1, 1);


        gridLayout_4->addWidget(frame_10, 1, 1, 1, 1);

        frame_11 = new QFrame(foodCategoryTab);
        frame_11->setObjectName("frame_11");
        frame_11->setFrameShape(QFrame::Shape::StyledPanel);
        frame_11->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_14 = new QGridLayout(frame_11);
        gridLayout_14->setSpacing(6);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName("gridLayout_14");
        cafe_btn = new QPushButton(frame_11);
        cafe_btn->setObjectName("cafe_btn");

        gridLayout_14->addWidget(cafe_btn, 0, 0, 1, 1);


        gridLayout_4->addWidget(frame_11, 1, 2, 1, 1);

        user_mainTabWidget->addTab(foodCategoryTab, QString());
        shopSearchTab = new QWidget();
        shopSearchTab->setObjectName("shopSearchTab");
        verticalLayout = new QVBoxLayout(shopSearchTab);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        label_2 = new QLabel(shopSearchTab);
        label_2->setObjectName("label_2");
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        label_2->setFont(font1);

        horizontalLayout->addWidget(label_2);

        shopSearchText = new QLineEdit(shopSearchTab);
        shopSearchText->setObjectName("shopSearchText");

        horizontalLayout->addWidget(shopSearchText);

        shopSearchButton = new QPushButton(shopSearchTab);
        shopSearchButton->setObjectName("shopSearchButton");

        horizontalLayout->addWidget(shopSearchButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        searchTableView = new QTableView(shopSearchTab);
        searchTableView->setObjectName("searchTableView");
        searchTableView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

        verticalLayout->addWidget(searchTableView);

        user_mainTabWidget->addTab(shopSearchTab, QString());
        orderStateTab = new QWidget();
        orderStateTab->setObjectName("orderStateTab");
        gridLayout_6 = new QGridLayout(orderStateTab);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName("gridLayout_6");
        b_tableView = new QTableView(orderStateTab);
        b_tableView->setObjectName("b_tableView");
        b_tableView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

        gridLayout_6->addWidget(b_tableView, 0, 0, 1, 1);

        user_mainTabWidget->addTab(orderStateTab, QString());
        shopBookmarkTab = new QWidget();
        shopBookmarkTab->setObjectName("shopBookmarkTab");
        shopBookmarkTab->setEnabled(true);
        gridLayout_5 = new QGridLayout(shopBookmarkTab);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName("gridLayout_5");
        tableView = new QTableView(shopBookmarkTab);
        tableView->setObjectName("tableView");

        gridLayout_5->addWidget(tableView, 0, 0, 1, 1);

        user_mainTabWidget->addTab(shopBookmarkTab, QString());

        gridLayout_3->addWidget(user_mainTabWidget, 0, 0, 1, 1);

        mainStackedWidget->addWidget(user_main_page);
        shopList_page = new QWidget();
        shopList_page->setObjectName("shopList_page");
        verticalLayout_6 = new QVBoxLayout(shopList_page);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName("verticalLayout_6");
        shopList_tableView = new QTableView(shopList_page);
        shopList_tableView->setObjectName("shopList_tableView");

        verticalLayout_6->addWidget(shopList_tableView);

        frame_12 = new QFrame(shopList_page);
        frame_12->setObjectName("frame_12");
        frame_12->setFrameShape(QFrame::Shape::StyledPanel);
        frame_12->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_12);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        pushButton = new QPushButton(frame_12);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(200, 0));
        pushButton->setSizeIncrement(QSize(0, 0));
        QFont font2;
        font2.setPointSize(13);
        pushButton->setFont(font2);

        horizontalLayout_4->addWidget(pushButton);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);


        verticalLayout_6->addWidget(frame_12);

        mainStackedWidget->addWidget(shopList_page);
        menuList_page = new QWidget();
        menuList_page->setObjectName("menuList_page");
        verticalLayout_3 = new QVBoxLayout(menuList_page);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        frame = new QFrame(menuList_page);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_5 = new QVBoxLayout(frame);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName("verticalLayout_5");
        menu_shopTitle = new QLabel(frame);
        menu_shopTitle->setObjectName("menu_shopTitle");
        QFont font3;
        font3.setPointSize(15);
        font3.setBold(true);
        menu_shopTitle->setFont(font3);
        menu_shopTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_5->addWidget(menu_shopTitle);

        menu_tableView = new QTableView(frame);
        menu_tableView->setObjectName("menu_tableView");
        menu_tableView->setMinimumSize(QSize(0, 300));

        verticalLayout_5->addWidget(menu_tableView);

        basket_tableView = new QTableView(frame);
        basket_tableView->setObjectName("basket_tableView");

        verticalLayout_5->addWidget(basket_tableView);


        verticalLayout_3->addWidget(frame);

        frame_2 = new QFrame(menuList_page);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_15 = new QGridLayout(frame_2);
        gridLayout_15->setSpacing(6);
        gridLayout_15->setContentsMargins(11, 11, 11, 11);
        gridLayout_15->setObjectName("gridLayout_15");
        toshop_backBtn = new QPushButton(frame_2);
        toshop_backBtn->setObjectName("toshop_backBtn");
        toshop_backBtn->setMinimumSize(QSize(120, 0));
        QFont font4;
        font4.setPointSize(12);
        toshop_backBtn->setFont(font4);

        gridLayout_15->addWidget(toshop_backBtn, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_15->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_15->addItem(horizontalSpacer_3, 0, 3, 1, 1);

        oder_btn = new QPushButton(frame_2);
        oder_btn->setObjectName("oder_btn");
        oder_btn->setMinimumSize(QSize(120, 0));
        oder_btn->setFont(font4);

        gridLayout_15->addWidget(oder_btn, 0, 2, 1, 1);


        verticalLayout_3->addWidget(frame_2);

        mainStackedWidget->addWidget(menuList_page);
        shop_main_page = new QWidget();
        shop_main_page->setObjectName("shop_main_page");
        verticalLayout_2 = new QVBoxLayout(shop_main_page);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        shopTabWidget = new QTabWidget(shop_main_page);
        shopTabWidget->setObjectName("shopTabWidget");
        shopTabWidget->setStyleSheet(QString::fromUtf8("#shopTabWidget QTabWidget::pane {\n"
"    background-color: white;\n"
"    border: 2px solid black;\n"
"	border-radius:8px\n"
"}\n"
"\n"
"#shopTabWidget QTabBar::tab {\n"
"    background: white;\n"
"    border: 3px solid black;\n"
"    border-radius: 8px; \n"
"    padding: 10px;\n"
"	margin-right: 10px;\n"
"	margin-bottom: 5px;\n"
"	min-width: 100px;  \n"
"    min-height: 24px;  \n"
"	color: black;\n"
"	font-size: 16px;\n"
"}\n"
"\n"
"#shopTabWidget QTabBar::tab:selected {\n"
"    background: gray;\n"
"	color: white;\n"
"	font-weight: bold;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QTabWidget::tab-bar {  /* \355\203\255 \353\262\204\355\212\274\354\235\204 \352\260\220\354\213\270\353\212\224 \353\260\224 */\n"
"    left: 20px;  /* \355\203\255 \353\252\251\353\241\235\354\235\264 \354\231\274\354\252\275\354\234\274\353\241\234 \354\241\260\352\270\210 \354\235\264\353\217\231 */\n"
"}"));
        shop_orderWait_tab = new QWidget();
        shop_orderWait_tab->setObjectName("shop_orderWait_tab");
        gridLayout = new QGridLayout(shop_orderWait_tab);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        orderWait_tableView = new QTableView(shop_orderWait_tab);
        orderWait_tableView->setObjectName("orderWait_tableView");

        gridLayout->addWidget(orderWait_tableView, 0, 0, 1, 1);

        frame_4 = new QFrame(shop_orderWait_tab);
        frame_4->setObjectName("frame_4");
        frame_4->setMinimumSize(QSize(0, 60));
        frame_4->setSizeIncrement(QSize(0, 0));
        frame_4->setFrameShape(QFrame::Shape::StyledPanel);
        frame_4->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_4);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        total_sales_text = new QLabel(frame_4);
        total_sales_text->setObjectName("total_sales_text");

        horizontalLayout_3->addWidget(total_sales_text);

        order_accept_btn = new QPushButton(frame_4);
        order_accept_btn->setObjectName("order_accept_btn");
        order_accept_btn->setFont(font4);

        horizontalLayout_3->addWidget(order_accept_btn);

        order_deny_btn = new QPushButton(frame_4);
        order_deny_btn->setObjectName("order_deny_btn");
        order_deny_btn->setFont(font4);

        horizontalLayout_3->addWidget(order_deny_btn);


        gridLayout->addWidget(frame_4, 1, 0, 1, 1);

        shopTabWidget->addTab(shop_orderWait_tab, QString());
        shop_orderAccept_tab = new QWidget();
        shop_orderAccept_tab->setObjectName("shop_orderAccept_tab");
        gridLayout_7 = new QGridLayout(shop_orderAccept_tab);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName("gridLayout_7");
        orderAccept_tableView = new QTableView(shop_orderAccept_tab);
        orderAccept_tableView->setObjectName("orderAccept_tableView");

        gridLayout_7->addWidget(orderAccept_tableView, 0, 0, 1, 1);

        shopTabWidget->addTab(shop_orderAccept_tab, QString());

        verticalLayout_2->addWidget(shopTabWidget);

        mainStackedWidget->addWidget(shop_main_page);
        rider_main_page = new QWidget();
        rider_main_page->setObjectName("rider_main_page");
        gridLayout_8 = new QGridLayout(rider_main_page);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName("gridLayout_8");
        frame_5 = new QFrame(rider_main_page);
        frame_5->setObjectName("frame_5");
        frame_5->setFrameShape(QFrame::Shape::StyledPanel);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_4 = new QVBoxLayout(frame_5);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName("verticalLayout_4");
        label = new QLabel(frame_5);
        label->setObjectName("label");
        QFont font5;
        font5.setPointSize(13);
        font5.setBold(false);
        label->setFont(font5);

        verticalLayout_4->addWidget(label);

        deliWait_tableView = new QTableView(frame_5);
        deliWait_tableView->setObjectName("deliWait_tableView");
        deliWait_tableView->setMinimumSize(QSize(0, 350));

        verticalLayout_4->addWidget(deliWait_tableView);

        deliAccept_tableView = new QTableView(frame_5);
        deliAccept_tableView->setObjectName("deliAccept_tableView");

        verticalLayout_4->addWidget(deliAccept_tableView);


        gridLayout_8->addWidget(frame_5, 0, 0, 1, 1);

        mainStackedWidget->addWidget(rider_main_page);

        gridLayout_2->addWidget(mainStackedWidget, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 899, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(shopSearchText, &QLineEdit::returnPressed, shopSearchButton, qOverload<>(&QPushButton::click));

        mainStackedWidget->setCurrentIndex(3);
        user_mainTabWidget->setCurrentIndex(0);
        shopTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "QTCPClient", nullptr));
        title_label->setText(QCoreApplication::translate("MainWindow", "\354\240\200\352\270\260\354\232\224", nullptr));
        logout_btn->setText(QCoreApplication::translate("MainWindow", "\353\241\234\352\267\270\354\225\204\354\233\203", nullptr));
        chicken_btn->setText(QCoreApplication::translate("MainWindow", "\354\271\230\355\202\250", nullptr));
        pizza_btn->setText(QCoreApplication::translate("MainWindow", "\355\224\274\354\236\220", nullptr));
        kFood_btn->setText(QCoreApplication::translate("MainWindow", "\355\225\234\354\213\235", nullptr));
        jFood_btn->setText(QCoreApplication::translate("MainWindow", "\354\235\274\354\213\235", nullptr));
        cFood_btn->setText(QCoreApplication::translate("MainWindow", "\354\244\221\352\265\255\354\247\221", nullptr));
        cafe_btn->setText(QCoreApplication::translate("MainWindow", "\354\271\264\355\216\230", nullptr));
        user_mainTabWidget->setTabText(user_mainTabWidget->indexOf(foodCategoryTab), QCoreApplication::translate("MainWindow", "\354\235\214\354\213\235 \354\271\264\355\205\214\352\263\240\353\246\254 \353\252\251\353\241\235", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\352\260\200\352\262\214 \354\235\264\353\246\204", nullptr));
        shopSearchButton->setText(QCoreApplication::translate("MainWindow", "\352\262\200\354\203\211", nullptr));
        user_mainTabWidget->setTabText(user_mainTabWidget->indexOf(shopSearchTab), QCoreApplication::translate("MainWindow", "\352\260\200\352\262\214 \352\262\200\354\203\211", nullptr));
        user_mainTabWidget->setTabText(user_mainTabWidget->indexOf(orderStateTab), QCoreApplication::translate("MainWindow", "\354\243\274\353\254\270 \355\230\204\355\231\251", nullptr));
        user_mainTabWidget->setTabText(user_mainTabWidget->indexOf(shopBookmarkTab), QCoreApplication::translate("MainWindow", "\352\260\200\352\262\214 \354\246\220\352\262\250\354\260\276\352\270\260", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\353\222\244\353\241\234 \352\260\200\352\270\260", nullptr));
        menu_shopTitle->setText(QCoreApplication::translate("MainWindow", "\352\260\200\352\262\214 \354\235\264\353\246\204", nullptr));
        toshop_backBtn->setText(QCoreApplication::translate("MainWindow", "\353\222\244\353\241\234 \352\260\200\352\270\260", nullptr));
        oder_btn->setText(QCoreApplication::translate("MainWindow", "\354\243\274\353\254\270 \355\225\230\352\270\260", nullptr));
        total_sales_text->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        order_accept_btn->setText(QCoreApplication::translate("MainWindow", "\354\243\274\353\254\270 \354\212\271\353\202\231", nullptr));
        order_deny_btn->setText(QCoreApplication::translate("MainWindow", "\354\243\274\353\254\270 \352\261\260\354\240\210", nullptr));
        shopTabWidget->setTabText(shopTabWidget->indexOf(shop_orderWait_tab), QCoreApplication::translate("MainWindow", "\354\243\274\353\254\270 \353\252\251\353\241\235", nullptr));
        shopTabWidget->setTabText(shopTabWidget->indexOf(shop_orderAccept_tab), QCoreApplication::translate("MainWindow", "\353\260\260\353\213\254 \355\230\204\355\231\251", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "  \354\243\274\353\254\270 \353\252\251\353\241\235", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
