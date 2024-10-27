/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
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
#include <QtWidgets/QToolButton>
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
    QFrame *frame_9;
    QGridLayout *gridLayout_12;
    QToolButton *jFood_btn;
    QFrame *frame_10;
    QGridLayout *gridLayout_13;
    QToolButton *cFood_btn;
    QFrame *frame_8;
    QGridLayout *gridLayout_11;
    QToolButton *kFood_btn;
    QFrame *frame_7;
    QGridLayout *gridLayout_10;
    QToolButton *pizza_btn;
    QFrame *frame_11;
    QGridLayout *gridLayout_14;
    QToolButton *cafe_btn;
    QFrame *frame_6;
    QGridLayout *gridLayout_9;
    QToolButton *chicken_btn;
    QWidget *shopSearchTab;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *shopSearchText;
    QPushButton *shopSearchButton;
    QSpacerItem *horizontalSpacer;
    QTableView *searchTableView;
    QWidget *shopBookmarkTab;
    QGridLayout *gridLayout_5;
    QTableView *bookmark_tableView;
    QWidget *orderStateTab;
    QGridLayout *gridLayout_6;
    QTableView *user_order_state_tableView;
    QWidget *user_order_history_tab;
    QGridLayout *gridLayout_20;
    QTableView *order_history_tableView;
    QWidget *shopList_page;
    QVBoxLayout *verticalLayout_6;
    QTableView *shopList_tableView;
    QFrame *frame_12;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *to_mainBtn;
    QSpacerItem *horizontalSpacer_6;
    QWidget *menuList_page;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame;
    QVBoxLayout *verticalLayout_5;
    QFrame *frame_5;
    QHBoxLayout *horizontalLayout_9;
    QLabel *menu_shopTitle;
    QPushButton *bookmark_btn;
    QFrame *frame_13;
    QGridLayout *gridLayout_16;
    QTableView *menu_basket_tableView;
    QTableView *menu_tableView;
    QLabel *label_3;
    QLabel *label_4;
    QFrame *frame_2;
    QGridLayout *gridLayout_15;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *toshop_backBtn;
    QPushButton *to_order_btn;
    QSpacerItem *horizontalSpacer_3;
    QWidget *pay_page;
    QGridLayout *gridLayout_17;
    QFrame *frame_14;
    QVBoxLayout *verticalLayout_7;
    QLabel *menu_shopTitle2;
    QTableView *pay_tableView;
    QFrame *frame_17;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_11;
    QLabel *label_8;
    QLabel *menu_price_label;
    QFrame *frame_15;
    QGridLayout *gridLayout_18;
    QLineEdit *del_address_text;
    QLineEdit *del_request_text;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_10;
    QFrame *frame_16;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *to_menu_back_btn;
    QPushButton *pay_btn;
    QSpacerItem *horizontalSpacer_8;
    QWidget *shop_main_page;
    QVBoxLayout *verticalLayout_2;
    QLabel *shop_title_text_label;
    QTabWidget *shopTabWidget;
    QWidget *shop_orderWait_tab;
    QGridLayout *gridLayout;
    QTableView *orderWait_tableView;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_12;
    QPushButton *order_accept_btn;
    QPushButton *order_deny_btn;
    QSpacerItem *horizontalSpacer_13;
    QWidget *shop_orderAccept_tab;
    QGridLayout *gridLayout_7;
    QTableView *orderAccept_tableView;
    QFrame *frame_18;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_14;
    QLabel *label_7;
    QLabel *total_sales_text;
    QWidget *rider_main_page;
    QGridLayout *gridLayout_8;
    QTabWidget *delTabWidget;
    QWidget *delivery_sate_tab;
    QVBoxLayout *verticalLayout_8;
    QLabel *label;
    QTableView *deliWait_tableView;
    QLabel *label_9;
    QTableView *deliAccept_tableView;
    QFrame *frame_19;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_15;
    QPushButton *del_complete_btn;
    QSpacerItem *horizontalSpacer_16;
    QWidget *del_history_tab;
    QGridLayout *gridLayout_19;
    QTableView *rider_history_tableView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(815, 696);
        MainWindow->setStyleSheet(QString::fromUtf8("/* QTableView */\n"
"QTableView {\n"
"    border: 1px solid #2c3e50; /* \355\205\214\353\221\220\353\246\254 \353\221\220\352\273\230 */\n"
"    gridline-color: #bdc3c7;      /* \354\205\200 \352\265\254\353\266\204\354\204\240 \354\203\211\354\203\201 */\n"
"    font-size: 13px;           /* \353\202\264\353\266\200 \355\205\215\354\212\244\355\212\270 \355\201\254\352\270\260 */\n"
"    font-family: \"Malgun Gothic\"; /* \353\202\264\353\266\200 \355\205\215\354\212\244\355\212\270 \355\217\260\355\212\270 */\n"
"}\n"
"\n"
"/* QHeaderView */\n"
"QHeaderView::section {\n"
"    background-color: #2ecc71; /* \355\227\244\353\215\224 \353\260\260\352\262\275\354\203\211\354\235\204 \354\227\260\355\225\234 \354\264\210\353\241\235\354\203\211\354\234\274\353\241\234 \353\263\200\352\262\275 */\n"
"    color: white;              /* \355\227\244\353\215\224 \352\270\200\354\236\220 \354\203\211\354\203\201 */\n"
"    font-size: 15px;           /* \355\227\244\353\215\224 \352\270\200\354\236\220 \355\201\254\352\270"
                        "\260 */\n"
"    font-weight: bold;         /* \355\227\244\353\215\224 \352\270\200\354\236\220 \352\265\265\352\270\260 */\n"
"    padding: 4px;\n"
"    border: 1px solid #27ae60; /* \355\227\244\353\215\224 \355\205\214\353\221\220\353\246\254\353\245\274 \354\241\260\352\270\210 \353\215\224 \354\247\204\355\225\234 \354\264\210\353\241\235\354\203\211\354\234\274\353\241\234 */\n"
"    font-family: \"Malgun Gothic\";\n"
"}\n"
"\n"
"/* QPushButton */\n"
"QPushButton {\n"
"    background-color: #2ecc71; /* \353\262\204\355\212\274 \353\260\260\352\262\275\354\235\204 \354\227\260\355\225\234 \354\264\210\353\241\235\354\203\211\354\234\274\353\241\234 */\n"
"    color: white;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"    border-radius: 5px;\n"
"    padding: 5px 10px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #27ae60; /* \353\247\210\354\232\260\354\212\244 \354\230\244\353\262\204 \354\213\234 \354\247\204\355\225\234 \354\264\210\353\241\235\354\203\211\354\234\274\353\241\234"
                        " */\n"
"}\n"
"\n"
"/* QMessageBox */\n"
"QMessageBox {\n"
"    background-color: #ffffff;        /* \353\260\260\352\262\275 \354\203\211\354\203\201\354\235\204 \355\235\260\354\203\211\354\234\274\353\241\234 \354\204\244\354\240\225 */\n"
"    border: 2px solid #27ae60;        /* \354\264\210\353\241\235\354\203\211 \355\205\214\353\221\220\353\246\254 */\n"
"    border-radius: 10px;              /* \353\221\245\352\267\274 \353\252\250\354\204\234\353\246\254 */\n"
"    padding: 10px;                    /* \353\202\264\353\266\200 \354\227\254\353\260\261 */\n"
"}\n"
"\n"
"/* QMessageBox \355\205\215\354\212\244\355\212\270 */\n"
"QMessageBox QLabel {\n"
"    color: #000000;                   /* \355\205\215\354\212\244\355\212\270 \354\203\211\354\203\201 (\352\262\200\354\240\225) */\n"
"    font-family: \"\353\247\221\354\235\200 \352\263\240\353\224\225\";          /* \355\217\260\355\212\270 \354\204\244\354\240\225 */\n"
"    font-size: 14pt;                  /* \355\205\215\354\212\244\355\212\270 \355"
                        "\201\254\352\270\260 */\n"
"    font-weight: bold;                /* \352\265\265\354\235\200 \355\205\215\354\212\244\355\212\270 */\n"
"    margin-bottom: 10px;              /* \353\251\224\354\213\234\354\247\200\354\231\200 \353\262\204\355\212\274 \354\202\254\354\235\264 \354\227\254\353\260\261 */\n"
"}\n"
"\n"
"/* QMessageBox \353\262\204\355\212\274 */\n"
"QMessageBox QPushButton {\n"
"    background-color: #27ae60;        /* \353\262\204\355\212\274 \353\260\260\352\262\275\354\235\204 \354\247\204\355\225\234 \354\264\210\353\241\235\354\203\211\354\234\274\353\241\234 */\n"
"    color: white;                     /* \353\262\204\355\212\274 \355\205\215\354\212\244\355\212\270 \354\203\211\354\203\201 */\n"
"    font-family: \"\353\247\221\354\235\200 \352\263\240\353\224\225\";          /* \353\262\204\355\212\274 \355\217\260\355\212\270 \354\204\244\354\240\225 */\n"
"    font-size: 12pt;                  /* \355\205\215\354\212\244\355\212\270 \355\201\254\352\270\260 */\n"
"    border-radius: 5"
                        "px;               /* \353\262\204\355\212\274 \353\252\250\354\204\234\353\246\254 \353\221\245\352\270\200\352\262\214 */\n"
"    padding: 5px 15px;                /* \353\262\204\355\212\274 \353\202\264\353\266\200 \354\227\254\353\260\261 */\n"
"    margin: 5px;                      /* \353\262\204\355\212\274 \354\231\270\353\266\200 \354\227\254\353\260\261 */\n"
"}\n"
"\n"
"QMessageBox QPushButton:hover {\n"
"    background-color: #2ecc71;        /* \353\247\210\354\232\260\354\212\244 \354\230\244\353\262\204 \354\213\234 \354\227\260\355\225\234 \354\264\210\353\241\235\354\203\211\354\234\274\353\241\234 */\n"
"}\n"
"\n"
"QMessageBox QPushButton:pressed {\n"
"    background-color: #1e8449;        /* \355\201\264\353\246\255 \354\213\234 \353\215\224 \354\247\204\355\225\234 \354\264\210\353\241\235\354\203\211 */\n"
"}"));
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
        logout_btn->setMinimumSize(QSize(80, 26));
        QFont font1;
        font1.setBold(true);
        logout_btn->setFont(font1);

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
        user_mainTabWidget->setStyleSheet(QString::fromUtf8("#user_mainTabWidget QTabWidget::pane {\n"
"    background-color: white;\n"
"    border: 2px solid black;\n"
"	border-radius:8px\n"
"}\n"
"\n"
"#user_mainTabWidget QTabBar::tab {\n"
"    background: white;\n"
"    border: 3px solid black;\n"
"    border-radius: 8px; \n"
"    padding: 10px;\n"
"	margin-right: 10px;\n"
"	margin-bottom: 5px;\n"
"	min-width: 100px;  \n"
"    min-height: 24px;  \n"
"	color: black;\n"
"	font-size: 14px;\n"
"}\n"
"\n"
"#user_mainTabWidget QTabBar::tab:selected {\n"
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
        frame_9 = new QFrame(foodCategoryTab);
        frame_9->setObjectName("frame_9");
        frame_9->setFrameShape(QFrame::Shape::StyledPanel);
        frame_9->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_12 = new QGridLayout(frame_9);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName("gridLayout_12");
        jFood_btn = new QToolButton(frame_9);
        jFood_btn->setObjectName("jFood_btn");
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        jFood_btn->setFont(font2);

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
        cFood_btn = new QToolButton(frame_10);
        cFood_btn->setObjectName("cFood_btn");
        cFood_btn->setFont(font2);

        gridLayout_13->addWidget(cFood_btn, 0, 0, 1, 1);


        gridLayout_4->addWidget(frame_10, 1, 1, 1, 1);

        frame_8 = new QFrame(foodCategoryTab);
        frame_8->setObjectName("frame_8");
        frame_8->setFrameShape(QFrame::Shape::StyledPanel);
        frame_8->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_11 = new QGridLayout(frame_8);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName("gridLayout_11");
        kFood_btn = new QToolButton(frame_8);
        kFood_btn->setObjectName("kFood_btn");
        kFood_btn->setFont(font2);

        gridLayout_11->addWidget(kFood_btn, 0, 0, 1, 1);


        gridLayout_4->addWidget(frame_8, 0, 2, 1, 1);

        frame_7 = new QFrame(foodCategoryTab);
        frame_7->setObjectName("frame_7");
        frame_7->setFrameShape(QFrame::Shape::StyledPanel);
        frame_7->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_10 = new QGridLayout(frame_7);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName("gridLayout_10");
        pizza_btn = new QToolButton(frame_7);
        pizza_btn->setObjectName("pizza_btn");
        pizza_btn->setFont(font2);

        gridLayout_10->addWidget(pizza_btn, 0, 0, 1, 1);


        gridLayout_4->addWidget(frame_7, 0, 1, 1, 1);

        frame_11 = new QFrame(foodCategoryTab);
        frame_11->setObjectName("frame_11");
        frame_11->setFrameShape(QFrame::Shape::StyledPanel);
        frame_11->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_14 = new QGridLayout(frame_11);
        gridLayout_14->setSpacing(6);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName("gridLayout_14");
        cafe_btn = new QToolButton(frame_11);
        cafe_btn->setObjectName("cafe_btn");
        cafe_btn->setFont(font2);

        gridLayout_14->addWidget(cafe_btn, 0, 0, 1, 1);


        gridLayout_4->addWidget(frame_11, 1, 2, 1, 1);

        frame_6 = new QFrame(foodCategoryTab);
        frame_6->setObjectName("frame_6");
        frame_6->setFrameShape(QFrame::Shape::StyledPanel);
        frame_6->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_9 = new QGridLayout(frame_6);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName("gridLayout_9");
        chicken_btn = new QToolButton(frame_6);
        chicken_btn->setObjectName("chicken_btn");
        QFont font3;
        font3.setFamilies({QString::fromUtf8("\353\247\221\354\235\200 \352\263\240\353\224\225")});
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setItalic(false);
        font3.setStrikeOut(false);
        chicken_btn->setFont(font3);

        gridLayout_9->addWidget(chicken_btn, 0, 0, 1, 1);


        gridLayout_4->addWidget(frame_6, 0, 0, 1, 1);

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
        label_2->setFont(font2);

        horizontalLayout->addWidget(label_2);

        shopSearchText = new QLineEdit(shopSearchTab);
        shopSearchText->setObjectName("shopSearchText");
        QFont font4;
        font4.setPointSize(12);
        shopSearchText->setFont(font4);

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
        shopBookmarkTab = new QWidget();
        shopBookmarkTab->setObjectName("shopBookmarkTab");
        shopBookmarkTab->setEnabled(true);
        gridLayout_5 = new QGridLayout(shopBookmarkTab);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName("gridLayout_5");
        bookmark_tableView = new QTableView(shopBookmarkTab);
        bookmark_tableView->setObjectName("bookmark_tableView");
        bookmark_tableView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

        gridLayout_5->addWidget(bookmark_tableView, 0, 0, 1, 1);

        user_mainTabWidget->addTab(shopBookmarkTab, QString());
        orderStateTab = new QWidget();
        orderStateTab->setObjectName("orderStateTab");
        gridLayout_6 = new QGridLayout(orderStateTab);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName("gridLayout_6");
        user_order_state_tableView = new QTableView(orderStateTab);
        user_order_state_tableView->setObjectName("user_order_state_tableView");
        user_order_state_tableView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

        gridLayout_6->addWidget(user_order_state_tableView, 0, 0, 1, 1);

        user_mainTabWidget->addTab(orderStateTab, QString());
        user_order_history_tab = new QWidget();
        user_order_history_tab->setObjectName("user_order_history_tab");
        gridLayout_20 = new QGridLayout(user_order_history_tab);
        gridLayout_20->setSpacing(6);
        gridLayout_20->setContentsMargins(11, 11, 11, 11);
        gridLayout_20->setObjectName("gridLayout_20");
        order_history_tableView = new QTableView(user_order_history_tab);
        order_history_tableView->setObjectName("order_history_tableView");

        gridLayout_20->addWidget(order_history_tableView, 0, 0, 1, 1);

        user_mainTabWidget->addTab(user_order_history_tab, QString());

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
        shopList_tableView->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustIgnored);
        shopList_tableView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        shopList_tableView->setIconSize(QSize(100, 100));
        shopList_tableView->setTextElideMode(Qt::TextElideMode::ElideMiddle);

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

        to_mainBtn = new QPushButton(frame_12);
        to_mainBtn->setObjectName("to_mainBtn");
        to_mainBtn->setMinimumSize(QSize(200, 0));
        to_mainBtn->setSizeIncrement(QSize(0, 0));
        to_mainBtn->setFont(font1);

        horizontalLayout_4->addWidget(to_mainBtn);

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
        frame_5 = new QFrame(frame);
        frame_5->setObjectName("frame_5");
        frame_5->setFrameShape(QFrame::Shape::StyledPanel);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_9 = new QHBoxLayout(frame_5);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        menu_shopTitle = new QLabel(frame_5);
        menu_shopTitle->setObjectName("menu_shopTitle");
        QFont font5;
        font5.setPointSize(16);
        font5.setBold(true);
        menu_shopTitle->setFont(font5);
        menu_shopTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_9->addWidget(menu_shopTitle);

        bookmark_btn = new QPushButton(frame_5);
        bookmark_btn->setObjectName("bookmark_btn");
        bookmark_btn->setMaximumSize(QSize(100, 50));
        bookmark_btn->setFont(font1);

        horizontalLayout_9->addWidget(bookmark_btn);


        verticalLayout_5->addWidget(frame_5);

        frame_13 = new QFrame(frame);
        frame_13->setObjectName("frame_13");
        frame_13->setFrameShape(QFrame::Shape::StyledPanel);
        frame_13->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_16 = new QGridLayout(frame_13);
        gridLayout_16->setSpacing(6);
        gridLayout_16->setContentsMargins(11, 11, 11, 11);
        gridLayout_16->setObjectName("gridLayout_16");
        menu_basket_tableView = new QTableView(frame_13);
        menu_basket_tableView->setObjectName("menu_basket_tableView");

        gridLayout_16->addWidget(menu_basket_tableView, 1, 1, 1, 1);

        menu_tableView = new QTableView(frame_13);
        menu_tableView->setObjectName("menu_tableView");
        menu_tableView->setMinimumSize(QSize(0, 300));
        menu_tableView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

        gridLayout_16->addWidget(menu_tableView, 1, 0, 1, 1);

        label_3 = new QLabel(frame_13);
        label_3->setObjectName("label_3");
        QFont font6;
        font6.setPointSize(12);
        font6.setBold(true);
        font6.setItalic(false);
        label_3->setFont(font6);

        gridLayout_16->addWidget(label_3, 0, 1, 1, 1);

        label_4 = new QLabel(frame_13);
        label_4->setObjectName("label_4");
        label_4->setFont(font2);

        gridLayout_16->addWidget(label_4, 0, 0, 1, 1);


        verticalLayout_5->addWidget(frame_13);


        verticalLayout_3->addWidget(frame);

        frame_2 = new QFrame(menuList_page);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_15 = new QGridLayout(frame_2);
        gridLayout_15->setSpacing(6);
        gridLayout_15->setContentsMargins(11, 11, 11, 11);
        gridLayout_15->setObjectName("gridLayout_15");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_15->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        toshop_backBtn = new QPushButton(frame_2);
        toshop_backBtn->setObjectName("toshop_backBtn");
        toshop_backBtn->setMinimumSize(QSize(120, 0));
        toshop_backBtn->setFont(font1);

        gridLayout_15->addWidget(toshop_backBtn, 0, 1, 1, 1);

        to_order_btn = new QPushButton(frame_2);
        to_order_btn->setObjectName("to_order_btn");
        to_order_btn->setMinimumSize(QSize(120, 0));
        to_order_btn->setFont(font1);

        gridLayout_15->addWidget(to_order_btn, 0, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_15->addItem(horizontalSpacer_3, 0, 3, 1, 1);


        verticalLayout_3->addWidget(frame_2);

        mainStackedWidget->addWidget(menuList_page);
        pay_page = new QWidget();
        pay_page->setObjectName("pay_page");
        gridLayout_17 = new QGridLayout(pay_page);
        gridLayout_17->setSpacing(6);
        gridLayout_17->setContentsMargins(11, 11, 11, 11);
        gridLayout_17->setObjectName("gridLayout_17");
        frame_14 = new QFrame(pay_page);
        frame_14->setObjectName("frame_14");
        frame_14->setFrameShape(QFrame::Shape::StyledPanel);
        frame_14->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_7 = new QVBoxLayout(frame_14);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName("verticalLayout_7");
        menu_shopTitle2 = new QLabel(frame_14);
        menu_shopTitle2->setObjectName("menu_shopTitle2");
        menu_shopTitle2->setFont(font5);
        menu_shopTitle2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_7->addWidget(menu_shopTitle2);

        pay_tableView = new QTableView(frame_14);
        pay_tableView->setObjectName("pay_tableView");
        pay_tableView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

        verticalLayout_7->addWidget(pay_tableView);

        frame_17 = new QFrame(frame_14);
        frame_17->setObjectName("frame_17");
        frame_17->setFrameShape(QFrame::Shape::StyledPanel);
        frame_17->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_6 = new QHBoxLayout(frame_17);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_11);

        label_8 = new QLabel(frame_17);
        label_8->setObjectName("label_8");
        label_8->setMinimumSize(QSize(70, 0));
        QFont font7;
        font7.setPointSize(13);
        font7.setBold(true);
        label_8->setFont(font7);

        horizontalLayout_6->addWidget(label_8);

        menu_price_label = new QLabel(frame_17);
        menu_price_label->setObjectName("menu_price_label");
        menu_price_label->setMinimumSize(QSize(110, 0));
        QFont font8;
        font8.setPointSize(13);
        font8.setBold(false);
        menu_price_label->setFont(font8);

        horizontalLayout_6->addWidget(menu_price_label);


        verticalLayout_7->addWidget(frame_17);

        frame_15 = new QFrame(frame_14);
        frame_15->setObjectName("frame_15");
        frame_15->setFrameShape(QFrame::Shape::StyledPanel);
        frame_15->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_18 = new QGridLayout(frame_15);
        gridLayout_18->setSpacing(6);
        gridLayout_18->setContentsMargins(11, 11, 11, 11);
        gridLayout_18->setObjectName("gridLayout_18");
        del_address_text = new QLineEdit(frame_15);
        del_address_text->setObjectName("del_address_text");
        del_address_text->setMinimumSize(QSize(600, 30));
        del_address_text->setFont(font4);

        gridLayout_18->addWidget(del_address_text, 0, 2, 1, 1);

        del_request_text = new QLineEdit(frame_15);
        del_request_text->setObjectName("del_request_text");
        del_request_text->setMinimumSize(QSize(600, 30));
        del_request_text->setFont(font4);

        gridLayout_18->addWidget(del_request_text, 1, 2, 1, 1);

        label_6 = new QLabel(frame_15);
        label_6->setObjectName("label_6");
        label_6->setFont(font2);

        gridLayout_18->addWidget(label_6, 1, 1, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_18->addItem(horizontalSpacer_9, 0, 0, 1, 1);

        label_5 = new QLabel(frame_15);
        label_5->setObjectName("label_5");
        label_5->setFont(font2);

        gridLayout_18->addWidget(label_5, 0, 1, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_18->addItem(horizontalSpacer_10, 0, 3, 1, 1);


        verticalLayout_7->addWidget(frame_15);

        frame_16 = new QFrame(frame_14);
        frame_16->setObjectName("frame_16");
        frame_16->setFrameShape(QFrame::Shape::StyledPanel);
        frame_16->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame_16);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);

        to_menu_back_btn = new QPushButton(frame_16);
        to_menu_back_btn->setObjectName("to_menu_back_btn");
        to_menu_back_btn->setMinimumSize(QSize(120, 0));
        to_menu_back_btn->setFont(font1);

        horizontalLayout_5->addWidget(to_menu_back_btn);

        pay_btn = new QPushButton(frame_16);
        pay_btn->setObjectName("pay_btn");
        pay_btn->setMinimumSize(QSize(120, 0));
        pay_btn->setFont(font1);

        horizontalLayout_5->addWidget(pay_btn);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_8);


        verticalLayout_7->addWidget(frame_16);


        gridLayout_17->addWidget(frame_14, 0, 0, 1, 1);

        mainStackedWidget->addWidget(pay_page);
        shop_main_page = new QWidget();
        shop_main_page->setObjectName("shop_main_page");
        verticalLayout_2 = new QVBoxLayout(shop_main_page);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        shop_title_text_label = new QLabel(shop_main_page);
        shop_title_text_label->setObjectName("shop_title_text_label");
        shop_title_text_label->setFont(font5);
        shop_title_text_label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        shop_title_text_label->setMargin(0);

        verticalLayout_2->addWidget(shop_title_text_label);

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
        orderWait_tableView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        orderWait_tableView->setTextElideMode(Qt::TextElideMode::ElideRight);
        orderWait_tableView->setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerItem);
        orderWait_tableView->setHorizontalScrollMode(QAbstractItemView::ScrollMode::ScrollPerItem);

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
        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_12);

        order_accept_btn = new QPushButton(frame_4);
        order_accept_btn->setObjectName("order_accept_btn");
        order_accept_btn->setMinimumSize(QSize(120, 0));
        order_accept_btn->setFont(font1);

        horizontalLayout_3->addWidget(order_accept_btn);

        order_deny_btn = new QPushButton(frame_4);
        order_deny_btn->setObjectName("order_deny_btn");
        order_deny_btn->setMinimumSize(QSize(120, 0));
        order_deny_btn->setFont(font1);

        horizontalLayout_3->addWidget(order_deny_btn);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_13);


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
        orderAccept_tableView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

        gridLayout_7->addWidget(orderAccept_tableView, 0, 0, 1, 1);

        frame_18 = new QFrame(shop_orderAccept_tab);
        frame_18->setObjectName("frame_18");
        frame_18->setFrameShape(QFrame::Shape::StyledPanel);
        frame_18->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_7 = new QHBoxLayout(frame_18);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_14);

        label_7 = new QLabel(frame_18);
        label_7->setObjectName("label_7");
        label_7->setFont(font2);

        horizontalLayout_7->addWidget(label_7);

        total_sales_text = new QLabel(frame_18);
        total_sales_text->setObjectName("total_sales_text");
        total_sales_text->setMinimumSize(QSize(120, 0));
        total_sales_text->setFont(font2);

        horizontalLayout_7->addWidget(total_sales_text);


        gridLayout_7->addWidget(frame_18, 1, 0, 1, 1);

        shopTabWidget->addTab(shop_orderAccept_tab, QString());

        verticalLayout_2->addWidget(shopTabWidget);

        mainStackedWidget->addWidget(shop_main_page);
        rider_main_page = new QWidget();
        rider_main_page->setObjectName("rider_main_page");
        gridLayout_8 = new QGridLayout(rider_main_page);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName("gridLayout_8");
        delTabWidget = new QTabWidget(rider_main_page);
        delTabWidget->setObjectName("delTabWidget");
        delTabWidget->setStyleSheet(QString::fromUtf8("#delTabWidget QTabWidget::pane {\n"
"    background-color: white;\n"
"    border: 2px solid black;\n"
"	border-radius:8px\n"
"}\n"
"\n"
"#delTabWidget QTabBar::tab {\n"
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
"#delTabWidget QTabBar::tab:selected {\n"
"    background: gray;\n"
"	color: white;\n"
"	font-weight: bold;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QTabWidget::tab-bar {  /* \355\203\255 \353\262\204\355\212\274\354\235\204 \352\260\220\354\213\270\353\212\224 \353\260\224 */\n"
"    left: 20px;  /* \355\203\255 \353\252\251\353\241\235\354\235\264 \354\231\274\354\252\275\354\234\274\353\241\234 \354\241\260\352\270\210 \354\235\264\353\217\231 */\n"
"}"));
        delivery_sate_tab = new QWidget();
        delivery_sate_tab->setObjectName("delivery_sate_tab");
        verticalLayout_8 = new QVBoxLayout(delivery_sate_tab);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName("verticalLayout_8");
        label = new QLabel(delivery_sate_tab);
        label->setObjectName("label");
        label->setFont(font2);

        verticalLayout_8->addWidget(label);

        deliWait_tableView = new QTableView(delivery_sate_tab);
        deliWait_tableView->setObjectName("deliWait_tableView");
        deliWait_tableView->setMinimumSize(QSize(0, 280));
        deliWait_tableView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

        verticalLayout_8->addWidget(deliWait_tableView);

        label_9 = new QLabel(delivery_sate_tab);
        label_9->setObjectName("label_9");
        label_9->setFont(font2);

        verticalLayout_8->addWidget(label_9);

        deliAccept_tableView = new QTableView(delivery_sate_tab);
        deliAccept_tableView->setObjectName("deliAccept_tableView");
        deliAccept_tableView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

        verticalLayout_8->addWidget(deliAccept_tableView);

        frame_19 = new QFrame(delivery_sate_tab);
        frame_19->setObjectName("frame_19");
        frame_19->setFrameShape(QFrame::Shape::StyledPanel);
        frame_19->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_8 = new QHBoxLayout(frame_19);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_15);

        del_complete_btn = new QPushButton(frame_19);
        del_complete_btn->setObjectName("del_complete_btn");
        del_complete_btn->setMinimumSize(QSize(120, 0));
        del_complete_btn->setFont(font1);

        horizontalLayout_8->addWidget(del_complete_btn);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_16);


        verticalLayout_8->addWidget(frame_19);

        delTabWidget->addTab(delivery_sate_tab, QString());
        del_history_tab = new QWidget();
        del_history_tab->setObjectName("del_history_tab");
        gridLayout_19 = new QGridLayout(del_history_tab);
        gridLayout_19->setSpacing(6);
        gridLayout_19->setContentsMargins(11, 11, 11, 11);
        gridLayout_19->setObjectName("gridLayout_19");
        rider_history_tableView = new QTableView(del_history_tab);
        rider_history_tableView->setObjectName("rider_history_tableView");
        rider_history_tableView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

        gridLayout_19->addWidget(rider_history_tableView, 0, 0, 1, 1);

        delTabWidget->addTab(del_history_tab, QString());

        gridLayout_8->addWidget(delTabWidget, 0, 0, 1, 1);

        mainStackedWidget->addWidget(rider_main_page);

        gridLayout_2->addWidget(mainStackedWidget, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 815, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(shopSearchText, &QLineEdit::returnPressed, shopSearchButton, qOverload<>(&QPushButton::click));
        QObject::connect(del_request_text, &QLineEdit::returnPressed, pay_btn, qOverload<>(&QPushButton::click));

        mainStackedWidget->setCurrentIndex(0);
        user_mainTabWidget->setCurrentIndex(1);
        shopTabWidget->setCurrentIndex(1);
        delTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "QTCPClient", nullptr));
        title_label->setText(QCoreApplication::translate("MainWindow", "\354\240\200\352\270\260\354\232\224", nullptr));
        logout_btn->setText(QCoreApplication::translate("MainWindow", "\353\241\234\352\267\270\354\225\204\354\233\203", nullptr));
        jFood_btn->setText(QCoreApplication::translate("MainWindow", "\354\235\274\354\213\235", nullptr));
        cFood_btn->setText(QCoreApplication::translate("MainWindow", "\354\244\221\352\265\255\354\247\221", nullptr));
        kFood_btn->setText(QCoreApplication::translate("MainWindow", "\355\225\234\354\213\235", nullptr));
        pizza_btn->setText(QCoreApplication::translate("MainWindow", "\355\224\274\354\236\220", nullptr));
        cafe_btn->setText(QCoreApplication::translate("MainWindow", "\354\271\264\355\216\230", nullptr));
        chicken_btn->setText(QCoreApplication::translate("MainWindow", "\354\271\230\355\202\250", nullptr));
        user_mainTabWidget->setTabText(user_mainTabWidget->indexOf(foodCategoryTab), QCoreApplication::translate("MainWindow", "\354\235\214\354\213\235 \354\271\264\355\205\214\352\263\240\353\246\254 \353\252\251\353\241\235", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\352\260\200\352\262\214 \354\235\264\353\246\204", nullptr));
        shopSearchButton->setText(QCoreApplication::translate("MainWindow", "\352\262\200\354\203\211", nullptr));
        user_mainTabWidget->setTabText(user_mainTabWidget->indexOf(shopSearchTab), QCoreApplication::translate("MainWindow", "\352\260\200\352\262\214 \352\262\200\354\203\211", nullptr));
        user_mainTabWidget->setTabText(user_mainTabWidget->indexOf(shopBookmarkTab), QCoreApplication::translate("MainWindow", "\354\260\234\355\225\234 \352\260\200\352\262\214", nullptr));
        user_mainTabWidget->setTabText(user_mainTabWidget->indexOf(orderStateTab), QCoreApplication::translate("MainWindow", "\353\260\260\353\213\254 \355\230\204\355\231\251", nullptr));
        user_mainTabWidget->setTabText(user_mainTabWidget->indexOf(user_order_history_tab), QCoreApplication::translate("MainWindow", "\354\243\274\353\254\270 \353\202\264\354\227\255", nullptr));
        to_mainBtn->setText(QCoreApplication::translate("MainWindow", "\353\222\244\353\241\234 \352\260\200\352\270\260", nullptr));
        menu_shopTitle->setText(QCoreApplication::translate("MainWindow", "\352\260\200\352\262\214 \354\235\264\353\246\204", nullptr));
        bookmark_btn->setText(QCoreApplication::translate("MainWindow", "\354\260\234\355\225\230\352\270\260", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "   \354\236\245\353\260\224\352\265\254\353\213\210", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "  \353\251\224\353\211\264", nullptr));
        toshop_backBtn->setText(QCoreApplication::translate("MainWindow", "\353\222\244\353\241\234\352\260\200\352\270\260", nullptr));
        to_order_btn->setText(QCoreApplication::translate("MainWindow", "\354\243\274\353\254\270\355\225\230\352\270\260", nullptr));
        menu_shopTitle2->setText(QCoreApplication::translate("MainWindow", "\352\260\200\352\262\214 \354\235\264\353\246\204", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\354\264\235 \352\260\200\352\262\251 :", nullptr));
        menu_price_label->setText(QCoreApplication::translate("MainWindow", "0\354\233\220", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\354\232\224\354\262\255\354\202\254\355\225\255", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\353\260\260\353\213\254\354\243\274\354\206\214", nullptr));
        to_menu_back_btn->setText(QCoreApplication::translate("MainWindow", "\353\222\244\353\241\234\352\260\200\352\270\260", nullptr));
        pay_btn->setText(QCoreApplication::translate("MainWindow", "\352\262\260\354\240\234\355\225\230\352\270\260", nullptr));
        shop_title_text_label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        order_accept_btn->setText(QCoreApplication::translate("MainWindow", "\354\243\274\353\254\270 \354\212\271\353\202\231", nullptr));
        order_deny_btn->setText(QCoreApplication::translate("MainWindow", "\354\243\274\353\254\270 \352\261\260\354\240\210", nullptr));
        shopTabWidget->setTabText(shopTabWidget->indexOf(shop_orderWait_tab), QCoreApplication::translate("MainWindow", "\354\243\274\353\254\270 \353\252\251\353\241\235", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\354\264\235 \353\247\244\354\266\234 :", nullptr));
        total_sales_text->setText(QCoreApplication::translate("MainWindow", "0\354\233\220", nullptr));
        shopTabWidget->setTabText(shopTabWidget->indexOf(shop_orderAccept_tab), QCoreApplication::translate("MainWindow", "\353\260\260\353\213\254 \355\230\204\355\231\251", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\353\260\260\353\213\254 \353\214\200\352\270\260\353\252\251\353\241\235", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\353\202\264 \353\260\260\353\213\254\353\252\251\353\241\235", nullptr));
        del_complete_btn->setText(QCoreApplication::translate("MainWindow", "\353\260\260\353\213\254 \354\231\204\353\243\214", nullptr));
        delTabWidget->setTabText(delTabWidget->indexOf(delivery_sate_tab), QCoreApplication::translate("MainWindow", "\353\260\260\353\213\254 \355\225\230\352\270\260", nullptr));
        delTabWidget->setTabText(delTabWidget->indexOf(del_history_tab), QCoreApplication::translate("MainWindow", "\353\260\260\353\213\254 \353\202\264\354\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
