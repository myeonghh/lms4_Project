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
    enum TYPE {LOGIN = 0, SIGNUP, IDSEARCH, PWSEARCH, IDDUPCHK, PNUMDUPCHK};
    Ui::MainWindow *ui;
    Login *loginWidget;
    QTcpSocket* m_socket;


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
    void slot_displayMessage(const QString& str);
    void send_message(int type, QString id, QString pw, QString phone_num, QString email);
};

#endif // MAINWINDOW_H
