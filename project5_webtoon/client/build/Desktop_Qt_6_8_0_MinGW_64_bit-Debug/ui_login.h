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
    QSpacerItem *horizontalSpacer;
    QLineEdit *l_idText;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *loginBtn;
    QLineEdit *l_pwText;
    QLabel *label_3;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout;
    QPushButton *toSearchIdBtn;
    QPushButton *toSearchPwBtn;
    QPushButton *toSignUpBtn;
    QFrame *frame;
    QGridLayout *gridLayout_9;
    QLabel *label;
    QWidget *signup;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_5;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_4;
    QFrame *frame_6;
    QVBoxLayout *verticalLayout_4;
    QFrame *frame_7;
    QGridLayout *gridLayout_4;
    QLabel *label_8;
    QLabel *label_5;
    QLabel *label_7;
    QLabel *pnumDupChkText;
    QPushButton *signUpBtn;
    QPushButton *idDupChkBtn;
    QLineEdit *s_emailText;
    QLabel *label_6;
    QLineEdit *s_pNumText;
    QLabel *idDupChkText;
    QPushButton *pnumDupChkBtn;
    QLineEdit *s_idText;
    QLineEdit *s_pwText;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_5;
    QFrame *frame_8;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *backBtn;
    QSpacerItem *horizontalSpacer_10;
    QWidget *idsearch;
    QVBoxLayout *verticalLayout_8;
    QFrame *frame_9;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_9;
    QFrame *frame_10;
    QVBoxLayout *verticalLayout_7;
    QFrame *frame_11;
    QGridLayout *gridLayout_5;
    QSpacerItem *verticalSpacer_3;
    QPushButton *idSearchBtn;
    QLabel *label_10;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *i_pNumText;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_3;
    QFrame *frame_17;
    QGridLayout *gridLayout_7;
    QLabel *idShowText;
    QFrame *frame_12;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *backBtn_2;
    QSpacerItem *horizontalSpacer_12;
    QWidget *pwsearch;
    QVBoxLayout *verticalLayout_11;
    QFrame *frame_13;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_12;
    QFrame *frame_14;
    QVBoxLayout *verticalLayout_10;
    QFrame *frame_15;
    QGridLayout *gridLayout_6;
    QLabel *label_15;
    QPushButton *pwSearchBtn;
    QLineEdit *p_emailText;
    QLineEdit *p_pNumText;
    QLineEdit *p_idText;
    QLabel *label_13;
    QLabel *label_14;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *horizontalSpacer_7;
    QFrame *frame_18;
    QGridLayout *gridLayout_8;
    QLabel *pwShowText;
    QFrame *frame_16;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_13;
    QPushButton *backBtn_3;
    QSpacerItem *horizontalSpacer_14;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(846, 715);
        Login->setStyleSheet(QString::fromUtf8("QWidget{\n"
"	font-family: 'Roboto';\n"
"}\n"
"\n"
"\n"
"QLabel {\n"
"    padding: 5px;\n"
"    margin: 0px;\n"
"    font-size: 16px;\n"
"	font-weight: bold;\n"
"	color:black;\n"
"    qproperty-alignment: AlignVCenter; /* \354\204\270\353\241\234 \354\244\221\354\225\231 \354\240\225\353\240\254 */\n"
"}\n"
"\n"
"\n"
"\n"
"/* \353\262\204\355\212\274 (\354\244\221\353\263\265 \355\231\225\354\235\270, \355\232\214\354\233\220\352\260\200\354\236\205, \353\241\234\352\267\270\354\235\270, \353\202\230\352\260\200\352\270\260 \353\223\261) */\n"
"QPushButton {\n"
"    background-color: #3498db; /* \355\214\214\353\236\200\354\203\211 */\n"
"    color: white;\n"
"    border: 2px solid #2980b9;\n"
"    border-radius: 10px;\n"
"    padding: 8px 15px;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2980b9; /* \353\247\210\354\232\260\354\212\244\353\245\274 \354\230\254\353\240\270\354\235\204 \353\225\214 \353\215\224 \354\247\231\354\235\200 \355\214"
                        "\214\353\236\200\354\203\211 */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #1f618d; /* \355\201\264\353\246\255\355\226\210\354\235\204 \353\225\214 \353\215\224 \354\226\264\353\221\220\354\232\264 \355\214\214\353\236\200\354\203\211 */\n"
"    border: 2px solid #1f618d;\n"
"}\n"
"\n"
"/* \354\236\205\353\240\245 \355\225\204\353\223\234 (ID, \353\271\204\353\260\200\353\262\210\355\230\270, \355\234\264\353\214\200\355\217\260 \353\262\210\355\230\270, \354\235\264\353\251\224\354\235\274) */\n"
"QLineEdit {\n"
"    background-color: #ffffff;\n"
"    border: 2px solid #dcdcdc;\n"
"    border-radius: 8px;\n"
"    padding: 6px 10px;\n"
"    font-size: 14px;\n"
"	color: black;\n"
"	font-weight: bold;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border-color: #3498db; /* \355\217\254\354\273\244\354\212\244 \354\213\234 \355\214\214\353\236\200\354\203\211 \355\205\214\353\221\220\353\246\254 */\n"
"    outline: none;\n"
"}\n"
"\n"
"/* \355\224\204\353\240\210\354\236\204 \355\205\214\353\221\220"
                        "\353\246\254 */\n"
"QFrame {\n"
"    border: 3px solid black;\n"
"    border-radius: 12px;\n"
"    padding: 10px;\n"
"    background-color: #ffffff;\n"
"	border-color: #1f618d;\n"
"}\n"
"\n"
"\n"
"\n"
"/* \353\202\230\352\260\200\352\270\260 \353\262\204\355\212\274 */\n"
"QPushButton#backBtn {\n"
"    background-color: #e74c3c; /* \353\271\250\352\260\204\354\203\211 */\n"
"    border: 2px solid #c0392b;\n"
"}\n"
"\n"
"QPushButton#backBtn_2{\n"
"    background-color: #e74c3c; /* \353\271\250\352\260\204\354\203\211 */\n"
"    border: 2px solid #c0392b;\n"
"}\n"
"\n"
"QPushButton#backBtn_3 {\n"
"    background-color: #e74c3c; /* \353\271\250\352\260\204\354\203\211 */\n"
"    border: 2px solid #c0392b;\n"
"}\n"
"\n"
"QPushButton#backBtn:hover {\n"
"    background-color: #c0392b;\n"
"}\n"
"\n"
"QPushButton#backBtn:pressed {\n"
"    background-color: #96281b;\n"
"}\n"
"\n"
"QPushButton#backBtn_2:hover {\n"
"    background-color: #c0392b;\n"
"}\n"
"\n"
"QPushButton#backBtn_2:pressed {\n"
"    background-color: #9"
                        "6281b;\n"
"}\n"
"\n"
"QPushButton#backBtn_3:hover {\n"
"    background-color: #c0392b;\n"
"}\n"
"\n"
"QPushButton#backBtn_3:pressed {\n"
"    background-color: #96281b;\n"
"}\n"
"\n"
"QMessageBox {\n"
"    background-color: #ffffff;           /* \355\214\235\354\227\205 \353\260\260\352\262\275\354\235\204 \355\235\260\354\203\211\354\234\274\353\241\234 */\n"
"    border: 2px solid #3b75b5;           /* \355\214\214\353\236\200\354\203\211 \355\205\214\353\221\220\353\246\254 */\n"
"    border-radius: 10px;                 /* \353\221\245\352\267\274 \353\252\250\354\204\234\353\246\254 */\n"
"}\n"
"\n"
"QMessageBox QLabel {\n"
"    color: #000000;                      /* \353\251\224\354\213\234\354\247\200 \355\205\215\354\212\244\355\212\270 \354\203\211\354\203\201 (\352\262\200\354\240\225) */\n"
"    font-family: \"\353\247\221\354\235\200 \352\263\240\353\224\225\";              /* \355\225\234\352\270\200 \355\217\260\355\212\270 \354\240\201\354\232\251 */\n"
"    font-size: 14pt;                    "
                        " /* \355\205\215\354\212\244\355\212\270 \355\201\254\352\270\260 */\n"
"    font-weight: bold;                   /* \355\205\215\354\212\244\355\212\270 \352\265\265\352\262\214 */\n"
"}\n"
"\n"
"QMessageBox QPushButton {\n"
"    background-color: #3b75b5;           /* \353\262\204\355\212\274 \353\260\260\352\262\275\354\203\211 (\355\214\214\353\236\200\354\203\211) */\n"
"    color: white;                        /* \353\262\204\355\212\274 \355\205\215\354\212\244\355\212\270 \354\203\211\354\203\201 (\355\235\260\354\203\211) */\n"
"    font-family: \"\353\247\221\354\235\200 \352\263\240\353\224\225\";              /* \353\262\204\355\212\274 \355\217\260\355\212\270 \354\204\244\354\240\225 */\n"
"    font-size: 12pt;                     /* \353\262\204\355\212\274 \355\205\215\354\212\244\355\212\270 \355\201\254\352\270\260 */\n"
"    border-radius: 5px;                  /* \353\262\204\355\212\274 \353\252\250\354\204\234\353\246\254\353\245\274 \353\221\245\352\270\200\352\262\214 */\n"
"    padding"
                        ": 5px 15px;                   /* \353\262\204\355\212\274 \353\202\264\353\266\200 \354\227\254\353\260\261 */\n"
"}\n"
"\n"
"QMessageBox QPushButton:hover {\n"
"    background-color: #619edc;           /* \353\262\204\355\212\274\354\227\220 \353\247\210\354\232\260\354\212\244\353\245\274 \354\230\254\353\240\270\354\235\204 \353\225\214 \353\260\260\352\262\275\354\203\211 */\n"
"}\n"
"\n"
"QMessageBox QPushButton:pressed {\n"
"    background-color: #2a5a84;           /* \353\262\204\355\212\274\354\235\204 \353\210\214\353\240\200\354\235\204 \353\225\214 \353\260\260\352\262\275\354\203\211 */\n"
"}\n"
""));
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
        frame_2->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    border: none;\n"
