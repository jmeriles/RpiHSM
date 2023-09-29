#include "hsm_full.h"
#include "lowpassfilter2.h"
#include "ui_hsm_full.h"
#include "qwt_plot_curve.h"
#include "qwt_plot.h"
#include <qwt_plot_dict.h>
#include <QPushButton>
extern "C" {
#include <wiringPiI2C.h>
#include <wiringPi.h>
//#include <pigpiod_if2.h>
}
#include<algorithm>
#include <cmath>
//#include "psas.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <string>
#include <iostream>
#include <wiringSerial.h>
#include <checksum.h>
#include<dirent.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <bitset>
#include <qwt_plot_legenditem.h>



//variables for sending and receiving over serial
int numToSend;
bool recvInProgress = false;

QTimer *timer;
QTimer *eStopTimer;
PyObject *u_p, *udot_p, *uddot_p, *f_p, *eq_p, *dt,*iter;
PyObject *pythonArgument;
PyObject *pName, *pName2, *pModule,*pModule2, *pDict, *pFunc,*pFunc2;
PyObject *pArgs, *x_next,*x_next2, *InitIntArgs, *Model2;
PyObject *PlotResultsName, *PlotResultsMethod, *PlotResultsFunc;
PyObject *PlotResultsArgs, *PlotResultsOut;
PyObject *LoadModelName, *LoadModelMethod, *LoadModelFunc, *LoadModelArgs, *LoadModelOut;
PyObject *SaveModelName, *SaveModelMethod, *SaveModelFunc, *SaveModelArgs, *SaveModelOut;
PyObject *Pyfp;

using namespace ABElectronics_CPP_Libraries;

bool useADCs = false;
bool hardwareConnected = false;
std::ifstream EQ("/home/pi/Desktop/RpiHSM/HSM_Full/InterpGM.txt");
double d_prev[3]; //This list stores the last 3 values for the displacement
double d_next; //This is the next displacement calculated by the integrator
double Force; // This is the Force measurement
double disp; // This vector will store all the displacement values from the integrator
double disp_tot; // this vector will store all the displacements including from pred_corr
double count =0.0; //This counts where we are in the predictor/corrector
double count_lim = 10.0;
int gcount =0; //This counts our position in total
int gcount_lim = 100;
int intcount =0;
double prevdisp = 0;
double ddisp = 0;
int maxDiffValue;
int minDiffValue;
int minDiffValue2;
double forceSlope = 1;
double forceSlope2 = 1;
double LC1Max = 1000;
double LC2Max = 1000;
int LC1Zero = 0;
int LC2Zero = 0;
int LC1Offset = 0;
int LC2Offset = 0;

bool running = 0;
int plotcount = 0;
pthread_mutex_t trigger_mutex;
pthread_mutex_t race_mutex;
pthread_cond_t trigger;//triggers the time integrator


std::ofstream intDisp;
std::ofstream intDisp2;
std::ofstream intForceResponse;
std::ofstream intForceResponse2;
std::ofstream ForceResponse;
std::ofstream ForceResponse2;
//std::ofstream output3;
std::ofstream sentCom;
std::ofstream sentCom2;
std::ofstream recDisp;
std::ofstream recDisp2;
std::ofstream DispT;
std::ofstream CommandT;
std::ofstream DispT2;
std::ofstream CommandT2;

std::ofstream runningCommand;
std::ofstream runningCommand2;
std::ofstream runningForceCommand;
std::ofstream runningForceCommand2;
std::ofstream runningTime;
std::ofstream runningTime2;
std::ofstream runningFeedback;
std::ofstream runningFeedback2;
std::ofstream runningForce;
std::ofstream runningForce2;

std::ofstream controlLoops;
std::ofstream signalLoopTime;
std::ofstream integratorIndex;
std::ofstream calcVelocity;
std::ofstream calcVelocity2;
std::ofstream calcAcc;
std::ofstream calcAcc2;
std::ofstream SinCommandFile;
std::ofstream SinCommandFile2;
std::ofstream SinResponseFile;
std::ofstream SinResponseFile2;
std::ofstream SinForceFile;
std::ofstream SinForceFile2;
std::ofstream SinTimeFile;
std::ofstream SinTimeFile2;




std::ofstream ForceSlopes;
std::ofstream LCData;
std::ofstream ScaleData;
std::ofstream Interlocks;

double EQdata;
std::vector<double> EQ_h{0};
std::vector<std::vector<double>> xn {{0},{0}};
std::vector<std::vector<double>> xd {{0},{0}};
std::vector<std::vector<double>> xdd {{0},{0}};
std::vector<std::vector<double>> xt {{0},{0}};
std::vector<std::vector<double>> xdt {{0},{0}};
std::vector<std::vector<double>> xddt {{0},{0}};
std::vector<double> time_delay{0};
std::vector<double> oof{0};
std::vector<double> force{0};
std::vector<double> sinWave{0};
std::vector<double> sinCommand{0};
std::vector<double> sinCommand2{0};
std::vector<double> sinResponse{0};
std::vector<double> sinResponse2{0};
std::vector<double> sinForce{0};
std::vector<double> sinForce2{0};
std::vector<double> sinTime{0};
std::vector<double> sinTime2{0};


double xcur;
int EQLen;
int Cor;
double P0;
double Pn1;
double Pn2;
double Pn3;
double Cp1;
double C0;
double Cn1;
double Cn2;
double dp_last;
std::vector<double> xp = {0.0, 0.0};
std::vector<double> xdp= {0.0, 0.0};
std::vector<double> xddp = {0.0, 0.0};
double eqp;
std::vector <double> fp = {0,0};
double K = 4.26;
double dtp = .005;
double xlag;
double f_prev = 0.0;
double dprev = 0.0;
double fy = 1.91;
double df;
double x_prev = 0.0;
struct timeval tv;
struct timeval tv1;
struct timeval runtv;
struct timeval signaltv;
int done=1;
bool cv = 1;
double vel = .01;
std::vector <double> ActuatorVel = {0.0, 0.0};
double sigt = .01; //time between signals
std::vector <double> dx = {0.0, 0.0};
std::vector <double> cur_x = {0.0, 0.0};
//note: change all these 1 2 variables to a 2d array. Much more generalizable and less annoying
double nsteps = 0.0;

double span = 5.5;
int feedback;
int zeroPoint = 2092;
int zeroPoint2 = 2092;
int ogZero;
double zeroPoint_in = 0.0;
double zeroPoint_in2 = 0.0;
double f1;
double f2;
double f3;
double f4;
double f5;
double f6;
double f7;
double f8;
double f9;
double f10;

double d1;
double d2;
double d3;
uint16_t data_to_send;
uint16_t data_to_send2;
uint16_t command;
//int fd;
int received_data;
double dispCommand =0.0;
double forceCommand =0.0;
double dispCommand2 =5.0;
double forceCommand2 =0.0;
double PCommand = .5;
double ICommand = .0001;
double DCommand = 0;
double PCommand2 = .5;
double ICommand2 = .0001;
double DCommand2 = 0;
double slideCommand;
double received_Force = 0.0;
double received_Force2 = 0.0;
double received_Disp = 0.0;
double received_Disp2 = 0.0;
bool sliderActive = 0;
bool sliderActive2 = 0;
double Pmax = 5;
double Imax = .001;
double Dmax = 5;
double maxspan = 12;
int controlcount = 0;
bool commandPlotting = 1;
int i2ctest;
double last_recieved;
double last_recieved2;
uint16_t hibyte;
uint16_t lobyte;
double relative_Disp;
double relative_Disp2;
int pcom = 0;
int pi;
char *buf;
int readtest;
double amp = 0;
double freq = 0;
bool sinOn = 0;
int i = 0;
double tstep = .005;
int sinVal;
bool hsmOn = 0;
bool stiffOn = 0;
int j = 0;
double time_initial;
bool setlim = 0;
double axlim = 5;
double time_in_mill1;
double time_in_s1;
double time_in_mill2;
double time_in_s2;
double runtime_in_mill;
double runtime_in_s;
double runtime_initial;
double loop_in_s_beg;
double loop_in_mill_beg;
double loop_in_s_end;
double loop_in_mill_end;
double runaxlim = 10;
double runaxlimLoad = 60;
double dispPlotRefresh = 10;
double plotRefresh = 60;

//all of these can just be 2d arrays too
std::vector<double> CommandVec{0};
std::vector<double> DispVec{0};
std::vector<double> CommandTime{0};
std::vector<double> ForceVec{0};
std::vector<double> DispTime{0};
std::vector<double> CommandVecAct2{0};
std::vector<double> DispVecAct2{0};
std::vector<double> CommandTimeAct2{0};
std::vector<double> DispTimeAct2{0};
std::vector<double> ForceVecAct2{0};
std::vector<double> loops;
std::vector<double> signalLoops;
std::vector<double> signalLoops2;
std::vector<double> runCommand(10000,0);
std::vector<double> runForceCommand(10000,0);
std::vector<double> runTime(10000,0);
std::vector<double> runFeedback(10000,0);
std::vector<double> runForce(10000,0);
std::vector<double> runCommand2(10000,0);
std::vector<double> runForceCommand2(10000,0);
std::vector<double> runTime2(10000,0);
std::vector<double> runFeedback2(10000,0);
std::vector<double> runForce2(10000,0);
std::vector<double> stiffnessvec;
std::vector<double> stiffdispvec;
std::vector<std::vector<double>> potCalibration;
std::vector<std::vector<double>> spanCalibration;
std::vector<int> intIndex = {};
std::map <double,std::vector<double>> spanCalMap;
std::vector <std::vector<double>> zeroMap;
std::vector<std::vector<double>> potCalibration2;
std::vector<std::vector<double>> spanCalibration2;
std::vector<int> intIndex2 = {};
std::map <double,std::vector<double>> spanCalMap2;
std::vector <std::vector<double>> zeroMap2;
double curloops;
int force_bits;
double w=.4;
double fprev = 0;
bool sinsweep = 0;
bool amptest = 0;
double freq1 = 0;
double freq0 = 0;
double slope;
bool logcontrolloops = 0;
int microcont = 1;
double zeroForce = 0;
double zeroForce2 = 0;
int sendZero;
int zeroDisp;
static int gil_init = 0;
PyObject *python_return;
int controller = 0;
int controller2 = 0;
double hybStiff;
int continuous = 1;
bool pinActive = 0;
int SerialDisp;
int SerialDisp2;
int fd;
int fd2;
int fd3;
char received[8];
int forceReceived[3];
int forceReceived2[3];
int numReceived;
unsigned char sendData[4];
int crcReceived;
unsigned char recData[2];
double spanSlope;
double spanSlope2;
double spanIntercept;
double spanIntercept2;
double spanMax;
double spanMax2;
bool actOneLow = false;
bool actOneHigh = false;
bool actTwoLow = false;
bool actTwoHigh = false;
int actOneLowPin = 28;
int actOneHighPin = 24;
int actTwoLowPin = 25;
int actTwoHighPin = 27;
bool eStopActive;
bool firstActuatorOn = false;
bool secondActuatorOn = false;
double newSpan;
double newSpan2;
double zeroVol;
double zeroVol2;
double loadCellZeroInBits;
double loadCellSlope;
bool legendPlotted = false;

//Labels should be Act 1 Act 2 force etc. Labels should change when running a hybrid simulation
QwtPlotCurve *curve1 = new QwtPlotCurve("Act 1 Rec Disp");
QwtPlotCurve *curve2 = new QwtPlotCurve("Act 1 Comm");
QwtPlotCurve *curve3 = new QwtPlotCurve("Act 2 Rec Disp");
QwtPlotCurve *curve4 = new QwtPlotCurve("Act 1 Hyst");
QwtPlotCurve *curve5 = new QwtPlotCurve("Act 2 Hyst");
QwtPlotCurve *curve10 = new QwtPlotCurve("Act 2 Comm");
QwtPlotCurve *curve11 = new QwtPlotCurve("Act 1 Force Comm");
QwtPlotCurve *curve12 = new QwtPlotCurve("Act 2 Force Comm");
double maxDisp = 100000;
double minDisp = -100000;
double maxForce = 100000;
double minForce = -100000;
double maxDisp2 = 100000;
double minDisp2 = -100000;
double maxForce2 = 100000;
double minForce2 = -100000;
bool maxSpanInterlock = false;
bool minSpanInterlock = false;
bool maxForceInterlock = false;
bool minForceInterlock = false;
bool maxSpanInterlock2 = false;
bool minSpanInterlock2 = false;
bool maxForceInterlock2 = false;
bool minForceInterlock2 = false;
std::vector <double> GM;
std::vector <std::vector<double>> DynamicsFile;
std::vector <double> DynOps;
std::vector <std::vector<double>> ActuatorSelections;
int numControlDOFS = 0;
int CT1 = 0;
int CT2 = 0;
double actOneDispScale = 1.0;
double actOneForceScale = 1.0;
double actTwoDispScale = 1.0;
double actTwoForceScale = 1.0;
bool plotDispCommand1 = true;
bool plotDispCommand2 = true;
bool plotForceCommand1 = false;
bool plotForceCommand2 = false;


#define SPI_CLOCK 500000     // 1 MHz

// See MCP3202 data sheet FIGURE 6-1 SPI Communication using 8-bit segments
#define MCP3202_START 1       // 0000 0001
#define MCP3202_CONFIG  0xA0  // 101x xxxx (Single-Ended + Channel 0 + MSB first)
#define MCP2002_BUFFER_SIZE 3
uint8_t buffer[MCP2002_BUFFER_SIZE]; // See FIGURE 6-1 on data sheet
int ADC;        // Voltage from ADC, as integer 0 -> 4095
//EDIT THIS FOR NEW HAT
//int bitmapports;
//int ports[15];
//struct uzpSpi::uzpChanList ChanList;
int A;
//ExpanderPi expi;

//EDIT THIS TOO
//uzpSpi* DAQ = new (uzpSpi);


//python arguments for time integrator

double pcount_last;
struct period_info {
        struct timespec next_period;
        long period_ns;
};

static void inc_period(struct period_info *pinfo);
static void periodic_task_init(struct period_info *pinfo);
static void do_pred_cor();
static void const_vel(hsm_full* plot_obj);
static void wait_rest_of_period(struct period_info *pinfo);
//void readForce(int channel);
void readDisp();
static void Call_Integrator();
void eStop();
int initializeLoad();
int readFromADC(int SS,int channel);
LowPassFilter2 lp(5,10,true); //not terrible at .1 hz cutoff, but this might be bad when actually measuring loads. TBD
double wForce = .2;
double ypForce = 0.0;
double wForce2 = .2;
double ypForce2 = 0.0;


void *simple_cyclic_task(void* plotter) //This runs a cyclic task in which
                                     // we perform the prediction and correction
{
        qDebug("test1");
        struct period_info pinfo;

        periodic_task_init(&pinfo);
        hsm_full* plot_obj = (hsm_full*)plotter;

        //Runs Hybrid Simulation
        if (sinOn == 0){
            int i = 0;
            qDebug("%d",EQ_h.size());

            while (intcount < GM.size()-1 && running == 1) {
                gettimeofday(&signaltv, NULL);
                loop_in_mill_beg = signaltv.tv_usec;
                loop_in_s_beg = signaltv.tv_sec + loop_in_mill_beg/1000000.0;
                plot_obj->readForce(0);
                plot_obj->readForce(1);

                //picks between constant velocity and predictor corrector
                //Currently predictor-corrector has been implemented, but pi seems to be too slow.
                //Needs further optimization as well as velocity control to work in real time.

                if(cv == 0){
                    do_pred_cor();
                }
                else{
                    const_vel(plot_obj);
                }
                i = i+1;
                feedback = 0;

                pthread_mutex_lock(&race_mutex);
                received_Disp = plot_obj->receivedToInches(1,(double)plot_obj->serialRead(1, 1, 0));
                if (secondActuatorOn) {
                    received_Disp2 = plot_obj->receivedToInches(2,(double)plot_obj->serialRead(2, 1, 0));
                }

                gettimeofday(&tv, NULL);
                time_in_mill1 = tv.tv_usec;
                time_in_s1 = tv.tv_sec + time_in_mill1/1000000.0-time_initial;
                //std::cout << "Time in integrator" << time_in_s1 << "\n";


                //Append time and displacement to vectors
                plot_obj->Xdata.append((double) time_in_s1);
                DispTime.push_back((double) time_in_s1);
                plot_obj->Ydata.append(plot_obj->getActOneDispScale() * (double) received_Disp);
                DispVec.push_back(received_Disp);

                plot_obj->XdataAct2.append((double) time_in_s1);
                DispTimeAct2.push_back((double) time_in_s1);
                plot_obj->YdataAct2.append(plot_obj->getActTwoDispScale() * (double) received_Disp2);
                DispVecAct2.push_back(received_Disp2);
                //std::cout<< ActuatorSelections[0][0] << ", "<< ActuatorSelections[0][1] << "\n";

                if (ActuatorSelections[0][0] == 0 || ActuatorSelections[0][1] == 0) {
                    if (ActuatorSelections[0][0] == 1) {
                        //std::cout << "Test\n";
                        plot_obj->YCommand.append(plot_obj->getActOneDispScale() * (double) xt[gcount-1][0]);
                        //plot_obj->YCommandAct2.append((double xt2[gcount - 1]))
                        //std::cout << xt[gcount - 1] << "\n";
                        CommandVec.push_back((double) xt[gcount-1][0]);
                        plot_obj->XCommand.append((double) time_in_s1);
                        CommandTime.push_back((double) time_in_s1);
                        plot_obj->HystDisp1.append(time_in_s1);
                        double measForce = plot_obj->getForce();
                        plot_obj->loadCellData1.append(plot_obj->getActOneForceScale() * measForce);
                        ForceVec.push_back((measForce));

                        //Send Signal
                        dispCommand = xt[gcount-1][0];
                        data_to_send = (uint16_t) plot_obj->inchesToBits(1,dispCommand);
                        plot_obj->serialWrite(1,0,data_to_send);

                        double act2Command;
                        if(plot_obj->getControlType2() == 0){
                            act2Command = plot_obj->getDispCommand2();
                            plot_obj->YCommandAct2.append(act2Command);
                        } else {
                            act2Command = plot_obj->getForceCommand2();
                            plot_obj->YForceCommandAct2.append(act2Command);
                        }
                        //plot_obj->YCommandAct2.append(plot_obj->getActOneDispScale() * );
                        CommandVecAct2.push_back((double) act2Command);
                        plot_obj->XCommandAct2.append((double) time_in_s1);
                        CommandTimeAct2.push_back((double) time_in_s1);
                        measForce= plot_obj->getForce2();
                        plot_obj->HystDisp2.append(time_in_s1);
                        plot_obj->loadCellData2.append(plot_obj->getActTwoForceScale() * measForce);
                        //std::cout << plot_obj->HystDisp2.size() << "\n";
                        //std::cout << plot_obj->loadCellData2.size() << "\n";
                        ForceVecAct2.push_back(measForce);
                    }
                    else if (ActuatorSelections[0][0] == 2) {
                        //std::cout << "Test 2\n";
                        plot_obj->YCommandAct2.append(plot_obj->getActTwoDispScale() * (double) xt[gcount-1][0]);
                        //plot_obj->YCommandAct2.append((double xt2[gcount - 1]))
                        //std::cout << xt[gcount - 1] << "\n";
                        CommandVecAct2.push_back((double) xt[gcount-1][0]);
                        plot_obj->XCommandAct2.append((double) time_in_s1);
                        CommandTimeAct2.push_back((double) time_in_s1);
                        plot_obj->HystDisp2.append(time_in_s1);
                        double measForce = plot_obj->getForce2();
                        plot_obj->loadCellData2.append(plot_obj->getActTwoForceScale() * measForce);
                        ForceVecAct2.push_back((measForce));


                        //Send Command
                        dispCommand2 = xt[gcount-1][0];
                        data_to_send = (uint16_t) plot_obj->inchesToBits(2,dispCommand);
                        plot_obj->serialWrite(2,0,data_to_send);


                        double act1Command;
                        if(plot_obj->getControlType() == 0){
                            act1Command = plot_obj->getDispCommand();
                            plot_obj->YCommand.append(act1Command);
                        } else {
                            act1Command = plot_obj->getForceCommand();
                            plot_obj->YForceCommand.append(act1Command);
                        }
                        //plot_obj->YCommandAct2.append(plot_obj->getActOneDispScale() * );
                        CommandVec.push_back((double) act1Command);
                        plot_obj->XCommand.append((double) time_in_s1);
                        CommandTime.push_back((double) time_in_s1);
                        measForce= plot_obj->getForce();
                        plot_obj->HystDisp1.append(time_in_s1);
                        plot_obj->loadCellData1.append(plot_obj->getActOneForceScale() * measForce);
                        ForceVec.push_back(measForce);
                    }
                } else if (ActuatorSelections[0][0] != 0 && ActuatorSelections[0][1] != 0) {
                    //std::cout<< "Check\n";
                    //std::cout << "Test 3\n";
                    for (int i = 0; i < ActuatorSelections[0].size(); i++) {
                        if (ActuatorSelections[0][i] == 1) {
                            plot_obj->YCommand.append(plot_obj->getActOneDispScale() * (double) xt[gcount-1][i]);
                            //plot_obj->YCommandAct2.append((double xt2[gcount - 1]))
                            //std::cout << xt[gcount - 1] << "\n";
                            CommandVec.push_back((double) xt[gcount-1][i]);
                            plot_obj->XCommand.append((double) time_in_s1);
                            CommandTime.push_back((double) time_in_s1);
                            plot_obj->HystDisp1.append(time_in_s1);
                            plot_obj->loadCellData1.append(plot_obj->getActOneForceScale() * plot_obj->getForce());

                            dispCommand = xt[gcount-1][i];
                            data_to_send = (uint16_t) plot_obj->inchesToBits(1,dispCommand);
                            plot_obj->serialWrite(1,0,data_to_send);

                        } else if (ActuatorSelections[0][i] == 2) {
                            plot_obj->XdataAct2.append((double) time_in_s1);
                            DispTimeAct2.push_back((double) time_in_s1);
                            plot_obj->YdataAct2.append(plot_obj->getActTwoDispScale() * (double) received_Disp2);
                            DispVecAct2.push_back(received_Disp2);
                            plot_obj->YCommandAct2.append(plot_obj->getActTwoDispScale() * (double) xt[gcount-1][i]);
                            CommandVecAct2.push_back((double) xt[gcount-1][i]);
                            plot_obj->XCommandAct2.append((double) time_in_s1);
                            CommandTimeAct2.push_back((double) time_in_s1);
                            plot_obj->HystDisp2.append(time_in_s1);
                            plot_obj->loadCellData2.append(plot_obj->getActTwoForceScale() * plot_obj->getForce2());

                            dispCommand2 = xt[gcount-1][i];
                            data_to_send = (uint16_t) plot_obj->inchesToBits(2,dispCommand2);
                            plot_obj->serialWrite(2,0,data_to_send);
                        }
                    }
                }




                //qDebug("%f",xt[gcount-1]);
                //Dont understand why I was doing this. Leaving in case I need it later
                /*gettimeofday(&tv, NULL);
                time_in_mill1 = tv.tv_usec;
                time_in_s1 = tv.tv_sec + time_in_mill1/1000000.0-time_initial;
                plot_obj->XCommand.append((double) time_in_s1);
                CommandTime.push_back((double) time_in_s1);*/

                if (time_in_s1 >= axlim){
                    setlim = 1;
                }

                //checks the amount of time it takes to run an hsm loop
                gettimeofday(&signaltv, NULL);
                loop_in_mill_end = signaltv.tv_usec;
                loop_in_s_end = signaltv.tv_sec + loop_in_mill_end/1000000.0;
                signalLoops.push_back(loop_in_s_end-loop_in_s_beg);
                pthread_mutex_unlock(&race_mutex);
                wait_rest_of_period(&pinfo);

                //does this work?
                //plot_obj->updatePlot();
            }
            qDebug("done");

            //This ramps the actuator back to 0 in order to reset the specimen. Is not really necessary


            //A = round((xt[gcount]+span)*3300.0/(2*span));

                   //WRITING TO DAC
                   //while(A>zeroPoint){
                   //        A = A-1;
                           //DAQ->DACWrite(DAC0,A);
                   //        expi.dac_set_raw(A,2, 2);
                   //        usleep(10000);
                   //}
                   //while(A<zeroPoint){
                   //        A = A+1;
                           //DAQ->DACWrite(DAC0,A);
                   //        expi.dac_set_raw(A,2, 2);
                   //        //printf("About to sleep");
                   //        usleep(10000);
                   //}
            running = 0;
        }else{

            // Runs a sin wave command on target actuator (s)
            int actuatorSelected = plot_obj->ui->selectAct->value();
            double act1Command;
            double act2Command;
            while (sinOn == 1 && running == 1) {

                //gets time

                //this is to check the amount of time it takes to send a sin signal
                gettimeofday(&signaltv, NULL);
                loop_in_mill_beg = signaltv.tv_usec;
                loop_in_s_beg = signaltv.tv_sec + time_in_mill1/1000000.0;


                gettimeofday(&tv, NULL);
                time_in_mill1 = tv.tv_usec;
                time_in_s1 = tv.tv_sec + time_in_mill1/1000000.0-time_initial;

                if(actuatorSelected == 1) {
                    if(plot_obj->getControlType() == 0) {
                        act1Command = (double) sinWave[i];
                        data_to_send = (uint16_t) plot_obj->inchesToBits(1,act1Command);
                        plot_obj->serialWrite(1,0,data_to_send);
                    } else if (plot_obj->getControlType() == 1) {
                        act1Command = (double) sinWave[i];
                        double double_to_send = act1Command / forceSlope + zeroForce;
                        plot_obj->sendDouble(1,command,double_to_send);
                    }
                    if(plot_obj->getControlType2() == 0) {
                        act2Command = plot_obj->getDispCommand2();
                    } else if (plot_obj->getControlType() == 1) {
                        act2Command = plot_obj->getForceCommand2();
                    }
                } else if (actuatorSelected == 2){
                    if(plot_obj->getControlType() == 0) {
                        act1Command = plot_obj->getDispCommand();
                    } else if (plot_obj->getControlType() == 1) {
                        act1Command = plot_obj->getForceCommand2();
                    }
                    if(plot_obj->getControlType2() == 0) {
                        act2Command = (double) sinWave[i];
                        data_to_send = (uint16_t) plot_obj->inchesToBits(2,act2Command);
                        plot_obj->serialWrite(2,0,data_to_send);
                    } else if (plot_obj->getControlType2() == 1) {
                        act2Command = (double) sinWave[i];
                        double double_to_send = act2Command / forceSlope2 + zeroForce2;
                        plot_obj->sendDouble(2,command,double_to_send);
                    }
                }




                if(firstActuatorOn){
                    received_Disp = plot_obj->receivedToInches(1,(double)plot_obj->serialRead(1, 1, 0));
                    plot_obj->readForce(0);
                    pthread_mutex_lock(&race_mutex);
                    if(plot_obj->getControlType() == 0){
                        plot_obj->YCommand.append(plot_obj->getActOneDispScale() * act1Command);
                        plot_obj->XCommand.append((double) time_in_s1);
                    }
                    if(plot_obj->getControlType() == 1){
                        plot_obj->YForceCommand.append(plot_obj->getActOneForceScale() * act1Command);
                        plot_obj->XForceCommand.append((double) time_in_s1);
                    }
                    plot_obj->Xdata.append((double) time_in_s1);
                    plot_obj->Ydata.append(plot_obj->getActOneDispScale() * (double) received_Disp);
                    plot_obj->HystDisp1.append((double) time_in_s1);
                    plot_obj->loadCellData1.append(plot_obj->getActOneForceScale() * (double) received_Force);

                    sinCommand.push_back(act1Command);
                    sinResponse.push_back(received_Disp);
                    sinForce.push_back(received_Force);
                    sinTime.push_back((double) time_in_s1);
                }
                //maybe edit this to allow for two sin signals at once
                if(secondActuatorOn) {
                    plot_obj->readForce(1);
                    received_Disp2 = plot_obj->receivedToInches(2,(double)plot_obj->serialRead(2, 1, 0));
                    if(plot_obj->getControlType2() == 0){
                        plot_obj->YCommandAct2.append(plot_obj->getActTwoDispScale() * act2Command);
                        plot_obj->XCommandAct2.append((double) time_in_s1);
                    }
                    if(plot_obj->getControlType2() == 1){
                        plot_obj->YForceCommandAct2.append(plot_obj->getActTwoForceScale() * act2Command);
                        plot_obj->XForceCommandAct2.append((double) time_in_s1);
                    }
                    plot_obj->XdataAct2.append((double) time_in_s1);
                    plot_obj->YdataAct2.append(plot_obj->getActTwoDispScale() * (double) received_Disp2);
                    plot_obj->HystDisp2.append((double) time_in_s1);
                    plot_obj->loadCellData2.append(plot_obj->getActTwoForceScale() * (double) received_Force2);

                    sinCommand2.push_back(act2Command);
                    std::cout << act2Command << "\n";
                    sinResponse2.push_back(received_Disp2);
                    sinForce2.push_back(received_Force2);
                    sinTime2.push_back((double) time_in_s1);
                }
                pthread_mutex_unlock(&race_mutex);

                DispVec.push_back((double) received_Disp);

                if(i<sinWave.size()-1){
                   i = i+1;
                }else{
                   i = 0;
                }

                j = j+1;
                //qDebug("%f",time_in_s1);
                /*if (time_in_s1>=runaxlim){
                    std::cout<<"WHy am I not working \n";
                    setlim = 1;
                }*/

                //sends command to actuator







                if (sinsweep == 1 && i*tstep>(30-2*tstep)){
                    running = 0;
                }
                if (amptest == 1 && slope*j*tstep>amp){
                    running = 0;
                }
                gettimeofday(&signaltv, NULL);
                loop_in_mill_end = signaltv.tv_usec;
                loop_in_s_end = signaltv.tv_sec + time_in_mill1/1000000.0;
                signalLoops.push_back(loop_in_s_end-loop_in_s_beg);
                wait_rest_of_period(&pinfo);

            }
    }

        return NULL;
}


