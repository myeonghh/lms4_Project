#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

    pageMove(LOGIN);
    ui->s_idText->setPlaceholderText("아이디를 입력하세요");
    ui->s_pwText->setPlaceholderText("비밀번호를 입력하세요");
    ui->s_pNumText->setPlaceholderText("전화번호를 입력하세요");

    connect(ui->toSignUpBtn, &QPushButton::clicked, this, [this](){pageMove(SIGNUP);});
    connect(ui->backBtn, &QPushButton::clicked, this, [this](){pageMove(LOGIN);});


    connect(ui->idDupChkBtn, &QPushButton::clicked, this, &Login::idDupChk);
    connect(ui->pnumDupChkBtn, &QPushButton::clicked, this, &Login::pnumDupChk);

    connect(ui->signUpBtn, &QPushButton::clicked, this, &Login::signUp);
    connect(ui->loginBtn, &QPushButton::clicked, this, &Login::login);


    connect(ui->s_idText, &QLineEdit::textChanged, this, &Login::idText_change);
    connect(ui->s_pNumText, &QLineEdit::textChanged, this, &Login::pNumText_change);
    connect(ui->login_client_choice, &QComboBox::currentIndexChanged, this, [this](int index){choice_shop_change(index);});

}

Login::~Login()
{
    delete ui;
}

void Login::choice_shop_change(int index)
{
    if (index == CLIENT::SHOP)
    {
        ui->toSignUpBtn->hide();
    }
    else
    {
        ui->toSignUpBtn->show();
    }
}

void Login::idText_change()
{
    id_dup_chk = false;
    ui->idDupChkText->clear();
}

void Login::pNumText_change()
{
    pNum_dup_chk = false;
    ui->pnumDupChkText->clear();
}

void Login::signUp_operate(QString info)
{
    if (info == "signUp success") // 회원가입 성공
    {
        QMessageBox::information(this, "정보", "회원가입이 완료되었습니다 로그인 하세요.");
        ui->s_idText->clear();
        ui->s_pwText->clear();
        ui->s_pNumText->clear();
        ui->idDupChkText->clear();
        ui->pnumDupChkText->clear();
        pageMove(LOGIN);
        ui->login_client_choice->setCurrentIndex(signUp_client_type);
    }
    else if (info == "signUp error") // 회원가입 DB오류
    {
        QMessageBox::critical(this, "오류", "회원가입에 실패 하였습니다.");
    }
    else if (info == "signUp idDup") // 아이디 중복
    {
        ui->idDupChkText->setText("이미 가입된 아이디입니다");
        ui->idDupChkText->setStyleSheet("color: red; font-size: 13px; font-weight: bold;");
        id_dup_chk = false;
    }
    else if (info == "signUp !idDup") // 아이디 중복 아님
    {
        ui->idDupChkText->setText("사용 가능한 아이디입니다");
        ui->idDupChkText->setStyleSheet("color: green; font-size: 13px; font-weight: bold;");
        id_dup_chk = true;
    }
    else if (info == "signUp phoneNumDup") // 핸드폰 번호 중복
    {
        ui->pnumDupChkText->setText("이미 가입된 번호입니다");
        ui->pnumDupChkText->setStyleSheet("color: red; font-size: 13px; font-weight: bold;");
        pNum_dup_chk = false;
    }
    else if (info == "signUp !phoneNumDup") // 핸드폰 번호 중복 아님
    {
        ui->pnumDupChkText->setText("사용 가능한 번호입니다");
        ui->pnumDupChkText->setStyleSheet("color: green; font-size: 13px; font-weight: bold;");
        pNum_dup_chk = true;
    }
}

void Login::login_operate(QString info)
{
    if (info == "login success")
    {
        emit login_success_signal(ui->l_idText->text());
        ui->l_idText->clear();
        ui->l_pwText->clear();
        id_dup_chk = false;
        pNum_dup_chk = false;
    }
    else if (info == "login fail")
    {
        QMessageBox::critical(this, "오류", "아이디 혹은 비밀번호가 맞지 않습니다.");
        ui->l_idText->clear();
        ui->l_pwText->clear();
    }
}

