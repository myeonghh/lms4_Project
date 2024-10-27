/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *login;
    QGridLayout *gridLayout_2;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout;
    QFrame *frame_3;
    QGridLayout *gridLayout_3;
    QLineEdit *l_pwText;
    QLabel *label_2;
    QPushButton *loginBtn;
    QLineEdit *l_idText;
    QLabel *label_3;
    QComboBox *login_client_choice;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *toSignUpBtn;
    QSpacerItem *horizontalSpacer_4;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QLabel *title_label;
    QWidget *signup;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_5;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_4;
    QFrame *frame_6;
    QVBoxLayout *verticalLayout_4;
    QFrame *frame_7;
    QGridLayout *gridLayout_4;
    QLabel *label_7;
    QLabel *idDupChkText;
    QPushButton *idDupChkBtn;
    QLabel *label_5;
    QLineEdit *s_pNumText;
    QLabel *label_6;
    QLineEdit *s_idText;
    QLineEdit *s_pwText;
    QComboBox *signUp_client_choice;
    QPushButton *signUpBtn;
    QPushButton *pnumDupChkBtn;
    QLabel *pnumDupChkText;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_6;
    QFrame *frame_8;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *backBtn;
    QSpacerItem *horizontalSpacer_10;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(681, 592);
        Login->setStyleSheet(QString::fromUtf8("/* QTableView */\n"
"QTableView {\n"
"    border: 1px solid #2c3e50; /* \355\205\214\353\221\220\353\246\254 \353\221\220\352\273\230 */\n"
"    gridline-color: #bdc3c7;      /* \354\205\200 \352\265\254\353\266\204\354\204\240 \354\203\211\354\203\201 */\n"
"    font-size: 13px;           /* \353\202\264\353\266\200 \355\205\215\354\212\244\355\212\270 \355\201\254\352\270\260 */\n"
"    font-family: \"Malgun Gothic\"; /* \353\202\264\353\266\200 \355\205\215\354\212\244\355\212\270 \355\217\260\355\212\270 */\n"
"}\n"
"\n"
"/* QHeaderView */\n"
"QHeaderView::section {\n"
"    background-color: #2ecc71; /* \355\227\244\353\215\224 \353\260\260\352\262\275\354\203\211\354\235\204 \354\227\260\355\225\234 \354\264\210\353\241\235\354\203\211\354\234\274\353\241\234 \353\263\200\352\262\275 */\n"
"    color: white;              /* \355\227\244\353\215\224 \352\270\200\354\236\220 \354\203\211\354\203\201 */\n"
"    font-size: 15px;           /* \355\227\244\353\215\224 \352\270\200\354\236\220 \355\201\254\352\270"
                        "\260 */\n"
"    font-weight: bold;         /* \355\227\244\353\215\224 \352\270\200\354\236\220 \352\265\265\352\270\260 */\n"
"    padding: 4px;\n"
"    border: 1px solid #27ae60; /* \355\227\244\353\215\224 \355\205\214\353\221\220\353\246\254\353\245\274 \354\241\260\352\270\210 \353\215\224 \354\247\204\355\225\234 \354\264\210\353\241\235\354\203\211\354\234\274\353\241\234 */\n"
"    font-family: \"Malgun Gothic\";\n"
"}\n"
"\n"
"/* QPushButton */\n"
"QPushButton {\n"
"    background-color: #2ecc71; /* \353\262\204\355\212\274 \353\260\260\352\262\275\354\235\204 \354\227\260\355\225\234 \354\264\210\353\241\235\354\203\211\354\234\274\353\241\234 */\n"
"    color: white;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"    border-radius: 5px;\n"
"    padding: 5px 10px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #27ae60; /* \353\247\210\354\232\260\354\212\244 \354\230\244\353\262\204 \354\213\234 \354\247\204\355\225\234 \354\264\210\353\241\235\354\203\211\354\234\274\353\241\234"
                        " */\n"
"}\n"
"\n"
"/* QMessageBox */\n"
"QMessageBox {\n"
"    background-color: #ffffff;        /* \353\260\260\352\262\275 \354\203\211\354\203\201\354\235\204 \355\235\260\354\203\211\354\234\274\353\241\234 \354\204\244\354\240\225 */\n"
"    border: 2px solid #27ae60;        /* \354\264\210\353\241\235\354\203\211 \355\205\214\353\221\220\353\246\254 */\n"
"    border-radius: 10px;              /* \353\221\245\352\267\274 \353\252\250\354\204\234\353\246\254 */\n"
"    padding: 10px;                    /* \353\202\264\353\266\200 \354\227\254\353\260\261 */\n"
"}\n"
"\n"
"/* QMessageBox \355\205\215\354\212\244\355\212\270 */\n"
"QMessageBox QLabel {\n"
"    color: #000000;                   /* \355\205\215\354\212\244\355\212\270 \354\203\211\354\203\201 (\352\262\200\354\240\225) */\n"
"    font-family: \"\353\247\221\354\235\200 \352\263\240\353\224\225\";          /* \355\217\260\355\212\270 \354\204\244\354\240\225 */\n"
"    font-size: 14pt;                  /* \355\205\215\354\212\244\355\212\270 \355"
                        "\201\254\352\270\260 */\n"
"    font-weight: bold;                /* \352\265\265\354\235\200 \355\205\215\354\212\244\355\212\270 */\n"
"    margin-bottom: 10px;              /* \353\251\224\354\213\234\354\247\200\354\231\200 \353\262\204\355\212\274 \354\202\254\354\235\264 \354\227\254\353\260\261 */\n"
"}\n"
"\n"
"/* QMessageBox \353\262\204\355\212\274 */\n"
"QMessageBox QPushButton {\n"
"    background-color: #27ae60;        /* \353\262\204\355\212\274 \353\260\260\352\262\275\354\235\204 \354\247\204\355\225\234 \354\264\210\353\241\235\354\203\211\354\234\274\353\241\234 */\n"
"    color: white;                     /* \353\262\204\355\212\274 \355\205\215\354\212\244\355\212\270 \354\203\211\354\203\201 */\n"
"    font-family: \"\353\247\221\354\235\200 \352\263\240\353\224\225\";          /* \353\262\204\355\212\274 \355\217\260\355\212\270 \354\204\244\354\240\225 */\n"
"    font-size: 12pt;                  /* \355\205\215\354\212\244\355\212\270 \355\201\254\352\270\260 */\n"
"    border-radius: 5"
                        "px;               /* \353\262\204\355\212\274 \353\252\250\354\204\234\353\246\254 \353\221\245\352\270\200\352\262\214 */\n"
"    padding: 5px 15px;                /* \353\262\204\355\212\274 \353\202\264\353\266\200 \354\227\254\353\260\261 */\n"
"    margin: 5px;                      /* \353\262\204\355\212\274 \354\231\270\353\266\200 \354\227\254\353\260\261 */\n"
"}\n"
"\n"
"QMessageBox QPushButton:hover {\n"
"    background-color: #2ecc71;        /* \353\247\210\354\232\260\354\212\244 \354\230\244\353\262\204 \354\213\234 \354\227\260\355\225\234 \354\264\210\353\241\235\354\203\211\354\234\274\353\241\234 */\n"
"}\n"
"\n"
"QMessageBox QPushButton:pressed {\n"
"    background-color: #1e8449;        /* \355\201\264\353\246\255 \354\213\234 \353\215\224 \354\247\204\355\225\234 \354\264\210\353\241\235\354\203\211 */\n"
"}\n"
"\n"
"/* QLineEdit */\n"
"QLineEdit {\n"
"    background-color: #ecf0f1;        /* \353\260\260\352\262\275\354\235\204 \354\227\260\355\225\234 \355\232\214\354\203\211\354\234\274"
                        "\353\241\234 */\n"
"    border: 1px solid #27ae60;        /* \355\205\214\353\221\220\353\246\254\353\245\274 \354\244\221\352\260\204 \354\264\210\353\241\235\354\203\211\354\234\274\353\241\234 */\n"
"    border-radius: 4px;               /* \353\252\250\354\204\234\353\246\254 \354\225\275\352\260\204 \353\221\245\352\270\200\352\262\214 */\n"
"    padding: 3px 8px;                 /* \353\202\264\353\266\200 \354\227\254\353\260\261\354\235\204 \352\260\200\353\263\215\352\262\214 */\n"
"    font-size: 14px;                  /* \355\205\215\354\212\244\355\212\270 \355\201\254\352\270\260 */\n"
"    font-family: \"Malgun Gothic\";     /* \355\217\260\355\212\270 \354\204\244\354\240\225 */\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 1px solid #2ecc71;        /* \355\217\254\354\273\244\354\212\244 \354\213\234 \355\205\214\353\221\220\353\246\254\353\245\274 \354\227\260\355\225\234 \354\264\210\353\241\235\354\203\211\354\234\274\353\241\234 */\n"
"}\n"
"\n"
"/* QComboBox */\n"
"QComboBox {\n"
"    b"
                        "ackground-color: #ecf0f1;        /* \353\260\260\352\262\275\354\235\204 \354\227\260\355\225\234 \355\232\214\354\203\211\354\234\274\353\241\234 */\n"
"    border: 1px solid #27ae60;        /* \355\205\214\353\221\220\353\246\254\353\245\274 \354\244\221\352\260\204 \354\264\210\353\241\235\354\203\211\354\234\274\353\241\234 */\n"
"    border-radius: 4px;               /* \353\252\250\354\204\234\353\246\254 \354\225\275\352\260\204 \353\221\245\352\270\200\352\262\214 */\n"
"    padding: 3px 8px;                 /* \353\202\264\353\266\200 \354\227\254\353\260\261\354\235\204 \352\260\200\353\263\215\352\262\214 */\n"
"    font-size: 14px;                  /* \355\205\215\354\212\244\355\212\270 \355\201\254\352\270\260 */\n"
"    font-family: \"Malgun Gothic\";     /* \355\217\260\355\212\270 \354\204\244\354\240\225 */\n"
"}\n"
"\n"
"/* QComboBox\354\235\230 \353\223\234\353\241\255\353\213\244\354\232\264 \353\246\254\354\212\244\355\212\270 */\n"
"QComboBox QAbstractItemView {\n"
"    background-color:"
                        " #ffffff;            /* \353\223\234\353\241\255\353\213\244\354\232\264 \353\260\260\352\262\275\354\235\204 \355\235\260\354\203\211\354\234\274\353\241\234 */\n"
"    border: 1px solid #27ae60;            /* \353\223\234\353\241\255\353\213\244\354\232\264 \355\205\214\353\221\220\353\246\254 */\n"
"    selection-background-color: #2ecc71;  /* \354\204\240\355\203\235 \355\225\255\353\252\251 \353\260\260\352\262\275\354\235\204 \354\227\260\355\225\234 \354\264\210\353\241\235\354\203\211\354\234\274\353\241\234 */\n"
"    selection-color: #ffffff;             /* \354\204\240\355\203\235 \355\225\255\353\252\251 \355\205\215\354\212\244\355\212\270 \354\203\211\354\203\201 */\n"
"}"));
        gridLayout = new QGridLayout(Login);
        gridLayout->setObjectName("gridLayout");
        stackedWidget = new QStackedWidget(Login);
        stackedWidget->setObjectName("stackedWidget");
        login = new QWidget();
        login->setObjectName("login");
        gridLayout_2 = new QGridLayout(login);
        gridLayout_2->setObjectName("gridLayout_2");
        frame_2 = new QFrame(login);
        frame_2->setObjectName("frame_2");
        frame_2->setMinimumSize(QSize(0, 300));
        frame_2->setStyleSheet(QString::fromUtf8(""));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout = new QVBoxLayout(frame_2);
        verticalLayout->setObjectName("verticalLayout");
        frame_3 = new QFrame(frame_2);
        frame_3->setObjectName("frame_3");
        frame_3->setMinimumSize(QSize(0, 180));
        frame_3->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    border: none;\n"