static void inc_period(struct period_info *pinfo)
{
        pinfo->next_period.tv_nsec += pinfo->period_ns;

        while (pinfo->next_period.tv_nsec >= 1000000000) {
                /* timespec nsec overflow */
                pinfo->next_period.tv_sec++;
                pinfo->next_period.tv_nsec -= 1000000000;
        }
}

static void periodic_task_init(struct period_info *pinfo)
{

    if(sinOn==0){
        if(cv==1){
            //send a signal every 10 ms
            //trying every 1 ms
            pinfo->period_ns = sigt*1000000000;
        }
        else{
            /* for simplicity, hardcoding a .5ms period */
            pinfo->period_ns = 500000;
        }

        clock_gettime(CLOCK_MONOTONIC, &(pinfo->next_period));
    }else {
        pinfo->period_ns = tstep*1000000000;
        clock_gettime(CLOCK_MONOTONIC, &(pinfo->next_period));
}
}

static void wait_rest_of_period(struct period_info *pinfo)
{
        inc_period(pinfo);

        /* for simplicity, ignoring possibilities of signal wakes */
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &pinfo->next_period, NULL);

}

static void const_vel(hsm_full* object)
{
    //printf("%f\n",nsteps);
    //received_data = wiringPiI2CReadReg16(fd,0x00);
    //received_data = (expi.adc_read_raw(2,0)-1650.0)*5.5/1650.0;
    //qDebug("%f",cur_x);
    if (done == 0){
        xt.push_back(cur_x);
        gcount++;

        /*if (microcont == 1){
            command = 0;
            command = command<<12;
            data_to_send = round((xt[gcount]+span)*4095.0/(2*span)+(ogZero-2048));
            data_to_send = data_to_send | command;
            //wiringPiI2CWriteReg16(fd,0x00,data_to_send);
        }else if(microcont ==2){
            command = 0;
            command = command<<10;
            data_to_send = round((xt[gcount]+span)*1023.0/(2*span)+(ogZero-512));
            data_to_send = data_to_send | command;
            //wiringPiI2CWriteReg16(fd,0x00,data_to_send);
        }
        else{

            //expi.dac_set_raw(std::min(3300.0,round((xt[gcount]+span)*3300.0/(2*span))+(sendZero-1650)),2,2);
        }*/

        //std::cout << "Sent data: " << (int)data_to_send << "\n";

        //std::cout << "Data received: " << received_data << "\n";
    }else if (count == ceil(nsteps) || nsteps == 0){
        std::cout << "Step: " << intcount << "\n";
        //std::cout <<"number of steps: "<< nsteps << "\n";
        if (nsteps == 0){
            cur_x = cur_x;
        }else{
            cur_x[0] = cur_x[0]+dx[0]/ceil(nsteps);
            cur_x[1] = cur_x[1]+dx[1]/ceil(nsteps); //can you do element wise division? Look up
        }
        xt.push_back(cur_x);
        intIndex.push_back(gcount);
        gcount++;
       // printf("Sending signal\n");
        //pthread_mutex_lock(&race_mutex);
        //df = K * (xn[intcount] -xp);
        xp = xn[intcount];
        eqp = GM[intcount];
        //fp = f_prev+df;
        //pthread_mutex_lock(&race_mutex);
        fp = {object->getForce(),0.0};
        //pthread_mutex_unlock(&race_mutex);
        //std::cout << "got Force: " << fp[0] << "\n";
        fp = {30.0 * xn[intcount][0], 0.0};
        //printf("Force Reading\n");
        //std::cout << xn[intcount] << "\n";
        //fp[1] = 3.3 * xn[intcount];

        //fp = 3.3* xp;


        count = 0;
        intcount++;
        Cor = 0;
        done = 0;
        //pthread_mutex_unlock(&race_mutex);
        pthread_cond_signal(&trigger);
        /*if (microcont == 1){
            command = 0;
            command = command<<12;
            data_to_send = round((xt[gcount]+span)*4095.0/(2*span)+(ogZero-2048));
            data_to_send = data_to_send | command;
            //wiringPiI2CWriteReg16(fd,0x00,data_to_send);
        }else if(microcont ==2){
            command = 0;
            command = command<<10;
            data_to_send = round((xt[gcount]+span)*1023.0/(2*span)+(ogZero-512));
            data_to_send = data_to_send | command;
            //wiringPiI2CWriteReg16(fd,0x00,data_to_send);
        }
        else{
            //expi.dac_set_raw(round((xt[gcount]+span)*3300.0/(2*span)+(sendZero-1650)),2, 2);
        }*/
        count++;
        force.push_back(fp[0]);
    }else if(count!=ceil(nsteps)){
        cur_x[0] = cur_x[0]+dx[0]/nsteps;
        cur_x[1] = cur_x[1]+dx[1]/nsteps;
        xt.push_back(cur_x);
        //std::cout << cur_x[0] << ", " << cur_x[1] << "\n";
        gcount++;
        /*if (microcont == 1){
            command = 0;
            command = command<<12;
            data_to_send = round((xt[gcount]+span)*4095.0/(2*span)+(ogZero-2048));
            data_to_send = data_to_send | command;
            wiringPiI2CWriteReg16(fd,0x00,data_to_send);
        }else if(microcont ==2){
            command = 0;
            command = command<<10;
            data_to_send = round((xt[gcount]+span)*1023.0/(2*span)+(ogZero-512));
            data_to_send = data_to_send | command;
            wiringPiI2CWriteReg16(fd,0x00,data_to_send);
        }
        else{
            //expi.dac_set_raw(round((xt[gcount]+span)*3300.0/(2*span))+(sendZero-1650),2, 2);
        }*/

        count++;

    }

    //Send signal to actuators



}



static void do_pred_cor()
{


        //measure force
        //struct timeval tv;
        gettimeofday(&tv, NULL);

        double time_in_mill = tv.tv_usec;
        double time_in_s = tv.tv_sec + time_in_mill/1000000.0;
        //printf("%f\n",time_in_s);
        //printf("%f\n",count);

        if (count==count_lim && done == 1){

                pthread_mutex_lock(&race_mutex);
                df = K * (xn[0][intcount] -xp[0]);
                xp = xn[intcount];
                //printf("%f\n",xp);
                xdp = xd[intcount];
                xddp = xdd[intcount];
                eqp = EQ_h[intcount];

                fp[0] = f_prev+df;

                if (fp[0]>fy){
                        fp[0] = fy;
                }if(fp[0]<-fy){
                        fp[0] = -fy;
                }

                pthread_mutex_unlock(&race_mutex);
                count = 0;
                intcount++;
                Cor = 0;
                done = 0;
                printf("send trigger signal\n");

                pthread_cond_signal(&trigger);
                oof.push_back(0);
                //printf("%d",x.size());
                //printf("%d\n",intcount);

        }else if (count == count_lim && done ==0){
                printf("send trigger signal\n");
                oof.push_back(1);
                printf("oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooops\n");
                //pthread_cond_signal(&trigger);
                count = 0;
                Cor = 0;
        }

        dp_last = xn[intcount - 1][0];

        if(Cor == 0){

                if(intcount>3){
                        xlag = (count)/10.0;
                        P0 = 1.0/6.0 * (xlag+1.0)*(xlag+2.0)*(xlag+3.0);
                        Pn1 = -1.0/2.0 * xlag*(xlag+2.0)*(xlag+3.0);
                        Pn2 = 1.0/2.0 * xlag*(xlag+1.0)*(xlag+3.0);
                        Pn3 = -1.0/6.0*xlag*(xlag+1.0)*(xlag+2.0);


                        pthread_mutex_unlock(&race_mutex);
                        xt[0].push_back(P0*xn[intcount-1][0]+Pn1*xn[intcount-2][0]+Pn2*xn[intcount-3][0]+Pn3*xn[intcount-4][0]);
                        dp_last = P0*xn[intcount-1][0]+Pn1*xn[intcount-2][0]+Pn2*xn[intcount-3][0]+Pn3*xn[intcount-4][0];
                        pthread_mutex_unlock(&race_mutex);
                        pcount_last = xlag;
                }else{
                        pthread_mutex_lock(&race_mutex);
                        xt[0].push_back(0);
                        pthread_mutex_unlock(&race_mutex);
                }
        }else{


                if(intcount>2){
                        pcount_last = 0;
                        xlag = (count)/10.0;
                        Cp1 = -1.0/6.0 * (xlag-pcount_last)*(xlag+1.0)*(xlag+2.0)/(pcount_last-1.0);
                        C0 = (xlag-1)*(xlag+1.0)*(xlag+2.0)/((pcount_last-1.0)*(pcount_last+1.0)*(pcount_last+2.0)); //this might need a 1/2
                        Cn1 = 1.0/2.0 * (xlag-1.0)*(xlag-pcount_last)*(xlag+2.0)/(pcount_last+1.0);
                        Cn2 = -1.0/3.0 * (xlag-1.0)*(xlag-pcount_last)*(xlag+1.0)/(pcount_last+2.0);

                        pthread_mutex_lock(&race_mutex);
                        xt[0].push_back(Cp1*xn[intcount][0]+C0*xn[intcount-1][0]+Cn1*xn[intcount-2][0]+Cn2*xn[intcount-3][0]);
                        pthread_mutex_unlock(&race_mutex);
                        //printf("%f\n",Cn2);
                }else{
                        pthread_mutex_lock(&race_mutex);
                        xt[0].push_back(0);
                        pthread_mutex_unlock(&race_mutex);
                }


        }

        //This is setting the DAC
        //DAQ->DACWrite(DAC0,round((xt[gcount]+2.0)*4095.0/4.0));
        //3378 is to adjust to roughly 3.3 volts as the max. currently it is 4
        //expi.dac_set_raw(round((xt[gcount]+span)*3378.0/(2*span)),2, 2);
        count++;
        gcount++;
        //printf("%f\n",xt[gcount]);

        //printf("%d\n",gcount);

}

void *Time_integrator(void* data)
{
        pthread_mutex_lock(&trigger_mutex);
        /*if (!gil_init) {
            gil_init = 1;
            PyEval_SaveThread();
        }*/

        int GM_dim[1] = {(int)GM.size()};
        int fp_dim[1] = {(int)fp.size()};
        double *GMmem = &GM[0];
        PyGM = PyArray_SimpleNewFromData(1,GM_dim,NPY_DOUBLE,(double*)GMmem);
        while(intcount < GM.size()-1) {
                //PyGILState_STATE state = PyGILState_Ensure();
                //printf("%d\n",intcount);
                //printf("waiting\n");
                pthread_cond_wait(&trigger,&trigger_mutex);
                double *fpmem = &fp[0];
                Pyfp = PyArray_SimpleNewFromData(1,fp_dim,NPY_DOUBLE,(double*)fpmem);
                //qDebug("Force: %f",fp[0]);
                //printf("IntCount: %d\n",intcount);
                //values sent to the integrator
                //printf("%f\n",xp);
                //printf("%f\n",fp);
                //printf("%d\n",intcount);
                //u_p = PyFloat_FromDouble(xp);

                //f_p = PyLong_FromLong(fp[0]);
                iter = PyLong_FromLong(intcount);

                pythonArgument = PyTuple_New(4);
                PyTuple_SetItem(pythonArgument, 0, Model);
                PyTuple_SetItem(pythonArgument, 1, Pyfp);
                PyTuple_SetItem(pythonArgument, 2, PyGM);
                PyTuple_SetItem(pythonArgument, 3, iter);


                if (pModule != NULL) {
                           if (pFunc2 && PyCallable_Check(pFunc2)) {
                                   x_next2 = PyObject_CallObject(pFunc2, pythonArgument);
                                   if (x_next2 != NULL) {
                                       Model = PyTuple_GetItem(x_next2,0);
                                       //std::cout << "Is Model Null? " << (Model == NULL) << "\n";
                                       //printf("%f",PyFloat_AsDouble(PyTuple_GetItem(x_next2,1)));
                                       PyArrayObject *xNext = (PyArrayObject*) PyTuple_GetItem(x_next2,1);
                                       double* x_next = (double*)PyArray_DATA(xNext);
                                       PyArrayObject *xdNext = (PyArrayObject*) PyTuple_GetItem(x_next2,2);
                                       double* xd_next = (double*)PyArray_DATA(xNext);
                                       PyArrayObject *xddNext = (PyArrayObject*) PyTuple_GetItem(x_next2,3);
                                       double* xdd_next = (double*)PyArray_DATA(xNext);                             
                                       if (numControlDOFS == 1) {
                                           xn.push_back({x_next[0],0.0});
                                           //std::cout << "x next: " <<< "\n";
                                           xd.push_back({xd_next[0],0});
                                           xdd.push_back({xdd_next[0],0});
                                       }

                                       if(numControlDOFS == 2) {
                                           xn.push_back({x_next[0],x_next[1]});
                                           //std::cout << "x next: " << x_next[0] << ", " << x_next[1] << "\n";
                                           xd.push_back({xd_next[0],xd_next[1]});
                                           xdd.push_back({xdd_next[1],xdd_next[1]});
                                       }

                                       //std::cout << "int result recieved \n";
                                       if(cv ==1){

                                           if(numControlDOFS == 2) {
                                               dx[0] = x_next[0] - cur_x[0];
                                               dx[1] = x_next[1] - cur_x[1];
                                               //std::cout << "current x: " << cur_x[1] << "\n";
                                               //std::cout << "dx: " << dx[0] << ", " << dx[1] << "\n";
                                               if(abs(dx[0]) > abs(dx[1])) {
                                                   ActuatorVel[0] = vel;
                                                   nsteps = abs(dx[0])/(ActuatorVel[0]*sigt);
                                                   ActuatorVel[1] = abs(dx[1]) / (nsteps *sigt);
                                                   //std::cout << "new velocity: " << ActuatorVel[1] << "\n";
                                               } else {
                                                   ActuatorVel[1] = vel;
                                                   nsteps = abs(dx[1])/(ActuatorVel[1]*sigt);
                                                   ActuatorVel[0] = abs(dx[0]) / (nsteps *sigt);
                                               }
                                           }
                                           if(numControlDOFS == 1) {
                                               dx[0] = x_next[0] - cur_x[0];
                                               ActuatorVel[0] = vel;
                                               nsteps = abs(dx[0])/(ActuatorVel[0]*sigt);
                                           }
                                           //printf("%f\n",dx);
                                           //printf("%f\n",nsteps);
                                           //std::cout << "number of steps calculatted: " << nsteps << "\n";
                                       }
                                       Cor = 1;

                                       //gettimeofday(&tv, NULL);
                                       //double time_in_mill1 = tv.tv_usec;
                                       //double t2 = tv.tv_sec + time_in_mill1/1000000.0;

                                       done = 1;
                                       pthread_mutex_unlock(&race_mutex);
                                   }else {
                                           PyErr_Print();
                                   }
                           }else {
                                   if (PyErr_Occurred())
                                   PyErr_Print();
                                   fprintf(stderr, "Cannot find function %s\n", "InitializeAlphaOS");
                           }
                   }
                   else {
                           PyErr_Print();
                           fprintf(stderr, "Failed to load %s\n", "Time_Integrator");
                   }

                //PyGILState_Release(state);
                pthread_mutex_unlock(&trigger_mutex);
        }
        printf("Done\n");
}



