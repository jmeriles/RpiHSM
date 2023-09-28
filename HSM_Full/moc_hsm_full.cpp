/****************************************************************************
** Meta object code from reading C++ file 'hsm_full.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "hsm_full.h"
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
    QByteArrayData data[106];
    char stringdata0[1299];
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
QT_MOC_LITERAL(7, 53, 20), // "initializeController"
QT_MOC_LITERAL(8, 74, 7), // "channel"
QT_MOC_LITERAL(9, 82, 15), // "saveForceSlopes"
QT_MOC_LITERAL(10, 98, 14), // "saveInterlocks"
QT_MOC_LITERAL(11, 113, 12), // "setPlotScale"
QT_MOC_LITERAL(12, 126, 9), // "setLCData"
QT_MOC_LITERAL(13, 136, 13), // "saveScaleData"
QT_MOC_LITERAL(14, 150, 10), // "saveLCData"
QT_MOC_LITERAL(15, 161, 18), // "getActOneDispScale"
QT_MOC_LITERAL(16, 180, 18), // "getActTwoDispScale"
QT_MOC_LITERAL(17, 199, 19), // "getActOneForceScale"
QT_MOC_LITERAL(18, 219, 19), // "getActTwoForceScale"
QT_MOC_LITERAL(19, 239, 16), // "useFirstActuator"
QT_MOC_LITERAL(20, 256, 11), // "sendCommand"
QT_MOC_LITERAL(21, 268, 7), // "sendPID"
QT_MOC_LITERAL(22, 276, 12), // "sendPIDForce"
QT_MOC_LITERAL(23, 289, 13), // "sliderCommand"
QT_MOC_LITERAL(24, 303, 14), // "activateButton"
QT_MOC_LITERAL(25, 318, 15), // "pressSpanButton"
QT_MOC_LITERAL(26, 334, 7), // "setZero"
QT_MOC_LITERAL(27, 342, 12), // "startControl"
QT_MOC_LITERAL(28, 355, 8), // "calForce"
QT_MOC_LITERAL(29, 364, 10), // "turnOnLow1"
QT_MOC_LITERAL(30, 375, 11), // "turnOnHigh1"
QT_MOC_LITERAL(31, 387, 17), // "switchControlType"
QT_MOC_LITERAL(32, 405, 17), // "useSecondActuator"
QT_MOC_LITERAL(33, 423, 12), // "sendCommand2"
QT_MOC_LITERAL(34, 436, 8), // "sendPID2"
QT_MOC_LITERAL(35, 445, 13), // "sendPIDForce2"
QT_MOC_LITERAL(36, 459, 14), // "sliderCommand2"
QT_MOC_LITERAL(37, 474, 15), // "activateButton2"
QT_MOC_LITERAL(38, 490, 16), // "pressSpanButton2"
QT_MOC_LITERAL(39, 507, 8), // "setZero2"
QT_MOC_LITERAL(40, 516, 13), // "startControl2"
QT_MOC_LITERAL(41, 530, 9), // "calForce2"
QT_MOC_LITERAL(42, 540, 10), // "turnOnLow2"
QT_MOC_LITERAL(43, 551, 11), // "turnOnHigh2"
QT_MOC_LITERAL(44, 563, 18), // "switchControlType2"
QT_MOC_LITERAL(45, 582, 9), // "readForce"
QT_MOC_LITERAL(46, 592, 17), // "turnOffHydraulics"
QT_MOC_LITERAL(47, 610, 9), // "updateLCD"
QT_MOC_LITERAL(48, 620, 11), // "spanCommand"
QT_MOC_LITERAL(49, 632, 10), // "targetSpan"
QT_MOC_LITERAL(50, 643, 10), // "targetZero"
QT_MOC_LITERAL(51, 654, 6), // "setAmp"
QT_MOC_LITERAL(52, 661, 7), // "setFreq"
QT_MOC_LITERAL(53, 669, 7), // "sinTest"
QT_MOC_LITERAL(54, 677, 5), // "sweep"
QT_MOC_LITERAL(55, 683, 7), // "ampTest"
QT_MOC_LITERAL(56, 691, 8), // "reqloops"
QT_MOC_LITERAL(57, 700, 11), // "PSAS_Window"
QT_MOC_LITERAL(58, 712, 10), // "Cal_Window"
QT_MOC_LITERAL(59, 723, 11), // "plotResults"
QT_MOC_LITERAL(60, 735, 10), // "serialRead"
QT_MOC_LITERAL(61, 746, 4), // "comm"
QT_MOC_LITERAL(62, 751, 4), // "data"
QT_MOC_LITERAL(63, 756, 11), // "serialWrite"
QT_MOC_LITERAL(64, 768, 9), // "readFiles"
QT_MOC_LITERAL(65, 778, 33), // "std::vector<std::vector<doubl..."
QT_MOC_LITERAL(66, 812, 11), // "std::string"
QT_MOC_LITERAL(67, 824, 8), // "fileName"
QT_MOC_LITERAL(68, 833, 16), // "LinearRegression"
QT_MOC_LITERAL(69, 850, 19), // "std::vector<double>"
QT_MOC_LITERAL(70, 870, 5), // "xData"
QT_MOC_LITERAL(71, 876, 5), // "yData"
QT_MOC_LITERAL(72, 882, 10), // "sendDouble"
QT_MOC_LITERAL(73, 893, 16), // "receivedToInches"
QT_MOC_LITERAL(74, 910, 10), // "dataInBits"
QT_MOC_LITERAL(75, 921, 12), // "inchesToBits"
QT_MOC_LITERAL(76, 934, 12), // "dataInInches"
QT_MOC_LITERAL(77, 947, 16), // "Interlock_Window"
QT_MOC_LITERAL(78, 964, 24), // "readAllFilesAndCalibrate"
QT_MOC_LITERAL(79, 989, 11), // "calLoadCell"
QT_MOC_LITERAL(80, 1001, 10), // "returnLoad"
QT_MOC_LITERAL(81, 1012, 10), // "setMaxDisp"
QT_MOC_LITERAL(82, 1023, 4), // "Disp"
QT_MOC_LITERAL(83, 1028, 10), // "setMinDisp"
QT_MOC_LITERAL(84, 1039, 11), // "setMaxForce"
QT_MOC_LITERAL(85, 1051, 5), // "Force"
QT_MOC_LITERAL(86, 1057, 11), // "setMinForce"
QT_MOC_LITERAL(87, 1069, 14), // "checkInterlock"
QT_MOC_LITERAL(88, 1084, 14), // "resetInterlock"
QT_MOC_LITERAL(89, 1099, 14), // "whichInterlock"
QT_MOC_LITERAL(90, 1114, 13), // "isInterlockOn"
QT_MOC_LITERAL(91, 1128, 16), // "clearPlotVectors"
QT_MOC_LITERAL(92, 1145, 7), // "readAck"
QT_MOC_LITERAL(93, 1153, 9), // "loadModel"
QT_MOC_LITERAL(94, 1163, 13), // "loadActuators"
QT_MOC_LITERAL(95, 1177, 8), // "getForce"
QT_MOC_LITERAL(96, 1186, 9), // "getForce2"
QT_MOC_LITERAL(97, 1196, 10), // "getMaxSpan"
QT_MOC_LITERAL(98, 1207, 11), // "getMaxSpan2"
QT_MOC_LITERAL(99, 1219, 10), // "getMinSpan"
QT_MOC_LITERAL(100, 1230, 11), // "getMinSpan2"
QT_MOC_LITERAL(101, 1242, 11), // "getMaxForce"
QT_MOC_LITERAL(102, 1254, 12), // "getMaxForce2"
QT_MOC_LITERAL(103, 1267, 11), // "getMinForce"
QT_MOC_LITERAL(104, 1279, 12), // "getMinForce2"
QT_MOC_LITERAL(105, 1292, 6) // "update"

    },
    "hsm_full\0sendSignal\0\0value\0updatePlot\0"
    "stiffTest\0save\0initializeController\0"
    "channel\0saveForceSlopes\0saveInterlocks\0"
    "setPlotScale\0setLCData\0saveScaleData\0"
    "saveLCData\0getActOneDispScale\0"
    "getActTwoDispScale\0getActOneForceScale\0"
    "getActTwoForceScale\0useFirstActuator\0"
    "sendCommand\0sendPID\0sendPIDForce\0"
    "sliderCommand\0activateButton\0"
    "pressSpanButton\0setZero\0startControl\0"
    "calForce\0turnOnLow1\0turnOnHigh1\0"
    "switchControlType\0useSecondActuator\0"
    "sendCommand2\0sendPID2\0sendPIDForce2\0"
    "sliderCommand2\0activateButton2\0"
    "pressSpanButton2\0setZero2\0startControl2\0"
    "calForce2\0turnOnLow2\0turnOnHigh2\0"
    "switchControlType2\0readForce\0"
    "turnOffHydraulics\0updateLCD\0spanCommand\0"
    "targetSpan\0targetZero\0setAmp\0setFreq\0"
    "sinTest\0sweep\0ampTest\0reqloops\0"
    "PSAS_Window\0Cal_Window\0plotResults\0"
    "serialRead\0comm\0data\0serialWrite\0"
    "readFiles\0std::vector<std::vector<double> >\0"
    "std::string\0fileName\0LinearRegression\0"
    "std::vector<double>\0xData\0yData\0"
    "sendDouble\0receivedToInches\0dataInBits\0"
    "inchesToBits\0dataInInches\0Interlock_Window\0"
    "readAllFilesAndCalibrate\0calLoadCell\0"
    "returnLoad\0setMaxDisp\0Disp\0setMinDisp\0"
    "setMaxForce\0Force\0setMinForce\0"
    "checkInterlock\0resetInterlock\0"
    "whichInterlock\0isInterlockOn\0"
    "clearPlotVectors\0readAck\0loadModel\0"
    "loadActuators\0getForce\0getForce2\0"
    "getMaxSpan\0getMaxSpan2\0getMinSpan\0"
    "getMinSpan2\0getMaxForce\0getMaxForce2\0"
    "getMinForce\0getMinForce2\0update"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_hsm_full[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      87,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  449,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,  452,    2, 0x0a /* Public */,
       5,    0,  453,    2, 0x0a /* Public */,
       6,    0,  454,    2, 0x0a /* Public */,
       7,    1,  455,    2, 0x0a /* Public */,
       9,    0,  458,    2, 0x0a /* Public */,
      10,    0,  459,    2, 0x0a /* Public */,
      11,    0,  460,    2, 0x0a /* Public */,
      12,    0,  461,    2, 0x0a /* Public */,
      13,    0,  462,    2, 0x0a /* Public */,
      14,    0,  463,    2, 0x0a /* Public */,
      15,    0,  464,    2, 0x0a /* Public */,
      16,    0,  465,    2, 0x0a /* Public */,
      17,    0,  466,    2, 0x0a /* Public */,
      18,    0,  467,    2, 0x0a /* Public */,
      19,    0,  468,    2, 0x0a /* Public */,
      20,    0,  469,    2, 0x0a /* Public */,
      21,    0,  470,    2, 0x0a /* Public */,
      22,    0,  471,    2, 0x0a /* Public */,
      23,    0,  472,    2, 0x0a /* Public */,
      24,    0,  473,    2, 0x0a /* Public */,
      25,    0,  474,    2, 0x0a /* Public */,
      26,    0,  475,    2, 0x0a /* Public */,
      27,    0,  476,    2, 0x0a /* Public */,
      28,    0,  477,    2, 0x0a /* Public */,
      29,    0,  478,    2, 0x0a /* Public */,
      30,    0,  479,    2, 0x0a /* Public */,
      31,    0,  480,    2, 0x0a /* Public */,
      32,    0,  481,    2, 0x0a /* Public */,
      33,    0,  482,    2, 0x0a /* Public */,
      34,    0,  483,    2, 0x0a /* Public */,
      35,    0,  484,    2, 0x0a /* Public */,
      36,    0,  485,    2, 0x0a /* Public */,
      37,    0,  486,    2, 0x0a /* Public */,
      38,    0,  487,    2, 0x0a /* Public */,
      39,    0,  488,    2, 0x0a /* Public */,
      40,    0,  489,    2, 0x0a /* Public */,
      41,    0,  490,    2, 0x0a /* Public */,
      42,    0,  491,    2, 0x0a /* Public */,
      43,    0,  492,    2, 0x0a /* Public */,
      44,    0,  493,    2, 0x0a /* Public */,
      45,    1,  494,    2, 0x0a /* Public */,
      46,    0,  497,    2, 0x0a /* Public */,
      47,    0,  498,    2, 0x0a /* Public */,
      48,    3,  499,    2, 0x0a /* Public */,
      51,    0,  506,    2, 0x0a /* Public */,
      52,    0,  507,    2, 0x0a /* Public */,
      53,    0,  508,    2, 0x0a /* Public */,
      54,    0,  509,    2, 0x0a /* Public */,
      55,    0,  510,    2, 0x0a /* Public */,
      56,    0,  511,    2, 0x0a /* Public */,
      57,    0,  512,    2, 0x0a /* Public */,
      58,    0,  513,    2, 0x0a /* Public */,
      59,    0,  514,    2, 0x0a /* Public */,
      60,    3,  515,    2, 0x0a /* Public */,
      63,    3,  522,    2, 0x0a /* Public */,
      64,    1,  529,    2, 0x0a /* Public */,
      68,    2,  532,    2, 0x0a /* Public */,
      72,    3,  537,    2, 0x0a /* Public */,
      73,    2,  544,    2, 0x0a /* Public */,
      75,    2,  549,    2, 0x0a /* Public */,
      77,    0,  554,    2, 0x0a /* Public */,
      78,    0,  555,    2, 0x0a /* Public */,
      79,    2,  556,    2, 0x0a /* Public */,
      80,    1,  561,    2, 0x0a /* Public */,
      81,    2,  564,    2, 0x0a /* Public */,
      83,    2,  569,    2, 0x0a /* Public */,
      84,    2,  574,    2, 0x0a /* Public */,
      86,    2,  579,    2, 0x0a /* Public */,
      87,    0,  584,    2, 0x0a /* Public */,
      88,    2,  585,    2, 0x0a /* Public */,
      90,    2,  590,    2, 0x0a /* Public */,
      91,    0,  595,    2, 0x0a /* Public */,
      92,    1,  596,    2, 0x0a /* Public */,
      93,    0,  599,    2, 0x0a /* Public */,
      94,    0,  600,    2, 0x0a /* Public */,
      95,    0,  601,    2, 0x0a /* Public */,
      96,    0,  602,    2, 0x0a /* Public */,
      97,    0,  603,    2, 0x0a /* Public */,
      98,    0,  604,    2, 0x0a /* Public */,
      99,    0,  605,    2, 0x0a /* Public */,
     100,    0,  606,    2, 0x0a /* Public */,
     101,    0,  607,    2, 0x0a /* Public */,
     102,    0,  608,    2, 0x0a /* Public */,
     103,    0,  609,    2, 0x0a /* Public */,
     104,    0,  610,    2, 0x0a /* Public */,
     105,    0,  611,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Double,
    QMetaType::Double,
    QMetaType::Double,
    QMetaType::Double,
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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Double, QMetaType::Double,    8,   49,   50,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    8,   61,   62,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    8,   61,   62,
    0x80000000 | 65, 0x80000000 | 66,   67,
    0x80000000 | 69, 0x80000000 | 69, 0x80000000 | 69,   70,   71,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Double,    8,   61,   62,
    QMetaType::Double, QMetaType::Int, QMetaType::Int,    8,   74,
    QMetaType::Int, QMetaType::Int, QMetaType::Double,    8,   76,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    3,
    QMetaType::Double, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::Double,    8,   82,
    QMetaType::Void, QMetaType::Int, QMetaType::Double,    8,   82,
    QMetaType::Void, QMetaType::Int, QMetaType::Double,    8,   85,
    QMetaType::Void, QMetaType::Int, QMetaType::Double,    8,   85,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,   89,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,    8,   89,
    QMetaType::Void,
    QMetaType::Int, QMetaType::Int,    8,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Double,
    QMetaType::Double,
    QMetaType::Double,
    QMetaType::Double,
    QMetaType::Double,
    QMetaType::Double,
    QMetaType::Double,
    QMetaType::Double,
    QMetaType::Double,
    QMetaType::Double,
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
        case 4: _t->initializeController((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->saveForceSlopes(); break;
        case 6: _t->saveInterlocks(); break;
        case 7: _t->setPlotScale(); break;
        case 8: _t->setLCData(); break;
        case 9: _t->saveScaleData(); break;
        case 10: _t->saveLCData(); break;
        case 11: { double _r = _t->getActOneDispScale();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 12: { double _r = _t->getActTwoDispScale();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 13: { double _r = _t->getActOneForceScale();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 14: { double _r = _t->getActTwoForceScale();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 15: _t->useFirstActuator(); break;
        case 16: _t->sendCommand(); break;
        case 17: _t->sendPID(); break;
        case 18: _t->sendPIDForce(); break;
        case 19: _t->sliderCommand(); break;
        case 20: _t->activateButton(); break;
        case 21: _t->pressSpanButton(); break;
        case 22: _t->setZero(); break;
        case 23: _t->startControl(); break;
        case 24: _t->calForce(); break;
        case 25: _t->turnOnLow1(); break;
        case 26: _t->turnOnHigh1(); break;
        case 27: _t->switchControlType(); break;
        case 28: _t->useSecondActuator(); break;
        case 29: _t->sendCommand2(); break;
        case 30: _t->sendPID2(); break;
        case 31: _t->sendPIDForce2(); break;
        case 32: _t->sliderCommand2(); break;
        case 33: _t->activateButton2(); break;
        case 34: _t->pressSpanButton2(); break;
        case 35: _t->setZero2(); break;
        case 36: _t->startControl2(); break;
        case 37: _t->calForce2(); break;
        case 38: _t->turnOnLow2(); break;
        case 39: _t->turnOnHigh2(); break;
        case 40: _t->switchControlType2(); break;
        case 41: _t->readForce((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 42: _t->turnOffHydraulics(); break;
        case 43: _t->updateLCD(); break;
        case 44: _t->spanCommand((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 45: _t->setAmp(); break;
        case 46: _t->setFreq(); break;
        case 47: _t->sinTest(); break;
        case 48: _t->sweep(); break;
        case 49: _t->ampTest(); break;
        case 50: _t->reqloops(); break;
        case 51: _t->PSAS_Window(); break;
        case 52: _t->Cal_Window(); break;
        case 53: { int _r = _t->plotResults();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 54: { int _r = _t->serialRead((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 55: _t->serialWrite((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 56: { std::vector<std::vector<double> > _r = _t->readFiles((*reinterpret_cast< std::string(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< std::vector<std::vector<double> >*>(_a[0]) = std::move(_r); }  break;
        case 57: { std::vector<double> _r = _t->LinearRegression((*reinterpret_cast< std::vector<double>(*)>(_a[1])),(*reinterpret_cast< std::vector<double>(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< std::vector<double>*>(_a[0]) = std::move(_r); }  break;
        case 58: _t->sendDouble((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 59: { double _r = _t->receivedToInches((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 60: { int _r = _t->inchesToBits((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 61: _t->Interlock_Window(); break;
        case 62: _t->readAllFilesAndCalibrate(); break;
        case 63: _t->calLoadCell((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 64: { double _r = _t->returnLoad((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 65: _t->setMaxDisp((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 66: _t->setMinDisp((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 67: _t->setMaxForce((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 68: _t->setMinForce((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 69: _t->checkInterlock(); break;
        case 70: _t->resetInterlock((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 71: { int _r = _t->isInterlockOn((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 72: _t->clearPlotVectors(); break;
        case 73: { int _r = _t->readAck((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 74: { int _r = _t->loadModel();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 75: _t->loadActuators(); break;
        case 76: { double _r = _t->getForce();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 77: { double _r = _t->getForce2();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 78: { double _r = _t->getMaxSpan();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 79: { double _r = _t->getMaxSpan2();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 80: { double _r = _t->getMinSpan();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 81: { double _r = _t->getMinSpan2();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 82: { double _r = _t->getMaxForce();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 83: { double _r = _t->getMaxForce2();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 84: { double _r = _t->getMinForce();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 85: { double _r = _t->getMinForce2();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 86: { int _r = _t->update();
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
        if (_id < 87)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 87;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 87)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 87;
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
    QByteArrayData data[20];
    char stringdata0[272];
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
QT_MOC_LITERAL(18, 236, 15), // "CustomEl_Window"
QT_MOC_LITERAL(19, 252, 19) // "SavePickedActuators"

    },
    "PSAS\0add_Node_to_Model\0\0remove_Node_from_Model\0"
    "add_Element_to_Model\0remove_Element_from_Model\0"
    "add_el_props\0add_BCs\0add_el_load\0"
    "add_node_load\0setupModel\0switchDim\0"
    "plotModel\0HybridEl_Window\0enableHybrid\0"
    "submitEQ\0submitDynOpt\0enableCustom\0"
    "CustomEl_Window\0SavePickedActuators"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PSAS[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x0a /* Public */,
       3,    0,  105,    2, 0x0a /* Public */,
       4,    0,  106,    2, 0x0a /* Public */,
       5,    0,  107,    2, 0x0a /* Public */,
       6,    0,  108,    2, 0x0a /* Public */,
       7,    0,  109,    2, 0x0a /* Public */,
       8,    0,  110,    2, 0x0a /* Public */,
       9,    0,  111,    2, 0x0a /* Public */,
      10,    0,  112,    2, 0x0a /* Public */,
      11,    0,  113,    2, 0x0a /* Public */,
      12,    0,  114,    2, 0x0a /* Public */,
      13,    0,  115,    2, 0x0a /* Public */,
      14,    0,  116,    2, 0x0a /* Public */,
      15,    0,  117,    2, 0x0a /* Public */,
      16,    0,  118,    2, 0x0a /* Public */,
      17,    0,  119,    2, 0x0a /* Public */,
      18,    0,  120,    2, 0x0a /* Public */,
      19,    0,  121,    2, 0x0a /* Public */,

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
        case 17: _t->SavePickedActuators(); break;
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
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
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
    char stringdata0[109];
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
QT_MOC_LITERAL(8, 69, 14), // "activatePotCal"
QT_MOC_LITERAL(9, 84, 9), // "BitToInch"
QT_MOC_LITERAL(10, 94, 6), // "bitVal"
QT_MOC_LITERAL(11, 101, 7) // "loadCal"

    },
    "SpanCalibration\0startCalibration\0\0"
    "plotCal\0QVector<double>\0X\0Y\0potCal\0"
    "activatePotCal\0BitToInch\0bitVal\0loadCal"
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
       9,    1,   52,    2, 0x0a /* Public */,
      11,    0,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 4,    5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Double, QMetaType::Int,   10,
    QMetaType::Void,

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
        case 3: _t->activatePotCal(); break;
        case 4: { double _r = _t->BitToInch((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->loadCal(); break;
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
struct qt_meta_stringdata_Interlock_t {
    QByteArrayData data[1];
    char stringdata0[10];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Interlock_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Interlock_t qt_meta_stringdata_Interlock = {
    {
QT_MOC_LITERAL(0, 0, 9) // "Interlock"

    },
    "Interlock"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Interlock[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void Interlock::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Interlock::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_Interlock.data,
    qt_meta_data_Interlock,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Interlock::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Interlock::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Interlock.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Interlock::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
