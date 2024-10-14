#include "loginwidget.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    connect(ui->loginButton, &QPushButton::pressed,
            this, &LoginWidget::loginBtnClicked);
}

void LoginWidget::loginBtnClicked()
{
    QString serverIp = ui->ipLineEdit->text().trimmed();
    QString name = ui->nameLineEdit->text().trimmed();

    emit sig_loginInfo(serverIp, name);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}