/*static void Call_Integrator(){
    printf("Check1\n");
    running = 1;
    if (pModule2 != NULL) {
            printf("Hello\n");
            std::vector<double> testArray = {1.,2.,3.,4.,5.};
            int test_dim[1] = {(int)testArray.size()};
            double *testmem = &testArray[0];

            PyObject* PyGMtest = PyArray_SimpleNewFromData(1,test_dim,NPY_DOUBLE,(double*)testmem);
            if (pFunc2 && PyCallable_Check(pFunc2)) {
                    gettimeofday(&tv, NULL);
                    pythonArgument = PyTuple_New(1);
                    PyTuple_SetItem(pythonArgument, 0, PyGMtest);
                    //printf("Pos5\n");
                    //std::cout << "Calling Python" << std::endl;
                    //pthread_mutex_lock(&race_mutex);
                    python_return = PyObject_CallObject(pFunc2,pythonArgument);


            }else{
                    if (PyErr_Occurred())
                            PyErr_Print();
                            fprintf(stderr, "Cannot find function %s\n", "Test_Python");
                    }
    }else {
            PyErr_Print();
            fprintf(stderr, "Failed to load %s\n", "Test_Python");
    }
    count++;
}*/


hsm_full::hsm_full(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::hsm_full)
{

    closeCallbackHsm = [&](){
        std::cout << "Window was closed" << "\n";
        eStopActive = true;
        turnOffHydraulics();
        if(controller == 1) {
            startControl();
        }
        if(controller2 == 1) {
            startControl2();
        }
    };

    //std::cout << "Is Hardware Connected?     " << hardwareConnected << "\n";
    initializeLoad();
    eStopActive = false;
    wiringPiSetup();			// Setup the library
    pinMode(7, OUTPUT);
    pinMode(actOneHighPin, OUTPUT);
    pinMode(actOneLowPin, OUTPUT);
    pinMode(actTwoLowPin, OUTPUT);
    pinMode(actTwoHighPin, OUTPUT);
    pinMode(actTwoHighPin, OUTPUT);
    pinMode(0, OUTPUT);
    pinMode(2,INPUT);
    digitalWrite(0, 1);
    setvbuf (stdout, NULL, _IONBF, 0);
    ui->setupUi(this);

    if((fd=serialOpen("/dev/ttyAMA0", 500000))<0){
      qDebug("Unable to open serial device 1: %s\n",strerror(errno));
    }
    if((fd2=serialOpen("/dev/ttyAMA1",500000))<0){
      qDebug("Unable to open serial device 2: %s\n",strerror(errno));
    }
    if((fd3=serialOpen("/dev/ttyACM0",115200))<0){
      qDebug("Unable to open serial device 3: %s\n",strerror(errno));
    }

    serialFlush(fd);
    serialFlush(fd2);
    serialFlush(fd3);



/*    std::vector<std::vector<double>> forceCalData = readFiles("forceSlopes.txt");
    if (forceCalData[0].size() == 1) {
        std::cout << "No Force Calibration File, Be sure top set slopes for Load Cell \n";
    } else {
        forceSlope = forceCalData[0][0];
        ui->LC1SlopeInput->setValue(forceSlope);
        std::cout << "Slope for LC 1 is: " << forceSlope << "\n";
        forceSlope2 = forceCalData[0][1];
        ui->LC2SlopeInput->setValue(forceSlope2);
        std::cout << "Slope for LC 2 is: " << forceSlope2 << "\n";
        zeroForce = forceCalData[1][0];
        std::cout << "Zero Force in bits for LC 1 is: " << zeroForce << "\n";
        zeroForce2 = forceCalData[1][1];
        std::cout << "Zero Force in bits for LC 2 is: " << zeroForce2 << "\n";
        LC1Offset = forceCalData[2][0];
        ui->LC1Int->setValue(LC1Offset);
        serialWrite(3,1,LC1Offset);
        std::cout << "Offset for LC 1 Electronically (fine tune): " << LC1Offset << "\n";
        LC2Offset = forceCalData[2][1];
        ui->LC2Int->setValue(LC2Offset);
        serialWrite(3,2,LC2Offset);
        std::cout << "Offset for LC 2 Electronically (fine tune): " << LC2Offset << "\n";
        LC1Zero = forceCalData[3][0];
        ui->LC1Int_2->setValue(LC1Zero);
        serialWrite(3,3,LC1Zero);
        std::cout << "Zero for LC 1 Electronically (Coarse tune): " << LC1Zero << "\n";
        LC2Zero = forceCalData[3][1];
        ui->LC2Int_2->setValue(LC2Zero);
        serialWrite(3,4,LC2Zero);
        std::cout << "Zero for LC 2 Electronically (Coarse tune): " << LC2Zero << "\n";
    }*/


    std::vector<std::vector<double>> interlockData = readFiles("Interlocks.txt");
    if (interlockData[0].size() == 1) {
        std::cout << "No Interlock File, Be sure to set interlocks \n";
    } else {
        maxDisp = interlockData[0][0];
        std::cout << "Max Displacement Interlock on Actuator 1 set to " << maxDisp << "\n";
        maxDisp2 = interlockData[0][1];
        std::cout << "Max Displacement Interlock on Actuator 2 set to " << maxDisp2 << "\n";
        minDisp = interlockData[1][0];
        std::cout << "Min Displacement Interlock on Actuator 1 set to " << minDisp << "\n";
        minDisp2 = interlockData[1][1];
        std::cout << "Min Displacement Interlock on Actuator 2 set to " << minDisp2 << "\n";
        maxForce = interlockData[2][0];
        std::cout << "Max Force Interlock on Actuator 1 set to " << maxForce << "\n";
        maxForce2 = interlockData[2][1];
        std::cout << "Max Force Interlock on Actuator 2 set to " << maxForce2 << "\n";
        minForce = interlockData[3][0];
        std::cout << "Min Force Interlock on Actuator 1 set to " << minForce << "\n";
        minForce2 = interlockData[3][1];
        std::cout << "Min Force Interlock on Actuator 2 set to " << minForce2 << "\n";
    }

    std::vector<std::vector<double>> ScaleData = readFiles("Scale.txt");
    if (ScaleData[0].size() == 1) {
        std::cout << "No Scale File, Scales all set to 1";
    } else {
        actOneDispScale = ScaleData[0][0];
        std::cout << "Displacement Scale on Actuator 1 set to " << actOneDispScale << "\n";
        ui->Act1DispScale->setValue(actOneDispScale);
        actOneForceScale = ScaleData[0][1];
        std::cout << "Force Scale on Actuator 1 set to " << actOneForceScale << "\n";
        ui->Act1ForceScale->setValue(actOneForceScale);
        actTwoDispScale = ScaleData[1][0];
        std::cout << "Displacement Scale on Actuator 2 set to " << actTwoDispScale << "\n";
        ui->Act2DispScale->setValue(actTwoDispScale);
        actTwoForceScale = ScaleData[1][1];
        std::cout << "Force Scale on Actuator 2 set to " << actTwoForceScale << "\n";
        ui->Act2ForceScale->setValue(actTwoForceScale);
    }

    std::vector<std::vector<double>> LCData = readFiles("LCData.txt");
    if (LCData[0].size() == 1) {
        std::cout << "No Scale File, Scales all set to 1";
    } else {
        forceSlope = LCData[0][0];
        std::cout << "Force Slope on Actuator 1 set to " << forceSlope << "\n";
        ui->Act1LCSlope->setValue(forceSlope);
        forceSlope2 = LCData[0][1];
        std::cout << "Force Slope on Actuator 2 set to " << forceSlope2 << "\n";
        ui->Act2LCSlope->setValue(forceSlope2);
        zeroForce = LCData[1][0];
        std::cout << "Zero Force on Actuator 1 set to " << zeroForce << "\n";
        zeroForce2 = LCData[1][1];
        std::cout << "Zero Force on Actuator 2 set to " << zeroForce2 << "\n";
        LC1Max = LCData[2][0];
        std::cout << "Max Force on Actuator 1 set to " << LC1Max << "\n";
        ui->Act1MaxLC->setValue(LC1Max);
        LC2Max = LCData[2][1];
        std::cout << "Max Force on Actuator 2 set to " << LC2Max << "\n";
        ui->Act2MaxLC->setValue(LC2Max);

    }

    readAllFilesAndCalibrate();
    timer = new QTimer(this);
    eStopTimer = new QTimer(this);
    eStopTimer -> start(10);
    connect(eStopTimer,&QTimer::timeout,this,&hsm_full::turnOffHydraulics);
    connect(timer,&QTimer::timeout,this,&hsm_full::updateLCD);
    timer->start(100);\
    if(logcontrolloops == 1){
        timer2 = new QTimer(this);
        connect(timer2,&QTimer::timeout,this,&hsm_full::reqloops);
        timer2->start(1000);
    }
    ui->Act1LowOn->setText("Off");
    ui->Act1HighOn->setText("Off");
    ui->Act2LowOn->setText("Off");
    ui->Act2HighOn->setText("Off");
    wiringPiISR(2, INT_EDGE_RISING, &eStop);

    //Temporary load cell parameters
    loadCellZeroInBits = 1650;
    loadCellSlope = 1.0 / 100.0;

    if (loadModel() == 0) {
        std::cout << "Model Loaded from file\n";
    } else{
        std::cout << "Model not Loaded Properly. Define a model before running a simulation\n";
    };

    loadActuators();
    std::cout << "Reading Force \n";

    for(int i = 0; i < 100; i++) {
        readForce(0);
        readForce(1);
    }

    qDebug("Test Starts now!");
    /*if (microcont ==1 or microcont ==2){
       // Setup I2C communication
       fd = wiringPiI2CSetup(DEVICE_ID);
       printf("%d\n",fd);
       //pi = pigpio_start(NULL,NULL);
       //fd = i2c_open(pi,1,DEVICE_ID,0);
       if (fd == -1) {
           std::cout << "Failed to init I2C communication.\n";
       }else{
           std::cout << "I2C communication successfully setup.\n";
       }
    }*/

    //readForce(1);

    //qDebug("Read from Controller 2: %d",serialRead(2, 1, 0));

    DynamicsFile = readFiles("InterpGM.txt");
    if(DynamicsFile[0][0] == -1) {
        std::cout << "Ground Motion Dynamics File not found. Make it in the Make Model menu\n";
    } else {
        for (int i = 0; i < DynamicsFile.size() - 1; i++){
            GM.push_back(DynamicsFile[i][1]);
        }
        DynOps = DynamicsFile.back();
        std::cout << "Dynamic Options\n " << "x Dir Scale: " << DynOps[0] << "\ny Dir Scale: " << DynOps[1] << "\nz Dir Scale:  " << DynOps[2] << "\nScale:  " << DynOps[3] << "\ndt Old:  " << DynOps[4] << "\ndt New: " <<
                     DynOps[5] << "\nAlpha: " << DynOps[6] << "\nZeta (Damping): " << DynOps[7] << "\nDamping Mode 1: " << DynOps[8] << "\nDamping Mode 2: " << DynOps[9] << "\n";
    }



   gettimeofday(&runtv, NULL);
   runtime_in_mill = runtv.tv_usec;
   runtime_initial = runtv.tv_sec + runtime_in_mill/1000000.0;
   //expi.adc_open();
   //calForce();
   initializeController(1);
   initializeController(2);

   /*if (microcont==1){
        zeroPoint = 2092;
        ogZero = 2092;
        zeroPoint_in = (zeroPoint-ogZero)*2*span/4095.0;
        command = 6;
        command = command<<12;
        data_to_send = 0;
        data_to_send = data_to_send | command;
        wiringPiI2CWriteReg16(fd,0x00,data_to_send);
        zeroPoint = wiringPiI2CReadReg16(fd,0x00);
        qDebug("%f",zeroPoint);
        zeroPoint_in = (2*span)*(zeroPoint-ogZero)/4095;
        span = (2*maxspan)*wiringPiI2CReadReg16(fd,0x00)/4095;
        PCommand = (Pmax/4095)*wiringPiI2CReadReg16(fd,0x00);
        ICommand = (Imax/4095)*wiringPiI2CReadReg16(fd,0x00);
        DCommand = (Dmax/4095)*wiringPiI2CReadReg16(fd,0x00);

   }else if (microcont ==2){
       zeroPoint = 512;
       ogZero = 523;
       zeroPoint_in = (zeroPoint-ogZero)*2*span/1023.0;
       command = 6;
       command = command<<10;
       data_to_send = 0;
       data_to_send = data_to_send | command;
       wiringPiI2CWriteReg16(fd,0x00,data_to_send);
       zeroPoint = wiringPiI2CReadReg16(fd,0x00);
       qDebug("%f",zeroPoint);
       zeroPoint_in = (2*span)*(zeroPoint-ogZero)/1023;
       span = (2*maxspan)*wiringPiI2CReadReg16(fd,0x00)/1023;
       PCommand = (Pmax/1023)*wiringPiI2CReadReg16(fd,0x00);
       ICommand = (Imax/1023)*wiringPiI2CReadReg16(fd,0x00);
       DCommand = (Dmax/1023)*wiringPiI2CReadReg16(fd,0x00);
   }
   else{
       zeroPoint = 1650;
       ogZero = 1665;
       zeroPoint_in = (zeroPoint-ogZero)*2*span/3300.0;
       zeroDisp = 40;
       //expi.dac_open();
       sendZero=1590;
       //expi.dac_set_raw(sendZero,2, 2);
       dprev = 0;
       //dprev = (expi.adc_read_raw(2,0)-1650.0-zeroDisp)*span/1650.0;
   }*/
    //qDebug("%d",zeroPoint);

    QWidget *wdg = new QWidget;
    //ui->IDisp->setPalette(Qt::black);
    ui->Offset->display(zeroPoint_in);
    ui->Offset_2->display(zeroPoint_in2);
    //ui->PDisp->display(PCommand);
    //ui->IDisp->display(ICommand);
    //ui->DDisp->display(DCommand);
    ui->CurSpan->display(totSpan);
    ui->CurSpan_2->display(totSpan2);
    index = 0;
    qDebug("Got this far");

    connect(ui->startButton, &QPushButton::released, this, &hsm_full::update);
    connect(ui->stiffButton, &QPushButton::released, this, &hsm_full::stiffTest);
    connect(ui->saveButton, &QPushButton::released, this, &hsm_full::save);
    connect(ui->AmpButton,&QPushButton::released,this,&hsm_full::setAmp);
    connect(ui->FreqButton,&QPushButton::released,this,&hsm_full::setFreq);
    connect(ui->SinButton,&QPushButton::released,this,&hsm_full::sinTest);
    connect(ui->SweepButton,&QPushButton::released,this,&hsm_full::sweep);
    connect(ui->AmpTestButton,&QPushButton::released,this,&hsm_full::ampTest);
    connect(ui->actionCalibration, &QAction::triggered,this,&hsm_full::Cal_Window);
    connect(ui->actionInterlocks, &QAction::triggered,this,&hsm_full::Interlock_Window);
    connect(ui->actionSet_Up_Model, &QAction::triggered,this,&hsm_full::PSAS_Window);
    connect(ui->actionPlot_Model, &QAction::triggered,this,&hsm_full::plotResults);

    //Actuator 1 Buttons
    connect(ui->FirstActBox,&QCheckBox::toggled,this,&hsm_full::useFirstActuator);
    connect(ui->CommandButton,&QPushButton::released,this,&hsm_full::sendCommand);
    connect(ui->DispPID,&QPushButton::released,this,&hsm_full::sendPID);
    //connect(ui->IButton,&QPushButton::released,this,&hsm_full::sendI);
    //connect(ui->DButton,&QPushButton::released,this,&hsm_full::sendD);
    connect(ui->ForcePID,&QPushButton::released,this,&hsm_full::sendPIDForce);
    connect(ui->horizontalSlider,&QSlider::sliderReleased,this,&hsm_full::sliderCommand);
    connect(ui->SliderButton,&QPushButton::released,this,&hsm_full::activateButton);
    connect(ui->SpanButton,&QPushButton::released,this,&hsm_full::pressSpanButton);
    connect(ui->zeroButton,&QPushButton::released,this,&hsm_full::setZero);
    connect(ui->fZeroButton,&QPushButton::released,this,&hsm_full::calForce);
    //connect(ui->StartControl,&QPushButton::released,this,&hsm_full::startControl);
    connect(ui->ActOneLowButton,&QPushButton::released,this,&hsm_full::turnOnLow1);
    connect(ui->ActOneHighButton,&QPushButton::released,this,&hsm_full::turnOnHigh1);
    //connect(ui->LC1Button, &QPushButton::released,this,&hsm_full::adjustLC1);
    //connect(ui->LC1Button_2, &QPushButton::released,this,&hsm_full::adjustLC1Zero);
    //connect(ui->LC1SlopeButton, &QPushButton::released,this,&hsm_full::setLC1Slope);
    connect(ui->SwitchControlButton, &QPushButton::released,this,&hsm_full::switchControlType);

    //Actuator 2 Buttons
    connect(ui->SecondActBox,&QCheckBox::toggled,this,&hsm_full::useSecondActuator);
    connect(ui->CommandButton_2,&QPushButton::released,this,&hsm_full::sendCommand2);
    connect(ui->DispPID2,&QPushButton::released,this,&hsm_full::sendPID2);
    connect(ui->ForcePID_2,&QPushButton::released,this,&hsm_full::sendPIDForce2);
    connect(ui->horizontalSlider_2,&QSlider::sliderReleased,this,&hsm_full::sliderCommand2);
    connect(ui->SliderButton_2,&QPushButton::released,this,&hsm_full::activateButton2);
    connect(ui->SpanButton_2,&QPushButton::released,this,&hsm_full::pressSpanButton2);
    connect(ui->zeroButton_2,&QPushButton::released,this,&hsm_full::setZero2);
    connect(ui->fZeroButton_2,&QPushButton::released,this,&hsm_full::calForce2);
    //connect(ui->StartControl_2,&QPushButton::released,this,&hsm_full::startControl2);
    connect(ui->ActTwoLowButton,&QPushButton::released,this,&hsm_full::turnOnLow2);
    connect(ui->ActTwoHighButton,&QPushButton::released,this,&hsm_full::turnOnHigh2);
    //connect(ui->LC2Button, &QPushButton::released,this,&hsm_full::adjustLC2);
    //connect(ui->LC2Button_2, &QPushButton::released,this,&hsm_full::adjustLC2Zero);
    //connect(ui->LC2SlopeButton, &QPushButton::released,this,&hsm_full::setLC2Slope);
    connect(ui->SwitchControlButton_2, &QPushButton::released,this,&hsm_full::switchControlType2);


    connect(ui->SetPlotScale, &QPushButton::released,this,&hsm_full::setPlotScale);
    connect(ui->SetLCInfo, &QPushButton::released,this,&hsm_full::setLCData);

    //need a function that sends command to act 1 and one that sends to act 2. Same with all the multiple actuator buttons
    //the sin wave functions will work just by having the dropdown because they are the same buttons
    //need to save a second column in the calibration file. Can make all the vectors 2D to make it easier to do inchToBit and bitToInch
    //

    //ui->ControlText->setText("Disp Control");
    ui->ControlText_2->setText("Disp Control");
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom,0,runaxlim);
    ui->qwtPlot->setAxisAutoScale(QwtPlot::yLeft,true);
    ui->qwtPlot_2->setAxisScale(QwtPlot::xBottom,0,runaxlimLoad);
    ui->qwtPlot_2->setAxisAutoScale(QwtPlot::yLeft,true);
    //serialWrite(1, 10, 128);


    while(EQ>>EQdata){
            EQ_h.push_back(EQdata/40);
            //x.push_back(0);
            //xd.push_back(0);
            //xdd.push_back(0);
    }

    //Xdata = {0,1,2,3,4,5,6,7,8,9,10};
    //Ydata = {0,1,2,3,4,5,6,7,8,9,10};




}

