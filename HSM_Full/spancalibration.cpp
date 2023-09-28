#include "hsm_full.h"
#include "ui_spancalibration.h"
#include "qwt_plot_curve.h"
#include "qwt_plot.h"
#include <qwt_plot_dict.h>
#include <string>
#include <iostream>
#include <stdio.h>
int origVolt;
int ampedVolt;
std::vector<std::vector<double>> calibrationMatrix;
std::vector<double> gain;
hsm_full *sourcefunction;
std::ofstream spanCalibrationFile;
std::ofstream potCalibrationFile;
std::ofstream spanCalibrationAllData;
std::ofstream potCalibrationAllData;
std::ofstream potCalibrationZeroData;
int gainCounter = 0;
QwtPlotCurve *curve6 = new QwtPlotCurve("Curve6");
int potCalCount = 0;
double sumX = 0;
double sumX2 = 0;
double sumY = 0;
double sumXY = 0;
int n;
std::vector<double> truDisp;
std::vector<double> diffDisp;
double calSlope;
double calIntercept;
double totSpan = 10.0;
double totSpan2 = 10.0;
double minAmpVal = 1000;
int maxValue = 0;
int minValue = 1000;
int maxOGValue = 0;
int minOGValue = 1000;
int boxChecked = false;
std::vector <double> ampCodes;
std::vector <double> calSlopes;
std::vector <double> calIntercepts;
std::vector <double> maxVals;
std::vector <double> minVals;
std::vector <double> potInches;
std::vector <double> potTru;
std::vector <double> potDiff;
std::vector <double> zeroData;
std::vector <double> origSlopes;
std::vector <double> origIntercepts;
std::vector <double> potInches2;
std::vector <double> potTru2;
std::vector <double> potDiff2;
std::vector <double> zeroData2;
std::vector <double> origSlopes2;
std::vector <double> origIntercepts2;
std::vector <std::vector<std::vector<double>>> allSpanData;
std::vector <std::vector<double>> allPotData;
int allDataCount = 0;
QVector<double> XCalData;
QVector<double> YCalData;
QVector<double> XCalData2;
QVector<double> YCalData2;
double inchVal;
int potInchCount = 0;
double inchSlope;
double inchIntercept;
double diffGain;
double diffGain2;
double diffIntercept;
double diffIntercept2;
int controlChannel;


//QTimer *timer;

SpanCalibration::SpanCalibration(QMainWindow *parent, hsm_full *source) :
    QMainWindow(parent),
    ui5(new Ui::SpanCalibration)
{
    sourcefunction = source;
    ui5->setupUi(this);
    connect(ui5->SpanCalButton,&QPushButton::released,this,&SpanCalibration::startCalibration);
    //connect(ui5->PotCalButton, &QPushButton::released,this,&SpanCalibration::potCal);
    connect(ui5->PotCalButton, &QPushButton::released,this,&SpanCalibration::potCal);
    //connect(ui5->activatePotCal, &QCheckBox::toggled,this,&SpanCalibration::activatePotCal);
    connect(ui5->calibrateLoadCell, &QPushButton::released,this,&SpanCalibration::loadCal);
    //window->cl
    closeCallback = [&](){
        timer->start();
        std::cout << "Window was closed" << "\n";
    };
    QString newText = "Perform Different Calibrations\nSelect Controller\n\nAdd Cal Point: Begins Calibration of Potentiometer. Requires Gauge Blocks.\n\nCalibrate Span: "
                        "Calibrates Gains for Span Control Circuit. Time Consuming. Be sure Potentiometer is at Max Extent Before Button is Pressed.";
    ui5->Instructions->setText(newText);
}



