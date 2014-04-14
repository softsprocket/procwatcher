/****************************************************************************
** Meta object code from reading C++ file 'procwatcher.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../procwatcher/procwatcher.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'procwatcher.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ProcWatcher_t {
    QByteArrayData data[19];
    char stringdata[320];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ProcWatcher_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ProcWatcher_t qt_meta_stringdata_ProcWatcher = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 29),
QT_MOC_LITERAL(2, 42, 0),
QT_MOC_LITERAL(3, 43, 5),
QT_MOC_LITERAL(4, 49, 7),
QT_MOC_LITERAL(5, 57, 28),
QT_MOC_LITERAL(6, 86, 5),
QT_MOC_LITERAL(7, 92, 26),
QT_MOC_LITERAL(8, 119, 23),
QT_MOC_LITERAL(9, 143, 31),
QT_MOC_LITERAL(10, 175, 34),
QT_MOC_LITERAL(11, 210, 12),
QT_MOC_LITERAL(12, 223, 24),
QT_MOC_LITERAL(13, 248, 13),
QT_MOC_LITERAL(14, 262, 11),
QT_MOC_LITERAL(15, 274, 9),
QT_MOC_LITERAL(16, 284, 13),
QT_MOC_LITERAL(17, 298, 16),
QT_MOC_LITERAL(18, 315, 3)
    },
    "ProcWatcher\0on_procTreeView_doubleClicked\0"
    "\0index\0onTimer\0saveHorizontalScrollBarValue\0"
    "value\0saveVerticalScrollBarValue\0"
    "on_actionStop_triggered\0"
    "on_actionSet_Interval_triggered\0"
    "on_actionFind_Process_ID_triggered\0"
    "treeExpanded\0on_actionAbout_triggered\0"
    "setTimerState\0updateModel\0Direntry*\0"
    "whenActivated\0contextMenuEvent\0pos\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProcWatcher[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x08,
       4,    0,   82,    2, 0x08,
       5,    1,   83,    2, 0x08,
       7,    1,   86,    2, 0x08,
       8,    0,   89,    2, 0x08,
       9,    0,   90,    2, 0x08,
      10,    0,   91,    2, 0x08,
      11,    1,   92,    2, 0x08,
      12,    0,   95,    2, 0x08,
      13,    0,   96,    2, 0x08,
      14,    1,   97,    2, 0x08,
      16,    1,  100,    2, 0x08,
      17,    1,  103,    2, 0x08,

 // slots: parameters
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15,    2,
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void, QMetaType::QPoint,   18,

       0        // eod
};

void ProcWatcher::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ProcWatcher *_t = static_cast<ProcWatcher *>(_o);
        switch (_id) {
        case 0: _t->on_procTreeView_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: _t->onTimer(); break;
        case 2: _t->saveHorizontalScrollBarValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->saveVerticalScrollBarValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_actionStop_triggered(); break;
        case 5: _t->on_actionSet_Interval_triggered(); break;
        case 6: _t->on_actionFind_Process_ID_triggered(); break;
        case 7: _t->treeExpanded((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 8: _t->on_actionAbout_triggered(); break;
        case 9: _t->setTimerState(); break;
        case 10: _t->updateModel((*reinterpret_cast< Direntry*(*)>(_a[1]))); break;
        case 11: _t->whenActivated((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 12: _t->contextMenuEvent((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ProcWatcher::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ProcWatcher.data,
      qt_meta_data_ProcWatcher,  qt_static_metacall, 0, 0}
};


const QMetaObject *ProcWatcher::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProcWatcher::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ProcWatcher.stringdata))
        return static_cast<void*>(const_cast< ProcWatcher*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ProcWatcher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