int hsm_full::update()
{
    if (running == 0){
    timer->stop();
    count=0;
    gcount=0;

    hsmOn = 1;
    //Initialize the hat
    setvbuf (stdout, NULL, _IONBF, 0); // needed to print to the command line
    xt = {{0},{0}};
    force = {{0},{0}};
    clearPlotVectors();
    xn = {{0, 0}};
    xd ={{0, 0}};
    xdd = {{0, 0}};
    xt = {{0, 0}};
    xdt = {{0, 0}};
    xddt = {{0, 0}};
    time_delay = {0};
    oof = {0};
    force = {0};
    intcount = 0;
    CommandVec = {0};
    DispVec = {0};
    CommandTime = {0};
    DispTime = {0};
    signalLoops= {};

//if (expi.dac_open() != 1){ // open the DAC spi channel
//    return(1); // if the SPI bus fails to open exit the program
//}

    struct sched_param param;
    struct sched_param param2;
    pthread_attr_t attr;
    pthread_attr_t attr2;
    pthread_t thread, thread2;
    int ret;
    int ret2;

    pthread_mutex_init(&race_mutex,NULL);
    pthread_mutex_init(&trigger_mutex,NULL);

    Py_Initialize();
    import_array();
    //Py_BEGIN_ALLOW_THREADS;
    //PyEval_InitThreads();
    PyObject *sysPath = PySys_GetObject((char*)"path");
    PyList_Append(sysPath,PyUnicode_FromString("/home/jim53/Desktop/RpiHSM/HSM_Full/HSM_Full"));
    pName = PyUnicode_FromString("Time_Integrator");
    pName2 =PyUnicode_FromString("testFunc");
    pModule = PyImport_Import(pName);
    pFunc = PyObject_GetAttrString(pModule, "InitializeAlphaOS");
    pFunc2 = PyObject_GetAttrString(pModule, "AlphaOS");
    int GM_dim[1] = {(int)GM.size()};
    double *GMmem = &GM[0];
    PyGM = PyArray_SimpleNewFromData(1,GM_dim,NPY_DOUBLE,(double*)GMmem);

    if (pModule != NULL) {
            printf("check3\n");
            InitIntArgs = PyTuple_New(3);
            PyTuple_SetItem(InitIntArgs,0,Model);
            PyTuple_SetItem(InitIntArgs,1,el);
            PyTuple_SetItem(InitIntArgs, 2, PyGM);
            printf("check4\n");
            if (pFunc && PyCallable_Check(pFunc)) {
                    x_next = PyObject_CallObject(pFunc, InitIntArgs);
                    if (Model != NULL) {
                        Model = PyTuple_GetItem(x_next,0);
                        printf("OK2\n");
                        xdd.push_back({PyFloat_AsDouble(PyTuple_GetItem(x_next,1))}); //Check this, needs to change to match the Const vel file
                        printf("OK3\n");

                        printf("OK");
                    }else {
                            PyErr_Print();
                    }
            }else {
                    if (PyErr_Occurred())
                    PyErr_Print();
                    fprintf(stderr, "Cannot find function %s\n", "InitializeAlphaOS");
            }
    }
    else {
            PyErr_Print();
            fprintf(stderr, "Failed to load %s\n", "Time_Integrator");
    }


    //Py_Initialize();
    d_prev[0] = 0;
    d_prev[1] = 0;
    d_prev[2] = 0;
    d_prev[3] = 0;

    //printf("%d\n",x.size());
    EQLen = EQ_h.size();

    // Lock memory
    if(mlockall(MCL_CURRENT|MCL_FUTURE) == -1) {
            printf("mlockall failed: %m\n");
            exit(-2);
    }

    // Initialize pthread attributes (default values)
    ret = pthread_attr_init(&attr);
    ret = pthread_attr_init(&attr2);
    if (ret) {
            printf("init pthread attributes failed\n");
            //goto out;
    }

    // Set a specific stack size
    ret = pthread_attr_setstacksize(&attr, 100000000);
    ret = pthread_attr_setstacksize(&attr2,100000000);
    if (ret) {
        printf("pthread setstacksize failed\n");
        //goto out;
    }

    // Set scheduler policy and priority of pthread
    ret = pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
    ret = pthread_attr_setschedpolicy(&attr2, SCHED_FIFO);
    if (ret) {
            printf("pthread setschedpolicy failed\n");
            //goto out;
    }
    param.sched_priority = 60;
    param2.sched_priority = 95;
    ret = pthread_attr_setschedparam(&attr, &param);
    ret = pthread_attr_setschedparam(&attr2, &param2);
    if (ret) {
            printf("pthread setschedparam failed\n");
            //goto out;
    }
    // Use scheduling parameters of attr
    ret = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    ret = pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);
    if (ret) {
            printf("pthread setinheritsched failed\n");
            //goto out;
    }
    gettimeofday(&tv, NULL);
    time_initial = tv.tv_usec;
    time_initial = tv.tv_sec + time_initial/1000000.0;
    // Create a pthread with specified attributes
    ret2 = pthread_create(&thread2, &attr2, Time_integrator, this);
    ret = pthread_create(&thread, &attr, simple_cyclic_task, this);
    if (ret) {
            printf("create pthread failed\n");
            //goto out;
    }

    if (ret2) {
            printf("create pthread2 failed\n");
            //goto out;
    }
    int i =0;
    ui->qwtPlot->setAxisAutoScale(QwtPlot::yLeft,true);
    //ui->qwtPlot->setAxisScale(QwtPlot::xBottom,0,axlim);
    //ui->qwtPlot->detachItems();
    running = 1;
    qDebug("Hello");
    runaxlim = 10;
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom,0,10);
    while(running == true){
        plotcount = plotcount+1;
        if (plotcount%500000 == 0){
            //readForce(0);
           pthread_mutex_lock(&race_mutex);
           this->updateLCD();
           pthread_mutex_unlock(&race_mutex);
        }
    }
    /*while(running == true){
        plotcount = plotcount+1;
        if (plotcount%1000000 == 0){
            //qDebug("Hello");
            gettimeofday(&tv1, NULL);
            time_in_mill2 = tv1.tv_usec;
            time_in_s2 = tv1.tv_sec + time_in_mill1/1000000.0-time_initial;

            if (setlim==1){

                Xdata = {};
                Ydata = {};
                XCommand = {};
                YCommand = {};
                ui->qwtPlot->setAxisScale(QwtPlot::xBottom,axlim,axlim+10);
                axlim = axlim+5;
                setlim = 0;
            }
           this->updatePlot();
            //qDebug("%d",j);


        }
    }*/
    printf("Running has changed\n");
    printf("%d\n",running);
    //QTimer *timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(updatePlot()));
    //timer->start(100);

    //sleep(1000);
    // Join the thread and wait until it is done
    ret = pthread_join(thread, NULL);
    if (ret){
            printf("join pthread failed: %m\n");
    }
    hsmOn = 0;
    clearPlotVectors();
    qDebug("Threads Closed");
    timer->start();
    gettimeofday(&runtv, NULL);
    runtime_in_mill = runtv.tv_usec;
    runtime_initial = runtv.tv_sec + runtime_in_mill/1000000.0;
    runaxlim = 10;
    saveModel();
    std::cout << "Done\n";
    }else{
        clearPlotVectors();
        //saveModel();
        running = 0;
        hsmOn = 0;
        runaxlim = 10;
        runaxlimLoad = 60;
        timer->start();
        ui->qwtPlot->setAxisAutoScale(QwtPlot::xBottom,true);
        ui->qwtPlot->setAxisAutoScale(QwtPlot::yLeft,true);
        ui->qwtPlot->setAxisScale(QwtPlot::xBottom,0,runaxlim);
        ui->qwtPlot_2->setAxisScale(QwtPlot::xBottom,0,runaxlimLoad);
    }
}



void hsm_full::updatePlot()
{
    index++;
    //qDebug("tick %f",dispCommand);


    curve1->setPen(QColor(Qt::red));
    curve3->setPen(QColor(Qt::green));
    curve4->setPen(QColor(Qt::red));
    curve5->setPen(QColor(Qt::green));
    curve10->setPen(QColor(Qt::blue));
    curve12->setPen(QColor(Qt::blue));

    if (legendPlotted == false) {
        QwtPlotLegendItem * legendItem1 = new QwtPlotLegendItem;
        QwtPlotLegendItem * legendItem2 = new QwtPlotLegendItem;
        legendItem1->attach(ui->qwtPlot);
        legendItem2->attach(ui->qwtPlot_2);
        legendPlotted = true;
    }
    //Xdata.removeFirst();
    //Ydata.removeFirst();

    //ui->qwtPlot->detachItems();
    //pthread_mutex_lock(&race_mutex);
    curve1->setSamples(Xdata,Ydata);
    //pthread_mutex_unlock(&race_mutex);
    curve1->attach(ui->qwtPlot);
    curve4->setSamples(HystDisp1,loadCellData1);
    curve4->attach(ui->qwtPlot_2);

    if(CT1 == 0){
       //pthread_mutex_lock(&race_mutex);
       curve2->setSamples(XCommand,YCommand);
       //pthread_mutex_unlock(&race_mutex);
       curve2->attach(ui->qwtPlot);

    }if(CT2 == 0) {
       curve10->setSamples(XCommandAct2,YCommandAct2);
       curve10->attach(ui->qwtPlot);
    }

    if(CT1 == 1) {
       curve11->setSamples(XForceCommand,YForceCommand);
       curve11->attach(ui->qwtPlot_2);
    }
    if(CT2 == 1) {
       curve12->setSamples(XForceCommandAct2,YForceCommandAct2);
       curve12->attach(ui->qwtPlot_2);
    }

    curve3->setSamples(XdataAct2,YdataAct2);
    curve3->attach(ui->qwtPlot);
    curve5->setSamples(HystDisp2,loadCellData2);
    curve5->attach(ui->qwtPlot_2);

    ui->qwtPlot->replot();
    ui->qwtPlot_2->replot();
}

void hsm_full::stiffTest()
{
    setvbuf (stdout, NULL, _IONBF, 0);
    stiffOn = 1;
    clearPlotVectors();
    force = {0};
    CommandVec = {0};
    DispVec = {0};
    CommandTime = {0};
    DispTime = {0};
    int Amax;
    int Amin;
    int Astable;

    A = 0;

    int startCommand;

    int channel = ui->selectAct->value();
    if (channel == 1) {
        startCommand = dispCommand;
    }
    if (channel == 2) {
        startCommand = dispCommand2;
    }
    Amax =  75;
    Amin = - 75;
    Astable = 0;

       //Edit to choose Actuator
       //WRITING TO DAC
       printf("Working\n");
       while(A<=Amax){
           A = A+1;
           qDebug("%d",index);
           readForce(channel - 1);
           //change to select actuator
           std::cout << runtime_in_s << "\n";
           stiffdispvec.push_back((double) startCommand + receivedToInches(channel,A));
           data_to_send = (uint16_t) inchesToBits(channel, startCommand) + A;
           serialWrite(channel,0,data_to_send); //I will need to think about how to incorporate the changes in span and zeros to the write command

           if (channel == 1) {
               dispCommand =((double) startCommand + receivedToInches(channel,A));
               stiffnessvec.push_back(received_Force);
           } if (channel == 2) {
               dispCommand2 = ((double) startCommand + receivedToInches(channel,A));
               stiffnessvec.push_back(received_Force2);
           }
           this->updateLCD();
           usleep(50000);
       }
       while(A>=Amin){
           A = A-1;
           qDebug("%d",index);
           readForce(channel - 1);
           if (channel == 1) {
               dispCommand =((double) startCommand + receivedToInches(channel,A));
               stiffnessvec.push_back(received_Force);
           } if (channel == 2) {
               dispCommand2 = ((double) startCommand + receivedToInches(channel,A));
               stiffnessvec.push_back(received_Force2);
           }
           stiffdispvec.push_back((double) startCommand + receivedToInches(channel,A));

           data_to_send = (uint16_t) inchesToBits(channel, startCommand) + A;
           serialWrite(channel,0,data_to_send);
           this->updatePlot();
           usleep(50000);
           this->updateLCD();
       }
       while(A<=Astable){
           A = A+1;
           qDebug("%d",index);
           readForce(channel - 1);
           if (channel == 1) {
               dispCommand =((double) startCommand + receivedToInches(channel,A));
               stiffnessvec.push_back(received_Force);
           } if (channel == 2) {
               dispCommand2 = ((double) startCommand + receivedToInches(channel,A));
               stiffnessvec.push_back(received_Force2);
           }
           stiffdispvec.push_back((double) startCommand + receivedToInches(channel,A));

           data_to_send = (uint16_t) inchesToBits(channel, startCommand) + A;
           serialWrite(channel,0,data_to_send);
           this->updateLCD();
           usleep(50000);
       }
       stiffdispvec =  {stiffdispvec.begin() + (Amax-Astable), stiffdispvec.end() - (Amax-Astable)};
       stiffnessvec =  {stiffnessvec.begin() + (Amax-Astable), stiffnessvec.end() - (Amax-Astable)};
       double sumX = 0;
       double sumX2 = 0;
       double sumY = 0;
       double sumXY = 0;
       int n = stiffdispvec.size();
       printf("%d\n",stiffdispvec.size());
       printf("%d\n",stiffnessvec.size());
       for (int i=0;i<n;i++){
           sumX = sumX + stiffdispvec[i];
           sumX2 = sumX2 + stiffdispvec[i]*stiffdispvec[i];
           sumY = sumY+stiffnessvec[i];
           sumXY = sumXY + stiffnessvec[i]*stiffdispvec[i];
       }
       double hybStiff = ((double)n*sumXY-sumX*sumY)/((double)n*sumX2-sumX*sumX);

       //adjust to make hybStiff a vector and make this display stiffness for proper actuator
       printf("%f\n",hybStiff);
       if (channel == 1) {
            ui->Stiffness->display(hybStiff);
       }
       if (channel == 2) {
            ui->Stiffness_2->display(hybStiff);
       }
       CommandVec = hsm_full::YCommand.toStdVector();
       DispVec = hsm_full::Ydata.toStdVector();
       CommandTime = hsm_full::XCommand.toStdVector();
       DispTime = hsm_full::Xdata.toStdVector();
       stiffOn = 0;
       printf("Done\n");
}

void hsm_full::save()
{

    setvbuf (stdout, NULL, _IONBF, 0);
    intDisp.open("SaveData/IntegratorDisp.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Integrator Disp\n");
    for(int i = 0 ; i<xn.size()-5; i++){
            std::cout << i << "\n";
            intDisp << xn[i][0] << "," << xn[i][1] << "\n";
            //printf("%d\n",i);
    }
    intDisp.close();

    intForceResponse.open("SaveData/IntegratorForce.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving force\n");
    for(int i = 0 ; i<force.size()+1; i++){
            intForceResponse << force[i] << "\n";
            //printf("%d\n",i);
    }
    intForceResponse.close();

    sentCom.open("SaveData/Command.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Commands x\n");
    for(int i = 0 ; i<CommandVec.size()+1; i++){
            sentCom << CommandVec[i] << "\n";
            //printf("%d\n",i);
    }
    sentCom.close();

    sentCom2.open("SaveData/Command2.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Commands x\n");
    for(int i = 0 ; i<CommandVecAct2.size()-5; i++){
            sentCom2 << CommandVecAct2[i] << "\n";
            //printf("%d\n",i);
    }
    sentCom2.close();

    recDisp.open("SaveData/recDisp.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Recieved Disp x\n");
    for(int i = 0 ; i<DispVec.size()-5; i++){
            recDisp << DispVec[i] << "\n";
            //printf("%d\n",i);
    }
    recDisp.close();

    recDisp2.open("SaveData/recDisp2.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Recieved Disp 2 x\n");
    for(int i = 0 ; i<DispVecAct2.size()-5; i++){
            recDisp2 << DispVecAct2[i] << "\n";
            //printf("%d\n",i);
    }
    recDisp2.close();


    CommandT.open("SaveData/CommandT.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Command Time x\n");
    for(int i = 0 ; i<CommandTime.size()-5; i++){
            CommandT << CommandTime[i] << "\n";
            //printf("%d\n",i);
    }
    CommandT.close();

    CommandT2.open("SaveData/CommandT2.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Command Time x\n");
    for(int i = 0 ; i<CommandTimeAct2.size()-5; i++){
            CommandT2 << CommandTimeAct2[i] << "\n";
            //printf("%d\n",i);
    }
    CommandT2.close();

    DispT.open("SaveData/DispT.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Recieved Disp Time x\n");
    for(int i = 0 ; i<DispTime.size()-5; i++){
            DispT << DispTime[i] << "\n";
            //printf("%d\n",i);
    }
    DispT.close();

    DispT2.open("SaveData/DispT2.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Recieved Disp Time 2 x\n");
    for(int i = 0 ; i<DispTimeAct2.size()-5; i++){
            DispT2 << DispTimeAct2[i] << "\n";
            //printf("%d\n",i);
    }
    DispT2.close();

    ForceResponse.open("SaveData/recForce.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving received Force Vector");
    for(int i=0; i < ForceVec.size()-1;i++) {
        ForceResponse << ForceVec[i] << "\n";
    }
    ForceResponse.close();

    ForceResponse2.open("SaveData/recForce2.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving received Force Vector");
    for(int i=0; i < ForceVecAct2.size()-1;i++) {
        ForceResponse2 << ForceVecAct2[i] << "\n";
    }
    ForceResponse2.close();


    runningCommand.open("SaveData/runningCommand.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Running Commands x\n");
    for(int i = 0 ; i<runCommand.size()-1; i++){
            runningCommand << runCommand[i] << "\n";
            //printf("%d\n",i);
    }
    runningCommand.close();

    runningCommand2.open("SaveData/runningCommand2.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Running Commands x\n");
    for(int i = 0 ; i<runCommand2.size()-5; i++){
            runningCommand2 << runCommand2[i] << "\n";
            //printf("%d\n",i);
    }
    runningCommand2.close();

    runningForceCommand.open("SaveData/runningForceCommand.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Running Commands x\n");
    for(int i = 0 ; i<runForceCommand.size()-1; i++){
            runningForceCommand << runForceCommand[i] << "\n";
            //printf("%d\n",i);
    }
    runningForceCommand.close();

    runningForceCommand2.open("SaveData/runningForceCommand2.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Running Commands x\n");
    for(int i = 0 ; i<runForceCommand2.size()-1; i++){
            runningForceCommand2 << runForceCommand2[i] << "\n";
            //printf("%d\n",i);
    }
    runningForceCommand2.close();

    runningTime.open("SaveData/runningTime.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Running Time x\n");
    for(int i = 0 ; i<runTime.size()-1; i++){
            runningTime << runTime[i] << "\n";
            //printf("%d\n",i);
    }
    runningTime.close();

    runningTime2.open("SaveData/runningTime2.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Running Time x\n");
    for(int i = 0 ; i<runTime2.size()-1; i++){
            runningTime2 << runTime2[i] << "\n";
            //printf("%d\n",i);
    }
    runningTime2.close();

    runningFeedback.open("SaveData/runningFeedback.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Running Disp Feedback x\n");
    for(int i = 0 ; i<runFeedback.size()-1; i++){
            runningFeedback << runFeedback[i] << "\n";
            //printf("%d\n",i);
    }
    runningFeedback.close();

    runningFeedback2.open("SaveData/runningFeedback2.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Running Disp Feedback x\n");
    for(int i = 0 ; i<runFeedback2.size()-1; i++){
            runningFeedback2 << runFeedback2[i] << "\n";
            //printf("%d\n",i);
    }
    runningFeedback2.close();

    if (xd[0].size()>1){
        integratorIndex.open("SaveData/integratorIndex.txt",std::ofstream::out | std::ofstream::trunc);
        printf("Saving Integrator Index %d\n",intIndex.size());
        for(int i = 0 ; i<intIndex.size()-1; i++){
                integratorIndex << intIndex[i] << "\n";
                //printf("%d\n",i);
        }
        integratorIndex.close();


        calcVelocity.open("SaveData/calcVelocity.txt",std::ofstream::out | std::ofstream::trunc);
        printf("Saving Calculated Velocity\n");
                for(int i = 0 ; i<xd[0].size()-1; i++){
                        calcVelocity << xd[0][i] << "," << xd[1][i] << "\n";
                        //printf("%d\n",i);
                }
                calcVelocity.close();

        calcAcc.open("SaveData/calcAcc.txt",std::ofstream::out | std::ofstream::trunc);
        printf("Saving Calculated Acceleration\n");
        for(int i = 0 ; i<xdd[0].size()-1; i++){
                calcAcc << xdd[0][i] << "," << xdd[1][i] << "\n";
                //printf("%d\n",i);
        }
        calcAcc.close();
    }

    qDebug("%d",sinCommand.size());

    SinCommandFile.open("SaveData/SinCommand.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Sin Commands\n");
    for(int i = 0 ; i<sinCommand.size(); i++){
            SinCommandFile << sinCommand[i] << "\n";
            //printf("%d\n",i);
    }
    SinCommandFile.close();

    SinCommandFile2.open("SaveData/SinCommand2.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Sin Commands\n");
    for(int i = 0 ; i<sinCommand2.size()+1; i++){
            SinCommandFile2 << sinCommand2[i] << "\n";
            //printf("%d\n",i);
    }
    SinCommandFile2.close();

    SinResponseFile.open("SaveData/SinResponse.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Sin Disp Response\n");
    for(int i = 0 ; i<sinResponse.size()+1; i++){
            SinResponseFile << sinResponse[i] << "\n";
            //printf("%d\n",i);
    }
    SinResponseFile.close();

    SinResponseFile2.open("SaveData/SinResponse2.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Sin Disp Response\n");
    for(int i = 0 ; i<sinResponse2.size()+1; i++){
            SinResponseFile2 << sinResponse2[i] << "\n";
            //printf("%d\n",i);
    }
    SinResponseFile2.close();

    SinForceFile.open("SaveData/SinForce.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Sin Force Response\n");
    for(int i = 0 ; i<sinForce.size()+1; i++){
            SinForceFile << sinForce[i] << "\n";
            //printf("%d\n",i);
    }
    SinForceFile.close();

    SinForceFile2.open("SaveData/SinForce2.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Sin Force Response\n");
    for(int i = 0 ; i<sinForce2.size()+1; i++){
            SinForceFile2 << sinForce2[i] << "\n";
            //printf("%d\n",i);
    }
    SinForceFile2.close();

    SinTimeFile.open("SaveData/SinTime.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Sin Time\n");
    for(int i = 0 ; i<sinTime.size()+1; i++){
            SinTimeFile << sinTime[i] << "\n";
            //printf("%d\n",i);
    }
    SinTimeFile.close();

    SinTimeFile2.open("SaveData/SinTime2.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Sin Time\n");
    for(int i = 0 ; i<sinTime2.size()+1; i++){
            SinTimeFile2 << sinTime2[i] << "\n";
            //printf("%d\n",i);
    }
    SinTimeFile2.close();


    if(logcontrolloops == 1){
    controlLoops.open("SaveData/controlLoops.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving control Loops x\n");
            for(int i = 0 ; i<loops.size()+1; i++){
                    controlLoops << loops[i] << "\n";
                    //printf("%d\n",i);
            }
            controlLoops.close();
    signalLoopTime.open("SaveData/signalLoopTime.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Signal Loop Time x\n");
            for(int i = 0 ; i<signalLoops.size()+1; i++){
                    signalLoopTime << signalLoops[i] << "\n";
            }
            signalLoopTime.close();
}
    printf("Done\n");
}

hsm_full::~hsm_full()
{
    delete ui;
}







// Actuator 1 Button Commands
void hsm_full::sendCommand(){
    setvbuf (stdout, NULL, _IONBF, 0);
    //printf("%f",dispCommand);
    command = 0;
    std::cout << CT1 << "\n";
    //data_to_send = (uint16_t) ((dispCommand + newSpan / 2)  * spanSlope + spanIntercept);
    if (CT1 == 0) {
        dispCommand = ui->CommandInput->value();
        data_to_send = (uint16_t) inchesToBits(1,dispCommand);
        std::cout << data_to_send << "\n";
        std::cout << receivedToInches(1,data_to_send) << "\n";
        std::cout << spanSlope << "   " << spanIntercept << "  " << zeroVol << "   " << diffGain << "\n";
        std::cout << origSlopes[4] << "   " << origIntercepts[4] << "\n";
        serialWrite(1,command,data_to_send);
    } else if (CT1 ==1) {
        forceCommand = ui->CommandInput->value();
        double double_to_send = forceCommand / forceSlope + zeroForce;
        sendDouble(1,command,double_to_send);
        std::cout <<"Sending force value" <<  double_to_send << "\n";
        //data_to_send = (uint16_t) forceCommand;
        //serialWrite(1,command,data_to_send);
    }
}

