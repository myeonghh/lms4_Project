#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

signals:
    void user_info_signal(int act_type, int client_type, QString id="", QString pw="", QString phone_num="");
    void login_success_signal(QString login_user_id);

public slots:
    void signUp_operate(QString info);
    void login_operate(QString info);

private slots:
    void pageMove(int page);
    void login();
    void idDupChk();
    void pnumDupChk();
    void signUp();
    void idText_change();
    void pNumText_change();
    void choice_shop_change(int index);

private:
    Ui::Login *ui;
    enum ACT {LOGIN = 0, SIGNUP, IDDUPCHK, PNUMDUPCHK};
    enum CLIENT {USER = 0, SHOP, RIDER};
    bool id_dup_chk = false;
    bool pNum_dup_chk = false;
    int signUp_client_type;
};

#endif // LOGIN_H
