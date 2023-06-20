#include "interlock.h"
#include "ui_interlock.h"

Interlock::Interlock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Interlock)
{
    ui->setupUi(this);
}

Interlock::~Interlock()
{
    delete ui;
}
