/****************************************************************************
** Meta object code from reading C++ file 'hsm_full.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../RpiHSM/HSM_Full/HSM_Full/hsm_full.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hsm_full.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_hsm_full_t {
    QByteArrayData data[57];
    char stringdata0[622];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_hsm_full_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_hsm_full_t qt_meta_stringdata_hsm_full = {
    {
QT_MOC_LITERAL(0, 0, 8), // "hsm_full"
QT_MOC_LITERAL(1, 9, 10), // "sendSignal"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 5), // "value"
QT_MOC_LITERAL(4, 27, 10), // "updatePlot"
QT_MOC_LITERAL(5, 38, 9), // "stiffTest"
QT_MOC_LITERAL(6, 48, 4), // "save"
QT_MOC_LITERAL(7, 53, 11), // "sendCommand"
QT_MOC_LITERAL(8, 65, 5), // "sendP"
QT_MOC_LITERAL(9, 71, 5), // "sendI"
QT_MOC_LITERAL(10, 77, 5), // "sendD"
QT_MOC_LITERAL(11, 83, 13), // "sliderCommand"
QT_MOC_LITERAL(12, 97, 14), // "activateButton"
QT_MOC_LITERAL(13, 112, 9), // "updateLCD"
QT_MOC_LITERAL(14, 122, 11), // "spanCommand"
QT_MOC_LITERAL(15, 134, 10), // "targetSpan"
QT_MOC_LITERAL(16, 145, 10), // "targetZero"
QT_MOC_LITERAL(17, 156, 7), // "setZero"
QT_MOC_LITERAL(18, 164, 12), // "startControl"
QT_MOC_LITERAL(19, 177, 6), // "setAmp"
QT_MOC_LITERAL(20, 184, 7), // "setFreq"
QT_MOC_LITERAL(21, 192, 7), // "sinTest"
QT_MOC_LITERAL(22, 200, 5), // "sweep"
QT_MOC_LITERAL(23, 206, 7), // "ampTest"
QT_MOC_LITERAL(24, 214, 8), // "reqloops"
QT_MOC_LITERAL(25, 223, 8), // "calForce"
QT_MOC_LITERAL(26, 232, 11), // "PSAS_Window"
QT_MOC_LITERAL(27, 244, 10), // "Cal_Window"
QT_MOC_LITERAL(28, 255, 11), // "activatePin"
QT_MOC_LITERAL(29, 267, 11), // "plotResults"
QT_MOC_LITERAL(30, 279, 10), // "serialRead"
QT_MOC_LITERAL(31, 290, 7), // "channel"
QT_MOC_LITERAL(32, 298, 4), // "comm"
QT_MOC_LITERAL(33, 303, 4), // "data"
QT_MOC_LITERAL(34, 308, 11), // "serialWrite"
QT_MOC_LITERAL(35, 320, 20), // "readCalibrationFiles"
QT_MOC_LITERAL(36, 341, 33), // "std::vector<std::vector<doubl..."
QT_MOC_LITERAL(37, 375, 11), // "std::string"
QT_MOC_LITERAL(38, 387, 8), // "fileName"
QT_MOC_LITERAL(39, 396, 16), // "LinearRegression"
QT_MOC_LITERAL(40, 413, 19), // "std::vector<double>"
QT_MOC_LITERAL(41, 433, 5), // "xData"
QT_MOC_LITERAL(42, 439, 5), // "yData"
QT_MOC_LITERAL(43, 445, 8), // "sendZero"
QT_MOC_LITERAL(44, 454, 10), // "changeSpan"
QT_MOC_LITERAL(45, 465, 10), // "sendDouble"
QT_MOC_LITERAL(46, 476, 12), // "sendDoubleUI"
QT_MOC_LITERAL(47, 489, 16), // "receivedToInches"
QT_MOC_LITERAL(48, 506, 10), // "dataInBits"
QT_MOC_LITERAL(49, 517, 15), // "pressSpanButton"
QT_MOC_LITERAL(50, 533, 10), // "turnOnLow1"
QT_MOC_LITERAL(51, 544, 10), // "turnOnLow2"
QT_MOC_LITERAL(52, 555, 11), // "turnOnHigh1"
QT_MOC_LITERAL(53, 567, 11), // "turnOnHigh2"
QT_MOC_LITERAL(54, 579, 17), // "turnOffHydraulics"
QT_MOC_LITERAL(55, 597, 17), // "useSecondActuator"
QT_MOC_LITERAL(56, 615, 6) // "update"

    },
    "hsm_full\0sendSignal\0\0value\0updatePlot\0"
    "stiffTest\0save\0sendCommand\0sendP\0sendI\0"
    "sendD\0sliderCommand\0activateButton\0"
    "updateLCD\0spanCommand\0targetSpan\0"
    "targetZero\0setZero\0startControl\0setAmp\0"
    "setFreq\0sinTest\0sweep\0ampTest\0reqloops\0"
    "calForce\0PSAS_Window\0Cal_Window\0"
    "activatePin\0plotResults\0serialRead\0"
    "channel\0comm\0data\0serialWrite\0"
    "readCalibrationFiles\0"
    "std::vector<std::vector<double> >\0"
    "std::string\0fileName\0LinearRegression\0"
    "std::vector<double>\0xData\0yData\0"
    "sendZero\0changeSpan\0sendDouble\0"
    "sendDoubleUI\0receivedToInches\0dataInBits\0"
    "pressSpanButton\0turnOnLow1\0turnOnLow2\0"
    "turnOnHigh1\0turnOnHigh2\0turnOffHydraulics\0"
    "useSecondActuator\0update"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_hsm_full[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      42,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  224,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,  227,    2, 0x0a /* Public */,
       5,    0,  228,    2, 0x0a /* Public */,
       6,    0,  229,    2, 0x0a /* Public */,
       7,    0,  230,    2, 0x0a /* Public */,
       8,    0,  231,    2, 0x0a /* Public */,
       9,    0,  232,    2, 0x0a /* Public */,
      10,    0,  233,    2, 0x0a /* Public */,
      11,    0,  234,    2, 0x0a /* Public */,
      12,    0,  235,    2, 0x0a /* Public */,
      13,    0,  236,    2, 0x0a /* Public */,
      14,    2,  237,    2, 0x0a /* Public */,
      17,    0,  242,    2, 0x0a /* Public */,
      18,    0,  243,    2, 0x0a /* Public */,
      19,    0,  244,    2, 0x0a /* Public */,
      20,    0,  245,    2, 0x0a /* Public */,
      21,    0,  246,    2, 0x0a /* Public */,
      22,    0,  247,    2, 0x0a /* Public */,
      23,    0,  248,    2, 0x0a /* Public */,
      24,    0,  249,    2, 0x0a /* Public */,
      25,    0,  250,    2, 0x0a /* Public */,
      26,    0,  251,    2, 0x0a /* Public */,
      27,    0,  252,    2, 0x0a /* Public */,
      28,    0,  253,    2, 0x0a /* Public */,
      29,    0,  254,    2, 0x0a /* Public */,
      30,    3,  255,    2, 0x0a /* Public */,
      34,    3,  262,    2, 0x0a /* Public */,
      35,    1,  269,    2, 0x0a /* Public */,
      39,    2,  272,    2, 0x0a /* Public */,
      43,    0,  277,    2, 0x0a /* Public */,
      44,    0,  278,    2, 0x0a /* Public */,
      45,    2,  279,    2, 0x0a /* Public */,
      46,    0,  284,    2, 0x0a /* Public */,
      47,    1,  285,    2, 0x0a /* Public */,
      49,    0,  288,    2, 0x0a /* Public */,
      50,    0,  289,    2, 0x0a /* Public */,
      51,    0,  290,    2, 0x0a /* Public */,
      52,    0,  291,    2, 0x0a /* Public */,
      53,    0,  292,    2, 0x0a /* Public */,
      54,    0,  293,    2, 0x0a /* Public */,
      55,    0,  294,    2, 0x0a /* Public */,
      56,    0,  295,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

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
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   15,   16,
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
    QMetaType::Int,
    QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   31,   32,   33,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   31,   32,   33,
    0x80000000 | 36, 0x80000000 | 37,   38,
    0x80000000 | 40, 0x80000000 | 40, 0x80000000 | 40,   41,   42,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Double,   31,   33,
    QMetaType::Void,
    QMetaType::Double, QMetaType::Int,   48,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,

       0        // eod
};