// ui->stackedWidget->setCurrentWidget(ui->signup);
void Login::pageMove(int page) // 페이지 이동 함수
{
    ui->l_idText->clear();
    ui->l_pwText->clear();
    ui->s_idText->clear();
    ui->s_pwText->clear();
    ui->s_pNumText->clear();

    ui->stackedWidget->setCurrentIndex(page);
}

void Login::login() // 로그인 버튼 클릭시 로그인 로직
{

    QString id;
    QString pw;

    id = ui->l_idText->text().trimmed();
    pw = ui->l_pwText->text().trimmed();

    if (id.isEmpty() || pw.isEmpty())
    {
        QMessageBox::critical(this, "오류", "아이디와 비밀번호를 모두 입력해야 합니다.");
    }
    else
    {
        int client_type = ui->login_client_choice->currentIndex();

        switch (client_type)
        {
        case CLIENT::USER:
            emit user_info_signal(CLIENT::USER, ACT::LOGIN, id, pw);
            break;
        case CLIENT::SHOP:
            emit user_info_signal(CLIENT::SHOP, ACT::LOGIN, id, pw);
            break;
        case CLIENT::RIDER:
            emit user_info_signal(CLIENT::RIDER, ACT::LOGIN, id, pw);
            break;
        default:
            break;
        }
    }
}


void Login::idDupChk() // 회원가입 아이디 중복 체크 버튼
{
    QString id;
    id = ui->s_idText->text().trimmed();

    if (id.isEmpty())
    {
        QMessageBox::critical(this, "오류", "아이디를 입력해야 합니다.");
    }
    else
    {
        signUp_client_type = ui->signUp_client_choice->currentIndex();

        switch (signUp_client_type)
        {
        case CLIENT::USER:
            emit user_info_signal(ACT::IDDUPCHK, CLIENT::USER, id);
            break;
        case CLIENT::RIDER-1:
            emit user_info_signal(ACT::IDDUPCHK, CLIENT::RIDER, id);
            break;
        default:
            break;
        }
    }
}

void Login::pnumDupChk() // 회원가입 휴대폰번호 중복 체크 버튼
{
    QString phone_num;
    phone_num = ui->s_pNumText->text().trimmed();

    if (phone_num.isEmpty())
    {
        QMessageBox::critical(this, "오류", "휴대폰 번호를 입력해야 합니다.");
    }
    else
    {
        signUp_client_type = ui->signUp_client_choice->currentIndex();

        switch (signUp_client_type)
        {
        case CLIENT::USER:
            emit user_info_signal(ACT::PNUMDUPCHK, CLIENT::USER, "", "", phone_num);
            break;
        case CLIENT::RIDER-1:
            emit user_info_signal(ACT::PNUMDUPCHK, CLIENT::RIDER, "", "", phone_num);
            break;
        default:
            break;
        }
    }
}


void Login::signUp() // 회원가입 버튼 클릭시 회원가입 로직
{
    QString id;
    QString pw;
    QString phone_num;

    id = ui->s_idText->text().trimmed();
    pw = ui->s_pwText->text().trimmed();
    phone_num = ui->s_pNumText->text().trimmed();

    if (id.isEmpty() || pw.isEmpty() || phone_num.isEmpty())
    {
        QMessageBox::critical(this, "오류", "모든 정보를 입력해야 합니다.");
    }
    else if (id_dup_chk == false || pNum_dup_chk == false)
    {
        QMessageBox::critical(this, "오류", "중복 체크를 모두 완료해야 합니다.");
    }
    else
    {
        int client_type = ui->signUp_client_choice->currentIndex();

        switch (client_type)
        {
        case CLIENT::USER:
            emit user_info_signal(ACT::SIGNUP, CLIENT::USER, id, pw, phone_num);
            signUp_client_type = USER;
            break;
        case CLIENT::RIDER-1:
            emit user_info_signal(ACT::SIGNUP, CLIENT::RIDER, id, pw, phone_num);
            signUp_client_type = RIDER;
            break;
        default:
            break;
        }
    }
}