void SpanCalibration::startCalibration() {
    //sourcefunction->timer->stop();
    controlChannel = ui5->ControllerSelect->value();
    spanCalibrationAllData.open("../AmpCalibrationAll.txt",std::ofstream::out | std::ofstream::trunc);
    for (int j = 120; j < 255 ; j++) {
        XCalData.clear();
        YCalData.clear();
        calibrationMatrix.push_back({0});
        calibrationMatrix.push_back({0});
        sourcefunction->serialWrite(controlChannel, 10, j);
        sourcefunction->serialWrite(controlChannel, 12, 0); //turns on calibration
        calibrationMatrix.push_back({0});
        //ui5->CalibrationPlot->setAxisAutoScale(QwtPlot::xTop,true);
        //ui5->CalibrationPlot->setAxisAutoScale(QwtPlot::yLeft,true);
        std::vector <double> paredDownAmpedVal;
        std::vector <double> paredDownOrigVal;
        std::vector<std::vector<double>> storeDataVec;
        allSpanData.push_back({});
        int maxAmpVal = 0;
        for (int i = 0; i < 4096; i++) {
            //std::cout << i << "\n";
            ampedVolt = sourcefunction->serialRead(controlChannel, 11, 1);
            //std::cout << "Read 1" << "\n";
            calibrationMatrix[2 * gainCounter].push_back(ampedVolt);
            origVolt = sourcefunction->serialRead(controlChannel, 11, 2);
            std::vector <double> tempDataVec;
            tempDataVec.push_back(ampedVolt);
            tempDataVec.push_back(origVolt);
            storeDataVec.push_back(tempDataVec);
            //std::cout << "Read 2" << "\n";
            calibrationMatrix[2 * gainCounter + 1].push_back(origVolt);
            double gainVal;
            if (ampedVolt < minAmpVal) {
                minAmpVal = ampedVolt;
            }
            if (origVolt != 0) {
                gainVal = (double)ampedVolt/(double)origVolt - 1.0;
            }else {
                gainVal = 1;
            }
            if (ampedVolt > maxAmpVal) {
                maxAmpVal = ampedVolt;
            }
            if(origVolt > 0 && i!=4095) {
                gain.push_back(gainVal);
                XCalData.append(origVolt);
                YCalData.append(ampedVolt);
            }
        }

        printf("Saving Calibration Info\n");
                spanCalibrationAllData << j << "\n";
                for(int i = 0 ; i < storeDataVec.size(); i++){
                        spanCalibrationAllData << storeDataVec[i][0] << ", " << storeDataVec[i][1] << "\n";
                }
        //std::cout << "Test 1 \n";
        bool maxReached = false;
        for (int k = 0; k < XCalData.size(); k++) {
            if (XCalData[k] > 0 && !maxReached) {
                if (YCalData[k] > maxAmpVal - 5) {
                    maxReached = true;
                }
                paredDownAmpedVal.push_back(YCalData[k]);
                paredDownOrigVal.push_back(XCalData[k]);
                //std::cout << "Amplified Value: " << YCalData[k] << "Inch Value: " << BitToInch((int) XCalData[k]) << "\n";
            }
        }
        std::vector<double> regressionData = sourcefunction->LinearRegression(paredDownOrigVal,paredDownAmpedVal);
        ampCodes.push_back(j);
        calSlopes.push_back(regressionData[0]);
        calIntercepts.push_back(regressionData[1]);
        maxVals.push_back(maxAmpVal);
        minVals.push_back(minAmpVal);
        plotCal(XCalData,YCalData);
        std::cout << "Slope: " << regressionData[0] << "Intercept: " << regressionData[1] << "\n";
        std::cout << "Done";
    }
    spanCalibrationAllData.close();
    setvbuf (stdout, NULL, _IONBF, 0);
    if (controlChannel == 1) {
        spanCalibrationFile.open("AmpCalibration.txt",std::ofstream::out | std::ofstream::trunc);
        printf("Saving Calibration Info\n");
        for(int i = 0 ; i < ampCodes.size(); i++){
                spanCalibrationFile << ampCodes[i] << ", " << calSlopes[i] << ", " << calIntercepts[i] << ", " << maxVals[i] << ", " << minVals[i] << "\n";
        }
        spanCalibrationFile.close();
    } else if (controlChannel == 2) {
        spanCalibrationFile.open("AmpCalibration2.txt",std::ofstream::out | std::ofstream::trunc);
        printf("Saving Calibration 2 Info\n");
        for(int i = 0 ; i < ampCodes.size(); i++){
                spanCalibrationFile << ampCodes[i] << ", " << calSlopes[i] << ", " << calIntercepts[i] << ", " << maxVals[i] << ", " << minVals[i] << "\n";
        }
        spanCalibrationFile.close();
    }
}

void SpanCalibration::plotCal(QVector<double> X, QVector<double> Y) {
    curve6->setSamples(X,Y);
    curve6->attach(ui5->CalibrationPlot);
    ui5->CalibrationPlot->replot();
    QApplication::processEvents();
}

