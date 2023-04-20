#include "hsm_full.h"
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

//variables for sending and receiving over serial
int numToSend;
bool recvInProgress = false;

PyObject *u_p, *udot_p, *uddot_p, *f_p, *eq_p, *dt,*iter;
PyObject *pythonArgument;
PyObject *pName, *pName2, *pModule,*pModule2, *pDict, *pFunc,*pFunc2;
PyObject *pArgs, *x_next,*x_next2, *InitIntArgs, *Model2;
PyObject *PlotResultsName, *PlotResultsMethod, *PlotResultsFunc;
PyObject *PlotResultsArgs, *PlotResultsOut;


using namespace ABElectronics_CPP_Libraries;

std::ifstream EQ("/home/pi/Desktop/HSM_Full/HSM_Full/El_Centro_interp.txt");
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

bool running = 0;
int plotcount = 0;
pthread_mutex_t trigger_mutex;
pthread_mutex_t race_mutex;
pthread_cond_t trigger;//triggers the time integrator


std::ofstream output;
std::ofstream output2;
std::ofstream output3;
std::ofstream sentCom;
std::ofstream recDisp;
std::ofstream DispT;
std::ofstream CommandT;
std::ofstream runningCommand;
std::ofstream runningTime;
std::ofstream runningFeedback;
std::ofstream controlLoops;
std::ofstream signalLoopTime;
std::ofstream integratorIndex;
std::ofstream calcVelocity;
std::ofstream calcAcc;
std::ofstream SinCommandFile;
std::ofstream SinResponseFile;
std::ofstream SinForceFile;
std::ofstream SinTimeFile;

double EQdata;
std::vector<double> EQ_h{0};
std::vector<double> xn{0};
std::vector<double> xd{0};
std::vector<double> xdd{0};
std::vector<double> xt{0};
std::vector<double> xdt{0};
std::vector<double> xddt{0};
std::vector<double> time_delay{0};
std::vector<double> oof{0};
std::vector<double> force{0};
std::vector<double> sinWave{0};
std::vector<double> sinCommand{0};
std::vector<double> sinResponse{0};
std::vector<double> sinForce{0};
std::vector<double> sinTime{0};


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
double xp = 0.0;
double xdp;
double xddp;
double eqp;
double fp = 0.0;
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
double vel = .1;
double sigt = .01; //time between signals
double dx;
double cur_x;
double nsteps = 0.0;
double span = 5.5;
int feedback;
int zeroPoint = 2092;
int ogZero;
double zeroPoint_in;
double f1;
double f2;
double f3;
double d1;
double d2;
double d3;
uint16_t data_to_send;
uint16_t command;
//int fd;
int received_data;
double dispCommand =0.0;
double PCommand = .5;
double ICommand = .0001;
double DCommand = 0;
double slideCommand;
double received_Force;
double received_Disp;
bool sliderActive = 0;
double Pmax = 5;
double Imax = .001;
double Dmax = 5;
double maxspan = 5.5;
int controlcount = 0;
bool commandPlotting = 1;
int i2ctest;
double last_recieved;
uint16_t hibyte;
uint16_t lobyte;
double relative_Disp;
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
std::vector<double> CommandVec{0};
std::vector<double> DispVec{0};
std::vector<double> CommandTime{0};
std::vector<double> DispTime{0};
std::vector<double> loops;
std::vector<double> signalLoops;
std::vector<double> runCommand(10000,0);
std::vector<double> runTime(10000,0);
std::vector<double> runFeedback(10000,0);
std::vector<double> stiffnessvec;
std::vector<double> stiffdispvec;
std::vector<int> intIndex = {};
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
int sendZero;
int zeroDisp;
static int gil_init = 0;
PyObject *python_return;
int controller = 0;
double hybStiff;
int continuous = 1;
bool pinActive = 0;
int SerialDisp;
int fd;
int fd2;
int serialRead();
char received[4];
int numReceived;
unsigned char sendData[4];
int crcReceived;
unsigned char recData[2];

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
static void const_vel();
static void wait_rest_of_period(struct period_info *pinfo);
void readForce();
void readDisp();
static void Call_Integrator();
int serialRead();



