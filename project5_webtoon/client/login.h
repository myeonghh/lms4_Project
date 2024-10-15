#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QDebug>
#include "mainwindow.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();


private slots:
    void pageMove(int page);
    void login();
    void idDupChk();
    void pnumDupChk();
    void signUp();
    void idSearch();
    void pwSearch();

private:
    Ui::Login *ui;
    enum Page {LOGIN = 0, SIGNUP, IDSEARCH, PWSEARCH};
};

#endif // LOGIN_H