"}\n"
""));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout = new QVBoxLayout(frame_2);
        verticalLayout->setObjectName("verticalLayout");
        frame_3 = new QFrame(frame_2);
        frame_3->setObjectName("frame_3");
        frame_3->setMinimumSize(QSize(0, 180));
        frame_3->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    border: none;\n"
"}\n"
"\n"
"QLabel{\n"
"	qproperty-alignment: 'AlignRight';\n"
"}"));
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_3 = new QGridLayout(frame_3);
        gridLayout_3->setObjectName("gridLayout_3");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 0, 3, 1, 1);

        l_idText = new QLineEdit(frame_3);
        l_idText->setObjectName("l_idText");
        l_idText->setMinimumSize(QSize(0, 0));

        gridLayout_3->addWidget(l_idText, 0, 2, 1, 1);

        label_2 = new QLabel(frame_3);
        label_2->setObjectName("label_2");
        QFont font;
        font.setFamilies({QString::fromUtf8("Roboto")});
        font.setBold(true);
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(label_2, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        loginBtn = new QPushButton(frame_3);
        loginBtn->setObjectName("loginBtn");
        loginBtn->setMinimumSize(QSize(0, 0));

        gridLayout_3->addWidget(loginBtn, 2, 2, 1, 1);

        l_pwText = new QLineEdit(frame_3);
        l_pwText->setObjectName("l_pwText");
        l_pwText->setEchoMode(QLineEdit::EchoMode::Password);

        gridLayout_3->addWidget(l_pwText, 1, 2, 1, 1);

        label_3 = new QLabel(frame_3);
        label_3->setObjectName("label_3");
        label_3->setFont(font);
        label_3->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(label_3, 1, 1, 1, 1);


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
        toSearchIdBtn = new QPushButton(frame_4);
        toSearchIdBtn->setObjectName("toSearchIdBtn");

        horizontalLayout->addWidget(toSearchIdBtn);

        toSearchPwBtn = new QPushButton(frame_4);
        toSearchPwBtn->setObjectName("toSearchPwBtn");

        horizontalLayout->addWidget(toSearchPwBtn);

        toSignUpBtn = new QPushButton(frame_4);
        toSignUpBtn->setObjectName("toSignUpBtn");

        horizontalLayout->addWidget(toSignUpBtn);


        verticalLayout->addWidget(frame_4);


        gridLayout_2->addWidget(frame_2, 1, 0, 1, 1);

        frame = new QFrame(login);
        frame->setObjectName("frame");
        frame->setMinimumSize(QSize(0, 250));
        frame->setStyleSheet(QString::fromUtf8(""));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_9 = new QGridLayout(frame);
        gridLayout_9->setObjectName("gridLayout_9");
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	font-size: 60px;\n"
"	qproperty-alignment: 'AlignCenter';\n"
"	border: none;\n"
"}\n"
""));
        label->setTextFormat(Qt::TextFormat::AutoText);
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_9->addWidget(label, 0, 0, 1, 1);


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
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	font-size: 30px;\n"
"	qproperty-alignment: 'AlignCenter';\n"
"	border: none;\n"
"}"));
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_5->addWidget(label_4);


        verticalLayout_3->addWidget(frame_5);

        frame_6 = new QFrame(signup);
        frame_6->setObjectName("frame_6");
        frame_6->setMinimumSize(QSize(0, 450));
        frame_6->setStyleSheet(QString::fromUtf8("QFrame {\n"
"	border: none;\n"
"	padding-left: 0px;\n"
"	padding-right: 0px;\n"
"}"));
        frame_6->setFrameShape(QFrame::Shape::StyledPanel);
        frame_6->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_4 = new QVBoxLayout(frame_6);
        verticalLayout_4->setObjectName("verticalLayout_4");
        frame_7 = new QFrame(frame_6);
        frame_7->setObjectName("frame_7");
        frame_7->setMinimumSize(QSize(0, 300));
        frame_7->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    border: none;\n"