void *simple_cyclic_task(void* plotter) //This runs a cyclic task in which
                                     // we perform the prediction and correction
{
        qDebug("test1");
        struct period_info pinfo;

        periodic_task_init(&pinfo);
        hsm_full* plot_obj = (hsm_full*)plotter;
        running = 1;
        if (sinOn ==0){
            int i = 0;
            qDebug("%d",EQ_h.size());

            while (intcount < GM.size()-1 && running == 1) {
                gettimeofday(&signaltv, NULL);
                loop_in_mill_beg = signaltv.tv_usec;
                loop_in_s_beg = signaltv.tv_sec + loop_in_mill_beg/1000000.0;

                if(cv == 0){
                    do_pred_cor();
                }
                else{
                    //printf("Constant Vel");
                    const_vel();
                }
                    //qDebug("%d",i);
                    i = i+1;
                    feedback = 0;
                    //printf("%d\n",feedback);
                    //printf("Trying to plot:%f\n",xt[gcount-1]);
                    /*if (microcont == 1){
                    i2ctest = wiringPiI2CReadReg16(fd,0x00);
                    if (i2ctest == -1){
                        while (i2ctest ==-1){
                            i2ctest = wiringPiI2CReadReg16(fd,0x00);

                        }
                    }
                    ddisp = (((double)i2ctest)-2048)*2*span/4095.0-((ogZero-2048)*2*span/4095)-prevdisp;
                    while(abs(ddisp)>1){
                        i2ctest = wiringPiI2CReadReg16(fd,0x00);
                        ddisp = (((double)i2ctest)-2048)*2*span/4095.0-((ogZero-2048)*2*span/4095)-prevdisp;
                    }

                    received_Disp = (((double)i2ctest)-2048)*2*span/4095.0-((ogZero-2048)*2*span/4095);

                    }else if(microcont == 2){
                        i2ctest = wiringPiI2CReadReg16(fd,0x00);
                        if (i2ctest == -1){
                            while (i2ctest ==-1){
                                i2ctest = wiringPiI2CReadReg16(fd,0x00);

                            }
                        }

                        received_Disp = (((double)i2ctest)-512)*2*span/1023.0-((ogZero-1023)*2*span/1023);

                    }else{
                        readDisp();
                        //received_Disp = (expi.adc_read_raw(2,0)-1650.0)*span/1650.0;
                    }*/

                    plot_obj->Xdata.append((double) time_in_s1);
                    DispTime.push_back((double) time_in_s1);
                    if ((received_Disp<span) && (received_Disp>-span)){
                        relative_Disp = received_Disp-zeroPoint_in;
                        plot_obj->Ydata.append((double) relative_Disp);
                        last_recieved = received_Disp;

                    }
                    else{
                        relative_Disp = last_recieved-zeroPoint_in;
                        plot_obj->Ydata.append((double) relative_Disp);
                    }
                    DispVec.push_back(relative_Disp);
                    plot_obj->Ydata2.append((double) xt[gcount-1]);
                    CommandVec.push_back((double) xt[gcount-1]);
                    //qDebug("%f",xt[gcount-1]);
                    gettimeofday(&tv, NULL);
                    time_in_mill1 = tv.tv_usec;
                    time_in_s1 = tv.tv_sec + time_in_mill1/1000000.0-time_initial;
                    plot_obj->Xdata2.append((double) time_in_s1);
                    CommandTime.push_back((double) time_in_s1);
                    if (time_in_s1>=axlim){

                        setlim = 1;

                    }
                    gettimeofday(&signaltv, NULL);
                    loop_in_mill_end = signaltv.tv_usec;
                    loop_in_s_end = signaltv.tv_sec + loop_in_mill_end/1000000.0;
                    signalLoops.push_back(loop_in_s_end-loop_in_s_beg);
                    wait_rest_of_period(&pinfo);

                    //plot_obj->updatePlot();
            }
            plot_obj->Xdata = {};
            plot_obj->Ydata = {};
            plot_obj->Xdata2 = {};
            plot_obj->Ydata2 = {};
            qDebug("done");
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

            while (sinOn == 1 && running == 1) {
                gettimeofday(&signaltv, NULL);
                loop_in_mill_beg = signaltv.tv_usec;
                loop_in_s_beg = signaltv.tv_sec + time_in_mill1/1000000.0;
                pthread_mutex_lock(&race_mutex);
                gettimeofday(&tv, NULL);
                time_in_mill1 = tv.tv_usec;
                time_in_s1 = tv.tv_sec + time_in_mill1/1000000.0-time_initial;

                plot_obj->Ydata2.append((double) sinWave[i]);
                plot_obj->Xdata2.append((double) time_in_s1);
                plot_obj->Xdata.append((double) time_in_s1);

                readForce();
                received_Disp = (((double)serialRead())-2048.0)*2*span/4095.0;//-((ogZero-2048.0)*2*span/4095.0)
                //received_Disp = 0;
                //force.push_back(-received_Force);
                //CommandVec.push_back((double) sinWave[i]);
                //CommandTime.push_back((double) time_in_s1);
                //DispTime.push_back((double) time_in_s1);
                /*if(microcont == 1){
                    i2ctest = wiringPiI2CReadReg16(fd,0x00);
                    //qDebug("%d",i2ctest);
                    if (i2ctest == -1){
                        while (i2ctest ==-1){
                            qDebug("error");
                            i2ctest = wiringPiI2CReadReg16(fd,0x00);
                        }
                    }
                    /*ddisp = (((double)i2ctest)-2048)*2*span/4095.0-((ogZero-2048)*2*span/4095)-prevdisp;
                    while(abs(ddisp)>1){
                        i2ctest = wiringPiI2CReadReg16(fd,0x00);
                        ddisp = (((double)i2ctest)-2048)*2*span/4095.0-((ogZero-2048)*2*span/4095)-prevdisp;
                    }
                    received_Disp = (((double)i2ctest)-2048.0)*2*span/4095.0-((ogZero-2048.0)*2*span/4095.0);
                }else if(microcont == 2){
                    i2ctest = wiringPiI2CReadReg16(fd,0x00);
                    if (i2ctest == -1){
                        while (i2ctest ==-1){
                            i2ctest = wiringPiI2CReadReg16(fd,0x00);

                        }
                    }

                    received_Disp = (((double)i2ctest)-512)*2*span/1023.0-((ogZero-1023)*2*span/1023);
                 }
                else{
                    readDisp();
                    //received_Disp = (expi.adc_read_raw(2,0)-1650.0)*span/1650.0;
                }*/
                //qDebug("%f",received_Disp);

                if ((received_Disp<span) && (received_Disp>-span)){
                    relative_Disp = received_Disp-zeroPoint_in;
                    plot_obj->Ydata.append((double) relative_Disp);
                    last_recieved = received_Disp;

                }
                else{
                    relative_Disp = last_recieved-zeroPoint_in;              
                    plot_obj->Ydata.append((double) relative_Disp);
                }
                DispVec.push_back((double) relative_Disp);

                if(i<sinWave.size()-1){
                   i = i+1;
                }else{
                   i = 0;
                }

                j = j+1;
                //qDebug("%f",time_in_s1);
                if (time_in_s1>=axlim){

                    setlim = 1;

                }

                //qDebug("%d",sinVal);
                //plotcount = plotcount+1;
                /*if (microcont == 1){
                    sinVal = std::min(4095.0,round(4095/(2*span)*sinWave[i]+2048)+(ogZero-2048));
                    command = 0;
                    command = command<<10;
                    data_to_send = sinVal;
                    data_to_send = data_to_send | command;
                    wiringPiI2CWriteReg16(fd,0x00,data_to_send);
                }else if(microcont == 2){
                    i2ctest = wiringPiI2CReadReg16(fd,0x00);
                    if (i2ctest == -1){
                        while (i2ctest ==-1){
                            i2ctest = wiringPiI2CReadReg16(fd,0x00);
                        }
                    }

                    received_Disp = (((double)i2ctest)-512)*2*span/1023.0-((ogZero-1023)*2*span/1023);
                 }
                else{
                    sinVal = std::min(3300.0,round((sinWave[i]+span)*3300.0/(2*span))+(sendZero-1650));
                    //expi.dac_set_raw(sinVal,2,2);
                    qDebug("%d",sinVal);
                }*/

                sinCommand.push_back(sinWave[i]);
                sinResponse.push_back(received_Disp);
                sinForce.push_back(-received_Force);
                sinTime.push_back((double) time_in_s1);

                //gettimeofday(&tv, NULL);
                //time_in_mill2 = tv.tv_usec;
                //time_in_s2 = tv.tv_sec + time_in_mill2/1000000.0;
                //double delay = time_in_s2-time_in_s1;
                //qDebug("%f",delay);
                pthread_mutex_unlock(&race_mutex);




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

static void const_vel()
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
        if (nsteps == 0){
            cur_x = cur_x;
        }else{
            cur_x = cur_x+dx/nsteps;
        }
        xt.push_back(cur_x);
        intIndex.push_back(gcount);
        gcount++;
        printf("Sending signal\n");
        pthread_mutex_lock(&race_mutex);
        //df = K * (xn[intcount] -xp);
        xp = xn[intcount];
        eqp = GM[intcount];
        //fp = f_prev+df;
        readForce();
        fp = -received_Force;
        //fp = 3.3* xp;


        count = 0;
        intcount++;
        Cor = 0;
        done = 0;
        pthread_mutex_unlock(&race_mutex);
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
        force.push_back(fp);
    }else if(count!=ceil(nsteps)){
        cur_x = cur_x+dx/nsteps;
        xt.push_back(cur_x);
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
                df = K * (xn[intcount] -xp);
                xp = xn[intcount];
                printf("%f\n",xp);
                xdp = xd[intcount];
                xddp = xdd[intcount];
                eqp = EQ_h[intcount];

                fp = f_prev+df;

                if (fp>fy){
                        fp = fy;
                }if(fp<-fy){
                        fp = -fy;
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

        dp_last = xn[intcount-1];

        if(Cor == 0){

                if(intcount>3){
                        xlag = (count)/10.0;
                        P0 = 1.0/6.0 * (xlag+1.0)*(xlag+2.0)*(xlag+3.0);
                        Pn1 = -1.0/2.0 * xlag*(xlag+2.0)*(xlag+3.0);
                        Pn2 = 1.0/2.0 * xlag*(xlag+1.0)*(xlag+3.0);
                        Pn3 = -1.0/6.0*xlag*(xlag+1.0)*(xlag+2.0);


                        pthread_mutex_unlock(&race_mutex);
                        xt.push_back(P0*xn[intcount-1]+Pn1*xn[intcount-2]+Pn2*xn[intcount-3]+Pn3*xn[intcount-4]);
                        dp_last = P0*xn[intcount-1]+Pn1*xn[intcount-2]+Pn2*xn[intcount-3]+Pn3*xn[intcount-4];
                        pthread_mutex_unlock(&race_mutex);
                        pcount_last = xlag;
                }else{
                        pthread_mutex_lock(&race_mutex);
                        xt.push_back(0);
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
                        xt.push_back(Cp1*xn[intcount]+C0*xn[intcount-1]+Cn1*xn[intcount-2]+Cn2*xn[intcount-3]);
                        pthread_mutex_unlock(&race_mutex);
                        //printf("%f\n",Cn2);
                }else{
                        pthread_mutex_lock(&race_mutex);
                        xt.push_back(0);
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
        double *GMmem = &GM[0];
        PyGM = PyArray_SimpleNewFromData(1,GM_dim,NPY_DOUBLE,(double*)GMmem);
        while(intcount < GM.size()-1) {
                //PyGILState_STATE state = PyGILState_Ensure();
                printf("%d\n",intcount);
                //printf("waiting\n");
                pthread_cond_wait(&trigger,&trigger_mutex);
                qDebug("Force:%f",fp);
                printf("IntCount: %d\n",intcount);
                //values sent to the integrator
                //printf("%f\n",xp);
                //printf("%f\n",fp);
                //printf("%d\n",intcount);
                //u_p = PyFloat_FromDouble(xp);
                f_p = PyFloat_FromDouble(fp);
                iter = PyLong_FromLong(intcount);


                pythonArgument = PyTuple_New(4);
                PyTuple_SetItem(pythonArgument, 0, Model);
                PyTuple_SetItem(pythonArgument, 1, f_p);
                PyTuple_SetItem(pythonArgument, 2, PyGM);
                PyTuple_SetItem(pythonArgument, 3, iter);


                if (pModule != NULL) {
                           if (pFunc2 && PyCallable_Check(pFunc2)) {
                                   x_next2 = PyObject_CallObject(pFunc2, pythonArgument);
                                   if (x_next2 != NULL) {
                                       Model = PyTuple_GetItem(x_next2,0);
                                       printf("%f",PyFloat_AsDouble(PyTuple_GetItem(x_next2,1)));
                                       xn.push_back(PyFloat_AsDouble(PyTuple_GetItem(x_next2,1)));
                                       xd.push_back(PyFloat_AsDouble(PyTuple_GetItem(x_next2,2)));
                                       xdd.push_back(PyFloat_AsDouble(PyTuple_GetItem(x_next2,3)));
                                       if(cv ==1){
                                           dx = PyFloat_AsDouble(PyTuple_GetItem(x_next2,1))-cur_x;
                                           nsteps = abs(dx)/(vel*sigt);
                                           printf("%f\n",dx);
                                           printf("%f\n",nsteps);
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
    wiringPiSetup();			// Setup the library
    pinMode(7, OUTPUT);
    digitalWrite(0, pinActive);
    setvbuf (stdout, NULL, _IONBF, 0);
    ui->setupUi(this);

    if((fd=serialOpen("/dev/serial0",2000000))<0){
      qDebug("Unable to open serial device: %s\n",strerror(errno));
    }
    //if((fd2=serialOpen("/dev/serial/by-id/usb-Teensyduino_USB_Serial_10336750-if00",115200))<0){
    //  qDebug("Unable to open serial device: %s\n",strerror(errno));
    //}

    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&hsm_full::updateLCD);
    timer->start(100);\
    if(logcontrolloops == 1){
        timer2 = new QTimer(this);
        connect(timer2,&QTimer::timeout,this,&hsm_full::reqloops);
        timer2->start(1000);
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


    qDebug("%d",serialRead());

   gettimeofday(&runtv, NULL);
   runtime_in_mill = runtv.tv_usec;
   runtime_initial = runtv.tv_sec + runtime_in_mill/1000000.0;
   //expi.adc_open();
   calForce();
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
    qDebug("%d",zeroPoint);

    QWidget *wdg = new QWidget;
    ui->IDisp->setPalette(Qt::black);
    ui->Offset->display(zeroPoint_in);
    ui->PDisp->display(PCommand);
    ui->IDisp->display(ICommand);
    ui->DDisp->display(DCommand);
    ui->CurSpan->display(span);
    index = 0;
    m_button = new QPushButton("Start Button",this);
    m_button->setGeometry(QRect(QPoint(30, 250), QSize(99, 30)));
    n_button = new QPushButton("Stiffness Test",this);
    n_button->setGeometry(QRect(QPoint(180, 250), QSize(99, 30)));
    s_button = new QPushButton("Save",this);
    s_button->setGeometry(QRect(QPoint(330, 250), QSize(99, 30)));


    connect(m_button, &QPushButton::released, this, &hsm_full::update);
    connect(n_button, &QPushButton::released, this, &hsm_full::stiffTest);
    connect(s_button, &QPushButton::released, this, &hsm_full::save);

    //wiringPiSetup();
    //pinMode(21,OUTPUT);
    //digitalWrite(21,HIGH);

    connect(ui->CommandButton,&QPushButton::released,this,&hsm_full::sendCommand);
    connect(ui->PButton,&QPushButton::released,this,&hsm_full::sendP);
    connect(ui->IButton,&QPushButton::released,this,&hsm_full::sendI);
    connect(ui->DButton,&QPushButton::released,this,&hsm_full::sendD);
    connect(ui->horizontalSlider,&QSlider::sliderReleased,this,&hsm_full::sliderCommand);
    connect(ui->SliderButton,&QPushButton::released,this,&hsm_full::activateButton);
    connect(ui->SpanButton,&QPushButton::released,this,&hsm_full::spanCommand);
    connect(ui->zeroButton,&QPushButton::released,this,&hsm_full::setZero);
    connect(ui->AmpButton,&QPushButton::released,this,&hsm_full::setAmp);
    connect(ui->FreqButton,&QPushButton::released,this,&hsm_full::setFreq);
    connect(ui->SinButton,&QPushButton::released,this,&hsm_full::sinTest);
    connect(ui->SweepButton,&QPushButton::released,this,&hsm_full::sweep);
    connect(ui->fZeroButton,&QPushButton::released,this,&hsm_full::calForce);
    connect(ui->PSASButton,&QPushButton::released,this,&hsm_full::PSAS_Window);
    connect(ui->StartControl,&QPushButton::released,this,&hsm_full::startControl);
    connect(ui->plotResults,&QPushButton::released,this,&hsm_full::plotResults);
    connect(ui->AmpTestButton,&QPushButton::released,this,&hsm_full::ampTest);
    connect(ui->PinButton,&QPushButton::released,this,&hsm_full::activatePin);

    ui->qwtPlot->setAxisScale(QwtPlot::xBottom,0,runaxlim);
    ui->qwtPlot->setAxisAutoScale(QwtPlot::yLeft,true);


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
    xt = {0};
    force = {0};
    Xdata = {};
    Xdata2 = {};
    Ydata = {};
    Ydata2 = {};
    xn = {0};
    xd ={0};
    xdd = {};
    xt = {0};
    xdt = {0};
    xddt = {};
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
    PyList_Append(sysPath,PyUnicode_FromString("/home/jim53/Desktop/HSM_Full"));
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
                        xdd.push_back(PyFloat_AsDouble(PyTuple_GetItem(x_next,1)));
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
    ui->qwtPlot->setAxisAutoScale(QwtPlot::xBottom,false);
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom,0,axlim);
    ui->qwtPlot->detachItems();
    running = 1;
    while(running == true){
        plotcount = plotcount+1;
        if (plotcount%1000000 == 0){
            //qDebug("Hello");
            gettimeofday(&tv1, NULL);
            time_in_mill2 = tv1.tv_usec;
            time_in_s2 = tv1.tv_sec + time_in_mill1/1000000.0-time_initial;

            if (setlim==1){

                Xdata = {};
                Ydata = {};
                Xdata2 = {};
                Ydata2 = {};
                ui->qwtPlot->setAxisScale(QwtPlot::xBottom,axlim,axlim+5);
                axlim = axlim+5;
                setlim = 0;
                ui->qwtPlot->detachItems();
            }
           this->updatePlot();
            //qDebug("%d",j);


        }
    }
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
    Xdata = {};
    Xdata2 = {};
    Ydata = {};
    Ydata2 = {};


    ui->qwtPlot->setAxisAutoScale(QwtPlot::yLeft,true);
    axlim = 5;
    qDebug("Threads Closed");
    ui->qwtPlot->detachItems();
    timer->start();
    gettimeofday(&runtv, NULL);
    runtime_in_mill = runtv.tv_usec;
    runtime_initial = runtv.tv_sec + runtime_in_mill/1000000.0;
    runaxlim = 10;
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom,0,runaxlim);
    }else{
        running = 0;
        hsmOn = 0;
    }
}

void hsm_full::updatePlot()
{
    QApplication::processEvents();
    index++;
    //qDebug("tick %f",dispCommand);

    QwtPlotCurve *curve1 = new QwtPlotCurve("Curve1");
    QwtPlotCurve *curve2 = new QwtPlotCurve("Curve2");
    curve1->setPen(QColor(Qt::red));


    //Xdata.removeFirst();
    //Ydata.removeFirst();

    //ui->qwtPlot->detachItems();
    //pthread_mutex_lock(&race_mutex);
    curve1->setSamples(Xdata,Ydata);
    //pthread_mutex_unlock(&race_mutex);
    curve1->attach(ui->qwtPlot);

    if(commandPlotting ==1){
       //pthread_mutex_lock(&race_mutex);
       curve2->setSamples(Xdata2,Ydata2);
       //pthread_mutex_unlock(&race_mutex);
       curve2->attach(ui->qwtPlot);
    }

    ui->qwtPlot->replot();


}

void hsm_full::stiffTest()
{
    setvbuf (stdout, NULL, _IONBF, 0);
    stiffOn = 1;
    Xdata = {};
    Xdata2 = {};
    Ydata = {};
    Ydata2 = {};
    force = {0};
    CommandVec = {0};
    DispVec = {0};
    CommandTime = {0};
    DispTime = {0};
    int Amax;
    int Amin;
    int Astable;
    if(microcont == 1){
        A = 2048;
        Amax = 2048+75;
        Amin = 2048-75;
        Astable = 2048;
    }else if(microcont == 2){
        A = 512;
        Amax = 512+20;
        Amin = 512-20;
        Astable = 512;
    }




           //WRITING TO DAC
           printf("Working\n");
           while(A<=Amax){
                   A = A+1;
                   qDebug("%d",index);
                   readForce();
                   force.push_back(received_Force);
                   if(microcont == 1){
                       xt.push_back((A-2048)*span/2048);
                       hsm_full::Ydata2.append((double) (A-2048)*span/2048);
                       hsm_full::Xdata2.append((double) runtime_in_s);
                       stiffdispvec.push_back((A-2048)*span/2048);
                       stiffnessvec.push_back(received_Force);
                       //stiffnessvec.push_back(runtime_in_s);
                       //stiffdispvec.push_back(runtime_in_s);
                       //stiffnessvec.push_back((A-2048)*span/2048);
                       command = 0;
                       command = command<<12;
                       data_to_send = round(A+(ogZero-2048));
                       data_to_send = data_to_send | command;
                       //wiringPiI2CWriteReg16(fd,0x00,data_to_send);
                   }else if(microcont ==2){
                       xt.push_back((A-512)*span/512);
                       hsm_full::Ydata2.append((double) (A-512)*span/512);
                       hsm_full::Xdata2.append((double) runtime_in_s);
                       stiffdispvec.push_back((A-2048)*span/2048);
                       stiffnessvec.push_back(received_Force);
                       //stiffnessvec.push_back(runtime_in_s);
                       //stiffdispvec.push_back(runtime_in_s);
                       //stiffnessvec.push_back((A-512)*span/512);
                       command = 0;
                       command = command<<10;
                       data_to_send = round(A+(ogZero-512));
                       data_to_send = data_to_send | command;
                       //wiringPiI2CWriteReg16(fd,0x00,data_to_send);
                   }
                   else{
                       //DAQ->DACWrite(DAC0,A);
                       //expi.dac_set_raw(round(A+(ogZero-512)),2, 2);
                   }
                   this->updatePlot();
                   usleep(50000);
           }
           while(A>=Amin){
               A = A-1;
               qDebug("%d",index);
               readForce();
               force.push_back(received_Force);
               if(microcont == 1){
                   xt.push_back((A-2048)*span/2048);
                   hsm_full::Ydata2.append((double) (A-2048)*span/2048);
                   hsm_full::Xdata2.append((double) runtime_in_s);
                   stiffdispvec.push_back((A-2048)*span/2048);
                   stiffnessvec.push_back(received_Force);
                   //stiffnessvec.push_back(runtime_in_s);
                   //stiffdispvec.push_back(runtime_in_s);
                   //stiffnessvec.push_back((A-2048)*span/2048);
                   command = 0;
                   command = command<<12;
                   data_to_send = round(A+(ogZero-2048));
                   data_to_send = data_to_send | command;
                   //wiringPiI2CWriteReg16(fd,0x00,data_to_send);
               }else if(microcont ==2){
                   xt.push_back((A-512)*span/512);
                   hsm_full::Ydata2.append((double) (A-512)*span/512);
                   hsm_full::Xdata2.append((double) runtime_in_s);
                   stiffdispvec.push_back((A-512)*span/512);
                   stiffnessvec.push_back(received_Force);
                   //stiffnessvec.push_back(runtime_in_s);
                   //stiffdispvec.push_back(runtime_in_s);
                   //stiffnessvec.push_back((A-512)*span/512);
                   command = 0;
                   command = command<<10;
                   data_to_send = round(A+(ogZero-512));
                   data_to_send = data_to_send | command;
                   //wiringPiI2CWriteReg16(fd,0x00,data_to_send);
               }
               else{
                   //DAQ->DACWrite(DAC0,A);
                   //expi.dac_set_raw(round(A+(ogZero-512)),2, 2);
               }
               this->updatePlot();
               usleep(50000);
           }
           while(A<=Astable){
               A = A+1;
               qDebug("%d",index);
               readForce();
               force.push_back(received_Force);
               if(microcont == 1){
                   xt.push_back((A-2048)*span/2048);
                   hsm_full::Ydata2.append((double) (A-2048)*span/2048);
                   hsm_full::Xdata2.append((double) runtime_in_s);
                   stiffdispvec.push_back((A-2048)*span/2048);
                   stiffnessvec.push_back(received_Force);
                   //stiffnessvec.push_back(runtime_in_s);
                   //stiffdispvec.push_back(runtime_in_s);
                   //stiffnessvec.push_back((A-2048)*span/2048);
                   command = 0;
                   command = command<<12;
                   data_to_send = round(A+(ogZero-2048));
                   data_to_send = data_to_send | command;
                   //wiringPiI2CWriteReg16(fd,0x00,data_to_send);
               }else if(microcont ==2){
                   xt.push_back((A-512)*span/512);
                   hsm_full::Ydata2.append((double) (A-512)*span/512);
                   hsm_full::Xdata2.append((double) runtime_in_s);
                   stiffdispvec.push_back((A-512)*span/512);
                   stiffnessvec.push_back(received_Force);
                   //stiffnessvec.push_back(runtime_in_s);
                   //stiffdispvec.push_back(runtime_in_s);
                   //stiffnessvec.push_back((A-512)*span/512);
                   command = 0;
                   command = command<<10;
                   data_to_send = round(A+(ogZero-512));
                   data_to_send = data_to_send | command;
                   //wiringPiI2CWriteReg16(fd,0x00,data_to_send);
               }
               else{
                   //DAQ->DACWrite(DAC0,A);
                   //expi.dac_set_raw(round(A+(ogZero-512)),2, 2);
               }
               this->updatePlot();
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
           printf("%f\n",hybStiff);
           ui->Stiffness->display(hybStiff);
           CommandVec = hsm_full::Ydata2.toStdVector();
           DispVec = hsm_full::Ydata.toStdVector();
           CommandTime = hsm_full::Xdata2.toStdVector();
           DispTime = hsm_full::Xdata.toStdVector();
           stiffOn = 0;
           printf("Done\n");
}

void hsm_full::save()
{

    setvbuf (stdout, NULL, _IONBF, 0);
    output.open("IntegratorDisp.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Integrator Disp\n");
            for(int i = 0 ; i<xn.size()+1; i++){
                    output << xn[i] << "\n";
                    //printf("%d\n",i);
            }
            output.close();
    output2.open("Force.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving force\n");
            for(int i = 0 ; i<force.size()+1; i++){
                    output2 << force[i] << "\n";
                    //printf("%d\n",i);
            }
            output2.close();

    sentCom.open("Command.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Commands x\n");
            for(int i = 0 ; i<CommandVec.size()+1; i++){
                    sentCom << CommandVec[i] << "\n";
                    //printf("%d\n",i);
            }
            sentCom.close();
    recDisp.open("recDisp.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Recieved Disp x\n");
            for(int i = 0 ; i<DispVec.size()+1; i++){
                    recDisp << DispVec[i] << "\n";
                    //printf("%d\n",i);
            }
            recDisp.close();
    CommandT.open("CommandT.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Command Time x\n");
            for(int i = 0 ; i<CommandTime.size()+1; i++){
                    CommandT << CommandTime[i] << "\n";
                    //printf("%d\n",i);
            }
            CommandT.close();
    DispT.open("DispT.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Recieved Disp Time x\n");
            for(int i = 0 ; i<DispTime.size()+1; i++){
                    DispT << DispTime[i] << "\n";
                    //printf("%d\n",i);
            }
            DispT.close();
    runningCommand.open("runningCommand.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Running Commands x\n");
            for(int i = 0 ; i<runCommand.size()+1; i++){
                    runningCommand << runCommand[i] << "\n";
                    //printf("%d\n",i);
            }
            runningCommand.close();
    runningTime.open("runningTime.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Running Time x\n");
            for(int i = 0 ; i<runTime.size()+1; i++){
                    runningTime << runTime[i] << "\n";
                    //printf("%d\n",i);
            }
            runningTime.close();
    runningFeedback.open("runningFeedback.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Running Disp Feedback x\n");
            for(int i = 0 ; i<runFeedback.size()+1; i++){
                    runningFeedback << runFeedback[i] << "\n";
                    //printf("%d\n",i);
            }
            runningFeedback.close();

    if (xd.size()>1){
        integratorIndex.open("integratorIndex.txt",std::ofstream::out | std::ofstream::trunc);
        printf("Saving Integrator Index %d\n",intIndex.size());
                for(int i = 0 ; i<intIndex.size()+1; i++){
                        integratorIndex << intIndex[i] << "\n";
                        //printf("%d\n",i);
                }
                integratorIndex.close();


        calcVelocity.open("calcVelocity.txt",std::ofstream::out | std::ofstream::trunc);
        printf("Saving Calculated Velocity\n");
                for(int i = 0 ; i<xd.size()+1; i++){
                        calcVelocity << xd[i] << "\n";
                        //printf("%d\n",i);
                }
                calcVelocity.close();

        calcAcc.open("calcAcc.txt",std::ofstream::out | std::ofstream::trunc);
        printf("Saving Calculated Acceleration\n");
                for(int i = 0 ; i<xdd.size()+1; i++){
                        calcAcc << xdd[i] << "\n";
                        //printf("%d\n",i);
                }
                calcAcc.close();
    }
    qDebug("%d",sinCommand.size());

    SinCommandFile.open("SinCommand.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Sin Commands\n");
            for(int i = 0 ; i<sinCommand.size()+1; i++){
                    SinCommandFile << sinCommand[i] << "\n";
                    //printf("%d\n",i);
            }
            SinCommandFile.close();

    SinResponseFile.open("SinResponse.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Sin Disp Response\n");
            for(int i = 0 ; i<sinResponse.size()+1; i++){
                    SinResponseFile << sinResponse[i] << "\n";
                    //printf("%d\n",i);
            }
            SinResponseFile.close();

    SinForceFile.open("SinForce.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Sin Force Response\n");
            for(int i = 0 ; i<sinForce.size()+1; i++){
                    SinForceFile << sinForce[i] << "\n";
                    //printf("%d\n",i);
            }
            SinForceFile.close();

    SinTimeFile.open("SinTime.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Sin Time\n");
            for(int i = 0 ; i<sinTime.size()+1; i++){
                    SinTimeFile << sinTime[i] << "\n";
                    //printf("%d\n",i);
            }
            SinTimeFile.close();


    if(logcontrolloops == 1){
    controlLoops.open("controlLoops.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving control Loops x\n");
            for(int i = 0 ; i<loops.size()+1; i++){
                    controlLoops << loops[i] << "\n";
                    //printf("%d\n",i);
            }
            controlLoops.close();
    signalLoopTime.open("signalLoopTime.txt",std::ofstream::out | std::ofstream::trunc);
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


void hsm_full::sendCommand(){
    /*setvbuf (stdout, NULL, _IONBF, 0);
    dispCommand = ui->CommandInput->value();
    printf("%f",dispCommand);
    if (microcont == 1){
        command = 0;
        command = command<<12;
        data_to_send = std::min(4095.0,round((dispCommand+span)*4095.0/(2*span))+(ogZero-2048));
        data_to_send = data_to_send | command;
        wiringPiI2CWriteReg16(fd,0x00,data_to_send);
    }else if (microcont ==2){
        command = 0;
        command = command<<10;
        data_to_send = std::min(1023.0,round((dispCommand+span)*1023.0/(2*span))+(ogZero-512));
        data_to_send = data_to_send | command;
        wiringPiI2CWriteReg16(fd,0x00,data_to_send);
    }else{
        data_to_send = std::min(3300.0,round((dispCommand+span)*3300.0/(2*span))+(sendZero-1650));
        //expi.dac_set_raw(data_to_send,2, 2);
        qDebug("%d",data_to_send);
    }*/
}

void hsm_full::sendP(){
    /*setvbuf (stdout, NULL, _IONBF, 0);
    PCommand = ui->PInput->value();
    ui->PDisp->display(PCommand);
    printf("%f",PCommand);
    command = 1;
    command = command<<12;
    data_to_send = std::min(4095.0,round(PCommand/Pmax*4095));
    data_to_send = data_to_send | command;
    wiringPiI2CWriteReg16(fd,0x00,data_to_send);*/
}

void hsm_full::sendI(){
    /*setvbuf (stdout, NULL, _IONBF, 0);
    ICommand = ui->IInput->value();
    ui->IDisp->display(ICommand);
    printf("%f",ICommand);
    command = 2;
    command = command<<12;
    data_to_send = std::min(4095.0,round(ICommand/Imax*4095));
    data_to_send = data_to_send | command;
    wiringPiI2CWriteReg16(fd,0x00,data_to_send);*/
}

void hsm_full::sendD(){
    /*setvbuf (stdout, NULL, _IONBF, 0);
    DCommand = ui->DInput->value();
    ui->DDisp->display(DCommand);
    printf("%f",DCommand);
    command = 3;
    command = command<<12;
    data_to_send = std::min(4095.0,round(DCommand/Dmax*4095));
    data_to_send = data_to_send | command;
    wiringPiI2CWriteReg16(fd,0x00,data_to_send);*/
}

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

void hsm_full::updateLCD(){

    SerialDisp = serialRead();
    //SerialDisp = 0;
    received_Disp = (((double)SerialDisp)-2048)*2*span/4095.0;



    /*if(microcont == 1){
        i2ctest = wiringPiI2CReadReg16(fd,0x00);
        if (i2ctest == -1){
            while (i2ctest ==-1){
                i2ctest = wiringPiI2CReadReg16(fd,0x00);
            }
        }
        ddisp = (((double)i2ctest)-2048)*2*span/4095.0-((ogZero-2048)*2*span/4095)-prevdisp;
        while(abs(ddisp)>1){
            i2ctest = wiringPiI2CReadReg16(fd,0x00);
            ddisp = (((double)i2ctest)-2048)*2*span/4095.0-((ogZero-2048)*2*span/4095)-prevdisp;
        }
        received_Disp = (((double)i2ctest)-2048)*2*span/4095.0-((ogZero-2048)*2*span/4095);
        //qDebug("%f",zeroPoint_in);
    }else if(microcont ==2){
        i2ctest = wiringPiI2CReadReg16(fd,0x00);
        if (i2ctest == -1){
            while (i2ctest ==-1){
                i2ctest = wiringPiI2CReadReg16(fd,0x00);
            }
        }
        ddisp = (((double)i2ctest)-2048)*2*span/4095.0-((ogZero-2048)*2*span/4095)-prevdisp;
        while(abs(ddisp)>1){
            i2ctest = wiringPiI2CReadReg16(fd,0x00);
            ddisp = (((double)i2ctest)-2048)*2*span/4095.0-((ogZero-2048)*2*span/4095)-prevdisp;
        }
        received_Disp = (((double)i2ctest)-512)*2*span/1023.0-((ogZero-512)*2*span/1023);
    }
    else{
        readDisp();
        //received_Disp = (expi.adc_read_raw(2,0)-1650.0)*span/1650.0;
    }*/
    //hibyte = i2ctest<<8;
    //lobyte = i2ctest>>8;
    //i2ctest = hibyte|lobyte;



    readForce();

    ui->Force->display(received_Force);
    ui->CurPos->display(relative_Disp);
    ui->CommandNum->display(ui->horizontalSlider->value());
    controlcount = controlcount+1;

    gettimeofday(&runtv, NULL);
    runtime_in_mill = runtv.tv_usec;
    runtime_in_s = runtv.tv_sec + runtime_in_mill/1000000.0-runtime_initial;
    runTime.erase(runTime.begin());
    runTime.push_back(runtime_in_s);
    runCommand.erase(runCommand.begin());
    runCommand.push_back(dispCommand);

    if (sinOn == 0 && hsmOn == 0 && stiffOn == 0){
    hsm_full::Xdata2.append((double) runtime_in_s);
    hsm_full::Ydata2.append((double) dispCommand);
    }
    if (runtime_in_s>runaxlim){
        ui->qwtPlot->setAxisScale(QwtPlot::xBottom,runaxlim,runaxlim+10);
        Xdata = {};
        Ydata = {};
        Xdata2 = {};
        Ydata2 = {};
        runaxlim = runaxlim+10;
        setlim = 0;
        ui->qwtPlot->detachItems();

    }

    if (sinOn ==0) {
        hsm_full::Xdata.append((double) runtime_in_s);
        if ((received_Disp<span) && (received_Disp>-span)){
            relative_Disp = received_Disp-zeroPoint_in;
            hsm_full::Ydata.append((double) relative_Disp);
            last_recieved = received_Disp;

        }
        else{
            relative_Disp = last_recieved-zeroPoint_in;
            hsm_full::Ydata.append((double) relative_Disp);
        }
        runFeedback.erase(runFeedback.begin());
        runFeedback.push_back(relative_Disp);

    }
    pcom = i2ctest;
    //qDebug("ye");

    this->updatePlot();

}

void hsm_full::spanCommand(){
    /*span = ui->SpanInput->value();
    ui->CurSpan->display(span);
    command = 4;
    command = command<<12;
    data_to_send = std::min(4095.0,round((span)*4095.0/(2*maxspan)));
    data_to_send = data_to_send | command;
    wiringPiI2CWriteReg16(fd,0x00,data_to_send);*/
}

void hsm_full::setZero(){
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

void hsm_full::calForce(){
    zeroForce = 0;
    for(int j=1; j<=100;j++){
        //zeroForce = zeroForce+(expi.adc_read_raw(1,0)-1650.0)*3.3/1650.0;
        zeroForce = 0;

    }
    zeroForce = zeroForce/100;
    qDebug("%f",zeroForce);
}

void readForce(){
    //f1 = (expi.adc_read_raw(1,0)-1650.0)*3.3/1650.0-zeroForce;
    //f2 = (expi.adc_read_raw(1,0)-1650.0)*3.3/1650.0-zeroForce;
    //f3 = (expi.adc_read_raw(1,0)-1650.0)*3.3/1650.0-zeroForce;
    f1 = 0;
    f2 = 0;
    f3 = 0;
    received_Force=.3*fprev+(1-.3)*(f1+f2+f3)/3;
    //force_bits = expi.adc_read_raw(1,0);
    fprev = received_Force;
    //qDebug("%d",force_bits);
}

void readDisp(){
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

void hsm_full::startControl(){
    /*if (controller == 0){
        ui->StartControl->setText("Stop Controller");
        controller = 1;
    }else{
        ui->StartControl->setText("Start Controller");
    }
    command = 8;
    command = command<<12;
    data_to_send = 0;
    data_to_send = data_to_send | command;
    wiringPiI2CWriteReg16(fd,0x00,data_to_send);*/
}


void hsm_full::PSAS_Window(){
    PSAS *StructSoft = new PSAS();
    StructSoft->show();
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
    Xdata = {};
    Xdata2 = {};
    Ydata = {};
    Ydata2 = {};
    sinOn =1;
    signalLoops= {};
    sinCommand = {};
    sinTime = {};
    sinResponse = {};
    sinForce = {};

    qDebug("test1");

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

    ui->qwtPlot->setAxisAutoScale(QwtPlot::xBottom,false);
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom,0,axlim);
    ui->qwtPlot->detachItems();
    while(running == true){
        plotcount = plotcount+1;

        if (plotcount%500000 == 0){
            //qDebug("Hello");
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
            if (setlim==1){
                ui->qwtPlot->setAxisScale(QwtPlot::xBottom,axlim,axlim+5);
                Xdata = {};
                Ydata = {};
                Xdata2 = {};
                Ydata2 = {};
                axlim = axlim+5;
                setlim = 0;
                ui->qwtPlot->detachItems();
            }
           //pthread_mutex_lock(&race_mutex);
           this->updatePlot();
           //pthread_mutex_unlock(&race_mutex);
            //qDebug("%d",j);


        }
    }
    ui->qwtPlot->detachItems();


    /* Join the thread and wait until it is done */
    ret = pthread_join(thread, NULL);
    if (ret){
            printf("join pthread failed: %m\n");
    }
    qDebug("Threads Closed");
    if(sinsweep==1 or amptest == 1){
        sinOn = 0;
        Xdata = {};
        Xdata2 = {};
        Ydata = {};
        Ydata2 = {};
        running = 0;
        timer->start();
        ui->qwtPlot->setAxisAutoScale(QwtPlot::xBottom,true);
        ui->qwtPlot->setAxisAutoScale(QwtPlot::yLeft,true);
        axlim = 5;
        sinWave = {};
        gettimeofday(&runtv, NULL);
        runtime_in_mill = runtv.tv_usec;
        runtime_initial = runtv.tv_sec + runtime_in_mill/1000000.0;
        runaxlim = 10;
        ui->qwtPlot->setAxisScale(QwtPlot::xBottom,0,runaxlim);
    }
}else{
    sinOn = 0;
    Xdata = {};
    Xdata2 = {};
    Ydata = {};
    Ydata2 = {};
    running = 0;
    timer->start();
    ui->qwtPlot->setAxisAutoScale(QwtPlot::xBottom,true);
    ui->qwtPlot->setAxisAutoScale(QwtPlot::yLeft,true);
    axlim = 5;
    sinWave = {};
    gettimeofday(&runtv, NULL);
    runtime_in_mill = runtv.tv_usec;
    runtime_initial = runtv.tv_sec + runtime_in_mill/1000000.0;
    runaxlim = 10;
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom,0,runaxlim);
}

}

int hsm_full::plotResults(){
    Py_Initialize();
    import_array();
    PyObject *sysPath = PySys_GetObject((char*)"path");
    PyList_Append(sysPath,PyUnicode_FromString("/home/jim53/Desktop/HSM_Full"));  // path to the module to import
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


void hsm_full::activatePin(){
    if (pinActive){
        pinActive = 0;
        digitalWrite(7, pinActive);
        qDebug("1");
    }else{
        pinActive = 1;
        digitalWrite(7, pinActive);
        qDebug("2");
    }
}

int serialRead() {
    command = 1;
    command = command<<12;
    data_to_send = 0;
    data_to_send = data_to_send | command;
    //serialFlush(fd); 
    sendData[0] = data_to_send >> 8;
    sendData[1] = data_to_send;
    uint16_t crcSum = crc_modbus(sendData,2);
    sendData[2] = crcSum >> 8;
    sendData[3] = crcSum;
    serialPutchar(fd,'<');
    serialPutchar(fd,sendData[0]);
    serialPutchar(fd,sendData[1]);
    serialPutchar(fd,sendData[2]);
    serialPutchar(fd,sendData[3]);
    serialPutchar(fd,'>');
    char startMarker = '<';
    char endMarker = '>';
    char rc;
    int maxBytes = 2;
    int ndx = 0;

    for(int i = 0; i < 4;i++){
      char rc;
      rc = serialGetchar(fd);
      received[i] = rc;
    }
    /*for(int i = 0; i < 4; i++) {
        rc = serialGetchar(fd);
        //qDebug("test");
        if (recvInProgress == true) {
            if(rc != endMarker || (rc == endMarker && ndx < maxBytes)) {
                received[ndx] = rc;
                ndx += 1;
            }
            else {
                numReceived = char(received[1])<<8;
                numReceived |= char(received[0]);
                numReceived = numReceived & 4095;
                recvInProgress = false;
            }
        }
        else if (rc == startMarker) {
            recvInProgress = true;
            qDebug("Begin");
        }
    }*/
      numReceived = received[1]<<8;
      numReceived |= received[0];
      recData[0] = received[1];
      recData[1] = received[0];
      numReceived = numReceived & 4095;
      crcReceived = received[3] << 8;
      crcReceived |= received[2];
      //std::cout << (crc_modbus(sendData,2)) << "\n";
      return numReceived;
}