void hsm_full::sendPID(){
    setvbuf (stdout, NULL, _IONBF, 0);
    PCommand = ui->PInputDisp->value();
    ui->PInputDisp->setValue(PCommand);
    ICommand = ui->IInputDisp->value();
    ui->IInputDisp->setValue(ICommand);
    DCommand = ui->DInputDisp->value();
    ui->DInputDisp->setValue(DCommand);
    command = 2;
    data_to_send = std::min(4095.0,round(PCommand/Pmax*4095));
    serialWrite(1,command,data_to_send);
    data_to_send = std::min(4095.0,round(ICommand/Imax*4095));
    command = 2;
    serialWrite(1,command,data_to_send);
    command = 2;
    data_to_send = std::min(4095.0,round(DCommand/Dmax*4095));
    serialWrite(1,command,data_to_send);
}

void hsm_full::sendPIDForce(){
    setvbuf (stdout, NULL, _IONBF, 0);
    PCommand = ui->PInputForce->value();
    ui->PInputForce->setValue(PCommand);
    ICommand = ui->IInputForce->value();
    ui->IInputForce->setValue(ICommand);
    DCommand = ui->DInputForce->value();
    ui->DInputForce->setValue(DCommand);
    command = 3;
    data_to_send = std::min(4095.0,round(PCommand/Pmax*4095));
    serialWrite(1,command,data_to_send);
    data_to_send = std::min(4095.0,round(ICommand/Imax*4095));
    command = 3;
    serialWrite(1,command,data_to_send);
    command = 3;
    data_to_send = std::min(4095.0,round(DCommand/Dmax*4095));
    serialWrite(1,command,data_to_send);
}

/*void hsm_full::sendI(){
    setvbuf (stdout, NULL, _IONBF, 0);
    ICommand = ui->IInput->value();
    ui->IDisp->display(ICommand);
    printf("%f",ICommand);
    command = 3;
    data_to_send = std::min(4095.0,round(ICommand/Imax*4095));
    serialWrite(1,command,data_to_send);
}

void hsm_full::sendD(){
    setvbuf (stdout, NULL, _IONBF, 0);
    DCommand = ui->DInput->value();
    ui->DDisp->display(DCommand);
    printf("%f",DCommand);
    command = 4;
    data_to_send = std::min(4095.0,round(DCommand/Dmax*4095));
    serialWrite(1,command,data_to_send);
}*/

void hsm_full::sliderCommand(){
    /*setvbuf (stdout, NULL, _IONBF, 0);
    if (sliderActive == 1) {
        slideCommand = ui->horizontalSlider->value();
        printf("%f",slideCommand);
        command = 0;
        command = command<<12;
        data_to_send = slideCommand;
        if (microcont == 1){
            data_to_send = data_to_send | command;
            wiringPiI2CWriteReg16(fd,0x00,data_to_send);
        }else{
            data_to_send = std::min(3300.0,round(3.22*slideCommand+(ogZero-1650)));
            //expi.dac_set_raw(data_to_send,2, 2);
        }
    }*/
}

void hsm_full::activateButton(){
    setvbuf (stdout, NULL, _IONBF, 0);
    if (sliderActive == 0){
        sliderActive = 1;
        ui->SliderButton->setText("De-Activate");
    }
    else if (sliderActive == 1){
        sliderActive = 0;
        ui->SliderButton->setText("Activate");
    }
}

void hsm_full::pressSpanButton() {
    double targetSpan = ui -> SpanInput -> value();
    double targetZero = ui -> approxZero -> value();
    spanCommand(1,targetSpan, targetZero);
}

void hsm_full::setZero(){
    dispCommand = 0;
    zeroPoint = serialRead(1, 1, 0);
    zeroPoint_in = receivedToInches(1,zeroPoint) + zeroPoint_in;
    ui->Offset->display(zeroPoint_in);
    /*command = 5;
    command = command<<12;
    data_to_send = round((zeroPoint_in)*4095.0/(2*span))+ogZero;
    zeroPoint = data_to_send;
    data_to_send = data_to_send | command;
    wiringPiI2CWriteReg16(fd,0x00,data_to_send);
    qDebug("%d",zeroPoint);*/
}

void hsm_full::calForce(){
    /*readForce(0);
    zeroForce = serialRead(1,1,1);
    saveForceSlopes();*/
    forceReceived[0] = serialRead(1,1,1);
    //std::cout << serialRead(1,1,1);
    forceReceived[1] = serialRead(1,1,1);
    forceReceived[2] = serialRead(1,1,1);

    forceReceived[0] = forceReceived[0] << 24;
    forceReceived[1] = forceReceived[1] << 12;

    forceReceived[0] |= forceReceived[1];
    forceReceived[0] |= forceReceived[2];
    zeroForce = (double) (long) forceReceived[0];
    saveLCData();
    qDebug("%f",zeroForce);
}


void hsm_full::startControl(){
    if (controller == 0){
        //ui->StartControl->setText("Stop Controller");
        controller = 1;
        dispCommand = received_Disp;
    }else{
        //ui->StartControl->setText("Start Controller");
        controller = 0;

    }
    serialWrite(1,9,0);
}

void hsm_full::turnOnLow1() {
    if (actOneLow){
        actOneLow = 0;
        startControl();
        digitalWrite(actOneLowPin, actOneLow);
        ui->Act1LowOn->setText("Off");
        if (actOneHigh) {
            actOneHigh = 0;
            ui->Act1HighOn->setText("Off");
            digitalWrite(actOneHighPin, actOneHigh);
        }
    }else{
        actOneLow = 1;
        ui->Act1LowOn->setText("On");
        startControl();
        digitalWrite(actOneLowPin, actOneLow);
    }
}

void hsm_full::turnOnHigh1() {
    if (actOneLow){
        if (actOneHigh){
            actOneHigh = 0;
            ui->Act1HighOn->setText("Off");
            digitalWrite(actOneHighPin, actOneHigh);
        }else{
            actOneHigh = 1;
            ui->Act1HighOn->setText("On");
            digitalWrite(actOneHighPin, actOneHigh);
        }
    }
}

/*void hsm_full::adjustLC1() {
    LC1Offset = (int) ui->LC1Int->value();
    serialWrite(3,1,LC1Offset);
    saveForceSlopes();
    //calLoadCell(0,ui->LC1Int->value());
}

void hsm_full::adjustLC1Zero() {
    LC1Zero = (int) ui->LC1Int_2->value();
    serialWrite(3,3,LC1Zero);
    saveForceSlopes();
    //calLoadCell(0,ui->LC1Int->value());
}

void hsm_full::setLC1Slope() {
    forceSlope = ui->LC1SlopeInput->value();
    saveForceSlopes();
}
*/
void hsm_full::switchControlType() {
    long testLong = (long) ui->CommandInput->value();
    if (CT1 == 0) {
        if((ui->minDispInput->value() != ui->maxDispInput->value()) and (received_Disp > ui->minDispInput->value() and received_Disp < ui->maxDispInput->value())){
            CT1 = 1;
            ui->SwitchControlButton->setText("Switch to Disp Control");
            ui->ControlText->setText("Force Control");
            std::cout << "Min Disp: " << ui->minDispInput->value() << "\n";
            std::cout << "Max Disp: " << ui->maxDispInput->value() << "\n";
            serialWrite(1,5,inchesToBits(1, ui->minDispInput->value()));
            serialWrite(1,5,inchesToBits(1, ui->maxDispInput->value()));
            std::cout << "Max Force: " << ui->Act1MaxLC->value() << "\n";
            std::cout << "Force Slope: " << ui->Act1LCSlope->value() << "\n";
            sendDouble(1,5,(double) ui->Act1MaxLC->value());
            sendDouble(1,5,(double) ui->Act1LCSlope->value());
        } else {
            std::cout << "Error, Force control not set, check min maxes\n";
        }
    } else if (CT1 == 1){
        CT1 = 0;
        ui->SwitchControlButton->setText("Switch to Force Control");
        ui->ControlText->setText("Disp Control");
        serialWrite(1,5,0);
    }

}

void hsm_full::useFirstActuator() {
    if (firstActuatorOn) {
        firstActuatorOn = false;
        ui->TrueForce->setEnabled(false);
        ui->label_37->setEnabled(false);
        ui->label_38->setEnabled(false);
        ui->Act1HighOn->setEnabled(false);
        ui->approxZero->setEnabled(false);
        ui->Act1LowOn->setEnabled(false);
        ui->ActOneHighButton->setEnabled(false);
        ui->ActOneLowButton->setEnabled(false);
        ui->Force->setEnabled(false);
        ui->SpanButton->setEnabled(false);
        ui->CommandButton->setEnabled(false);
        ui->CommandInput->setEnabled(false);
        ui->CommandNum->setEnabled(false);
        ui->CurPos->setEnabled(false);
        ui->CurSpan->setEnabled(false);
        ui->SliderButton->setEnabled(false);
        ui->SpanInput->setEnabled(false);
        ui->Offset->setEnabled(false);
        ui->zeroButton->setEnabled(false);
        ui->Stiffness->setEnabled(false);
        ui->fZeroButton->setEnabled(false);
        ui->horizontalSlider->setEnabled(false);
        ui->Stiffness->setEnabled(false);
        ui->label_2->setEnabled(false);
        ui->label_3->setEnabled(false);
        ui->label_6->setEnabled(false);
        ui->label_7->setEnabled(false);
        ui->label_8->setEnabled(false);
        ui->label_9->setEnabled(false);
        ui->label_24->setEnabled(false);
        ui->label_25->setEnabled(false);
        ui->label_26->setEnabled(false);
        ui->label_10->setEnabled(false);
        //ui->LC1Int->setEnabled(false);
        //ui->LC1Button->setEnabled(false);
        ui->DispPID->setEnabled(false);
        ui->PInputDisp->setEnabled(false);
        ui->IInputDisp->setEnabled(false);
        ui->DInputDisp->setEnabled(false);
        ui->PInputForce->setEnabled(false);
        ui->IInputForce->setEnabled(false);
        ui->DInputForce->setEnabled(false);
        ui->ForcePID->setEnabled(false);
        ui->minDispInput->setEnabled(false);
        ui->maxDispInput->setEnabled(false);
        ui->label_27->setEnabled(false);
        ui->label_28->setEnabled(false);
        ui->label_29->setEnabled(false);
        ui->label_33->setEnabled(false);
        ui->label_30->setEnabled(false);
        ui->label_31->setEnabled(false);
        ui->label_32->setEnabled(false);
        ui->ControlText->setEnabled(false);
        ui->SwitchControlButton->setEnabled(false);
        ui->label_22->setEnabled(false);
        /*ui->LC1Button->setEnabled(false);
        ui->LC1Button_2->setEnabled(false);
        ui->LC1Int->setEnabled(false);
        ui->LC1Int_2->setEnabled(false);
        ui->LC1SlopeInput->setEnabled(false);
        ui->LC1SlopeButton->setEnabled(false);*/
        ui->label->setEnabled(false);
        ui->label_5->setEnabled(false);
        ui->label_4->setEnabled(false);

    } else {
        SerialDisp = serialRead(1, 1, 0);
        received_Disp = receivedToInches(1,SerialDisp);
        firstActuatorOn = true;
        dispCommand = received_Disp;
        ui->CommandInput->setValue(dispCommand);
        ui->TrueForce->setEnabled(true);
        ui->label_37->setEnabled(true);
        ui->label_38->setEnabled(true);
        ui->Act1HighOn->setEnabled(true);
        ui->approxZero->setEnabled(true);
        ui->Act1LowOn->setEnabled(true);
        ui->ActOneHighButton->setEnabled(true);
        ui->ActOneLowButton->setEnabled(true);
        ui->Force->setEnabled(true);
        ui->SpanButton->setEnabled(true);
        ui->CommandButton->setEnabled(true);
        ui->CommandInput->setEnabled(true);
        ui->CommandNum->setEnabled(true);
        ui->CurPos->setEnabled(true);
        ui->CurSpan->setEnabled(true);
        ui->SliderButton->setEnabled(true);
        ui->SpanInput->setEnabled(true);
        ui->Offset->setEnabled(true);
        ui->zeroButton->setEnabled(true);
        ui->Stiffness->setEnabled(true);
        ui->fZeroButton->setEnabled(true);
        ui->horizontalSlider->setEnabled(true);
        ui->Stiffness->setEnabled(true);
        ui->label_2->setEnabled(true);
        ui->label_3->setEnabled(true);
        ui->label_6->setEnabled(true);
        ui->label_7->setEnabled(true);
        ui->label_8->setEnabled(true);
        ui->label_9->setEnabled(true);
        ui->label_24->setEnabled(true);
        ui->label_25->setEnabled(true);
        ui->label_26->setEnabled(true);
        ui->label_10->setEnabled(true);
        /*ui->LC1Int->setEnabled(true);
        ui->LC1Button->setEnabled(true);*/
        ui->DispPID->setEnabled(true);
        ui->PInputDisp->setEnabled(true);
        ui->IInputDisp->setEnabled(true);
        ui->DInputDisp->setEnabled(true);
        ui->PInputForce->setEnabled(true);
        ui->IInputForce->setEnabled(true);
        ui->DInputForce->setEnabled(true);
        ui->ForcePID->setEnabled(true);
        ui->minDispInput->setEnabled(true);
        ui->maxDispInput->setEnabled(true);
        ui->label_27->setEnabled(true);
        ui->label_28->setEnabled(true);
        ui->label_29->setEnabled(true);
        ui->label_33->setEnabled(true);
        ui->label_30->setEnabled(true);
        ui->label_31->setEnabled(true);
        ui->label_32->setEnabled(true);
        ui->ControlText->setEnabled(true);
        ui->SwitchControlButton->setEnabled(true);
        ui->label_22->setEnabled(true);
        /*ui->LC1Button->setEnabled(true);
        ui->LC1Button_2->setEnabled(true);
        ui->LC1Int->setEnabled(true);
        ui->LC1Int_2->setEnabled(true);
        ui->LC1SlopeInput->setEnabled(true);
        ui->LC1SlopeButton->setEnabled(true);*/
        ui->label->setEnabled(true);
        ui->label_5->setEnabled(true);
        ui->label_4->setEnabled(true);
    }
}

//These are the functions for the Second Actuator Buttons
//If there is time, may be useful to make an actuator class. The actuators would have all these functions, and a class variable that specifies the actuator's pins.
//By far the best way to implement this but I am low on time.
void hsm_full::useSecondActuator() {
    if (secondActuatorOn) {
        secondActuatorOn = false;
        ui->TrueForce_2->setEnabled(false);
        ui->label_39->setEnabled(false);
        ui->label_40->setEnabled(false);
        ui->Act2HighOn->setEnabled(false);
        ui->Act2LowOn->setEnabled(false);
        ui->ActTwoHighButton->setEnabled(false);
        ui->ActTwoLowButton->setEnabled(false);
        ui->Force_2->setEnabled(false);
        ui->SpanButton_2->setEnabled(false);
        ui->CommandButton_2->setEnabled(false);
        ui->CommandInput_2->setEnabled(false);
        ui->CommandNum_2->setEnabled(false);
        ui->CurPos_2->setEnabled(false);
        ui->CurSpan_2->setEnabled(false);
        ui->SliderButton_2->setEnabled(false);
        ui->SpanInput_2->setEnabled(false);
        ui->Offset_2->setEnabled(false);
        ui->zeroButton_2->setEnabled(false);
        ui->Stiffness_2->setEnabled(false);
        ui->fZeroButton_2->setEnabled(false);
        ui->horizontalSlider_2->setEnabled(false);
        ui->Stiffness_2->setEnabled(false);
        ui->label_11->setEnabled(false);
        ui->label_12->setEnabled(false);
        ui->label_13->setEnabled(false);
        ui->label_14->setEnabled(false);
        ui->label_15->setEnabled(false);
        ui->label_16->setEnabled(false);
        ui->label_17->setEnabled(false);
        ui->label_23->setEnabled(false);
        /*ui->LC2Int->setEnabled(false);
        ui->LC2Button->setEnabled(false);*/
        ui->DispPID2->setEnabled(false);
        ui->PInputDisp2->setEnabled(false);
        ui->IInputDisp2->setEnabled(false);
        ui->DInputDisp2->setEnabled(false);
        ui->PInputForce2->setEnabled(false);
        ui->IInputForce2->setEnabled(false);
        ui->DInputForce2->setEnabled(false);
        ui->ForcePID_2->setEnabled(false);
        ui->label_18->setEnabled(false);
        ui->label_19->setEnabled(false);
        ui->label_20->setEnabled(false);
        ui->label_34->setEnabled(false);
        ui->label_35->setEnabled(false);
        ui->label_36->setEnabled(false);
        ui->label_49->setEnabled(false);
        ui->label_50->setEnabled(false);
        ui->label_51->setEnabled(false);
        ui->label_52->setEnabled(false);
        ui->ControlText_2->setEnabled(false);
        ui->SwitchControlButton_2->setEnabled(false);
        /*ui->LC2Button->setEnabled(false);
        ui->LC2Button_2->setEnabled(false);
        ui->LC2Int->setEnabled(false);
        ui->LC2Int_2->setEnabled(false);
        ui->LC2SlopeInput->setEnabled(false);
        ui->LC2SlopeButton->setEnabled(false);*/
        ui->minDispInput_2->setEnabled(false);
        ui->maxDispInput_2->setEnabled(false);

    } else {
        SerialDisp = serialRead(2, 1, 0);
        received_Disp2 = receivedToInches(2,SerialDisp);
        dispCommand2 = received_Disp2;
        secondActuatorOn = true;
        ui->CommandInput_2->setValue(dispCommand2);
        ui->TrueForce_2->setEnabled(true);
        ui->label_39->setEnabled(true);
        ui->label_40->setEnabled(true);
        ui->Act2HighOn->setEnabled(true);
        ui->Act2LowOn->setEnabled(true);
        ui->ActTwoHighButton->setEnabled(true);
        ui->ActTwoLowButton->setEnabled(true);
        ui->Force_2->setEnabled(true);
        ui->SpanButton_2->setEnabled(true);
        ui->CommandButton_2->setEnabled(true);
        ui->CommandInput_2->setEnabled(true);
        ui->CommandNum_2->setEnabled(true);
        ui->CurPos_2->setEnabled(true);
        ui->CurSpan_2->setEnabled(true);
        ui->SliderButton_2->setEnabled(true);
        ui->SpanInput_2->setEnabled(true);
        ui->Offset_2->setEnabled(true);
        ui->zeroButton_2->setEnabled(true);
        ui->Stiffness_2->setEnabled(true);
        ui->fZeroButton_2->setEnabled(true);
        ui->horizontalSlider_2->setEnabled(true);
        ui->Stiffness_2->setEnabled(true);
        ui->label_11->setEnabled(true);
        ui->label_12->setEnabled(true);
        ui->label_13->setEnabled(true);
        ui->label_14->setEnabled(true);
        ui->label_15->setEnabled(true);
        ui->label_16->setEnabled(true);
        ui->label_17->setEnabled(true);
        ui->label_23->setEnabled(true);
        /*ui->LC2Int->setEnabled(true);
        ui->LC2Button->setEnabled(true);*/
        ui->DispPID2->setEnabled(true);
        ui->PInputDisp2->setEnabled(true);
        ui->IInputDisp2->setEnabled(true);
        ui->DInputDisp2->setEnabled(true);
        ui->PInputForce2->setEnabled(true);
        ui->IInputForce2->setEnabled(true);
        ui->DInputForce2->setEnabled(true);
        ui->ForcePID_2->setEnabled(true);
        ui->label_18->setEnabled(true);
        ui->label_19->setEnabled(true);
        ui->label_20->setEnabled(true);
        ui->label_34->setEnabled(true);
        ui->label_35->setEnabled(true);
        ui->label_36->setEnabled(true);
        ui->label_49->setEnabled(true);
        ui->label_50->setEnabled(true);
        ui->label_51->setEnabled(true);
        ui->label_52->setEnabled(true);
        ui->ControlText_2->setEnabled(true);
        ui->SwitchControlButton_2->setEnabled(true);
        /*ui->LC2Button->setEnabled(true);
        ui->LC2Button_2->setEnabled(true);
        ui->LC2Int->setEnabled(true);
        ui->LC2Int_2->setEnabled(true);
        ui->LC2SlopeInput->setEnabled(true);
        ui->LC2SlopeButton->setEnabled(true);*/
        ui->minDispInput_2->setEnabled(true);
        ui->maxDispInput_2->setEnabled(true);
    }
}

// Actuator 2 Button Commands


void hsm_full::sendCommand2(){
    setvbuf (stdout, NULL, _IONBF, 0);
    //printf("%f",dispCommand);
    command = 0;
    std::cout << CT2 << "\n";
    //data_to_send = (uint16_t) ((dispCommand + newSpan / 2)  * spanSlope + spanIntercept);
    if (CT2 == 0) {
        dispCommand2 = ui->CommandInput_2->value();
        data_to_send = (uint16_t) inchesToBits(2,dispCommand2);
        std::cout << data_to_send << "\n";
        std::cout << receivedToInches(2,data_to_send) << "\n";
        std::cout << spanSlope2 << "   " << spanIntercept2 << "  " << zeroVol2 << "   " << diffGain2 << "\n";
        std::cout << origSlopes2[4] << "   " << origIntercepts2[4] << "\n";
        serialWrite(2,command,data_to_send);
    } else if (CT2 ==1) {
        forceCommand2 = ui->CommandInput_2->value();
        double double_to_send = forceCommand2 / forceSlope2 + zeroForce2;
        std::cout <<"Sending force value" <<  double_to_send << "\n";
        sendDouble(2,command,double_to_send);

        //data_to_send = (uint16_t) forceCommand;
        //serialWrite(1,command,data_to_send);
    }
}

void hsm_full::sendPID2(){
    setvbuf (stdout, NULL, _IONBF, 0);
    PCommand2 = ui->PInputDisp2->value();
    ui->PInputDisp2->setValue(PCommand2);
    ICommand2 = ui->IInputDisp2->value();
    ui->IInputDisp2->setValue(ICommand2);
    DCommand2 = ui->DInputDisp2->value();
    ui->DInputDisp2->setValue(DCommand2);
    command = 2;
    data_to_send = std::min(4095.0,round(PCommand2/Pmax*4095));
    serialWrite(1,command,data_to_send);
    data_to_send = std::min(4095.0,round(ICommand2/Imax*4095));
    command = 2;
    serialWrite(1,command,data_to_send);
    command = 2;
    data_to_send = std::min(4095.0,round(DCommand2/Dmax*4095));
    serialWrite(1,command,data_to_send);
}