"}\n"
"QLabel{\n"
"	qproperty-alignment: 'AlignRight';\n"
"}"));
        frame_7->setFrameShape(QFrame::Shape::StyledPanel);
        frame_7->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_4 = new QGridLayout(frame_7);
        gridLayout_4->setObjectName("gridLayout_4");
        label_8 = new QLabel(frame_7);
        label_8->setObjectName("label_8");
        label_8->setFont(font);
        label_8->setAlignment(Qt::AlignmentFlag::AlignRight);

        gridLayout_4->addWidget(label_8, 3, 2, 1, 1);

        label_5 = new QLabel(frame_7);
        label_5->setObjectName("label_5");
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignmentFlag::AlignRight);

        gridLayout_4->addWidget(label_5, 0, 2, 1, 1);

        label_7 = new QLabel(frame_7);
        label_7->setObjectName("label_7");
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignmentFlag::AlignRight);

        gridLayout_4->addWidget(label_7, 2, 2, 1, 1);

        pnumDupChkText = new QLabel(frame_7);
        pnumDupChkText->setObjectName("pnumDupChkText");
        pnumDupChkText->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	padding-left: 0px; \n"
"    padding-right: 0px; \n"
"	margin-left: 0px;\n"
"	margin-right: 0px;\n"
"}"));

        gridLayout_4->addWidget(pnumDupChkText, 2, 6, 1, 1);

        signUpBtn = new QPushButton(frame_7);
        signUpBtn->setObjectName("signUpBtn");

        gridLayout_4->addWidget(signUpBtn, 4, 3, 1, 1);

        idDupChkBtn = new QPushButton(frame_7);
        idDupChkBtn->setObjectName("idDupChkBtn");
        idDupChkBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"font-size: 13px;\n"
