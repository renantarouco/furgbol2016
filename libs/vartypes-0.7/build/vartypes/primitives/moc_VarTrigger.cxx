/****************************************************************************
** Meta object code from reading C++ file 'VarTrigger.h'
**
** Created: Sat Oct 8 02:30:04 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../vartypes/primitives/VarTrigger.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VarTrigger.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VarTypes__VarTrigger[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
      40,   21,   21,   21, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_VarTypes__VarTrigger[] = {
    "VarTypes::VarTrigger\0\0signalTriggered()\0"
    "trigger()\0"
};

void VarTypes::VarTrigger::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        VarTrigger *_t = static_cast<VarTrigger *>(_o);
        switch (_id) {
        case 0: _t->signalTriggered(); break;
        case 1: _t->trigger(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData VarTypes::VarTrigger::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject VarTypes::VarTrigger::staticMetaObject = {
    { &VarType::staticMetaObject, qt_meta_stringdata_VarTypes__VarTrigger,
      qt_meta_data_VarTypes__VarTrigger, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VarTypes::VarTrigger::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VarTypes::VarTrigger::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VarTypes::VarTrigger::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VarTypes__VarTrigger))
        return static_cast<void*>(const_cast< VarTrigger*>(this));
    return VarType::qt_metacast(_clname);
}

int VarTypes::VarTrigger::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = VarType::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void VarTypes::VarTrigger::signalTriggered()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
