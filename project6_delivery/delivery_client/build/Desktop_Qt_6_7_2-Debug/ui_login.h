/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
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
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *l_pwText;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QPushButton *loginBtn;
    QLineEdit *l_idText;
    QLabel *label_3;
    QComboBox *login_client_choice;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout;
    QPushButton *toSignUpBtn;
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
    QLineEdit *s_pwText;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pnumDupChkBtn;
    QLabel *label_7;
    QPushButton *signUpBtn;
    QLabel *pnumDupChkText;
    QLabel *label_5;
    QLineEdit *s_idText;
    QLineEdit *s_pNumText;
    QLabel *idDupChkText;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_6;
    QPushButton *idDupChkBtn;
    QComboBox *signUp_client_choice;
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
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        l_pwText = new QLineEdit(frame_3);
        l_pwText->setObjectName("l_pwText");
        l_pwText->setEchoMode(QLineEdit::EchoMode::Password);

        gridLayout_3->addWidget(l_pwText, 2, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 1, 3, 1, 1);

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
        toSignUpBtn = new QPushButton(frame_4);
        toSignUpBtn->setObjectName("toSignUpBtn");

        horizontalLayout->addWidget(toSignUpBtn);


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
        font1.setPointSize(30);
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
        font2.setPointSize(15);
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
        s_pwText = new QLineEdit(frame_7);
        s_pwText->setObjectName("s_pwText");

        gridLayout_4->addWidget(s_pwText, 2, 2, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_5, 3, 0, 1, 1);

        pnumDupChkBtn = new QPushButton(frame_7);
        pnumDupChkBtn->setObjectName("pnumDupChkBtn");

        gridLayout_4->addWidget(pnumDupChkBtn, 3, 3, 1, 1);

        label_7 = new QLabel(frame_7);
        label_7->setObjectName("label_7");
        QFont font3;
        font3.setPointSize(13);
        label_7->setFont(font3);
        label_7->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout_4->addWidget(label_7, 3, 1, 1, 1);

        signUpBtn = new QPushButton(frame_7);
        signUpBtn->setObjectName("signUpBtn");

        gridLayout_4->addWidget(signUpBtn, 5, 2, 1, 1);

        pnumDupChkText = new QLabel(frame_7);
        pnumDupChkText->setObjectName("pnumDupChkText");

        gridLayout_4->addWidget(pnumDupChkText, 3, 5, 1, 1);

        label_5 = new QLabel(frame_7);
        label_5->setObjectName("label_5");
        label_5->setFont(font3);
        label_5->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout_4->addWidget(label_5, 1, 1, 1, 1);

        s_idText = new QLineEdit(frame_7);
        s_idText->setObjectName("s_idText");
        s_idText->setMinimumSize(QSize(180, 0));
        s_idText->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(s_idText, 1, 2, 1, 1);

        s_pNumText = new QLineEdit(frame_7);
        s_pNumText->setObjectName("s_pNumText");

        gridLayout_4->addWidget(s_pNumText, 3, 2, 1, 1);

        idDupChkText = new QLabel(frame_7);
        idDupChkText->setObjectName("idDupChkText");

        gridLayout_4->addWidget(idDupChkText, 1, 5, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_6, 3, 4, 1, 1);

        label_6 = new QLabel(frame_7);
        label_6->setObjectName("label_6");
        label_6->setFont(font3);
        label_6->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout_4->addWidget(label_6, 2, 1, 1, 1);

        idDupChkBtn = new QPushButton(frame_7);
        idDupChkBtn->setObjectName("idDupChkBtn");

        gridLayout_4->addWidget(idDupChkBtn, 1, 3, 1, 1);

        signUp_client_choice = new QComboBox(frame_7);
        signUp_client_choice->addItem(QString());
        signUp_client_choice->addItem(QString());
        signUp_client_choice->setObjectName("signUp_client_choice");
        signUp_client_choice->setMinimumSize(QSize(0, 30));

        gridLayout_4->addWidget(signUp_client_choice, 0, 2, 1, 1);


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
        QObject::connect(l_pwText, &QLineEdit::editingFinished, loginBtn, qOverload<>(&QPushButton::click));

        stackedWidget->setCurrentIndex(0);


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
        pnumDupChkBtn->setText(QCoreApplication::translate("Login", "\354\244\221\353\263\265 \355\231\225\354\235\270", nullptr));
        label_7->setText(QCoreApplication::translate("Login", "\355\234\264\353\214\200\355\217\260 \353\262\210\355\230\270 ", nullptr));
        signUpBtn->setText(QCoreApplication::translate("Login", "\355\232\214\354\233\220\352\260\200\354\236\205", nullptr));
        pnumDupChkText->setText(QString());
        label_5->setText(QCoreApplication::translate("Login", "\354\225\204\354\235\264\353\224\224 ", nullptr));
        idDupChkText->setText(QString());
        label_6->setText(QCoreApplication::translate("Login", " \353\271\204\353\260\200\353\262\210\355\230\270 ", nullptr));
        idDupChkBtn->setText(QCoreApplication::translate("Login", "\354\244\221\353\263\265 \355\231\225\354\235\270", nullptr));
        signUp_client_choice->setItemText(0, QCoreApplication::translate("Login", "\354\235\274\353\260\230 \354\234\240\354\240\200", nullptr));
        signUp_client_choice->setItemText(1, QCoreApplication::translate("Login", "\353\235\274\354\235\264\353\215\224", nullptr));

        backBtn->setText(QCoreApplication::translate("Login", "\353\202\230\352\260\200\352\270\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