"margin:1px;\n"
"}\n"
""));

        gridLayout_4->addWidget(idDupChkBtn, 0, 4, 1, 1);

        s_emailText = new QLineEdit(frame_7);
        s_emailText->setObjectName("s_emailText");

        gridLayout_4->addWidget(s_emailText, 3, 3, 1, 1);

        label_6 = new QLabel(frame_7);
        label_6->setObjectName("label_6");
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignmentFlag::AlignRight);

        gridLayout_4->addWidget(label_6, 1, 2, 1, 1);

        s_pNumText = new QLineEdit(frame_7);
        s_pNumText->setObjectName("s_pNumText");

        gridLayout_4->addWidget(s_pNumText, 2, 3, 1, 1);

        idDupChkText = new QLabel(frame_7);
        idDupChkText->setObjectName("idDupChkText");
        idDupChkText->setMinimumSize(QSize(150, 0));
        idDupChkText->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	padding-left: 0px; \n"
"    padding-right: 0px; \n"
"	margin-left: 0px;\n"
"	margin-right: 0px;\n"
"}"));

        gridLayout_4->addWidget(idDupChkText, 0, 6, 1, 1);

        pnumDupChkBtn = new QPushButton(frame_7);
        pnumDupChkBtn->setObjectName("pnumDupChkBtn");

        gridLayout_4->addWidget(pnumDupChkBtn, 2, 4, 1, 1);

        s_idText = new QLineEdit(frame_7);
        s_idText->setObjectName("s_idText");
        s_idText->setMinimumSize(QSize(190, 0));
        s_idText->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(s_idText, 0, 3, 1, 1);

        s_pwText = new QLineEdit(frame_7);
        s_pwText->setObjectName("s_pwText");

        gridLayout_4->addWidget(s_pwText, 1, 3, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_6, 4, 6, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_5, 2, 1, 1, 1);


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
        idsearch = new QWidget();
        idsearch->setObjectName("idsearch");
        verticalLayout_8 = new QVBoxLayout(idsearch);
        verticalLayout_8->setObjectName("verticalLayout_8");
        frame_9 = new QFrame(idsearch);
        frame_9->setObjectName("frame_9");
        frame_9->setMinimumSize(QSize(0, 197));
        frame_9->setFrameShape(QFrame::Shape::StyledPanel);
        frame_9->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_6 = new QVBoxLayout(frame_9);
        verticalLayout_6->setObjectName("verticalLayout_6");
        label_9 = new QLabel(frame_9);
        label_9->setObjectName("label_9");
        label_9->setFont(font);
        label_9->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	font-size: 30px;\n"
