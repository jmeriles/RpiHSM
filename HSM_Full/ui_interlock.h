/********************************************************************************
** Form generated from reading UI file 'interlock.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERLOCK_H
#define UI_INTERLOCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Interlock
{
public:
    QPushButton *SetMaxSpanInter;
    QDoubleSpinBox *MaxSpanInput;
    QDoubleSpinBox *MinSpanInput;
    QDoubleSpinBox *MaxForceInput;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QDoubleSpinBox *MinForceInput;
    QLabel *label_4;
    QPushButton *SetMinSpanInter;
    QPushButton *SetMaxForceInter;
    QPushButton *SetMinForceInter;
    QLabel *label_5;
    QPushButton *UnlockEStop;
    QPushButton *UnlockMaxSpan;
    QPushButton *UnlockMinSpan;
    QPushButton *UnlockMaxForce;
    QPushButton *UnlockMinForce;
    QLabel *label_6;
    QSpinBox *ControllerSelect;
    QLabel *label_7;
    QCheckBox *MaxDispCheckBox;
    QCheckBox *MinDispCheckBox;
    QCheckBox *MaxForceCheckBox;
    QCheckBox *MinForceCheckBox;
    QLabel *label_8;
    QCheckBox *MaxForceCheckBox_2;
    QCheckBox *MinForceCheckBox_2;
    QLabel *label_9;
    QCheckBox *MaxDispCheckBox_2;
    QCheckBox *MinDispCheckBox_2;
    QCheckBox *EStopCheckBox;

    void setupUi(QWidget *Interlock)
    {
        if (Interlock->objectName().isEmpty())
            Interlock->setObjectName(QString::fromUtf8("Interlock"));
        Interlock->resize(478, 300);
        SetMaxSpanInter = new QPushButton(Interlock);
        SetMaxSpanInter->setObjectName(QString::fromUtf8("SetMaxSpanInter"));
        SetMaxSpanInter->setGeometry(QRect(130, 70, 80, 23));
        MaxSpanInput = new QDoubleSpinBox(Interlock);
        MaxSpanInput->setObjectName(QString::fromUtf8("MaxSpanInput"));
        MaxSpanInput->setGeometry(QRect(40, 70, 62, 24));
        MaxSpanInput->setMinimum(-10000000000.000000000000000);
        MaxSpanInput->setMaximum(10000000000.000000000000000);
        MinSpanInput = new QDoubleSpinBox(Interlock);
        MinSpanInput->setObjectName(QString::fromUtf8("MinSpanInput"));
        MinSpanInput->setGeometry(QRect(40, 120, 62, 24));
        MinSpanInput->setMinimum(-1000000000000.000000000000000);
        MinSpanInput->setMaximum(100000000000.000000000000000);
        MaxForceInput = new QDoubleSpinBox(Interlock);
        MaxForceInput->setObjectName(QString::fromUtf8("MaxForceInput"));
        MaxForceInput->setGeometry(QRect(40, 170, 62, 24));
        MaxForceInput->setMinimum(-1000000000000.000000000000000);
        MaxForceInput->setMaximum(10000000000.000000000000000);
        label = new QLabel(Interlock);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 50, 81, 16));
        label_2 = new QLabel(Interlock);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 100, 81, 16));
        label_3 = new QLabel(Interlock);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(40, 150, 81, 16));
        MinForceInput = new QDoubleSpinBox(Interlock);
        MinForceInput->setObjectName(QString::fromUtf8("MinForceInput"));
        MinForceInput->setGeometry(QRect(40, 220, 62, 24));
        MinForceInput->setMinimum(-100000000000000.000000000000000);
        MinForceInput->setMaximum(100000000000.000000000000000);
        label_4 = new QLabel(Interlock);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(40, 200, 81, 16));
        SetMinSpanInter = new QPushButton(Interlock);
        SetMinSpanInter->setObjectName(QString::fromUtf8("SetMinSpanInter"));
        SetMinSpanInter->setGeometry(QRect(130, 120, 80, 23));
        SetMaxForceInter = new QPushButton(Interlock);
        SetMaxForceInter->setObjectName(QString::fromUtf8("SetMaxForceInter"));
        SetMaxForceInter->setGeometry(QRect(130, 170, 80, 23));
        SetMinForceInter = new QPushButton(Interlock);
        SetMinForceInter->setObjectName(QString::fromUtf8("SetMinForceInter"));
        SetMinForceInter->setGeometry(QRect(130, 220, 80, 23));
        label_5 = new QLabel(Interlock);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(40, 250, 81, 16));
        UnlockEStop = new QPushButton(Interlock);
        UnlockEStop->setObjectName(QString::fromUtf8("UnlockEStop"));
        UnlockEStop->setGeometry(QRect(130, 260, 80, 23));
        UnlockMaxSpan = new QPushButton(Interlock);
        UnlockMaxSpan->setObjectName(QString::fromUtf8("UnlockMaxSpan"));
        UnlockMaxSpan->setGeometry(QRect(230, 70, 80, 23));
        UnlockMinSpan = new QPushButton(Interlock);
        UnlockMinSpan->setObjectName(QString::fromUtf8("UnlockMinSpan"));
        UnlockMinSpan->setGeometry(QRect(230, 120, 80, 23));
        UnlockMaxForce = new QPushButton(Interlock);
        UnlockMaxForce->setObjectName(QString::fromUtf8("UnlockMaxForce"));
        UnlockMaxForce->setGeometry(QRect(230, 170, 80, 23));
        UnlockMinForce = new QPushButton(Interlock);
        UnlockMinForce->setObjectName(QString::fromUtf8("UnlockMinForce"));
        UnlockMinForce->setGeometry(QRect(230, 220, 80, 23));
        label_6 = new QLabel(Interlock);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(40, 10, 81, 16));
        ControllerSelect = new QSpinBox(Interlock);
        ControllerSelect->setObjectName(QString::fromUtf8("ControllerSelect"));
        ControllerSelect->setGeometry(QRect(130, 10, 43, 24));
        label_7 = new QLabel(Interlock);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(390, 30, 81, 16));
        MaxDispCheckBox = new QCheckBox(Interlock);
        MaxDispCheckBox->setObjectName(QString::fromUtf8("MaxDispCheckBox"));
        MaxDispCheckBox->setGeometry(QRect(340, 70, 85, 21));
        MinDispCheckBox = new QCheckBox(Interlock);
        MinDispCheckBox->setObjectName(QString::fromUtf8("MinDispCheckBox"));
        MinDispCheckBox->setGeometry(QRect(340, 120, 85, 21));
        MaxForceCheckBox = new QCheckBox(Interlock);
        MaxForceCheckBox->setObjectName(QString::fromUtf8("MaxForceCheckBox"));
        MaxForceCheckBox->setGeometry(QRect(340, 170, 85, 21));
        MinForceCheckBox = new QCheckBox(Interlock);
        MinForceCheckBox->setObjectName(QString::fromUtf8("MinForceCheckBox"));
        MinForceCheckBox->setGeometry(QRect(340, 220, 85, 21));
        label_8 = new QLabel(Interlock);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(330, 50, 81, 16));
        MaxForceCheckBox_2 = new QCheckBox(Interlock);
        MaxForceCheckBox_2->setObjectName(QString::fromUtf8("MaxForceCheckBox_2"));
        MaxForceCheckBox_2->setGeometry(QRect(420, 170, 85, 21));
        MinForceCheckBox_2 = new QCheckBox(Interlock);
        MinForceCheckBox_2->setObjectName(QString::fromUtf8("MinForceCheckBox_2"));
        MinForceCheckBox_2->setGeometry(QRect(420, 220, 85, 21));
        label_9 = new QLabel(Interlock);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(410, 50, 81, 16));
        MaxDispCheckBox_2 = new QCheckBox(Interlock);
        MaxDispCheckBox_2->setObjectName(QString::fromUtf8("MaxDispCheckBox_2"));
        MaxDispCheckBox_2->setGeometry(QRect(420, 70, 85, 21));
        MinDispCheckBox_2 = new QCheckBox(Interlock);
        MinDispCheckBox_2->setObjectName(QString::fromUtf8("MinDispCheckBox_2"));
        MinDispCheckBox_2->setGeometry(QRect(420, 120, 85, 21));
        EStopCheckBox = new QCheckBox(Interlock);
        EStopCheckBox->setObjectName(QString::fromUtf8("EStopCheckBox"));
        EStopCheckBox->setGeometry(QRect(240, 260, 85, 21));

        retranslateUi(Interlock);

        QMetaObject::connectSlotsByName(Interlock);
    } // setupUi

    void retranslateUi(QWidget *Interlock)
    {
        Interlock->setWindowTitle(QCoreApplication::translate("Interlock", "Form", nullptr));
        SetMaxSpanInter->setText(QCoreApplication::translate("Interlock", "Set", nullptr));
        label->setText(QCoreApplication::translate("Interlock", "Max Span", nullptr));
        label_2->setText(QCoreApplication::translate("Interlock", "Min Span", nullptr));
        label_3->setText(QCoreApplication::translate("Interlock", "Max Force", nullptr));
        label_4->setText(QCoreApplication::translate("Interlock", "Min Force", nullptr));
        SetMinSpanInter->setText(QCoreApplication::translate("Interlock", "Set", nullptr));
        SetMaxForceInter->setText(QCoreApplication::translate("Interlock", "Set", nullptr));
        SetMinForceInter->setText(QCoreApplication::translate("Interlock", "Set", nullptr));
        label_5->setText(QCoreApplication::translate("Interlock", "E-Stop", nullptr));
        UnlockEStop->setText(QCoreApplication::translate("Interlock", "Reset", nullptr));
        UnlockMaxSpan->setText(QCoreApplication::translate("Interlock", "Unlock", nullptr));
        UnlockMinSpan->setText(QCoreApplication::translate("Interlock", "Unlock", nullptr));
        UnlockMaxForce->setText(QCoreApplication::translate("Interlock", "Unlock", nullptr));
        UnlockMinForce->setText(QCoreApplication::translate("Interlock", "Unlock", nullptr));
        label_6->setText(QCoreApplication::translate("Interlock", "Controller", nullptr));
        label_7->setText(QCoreApplication::translate("Interlock", "ON?", nullptr));
        MaxDispCheckBox->setText(QString());
        MinDispCheckBox->setText(QString());
        MaxForceCheckBox->setText(QString());
        MinForceCheckBox->setText(QString());
        label_8->setText(QCoreApplication::translate("Interlock", "Act 1", nullptr));
        MaxForceCheckBox_2->setText(QString());
        MinForceCheckBox_2->setText(QString());
        label_9->setText(QCoreApplication::translate("Interlock", "Act 2", nullptr));
        MaxDispCheckBox_2->setText(QString());
        MinDispCheckBox_2->setText(QString());
        EStopCheckBox->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Interlock: public Ui_Interlock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERLOCK_H