void hsm_full::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<hsm_full *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->updatePlot(); break;
        case 2: _t->stiffTest(); break;
        case 3: _t->save(); break;
        case 4: _t->sendCommand(); break;
        case 5: _t->sendP(); break;
        case 6: _t->sendI(); break;
        case 7: _t->sendD(); break;
        case 8: _t->sliderCommand(); break;
        case 9: _t->activateButton(); break;
        case 10: _t->updateLCD(); break;
        case 11: _t->spanCommand((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 12: _t->setZero(); break;
        case 13: _t->startControl(); break;
        case 14: _t->setAmp(); break;
        case 15: _t->setFreq(); break;
        case 16: _t->sinTest(); break;
        case 17: _t->sweep(); break;
        case 18: _t->ampTest(); break;
        case 19: _t->reqloops(); break;
        case 20: _t->calForce(); break;
        case 21: _t->PSAS_Window(); break;
        case 22: _t->Cal_Window(); break;
        case 23: _t->activatePin(); break;
        case 24: { int _r = _t->plotResults();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 25: { int _r = _t->serialRead((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 26: _t->serialWrite((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 27: { std::vector<std::vector<double> > _r = _t->readCalibrationFiles((*reinterpret_cast< std::string(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< std::vector<std::vector<double> >*>(_a[0]) = std::move(_r); }  break;
        case 28: { std::vector<double> _r = _t->LinearRegression((*reinterpret_cast< std::vector<double>(*)>(_a[1])),(*reinterpret_cast< std::vector<double>(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< std::vector<double>*>(_a[0]) = std::move(_r); }  break;
        case 29: _t->sendZero(); break;
        case 30: _t->changeSpan(); break;
        case 31: _t->sendDouble((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 32: _t->sendDoubleUI(); break;
        case 33: { double _r = _t->receivedToInches((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 34: _t->pressSpanButton(); break;
        case 35: _t->turnOnLow1(); break;
        case 36: _t->turnOnLow2(); break;
        case 37: _t->turnOnHigh1(); break;
        case 38: _t->turnOnHigh2(); break;
        case 39: _t->turnOffHydraulics(); break;
        case 40: _t->useSecondActuator(); break;
        case 41: { int _r = _t->update();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (hsm_full::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&hsm_full::sendSignal)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject hsm_full::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_hsm_full.data,
    qt_meta_data_hsm_full,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *hsm_full::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *hsm_full::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_hsm_full.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int hsm_full::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 42)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 42;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 42)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 42;
    }
    return _id;
}

// SIGNAL 0
void hsm_full::sendSignal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_PSAS_t {
    QByteArrayData data[19];
    char stringdata0[252];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PSAS_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PSAS_t qt_meta_stringdata_PSAS = {
    {
QT_MOC_LITERAL(0, 0, 4), // "PSAS"
QT_MOC_LITERAL(1, 5, 17), // "add_Node_to_Model"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 22), // "remove_Node_from_Model"
QT_MOC_LITERAL(4, 47, 20), // "add_Element_to_Model"
QT_MOC_LITERAL(5, 68, 25), // "remove_Element_from_Model"
QT_MOC_LITERAL(6, 94, 12), // "add_el_props"
QT_MOC_LITERAL(7, 107, 7), // "add_BCs"
QT_MOC_LITERAL(8, 115, 11), // "add_el_load"
QT_MOC_LITERAL(9, 127, 13), // "add_node_load"
QT_MOC_LITERAL(10, 141, 10), // "setupModel"
QT_MOC_LITERAL(11, 152, 9), // "switchDim"
QT_MOC_LITERAL(12, 162, 9), // "plotModel"
QT_MOC_LITERAL(13, 172, 15), // "HybridEl_Window"
QT_MOC_LITERAL(14, 188, 12), // "enableHybrid"
QT_MOC_LITERAL(15, 201, 8), // "submitEQ"
QT_MOC_LITERAL(16, 210, 12), // "submitDynOpt"
QT_MOC_LITERAL(17, 223, 12), // "enableCustom"
QT_MOC_LITERAL(18, 236, 15) // "CustomEl_Window"

    },
    "PSAS\0add_Node_to_Model\0\0remove_Node_from_Model\0"
    "add_Element_to_Model\0remove_Element_from_Model\0"
    "add_el_props\0add_BCs\0add_el_load\0"
    "add_node_load\0setupModel\0switchDim\0"
    "plotModel\0HybridEl_Window\0enableHybrid\0"
    "submitEQ\0submitDynOpt\0enableCustom\0"
    "CustomEl_Window"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PSAS[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x0a /* Public */,
       3,    0,  100,    2, 0x0a /* Public */,
       4,    0,  101,    2, 0x0a /* Public */,
       5,    0,  102,    2, 0x0a /* Public */,
       6,    0,  103,    2, 0x0a /* Public */,
       7,    0,  104,    2, 0x0a /* Public */,
       8,    0,  105,    2, 0x0a /* Public */,
       9,    0,  106,    2, 0x0a /* Public */,
      10,    0,  107,    2, 0x0a /* Public */,
      11,    0,  108,    2, 0x0a /* Public */,
      12,    0,  109,    2, 0x0a /* Public */,
      13,    0,  110,    2, 0x0a /* Public */,
      14,    0,  111,    2, 0x0a /* Public */,
      15,    0,  112,    2, 0x0a /* Public */,
      16,    0,  113,    2, 0x0a /* Public */,
      17,    0,  114,    2, 0x0a /* Public */,
      18,    0,  115,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PSAS::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PSAS *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->add_Node_to_Model(); break;
        case 1: _t->remove_Node_from_Model(); break;
        case 2: _t->add_Element_to_Model(); break;
        case 3: _t->remove_Element_from_Model(); break;
        case 4: _t->add_el_props(); break;
        case 5: _t->add_BCs(); break;
        case 6: _t->add_el_load(); break;
        case 7: _t->add_node_load(); break;
        case 8: { int _r = _t->setupModel();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->switchDim(); break;
        case 10: { int _r = _t->plotModel();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 11: _t->HybridEl_Window(); break;
        case 12: _t->enableHybrid(); break;
        case 13: _t->submitEQ(); break;
        case 14: { int _r = _t->submitDynOpt();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 15: _t->enableCustom(); break;
        case 16: _t->CustomEl_Window(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PSAS::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_PSAS.data,
    qt_meta_data_PSAS,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PSAS::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PSAS::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PSAS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int PSAS::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
struct qt_meta_stringdata_HybridEl_t {
    QByteArrayData data[4];
    char stringdata0[35];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HybridEl_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HybridEl_t qt_meta_stringdata_HybridEl = {
    {
QT_MOC_LITERAL(0, 0, 8), // "HybridEl"
QT_MOC_LITERAL(1, 9, 13), // "submitElement"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 10) // "undoSubmit"

    },
    "HybridEl\0submitElement\0\0undoSubmit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HybridEl[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void HybridEl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HybridEl *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->submitElement(); break;
        case 1: _t->undoSubmit(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject HybridEl::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_HybridEl.data,
    qt_meta_data_HybridEl,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *HybridEl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HybridEl::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HybridEl.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int HybridEl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_CustomElement_t {
    QByteArrayData data[4];
    char stringdata0[40];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CustomElement_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CustomElement_t qt_meta_stringdata_CustomElement = {
    {
QT_MOC_LITERAL(0, 0, 13), // "CustomElement"
QT_MOC_LITERAL(1, 14, 13), // "submitElement"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 10) // "undoSubmit"

    },
    "CustomElement\0submitElement\0\0undoSubmit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CustomElement[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CustomElement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CustomElement *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->submitElement(); break;
        case 1: _t->undoSubmit(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject CustomElement::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CustomElement.data,
    qt_meta_data_CustomElement,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CustomElement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CustomElement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CustomElement.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int CustomElement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_SpanCalibration_t {
    QByteArrayData data[12];
    char stringdata0[112];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SpanCalibration_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SpanCalibration_t qt_meta_stringdata_SpanCalibration = {
    {
QT_MOC_LITERAL(0, 0, 15), // "SpanCalibration"
QT_MOC_LITERAL(1, 16, 16), // "startCalibration"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 7), // "plotCal"
QT_MOC_LITERAL(4, 42, 15), // "QVector<double>"
QT_MOC_LITERAL(5, 58, 1), // "X"
QT_MOC_LITERAL(6, 60, 1), // "Y"
QT_MOC_LITERAL(7, 62, 6), // "potCal"
QT_MOC_LITERAL(8, 69, 10), // "setTotSpan"
QT_MOC_LITERAL(9, 80, 14), // "activatePotCal"
QT_MOC_LITERAL(10, 95, 9), // "BitToInch"
QT_MOC_LITERAL(11, 105, 6) // "bitVal"

    },
    "SpanCalibration\0startCalibration\0\0"
    "plotCal\0QVector<double>\0X\0Y\0potCal\0"
    "setTotSpan\0activatePotCal\0BitToInch\0"
    "bitVal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SpanCalibration[] = {

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
       1,    0,   44,    2, 0x0a /* Public */,
       3,    2,   45,    2, 0x0a /* Public */,
       7,    0,   50,    2, 0x0a /* Public */,
       8,    0,   51,    2, 0x0a /* Public */,
       9,    0,   52,    2, 0x0a /* Public */,
      10,    1,   53,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 4,    5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Double, QMetaType::Int,   11,

       0        // eod
};

void SpanCalibration::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SpanCalibration *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startCalibration(); break;
        case 1: _t->plotCal((*reinterpret_cast< QVector<double>(*)>(_a[1])),(*reinterpret_cast< QVector<double>(*)>(_a[2]))); break;
        case 2: _t->potCal(); break;
        case 3: _t->setTotSpan(); break;
        case 4: _t->activatePotCal(); break;
        case 5: { double _r = _t->BitToInch((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<double> >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SpanCalibration::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_SpanCalibration.data,
    qt_meta_data_SpanCalibration,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SpanCalibration::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SpanCalibration::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SpanCalibration.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int SpanCalibration::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