"	qproperty-alignment: 'AlignCenter';\n"
"	border: none;\n"
"}"));
        label_9->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_6->addWidget(label_9);


        verticalLayout_8->addWidget(frame_9);

        frame_10 = new QFrame(idsearch);
        frame_10->setObjectName("frame_10");
        frame_10->setMinimumSize(QSize(0, 450));
        frame_10->setStyleSheet(QString::fromUtf8("QFrame {\n"
"	border: none;\n"
"}"));
        frame_10->setFrameShape(QFrame::Shape::StyledPanel);
        frame_10->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_7 = new QVBoxLayout(frame_10);
        verticalLayout_7->setObjectName("verticalLayout_7");
        frame_11 = new QFrame(frame_10);
        frame_11->setObjectName("frame_11");
        frame_11->setMinimumSize(QSize(0, 0));
        frame_11->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    border: none;\n"
"}"));
        frame_11->setFrameShape(QFrame::Shape::StyledPanel);
        frame_11->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_5 = new QGridLayout(frame_11);
        gridLayout_5->setObjectName("gridLayout_5");
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_5->addItem(verticalSpacer_3, 3, 1, 1, 1);

        idSearchBtn = new QPushButton(frame_11);
        idSearchBtn->setObjectName("idSearchBtn");

        gridLayout_5->addWidget(idSearchBtn, 2, 1, 1, 1);

        label_10 = new QLabel(frame_11);
        label_10->setObjectName("label_10");
        label_10->setFont(font);
        label_10->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	qproperty-alignment: 'AlignRight';\n"
