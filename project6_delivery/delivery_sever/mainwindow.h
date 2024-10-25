#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QMetaType>
#include <QSet>
#include <QStandardPaths>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlQuery>



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
    Ui::MainWindow *ui;

    QTcpServer* m_server;
    QSet<QTcpSocket*> qset_connectedSKT;
    QSqlDatabase m_db;
    QSqlTableModel *m_model;
    enum ACTTYPE {SIGNUPINFO = 0, LOGININFO, SHOPLIST, MENULIST, USERORDER};
    enum CLIENTTYPE {USER = 0, SHOP, RIDER};

    bool initializeDataBase();
    void appendToSocketList(QTcpSocket* socket);
    void sendMessage(QTcpSocket* socket, int act_type, QString msg = "", int sender=0, int senderNum=0, int receiver=0, int receiverNum=0);

    void sendAttachment(QTcpSocket* socket, QString filePath);
    void refreshComboBox();
    QString client_type_to_string(int client_type);

    struct Client {int type; int clnt_num; QTcpSocket* clnt_socket; QString clnt_id;
                    Client(int type, int clnt_num, QTcpSocket* clnt_socket, QString clnt_id)
                    : type(type), clnt_num(clnt_num), clnt_socket(clnt_socket), clnt_id(clnt_id){}};
    QList<Client*> login_clnt_list;

signals:
    void singal_newMessage(QString);

private slots:
    void slot_newConnection();
    void slot_discardSocket();
    void slot_displayError(QAbstractSocket::SocketError socketError);
    void slot_readSocket();
    // void on_pushButton_sendMessage_clicked();
    // void on_pushButton_sendAttachment_clicked();
    void slot_displayMessage(const QString& str);
};

#endif // MAINWINDOW_H
