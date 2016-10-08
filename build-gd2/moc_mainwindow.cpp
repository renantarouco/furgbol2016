/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Sat Oct 8 08:12:31 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../GerenteDados2/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   12,   11,   11, 0x08,
      61,   12,   11,   11, 0x08,
     103,   11,   11,   11, 0x08,
     128,   11,   11,   11, 0x08,
     146,   11,   11,   11, 0x08,
     163,   11,   11,   11, 0x08,
     188,  180,   11,   11, 0x08,
     218,  180,   11,   11, 0x08,
     247,  180,   11,   11, 0x08,
     276,  180,   11,   11, 0x08,
     312,  307,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0error\0"
    "errorReferee(QAbstractSocket::SocketError)\0"
    "errorVision(QAbstractSocket::SocketError)\0"
    "on_pbStartStop_clicked()\0readRefereeData()\0"
    "readVisionData()\0send_packet_ia()\0"
    "checked\0on_rbRightColor_clicked(bool)\0"
    "on_rbLeftColor_clicked(bool)\0"
    "on_rbBlueColor_clicked(bool)\0"
    "on_rbYellowColor_clicked(bool)\0arg1\0"
    "on_sbIDGoleiro_valueChanged(int)\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->errorReferee((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 1: _t->errorVision((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 2: _t->on_pbStartStop_clicked(); break;
        case 3: _t->readRefereeData(); break;
        case 4: _t->readVisionData(); break;
        case 5: _t->send_packet_ia(); break;
        case 6: _t->on_rbRightColor_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_rbLeftColor_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_rbBlueColor_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_rbYellowColor_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_sbIDGoleiro_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
