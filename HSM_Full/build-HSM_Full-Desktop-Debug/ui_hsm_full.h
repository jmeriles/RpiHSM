/********************************************************************************
** Form generated from reading UI file 'hsm_full.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HSM_FULL_H
#define UI_HSM_FULL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_hsm_full
{
public:
    QWidget *centralWidget;
    QwtPlot *qwtPlot;
    QPushButton *SpanButton;
    QLCDNumber *CommandNum;
    QLCDNumber *CurPos;
    QSlider *horizontalSlider;
    QLCDNumber *Offset;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLCDNumber *CurSpan;
    QLabel *label_4;
    QLabel *label_5;
    QLCDNumber *Force;
    QLabel *label_6;
    QPushButton *CommandButton;
    QPushButton *SliderButton;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QPushButton *PButton;
    QPushButton *IButton;
    QPushButton *DButton;
    QDoubleSpinBox *CommandInput;
    QDoubleSpinBox *SpanInput;
    QDoubleSpinBox *PInput;
    QDoubleSpinBox *IInput;
    QDoubleSpinBox *DInput;
    QPushButton *zeroButton;
    QPushButton *SinButton;
    QDoubleSpinBox *AmpInput;
    QDoubleSpinBox *FreqInput;
    QPushButton *FreqButton;
    QPushButton *AmpButton;
    QLCDNumber *PDisp;
    QLCDNumber *IDisp;
    QLCDNumber *DDisp;
    QPushButton *SweepButton;
    QPushButton *fZeroButton;
    QPushButton *PSASButton;
    QPushButton *StartControl;
    QLCDNumber *Stiffness;
    QLabel *label_10;
    QPushButton *plotResults;
    QPushButton *AmpTestButton;
    QPushButton *PinButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *hsm_full)
    {
        if (hsm_full->objectName().isEmpty())
            hsm_full->setObjectName(QString::fromUtf8("hsm_full"));
        hsm_full->resize(798, 661);
        centralWidget = new QWidget(hsm_full);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        qwtPlot = new QwtPlot(centralWidget);
        qwtPlot->setObjectName(QString::fromUtf8("qwtPlot"));
        qwtPlot->setGeometry(QRect(20, 20, 400, 200));
        SpanButton = new QPushButton(centralWidget);
        SpanButton->setObjectName(QString::fromUtf8("SpanButton"));
        SpanButton->setGeometry(QRect(580, 420, 101, 30));
        CommandNum = new QLCDNumber(centralWidget);
        CommandNum->setObjectName(QString::fromUtf8("CommandNum"));
        CommandNum->setGeometry(QRect(650, 100, 64, 31));
        CurPos = new QLCDNumber(centralWidget);
        CurPos->setObjectName(QString::fromUtf8("CurPos"));
        CurPos->setGeometry(QRect(480, 220, 64, 31));
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(479, 100, 161, 26));
        horizontalSlider->setMinimum(0);
        horizontalSlider->setMaximum(1023);
        horizontalSlider->setSliderPosition(512);
        horizontalSlider->setOrientation(Qt::Horizontal);
        Offset = new QLCDNumber(centralWidget);
        Offset->setObjectName(QString::fromUtf8("Offset"));
        Offset->setGeometry(QRect(480, 260, 64, 31));
        Offset->setSmallDecimalPoint(false);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(510, 20, 101, 22));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(560, 220, 141, 22));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(560, 260, 151, 22));
        CurSpan = new QLCDNumber(centralWidget);
        CurSpan->setObjectName(QString::fromUtf8("CurSpan"));
        CurSpan->setGeometry(QRect(700, 420, 64, 31));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(690, 390, 101, 22));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(480, 390, 81, 22));
        Force = new QLCDNumber(centralWidget);
        Force->setObjectName(QString::fromUtf8("Force"));
        Force->setGeometry(QRect(480, 300, 64, 31));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(560, 300, 141, 22));
        CommandButton = new QPushButton(centralWidget);
        CommandButton->setObjectName(QString::fromUtf8("CommandButton"));
        CommandButton->setGeometry(QRect(590, 50, 131, 30));
        SliderButton = new QPushButton(centralWidget);
        SliderButton->setObjectName(QString::fromUtf8("SliderButton"));
        SliderButton->setGeometry(QRect(490, 130, 131, 30));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(40, 410, 21, 22));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(170, 410, 21, 22));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(290, 410, 21, 22));
        PButton = new QPushButton(centralWidget);
        PButton->setObjectName(QString::fromUtf8("PButton"));
        PButton->setGeometry(QRect(70, 480, 61, 30));
        IButton = new QPushButton(centralWidget);
        IButton->setObjectName(QString::fromUtf8("IButton"));
        IButton->setGeometry(QRect(190, 480, 61, 30));
        DButton = new QPushButton(centralWidget);
        DButton->setObjectName(QString::fromUtf8("DButton"));
        DButton->setGeometry(QRect(310, 480, 61, 30));
        CommandInput = new QDoubleSpinBox(centralWidget);
        CommandInput->setObjectName(QString::fromUtf8("CommandInput"));
        CommandInput->setGeometry(QRect(500, 50, 71, 32));
        CommandInput->setMinimum(-100.000000000000000);
        CommandInput->setMaximum(100.000000000000000);
        SpanInput = new QDoubleSpinBox(centralWidget);
        SpanInput->setObjectName(QString::fromUtf8("SpanInput"));
        SpanInput->setGeometry(QRect(480, 420, 81, 32));
        PInput = new QDoubleSpinBox(centralWidget);
        PInput->setObjectName(QString::fromUtf8("PInput"));
        PInput->setGeometry(QRect(60, 440, 81, 32));
        IInput = new QDoubleSpinBox(centralWidget);
        IInput->setObjectName(QString::fromUtf8("IInput"));
        IInput->setGeometry(QRect(180, 440, 81, 32));
        IInput->setDecimals(10);
        DInput = new QDoubleSpinBox(centralWidget);
        DInput->setObjectName(QString::fromUtf8("DInput"));
        DInput->setGeometry(QRect(300, 440, 81, 32));
        zeroButton = new QPushButton(centralWidget);
        zeroButton->setObjectName(QString::fromUtf8("zeroButton"));
        zeroButton->setGeometry(QRect(678, 220, 111, 30));
        SinButton = new QPushButton(centralWidget);
        SinButton->setObjectName(QString::fromUtf8("SinButton"));
        SinButton->setGeometry(QRect(370, 280, 91, 30));
        AmpInput = new QDoubleSpinBox(centralWidget);
        AmpInput->setObjectName(QString::fromUtf8("AmpInput"));
        AmpInput->setGeometry(QRect(40, 300, 71, 32));
        FreqInput = new QDoubleSpinBox(centralWidget);
        FreqInput->setObjectName(QString::fromUtf8("FreqInput"));
        FreqInput->setGeometry(QRect(210, 300, 71, 32));
        FreqButton = new QPushButton(centralWidget);
        FreqButton->setObjectName(QString::fromUtf8("FreqButton"));
        FreqButton->setGeometry(QRect(290, 300, 61, 30));
        AmpButton = new QPushButton(centralWidget);
        AmpButton->setObjectName(QString::fromUtf8("AmpButton"));
        AmpButton->setGeometry(QRect(120, 300, 61, 30));
        PDisp = new QLCDNumber(centralWidget);
        PDisp->setObjectName(QString::fromUtf8("PDisp"));
        PDisp->setGeometry(QRect(60, 402, 64, 31));
        IDisp = new QLCDNumber(centralWidget);
        IDisp->setObjectName(QString::fromUtf8("IDisp"));
        IDisp->setGeometry(QRect(180, 402, 71, 31));
        IDisp->setDigitCount(9);
        DDisp = new QLCDNumber(centralWidget);
        DDisp->setObjectName(QString::fromUtf8("DDisp"));
        DDisp->setGeometry(QRect(300, 402, 64, 31));
        SweepButton = new QPushButton(centralWidget);
        SweepButton->setObjectName(QString::fromUtf8("SweepButton"));
        SweepButton->setGeometry(QRect(370, 320, 91, 30));
        fZeroButton = new QPushButton(centralWidget);
        fZeroButton->setObjectName(QString::fromUtf8("fZeroButton"));
        fZeroButton->setGeometry(QRect(678, 300, 111, 30));
        PSASButton = new QPushButton(centralWidget);
        PSASButton->setObjectName(QString::fromUtf8("PSASButton"));
        PSASButton->setGeometry(QRect(40, 550, 121, 30));
        StartControl = new QPushButton(centralWidget);
        StartControl->setObjectName(QString::fromUtf8("StartControl"));
        StartControl->setGeometry(QRect(190, 550, 131, 30));
        Stiffness = new QLCDNumber(centralWidget);
        Stiffness->setObjectName(QString::fromUtf8("Stiffness"));
        Stiffness->setGeometry(QRect(480, 340, 64, 31));
        Stiffness->setDigitCount(7);
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(560, 340, 121, 22));
        plotResults = new QPushButton(centralWidget);
        plotResults->setObjectName(QString::fromUtf8("plotResults"));
        plotResults->setGeometry(QRect(350, 550, 131, 30));
        AmpTestButton = new QPushButton(centralWidget);
        AmpTestButton->setObjectName(QString::fromUtf8("AmpTestButton"));
        AmpTestButton->setGeometry(QRect(370, 360, 91, 30));
        PinButton = new QPushButton(centralWidget);
        PinButton->setObjectName(QString::fromUtf8("PinButton"));
        PinButton->setGeometry(QRect(650, 550, 131, 30));
        hsm_full->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(hsm_full);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 798, 27));
        hsm_full->setMenuBar(menuBar);
        mainToolBar = new QToolBar(hsm_full);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        hsm_full->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(hsm_full);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        hsm_full->setStatusBar(statusBar);

        retranslateUi(hsm_full);

        QMetaObject::connectSlotsByName(hsm_full);
    } // setupUi

    void retranslateUi(QMainWindow *hsm_full)
    {
        hsm_full->setWindowTitle(QCoreApplication::translate("hsm_full", "hsm_full", nullptr));
        SpanButton->setText(QCoreApplication::translate("hsm_full", "Set Span", nullptr));
        label->setText(QCoreApplication::translate("hsm_full", "Command", nullptr));
        label_2->setText(QCoreApplication::translate("hsm_full", "Current Position", nullptr));
        label_3->setText(QCoreApplication::translate("hsm_full", "Offset from Zero", nullptr));
        label_4->setText(QCoreApplication::translate("hsm_full", "Current Span:", nullptr));
        label_5->setText(QCoreApplication::translate("hsm_full", "Input Span:", nullptr));
        label_6->setText(QCoreApplication::translate("hsm_full", "Force Reading", nullptr));
        CommandButton->setText(QCoreApplication::translate("hsm_full", "Send Command", nullptr));
        SliderButton->setText(QCoreApplication::translate("hsm_full", "Activate", nullptr));
        label_7->setText(QCoreApplication::translate("hsm_full", "P", nullptr));
        label_8->setText(QCoreApplication::translate("hsm_full", "I", nullptr));
        label_9->setText(QCoreApplication::translate("hsm_full", "D", nullptr));
        PButton->setText(QCoreApplication::translate("hsm_full", "Set", nullptr));
        IButton->setText(QCoreApplication::translate("hsm_full", "Set", nullptr));
        DButton->setText(QCoreApplication::translate("hsm_full", "Set", nullptr));
        zeroButton->setText(QCoreApplication::translate("hsm_full", "Set Zero", nullptr));
        SinButton->setText(QCoreApplication::translate("hsm_full", "Sin Test", nullptr));
        FreqButton->setText(QCoreApplication::translate("hsm_full", "Set Freq", nullptr));
        AmpButton->setText(QCoreApplication::translate("hsm_full", "Set Amp", nullptr));
        SweepButton->setText(QCoreApplication::translate("hsm_full", "Sweep", nullptr));
        fZeroButton->setText(QCoreApplication::translate("hsm_full", "Calibrate Force", nullptr));
        PSASButton->setText(QCoreApplication::translate("hsm_full", "Set Up Model", nullptr));
        StartControl->setText(QCoreApplication::translate("hsm_full", "Start Controller", nullptr));
        label_10->setText(QCoreApplication::translate("hsm_full", "Approx Stiffness", nullptr));
        plotResults->setText(QCoreApplication::translate("hsm_full", "Plot Results", nullptr));
        AmpTestButton->setText(QCoreApplication::translate("hsm_full", "Amp Test", nullptr));
        PinButton->setText(QCoreApplication::translate("hsm_full", "Pin Button", nullptr));
    } // retranslateUi

};

namespace Ui {
    class hsm_full: public Ui_hsm_full {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HSM_FULL_H
