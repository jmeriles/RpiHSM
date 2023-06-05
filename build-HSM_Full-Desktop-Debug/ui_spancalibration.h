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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_SpanCalibration
{
public:
    QwtPlot *CalibrationPlot;
    QPushButton *SpanCalButton;
    QPushButton *PotCalButton;
    QTextBrowser *Instructions;
    QLCDNumber *curSpanDisplay;
    QPushButton *setTotSpanButton;
    QDoubleSpinBox *setTotSpan;
    QLabel *label;
    QLabel *label_2;
    QCheckBox *activatePotCal;

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
        SpanCalButton->setEnabled(false);
        SpanCalButton->setGeometry(QRect(110, 400, 181, 21));
        PotCalButton = new QPushButton(SpanCalibration);
        PotCalButton->setObjectName(QString::fromUtf8("PotCalButton"));
        PotCalButton->setEnabled(false);
        PotCalButton->setGeometry(QRect(110, 440, 181, 21));
        Instructions = new QTextBrowser(SpanCalibration);
        Instructions->setObjectName(QString::fromUtf8("Instructions"));
        Instructions->setGeometry(QRect(600, 30, 256, 192));
        curSpanDisplay = new QLCDNumber(SpanCalibration);
        curSpanDisplay->setObjectName(QString::fromUtf8("curSpanDisplay"));
        curSpanDisplay->setGeometry(QRect(500, 400, 64, 23));
        setTotSpanButton = new QPushButton(SpanCalibration);
        setTotSpanButton->setObjectName(QString::fromUtf8("setTotSpanButton"));
        setTotSpanButton->setGeometry(QRect(320, 430, 111, 23));
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
        activatePotCal = new QCheckBox(SpanCalibration);
        activatePotCal->setObjectName(QString::fromUtf8("activatePotCal"));
        activatePotCal->setGeometry(QRect(110, 460, 111, 41));

        retranslateUi(SpanCalibration);

        QMetaObject::connectSlotsByName(SpanCalibration);
    } // setupUi

    void retranslateUi(QWidget *SpanCalibration)
    {
        SpanCalibration->setWindowTitle(QCoreApplication::translate("SpanCalibration", "Form", nullptr));
        SpanCalButton->setText(QCoreApplication::translate("SpanCalibration", "Calibrate Span", nullptr));
        PotCalButton->setText(QCoreApplication::translate("SpanCalibration", "Calibrate Potentiometer", nullptr));
        setTotSpanButton->setText(QCoreApplication::translate("SpanCalibration", "Add Cal Point", nullptr));
        label->setText(QCoreApplication::translate("SpanCalibration", "Target Inches", nullptr));
        label_2->setText(QCoreApplication::translate("SpanCalibration", "Current total span", nullptr));
        activatePotCal->setText(QCoreApplication::translate("SpanCalibration", "Activate Pot Cal", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SpanCalibration: public Ui_SpanCalibration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPANCALIBRATION_H
