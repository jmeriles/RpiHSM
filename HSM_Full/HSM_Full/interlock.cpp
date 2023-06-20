#include "hsm_full.h"
#include "ui_interlock.h"

Interlock::Interlock(QWidget *parent) :
    QMainWindow(parent),
    ui6(new Ui::Interlock)
{
    ui6->setupUi(this);
    closeCallbackInter = [&](){
        timer->start();
        std::cout << "Window was closed" << "\n";
    };
}

Interlock::~Interlock()
{
    delete ui6;
}
