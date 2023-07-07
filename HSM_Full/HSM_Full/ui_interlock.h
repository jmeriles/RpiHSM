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

    void setupUi(QWidget *Interlock)
    {
        if (Interlock->objectName().isEmpty())
            Interlock->setObjectName(QString::fromUtf8("Interlock"));
        Interlock->resize(400, 300);
        SetMaxSpanInter = new QPushButton(Interlock);
        SetMaxSpanInter->setObjectName(QString::fromUtf8("SetMaxSpanInter"));
        SetMaxSpanInter->setGeometry(QRect(130, 70, 80, 23));
        MaxSpanInput = new QDoubleSpinBox(Interlock);
        MaxSpanInput->setObjectName(QString::fromUtf8("MaxSpanInput"));
        MaxSpanInput->setGeometry(QRect(40, 70, 62, 24));
        MinSpanInput = new QDoubleSpinBox(Interlock);
        MinSpanInput->setObjectName(QString::fromUtf8("MinSpanInput"));
        MinSpanInput->setGeometry(QRect(40, 120, 62, 24));
        MaxForceInput = new QDoubleSpinBox(Interlock);
        MaxForceInput->setObjectName(QString::fromUtf8("MaxForceInput"));
        MaxForceInput->setGeometry(QRect(40, 170, 62, 24));
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
        UnlockEStop->setGeometry(QRect(130, 270, 80, 23));
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
    } // retranslateUi

};

namespace Ui {
    class Interlock: public Ui_Interlock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERLOCK_H