/*void SpanCalibration::potCal() {
    QString newText = "Pick 30 points along Potentiometer Span to calibrate \n" + QString::number(potCalCount);
    ui5->Instructions->setText(newText);
    //ui5->Instructions->setText(QString::number(potCalCount));
    if (potCalCount <= 30) {
        double xData = sourcefunction->serialRead(1, 11, 3);
        double yData = sourcefunction->serialRead(1, 11, 2);
        if (yData > maxValue) {
            maxValue = yData;
        }
        if (xData > maxOGValue) {
            maxOGValue = xData;
        }
        if (yData < minValue) {
            minValue = yData;
        }
        if (xData < minOGValue) {
            minOGValue = xData;
        }
        truDisp.push_back(xData);
        diffDisp.push_back(yData);
        XCalData2.append(xData);
        YCalData2.append(yData);
        potCalCount += 1;
    } else {
        n = truDisp.size();
        //printf("%d\n",stiffdispvec.size());
        //printf("%d\n",stiffnessvec.size());
        for (int i=0;i<n;i++){
            sumX = sumX + truDisp[i];
            sumX2 = sumX2 + truDisp[i]*truDisp[i];
            sumY = sumY+diffDisp[i];
            sumXY = sumXY + truDisp[i]*diffDisp[i];
        }
        calSlope = ((double)n*sumXY-sumX*sumY)/((double)n*sumX2-sumX*sumX);
        calIntercept = (sumY - calSlope * sumX) / n;
        //const char *path="./file.txt";
        potCalibrationFile.open("../potCal.txt",std::ofstream::out | std::ofstream::trunc);
        printf("Saving Pot Calibration\n");
        potCalibrationFile << calSlope << ", " << calIntercept << ", " << maxValue << ", " << maxOGValue << ", " << minValue << "," << minOGValue << "," << totSpan << "," << inchSlope << "\n";
        potCalibrationFile.close();

        potCalibrationAllData.open("../PotCalibrationAll.txt",std::ofstream::out | std::ofstream::trunc);
        printf("Saving Calibration Info\n");
                for(int i = 0 ; i < truDisp.size(); i++){
                        potCalibrationAllData << truDisp[i] << ", " << diffDisp[i] << "\n";
                }
                potCalibrationAllData.close();

        std::cout << "Slope: " << calSlope << "\n";
        std::cout << "Intercept: " << calIntercept << "\n";
        potCalCount = 0;
        ui5->activatePotCal->toggle();
        ui5->Instructions->clear();
        ui5->Instructions->setText("Calibrated!");
        std::cout << "Max in Inches = " << BitToInch(maxValue) << "\n";
        std::cout << "Min in Inches = " << BitToInch(minValue) << "\n";
    }
    std::cout << "Max Diff Value: " << maxValue << "\n";
    std::cout << "Min Diff Value: " << minValue << "\n";
    std::cout << "Max Original Value: " << maxOGValue << "\n";
    std::cout << "Min Original Value: " << minOGValue << "\n";

    plotCal(XCalData2,YCalData2);

}*/

double SpanCalibration::BitToInch(int bitVal) {
    double newCalSlope = calSlope / totSpan * (maxOGValue - minOGValue);
    return (bitVal - calIntercept) / newCalSlope;
}

