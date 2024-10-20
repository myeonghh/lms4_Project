/****************************************************************************
** Meta object code from reading C++ file 'login.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../login.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'login.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSLoginENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSLoginENDCLASS = QtMocHelpers::stringData(
    "Login",
    "user_info_signal",
    "",
    "type",
    "id",
    "pw",
    "phone_num",
    "email",
    "login_success_signal",
    "login_user_id",
    "signUp_operate",
    "info",
    "login_operate",
    "idSearch_operate",
    "pwSearch_operate",
    "pageMove",
    "page",
    "login",
    "idDupChk",
    "pnumDupChk",
    "signUp",
    "idSearch",
    "pwSearch",
    "idText_change",
    "pNumText_change"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSLoginENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    5,  128,    2, 0x06,    1 /* Public */,
       1,    4,  139,    2, 0x26,    7 /* Public | MethodCloned */,
       1,    3,  148,    2, 0x26,   12 /* Public | MethodCloned */,
       1,    2,  155,    2, 0x26,   16 /* Public | MethodCloned */,
       1,    1,  160,    2, 0x26,   19 /* Public | MethodCloned */,
       8,    1,  163,    2, 0x06,   21 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      10,    1,  166,    2, 0x0a,   23 /* Public */,
      12,    1,  169,    2, 0x0a,   25 /* Public */,
      13,    1,  172,    2, 0x0a,   27 /* Public */,
      14,    1,  175,    2, 0x0a,   29 /* Public */,
      15,    1,  178,    2, 0x08,   31 /* Private */,
      17,    0,  181,    2, 0x08,   33 /* Private */,
      18,    0,  182,    2, 0x08,   34 /* Private */,
      19,    0,  183,    2, 0x08,   35 /* Private */,
      20,    0,  184,    2, 0x08,   36 /* Private */,
      21,    0,  185,    2, 0x08,   37 /* Private */,
      22,    0,  186,    2, 0x08,   38 /* Private */,
      23,    0,  187,    2, 0x08,   39 /* Private */,
      24,    0,  188,    2, 0x08,   40 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    3,    4,    5,    6,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString,    3,    4,    5,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString,    3,    4,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    9,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Login::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSLoginENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSLoginENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSLoginENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Login, std::true_type>,
        // method 'user_info_signal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'user_info_signal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'user_info_signal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'user_info_signal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'user_info_signal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'login_success_signal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'signUp_operate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'login_operate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'idSearch_operate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'pwSearch_operate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'pageMove'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'login'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'idDupChk'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pnumDupChk'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'signUp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'idSearch'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pwSearch'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'idText_change'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pNumText_change'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Login::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Login *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->user_info_signal((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[5]))); break;
        case 1: _t->user_info_signal((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4]))); break;
        case 2: _t->user_info_signal((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 3: _t->user_info_signal((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 4: _t->user_info_signal((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->login_success_signal((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->signUp_operate((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->login_operate((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->idSearch_operate((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->pwSearch_operate((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 10: _t->pageMove((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->login(); break;
        case 12: _t->idDupChk(); break;
        case 13: _t->pnumDupChk(); break;
        case 14: _t->signUp(); break;
        case 15: _t->idSearch(); break;
        case 16: _t->pwSearch(); break;
        case 17: _t->idText_change(); break;
        case 18: _t->pNumText_change(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Login::*)(int , QString , QString , QString , QString );
            if (_t _q_method = &Login::user_info_signal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Login::*)(QString );
            if (_t _q_method = &Login::login_success_signal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject *Login::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Login::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSLoginENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Login::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void Login::user_info_signal(int _t1, QString _t2, QString _t3, QString _t4, QString _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 5
void Login::login_success_signal(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
