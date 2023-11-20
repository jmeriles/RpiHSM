#include "hsm_full.h"
#include "ui_interlock.h"
hsm_full *sourcefunction1;

Interlock::Interlock(QWidget *parent,  hsm_full *source) :
    QMainWindow(parent),
    ui6(new Ui::Interlock)
{
    sourcefunction1 = source;
    ui6->setupUi(this);
    connect(ui6->SetMaxSpanInter, &QPushButton::released, this, &Interlock::setMaxSpanInterlock);
    connect(ui6->SetMinSpanInter, &QPushButton::released, this, &Interlock::setMinSpanInterlock);
    connect(ui6->SetMaxForceInter, &QPushButton::released, this, &Interlock::setMaxForceInterlock);
    connect(ui6->SetMinForceInter, &QPushButton::released, this, &Interlock::setMinForceInterlock);
    connect(ui6->UnlockEStop, &QPushButton::released, this, &Interlock::resetEStop);
    connect(ui6->UnlockMaxSpan, &QPushButton::released, this, &Interlock::unlockMaxSpan);
    connect(ui6->UnlockMinSpan, &QPushButton::released, this, &Interlock::unlockMinSpan);
    connect(ui6->UnlockMaxForce, &QPushButton::released, this, &Interlock::unlockMaxForce);
    connect(ui6->UnlockMinForce, &QPushButton::released, this, &Interlock::unlockMinForce);
    connect(ui6->ControllerSelect, &QSpinBox::textChanged, this, &Interlock::writeOutInterlocks);

    ui6->MaxSpanInput->setValue(sourcefunction1->getMaxSpan());
    ui6->MinSpanInput->setValue(sourcefunction1->getMinSpan());
    ui6->MaxForceInput->setValue(sourcefunction1->getMaxForce());
    ui6->MinForceInput->setValue(sourcefunction1->getMinForce());

    if(sourcefunction1->isInterlockOn(0,0) == 1) {
        ui6->MaxDispCheckBox->toggle();
    }
    if(sourcefunction1->isInterlockOn(0,1) == 1) {
        ui6->MinDispCheckBox->toggle();
    }
    if(sourcefunction1->isInterlockOn(0,2) == 1) {
        ui6->MaxForceCheckBox->toggle();
    }
    if(sourcefunction1->isInterlockOn(0,3) == 1) {
        ui6->MinForceCheckBox->toggle();
    }
    if(sourcefunction1->isInterlockOn(1,0) == 1) {
        ui6->MaxDispCheckBox_2->toggle();
    }
    if(sourcefunction1->isInterlockOn(1,1) == 1) {
        ui6->MinDispCheckBox_2->toggle();
    }
    if(sourcefunction1->isInterlockOn(1,2) == 1) {
        ui6->MaxForceCheckBox_2->toggle();
    }
    if(sourcefunction1->isInterlockOn(1,3) == 1) {
        ui6->MinForceCheckBox_2->toggle();
    }
    if(sourcefunction1->isInterlockOn(2,0) == 1) {
        ui6->EStopCheckBox->toggle();
    }

    closeCallbackInter = [&](){
        timer->start();
        std::cout << "Window was closed" << "\n";
    };
}

void Interlock::setMaxSpanInterlock() {
    sourcefunction1->setMaxDisp(ui6->ControllerSelect->value(), ui6->MaxSpanInput->value());
    sourcefunction1->saveInterlocks();
}

void Interlock::setMinSpanInterlock() {
    sourcefunction1->setMinDisp(ui6->ControllerSelect->value(), ui6->MinSpanInput->value());
    sourcefunction1->saveInterlocks();
}

void Interlock::setMaxForceInterlock() {
    sourcefunction1->setMaxForce(ui6->ControllerSelect->value(), ui6->MaxForceInput->value());
    sourcefunction1->saveInterlocks();
}

void Interlock::setMinForceInterlock() {
    sourcefunction1->setMinForce(ui6->ControllerSelect->value(), ui6->MinForceInput->value());
    sourcefunction1->saveInterlocks();
}

void Interlock::resetEStop() {
    sourcefunction1->resetInterlock(2,0);
    if(ui6->EStopCheckBox->isChecked()){
        ui6->EStopCheckBox->toggle();
    }
}

void Interlock::unlockMaxSpan() {
    sourcefunction1->resetInterlock(ui6->ControllerSelect->value(),0);
    if (ui6->ControllerSelect->value() == 0) {
        if(ui6->MaxDispCheckBox->isChecked()){
            ui6->MaxDispCheckBox->toggle();
        }
    } if (ui6->ControllerSelect->value() == 1) {
        if(ui6->MaxDispCheckBox_2->isChecked()){
            ui6->MaxDispCheckBox_2->toggle();
        }
    }
}

void Interlock::unlockMinSpan() {
    sourcefunction1->resetInterlock(ui6->ControllerSelect->value(),1);
    if (ui6->ControllerSelect->value() == 0) {
        if(ui6->MinDispCheckBox->isChecked()){
            ui6->MinDispCheckBox->toggle();
        }
    } if (ui6->ControllerSelect->value() == 1) {
        if(ui6->MinDispCheckBox_2->isChecked()){
            ui6->MinDispCheckBox_2->toggle();
        }
    }
}

void Interlock::unlockMaxForce() {
    sourcefunction1->resetInterlock(ui6->ControllerSelect->value(),2);
    if (ui6->ControllerSelect->value() == 0) {
        if(ui6->MaxForceCheckBox->isChecked()){
            ui6->MaxForceCheckBox->toggle();
        }
    } if (ui6->ControllerSelect->value() == 1) {
        if(ui6->MaxForceCheckBox_2->isChecked()){
            ui6->MaxForceCheckBox_2->toggle();
        }
    }
}

void Interlock::unlockMinForce() {
    sourcefunction1->resetInterlock(ui6->ControllerSelect->value(),3);
    if (ui6->ControllerSelect->value() == 0) {
        if(ui6->MinForceCheckBox->isChecked()){
            ui6->MinForceCheckBox->toggle();
        }
    } if (ui6->ControllerSelect->value() == 1) {
        if(ui6->MinForceCheckBox_2->isChecked()){
            ui6->MinForceCheckBox_2->toggle();
        }
    }
}

void Interlock::writeOutInterlocks() {
    if (ui6->ControllerSelect->value() == 0) {
        ui6->MaxSpanInput->setValue(sourcefunction1->getMaxSpan());
        ui6->MinSpanInput->setValue(sourcefunction1->getMinSpan());
        ui6->MaxForceInput->setValue(sourcefunction1->getMaxForce());
        ui6->MinForceInput->setValue(sourcefunction1->getMinForce());
    } else if (ui6->ControllerSelect->value() == 1) {
        ui6->MaxSpanInput->setValue(sourcefunction1->getMaxSpan2());
        ui6->MinSpanInput->setValue(sourcefunction1->getMinSpan2());
        ui6->MaxForceInput->setValue(sourcefunction1->getMaxForce2());
        ui6->MinForceInput->setValue(sourcefunction1->getMinForce2());
    }
}
Interlock::~Interlock()
{
    delete ui6;
}
