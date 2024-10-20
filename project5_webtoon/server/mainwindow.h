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
    enum TYPE {SIGNUPINFO = 0, LOGININFO, IDINFO, PWINFO, TOONINFO, TOONLIST, TOONIMAGE, BOOKMARK, BOOKMARKLIST, TOONLIKE, EPICHANGE, TOONINFOTEXT};

    bool initializeDataBase();
    void appendToSocketList(QTcpSocket* socket);
    void sendMessage(QTcpSocket* socket, int type, QString msg);
    void sendAttachment(QTcpSocket* socket, QString filePath);
    void refreshComboBox();

signals:
    void singal_newMessage(QString);

private slots:
    void slot_newConnection();
    void slot_discardSocket();
    void slot_displayError(QAbstractSocket::SocketError socketError);
    void slot_readSocket();
    void slot_displayMessage(const QString& str);
};

#endif // MAINWINDOW_H
