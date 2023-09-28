/********************************************************************************
** Form generated from reading UI file 'spancalibration.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPANCALIBRATION_H
#define UI_SPANCALIBRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_SpanCalibration
{
public:
    QwtPlot *CalibrationPlot;
    QPushButton *SpanCalButton;
    QTextBrowser *Instructions;
    QLCDNumber *curSpanDisplay;
    QPushButton *PotCalButton;
    QDoubleSpinBox *setTotSpan;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *selectLoadCell;
    QPushButton *calibrateLoadCell;
    QLabel *label_3;
    QSpinBox *ControllerSelect;
    QLabel *label_4;

    void setupUi(QWidget *SpanCalibration)
    {
        if (SpanCalibration->objectName().isEmpty())
            SpanCalibration->setObjectName(QString::fromUtf8("SpanCalibration"));
        SpanCalibration->resize(909, 554);
        CalibrationPlot = new QwtPlot(SpanCalibration);
        CalibrationPlot->setObjectName(QString::fromUtf8("CalibrationPlot"));
        CalibrationPlot->setGeometry(QRect(30, 30, 541, 331));
        SpanCalButton = new QPushButton(SpanCalibration);
        SpanCalButton->setObjectName(QString::fromUtf8("SpanCalButton"));
        SpanCalButton->setEnabled(true);
        SpanCalButton->setGeometry(QRect(110, 400, 181, 21));
        Instructions = new QTextBrowser(SpanCalibration);
        Instructions->setObjectName(QString::fromUtf8("Instructions"));
        Instructions->setGeometry(QRect(600, 30, 256, 192));
        curSpanDisplay = new QLCDNumber(SpanCalibration);
        curSpanDisplay->setObjectName(QString::fromUtf8("curSpanDisplay"));
        curSpanDisplay->setGeometry(QRect(500, 400, 64, 23));
        PotCalButton = new QPushButton(SpanCalibration);
        PotCalButton->setObjectName(QString::fromUtf8("PotCalButton"));
        PotCalButton->setGeometry(QRect(320, 430, 111, 23));
        setTotSpan = new QDoubleSpinBox(SpanCalibration);
        setTotSpan->setObjectName(QString::fromUtf8("setTotSpan"));
        setTotSpan->setGeometry(QRect(320, 400, 111, 24));
        setTotSpan->setDecimals(4);
        label = new QLabel(SpanCalibration);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(320, 380, 161, 16));
        label_2 = new QLabel(SpanCalibration);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(500, 380, 161, 16));
        selectLoadCell = new QSpinBox(SpanCalibration);
        selectLoadCell->setObjectName(QString::fromUtf8("selectLoadCell"));
        selectLoadCell->setEnabled(false);
        selectLoadCell->setGeometry(QRect(670, 400, 43, 24));
        selectLoadCell->setMinimum(1);
        calibrateLoadCell = new QPushButton(SpanCalibration);
        calibrateLoadCell->setObjectName(QString::fromUtf8("calibrateLoadCell"));
        calibrateLoadCell->setEnabled(false);
        calibrateLoadCell->setGeometry(QRect(720, 400, 111, 23));
        label_3 = new QLabel(SpanCalibration);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setEnabled(false);
        label_3->setGeometry(QRect(670, 380, 161, 16));
        ControllerSelect = new QSpinBox(SpanCalibration);
        ControllerSelect->setObjectName(QString::fromUtf8("ControllerSelect"));
        ControllerSelect->setGeometry(QRect(10, 400, 43, 24));
        ControllerSelect->setMinimum(1);
        label_4 = new QLabel(SpanCalibration);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 380, 161, 16));

        retranslateUi(SpanCalibration);

        QMetaObject::connectSlotsByName(SpanCalibration);
    } // setupUi

    void retranslateUi(QWidget *SpanCalibration)
    {
        SpanCalibration->setWindowTitle(QCoreApplication::translate("SpanCalibration", "Form", nullptr));
        SpanCalButton->setText(QCoreApplication::translate("SpanCalibration", "Calibrate Span", nullptr));
        PotCalButton->setText(QCoreApplication::translate("SpanCalibration", "Add Cal Point", nullptr));
        label->setText(QCoreApplication::translate("SpanCalibration", "Target Inches", nullptr));
        label_2->setText(QCoreApplication::translate("SpanCalibration", "Current total span", nullptr));
        calibrateLoadCell->setText(QCoreApplication::translate("SpanCalibration", "Calibrate Load", nullptr));
        label_3->setText(QCoreApplication::translate("SpanCalibration", "Select Load Cell", nullptr));
        label_4->setText(QCoreApplication::translate("SpanCalibration", "Select Controller", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SpanCalibration: public Ui_SpanCalibration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPANCALIBRATION_H
