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
    void signup_signal(int type, QString id, QString pw, QString phone_num, QString email);
    void login_signal(int type, QString id, QString pw, QString phone_num, QString email);
    void id_dupchk_signal(int type, QString id, QString pw, QString phone_num, QString email);
    void pnum_dupchk_signal(int type, QString id, QString pw, QString phone_num, QString email);
private slots:
    void pageMove(int page);
    void login();
    void idDupChk();
    void pnumDupChk();
    void signUp();
    void idSearch();
    void pwSearch();
    void signupSuccess();
    // 내일 해야 될것 => 회원가입 성공시 로그인 화면으로 바꾸고, 로그인 성공 팝업 띄우기!!!!!!!!!!!!!!!!!!
    // connect는 mainwindow에서 시그널도 mainwindow에서,리시버와 슬롯 함수를 login 클래스에서 해야됨!!!!
private:
    Ui::Login *ui;
    enum PAGE {LOGIN = 0, SIGNUP, IDSEARCH, PWSEARCH, IDDUPCHK, PNUMDUPCHK};
};

#endif // LOGIN_H
