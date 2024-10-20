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
    void user_info_signal(int type, QString id="", QString pw="", QString phone_num="", QString email="");
    void login_success_signal(QString login_user_id);

public slots:
    void signUp_operate(QString info);
    void login_operate(QString info);
    void idSearch_operate(QString info);
    void pwSearch_operate(QString info);

private slots:
    void pageMove(int page);
    void login();
    void idDupChk();
    void pnumDupChk();
    void signUp();
    void idSearch();
    void pwSearch();
    void idText_change();
    void pNumText_change();

private:
    Ui::Login *ui;
    enum PAGE {LOGIN = 0, SIGNUP, IDSEARCH, PWSEARCH, IDDUPCHK, PNUMDUPCHK};
    bool id_dup_chk = false;
    bool pNum_dup_chk = false;
};

#endif // LOGIN_H
