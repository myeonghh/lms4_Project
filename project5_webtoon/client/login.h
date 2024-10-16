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
    // void login_info_signal(int type, QString id, QString pw);
    // void search_info_signal(int type, QString id, QString phone_num, QString email="");

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

    // 내일 해야 될것 => 회원가입 성공시 로그인 화면으로 바꾸고, 로그인 성공 팝업 띄우기!!!!!!!!!!!!!!!!!!
    // connect는 mainwindow에서 시그널도 mainwindow에서,리시버와 슬롯 함수를 login 클래스에서 해야됨!!!!
private:
    Ui::Login *ui;
    enum PAGE {LOGIN = 0, SIGNUP, IDSEARCH, PWSEARCH, IDDUPCHK, PNUMDUPCHK};
    bool id_dup_chk = false;
    bool pNum_dup_chk = false;
};

#endif // LOGIN_H
