/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../24Game/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[22];
    char stringdata0[254];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 5), // "clear"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 14), // "clear_equation"
QT_MOC_LITERAL(4, 33, 9), // "backspace"
QT_MOC_LITERAL(5, 43, 5), // "equal"
QT_MOC_LITERAL(6, 49, 10), // "input_plus"
QT_MOC_LITERAL(7, 60, 11), // "input_minus"
QT_MOC_LITERAL(8, 72, 11), // "input_times"
QT_MOC_LITERAL(9, 84, 12), // "input_divide"
QT_MOC_LITERAL(10, 97, 11), // "input_power"
QT_MOC_LITERAL(11, 109, 10), // "input_left"
QT_MOC_LITERAL(12, 120, 11), // "input_right"
QT_MOC_LITERAL(13, 132, 8), // "input_no"
QT_MOC_LITERAL(14, 141, 16), // "on_card1_clicked"
QT_MOC_LITERAL(15, 158, 16), // "on_card2_clicked"
QT_MOC_LITERAL(16, 175, 16), // "on_card3_clicked"
QT_MOC_LITERAL(17, 192, 16), // "on_card4_clicked"
QT_MOC_LITERAL(18, 209, 8), // "get_hint"
QT_MOC_LITERAL(19, 218, 15), // "showErrorDialog"
QT_MOC_LITERAL(20, 234, 9), // "show_time"
QT_MOC_LITERAL(21, 244, 9) // "exit_game"

    },
    "MainWindow\0clear\0\0clear_equation\0"
    "backspace\0equal\0input_plus\0input_minus\0"
    "input_times\0input_divide\0input_power\0"
    "input_left\0input_right\0input_no\0"
    "on_card1_clicked\0on_card2_clicked\0"
    "on_card3_clicked\0on_card4_clicked\0"
    "get_hint\0showErrorDialog\0show_time\0"
    "exit_game"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  114,    2, 0x08 /* Private */,
       3,    0,  115,    2, 0x08 /* Private */,
       4,    0,  116,    2, 0x08 /* Private */,
       5,    0,  117,    2, 0x08 /* Private */,
       6,    0,  118,    2, 0x08 /* Private */,
       7,    0,  119,    2, 0x08 /* Private */,
       8,    0,  120,    2, 0x08 /* Private */,
       9,    0,  121,    2, 0x08 /* Private */,
      10,    0,  122,    2, 0x08 /* Private */,
      11,    0,  123,    2, 0x08 /* Private */,
      12,    0,  124,    2, 0x08 /* Private */,
      13,    0,  125,    2, 0x08 /* Private */,
      14,    0,  126,    2, 0x08 /* Private */,
      15,    0,  127,    2, 0x08 /* Private */,
      16,    0,  128,    2, 0x08 /* Private */,
      17,    0,  129,    2, 0x08 /* Private */,
      18,    0,  130,    2, 0x08 /* Private */,
      19,    1,  131,    2, 0x08 /* Private */,
      20,    0,  134,    2, 0x08 /* Private */,
      21,    0,  135,    2, 0x08 /* Private */,

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
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
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
        case 16: _t->get_hint(); break;
        case 17: _t->showErrorDialog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: _t->show_time(); break;
        case 19: _t->exit_game(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