void hsm_full::sendPIDForce2(){
    setvbuf (stdout, NULL, _IONBF, 0);
    PCommand2 = ui->PInputForce2->value();
    ui->PInputForce2->setValue(PCommand2);
    ICommand2 = ui->IInputForce2->value();
    ui->IInputForce2->setValue(ICommand2);
    DCommand2 = ui->DInputForce2->value();
    ui->DInputForce2->setValue(DCommand2);
    command = 3;
    data_to_send = std::min(4095.0,round(PCommand2/Pmax*4095));
    serialWrite(1,command,data_to_send);
    data_to_send = std::min(4095.0,round(ICommand2/Imax*4095));
    command = 3;
    serialWrite(1,command,data_to_send);
    command = 3;
    data_to_send = std::min(4095.0,round(DCommand2/Dmax*4095));
    serialWrite(1,command,data_to_send);
}

void hsm_full::sliderCommand2(){
    /*setvbuf (stdout, NULL, _IONBF, 0);
    if (sliderActive == 1) {
        slideCommand = ui->horizontalSlider->value();
        printf("%f",slideCommand);
        command = 0;
        command = command<<12;
        data_to_send = slideCommand;
        if (microcont == 1){
            data_to_send = data_to_send | command;
            wiringPiI2CWriteReg16(fd,0x00,data_to_send);
        }else{
            data_to_send = std::min(3300.0,round(3.22*slideCommand+(ogZero-1650)));
            //expi.dac_set_raw(data_to_send,2, 2);
        }
    }*/
}

void hsm_full::activateButton2(){
    setvbuf (stdout, NULL, _IONBF, 0);
    if (sliderActive2 == 0){
        sliderActive2 = 1;
        ui->SliderButton_2->setText("De-Activate");
    }
    else if (sliderActive2 == 1){
        sliderActive2 = 0;
        ui->SliderButton_2->setText("Activate");
    }
}

void hsm_full::pressSpanButton2() {
    double targetSpan = ui -> SpanInput_2 -> value();
    double targetZero = ui -> approxZero_2 -> value();
    spanCommand(2,targetSpan, targetZero);
}

void hsm_full::setZero2(){
    dispCommand2 = 0;
    zeroPoint2 = serialRead(2, 1, 0);
    zeroPoint_in2 = receivedToInches(2,zeroPoint2) + zeroPoint_in2;
    ui->Offset_2->display(zeroPoint_in2);
    /*zeroPoint_in = received_Disp;
    ui->Offset->display(zeroPoint_in);
    command = 5;
    command = command<<12;
    data_to_send = round((zeroPoint_in)*4095.0/(2*span))+ogZero;
    zeroPoint = data_to_send;
    data_to_send = data_to_send | command;
    wiringPiI2CWriteReg16(fd,0x00,data_to_send);
    qDebug("%d",zeroPoint);*/
}

void hsm_full::calForce2(){
    forceReceived2[0] = serialRead(2,1,1);
    //std::cout << serialRead(1,1,1);
    forceReceived2[1] = serialRead(2,1,1);
    forceReceived2[2] = serialRead(2,1,1);

    forceReceived2[0] = forceReceived2[0] << 24;
    forceReceived2[1] = forceReceived2[1] << 12;

    forceReceived2[0] |= forceReceived2[1];
    forceReceived2[0] |= forceReceived2[2];
    zeroForce2 = (double) (long) forceReceived2[0];
    saveLCData();
    qDebug("%f",zeroForce2);
}


void hsm_full::startControl2(){
    if (controller2 == 0){
       // ui->StartControl->setText("Stop Controller 2");
        controller2 = 1;
    }else{
        controller2 = 0;
        //ui->StartControl->setText("Start Controller 2");
    }
    serialWrite(2,9,0);
}


void hsm_full::turnOnLow2() {
    if (actTwoLow){
        actTwoLow = 0;
        startControl2();
        ui->Act2LowOn->setText("Off");
        digitalWrite(actTwoLowPin, actTwoLow);
        if (actTwoHigh) {
            actTwoHigh = 0;
            ui->Act1HighOn->setText("Off");
            digitalWrite(actTwoHighPin, actTwoHigh);
        }
    }else{
        actTwoLow = 1;
        startControl2();
        ui->Act2LowOn->setText("On");
        digitalWrite(actTwoLowPin, actTwoLow);
    }
}

void hsm_full::turnOnHigh2() {
    if (actTwoLow){
        if (actTwoHigh){
            actTwoHigh = 0;
            ui->Act2HighOn->setText("Off");
            digitalWrite(actTwoHighPin, actTwoHigh);
        }else{
            actTwoHigh = 1;
            ui->Act2HighOn->setText("On");
            digitalWrite(actTwoHighPin, actTwoHigh);
        }
    }
}


/*void hsm_full::adjustLC2() {
    LC2Offset = (int) ui->LC2Int->value();
    serialWrite(3,2,LC2Offset);
    saveForceSlopes();
    //calLoadCell(1,ui->LC1Int->value());
}

void hsm_full::adjustLC2Zero() {
    LC2Zero = (int) ui->LC2Int_2->value();
    serialWrite(3,4,LC2Zero);
    saveForceSlopes();
    //calLoadCell(0,ui->LC2Int->value());
}

void hsm_full::setLC2Slope() {
    forceSlope2 = ui->LC2SlopeInput->value();
    saveForceSlopes();
}*/

void hsm_full::switchControlType2() {
    if (CT2 == 0) {
        if((ui->minDispInput_2->value() != ui->maxDispInput_2->value()) and (received_Disp2 > ui->minDispInput_2->value() and received_Disp2 < ui->maxDispInput_2->value())){
            CT2 = 1;
            ui->SwitchControlButton_2->setText("Switch to Disp Control");
            ui->ControlText_2->setText("Force Control");
            std::cout << "Min Disp: " << ui->minDispInput_2->value() << "\n";
            std::cout << "Max Disp: " << ui->maxDispInput_2->value() << "\n";
            serialWrite(2,5,inchesToBits(2, ui->minDispInput_2->value()));
            serialWrite(2,5,inchesToBits(2, ui->maxDispInput_2->value()));
            std::cout << "Max Force: " << ui->Act2MaxLC->value() << "\n";
            std::cout << "Force Slope: " << ui->Act2LCSlope->value() << "\n";
            sendDouble(2,5,(double) ui->Act2MaxLC->value());
            sendDouble(2,5,(double) ui->Act2LCSlope->value());
        } else {
            std::cout << "Error, Force control not set, check min maxes\n";
        }
    } else if (CT2 == 1){
        CT2 = 0;
        ui->SwitchControlButton_2->setText("Switch to Force Control");
        ui->ControlText_2->setText("Disp Control");
        serialWrite(2,5,0);
    }
}

//
//
//
//The rest of these functions are more general
//
//
//

void hsm_full::updateLCD(){

    QApplication::processEvents();
    //if (sinOn == 0 && hsmOn == 0 && stiffOn == 0)
    //std::cout << dispCommand << "\n";
    if (running == 0) {
        gettimeofday(&tv, NULL);
        runtime_in_mill = tv.tv_usec;
        runtime_in_s = tv.tv_sec + runtime_in_mill/1000000.0-runtime_initial;
        if(firstActuatorOn) {
            readForce(0);
            ui->Force->display(received_Force);

            ui->TrueForce->display(received_Force + zeroForce);
            ui->CurPos->display(received_Disp);
            ui->CommandNum->display(ui->horizontalSlider->value());
            SerialDisp = serialRead(1, 1, 0);
            //std::cout << SerialDisp << "\n";
            //SerialDisp = 0;
            received_Disp = receivedToInches(1,SerialDisp);
            //std::cout << received_Disp << "\n";
            if(CT1 == 0) {
                hsm_full::XCommand.append((double) runtime_in_s);
                hsm_full::YCommand.append(actOneDispScale * (double) dispCommand);
            }
            if(CT1 == 1) {
                hsm_full::XForceCommand.append((double) runtime_in_s);
                hsm_full::YForceCommand.append(actOneForceScale * (double) forceCommand);
            }
            hsm_full::Xdata.append((double) runtime_in_s);
            //if ((received_Disp<totSpan) && (received_Disp>-totSpan)){
            hsm_full::Ydata.append(actOneDispScale * (double) received_Disp);
            hsm_full::loadCellData1.append(actOneForceScale * received_Force);
            hsm_full::HystDisp1.append((double) runtime_in_s);
            //std::cout << received_Force << "\n";
            last_recieved = received_Disp;

            runCommand.erase(runCommand.begin());
            runCommand.push_back(dispCommand);
            runForceCommand.erase(runForceCommand.begin());
            runForceCommand.push_back(forceCommand);
            runFeedback.erase(runFeedback.begin());
            runFeedback.push_back(received_Disp);
            runForce.erase(runForce.begin());
            runForce.push_back(received_Force);
            runTime.erase(runTime.begin());
            runTime.push_back(runtime_in_s);
        }


        if(secondActuatorOn) {
            SerialDisp2 = serialRead(2,1,0);
            received_Disp2 = receivedToInches(2,SerialDisp2);
            readForce(1);
            hsm_full::XdataAct2.append((double) runtime_in_s);
            hsm_full::YdataAct2.append(actTwoDispScale * (double) received_Disp2);
            hsm_full::HystDisp2.append((double) runtime_in_s);
            hsm_full::loadCellData2.append(actTwoForceScale * received_Force2);
            if(CT2 == 0) {
                hsm_full::XCommandAct2.append((double) runtime_in_s);
                hsm_full::YCommandAct2.append(actTwoDispScale * (double) dispCommand2);

            }
            if(CT2 == 1) {
                hsm_full::XForceCommandAct2.append((double) runtime_in_s);
                hsm_full::YForceCommandAct2.append(actTwoForceScale * (double) forceCommand2);
            }
            last_recieved2 = received_Disp2;
            ui->Force_2->display(received_Force2);
            ui->TrueForce_2->display(received_Force2 + zeroForce2);
            ui->CurPos_2->display(received_Disp2);
            ui->CommandNum_2->display(ui->horizontalSlider_2->value());

            runCommand2.erase(runCommand2.begin());
            runCommand2.push_back(dispCommand2);
            runForceCommand2.erase(runForceCommand2.begin());
            runForceCommand2.push_back(forceCommand2);
            runFeedback2.erase(runFeedback.begin());
            runFeedback2.push_back(received_Disp2);
            runForce2.erase(runForce.begin());
            runForce2.push_back(received_Force2);
            runTime2.erase(runTime.begin());
            runTime2.push_back(runtime_in_s);
        }
    }


    controlcount = controlcount+1;

    if(running == 1) {
        if (firstActuatorOn) {
            if(Xdata.size() > 0){
                runtime_in_s = Xdata.back();
            } else {
                runtime_in_s = 0;
            }
        }
        if (secondActuatorOn) {
            if(XdataAct2.size() > 0) {
                runtime_in_s = XdataAct2.back();
            } else {
                runtime_in_s = 0;
            }
        }
        //std::cout << runtime_in_s << "\n";
        //std::cout << runaxlim << "\n";
    }
    if (runtime_in_s>runaxlim){
        qDebug("What is happeneing");
        std::cout << runaxlim << "    " << runtime_in_s << "\n";
        ui->qwtPlot->setAxisScale(QwtPlot::xBottom,runaxlim,runaxlim+dispPlotRefresh);
        Xdata = {};
        Ydata = {};
        XCommand = {};
        YCommand = {};
        XdataAct2 = {};
        YdataAct2 = {};
        runaxlim = runaxlim+dispPlotRefresh;
    }

    if (runtime_in_s>runaxlimLoad){
        std::cout << runaxlimLoad << "    " << runtime_in_s << "\n";
        ui->qwtPlot_2->setAxisScale(QwtPlot::xBottom,runaxlimLoad,runaxlimLoad+plotRefresh);
        loadCellData1 = {};
        loadCellData2 = {};
        HystDisp1 = {};
        HystDisp2 = {};
        runaxlimLoad = runaxlimLoad+plotRefresh;
    }


    if ((maxSpanInterlock || minSpanInterlock || maxForceInterlock || minForceInterlock || maxSpanInterlock2 || minSpanInterlock2 || maxForceInterlock2 || minForceInterlock2 || eStopActive)
            && !ui->InterAct1->isChecked()) {
        ui->InterAct1->toggle();
    } else if(!(maxSpanInterlock || minSpanInterlock || maxForceInterlock || minForceInterlock || maxSpanInterlock2 || minSpanInterlock2 || maxForceInterlock2 || minForceInterlock2 || eStopActive)
              && ui->InterAct1->isChecked()) {
        ui->InterAct1->toggle();
    }

    checkInterlock();
    turnOffHydraulics();
    this->updatePlot();

}


void hsm_full::spanCommand(int channel, double targetSpan, double targetZero){
    double ampedSpan = 100000000;
    int ampValue = 128;
    int zeroBit;
    std::map <double,std::vector<double>> calMap;
    std::vector <std::vector<double>> zMap;
    double dGain;
    double zVol;

    if (channel ==1) {
        calMap = spanCalMap;
        zMap = zeroMap;
        dGain = diffGain;
        zVol = zeroVol;
    }
    if (channel ==2) {
        calMap = spanCalMap2;
        zMap = zeroMap2;
        dGain = diffGain2;
        zVol = zeroVol2;
    }
    //std::cout << (totSpan) << "\n";
    std::map<double,std::vector<double>>::iterator mapIter;
    int ampPrecision = 0;
    for (mapIter = calMap.begin(); mapIter != calMap.end(); mapIter ++) {
        if (mapIter->second[4] >= targetSpan && mapIter->second[4] < ampedSpan) {
            //if(mapIter->second[2] >ampPrecision){
                ampPrecision = mapIter->second[2];
                ampedSpan = mapIter -> second[4];
                std::cout << "Checking Span" << ampedSpan << "\n";
                ampValue = mapIter -> first;
                //std::cout << "Amped Precision: " << ampPrecision << "\n";
            //}
        }
    }
    if (ampedSpan == 100000000) {
        ampedSpan = calMap.begin() -> second[4];
        ampValue = calMap.begin() -> first;
    }
    std::cout << "Amped Value: " << ampValue << "\n";
    targetZero = targetZero - ampedSpan / 2;
    //std::cout << "target zero: " << targetZero << "\n";
    zeroBit = inchesToBits(channel,targetZero);
    //std::cout << "Bit zero: " << zeroBit << "\n";
    int sendZero = 0;
    for (int i = 0; i < zMap.size(); i++) {
        //std::cout << zeroMap.size() << "    "<< i << "\n";

        if (abs(zMap[i][1] - zeroBit) < 5) {
            //std::cout << "test 1\n";
            sendZero = round(zMap[i][0]);
            zVol = zMap[i][1];
        }
    }
    std::cout << "test 2\n";
    /*if (zeroVol < 0) {
        zeroVol = 0;
    }*/


    //sendZero = 0;
    //zeroVol = 0;
    //std::cout << "test 3\n";
    serialWrite(channel, 14, sendZero);
    std::cout << "Send Zero: " << sendZero << "\n";
    std::cout <<"Span: " << ampedSpan << "   ampValue: " << ampValue << "\n";
    serialWrite(channel ,10 , ampValue);

    double Slope = calMap[ampValue][0];
    double Intercept = calMap[ampValue][1];
    double Max = calMap[ampValue][2];
    double nSpan = ampedSpan;

    /*
    spanSlope = calMap[ampValue][0];
    spanIntercept = calMap[ampValue][1];
    spanMax = calMap[ampValue][2];
    newSpan = ampedSpan;*/

    //std::cout << (ampValue) << "\n";
    //std::cout << "new Span: " << ampedSpan << "\n";
    sendDouble(channel,15, Slope);
    std::cout << Slope << "\n";
    sendDouble(channel,15, Intercept);
    std::cout << Intercept << "\n";
    sendDouble(channel,15, dGain);
    std::cout << dGain << "\n";
    sendDouble(channel,15, zVol);
    std::cout << zVol << "\n";

    if(channel == 1) {
        spanSlope = calMap[ampValue][0];
        spanIntercept = calMap[ampValue][1];
        spanMax = calMap[ampValue][2];
        newSpan = ampedSpan;
        zeroVol = zVol;

        for (int i = 0; i < potTru.size(); i++) {
            sendDouble(channel,15,(double) potTru[i]);
            std::cout << potTru[i] << "\n";
        }
        for (int i = 0; i < origSlopes.size(); i++) {
            sendDouble(channel,15,origSlopes[i]);
            sendDouble(channel,15,origIntercepts[i]);
            std::cout << origSlopes[i] << "    " << origIntercepts[i] << "\n";
        }
    }
    if(channel == 2) {
        spanSlope2 = calMap[ampValue][0];
        spanIntercept2 = calMap[ampValue][1];
        spanMax2 = calMap[ampValue][2];
        newSpan2 = ampedSpan;
        zeroVol2 = zVol;
        for (int i = 0; i < potTru2.size(); i++) {
            sendDouble(channel,15,(double) potTru2[i]);
            std::cout << potTru2[i] << "\n";
        }
        for (int i = 0; i < origSlopes2.size(); i++) {
            sendDouble(channel,15,origSlopes2[i]);
            sendDouble(channel,15,origIntercepts2[i]);
            std::cout << origSlopes2[i] << "    " << origIntercepts2[i] << "\n";
        }
    }
    /*span = ui->SpanInput->value();
    ui->CurSpan->display(span);
    command = 4;
    command = command<<12;
    data_to_send = std::min(4095.0,round((span)*4095.0/(2*maxspan)));
    data_to_send = data_to_send | command;
    wiringPiI2CWriteReg16(fd,0x00,data_to_send);*/
}


void hsm_full::readForce(int channel){
    // Loop gettting the fresh readings.

    int SS;

    if (hardwareConnected) {
        if (useADCs) {
            if (channel == 0) {
                    SS = 10;
                } else if(channel == 1) {
                    SS = 11;
                } else {
                    std::cout << "Channel must be 0 or 1 \n";
                    SS = 10;
                }
                bool tryAgain = true;
                double sum = 0;
                int numReads = 50;

                while (tryAgain == true) {
                    //int oldValue = readFromADC(SS, channel);
                    for (int j = 0; j < numReads; j++) {
                    //int newValue = readFromADC(SS, channel);
                    //if (abs(newValue - ))
                    sum += readFromADC(SS, channel);
                    }

                    f1 = (int) (sum / (double) numReads);
                    tryAgain = false;

                }

                if (channel == 0) {

                    received_Force = wForce * f1 + (1 - wForce) * ypForce;//(f1 * forceSlope) - zeroForce;
                    ypForce = received_Force;
                    //received_Force = lp.filt(received_Force);
                    //std::cout << "Reading Force\n";
                } else if (channel == 1) {
                    received_Force2 = (f1 * forceSlope2) - zeroForce2;
                }
        } else{
            if (channel == 0) {
                //std::cout << "Reading force from teensy \n";

                //numReceived = received[1]<<8;
                //numReceived |= received[0];
                forceReceived[0] = serialRead(1,1,1);
                //std::cout << serialRead(1,1,1);
                forceReceived[1] = serialRead(1,1,1);
                forceReceived[2] = serialRead(1,1,1);

                forceReceived[0] = forceReceived[0] << 24;
                forceReceived[1] = forceReceived[1] << 12;

                forceReceived[0] |= forceReceived[1];
                forceReceived[0] |= forceReceived[2];
                //std::cout << forceSlope << ", " << forceReceived[0] << "\n";
                received_Force = forceSlope * ((double) (long) forceReceived[0] - zeroForce);
                //std::cout << received_Force << "\n";

                ypForce = received_Force;
                //received_Force = 0;
            } else if (channel == 1) {
                forceReceived2[0] = serialRead(2,1,1);
                //std::cout << serialRead(1,1,1);
                forceReceived2[1] = serialRead(2,1,1);
                forceReceived2[2] = serialRead(2,1,1);

                forceReceived2[0] = forceReceived2[0] << 24;
                forceReceived2[1] = forceReceived2[1] << 12;

                forceReceived2[0] |= forceReceived2[1];
                forceReceived2[0] |= forceReceived2[2];
                received_Force2 = forceSlope2 * ((double) (long) forceReceived2[0] - zeroForce2);

                //std::cout << received_Force2 << "\n";
                ypForce2 = received_Force2;
            }
        }
    }
    else {
        if (channel == 0) {
            received_Force = 0;
        } else if (channel == 1) {
            received_Force2 = 0;
        }
    }


}

int readFromADC(int SS,int channel) {
    int ADC = 10000;
    while (ADC > 4090) {
    digitalWrite (SS, 0) ;
    buffer[0] = MCP3202_START; // Set output buffrt with MCP3202 configuration
    buffer[1] = MCP3202_CONFIG;
    buffer[2] = 0;

    wiringPiSPIDataRW(channel, buffer, MCP2002_BUFFER_SIZE); // Read and write buffer

    ADC = (buffer[2] | ((buffer[1] & 0x0F) << 8));
    digitalWrite (SS, 1);
    }
    return ADC;
}


void hsm_full::setAmp(){
    if(sinsweep==0){
        amp = ui->AmpInput->value();
    }else{
        freq0 = ui->AmpInput->value();
    }
    qDebug("%f",amp);
}

void hsm_full::setFreq(){
    if(sinsweep==0){
        freq = ui->FreqInput->value();
    }else{
        freq1 = ui->FreqInput->value();
    }
    qDebug("%f",freq);
}

void hsm_full::sweep(){
    if(sinsweep==0){
        sinsweep = 1;
        ui->AmpButton->setText("Freq0");
        ui->FreqButton->setText("Freq1");
        ui->SinButton->setText("Sweep Test");
    }else {
        sinsweep = 0;
        ui->AmpButton->setText("Set Amp");
        ui->FreqButton->setText("Set Freq");
        ui->SinButton->setText("Sin Test");
}
    //qDebug("%f",freq);
}

void hsm_full::ampTest(){
    if(amptest==0){
        amptest = 1;
        ui->AmpButton->setText("Max Amp");
        ui->FreqButton->setText("Set Freq");
        ui->SinButton->setText("Amp Test");
    }else {
        amptest = 0;
        ui->AmpButton->setText("Set Amp");
        ui->FreqButton->setText("Set Freq");
        ui->SinButton->setText("Sin Test");
}
}

void hsm_full::reqloops(){
    /*command = 7;
    command = command<<12;
    data_to_send = 0;
    data_to_send = data_to_send | command;
    wiringPiI2CWriteReg16(fd,0x00,data_to_send);
    curloops = wiringPiI2CReadReg16(fd,0x00);
    loops.push_back(curloops);
    command = 0;*/
    //qDebug("%f",curloops);
}


void hsm_full::PSAS_Window(){
    PSAS *StructSoft = new PSAS(this);
    StructSoft->show();
}

