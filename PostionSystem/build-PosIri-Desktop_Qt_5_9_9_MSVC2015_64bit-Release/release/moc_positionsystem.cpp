/****************************************************************************
** Meta object code from reading C++ file 'positionsystem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PosIri/positionsystem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'positionsystem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PositionSystem_t {
    QByteArrayData data[41];
    char stringdata0[831];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PositionSystem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PositionSystem_t qt_meta_stringdata_PositionSystem = {
    {
QT_MOC_LITERAL(0, 0, 14), // "PositionSystem"
QT_MOC_LITERAL(1, 15, 24), // "on_GPSSearchPort_clicked"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 8), // "ReadPort"
QT_MOC_LITERAL(4, 50, 22), // "on_GPSOpenPort_clicked"
QT_MOC_LITERAL(5, 73, 21), // "on_GPSReceive_clicked"
QT_MOC_LITERAL(6, 95, 25), // "on_GPSSentCommand_clicked"
QT_MOC_LITERAL(7, 121, 28), // "on_TekReadpushButton_clicked"
QT_MOC_LITERAL(8, 150, 30), // "on_TekWriteCpushButton_clicked"
QT_MOC_LITERAL(9, 181, 29), // "on_TekStartpushButton_clicked"
QT_MOC_LITERAL(10, 211, 27), // "on_TekEndpushButton_clicked"
QT_MOC_LITERAL(11, 239, 13), // "refreshtekout"
QT_MOC_LITERAL(12, 253, 29), // "on_AcqReadApushButton_clicked"
QT_MOC_LITERAL(13, 283, 29), // "on_AcqReadCpushButton_clicked"
QT_MOC_LITERAL(14, 313, 30), // "on_AcqWriteCpushButton_clicked"
QT_MOC_LITERAL(15, 344, 29), // "on_AcqStartpushButton_clicked"
QT_MOC_LITERAL(16, 374, 27), // "on_AcqEndpushButton_clicked"
QT_MOC_LITERAL(17, 402, 13), // "refreshacqout"
QT_MOC_LITERAL(18, 416, 17), // "refreshacqoutSort"
QT_MOC_LITERAL(19, 434, 8), // "ReadData"
QT_MOC_LITERAL(20, 443, 8), // "PlotData"
QT_MOC_LITERAL(21, 452, 10), // "RefreshBar"
QT_MOC_LITERAL(22, 463, 3), // "ind"
QT_MOC_LITERAL(23, 467, 14), // "onAcqModeClick"
QT_MOC_LITERAL(24, 482, 18), // "on_Iridium_clicked"
QT_MOC_LITERAL(25, 501, 22), // "on_IridiumNext_clicked"
QT_MOC_LITERAL(26, 524, 20), // "on_UpdateTLE_clicked"
QT_MOC_LITERAL(27, 545, 27), // "on_UpCopypushButton_clicked"
QT_MOC_LITERAL(28, 573, 24), // "on_LocConfigRead_clicked"
QT_MOC_LITERAL(29, 598, 25), // "on_LocConfigWrite_clicked"
QT_MOC_LITERAL(30, 624, 24), // "on_LocMapDisplay_clicked"
QT_MOC_LITERAL(31, 649, 20), // "on_LocMapAll_clicked"
QT_MOC_LITERAL(32, 670, 20), // "on_LocMapOne_clicked"
QT_MOC_LITERAL(33, 691, 26), // "on_LocMapRefCircle_clicked"
QT_MOC_LITERAL(34, 718, 26), // "on_LocMapResCircle_clicked"
QT_MOC_LITERAL(35, 745, 22), // "on_LocStartLoc_clicked"
QT_MOC_LITERAL(36, 768, 20), // "on_LocEndLoc_clicked"
QT_MOC_LITERAL(37, 789, 13), // "refreshlocout"
QT_MOC_LITERAL(38, 803, 11), // "timerUpdate"
QT_MOC_LITERAL(39, 815, 10), // "Delay_MSec"
QT_MOC_LITERAL(40, 826, 4) // "msec"

    },
    "PositionSystem\0on_GPSSearchPort_clicked\0"
    "\0ReadPort\0on_GPSOpenPort_clicked\0"
    "on_GPSReceive_clicked\0on_GPSSentCommand_clicked\0"
    "on_TekReadpushButton_clicked\0"
    "on_TekWriteCpushButton_clicked\0"
    "on_TekStartpushButton_clicked\0"
    "on_TekEndpushButton_clicked\0refreshtekout\0"
    "on_AcqReadApushButton_clicked\0"
    "on_AcqReadCpushButton_clicked\0"
    "on_AcqWriteCpushButton_clicked\0"
    "on_AcqStartpushButton_clicked\0"
    "on_AcqEndpushButton_clicked\0refreshacqout\0"
    "refreshacqoutSort\0ReadData\0PlotData\0"
    "RefreshBar\0ind\0onAcqModeClick\0"
    "on_Iridium_clicked\0on_IridiumNext_clicked\0"
    "on_UpdateTLE_clicked\0on_UpCopypushButton_clicked\0"
    "on_LocConfigRead_clicked\0"
    "on_LocConfigWrite_clicked\0"
    "on_LocMapDisplay_clicked\0on_LocMapAll_clicked\0"
    "on_LocMapOne_clicked\0on_LocMapRefCircle_clicked\0"
    "on_LocMapResCircle_clicked\0"
    "on_LocStartLoc_clicked\0on_LocEndLoc_clicked\0"
    "refreshlocout\0timerUpdate\0Delay_MSec\0"
    "msec"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PositionSystem[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      37,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  199,    2, 0x08 /* Private */,
       3,    0,  200,    2, 0x08 /* Private */,
       4,    0,  201,    2, 0x08 /* Private */,
       5,    0,  202,    2, 0x08 /* Private */,
       6,    0,  203,    2, 0x08 /* Private */,
       7,    0,  204,    2, 0x08 /* Private */,
       8,    0,  205,    2, 0x08 /* Private */,
       9,    0,  206,    2, 0x08 /* Private */,
      10,    0,  207,    2, 0x08 /* Private */,
      11,    0,  208,    2, 0x08 /* Private */,
      12,    0,  209,    2, 0x08 /* Private */,
      13,    0,  210,    2, 0x08 /* Private */,
      14,    0,  211,    2, 0x08 /* Private */,
      15,    0,  212,    2, 0x08 /* Private */,
      16,    0,  213,    2, 0x08 /* Private */,
      17,    0,  214,    2, 0x08 /* Private */,
      18,    0,  215,    2, 0x08 /* Private */,
      19,    0,  216,    2, 0x08 /* Private */,
      20,    0,  217,    2, 0x08 /* Private */,
      21,    1,  218,    2, 0x08 /* Private */,
      23,    0,  221,    2, 0x08 /* Private */,
      24,    0,  222,    2, 0x08 /* Private */,
      25,    0,  223,    2, 0x08 /* Private */,
      26,    0,  224,    2, 0x08 /* Private */,
      27,    0,  225,    2, 0x08 /* Private */,
      28,    0,  226,    2, 0x08 /* Private */,
      29,    0,  227,    2, 0x08 /* Private */,
      30,    0,  228,    2, 0x08 /* Private */,
      31,    0,  229,    2, 0x08 /* Private */,
      32,    0,  230,    2, 0x08 /* Private */,
      33,    0,  231,    2, 0x08 /* Private */,
      34,    0,  232,    2, 0x08 /* Private */,
      35,    0,  233,    2, 0x08 /* Private */,
      36,    0,  234,    2, 0x08 /* Private */,
      37,    0,  235,    2, 0x08 /* Private */,
      38,    0,  236,    2, 0x08 /* Private */,
      39,    1,  237,    2, 0x08 /* Private */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   22,
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
    QMetaType::Void, QMetaType::UInt,   40,

       0        // eod
};