"}"));
        label_10->setAlignment(Qt::AlignmentFlag::AlignRight);

        gridLayout_5->addWidget(label_10, 1, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_4, 2, 0, 1, 1);

        i_pNumText = new QLineEdit(frame_11);
        i_pNumText->setObjectName("i_pNumText");

        gridLayout_5->addWidget(i_pNumText, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_5->addItem(verticalSpacer, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_3, 2, 2, 1, 1);


        verticalLayout_7->addWidget(frame_11);

        frame_17 = new QFrame(frame_10);
        frame_17->setObjectName("frame_17");
        frame_17->setMinimumSize(QSize(0, 70));
        frame_17->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    border: none;\n"
"}"));
        frame_17->setFrameShape(QFrame::Shape::StyledPanel);
        frame_17->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_7 = new QGridLayout(frame_17);
        gridLayout_7->setObjectName("gridLayout_7");
        idShowText = new QLabel(frame_17);
        idShowText->setObjectName("idShowText");
        idShowText->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_7->addWidget(idShowText, 0, 0, 1, 1);


        verticalLayout_7->addWidget(frame_17);

        frame_12 = new QFrame(frame_10);
        frame_12->setObjectName("frame_12");
        frame_12->setMinimumSize(QSize(0, 123));
        frame_12->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    border: none;\n"
"}"));
        frame_12->setFrameShape(QFrame::Shape::StyledPanel);
        frame_12->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_12);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_11);

        backBtn_2 = new QPushButton(frame_12);
        backBtn_2->setObjectName("backBtn_2");
        backBtn_2->setMinimumSize(QSize(150, 40));

        horizontalLayout_3->addWidget(backBtn_2);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_12);


        verticalLayout_7->addWidget(frame_12);


        verticalLayout_8->addWidget(frame_10);

        stackedWidget->addWidget(idsearch);
        pwsearch = new QWidget();
        pwsearch->setObjectName("pwsearch");
        verticalLayout_11 = new QVBoxLayout(pwsearch);
        verticalLayout_11->setObjectName("verticalLayout_11");
        frame_13 = new QFrame(pwsearch);
        frame_13->setObjectName("frame_13");
        frame_13->setMinimumSize(QSize(0, 197));
        frame_13->setFrameShape(QFrame::Shape::StyledPanel);
        frame_13->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_9 = new QVBoxLayout(frame_13);
        verticalLayout_9->setObjectName("verticalLayout_9");
        label_12 = new QLabel(frame_13);
        label_12->setObjectName("label_12");
        label_12->setFont(font);
        label_12->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	font-size: 30px;\n"
"	qproperty-alignment: 'AlignCenter';\n"
"	border: none;\n"
"}"));
        label_12->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_9->addWidget(label_12);


        verticalLayout_11->addWidget(frame_13);

        frame_14 = new QFrame(pwsearch);
        frame_14->setObjectName("frame_14");
        frame_14->setMinimumSize(QSize(0, 450));
        frame_14->setStyleSheet(QString::fromUtf8("QFrame {\n"
"	border: none;\n"
"}"));
        frame_14->setFrameShape(QFrame::Shape::StyledPanel);
        frame_14->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_10 = new QVBoxLayout(frame_14);
        verticalLayout_10->setObjectName("verticalLayout_10");
        frame_15 = new QFrame(frame_14);
        frame_15->setObjectName("frame_15");
        frame_15->setMinimumSize(QSize(0, 230));
        frame_15->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    border: none;\n"
