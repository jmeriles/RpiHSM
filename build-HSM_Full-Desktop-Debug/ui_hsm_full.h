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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_hsm_full
{
public:
    QAction *actionCalibration;
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
    QLabel *label_11;
    QDoubleSpinBox *CommandInput_2;
    QPushButton *SliderButton_2;
    QLabel *label_12;
    QPushButton *CommandButton_2;
    QLCDNumber *CurSpan_2;
    QLabel *label_13;
    QLCDNumber *CurPos_2;
    QDoubleSpinBox *SpanInput_2;
    QPushButton *zeroButton_2;
    QLabel *label_14;
    QLabel *label_15;
    QSlider *horizontalSlider_2;
    QLCDNumber *CommandNum_2;
    QLabel *label_16;
    QLCDNumber *Offset_2;
    QPushButton *SpanButton_2;
    QLabel *label_17;
    QLCDNumber *Force_2;
    QPushButton *fZeroButton_2;
    QLCDNumber *Stiffness_2;
    QFrame *line;
    QLCDNumber *zeroBitDisp;
    QLCDNumber *spanBitDisp;
    QPushButton *setSpanBit;
    QPushButton *setZeroBit;
    QSpinBox *zeroBitInput;
    QSpinBox *SpanBitInput;
    QDoubleSpinBox *approxZero;
    QDoubleSpinBox *sendDouble;
    QPushButton *sendDoubleButton;
    QPushButton *ActOneLowButton;
    QPushButton *ActOneHighButton;
    QTextBrowser *Act1LowOn;
    QTextBrowser *Act1HighOn;
    QTextBrowser *Act2HighOn;
    QTextBrowser *Act2LowOn;
    QPushButton *ActTwoHighButton;
    QPushButton *ActTwoLowButton;
    QCheckBox *SecondActBox;
    QMenuBar *menuBar;
    QMenu *menuCalibration;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *hsm_full)
    {
        if (hsm_full->objectName().isEmpty())
            hsm_full->setObjectName(QString::fromUtf8("hsm_full"));
        hsm_full->resize(1143, 721);
        actionCalibration = new QAction(hsm_full);
        actionCalibration->setObjectName(QString::fromUtf8("actionCalibration"));
        centralWidget = new QWidget(hsm_full);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        qwtPlot = new QwtPlot(centralWidget);
        qwtPlot->setObjectName(QString::fromUtf8("qwtPlot"));
        qwtPlot->setGeometry(QRect(20, 20, 400, 200));
        SpanButton = new QPushButton(centralWidget);
        SpanButton->setObjectName(QString::fromUtf8("SpanButton"));
        SpanButton->setGeometry(QRect(580, 470, 101, 30));
        CommandNum = new QLCDNumber(centralWidget);
        CommandNum->setObjectName(QString::fromUtf8("CommandNum"));
        CommandNum->setGeometry(QRect(650, 190, 64, 31));
        CurPos = new QLCDNumber(centralWidget);
        CurPos->setObjectName(QString::fromUtf8("CurPos"));
        CurPos->setGeometry(QRect(480, 270, 64, 31));
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(479, 190, 161, 26));
        horizontalSlider->setMinimum(0);
        horizontalSlider->setMaximum(1023);
        horizontalSlider->setSliderPosition(512);
        horizontalSlider->setOrientation(Qt::Horizontal);
        Offset = new QLCDNumber(centralWidget);
        Offset->setObjectName(QString::fromUtf8("Offset"));
        Offset->setGeometry(QRect(480, 310, 64, 31));
        Offset->setSmallDecimalPoint(false);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(510, 110, 101, 22));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(560, 270, 141, 22));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(560, 310, 151, 22));
        CurSpan = new QLCDNumber(centralWidget);
        CurSpan->setObjectName(QString::fromUtf8("CurSpan"));
        CurSpan->setGeometry(QRect(700, 470, 64, 31));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(690, 440, 101, 22));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(480, 440, 81, 22));
        Force = new QLCDNumber(centralWidget);
        Force->setObjectName(QString::fromUtf8("Force"));
        Force->setGeometry(QRect(480, 350, 64, 31));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(560, 350, 141, 22));
        CommandButton = new QPushButton(centralWidget);
        CommandButton->setObjectName(QString::fromUtf8("CommandButton"));
        CommandButton->setGeometry(QRect(590, 140, 131, 30));
        SliderButton = new QPushButton(centralWidget);
        SliderButton->setObjectName(QString::fromUtf8("SliderButton"));
        SliderButton->setGeometry(QRect(490, 220, 131, 30));
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
        CommandInput->setGeometry(QRect(500, 140, 71, 32));
        CommandInput->setMinimum(-100.000000000000000);
        CommandInput->setMaximum(100.000000000000000);
        SpanInput = new QDoubleSpinBox(centralWidget);
        SpanInput->setObjectName(QString::fromUtf8("SpanInput"));
        SpanInput->setGeometry(QRect(480, 470, 81, 32));
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
        zeroButton->setGeometry(QRect(678, 270, 111, 30));
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
        fZeroButton->setGeometry(QRect(678, 350, 111, 30));
        PSASButton = new QPushButton(centralWidget);
        PSASButton->setObjectName(QString::fromUtf8("PSASButton"));
        PSASButton->setGeometry(QRect(40, 550, 121, 30));
        StartControl = new QPushButton(centralWidget);
        StartControl->setObjectName(QString::fromUtf8("StartControl"));
        StartControl->setGeometry(QRect(190, 550, 131, 30));
        Stiffness = new QLCDNumber(centralWidget);
        Stiffness->setObjectName(QString::fromUtf8("Stiffness"));
        Stiffness->setGeometry(QRect(480, 390, 64, 31));
        Stiffness->setDigitCount(7);
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(560, 390, 121, 22));
        plotResults = new QPushButton(centralWidget);
        plotResults->setObjectName(QString::fromUtf8("plotResults"));
        plotResults->setGeometry(QRect(350, 550, 131, 30));
        AmpTestButton = new QPushButton(centralWidget);
        AmpTestButton->setObjectName(QString::fromUtf8("AmpTestButton"));
        AmpTestButton->setGeometry(QRect(370, 360, 91, 30));
        PinButton = new QPushButton(centralWidget);
        PinButton->setObjectName(QString::fromUtf8("PinButton"));
        PinButton->setGeometry(QRect(650, 600, 131, 30));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setEnabled(false);
        label_11->setGeometry(QRect(890, 310, 151, 22));
        CommandInput_2 = new QDoubleSpinBox(centralWidget);
        CommandInput_2->setObjectName(QString::fromUtf8("CommandInput_2"));
        CommandInput_2->setEnabled(false);
        CommandInput_2->setGeometry(QRect(830, 140, 71, 32));
        CommandInput_2->setMinimum(-100.000000000000000);
        CommandInput_2->setMaximum(100.000000000000000);
        SliderButton_2 = new QPushButton(centralWidget);
        SliderButton_2->setObjectName(QString::fromUtf8("SliderButton_2"));
        SliderButton_2->setEnabled(false);
        SliderButton_2->setGeometry(QRect(820, 220, 131, 30));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setEnabled(false);
        label_12->setGeometry(QRect(890, 390, 121, 22));
        CommandButton_2 = new QPushButton(centralWidget);
        CommandButton_2->setObjectName(QString::fromUtf8("CommandButton_2"));
        CommandButton_2->setEnabled(false);
        CommandButton_2->setGeometry(QRect(920, 140, 131, 30));
        CurSpan_2 = new QLCDNumber(centralWidget);
        CurSpan_2->setObjectName(QString::fromUtf8("CurSpan_2"));
        CurSpan_2->setEnabled(false);
        CurSpan_2->setGeometry(QRect(1030, 470, 64, 31));
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setEnabled(false);
        label_13->setGeometry(QRect(1020, 440, 101, 22));
        CurPos_2 = new QLCDNumber(centralWidget);
        CurPos_2->setObjectName(QString::fromUtf8("CurPos_2"));
        CurPos_2->setEnabled(false);
        CurPos_2->setGeometry(QRect(810, 270, 64, 31));
        SpanInput_2 = new QDoubleSpinBox(centralWidget);
        SpanInput_2->setObjectName(QString::fromUtf8("SpanInput_2"));
        SpanInput_2->setEnabled(false);
        SpanInput_2->setGeometry(QRect(810, 470, 81, 32));
        zeroButton_2 = new QPushButton(centralWidget);
        zeroButton_2->setObjectName(QString::fromUtf8("zeroButton_2"));
        zeroButton_2->setEnabled(false);
        zeroButton_2->setGeometry(QRect(1008, 270, 111, 30));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setEnabled(false);
        label_14->setGeometry(QRect(890, 270, 141, 22));
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setEnabled(false);
        label_15->setGeometry(QRect(840, 110, 101, 22));
        horizontalSlider_2 = new QSlider(centralWidget);
        horizontalSlider_2->setObjectName(QString::fromUtf8("horizontalSlider_2"));
        horizontalSlider_2->setEnabled(false);
        horizontalSlider_2->setGeometry(QRect(809, 190, 161, 26));
        horizontalSlider_2->setMinimum(0);
        horizontalSlider_2->setMaximum(1023);
        horizontalSlider_2->setSliderPosition(512);
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        CommandNum_2 = new QLCDNumber(centralWidget);
        CommandNum_2->setObjectName(QString::fromUtf8("CommandNum_2"));
        CommandNum_2->setEnabled(false);
        CommandNum_2->setGeometry(QRect(980, 190, 64, 31));
        label_16 = new QLabel(centralWidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setEnabled(false);
        label_16->setGeometry(QRect(890, 350, 141, 22));
        Offset_2 = new QLCDNumber(centralWidget);
        Offset_2->setObjectName(QString::fromUtf8("Offset_2"));
        Offset_2->setEnabled(false);
        Offset_2->setGeometry(QRect(810, 310, 64, 31));
        Offset_2->setSmallDecimalPoint(false);
        SpanButton_2 = new QPushButton(centralWidget);
        SpanButton_2->setObjectName(QString::fromUtf8("SpanButton_2"));
        SpanButton_2->setEnabled(false);
        SpanButton_2->setGeometry(QRect(910, 470, 101, 30));
        label_17 = new QLabel(centralWidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setEnabled(false);
        label_17->setGeometry(QRect(810, 440, 81, 22));
        Force_2 = new QLCDNumber(centralWidget);
        Force_2->setObjectName(QString::fromUtf8("Force_2"));
        Force_2->setEnabled(false);
        Force_2->setGeometry(QRect(810, 350, 64, 31));
        fZeroButton_2 = new QPushButton(centralWidget);
        fZeroButton_2->setObjectName(QString::fromUtf8("fZeroButton_2"));
        fZeroButton_2->setEnabled(false);
        fZeroButton_2->setGeometry(QRect(1008, 350, 111, 30));
        Stiffness_2 = new QLCDNumber(centralWidget);
        Stiffness_2->setObjectName(QString::fromUtf8("Stiffness_2"));
        Stiffness_2->setEnabled(false);
        Stiffness_2->setGeometry(QRect(810, 390, 64, 31));
        Stiffness_2->setDigitCount(7);
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(790, 0, 20, 661));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        zeroBitDisp = new QLCDNumber(centralWidget);
        zeroBitDisp->setObjectName(QString::fromUtf8("zeroBitDisp"));
        zeroBitDisp->setEnabled(true);
        zeroBitDisp->setGeometry(QRect(910, 510, 64, 31));
        spanBitDisp = new QLCDNumber(centralWidget);
        spanBitDisp->setObjectName(QString::fromUtf8("spanBitDisp"));
        spanBitDisp->setEnabled(true);
        spanBitDisp->setGeometry(QRect(910, 550, 64, 31));
        spanBitDisp->setSmallDecimalPoint(false);
        setSpanBit = new QPushButton(centralWidget);
        setSpanBit->setObjectName(QString::fromUtf8("setSpanBit"));
        setSpanBit->setEnabled(true);
        setSpanBit->setGeometry(QRect(1010, 550, 101, 30));
        setZeroBit = new QPushButton(centralWidget);
        setZeroBit->setObjectName(QString::fromUtf8("setZeroBit"));
        setZeroBit->setEnabled(true);
        setZeroBit->setGeometry(QRect(1010, 510, 101, 30));
        zeroBitInput = new QSpinBox(centralWidget);
        zeroBitInput->setObjectName(QString::fromUtf8("zeroBitInput"));
        zeroBitInput->setEnabled(true);
        zeroBitInput->setGeometry(QRect(810, 510, 81, 24));
        zeroBitInput->setMaximum(4095);
        SpanBitInput = new QSpinBox(centralWidget);
        SpanBitInput->setObjectName(QString::fromUtf8("SpanBitInput"));
        SpanBitInput->setEnabled(true);
        SpanBitInput->setGeometry(QRect(810, 550, 81, 24));
        SpanBitInput->setMaximum(255);
        approxZero = new QDoubleSpinBox(centralWidget);
        approxZero->setObjectName(QString::fromUtf8("approxZero"));
        approxZero->setGeometry(QRect(480, 510, 81, 32));
        approxZero->setMinimum(-99.000000000000000);
        sendDouble = new QDoubleSpinBox(centralWidget);
        sendDouble->setObjectName(QString::fromUtf8("sendDouble"));
        sendDouble->setEnabled(true);
        sendDouble->setGeometry(QRect(870, 600, 81, 32));
        sendDouble->setMinimum(-99.000000000000000);
        sendDoubleButton = new QPushButton(centralWidget);
        sendDoubleButton->setObjectName(QString::fromUtf8("sendDoubleButton"));
        sendDoubleButton->setEnabled(true);
        sendDoubleButton->setGeometry(QRect(1010, 600, 101, 30));
        ActOneLowButton = new QPushButton(centralWidget);
        ActOneLowButton->setObjectName(QString::fromUtf8("ActOneLowButton"));
        ActOneLowButton->setGeometry(QRect(500, 70, 51, 30));
        ActOneHighButton = new QPushButton(centralWidget);
        ActOneHighButton->setObjectName(QString::fromUtf8("ActOneHighButton"));
        ActOneHighButton->setGeometry(QRect(650, 70, 51, 30));
        Act1LowOn = new QTextBrowser(centralWidget);
        Act1LowOn->setObjectName(QString::fromUtf8("Act1LowOn"));
        Act1LowOn->setGeometry(QRect(560, 70, 71, 31));
        Act1HighOn = new QTextBrowser(centralWidget);
        Act1HighOn->setObjectName(QString::fromUtf8("Act1HighOn"));
        Act1HighOn->setGeometry(QRect(720, 70, 71, 31));
        Act2HighOn = new QTextBrowser(centralWidget);
        Act2HighOn->setObjectName(QString::fromUtf8("Act2HighOn"));
        Act2HighOn->setEnabled(false);
        Act2HighOn->setGeometry(QRect(1040, 70, 71, 31));
        Act2LowOn = new QTextBrowser(centralWidget);
        Act2LowOn->setObjectName(QString::fromUtf8("Act2LowOn"));
        Act2LowOn->setEnabled(false);
        Act2LowOn->setGeometry(QRect(880, 70, 71, 31));
        ActTwoHighButton = new QPushButton(centralWidget);
        ActTwoHighButton->setObjectName(QString::fromUtf8("ActTwoHighButton"));
        ActTwoHighButton->setEnabled(false);
        ActTwoHighButton->setGeometry(QRect(970, 70, 51, 30));
        ActTwoLowButton = new QPushButton(centralWidget);
        ActTwoLowButton->setObjectName(QString::fromUtf8("ActTwoLowButton"));
        ActTwoLowButton->setEnabled(false);
        ActTwoLowButton->setGeometry(QRect(820, 70, 51, 30));
        SecondActBox = new QCheckBox(centralWidget);
        SecondActBox->setObjectName(QString::fromUtf8("SecondActBox"));
        SecondActBox->setGeometry(QRect(820, 20, 211, 21));
        hsm_full->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(hsm_full);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1143, 20));
        menuCalibration = new QMenu(menuBar);
        menuCalibration->setObjectName(QString::fromUtf8("menuCalibration"));
        hsm_full->setMenuBar(menuBar);
        mainToolBar = new QToolBar(hsm_full);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        hsm_full->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(hsm_full);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        hsm_full->setStatusBar(statusBar);

        menuBar->addAction(menuCalibration->menuAction());
        menuCalibration->addAction(actionCalibration);

        retranslateUi(hsm_full);

        QMetaObject::connectSlotsByName(hsm_full);
    } // setupUi

    void retranslateUi(QMainWindow *hsm_full)
    {
        hsm_full->setWindowTitle(QCoreApplication::translate("hsm_full", "hsm_full", nullptr));
        actionCalibration->setText(QCoreApplication::translate("hsm_full", "Calibration", nullptr));
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
        label_11->setText(QCoreApplication::translate("hsm_full", "Offset from Zero", nullptr));
        SliderButton_2->setText(QCoreApplication::translate("hsm_full", "Activate", nullptr));
        label_12->setText(QCoreApplication::translate("hsm_full", "Approx Stiffness", nullptr));
        CommandButton_2->setText(QCoreApplication::translate("hsm_full", "Send Command", nullptr));
        label_13->setText(QCoreApplication::translate("hsm_full", "Current Span:", nullptr));
        zeroButton_2->setText(QCoreApplication::translate("hsm_full", "Set Zero", nullptr));
        label_14->setText(QCoreApplication::translate("hsm_full", "Current Position", nullptr));
        label_15->setText(QCoreApplication::translate("hsm_full", "Command", nullptr));
        label_16->setText(QCoreApplication::translate("hsm_full", "Force Reading", nullptr));
        SpanButton_2->setText(QCoreApplication::translate("hsm_full", "Set Span", nullptr));
        label_17->setText(QCoreApplication::translate("hsm_full", "Input Span:", nullptr));
        fZeroButton_2->setText(QCoreApplication::translate("hsm_full", "Calibrate Force", nullptr));
        setSpanBit->setText(QCoreApplication::translate("hsm_full", "Change Span", nullptr));
        setZeroBit->setText(QCoreApplication::translate("hsm_full", "Send Zero", nullptr));
        sendDoubleButton->setText(QCoreApplication::translate("hsm_full", "send Double", nullptr));
        ActOneLowButton->setText(QCoreApplication::translate("hsm_full", "Low ", nullptr));
        ActOneHighButton->setText(QCoreApplication::translate("hsm_full", "High", nullptr));
        ActTwoHighButton->setText(QCoreApplication::translate("hsm_full", "High", nullptr));
        ActTwoLowButton->setText(QCoreApplication::translate("hsm_full", "Low ", nullptr));
        SecondActBox->setText(QCoreApplication::translate("hsm_full", "Use Second Actuator", nullptr));
        menuCalibration->setTitle(QCoreApplication::translate("hsm_full", "Calibration", nullptr));
    } // retranslateUi

};

namespace Ui {
    class hsm_full: public Ui_hsm_full {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HSM_FULL_H