void hsm_full::Cal_Window(){
    timer->stop();
    SpanCalibration *newStructSoft = new SpanCalibration(this);
    newStructSoft->show();
}

void hsm_full::sinTest(){
struct sched_param param;
struct sched_param param2;
pthread_attr_t attr;
pthread_attr_t attr2;
pthread_t thread, thread2;
int ret;
int ret2;


if (sinOn == 0){
    timer->stop();
    //qDebug("AmpTest:%d",amptest);
    if (sinsweep == 0 && amptest == 0){
        for(int j=1; j*tstep<1/freq;j++){
             sinWave.push_back(amp*sin(tstep*j*freq*2*3.14159));
         }
    }else if(amptest == 1){
        slope = .02/(1/freq);
        for (int j = 1;slope*j*tstep<amp;j++){
            sinWave.push_back(slope*(tstep*j)*sin(tstep*j*freq*2*3.14159));
        }
        //qDebug("Done");
    }else{
        for (int j = 1;j*tstep<30;j++){
            sinWave.push_back(amp*sin(2*3.14159*((freq0*tstep*j)+((freq1-freq0)/(2*30))*pow((tstep*j),2.0))));
        }
    }
    i = 0;
    clearPlotVectors();

    sinOn =1;

    if(ui->selectAct->value() == 1){
        signalLoops= {};
        sinCommand = {};
        sinTime = {};
        sinResponse = {};
        sinForce = {};
    }
    else if(ui->selectAct->value() == 2){
        signalLoops2 = {};
        sinCommand2 = {};
        sinTime2 = {};
        sinResponse2 = {};
        sinForce2 = {};
    }
    running = 1;


    pthread_mutex_init(&race_mutex,NULL);
    pthread_mutex_init(&trigger_mutex,NULL);
    /* Lock memory */
    if(mlockall(MCL_CURRENT|MCL_FUTURE) == -1) {
            printf("mlockall failed: %m\n");
            exit(-2);
    }

    /* Initialize pthread attributes (default values) */
    ret = pthread_attr_init(&attr);
    if (ret) {
            printf("init pthread attributes failed\n");
            //goto out;
    }

    /* Set a specific stack size  */
    ret = pthread_attr_setstacksize(&attr, 100000000);
    if (ret) {
        printf("pthread setstacksize failed\n");
        //goto out;
    }

    /* Set scheduler policy and priority of pthread */
    ret = pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
    if (ret) {
            printf("pthread setschedpolicy failed\n");
            //goto out;
    }
    param.sched_priority = 95;
    ret = pthread_attr_setschedparam(&attr, &param);
    if (ret) {
            printf("pthread setschedparam failed\n");
            //goto out;
    }
    /* Use scheduling parameters of attr */
    ret = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    if (ret) {
            printf("pthread setinheritsched failed\n");
            //goto out;
    }
    gettimeofday(&tv, NULL);
    time_initial = tv.tv_usec;
    time_initial = tv.tv_sec + time_initial/1000000.0;

    /* Create a pthread with specified attributes */
    ret = pthread_create(&thread, &attr, simple_cyclic_task, this);
    if (ret) {
            printf("create pthread failed\n");
            //goto out;
    }
    int i = 0;


    //ui->qwtPlot->setAxisAutoScale(QwtPlot::xBottom,false);
    //ui->qwtPlot->setAxisScale(QwtPlot::xBottom,0,axlim);
    //ui->qwtPlot->detachItems();

    qDebug("Hello");
    runaxlim = 10;
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom,0,10);
    while(running == true){
        plotcount = plotcount+1;
        if (plotcount%500000 == 0){
            //readForce(0);
            //curve1->setSamples(Xdata,Ydata);
            //updateLCD();
            //gettimeofday(&tv1, NULL);
            //double time_in_mill1 = tv1.tv_usec;
            //double time_in_s1 = tv1.tv_sec + time_in_mill1/1000000.0-time_initial;
            //i2ctest = wiringPiI2CReadReg16(fd,0x00);
            //if (i2ctest == -1){
            //   while (i2ctest ==-1){
            //         i2ctest = wiringPiI2CReadReg16(fd,0x00);
            //    }
            //}
            //received_Disp = (((double)i2ctest)-512)*2*span/1023.0-((ogZero-512)*2*span/1023);

            //hsm_full::Xdata.append((double) time_in_s1);
            //if ((received_Disp<span) && (received_Disp>-span)){
            //    relative_Disp = received_Disp-zeroPoint_in;
            //    hsm_full::Ydata.append((double) relative_Disp);
            //    last_recieved = received_Disp;

            //}
            //else{
            //    relative_Disp = last_recieved-zeroPoint_in;
            //    hsm_full::Ydata.append((double) relative_Disp);
            //}
            /*if (setlim==1){
                ui->qwtPlot->setAxisScale(QwtPlot::xBottom,runaxlim,runaxlim+10);
                Xdata = {};
                Ydata = {};
                XCommand = {};
                YCommand = {};
                runaxlim = runaxlim+10;
                setlim = 0;
            }*/

           pthread_mutex_lock(&race_mutex);
           this->updateLCD();
           pthread_mutex_unlock(&race_mutex);
            //qDebug("%d",j);

        }
    }


    /* Join the thread and wait until it is done */
    ret = pthread_join(thread, NULL);
    if (ret){
            printf("join pthread failed: %m\n");
    }
    qDebug("Threads Closed");
    timer->start();
    sinWave = {};
    clearPlotVectors();

    if(sinsweep==1 or amptest == 1){
        sinOn = 0;
        clearPlotVectors();
        running = 0;
        timer->start();
        ui->qwtPlot->setAxisAutoScale(QwtPlot::xBottom,true);
        ui->qwtPlot->setAxisAutoScale(QwtPlot::yLeft,true);
        sinWave = {};
        runaxlim = 10;
        runaxlimLoad = 60;
        ui->qwtPlot->setAxisScale(QwtPlot::xBottom,0,runaxlim);
        ui->qwtPlot_2->setAxisScale(QwtPlot::xBottom,0,runaxlimLoad);
    }
}else{
    sinOn = 0;
    running = 0;
    runaxlim = 10;
    runaxlimLoad= 10;
    timer->start();
    ui->qwtPlot->setAxisAutoScale(QwtPlot::xBottom,true);
    ui->qwtPlot->setAxisAutoScale(QwtPlot::yLeft,true);
    sinWave = {};
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom,0,runaxlim);
    ui->qwtPlot_2->setAxisScale(QwtPlot::xBottom,0,runaxlimLoad);
}

}

int hsm_full::plotResults(){
    Py_Initialize();
    import_array();
    PyObject *sysPath = PySys_GetObject((char*)"path");
    PyList_Append(sysPath,PyUnicode_FromString("/home/jim53/Desktop/RpiHSM/HSM_Full/HSM_Full"));  // path to the module to import
    PlotResultsName = PyUnicode_FromString("PlotHybridResults");
    PlotResultsMethod = PyImport_Import(PlotResultsName);

    if (PlotResultsMethod != NULL) {

        PlotResultsArgs = PyTuple_New(1);
        PyTuple_SetItem(PlotResultsArgs, 0, Model);

        PlotResultsFunc = PyObject_GetAttrString(PlotResultsMethod, "PlotHybridResults");
        if (PlotResultsFunc && PyCallable_Check(PlotResultsFunc)) {
            printf("attempt\n");
            PlotResultsOut = PyObject_CallObject(PlotResultsFunc, PlotResultsArgs);
        } else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function %s\n", "PlotResults");
        }
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load %s\n", "PlotResults");
        return 1;
    }
}


//This is a function that activates a pin on the raspberry pi. It was used for testing before the HSM activation relays were set up
/*void hsm_full::activatePin(){
    if (pinActive){
        pinActive = 0;
        digitalWrite(7, pinActive);
        qDebug("1");
    }else{
        pinActive = 1;
        digitalWrite(7, pinActive);
        qDebug("2");
    }
}*/

int hsm_full::serialRead(int channel, int comm, int data) {
    int sendChan;
    std::vector<double> returnList;

    if (hardwareConnected){
        command = comm;
        command = command<<12;
        if (channel == 1) {
            sendChan = fd;
        } else if (channel == 2) {
            sendChan = fd2;
        } else {
            sendChan = fd;
        }
        data_to_send = data;
        data_to_send = data_to_send | command;
        //serial(fd);
        sendData[0] = data_to_send >> 8;
        sendData[1] = data_to_send;
        uint16_t crcSum = crc_modbus(sendData,2);
        sendData[2] = crcSum >> 8;
        sendData[3] = crcSum;
        bool tryagain = true;
        while (tryagain) {
            //std::cout << "Trying to Send... \n";
            serialPutchar(sendChan,'<');
            //std::cout << "Sent Start \n";
            serialPutchar(sendChan,sendData[0]);
            //std::cout << "Sent 1 \n";
            serialPutchar(sendChan,sendData[1]);
            //std::cout << "Sent 2 \n";
            serialPutchar(sendChan,sendData[2]);
            //std::cout << "Sent 3 \n";
            serialPutchar(sendChan,sendData[3]);
            //std::cout << "Sent 4 \n";
            serialPutchar(sendChan,'>');
            //std::cout << "Sent End \n";

            if (readAck(channel) == 1) {
                tryagain = false;
            }
        }
        //std::cout << "Sent Read!\n";
        /*char startMarker = '<';
        char endMarker = '>';
        char rc;
        int maxBytes = 2;
        int ndx = 0;*/
        int numReads = 4;

        /*if (comm == 11) {
            numReads = 8;
        }*/
        for(int i = 0; i < numReads;i++){
          char rc;
          rc = serialGetchar(sendChan);
          received[i] = rc;
          //std::cout << "Check "<< i << "\n";
        }

        //numReceived = received[1]<<8;
        //numReceived |= received[0];
        //recData[0] = received[1];
        //recData[1] = received[0];
        //numReceived = numReceived & 4095;
        //returnList.push_back(numReceived); //this isnt being used or returned. Should I remove?
        unsigned char crcRec[4];

        numReceived = received[1]<<8;
        numReceived |= received[0];
        crcRec[0] = received[0];
        crcRec[1] = received[1];
        crcSum = crc_modbus(crcRec,2);
        numReceived = numReceived & 4095;
        crcReceived = received[3] << 8;
        crcReceived |= received[2];

        unsigned char ACK;
        if (crcSum == crcReceived) {
            //std::cout<< "CRC Check passed\n";
            ACK = 1;

        } else {
            //std::cout<< "CRC Check failed\n";
            ACK = 0;
        }
        //serialPutchar(sendChan,ACK);
        //we dont really need an ack bit because if crcReceived != crc, we can just say the last received disp is the numReceived, but I added it
      //} //Took this out because I don't think its right.

    }else {
        numReceived = 0;
    }
    return numReceived;
}

void hsm_full::serialWrite(int channel, int comm, int data) {
    int sendChan;

    if (hardwareConnected){
        command = comm;
        command = command<<12;
        if (channel == 1) {
            sendChan = fd;
        } else if (channel == 2) {
            sendChan = fd2;
        } else if (channel == 3) {
            sendChan = fd3;
        } else {
            sendChan = fd;
        }
        data_to_send = data;
        data_to_send = data_to_send | command;
        //serialFlush(fd);
        sendData[0] = data_to_send >> 8;
        sendData[1] = data_to_send;
        int test = data_to_send & 255;
        uint16_t crcSum = crc_modbus(sendData,2);
        //std::cout << test << "\n";
        sendData[2] = crcSum >> 8;
        sendData[3] = crcSum;
        bool tryagain = true;
        while (tryagain) {
            //std::cout << "trying to send \n";
            serialPutchar(sendChan,'<');
            serialPutchar(sendChan,sendData[0]);
            serialPutchar(sendChan,sendData[1]);
            serialPutchar(sendChan,sendData[2]);
            serialPutchar(sendChan,sendData[3]);
            serialPutchar(sendChan,'>');
            if (readAck(channel) == 1) {
                tryagain = false;
                //std::cout << "ACK recieved \n";
            }
        }
        //std::cout << "Sent Write!\n";
    }
}

int hsm_full::readAck(int channel) {
    int returnNum;
    int sendChan;
    int numReads = 1; //only need one byte. If it is 1, acknowledged recieved, otherwise we need to resend
    char recACK;
    if (channel == 1) {
        sendChan = fd;
    } else if (channel == 2) {
        sendChan = fd2;
    } else if (channel == 3) {
        sendChan = fd3;
    } else {
        sendChan = fd;
    }
    char rc;
    rc = serialGetchar(sendChan);
    recACK = rc;

    returnNum = (int) recACK;
    //std::cout << returnNum << "\n";

    return returnNum;
}


void hsm_full::sendDouble(int channel, int comm, double data) {
    int sendChan;
    if (hardwareConnected) {
        union myUnion {
            double dValue;
            uint64_t iValue;
        };

        myUnion myValue;
        myValue.dValue=data;
        //std::cout << myValue.iValue << "\n";
        std::bitset<64> x(myValue.iValue);
        //std::cout << x << "\n";
        int double1 = myValue.iValue >> 56 & 255;
        int double2 = myValue.iValue >> 48 & 255;
        int double3 = myValue.iValue >> 40 & 255;
        int double4 = myValue.iValue >> 32 & 255;
        int double5 = myValue.iValue >> 24 & 255;
        int double6 = myValue.iValue >> 16 & 255;
        int double7 = myValue.iValue >> 8 & 255;
        int double8 = myValue.iValue & 255;
        serialWrite(channel,comm,double1);
        serialWrite(channel,comm,double2);
        serialWrite(channel,comm,double3);
        serialWrite(channel,comm,double4);
        serialWrite(channel,comm,double5);
        serialWrite(channel,comm,double6);
        serialWrite(channel,comm,double7);
        serialWrite(channel,comm,double8);
    }
}


std::vector <std::vector <double>>  hsm_full::readFiles(std::string fileName){
    DIR *directory;
    std::vector <std::vector <double>> returnVector;
    struct dirent *x;
    std::string *Data;
    bool result = FALSE;
    if ((directory = opendir("/home/jim53/Desktop/RpiHSM/HSM_Full")) != NULL){
        while((x=readdir(directory))!=NULL){
            if(fileName==x->d_name){
                    printf("attempt");
                    result=true;  //if file found then  assign  result to false.
                        break;     // break the loop if file found.
        }
    }
    closedir(directory);
    if(result)   // if file is present then....
      {
        std::cout << "Pot calibration file is present" << "\n";
        std::string calDir = "/home/jim53/Desktop/RpiHSM/HSM_Full/";
        for(int i = 0; i <= (int)fileName.size(); i++)
            {
                calDir.push_back(fileName.c_str()[i]);
            }

        std::ifstream fileName(calDir.c_str());
        if (fileName.is_open()) {
            std::vector<float> dataRow;
            std::string line, data;
            int lineCount = 0;

            while(getline(fileName, line)){
                std::stringstream str(line);
                returnVector.push_back({});
                while(getline(str, data, ',')){
                     dataRow.push_back(std::stof(data));
                }
                for (int i = 0; i < dataRow.size(); i ++) {
                    returnVector[lineCount].push_back(dataRow[i]);
                }
                dataRow.clear();
                lineCount += 1;
            }
        }
        return returnVector;
      }
      else    //if file is not present....
      {
        std::cout << "Cal file is was not found" << "\n";
        returnVector = {{-1}};
      }

}else{
        returnVector = {{-1}};
        printf("Directory Not Found");
    }
return returnVector;
}

std::vector <double> hsm_full::LinearRegression(std::vector <double> xData, std::vector<double> yData) {
    double sumX = 0;
    double sumX2 = 0;
    double sumY = 0;
    double sumXY = 0;
    double n = xData.size();
    double slope;
    double intercept;
    std::vector <double> returnVec;
    for (int i=0;i<n;i++){
        sumX = sumX + xData[i];
        sumX2 = sumX2 + xData[i]*xData[i];
        sumY = sumY+yData[i];
        sumXY = sumXY + xData[i]*yData[i];
    }
    slope = ((double)n*sumXY-sumX*sumY)/((double)n*sumX2-sumX*sumX);
    intercept = (sumY - slope * sumX) / n;
    returnVec.push_back(slope);
    returnVec.push_back(intercept);
    return returnVec;
}

// Send zero was used to send the digital zero value for disp. Change Span was used to change the max span of the the disp. These are both
// replaced by the change span function
// send double was a function that sends a double to the teensys. No longer used

//void hsm_full::sendZero() {
//    int zeroToSend = ui->zeroBitInput->value();
//    ui->zeroBitDisp->display(zeroToSend);
//    serialWrite(1,14,zeroToSend);
//}

//void hsm_full::changeSpan() {
//    int spanToSend = ui->SpanBitInput->value();
//    ui->spanBitDisp->display(spanToSend);
//    serialWrite(1,10,spanToSend);
//}

//void hsm_full::sendDoubleUI() {
//    double doubleToSend= ui->sendDouble->value();
//    sendDouble(1,doubleToSend);
//}

double hsm_full::receivedToInches(int channel, int dataInBits) {

    //Implement Relative Disp. Need to subract zeropoint
    double inches;
    double spanZeroPoint;
    double zPoint_in;
    std::vector<double> Slopes;
    std::vector<double> Intercepts;
    std::vector<double> potIn;
    double zVol;
    double dGain;
    double dIntercept;
    double sSlope;
    double sInter;
    std::vector <double>  potTrue;

    if (channel == 1){
        zPoint_in = zeroPoint_in;
        Slopes = origSlopes;
        Intercepts = origIntercepts;
        potIn = potInches;
        zVol = zeroVol;
        dGain = diffGain;
        dIntercept = diffIntercept;
        sSlope = spanSlope;
        sInter = spanIntercept;
        potTrue = potTru;
    }
    if (channel == 2){
        zPoint_in = zeroPoint_in2;
        Slopes = origSlopes2;
        Intercepts = origIntercepts2;
        potIn = potInches2;
        zVol = zeroVol2;
        dGain = diffGain2;
        dIntercept = diffIntercept2;
        sSlope = spanSlope2;
        sInter = spanIntercept2;
        potTrue= potTru2;
    }
    //std::cout << dataInBits << "\n";
    /*if (spanIntercept > 0) {
        spanZeroPoint = (spanMax - spanIntercept) / 2;
    } else {
        spanZeroPoint = (spanMax - 0) / 2;
    }
    // Conversion from bits to inches using calibration factors. This uses slopes and intercepts from calibration.
    // Also shifts data to a +- span / 2 range rather than 0 to span;

    //When you get close to the intercept accuracy drops significantly. This makes sure it doesn't read incorrectly
    if (dataInBits < spanIntercept) {
        dataInBits = spanIntercept;
    }*/
    //std::cout << spanIntercept << "    " << spanSlope << "     " << diffGain << "      " << zeroVol << "\n";
    //std::cout << dataInBits << "\n";
    dataInBits = ((double) dataInBits - sInter) / sSlope;//((((dataInBits - spanIntercept) / spanSlope) - calIntercept) / calSlope * (1 / inchSlope)) / 1.057;
    dataInBits = (dataInBits * dGain + dIntercept) + zVol;

    //dataInBits = dataInBits - 65;
    //std::cout << dataInBits << "\n";

    if (dataInBits < potTrue[1]) {
        inches = (dataInBits - Intercepts[0]) / Slopes[0];
    } else if (dataInBits < potTrue[2]) {
        inches = (dataInBits - Intercepts[1]) / Slopes[1];
    } else if (dataInBits < potTrue[3]) {
        inches = (dataInBits - Intercepts[2]) / Slopes[2];
    } else if (dataInBits < potTrue[4]) {
        inches = (dataInBits - Intercepts[3]) / Slopes[3];
    } else if (dataInBits < potTrue[5]) {
        inches = (dataInBits - Intercepts[4]) / Slopes[4];
    } else if (dataInBits < potTrue[6]) {
        inches = (dataInBits - Intercepts[5]) / Slopes[5];
    } else if (dataInBits < potTrue[7]) {
        inches = (dataInBits - Intercepts[6]) / Slopes[6];
    } else if (dataInBits < potTrue[8]) {
        inches = (dataInBits - Intercepts[7]) / Slopes[7];
    } else {
        inches = (dataInBits - Intercepts[8]) / Slopes[8];
    }
    //std::cout << "inches: " << inches << "\n";
    inches = inches - zPoint_in;
    return inches;
}

int hsm_full::inchesToBits(int channel, double dataInInches) {
    int bits;
    double tempbits;
    double spanZeroPoint;
    double zPoint_in;
    std::vector<double> Slopes;
    std::vector<double> Intercepts;
    std::vector<double> potIn;
    double zVol;
    double dGain;
    double dIntercept;
    double sSlope;
    double sInter;

    if (channel == 1){
        zPoint_in = zeroPoint_in;
        Slopes = origSlopes;
        Intercepts = origIntercepts;
        potIn = potInches;
        zVol = zeroVol;
        dGain = diffGain;
        dIntercept = diffIntercept;
        sSlope = spanSlope;
        sInter = spanIntercept;
    }
    if (channel == 2){
        zPoint_in = zeroPoint_in2;
        Slopes = origSlopes2;
        Intercepts = origIntercepts2;
        potIn = potInches2;
        zVol = zeroVol2;
        dGain = diffGain2;
        dIntercept = diffIntercept2;
        sSlope = spanSlope2;
        sInter = spanIntercept2;
    }

    dataInInches = dataInInches + zPoint_in;
    if (dataInInches < potIn[1]) {
        tempbits = (dataInInches * Slopes[0]) + Intercepts[0];
    } else if (dataInInches < potIn[2]) {
        tempbits = (dataInInches * Slopes[1]) + Intercepts[1];
    } else if (dataInInches < potIn[3]) {
        tempbits = (dataInInches * Slopes[2]) + Intercepts[2];
    } else if (dataInInches < potIn[4]) {
        tempbits = (dataInInches * Slopes[3]) + Intercepts[3];
    } else if (dataInInches < potIn[5]) {
        tempbits = (dataInInches * Slopes[4]) + Intercepts[4];
    } else if (dataInInches < potIn[6]) {
        tempbits = (dataInInches * Slopes[5]) + Intercepts[5];
    } else if (dataInInches < potIn[7]) {
        tempbits = (dataInInches * Slopes[6]) + Intercepts[6];
    } else if (dataInInches < potIn[8]) {
        tempbits = (dataInInches * Slopes[7]) + Intercepts[7];
    } else {
        tempbits = (dataInInches * Slopes[8]) + Intercepts[8];

    }
    tempbits = (tempbits - dIntercept - zVol) / dGain;
    tempbits = (tempbits * sSlope) + sInter;//((((dataInBits - spanIntercept) / spanSlope) - calIntercept) / calSlope * (1 / inchSlope)) / 1.057;
    bits = round(tempbits);
    if (bits < 0) {
        bits = 0;
    } else if (bits >4095) {
        bits = 4095;
    }
    //std::cout << "inches: " << inches << "\n";
    return bits;
}