"}"));
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_3 = new QGridLayout(frame_3);
        gridLayout_3->setObjectName("gridLayout_3");
        l_pwText = new QLineEdit(frame_3);
        l_pwText->setObjectName("l_pwText");
        l_pwText->setEchoMode(QLineEdit::EchoMode::Password);

        gridLayout_3->addWidget(l_pwText, 2, 2, 1, 1);

        label_2 = new QLabel(frame_3);
        label_2->setObjectName("label_2");
        QFont font;
        font.setPointSize(14);
        label_2->setFont(font);

        gridLayout_3->addWidget(label_2, 1, 1, 1, 1);

        loginBtn = new QPushButton(frame_3);
        loginBtn->setObjectName("loginBtn");
        loginBtn->setMinimumSize(QSize(0, 0));

        gridLayout_3->addWidget(loginBtn, 3, 2, 1, 1);

        l_idText = new QLineEdit(frame_3);
        l_idText->setObjectName("l_idText");
        l_idText->setMinimumSize(QSize(0, 0));

        gridLayout_3->addWidget(l_idText, 1, 2, 1, 1);

        label_3 = new QLabel(frame_3);
        label_3->setObjectName("label_3");
        label_3->setFont(font);

        gridLayout_3->addWidget(label_3, 2, 1, 1, 1);

        login_client_choice = new QComboBox(frame_3);
        login_client_choice->addItem(QString());
        login_client_choice->addItem(QString());
        login_client_choice->addItem(QString());
        login_client_choice->setObjectName("login_client_choice");
        login_client_choice->setMinimumSize(QSize(0, 30));

        gridLayout_3->addWidget(login_client_choice, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 2, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 2, 0, 1, 1);


        verticalLayout->addWidget(frame_3);

        frame_4 = new QFrame(frame_2);
        frame_4->setObjectName("frame_4");
        frame_4->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    border: none;\n"
