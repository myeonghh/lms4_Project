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

    QTcpSocket* m_socket;

signals:
    void signal_newMessage(QString);

private slots:
    void slot_discardSocket();
    void slot_displayError(QAbstractSocket::SocketError socketError);
    void slot_readSocket();
    void on_pushButton_sendMessage_clicked();
    void on_pushButton_sendAttachment_clicked();
    void slot_displayMessage(const QString& str);
};

#endif // MAINWINDOW_H
