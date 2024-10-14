#include "widget.h"
#include "./ui_widget.h"

#include <QRegularExpression>
#include <QRegularExpressionMatch>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    loginWidget = new LoginWidget();

    connect(loginWidget, &LoginWidget::sig_loginInfo,
            this,        &Widget::loginInfo);

    connect(ui->sayButton, &QPushButton::pressed,
            this,           &Widget::sayButton_clicked);

    loginWidget->show();

    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()),
            this,   SLOT(readyRead()));
    connect(socket, SIGNAL(connected()),
            this,   SLOT(connected()));
}

void Widget::loginInfo(QString addr, QString name)
{
    ipAddr = addr;
    userName = name;

    socket->connectToHost(ipAddr, 35000);
}

void Widget::sayButton_clicked()
{
    QString message = ui->sayLineEdit->text().trimmed();

    if(!message.isEmpty())
    {
        socket->write(QString(message + "\n").toUtf8());
    }

    ui->sayLineEdit->clear();
    ui->sayLineEdit->setFocus();
}

void Widget::connected()
{
    loginWidget->hide();
    this->window()->show();

    socket->write(QString("/me:" + userName + "\n").toUtf8());
}

void Widget::readyRead()
{
    while(socket->canReadLine())
    {
        QString line = QString::fromUtf8(socket->readLine()).trimmed();

        QRegularExpression re("^([^:]+):(.*)$");
        QRegularExpressionMatch match = re.match(line);

        if(match.hasMatch())
        {
            QString user = match.captured(1);
            QString message = match.captured(2);

            ui->roomTextEdit->append("<b>"+user+"</b>:"+message);
        }
    }
}

Widget::~Widget()
{
    delete ui;
}