"}"));
        frame_4->setFrameShape(QFrame::Shape::StyledPanel);
        frame_4->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout = new QHBoxLayout(frame_4);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        toSignUpBtn = new QPushButton(frame_4);
        toSignUpBtn->setObjectName("toSignUpBtn");
        toSignUpBtn->setMinimumSize(QSize(150, 0));

        horizontalLayout->addWidget(toSignUpBtn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout->addWidget(frame_4);


        gridLayout_2->addWidget(frame_2, 1, 0, 1, 1);

        frame = new QFrame(login);
        frame->setObjectName("frame");
        frame->setMinimumSize(QSize(0, 200));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName("verticalLayout_2");
        title_label = new QLabel(frame);
        title_label->setObjectName("title_label");
        QFont font1;
        font1.setPointSize(32);
        font1.setBold(true);
        title_label->setFont(font1);
        title_label->setTextFormat(Qt::TextFormat::AutoText);
        title_label->setScaledContents(false);
        title_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(title_label);


        gridLayout_2->addWidget(frame, 0, 0, 1, 1);

        stackedWidget->addWidget(login);
        signup = new QWidget();
        signup->setObjectName("signup");
        verticalLayout_3 = new QVBoxLayout(signup);
        verticalLayout_3->setObjectName("verticalLayout_3");
        frame_5 = new QFrame(signup);
        frame_5->setObjectName("frame_5");
        frame_5->setMinimumSize(QSize(0, 0));
        frame_5->setFrameShape(QFrame::Shape::StyledPanel);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_5 = new QVBoxLayout(frame_5);
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_4 = new QLabel(frame_5);
        label_4->setObjectName("label_4");
        QFont font2;
        font2.setPointSize(20);
        font2.setBold(true);
        label_4->setFont(font2);
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_5->addWidget(label_4);


        verticalLayout_3->addWidget(frame_5);

        frame_6 = new QFrame(signup);
        frame_6->setObjectName("frame_6");
        frame_6->setMinimumSize(QSize(0, 450));
        frame_6->setFrameShape(QFrame::Shape::StyledPanel);
        frame_6->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_4 = new QVBoxLayout(frame_6);
        verticalLayout_4->setObjectName("verticalLayout_4");
        frame_7 = new QFrame(frame_6);
        frame_7->setObjectName("frame_7");
        frame_7->setMinimumSize(QSize(0, 300));
        frame_7->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    border: none;\n"
"}"));
        frame_7->setFrameShape(QFrame::Shape::StyledPanel);
        frame_7->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_4 = new QGridLayout(frame_7);
        gridLayout_4->setObjectName("gridLayout_4");
        label_7 = new QLabel(frame_7);
        label_7->setObjectName("label_7");
        QFont font3;
        font3.setPointSize(13);
        label_7->setFont(font3);
        label_7->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout_4->addWidget(label_7, 5, 1, 1, 1);

        idDupChkText = new QLabel(frame_7);
        idDupChkText->setObjectName("idDupChkText");
        idDupChkText->setMaximumSize(QSize(16777215, 20));
        idDupChkText->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	margin: 0;\n"
