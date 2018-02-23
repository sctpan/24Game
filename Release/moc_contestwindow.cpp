/****************************************************************************
** Meta object code from reading C++ file 'contestwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../24Game/contestwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'contestwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ContestWindow_t {
    QByteArrayData data[21];
    char stringdata0[251];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ContestWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ContestWindow_t qt_meta_stringdata_ContestWindow = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ContestWindow"
QT_MOC_LITERAL(1, 14, 5), // "clear"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 14), // "clear_equation"
QT_MOC_LITERAL(4, 36, 9), // "backspace"
QT_MOC_LITERAL(5, 46, 5), // "equal"
QT_MOC_LITERAL(6, 52, 10), // "input_plus"
QT_MOC_LITERAL(7, 63, 11), // "input_minus"
QT_MOC_LITERAL(8, 75, 11), // "input_times"
QT_MOC_LITERAL(9, 87, 12), // "input_divide"
QT_MOC_LITERAL(10, 100, 11), // "input_power"
QT_MOC_LITERAL(11, 112, 10), // "input_left"
QT_MOC_LITERAL(12, 123, 11), // "input_right"
QT_MOC_LITERAL(13, 135, 8), // "input_no"
QT_MOC_LITERAL(14, 144, 16), // "on_card1_clicked"
QT_MOC_LITERAL(15, 161, 16), // "on_card2_clicked"
QT_MOC_LITERAL(16, 178, 16), // "on_card3_clicked"
QT_MOC_LITERAL(17, 195, 16), // "on_card4_clicked"
QT_MOC_LITERAL(18, 212, 15), // "showErrorDialog"
QT_MOC_LITERAL(19, 228, 9), // "show_time"
QT_MOC_LITERAL(20, 238, 12) // "exit_contest"

    },
    "ContestWindow\0clear\0\0clear_equation\0"
    "backspace\0equal\0input_plus\0input_minus\0"
    "input_times\0input_divide\0input_power\0"
    "input_left\0input_right\0input_no\0"
    "on_card1_clicked\0on_card2_clicked\0"
    "on_card3_clicked\0on_card4_clicked\0"
    "showErrorDialog\0show_time\0exit_contest"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ContestWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  109,    2, 0x08 /* Private */,
       3,    0,  110,    2, 0x08 /* Private */,
       4,    0,  111,    2, 0x08 /* Private */,
       5,    0,  112,    2, 0x08 /* Private */,
       6,    0,  113,    2, 0x08 /* Private */,
       7,    0,  114,    2, 0x08 /* Private */,
       8,    0,  115,    2, 0x08 /* Private */,
       9,    0,  116,    2, 0x08 /* Private */,
      10,    0,  117,    2, 0x08 /* Private */,
      11,    0,  118,    2, 0x08 /* Private */,
      12,    0,  119,    2, 0x08 /* Private */,
      13,    0,  120,    2, 0x08 /* Private */,
      14,    0,  121,    2, 0x08 /* Private */,
      15,    0,  122,    2, 0x08 /* Private */,
      16,    0,  123,    2, 0x08 /* Private */,
      17,    0,  124,    2, 0x08 /* Private */,
      18,    1,  125,    2, 0x08 /* Private */,
      19,    0,  128,    2, 0x08 /* Private */,
      20,    0,  129,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ContestWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ContestWindow *_t = static_cast<ContestWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clear(); break;
        case 1: _t->clear_equation(); break;
        case 2: _t->backspace(); break;
        case 3: _t->equal(); break;
        case 4: _t->input_plus(); break;
        case 5: _t->input_minus(); break;
        case 6: _t->input_times(); break;
        case 7: _t->input_divide(); break;
        case 8: _t->input_power(); break;
        case 9: _t->input_left(); break;
        case 10: _t->input_right(); break;
        case 11: _t->input_no(); break;
        case 12: _t->on_card1_clicked(); break;
        case 13: _t->on_card2_clicked(); break;
        case 14: _t->on_card3_clicked(); break;
        case 15: _t->on_card4_clicked(); break;
        case 16: _t->showErrorDialog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: _t->show_time(); break;
        case 18: _t->exit_contest(); break;
        default: ;
        }
    }
}

const QMetaObject ContestWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ContestWindow.data,
      qt_meta_data_ContestWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ContestWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ContestWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ContestWindow.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ContestWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
