#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractSocket>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QHostAddress>
#include <QMessageBox>
#include <QMetaType>
#include <QString>
#include <QStandardPaths>
#include <QTcpSocket>
#include <QStandardItemModel>
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QRegularExpression>
#include <QIcon>
#include <QSpinBox>
#include "login.h"
#include "qtoolbutton.h"

namespace Ui {
class MainWindow;
}

// [ex.02]
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    enum LOGINACT {LOGIN = 0, SIGNUP, IDDUPCHK, PNUMDUPCHK};
    enum DELIVERYACT {LOGOUT = 0, CATEGORY, SHOPTITLE ,SHOPLIST, MENULIST, USERORDER, ORDERDENY,
                       ORDERACCEPT, UORDERLIST, SORDERLIST_WAITING, SORDERLIST_ENTIRE, DELIVERYLIST,
                       DELIACCEPT, DELIACCEPTLIST, DELICOMPLETE, DELIHISTORYLIST, UORDER_HISTORYLIST, BOOKMARK, BOOKMARKLIST};
    enum CLIENT {USER= 0, SHOP, RIDER};
    enum FOOD {CHICKEN = 0, PIZZA, KFOOD, JFOOD, CFOOD, CAFE};
    enum VIEWTYPE {TYPE1 = 0, TYPE2};
    Ui::MainWindow *ui;
    Login *loginWidget;
    QTcpSocket *m_socket;

    QStandardItemModel *shoplist_model = nullptr;
    QStandardItemModel *menulist_model = nullptr;
    QStandardItemModel *basketlist_model = nullptr;
    QSortFilterProxyModel *proxyModel = nullptr;
    QStandardItemModel *orderWaitList_model = nullptr;
    QStandardItemModel *user_orderlist_model = nullptr;
    QStandardItemModel *user_historyList_model = nullptr;
    QStandardItemModel *shop_orderlist_model = nullptr;
    QStandardItemModel *rider_orderlist_model = nullptr;
    QStandardItemModel *orderEntireList_model = nullptr;
    QStandardItemModel *deliveryWaitList_model = nullptr;
    QStandardItemModel *deliveryAcceptList_model = nullptr;
    QStandardItemModel *deliveryCompleteList_model = nullptr;
    QStandardItemModel *bookmarkList_model = nullptr;

    QString clicked_shop_num;
    QString clicked_shop_title;
    QList<QToolButton*> category_btn_list;
    QList<QPixmap> shop_img_list;
    QList<QPixmap> menu_img_list;
    QList<QPixmap> category_img_list;
    int rowIndex = 0;
    void send_login_func_order(int act_type, int client_type, QString id = "", QString pw = "", QString phone_num = "");
    void send_delivery_func_order(int act_type, QString msg = "", int sender = 0, int senderNum = 0, int receiver = 0, int receiverNum = 0);
    void shop_img_to_item(QByteArray &img_buf);
    void menu_img_to_item(QByteArray &img_buf);
    void category_img_to_item(QByteArray &img_buf);
    void create_shop_list_model(QString &shopList);
    void create_menu_list_model(QString &menulist);
    void create_food_category();
    void m_view_design_setting(QTableView *view, int type);
    void s_view_design_setting(QTableView *view);
    struct PresentClnt {int type; int clnt_num; QString clnt_id;};
    PresentClnt present_clnt;
    int clicked_food_type;
    bool shop_search_chk = false;
    bool shop_renewal_chk = false;
    bool bookmarkview_chk = false;
    int total_price;
    void create_client_order_list_model(QStandardItemModel *model, QString orderlist);
    void show_user_state_tableView(QString orderlist);
    void show_user_history_tableView(QString orderlist);
    void show_order_wait_tableView(QString orderlist);
    void show_order_entire_tableView(QString orderlist);
    void show_delivery_wait_tableView(QString orderlist);
    void show_delivery_accept_tableView(QString orderlist);
    void show_delivery_complete_tableView(QString orderlist);
    void rider_view_design_setting(QTableView *view);
    void bookmark_operate(QString msg);
    void create_bookmark_list_model(QString &shoplist);

signals:
    void signal_newMessage(QString);
    void operate_info_signal(QString info);
    void login_info_signal(QString info);
    void idSearch_info_signal(QString info);
    void pwSearch_info_signal(QString info);

private slots:
    void slot_discardSocket();
    void slot_displayError(QAbstractSocket::SocketError socketError);
    void slot_readSocket();
    void to_shop_list_view(int foodType);
    void shop_view_double_clicked(const QModelIndex &index);
    void menu_view_double_clicked(const QModelIndex &index);
    void basket_view_double_clicked(const QModelIndex &index);
    void shop_search();
    void get_login_user_id(QString id);
    void on_logout_btn_clicked();
    void to_order_page();
    void user_final_order();
    void order_accept_or_deny(bool accept);
    void delivery_tableView_double_clicked(const QModelIndex &index);
    void change_bookmark_tab(int index);
    void on_to_mainBtn_clicked();
    void on_to_menu_back_btn_clicked();
    void delivery_complete();
};

#endif // MAINWINDOW_H