"}\n"
"\n"
"QLabel{\n"
"	qproperty-alignment: 'AlignRight';\n"
"}"));
        frame_15->setFrameShape(QFrame::Shape::StyledPanel);
        frame_15->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_6 = new QGridLayout(frame_15);
        gridLayout_6->setObjectName("gridLayout_6");
        label_15 = new QLabel(frame_15);
        label_15->setObjectName("label_15");
        label_15->setFont(font);
        label_15->setAlignment(Qt::AlignmentFlag::AlignRight);

        gridLayout_6->addWidget(label_15, 0, 1, 1, 1);

        pwSearchBtn = new QPushButton(frame_15);
        pwSearchBtn->setObjectName("pwSearchBtn");

        gridLayout_6->addWidget(pwSearchBtn, 3, 2, 1, 1);

        p_emailText = new QLineEdit(frame_15);
        p_emailText->setObjectName("p_emailText");

        gridLayout_6->addWidget(p_emailText, 2, 2, 1, 1);

        p_pNumText = new QLineEdit(frame_15);
        p_pNumText->setObjectName("p_pNumText");

        gridLayout_6->addWidget(p_pNumText, 1, 2, 1, 1);

        p_idText = new QLineEdit(frame_15);
        p_idText->setObjectName("p_idText");

        gridLayout_6->addWidget(p_idText, 0, 2, 1, 1);

        label_13 = new QLabel(frame_15);
        label_13->setObjectName("label_13");
        label_13->setFont(font);
        label_13->setStyleSheet(QString::fromUtf8(""));
        label_13->setAlignment(Qt::AlignmentFlag::AlignRight);

        gridLayout_6->addWidget(label_13, 1, 1, 1, 1);

        label_14 = new QLabel(frame_15);
        label_14->setObjectName("label_14");
        label_14->setFont(font);
        label_14->setAlignment(Qt::AlignmentFlag::AlignRight);

        gridLayout_6->addWidget(label_14, 2, 1, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_8, 3, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_7, 3, 3, 1, 1);


        verticalLayout_10->addWidget(frame_15);

        frame_18 = new QFrame(frame_14);
        frame_18->setObjectName("frame_18");
        frame_18->setMinimumSize(QSize(0, 70));
        frame_18->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    border: none;\n"
"	padding: 0;\n"
"}"));
        frame_18->setFrameShape(QFrame::Shape::StyledPanel);
        frame_18->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_8 = new QGridLayout(frame_18);
        gridLayout_8->setObjectName("gridLayout_8");
        pwShowText = new QLabel(frame_18);
        pwShowText->setObjectName("pwShowText");
        pwShowText->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	padding: 0;\n"
"}"));
        pwShowText->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_8->addWidget(pwShowText, 0, 0, 1, 1);


        verticalLayout_10->addWidget(frame_18);

        frame_16 = new QFrame(frame_14);
        frame_16->setObjectName("frame_16");
        frame_16->setMinimumSize(QSize(0, 123));
        frame_16->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    border: none;\n"