void hsm_full::turnOffHydraulics() {
    if (eStopActive || maxSpanInterlock || minSpanInterlock || maxForceInterlock || minForceInterlock
            || maxSpanInterlock2 || minSpanInterlock2 || maxForceInterlock2 || minForceInterlock2) {
        if (actOneHigh) {
            turnOnHigh1();
        }
        if (actOneLow) {
            turnOnLow1();
        }
        if (actTwoHigh) {
            turnOnHigh2();
        }
        if (actTwoLow) {
            turnOnLow2();
        }
    }
}



void eStop() {
    //std::cout << "eStop Activated" << "\n";
    eStopActive = true;
}

void hsm_full::Interlock_Window(){
    timer->stop();
    Interlock *newStructSoft = new Interlock(this);
    newStructSoft->show();
}

void hsm_full::readAllFilesAndCalibrate() {
    zeroMap = {};
    origSlopes = {};
    origIntercepts = {};
    potTru = {};
    potInches = {};
    spanCalMap.clear();

    zeroMap2 = {};
    origSlopes2 = {};
    origIntercepts2 = {};
    potTru2 = {};
    potInches2 = {};

    potCalibration = readFiles("PotCalibrationAll.txt");
    potCalibration2 = readFiles("PotCalibrationAll2.txt");

    if (potCalibration.size() > 1) {
        for (int i = 0; i < potCalibration.size() - 1; i++) {
            potTru.push_back(potCalibration[i][0]);
            potInches.push_back(potCalibration[i][1]);
        }
        for (int i = 0; i < potCalibration.size() - 2; i ++) {
            origSlopes.push_back((potTru[i + 1] - potTru[i]) / (potInches[i + 1] - potInches[i]));
            origIntercepts.push_back(potTru[i] - origSlopes[i] * potInches[i]);
            //std::cout << "Slope: " << origSlopes[i] << "    " << "Intercept: " << origIntercepts[i] << "\n";
        }
        diffGain = potCalibration[10][0];
        diffIntercept = potCalibration[10][1];
        totSpan = potCalibration[10][2];
    }

    // A lot of this can and maybe should be condensed into multidim vectors. Implementing like this because of time limitations
    // Everything should be saved into the same file and then it should be arbitrarily sized based on number of controllers
    if (potCalibration2.size() > 1) {
        for (int i = 0; i < potCalibration2.size() - 1; i++) {
            potTru2.push_back(potCalibration2[i][0]);
            potInches2.push_back(potCalibration2[i][1]);
        }
        for (int i = 0; i < potCalibration2.size() - 2; i ++) {
            origSlopes2.push_back((potTru2[i + 1] - potTru2[i]) / (potInches2[i + 1] - potInches2[i]));
            origIntercepts2.push_back(potTru2[i] - origSlopes2[i] * potInches2[i]);
            //std::cout << "Slope: " << origSlopes[i] << "    " << "Intercept: " << origIntercepts[i] << "\n";
        }
        diffGain2 = potCalibration2[10][0];
        diffIntercept2 = potCalibration2[10][1];
        totSpan2 = potCalibration2[10][2];
    }
    //totSpan = 11;
    //std::cout << "Diff Gain" << diffGain << "\n";
    //calSlope = potCalibration[0][0];
    //calIntercept = potCalibration[0][1];
    //maxDiffValue = potCalibration[0][2];
    //maxOGValue = potCalibration[0][3];
    //minDiffValue = 0;
    //minDiffValue2 = 0;
    //minOGValue = potCalibration[0][5];
    //inchSlope = potCalibration[0][7];
    //double newCalSlope = calSlope / totSpan * (maxOGValue - minOGValue);
    //double minDiffInInch = (minDiffValue - calIntercept) / newCalSlope;

    spanCalibration = readFiles("AmpCalibration.txt");
    spanCalibration2 = readFiles("AmpCalibration2.txt");
    //std::cout << "Hello " << minOGValue << "\n";
    //std::cout << maxOGValue << "\n";

    if(spanCalibration.size() > 1) {
        for (int i = 0; i < spanCalibration.size(); i++) {
            std::vector<double> tempData;
            for (int j = 1; j < spanCalibration[i].size(); j++) {
                tempData.push_back(spanCalibration[i][j]);
            }
            spanSlope = spanCalibration[i][1];
            spanIntercept = spanCalibration[i][2];
            //std::cout << "SpanTest: "<< spanCalibration[i][3] << "\n";
            double spanInch = receivedToInches(1,spanCalibration[i][3]);
            tempData.push_back(spanInch);
            //std::cout << "Span: "<< spanInch << "\n";
            spanCalMap.insert({spanCalibration[i][0], tempData});
            //inches = (dataInBits - spanIntercept - spanZeroPoint) / spanSlope;
        }

        std::vector<std::vector<double>> zeroData = readFiles("PotZeroVals.txt");
        for (int i = 0; i < zeroData.size(); i ++) {
            zeroMap.push_back(std::vector <double> ());
            zeroMap[i].push_back(i);
            zeroMap[i].push_back(zeroData[i][1]);
        }
        zeroVol = zeroMap[0][1];
        if(zeroVol < 0) {
            zeroVol = 0;
        }
        spanCommand(1,totSpan, 0);
    }

    if (spanCalibration2.size() > 1) {
        for (int i = 0; i < spanCalibration2.size(); i++) {
            std::vector<double> tempData;
            for (int j = 1; j < spanCalibration2[i].size(); j++) {
                tempData.push_back(spanCalibration2[i][j]);
            }
            spanSlope2 = spanCalibration2[i][1];
            spanIntercept2 = spanCalibration2[i][2];
            //std::cout << "SpanTest: "<< spanCalibration[i][3] << "\n";
            double spanInch = receivedToInches(2,spanCalibration2[i][3]);
            tempData.push_back(spanInch);
            //std::cout << "Span: "<< spanInch << "\n";
            spanCalMap2.insert({spanCalibration2[i][0], tempData});
            //inches = (dataInBits - spanIntercept - spanZeroPoint) / spanSlope;
        }

        std::vector<std::vector<double>> zeroData2 = readFiles("PotZeroVals2.txt");
        for (int i = 0; i < zeroData2.size(); i ++) {
            zeroMap2.push_back(std::vector <double> ());
            zeroMap2[i].push_back(i);
            zeroMap2[i].push_back(zeroData2[i][1]);
        }
        zeroVol2 = zeroMap2[0][1];
        if(zeroVol2 < 0) {
            zeroVol2 = 0;
        }
        std::cout << "Sending to Controller 2: "<< totSpan2 << "\n";
        spanCommand(2,totSpan2, 0);
    }

}

int initializeLoad() {
    setbuf(stdout, NULL); // NetBeans hack: disable buffering on stdout
    wiringPiSetup();
    wiringPiSPISetup(1, SPI_CLOCK); // Set SPI clock
    wiringPiSPISetup(0, SPI_CLOCK); // Set SPI clock

}

void hsm_full::calLoadCell(int channel, int value) {
    serialWrite(3, channel, value);
}

double hsm_full::returnLoad(int channel) {
    readForce(channel);
    double retForce;
    if (channel == 0) {
        retForce = received_Force;
    } else {
        retForce = received_Force2;
    }
    return retForce;
}

void hsm_full::setMaxDisp(int channel, double Disp) {
    if (channel == 0) {
        maxDisp = Disp;
    } else if (channel == 1) {
        maxDisp2 = Disp;
    }
}

void hsm_full::setMinDisp(int channel, double Disp) {
    if (channel == 0) {
        minDisp = Disp;
    } else if (channel == 1) {
        minDisp2 = Disp;
    }
}

void hsm_full::setMaxForce(int channel, double Force) {
    if (channel == 0) {
        maxForce = Force;
    } else if (channel == 1) {
        maxForce2 = Force;
    }
}

void hsm_full::setMinForce(int channel, double Force) {
    if (channel == 0) {
        minForce = Force;
    } else if (channel == 1) {
        minForce2 = Force;
    }
}

void hsm_full::checkInterlock() {
    if ((received_Disp > maxDisp)) {
        maxSpanInterlock = true;
    } if(received_Disp < minDisp) {
        minSpanInterlock = true;
    } if (received_Force > maxForce) {
        maxForceInterlock = true;
    } if (received_Force < minForce) {
        minForceInterlock = true;
    }

    if ((received_Disp2 > maxDisp2)) {
        maxSpanInterlock2 = true;
    } if(received_Disp2 < minDisp2) {
        minSpanInterlock2 = true;
    } if (received_Force2 > maxForce2) {
        //std::cout << "Interlock Tripped, Received Force was: " << received_Force2 << "but max Force is: " << maxForce2 << "\n";
        maxForceInterlock2 = true;
    } if (received_Force2 < minForce2) {
        minForceInterlock2 = true;
    }



}

void hsm_full::resetInterlock(int channel, int whichInterlock) {
    if (channel == 0) {
        if (whichInterlock == 0) {
            maxSpanInterlock = false;
        } else if (whichInterlock == 1) {
            minSpanInterlock = false;
        } else if (whichInterlock == 2) {
            maxForceInterlock = false;
        } else if (whichInterlock == 3) {
            minForceInterlock = false;
        }
    }
    if (channel == 1) {
        if (whichInterlock == 0) {
            maxSpanInterlock2 = false;
        } else if (whichInterlock == 1) {
            minSpanInterlock2 = false;
        } else if (whichInterlock == 2) {
            maxForceInterlock2 = false;
        } else if (whichInterlock == 3) {
            minForceInterlock2 = false;
        }
    }
    if (channel == 2) {
        eStopActive = false;
    }
}

int hsm_full::isInterlockOn(int channel, int whichInterlock) {
    int returnBool = 0;
    if (channel == 0) {
        if (whichInterlock == 0 && maxSpanInterlock == true) {
            returnBool = 1;
        } else if (whichInterlock == 1 && minSpanInterlock == true) {
            returnBool = 1;
        } else if (whichInterlock == 2 && maxForceInterlock == true) {
            returnBool = 1;
        } else if (whichInterlock == 3 && minForceInterlock == true) {
            returnBool = 1;
        }
    }
    if (channel == 1) {
        if (whichInterlock == 0 && maxSpanInterlock2 == true) {
            returnBool = 1;
        } else if (whichInterlock == 1 && minSpanInterlock2 == true) {
            returnBool = 1;
        } else if (whichInterlock == 2 && maxForceInterlock2 == true) {
            returnBool = 1;
        } else if (whichInterlock == 3 && minForceInterlock2 == true) {
            returnBool = 1;
        }
    }
    if (channel == 2 && eStopActive == true) {
        returnBool = 1;
    }
    return returnBool;
}

void hsm_full::clearPlotVectors() {
    qDebug("clearing plot");
    gettimeofday(&runtv, NULL);
    runtime_in_mill = runtv.tv_usec;
    runtime_initial = runtv.tv_sec + runtime_in_mill/1000000.0;
    runtime_in_s = 0;
    Xdata.clear();
    XCommand.clear();
    XForceCommand.clear();
    Ydata.clear();
    YCommand.clear();
    YForceCommand.clear();
    XdataAct2.clear();
    XCommandAct2.clear();
    XForceCommandAct2.clear();
    YdataAct2.clear();
    YCommandAct2.clear();
    YForceCommandAct2.clear();
    loadCellData1.clear();
    loadCellData2.clear();
    HystDisp1.clear();
    HystDisp2.clear();
    //ui->qwtPlot->detachItems(false);
    ui->qwtPlot->detachItems(QwtPlotItem::Rtti_PlotCurve,false);
    ui->qwtPlot_2->detachItems(QwtPlotItem::Rtti_PlotCurve,false);
    curve1->setData(NULL);
    curve2->setData(NULL);
    curve3->setData(NULL);
    curve4->setData(NULL);
    curve5->setData(NULL);
    curve10->setData(NULL);
    curve11->setData(NULL);
    curve12->setData(NULL);
    curve1->attach(ui->qwtPlot);
    curve2->attach(ui->qwtPlot);
    curve3->attach(ui->qwtPlot);
    curve4->attach(ui->qwtPlot_2);
    curve5->attach(ui->qwtPlot_2);
    curve10->attach(ui->qwtPlot);
    curve11->attach(ui->qwtPlot_2);
    curve12->attach(ui->qwtPlot_2);
    ui->qwtPlot->setAxisAutoScale(QwtPlot::yLeft,true);
    runaxlim = 10;
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom,0,runaxlim);
    runaxlimLoad = 60;
    ui->qwtPlot_2->setAxisScale(QwtPlot::xBottom,0,runaxlimLoad);
    ui->qwtPlot->replot();
    ui->qwtPlot->repaint();
    ui->qwtPlot_2->replot();
    ui->qwtPlot_2->repaint();
}


int hsm_full::loadModel() {
    Py_Initialize();
    import_array();
    PyObject *sysPath = PySys_GetObject((char*)"path");
    PyList_Append(sysPath,PyUnicode_FromString("/home/jim53/Desktop/RpiHSM/HSM_Full/"));  // path to the module to import
    LoadModelName = PyUnicode_FromString("Model_Setup");

    //build python matrices
    LoadModelMethod = PyImport_Import(LoadModelName);
    LoadModelArgs = PyTuple_New (1);
    std::cout << "Setting Arguments\n";
    PyTuple_SetItem(LoadModelArgs, 0, PyUnicode_FromString("ModelFile.dat"));

    if (LoadModelMethod != NULL) {

        LoadModelFunc = PyObject_GetAttrString(LoadModelMethod, "modelLoad");
        if (LoadModelFunc && PyCallable_Check(LoadModelFunc)) {
            std::cout << "Loading Model \n";
            LoadModelOut = PyObject_CallObject(LoadModelFunc, LoadModelArgs);
            if (LoadModelOut != NULL) {
                Model = PyTuple_GetItem(LoadModelOut,0);
                el = PyTuple_GetItem(LoadModelOut,1);
                printf("Value returned from the function\n");
                return 0;
            } else {
                printf("Error, No output from method");
                PyErr_Print();
                return -1;
            }
        } else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function %s\n", LoadModelFunc);
            return -1;
        }
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load %s\n", LoadModelMethod);
        return -1;
    }
}

int hsm_full::saveModel() {
    Py_Initialize();
    import_array();
    PyObject *sysPath = PySys_GetObject((char*)"path");
    PyList_Append(sysPath,PyUnicode_FromString("/home/jim53/Desktop/RpiHSM/HSM_Full/"));  // path to the module to import
    SaveModelName = PyUnicode_FromString("Model_Setup");

    //build python matrices
    SaveModelMethod = PyImport_Import(SaveModelName);
    SaveModelArgs = PyTuple_New (2);
    std::cout << "Setting Arguments\n";
    PyTuple_SetItem(SaveModelArgs, 0, Model);
    PyTuple_SetItem(SaveModelArgs, 1, el);

    if (SaveModelMethod != NULL) {

        SaveModelFunc = PyObject_GetAttrString(SaveModelMethod, "saveModel");
        if (SaveModelFunc && PyCallable_Check(SaveModelFunc)) {
            std::cout << "Saving Model \n";
            SaveModelOut = PyObject_CallObject(SaveModelFunc, SaveModelArgs);

        } else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function %s\n", SaveModelFunc);
            return -1;
        }
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load %s\n", SaveModelMethod);
        return -1;
    }
}

void hsm_full::loadActuators() {
    ActuatorSelections = readFiles("PickActuators.txt");
    numControlDOFS = 0;
    if (!ActuatorSelections.empty()){
        std::cout << "Actuators Selected. \nHybrid DOF 1: Actuator " << (int) ActuatorSelections[0][0] << "\n" << "Hybrid DOF 2: Actuator " << (int) ActuatorSelections[0][1] << "\n";
    }
    if (ActuatorSelections[0][0] != 0) {
        numControlDOFS += 1;
    }
    if (ActuatorSelections[0][1] != 0) {
        numControlDOFS += 1;
    }
    std::cout << "Number of Control Dofs" << numControlDOFS << "\n";
}

double hsm_full::getForce() {
    readForce(0);
    return received_Force;
}

double hsm_full::getForce2() {
    readForce(1);
    return received_Force2;
}

//I think this is a legacy function?
/*void readDisp(){
    //d1 = (expi.adc_read_raw(2,0)-1650.0-zeroDisp)*span/1650.0;
    //d2 = (expi.adc_read_raw(2,0)-1650.0-zeroDisp)*span/1650.0;
    //d3 = (expi.adc_read_raw(2,0)-1650.0-zeroDisp)*span/1650.0;
    d1 = 0;
    d2 = 0;
    d3 = 0;
    received_Disp=w*dprev+(1-w)*(d1+d2+d3)/3;
    //force_bits = expi.adc_read_raw(1,0);
    dprev = received_Disp;
    //qDebug("%d",force_bits);
}*/

void hsm_full::initializeController(int channel) {
    command = 1;
    double Kp = serialRead(channel,command,2) * Pmax/4095;
    command = 1;
    double Ki = serialRead(channel,command,2) * Imax/4095;
    command = 1;
    double Kd = serialRead(channel,command,2) * Dmax/4095;
    command = 1;
    double KpF = serialRead(channel,command,2) * Pmax/4095;
    command = 1;
    double KiF = serialRead(channel,command,2) * Imax/4095;
    command = 1;
    double KdF = serialRead(channel,command,2) * Dmax/4095;
    command = 1;
    bool FC = serialRead(channel,command,2);


    if (channel ==1) {
        if (FC == 0) {
            CT1 = 0;
        } else if (FC == 1) {
            CT1 = 1;
        }
        if (CT1 == 0) {
            ui->ControlText->setText("Disp Control");
            ui->SwitchControlButton->setText("Switch to Force Control");
        } else if (CT1 == 1){
            ui->SwitchControlButton->setText("Switch to Disp Control");
            ui->ControlText->setText("Force Control");
        }
        ui->PInputDisp->setValue(Kp);
        ui->IInputDisp->setValue(Ki);
        ui->DInputDisp->setValue(Kd);
        ui->PInputForce->setValue(KpF);
        ui->IInputForce->setValue(KiF);
        ui->DInputForce->setValue(KdF);
    }

    if (channel ==2) {
        if (FC == 0) {
            CT2 = 0;
        } else if (FC == 1) {
            CT2 = 1;
        }
        if (CT2 == 0) {
            ui->ControlText_2->setText("Disp Control");
            ui->SwitchControlButton_2->setText("Switch to Force Control");
        } else if (CT1 == 1){
            ui->SwitchControlButton_2->setText("Switch to Disp Control");
            ui->ControlText_2->setText("Force Control");
        }
        ui->PInputDisp2->setValue(Kp);
        ui->IInputDisp2->setValue(Ki);
        ui->DInputDisp2->setValue(Kd);
        ui->PInputForce2->setValue(KpF);
        ui->IInputForce2->setValue(KiF);
        ui->DInputForce2->setValue(KdF);
    }
}

void hsm_full::saveForceSlopes(){
    ForceSlopes.open("forceSlopes.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Force Slopes x\n");
    ForceSlopes << forceSlope << "," << forceSlope2 << "\n";
    ForceSlopes << zeroForce << "," << zeroForce2 << "\n";
    ForceSlopes << LC1Offset << "," << LC2Offset << "\n";
    ForceSlopes << LC1Zero << "," << LC2Zero << "\n";
    ForceSlopes.close();
}

void hsm_full::saveInterlocks(){
    Interlocks.open("Interlocks.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Interlocks x\n");
    Interlocks << maxDisp << "," << maxDisp2 << "\n";
    Interlocks << minDisp << "," << minDisp2 << "\n";
    Interlocks << maxForce << "," << maxForce2 << "\n";
    Interlocks << minForce << "," << minForce2 << "\n";
    Interlocks.close();
}

void hsm_full::setPlotScale() {
    actOneDispScale = ui->Act1DispScale->value();
    actOneForceScale = ui->Act1ForceScale->value();
    actTwoDispScale = ui->Act2DispScale->value();
    actTwoForceScale = ui->Act2ForceScale->value();
    clearPlotVectors();
    saveScaleData();
}

void hsm_full::setLCData() {
    forceSlope = ui->Act1LCSlope->value();
    forceSlope2 = ui->Act2LCSlope->value();
    LC1Max = ui->Act1MaxLC->value();
    LC2Max = ui->Act2MaxLC->value();
    saveLCData();
}

void hsm_full::saveLCData() {
    LCData.open("LCData.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Force Slopes x\n");
    LCData << forceSlope << "," << forceSlope2 << "\n";
    LCData << zeroForce << "," << zeroForce2 << "\n";
    LCData << LC1Max << "," << LC2Max << "\n";
    LCData.close();
}


void hsm_full::saveScaleData() {
    ScaleData.open("Scale.txt",std::ofstream::out | std::ofstream::trunc);
    ScaleData << actOneDispScale << "," << actOneForceScale << "\n";
    ScaleData << actTwoDispScale << "," << actTwoDispScale << "\n";
    ScaleData.close();
}

double hsm_full::getActOneDispScale() {
    return actOneDispScale;
}

double hsm_full::getActTwoDispScale(){
    return actTwoDispScale;
}

double hsm_full::getActOneForceScale() {
    return actOneForceScale;
}

double hsm_full::getActTwoForceScale() {
    return actTwoForceScale;
}

double hsm_full::getMaxSpan() {
    std::cout <<"Sending: " << maxDisp << "\n";
    return maxDisp;
}
double hsm_full::getMaxSpan2() {
    return maxDisp2;
}
double hsm_full::getMinSpan() {
    return minDisp;
}
double hsm_full::getMinSpan2() {
    return minDisp2;
}
double hsm_full::getMaxForce() {
    return maxForce;
}
double hsm_full::getMaxForce2() {
    return maxForce2;
}
double hsm_full::getMinForce() {
    return minForce;
}
double hsm_full::getMinForce2() {
    return minForce2;
}
double hsm_full::getDispCommand() {
    return dispCommand;
}
double hsm_full::getDispCommand2() {
    return dispCommand2;
}
double hsm_full::getForceCommand() {
    return forceCommand;
}
double hsm_full::getForceCommand2() {
    return forceCommand2;
}
int hsm_full::getControlType() {
    return CT1;
}
int hsm_full::getControlType2() {
    return CT2;
}