"}"));

        gridLayout_4->addWidget(idDupChkText, 2, 2, 1, 1);

        idDupChkBtn = new QPushButton(frame_7);
        idDupChkBtn->setObjectName("idDupChkBtn");

        gridLayout_4->addWidget(idDupChkBtn, 1, 3, 1, 1);

        label_5 = new QLabel(frame_7);
        label_5->setObjectName("label_5");
        label_5->setFont(font3);
        label_5->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout_4->addWidget(label_5, 1, 1, 1, 1);

        s_pNumText = new QLineEdit(frame_7);
        s_pNumText->setObjectName("s_pNumText");

        gridLayout_4->addWidget(s_pNumText, 5, 2, 1, 1);

        label_6 = new QLabel(frame_7);
        label_6->setObjectName("label_6");
        label_6->setFont(font3);
        label_6->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout_4->addWidget(label_6, 4, 1, 1, 1);

        s_idText = new QLineEdit(frame_7);
        s_idText->setObjectName("s_idText");
        s_idText->setMinimumSize(QSize(180, 0));
        s_idText->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(s_idText, 1, 2, 1, 1);

        s_pwText = new QLineEdit(frame_7);
        s_pwText->setObjectName("s_pwText");

        gridLayout_4->addWidget(s_pwText, 4, 2, 1, 1);

        signUp_client_choice = new QComboBox(frame_7);
        signUp_client_choice->addItem(QString());
        signUp_client_choice->addItem(QString());
        signUp_client_choice->setObjectName("signUp_client_choice");
        signUp_client_choice->setMinimumSize(QSize(0, 30));

        gridLayout_4->addWidget(signUp_client_choice, 0, 2, 1, 1);

        signUpBtn = new QPushButton(frame_7);
        signUpBtn->setObjectName("signUpBtn");

        gridLayout_4->addWidget(signUpBtn, 8, 2, 1, 1);

        pnumDupChkBtn = new QPushButton(frame_7);
        pnumDupChkBtn->setObjectName("pnumDupChkBtn");

        gridLayout_4->addWidget(pnumDupChkBtn, 5, 3, 1, 1);

        pnumDupChkText = new QLabel(frame_7);
        pnumDupChkText->setObjectName("pnumDupChkText");
        pnumDupChkText->setMaximumSize(QSize(16777215, 20));

        gridLayout_4->addWidget(pnumDupChkText, 6, 2, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_5, 5, 0, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_6, 5, 5, 1, 1);


        verticalLayout_4->addWidget(frame_7);

        frame_8 = new QFrame(frame_6);
        frame_8->setObjectName("frame_8");
        frame_8->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    border: none;\n"