void PositionSystem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PositionSystem *_t = static_cast<PositionSystem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_GPSSearchPort_clicked(); break;
        case 1: _t->ReadPort(); break;
        case 2: _t->on_GPSOpenPort_clicked(); break;
        case 3: _t->on_GPSReceive_clicked(); break;
        case 4: _t->on_GPSSentCommand_clicked(); break;
        case 5: _t->on_TekReadpushButton_clicked(); break;
        case 6: _t->on_TekWriteCpushButton_clicked(); break;
        case 7: _t->on_TekStartpushButton_clicked(); break;
        case 8: _t->on_TekEndpushButton_clicked(); break;
        case 9: _t->refreshtekout(); break;
        case 10: _t->on_AcqReadApushButton_clicked(); break;
        case 11: _t->on_AcqReadCpushButton_clicked(); break;
        case 12: _t->on_AcqWriteCpushButton_clicked(); break;
        case 13: _t->on_AcqStartpushButton_clicked(); break;
        case 14: _t->on_AcqEndpushButton_clicked(); break;
        case 15: _t->refreshacqout(); break;
        case 16: _t->refreshacqoutSort(); break;
        case 17: _t->ReadData(); break;
        case 18: _t->PlotData(); break;
        case 19: _t->RefreshBar((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->onAcqModeClick(); break;
        case 21: _t->on_Iridium_clicked(); break;
        case 22: _t->on_IridiumNext_clicked(); break;
        case 23: _t->on_UpdateTLE_clicked(); break;
        case 24: _t->on_UpCopypushButton_clicked(); break;
        case 25: _t->on_LocConfigRead_clicked(); break;
        case 26: _t->on_LocConfigWrite_clicked(); break;
        case 27: _t->on_LocMapDisplay_clicked(); break;
        case 28: _t->on_LocMapAll_clicked(); break;
        case 29: _t->on_LocMapOne_clicked(); break;
        case 30: _t->on_LocMapRefCircle_clicked(); break;
        case 31: _t->on_LocMapResCircle_clicked(); break;
        case 32: _t->on_LocStartLoc_clicked(); break;
        case 33: _t->on_LocEndLoc_clicked(); break;
        case 34: _t->refreshlocout(); break;
        case 35: _t->timerUpdate(); break;
        case 36: _t->Delay_MSec((*reinterpret_cast< uint(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject PositionSystem::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_PositionSystem.data,
      qt_meta_data_PositionSystem,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PositionSystem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PositionSystem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PositionSystem.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int PositionSystem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 37)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 37;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 37)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 37;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
