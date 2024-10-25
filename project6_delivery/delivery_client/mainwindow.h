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
    enum DELIVERYACT {LOGOUT = 0, CATEGORY, SHOPLIST, MENULIST};
    enum CLIENT {USER= 0, SHOP, RIDER};
    enum FOOD {CHICKEN = 0, PIZZA, KFOOD, JFOOD, CFOOD, CAFE};
    Ui::MainWindow *ui;
    Login *loginWidget;
    QTcpSocket *m_socket;

    QStandardItemModel *shoplist_model;
    QStandardItemModel *menulist_model;
    QStandardItemModel *basketlist_model;
    QSortFilterProxyModel *proxyModel;

    QString clicked_shop_num;
    QString clicked_shop_title;
    QList<QToolButton*> category_btn_list;
    QList<QPixmap> shop_img_list;
    QList<QPixmap> menu_img_list;
    QList<QPixmap> category_img_list;
    int rowIndex = 0;

    void send_login_func_order(int act_type, int client_type, QString id = "", QString pw = "", QString phone_num = "");
    void send_delivery_func_order(int act_type, QString msg = "", int sender = 0, int senderNum = 0, int receiver = 0, int receiverNum = 0);
    QString client_type_to_string(int client_type);
    void shop_img_to_item(QByteArray &img_buf);
    void menu_img_to_item(QByteArray &img_buf);
    void category_img_to_item(QByteArray &img_buf);
    void create_shop_list_model(QString &shopList);
    void create_menu_list_model(QString &menulist);
    void create_food_category();

    struct PresentClnt {int type; int clnt_num; QString clnt_id;};
    PresentClnt present_clnt;
    int clicked_food_type;
    bool shop_search_chk = false;

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


    // void create_toonInfo_model(QString &toonlist);
    // void create_toonList_model(QString &toonlist);
    // void view_double_clicked(const QModelIndex &index);
    // void toon_search();
    // void on_toList_backBtn_clicked();
    // void epi_view_double_clicked(const QModelIndex &index);
    // void on_backList_btn_clicked();
    // void bookmark_control();
    // void like_control();

    void on_to_mainBtn_clicked();
};

#endif // MAINWINDOW_H
