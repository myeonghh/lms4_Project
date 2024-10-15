#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

    connect(ui->toSignUpBtn, &QPushButton::clicked, this, [this](){pageMove(SIGNUP);});
    connect(ui->toSearchIdBtn, &QPushButton::clicked, this, [this](){pageMove(IDSEARCH);});
    connect(ui->toSearchPwBtn, &QPushButton::clicked, this, [this](){pageMove(PWSEARCH);});
    connect(ui->backBtn, &QPushButton::clicked, this, [this](){pageMove(LOGIN);});
    connect(ui->backBtn_2, &QPushButton::clicked, this, [this](){pageMove(LOGIN);});
    connect(ui->backBtn_3, &QPushButton::clicked, this, [this](){pageMove(LOGIN);});

    connect(ui->signUpBtn, &QPushButton::clicked, this, &Login::signUp);
    connect(this, &MainWindow::operate)

}

Login::~Login()
{
    delete ui;
}

// ui->stackedWidget->setCurrentWidget(ui->signup);


void Login::pageMove(int page) // 페이지 이동 함수
{
    ui->stackedWidget->setCurrentIndex(page);
}

void Login::login() // 로그인 버튼 클릭시 로그인 로직
{

}


void Login::idDupChk() // 회원가입 아이디 중복 체크 버튼
{

}

void Login::pnumDupChk() // 회원가입 휴대폰번호 중복 체크 버튼
{

}


void Login::signUp() // 회원가입 버튼 클릭시 회원가입 로직
{
    QString id;
    QString pw;
    QString phone_num;
    QString email;

    id = ui->s_idText->text().trimmed();
    pw = ui->s_pwText->text().trimmed();
    phone_num = ui->s_pNumText->text().trimmed();
    email = ui->s_emailText->text().trimmed();

    if (id.isEmpty() || pw.isEmpty() || phone_num.isEmpty() || email.isEmpty())
    {
        QMessageBox::critical(this, "오류", "모든 정보를 입력해야 합니다.");
    }
    else
    {
        emit signup_signal(SIGNUP, id, pw, phone_num, email);
    }
}

void Login::idSearch() // 아이디 찾기 버튼 클릭시 아이디 찾기 로직
{

}

void Login::pwSearch() // 비밀번호 찾기 버튼 클릭시 비밀번호 찾기 로직
{

}