"}"));
        frame_8->setFrameShape(QFrame::Shape::StyledPanel);
        frame_8->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_8);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_9);

        backBtn = new QPushButton(frame_8);
        backBtn->setObjectName("backBtn");
        backBtn->setMinimumSize(QSize(150, 40));

        horizontalLayout_2->addWidget(backBtn);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_10);


        verticalLayout_4->addWidget(frame_8);


        verticalLayout_3->addWidget(frame_6);

        stackedWidget->addWidget(signup);

        gridLayout->addWidget(stackedWidget, 0, 1, 1, 1);


        retranslateUi(Login);
        QObject::connect(l_pwText, &QLineEdit::returnPressed, loginBtn, qOverload<>(&QPushButton::click));

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("Login", "\354\225\204\354\235\264\353\224\224", nullptr));
        loginBtn->setText(QCoreApplication::translate("Login", "\353\241\234\352\267\270\354\235\270", nullptr));
        label_3->setText(QCoreApplication::translate("Login", "\353\271\204\353\260\200\353\262\210\355\230\270", nullptr));
        login_client_choice->setItemText(0, QCoreApplication::translate("Login", "\354\235\274\353\260\230 \354\234\240\354\240\200", nullptr));
        login_client_choice->setItemText(1, QCoreApplication::translate("Login", "\352\260\200\352\262\214", nullptr));
        login_client_choice->setItemText(2, QCoreApplication::translate("Login", "\353\235\274\354\235\264\353\215\224", nullptr));

        toSignUpBtn->setText(QCoreApplication::translate("Login", "\355\232\214\354\233\220\352\260\200\354\236\205", nullptr));
        title_label->setText(QCoreApplication::translate("Login", "\352\261\260\352\270\260\354\232\224", nullptr));
        label_4->setText(QCoreApplication::translate("Login", "\355\232\214\354\233\220 \352\260\200\354\236\205", nullptr));
        label_7->setText(QCoreApplication::translate("Login", "\355\234\264\353\214\200\355\217\260 \353\262\210\355\230\270 ", nullptr));
        idDupChkText->setText(QString());
        idDupChkBtn->setText(QCoreApplication::translate("Login", "\354\244\221\353\263\265 \355\231\225\354\235\270", nullptr));
        label_5->setText(QCoreApplication::translate("Login", "\354\225\204\354\235\264\353\224\224 ", nullptr));
        label_6->setText(QCoreApplication::translate("Login", " \353\271\204\353\260\200\353\262\210\355\230\270 ", nullptr));
        signUp_client_choice->setItemText(0, QCoreApplication::translate("Login", "\354\235\274\353\260\230 \354\234\240\354\240\200", nullptr));
        signUp_client_choice->setItemText(1, QCoreApplication::translate("Login", "\353\235\274\354\235\264\353\215\224", nullptr));

        signUpBtn->setText(QCoreApplication::translate("Login", "\355\232\214\354\233\220\352\260\200\354\236\205", nullptr));
        pnumDupChkBtn->setText(QCoreApplication::translate("Login", "\354\244\221\353\263\265 \355\231\225\354\235\270", nullptr));
        pnumDupChkText->setText(QString());
        backBtn->setText(QCoreApplication::translate("Login", "\353\202\230\352\260\200\352\270\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
