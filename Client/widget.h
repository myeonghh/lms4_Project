#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include "loginwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    LoginWidget *loginWidget;

    QTcpSocket *socket;
    QString    ipAddr;
    QString    userName;

private slots:
    void loginInfo(QString addr, QString name);
    void sayButton_clicked();
    void connected();
    void readyRead();

};
#endif // WIDGET_H
