/****************************************************************************
** Meta object code from reading C++ file 'm_Window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../m_Window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'm_Window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_m_Window_t {
    QByteArrayData data[11];
    char stringdata0[154];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_m_Window_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_m_Window_t qt_meta_stringdata_m_Window = {
    {
QT_MOC_LITERAL(0, 0, 8), // "m_Window"
QT_MOC_LITERAL(1, 9, 15), // "showContextMenu"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 3), // "pos"
QT_MOC_LITERAL(4, 30, 6), // "QMenu*"
QT_MOC_LITERAL(5, 37, 11), // "contextMenu"
QT_MOC_LITERAL(6, 49, 16), // "addClientToTable"
QT_MOC_LITERAL(7, 66, 21), // "removeClientFromTable"
QT_MOC_LITERAL(8, 88, 27), // "onCreateServerButtonClicked"
QT_MOC_LITERAL(9, 116, 25), // "onStopServerButtonClicked"
QT_MOC_LITERAL(10, 142, 11) // "onTriggered"

    },
    "m_Window\0showContextMenu\0\0pos\0QMenu*\0"
    "contextMenu\0addClientToTable\0"
    "removeClientFromTable\0onCreateServerButtonClicked\0"
    "onStopServerButtonClicked\0onTriggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_m_Window[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x08 /* Private */,
       6,    5,   49,    2, 0x08 /* Private */,
       7,    1,   60,    2, 0x08 /* Private */,
       8,    0,   63,    2, 0x08 /* Private */,
       9,    0,   64,    2, 0x08 /* Private */,
      10,    0,   65,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QPoint, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::QString,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void m_Window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<m_Window *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1])),(*reinterpret_cast< QMenu*(*)>(_a[2]))); break;
        case 1: _t->addClientToTable((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 2: _t->removeClientFromTable((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onCreateServerButtonClicked(); break;
        case 4: _t->onStopServerButtonClicked(); break;
        case 5: _t->onTriggered(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject m_Window::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_m_Window.data,
    qt_meta_data_m_Window,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *m_Window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *m_Window::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_m_Window.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int m_Window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
