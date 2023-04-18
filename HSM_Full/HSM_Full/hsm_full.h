#ifndef HSM_FULL_H
#define HSM_FULL_H

#include </usr/include/python3.9/Python.h>
#include </usr/include/python3.9/numpy/ndarraytypes.h>
#include <iterator>
#include </usr/include/python3.9/numpy/ndarrayobject.h>
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdint.h>
#include <unistd.h>
#include <ABE_ExpanderPi.h>
#include <QMainWindow>
#include<QTimer>
#include<QPushButton>
#include<QDoubleSpinBox>
#include <limits.h>
#include <iostream>
extern "C" {
#include <wiringPiI2C.h>
#include <wiringPi.h>
}
#define DEVICE_ID 100
//#include "qwt_plot_dict.h"
#include <pigpio.h>
#include <QWidget>


namespace Ui {
class hsm_full;
class PSAS;
class HybridEl;
class CustomElement;
}

class hsm_full : public QMainWindow
{
    Q_OBJECT

public:
    explicit hsm_full(QWidget *parent = nullptr);
    ~hsm_full();


    QTimer *timer;
    QTimer *timer2;
    int index;
    QVector<double> Xdata;
    QVector<double> Ydata;
    QVector<double> Xdata2;
    QVector<double> Ydata2;
    //QwtPlotDict plotdict;
    Ui::hsm_full *ui;

public slots:
    void updatePlot();
    void stiffTest();
    void save();
    void sendCommand();
    void sendP();
    void sendI();
    void sendD();
    void sliderCommand();
    void activateButton();
    void updateLCD();
    void spanCommand();
    void setZero();
    void startControl();
    void setAmp();
    void setFreq();
    void sinTest();
    void sweep();
    void ampTest();
    void reqloops();
    void calForce();
    void PSAS_Window();
    void activatePin();
    int plotResults();



signals:
    void sendSignal(int value);


private:
    QPushButton *m_button;
    QPushButton *n_button;
    QPushButton *s_button;


private slots:
    int update();

};

class PSAS : public QMainWindow
{
    Q_OBJECT

public:
    explicit PSAS(QWidget *parent = nullptr);
    ~PSAS();

public slots:
    void add_Node_to_Model();
    void remove_Node_from_Model();
    void add_Element_to_Model();
    void remove_Element_from_Model();
    void add_el_props();
    void add_BCs();
    void add_el_load();
    void add_node_load();
    int setupModel();
    void switchDim();
    int plotModel();
    void HybridEl_Window();
    void enableHybrid();
    void submitEQ();
    int submitDynOpt();
    void enableCustom();
    void CustomEl_Window();

private:
    Ui::PSAS *ui2;
};

class HybridEl : public QMainWindow
{
    Q_OBJECT

public:
    explicit HybridEl(QWidget *parent = nullptr);
    ~HybridEl();

public slots:
    void submitElement();
    void undoSubmit();


private:
    Ui::HybridEl *ui3;
};

class CustomElement : public QMainWindow
{
    Q_OBJECT

public:
    explicit CustomElement(QWidget *parent = nullptr);
    ~CustomElement();

public slots:
    void submitElement();
    void undoSubmit();

private:
    Ui::CustomElement *ui4;
};




extern PyObject *u_p, *udot_p, *uddot_p, *f_p, *eq_p, *dt;
extern PyObject *pythonArgument;
extern PyObject *pName, *pModule, *pDict, *pFunc,*Model,*el;
extern PyObject *pArgs, *x_next,*PyGM;
extern int twodthreed;

extern std::vector<std::vector<std::vector<double>>> HybridElMatrix;
extern std::vector<std::vector<int>> HybridElControl;
extern std::vector<std::vector<std::vector<double>>> CustomElMatrix;
extern std::vector<double> GM;





#endif // HSM_FULL_H
