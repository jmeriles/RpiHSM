#include "hsm_full.h"
#include "lowpassfilter2.h"
#include <QApplication>
#include <limits.h>
#include <qwt_plot_curve.h>
#include <qwt_plot.h>
#include <QPushButton>
#include "ui_hsm_full.h"
//#include "psas.h"
#include "ui_psas.h"
#include <string.h>
#include <errno.h>
#include <string>
#include <iostream>
#include <wiringSerial.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    hsm_full w;
    w.show();

    //PSAS y;
    //y.show();

    return a.exec();
}