"}"));
        frame_16->setFrameShape(QFrame::Shape::StyledPanel);
        frame_16->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_16);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_13);

        backBtn_3 = new QPushButton(frame_16);
        backBtn_3->setObjectName("backBtn_3");
        backBtn_3->setMinimumSize(QSize(150, 40));

        horizontalLayout_4->addWidget(backBtn_3);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_14);


        verticalLayout_10->addWidget(frame_16);


        verticalLayout_11->addWidget(frame_14);

        stackedWidget->addWidget(pwsearch);

        gridLayout->addWidget(stackedWidget, 0, 0, 1, 1);


        retranslateUi(Login);
        QObject::connect(s_emailText, &QLineEdit::returnPressed, signUpBtn, qOverload<>(&QPushButton::click));
        QObject::connect(i_pNumText, &QLineEdit::returnPressed, idSearchBtn, qOverload<>(&QPushButton::click));
        QObject::connect(p_emailText, &QLineEdit::returnPressed, pwSearchBtn, qOverload<>(&QPushButton::click));
        QObject::connect(l_pwText, &QLineEdit::returnPressed, loginBtn, qOverload<>(&QPushButton::click));

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Form", nullptr));
        l_idText->setText(QString());
        label_2->setText(QCoreApplication::translate("Login", "\354\225\204\354\235\264\353\224\224", nullptr));
        loginBtn->setText(QCoreApplication::translate("Login", "\353\241\234\352\267\270\354\235\270", nullptr));
        label_3->setText(QCoreApplication::translate("Login", "\353\271\204\353\260\200\353\262\210\355\230\270", nullptr));
        toSearchIdBtn->setText(QCoreApplication::translate("Login", "\354\225\204\354\235\264\353\224\224 \354\260\276\352\270\260", nullptr));
        toSearchPwBtn->setText(QCoreApplication::translate("Login", "\353\271\204\353\260\200\353\262\210\355\230\270 \354\260\276\352\270\260", nullptr));
        toSignUpBtn->setText(QCoreApplication::translate("Login", "\355\232\214\354\233\220\352\260\200\354\236\205", nullptr));
        label->setText(QCoreApplication::translate("Login", "T_T OON", nullptr));
        label_4->setText(QCoreApplication::translate("Login", "\355\232\214\354\233\220 \352\260\200\354\236\205", nullptr));
        label_8->setText(QCoreApplication::translate("Login", "\354\235\264\353\251\224\354\235\274 ", nullptr));
        label_5->setText(QCoreApplication::translate("Login", "\354\225\204\354\235\264\353\224\224 ", nullptr));
        label_7->setText(QCoreApplication::translate("Login", "\355\234\264\353\214\200\355\217\260 \353\262\210\355\230\270 ", nullptr));
        pnumDupChkText->setText(QString());
        signUpBtn->setText(QCoreApplication::translate("Login", "\355\232\214\354\233\220\352\260\200\354\236\205", nullptr));
        idDupChkBtn->setText(QCoreApplication::translate("Login", "\354\244\221\353\263\265 \355\231\225\354\235\270", nullptr));
        label_6->setText(QCoreApplication::translate("Login", " \353\271\204\353\260\200\353\262\210\355\230\270 ", nullptr));
        idDupChkText->setText(QString());
        pnumDupChkBtn->setText(QCoreApplication::translate("Login", "\354\244\221\353\263\265 \355\231\225\354\235\270", nullptr));
        backBtn->setText(QCoreApplication::translate("Login", "\353\202\230\352\260\200\352\270\260", nullptr));
        label_9->setText(QCoreApplication::translate("Login", "\354\225\204\354\235\264\353\224\224 \354\260\276\352\270\260", nullptr));
        idSearchBtn->setText(QCoreApplication::translate("Login", "\354\225\204\354\235\264\353\224\224 \354\260\276\352\270\260", nullptr));
        label_10->setText(QCoreApplication::translate("Login", "\355\234\264\353\214\200\355\217\260 \353\262\210\355\230\270", nullptr));
        idShowText->setText(QString());
        backBtn_2->setText(QCoreApplication::translate("Login", "\353\202\230\352\260\200\352\270\260", nullptr));
        label_12->setText(QCoreApplication::translate("Login", "\353\271\204\353\260\200\353\262\210\355\230\270 \354\260\276\352\270\260", nullptr));
        label_15->setText(QCoreApplication::translate("Login", "\354\225\204\354\235\264\353\224\224 ", nullptr));
        pwSearchBtn->setText(QCoreApplication::translate("Login", "\353\271\204\353\260\200\353\262\210\355\230\270 \354\260\276\352\270\260", nullptr));
        label_13->setText(QCoreApplication::translate("Login", "\355\234\264\353\214\200\355\217\260 \353\262\210\355\230\270", nullptr));
        label_14->setText(QCoreApplication::translate("Login", "\354\235\264\353\251\224\354\235\274", nullptr));
        pwShowText->setText(QString());
        backBtn_3->setText(QCoreApplication::translate("Login", "\353\202\230\352\260\200\352\270\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
