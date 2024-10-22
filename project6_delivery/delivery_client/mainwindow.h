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
#include "login.h"

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
    enum LOGINACTTYPE {LOGIN = 0, SIGNUP, IDDUPCHK, PNUMDUPCHK};
    enum TOONTYPE {TOONINFO = 0, TOONLIST, TOONIMAGE, BOOKMARK};
    enum CLIENT {USER= 0, SHOP, RIDER};
    Ui::MainWindow *ui;
    Login *loginWidget;
    QTcpSocket *m_socket;
    QStandardItemModel *toonInfo_model;
    QStandardItemModel *toonList_model;
    void create_day_view();
    void toon_img_show(QByteArray &img_buf);
    void thumbnail_to_item(QByteArray &img_buf);
    QList<QLabel*> imgLabel_list;
    QString toonInfo_data;
    QList<QPixmap> thumbnail_list;
    QStandardItemModel *model123;
    int rowIndex = 0;
    QString login_user_id;
    QString present_toon_id;
    QString client_type_to_string(int client_type);

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
    void on_pushButton_sendMessage_clicked();
    void on_pushButton_sendAttachment_clicked();
    void slot_displayMessage(const QString &str);
    void send_toon_info(int type, QString str="");
    void send_user_info(int act_type, int client_type, QString id, QString pw, QString phone_num);


    void create_toonInfo_model(QString &toonlist);
    void create_toonList_model(QString &toonlist);
    void view_double_clicked(const QModelIndex &index);
    void toon_search();
    void on_toList_backBtn_clicked();
    void epi_view_double_clicked(const QModelIndex &index);
    void on_backList_btn_clicked();
    void bookmark_control();
    void like_control();
    void get_login_user_info(QString id);
};

#endif // MAINWINDOW_H