void SpanCalibration::activatePotCal() {
    if (!boxChecked) {
        ui5->PotCalButton->setEnabled(true);
        boxChecked = true;
    } else {
        ui5->PotCalButton->setEnabled(false);
        boxChecked = false;
    }
}
void SpanCalibration::potCal() {
    inchVal = ui5->setTotSpan->value();
    controlChannel = ui5->ControllerSelect->value();
    if (potInches.size() > 9 && potInchCount == 0) {
        potInches = {};
        potTru = {};
    }
    if(potInchCount < 10) {
        if (potInchCount == 0) {
            sourcefunction->serialWrite(controlChannel, 14, 0);
        }
        potInches.push_back(inchVal);
        int truRead = sourcefunction->serialRead(controlChannel, 11, 3);
        int diffRead = sourcefunction->serialRead(controlChannel, 11, 2);
        potTru.push_back(truRead);
        potDiff.push_back(diffRead);
        potInchCount += 1;
        QString newText = QString::number(inchVal) + ", " + QString::number(truRead) + ", " + QString::number(diffRead) + "\nNumber of Points Left: " + QString::number(10 - potInchCount);
        if (potInchCount == 10) {
            newText = newText + "\n\nMove Transducer to Furthest Extreme and Press Button One More Time";
        }
        ui5->Instructions->setText(newText);
    }
    else {
        origSlopes = {};
        origIntercepts = {};
        QString newText = "Calibrating... ";
        ui5->Instructions->setText(newText);
        QApplication::processEvents();
        std::vector<double> potDiff_trim;
        std::vector<double> potTru_trim;
        /*for (int i = 200; i < 3000; i++){
            potDiff_trim.push_back(potDiff[i]);
            potTru_trim.push_back(potTru[i]);
        }*/
        diffGain = sourcefunction->LinearRegression(potDiff,potTru)[0];
        diffIntercept = sourcefunction->LinearRegression(potDiff,potTru)[1];
        for (int i = 0; i < 9; i ++) {
            origSlopes.push_back((potTru[i + 1] - potTru[i]) / (potInches[i + 1] - potInches[i]));
            origIntercepts.push_back(potTru[i] - origSlopes[i] * potInches[i]);
            std::cout << "Slope: " << origSlopes[i] << "\n";
        }
        maxOGValue = sourcefunction->serialRead(controlChannel, 11, 3);
        totSpan = (maxOGValue - origIntercepts[8]) / origSlopes[8];
        std::cout << "Diff Gain: " << diffGain << "\n";
        /*inchSlope = sourcefunction->LinearRegression(potInches,potTru)[0];
        inchIntercept = sourcefunction->LinearRegression(potInches,potTru)[1];
        potInchCount = 0;
        std::cout << "Slope: " << inchSlope << "\n";
        std::cout << "Intercept: " << inchIntercept << "\n";*/


        if (controlChannel == 1) {
            potCalibrationAllData.open("PotCalibrationAll.txt",std::ofstream::out | std::ofstream::trunc);
            printf("Saving Calibration Info\n");
            for(int i = 0 ; i < potTru.size(); i++){
                    potCalibrationAllData << potTru[i] << ", " << potInches[i] << "\n";
            }
            potCalibrationAllData << diffGain << ", " << diffIntercept << ", " << totSpan << ", " << maxOGValue << "\n";
            potCalibrationAllData.close();
            //potCalibrationFile.open("potCal.txt",std::ofstream::out | std::ofstream::trunc);
            printf("Saving Pot Calibration\n");
            for(int i = 0; i < 4096; i++){
                sourcefunction->serialWrite(1, 14, i);
                delay(1);
                int origVol = sourcefunction->serialRead(controlChannel, 11, 3);
                int diffVol = sourcefunction->serialRead(controlChannel, 11, 2);
                double zeroVol = -((diffVol * diffGain + diffIntercept) - origVol);
                zeroData.push_back(zeroVol);
                std::cout << "orig Vol:  " << origVol << "  Diff Vol:  " << diffVol << "  Zero Voltage:  " << zeroVol << "\n";
            }
            potCalibrationZeroData.open("PotZeroVals.txt",std::ofstream::out | std::ofstream::trunc);
            printf("Saving Calibration Info\n");
            for(int i = 0 ; i < zeroData.size(); i++){
                    potCalibrationZeroData << i << ", " << zeroData[i] << "\n";
            }
            potCalibrationZeroData.close();
        }
        if (controlChannel == 2) {
            potCalibrationAllData.open("PotCalibrationAll2.txt",std::ofstream::out | std::ofstream::trunc);
            printf("Saving Calibration Info\n");
            for(int i = 0 ; i < potTru.size(); i++){
                    potCalibrationAllData << potTru[i] << ", " << potInches[i] << "\n";
            }
            potCalibrationAllData << diffGain <<", " << diffIntercept << ", " << totSpan << ", " << maxOGValue << "\n";
            potCalibrationAllData.close();

            potCalibrationFile.open("potCal2.txt",std::ofstream::out | std::ofstream::trunc);
            printf("Saving Pot Calibration\n");
            for(int i = 0; i < 4096; i++){
                sourcefunction->serialWrite(1, 14, i);
                delay(1);
                int origVol = sourcefunction->serialRead(controlChannel, 11, 3);
                int diffVol = sourcefunction->serialRead(controlChannel, 11, 2);
                double zeroVol = -(diffVol * diffGain - origVol);
                zeroData.push_back(zeroVol);
                std::cout << "orig Vol:  " << origVol << "  Diff Vol:  " << diffVol << "  Zero Voltage:  " << zeroVol << "\n";
            }
            potCalibrationZeroData.open("PotZeroVals2.txt",std::ofstream::out | std::ofstream::trunc);
            printf("Saving Calibration Info\n");
            for(int i = 0 ; i < zeroData.size(); i++){
                    potCalibrationZeroData << i << ", " << zeroData[i] << "\n";
            }
            potCalibrationZeroData.close();
        }
        sourcefunction->readAllFilesAndCalibrate();
        newText = "Potentiometer Calibration Done. \nPress Calibrate Span Button if Gain Calibration is Needed";
        ui5->Instructions->setText(newText);
    }

    ui5->curSpanDisplay->display(totSpan);
    //ui5->PotCalButton->setEnabled(true);
    ui5->SpanCalButton->setEnabled(true);
}

void SpanCalibration::loadCal() {
    //Should do an auto tuning of load cell. improve in future
    int channel = ui5->selectLoadCell->value();
    //channel = 1; //remove this
    int i = 0;
    double forceReading = 10000000000;
    while(abs(forceReading) > .05 && i < 4096) {
        sourcefunction->calLoadCell(channel,i);
        //delay(10);
        forceReading = sourcefunction->returnLoad(channel);
        QString newText = "DAC set to: " + QString::number(i) + ", Current Force Reading" + QString::number(forceReading);
        ui5->Instructions->setText(newText);
        QApplication::processEvents();
        i ++;
    }
    if(i >= 4095) {
        ui5->Instructions->setText("Load Cell not plugged in");
    } else {
        QString newText = "DAC set to: " + QString::number(i) + ", Current Force Reading" + QString::number(forceReading);
        ui5->Instructions->setText(newText);
    }

}

SpanCalibration::~SpanCalibration()
{
    delete ui5;
}
