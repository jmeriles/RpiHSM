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
#include <QtGui/QCloseEvent>
#include <functional>
#include "wiringPiSPI.h"
#include <linux/spi/spidev.h>


namespace Ui {
class hsm_full;
class PSAS;
class SpanCalibration;
class HybridEl;
class CustomElement;
class Interlock;
}

class hsm_full : public QMainWindow
{
    Q_OBJECT

public:
    explicit hsm_full(QWidget *parent = nullptr);
    ~hsm_full();

    std::function<void()> closeCallbackHsm;
    QTimer *timer2;
    int index;
    QVector<double> Xdata;
    QVector<double> Ydata;
    QVector<double> XCommand;
    QVector<double> YCommand;
    QVector<double> XdataAct2;
    QVector<double> YdataAct2;
    QVector<double> XCommandAct2;
    QVector<double> YCommandAct2;
    QVector<double> loadCellData1;
    QVector<double> loadCellData2;
    QVector<double> HystDisp1;
    QVector<double> HystDisp2;
    //QwtPlotDict plotdict;
    Ui::hsm_full *ui;

public slots:
    void updatePlot();
    void stiffTest();
    void save();
    void initializeController(int channel);
    void saveForceSlopes();
    void saveInterlocks();
    void setPlotScale();
    void setLCData();
    void saveScaleData();
    void saveLCData();
    double getActOneDispScale();
    double getActTwoDispScale();
    double getActOneForceScale();
    double getActTwoForceScale();



    void useFirstActuator();
    void sendCommand();
    void sendPID();
    void sendPIDForce();
    //void sendI();
    //void sendD();
    void sliderCommand();
    void activateButton();
    void pressSpanButton();
    void setZero();
    void startControl();
    void calForce();
    void turnOnLow1();
    void turnOnHigh1();
    //void adjustLC1();
    //void adjustLC1Zero();
    //void setLC1Slope();
    void switchControlType();

    void useSecondActuator();
    void sendCommand2();
    void sendPID2();
    void sendPIDForce2();
    void sliderCommand2();
    void activateButton2();
    void pressSpanButton2();
    void setZero2();
    void startControl2();
    void calForce2();
    void turnOnLow2();
    void turnOnHigh2();
    //void adjustLC2();
    //void adjustLC2Zero();
    //void setLC2Slope();
    void switchControlType2();
    void readForce(int channel);

    void turnOffHydraulics();
    //void changeSpan();
    void updateLCD();
    void spanCommand(int channel, double targetSpan, double targetZero);
    void setAmp();
    void setFreq();
    void sinTest();
    void sweep();
    void ampTest();
    void reqloops();
    void PSAS_Window();
    void Cal_Window();
    int plotResults();
    int serialRead(int channel, int comm, int data);
    void serialWrite(int channel, int comm, int data);
    std::vector <std::vector <double>>  readFiles(std::string fileName);
    std::vector <double> LinearRegression(std::vector <double> xData, std::vector<double> yData);
    //void sendZero();
    void sendDouble(int channel, int comm, double data);
   // void sendDoubleUI();
    double receivedToInches(int channel, int dataInBits);
    int inchesToBits(int channel,double dataInInches);


    void Interlock_Window();
    void readAllFilesAndCalibrate();
    void calLoadCell(int channel,int value);
    double returnLoad(int channel);
    void setMaxDisp(int channel, double Disp);
    void setMinDisp(int channel, double Disp);
    void setMaxForce(int channel, double Force);
    void setMinForce(int channel, double Force);
    void checkInterlock();
    void resetInterlock(int channel, int whichInterlock);
    int isInterlockOn(int channel, int whichInterlock);
    void clearPlotVectors();
    int readAck(int channel);
    int loadModel();
    void loadActuators();
    double getForce();
    double getForce2();
    double getMaxSpan();
    double getMaxSpan2();
    double getMinSpan();
    double getMinSpan2();
    double getMaxForce();
    double getMaxForce2();
    double getMinForce();
    double getMinForce2();


signals:
    void sendSignal(int value);


private:
    QPushButton *m_button;
    QPushButton *n_button;
    QPushButton *s_button;


private slots:
    int update();

protected:
    inline void closeEvent(QCloseEvent *event) override
    {
        if (closeCallbackHsm)
            closeCallbackHsm();
    }

};

class PSAS : public QMainWindow
{
    Q_OBJECT

public:
    explicit PSAS(QWidget *parent = nullptr,hsm_full *source = nullptr);
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
    void SavePickedActuators();



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


class SpanCalibration : public QMainWindow
{
    Q_OBJECT

public:
    explicit SpanCalibration(QMainWindow *parent = nullptr, hsm_full *source = nullptr);
    ~SpanCalibration();
    std::function<void()> closeCallback;

public slots:
    void startCalibration();
    void plotCal(QVector<double> X, QVector<double> Y);
    void potCal();
    void activatePotCal();
    double BitToInch(int bitVal);
    void loadCal();

protected:
    inline void closeEvent(QCloseEvent *event) override
    {
        if (closeCallback)
            closeCallback();
    }

private:
    Ui::SpanCalibration *ui5;

};

class Interlock : public QMainWindow
{
    Q_OBJECT

public:
    explicit Interlock(QWidget *parent = nullptr, hsm_full *source = nullptr);
    ~Interlock();
    std::function<void()> closeCallbackInter;
    void setMaxSpanInterlock();
    void setMinSpanInterlock();
    void setMaxForceInterlock();
    void setMinForceInterlock();
    void unlockMaxSpan();
    void unlockMinSpan();
    void unlockMaxForce();
    void unlockMinForce();
    void resetEStop();
    void writeOutInterlocks();

protected:
    inline void closeEvent(QCloseEvent *event) override
    {
        if (closeCallbackInter)
            closeCallbackInter();
    }

private:
    Ui::Interlock *ui6;
};


extern PyObject *u_p, *udot_p, *uddot_p, *f_p, *eq_p, *dt;
extern PyObject *pythonArgument;
extern PyObject *pName, *pModule, *pDict, *pFunc,*Model,*el;
extern PyObject *pArgs, *x_next,*PyGM;
extern int twodthreed;
extern QTimer *timer;

extern std::vector<std::vector<std::vector<double>>> HybridElMatrix;
extern std::vector<std::vector<int>> HybridElControl;
extern std::vector<std::vector<std::vector<double>>> CustomElMatrix;
extern double calSlope;
extern double calIntercept;
extern double  totSpan;
extern double totSpan2;
extern int maxDiffValue;
extern int minDiffValue;
extern int maxOGValue;
extern int minOGValue;
extern double spanSlope;
extern double spanIntercept;
extern double spanMax;
extern double spanMin;
extern bool eStopActive;
extern double inchSlope;
extern std::vector <double> potInches;
extern std::vector <double> potTru;
extern std::vector <double> potDiff;
extern std::vector <double> origSlopes;
extern std::vector <double> origIntercepts;
extern std::vector <double> zeroData;
extern std::vector <double> potInches2;
extern std::vector <double> potTru2;
extern std::vector <double> potDiff2;
extern std::vector <double> origSlopes2;
extern std::vector <double> origIntercepts2;
extern std::vector <double> zeroData2;
extern double diffGain;
extern double diffGain2;
extern double diffIntercept;
extern double diffIntercept2;
extern double loadCellZeroInBits;
extern double loadCellSlope;




#endif // HSM_FULL_H
