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
int gainCounter = 0;
QwtPlotCurve *curve1 = new QwtPlotCurve("Curve1");
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
double totSpan;
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


//QTimer *timer;

SpanCalibration::SpanCalibration(QMainWindow *parent, hsm_full *source) :
    QMainWindow(parent),
    ui5(new Ui::SpanCalibration)
{
    sourcefunction = source;
    ui5->setupUi(this);
    connect(ui5->SpanCalButton,&QPushButton::released,this,&SpanCalibration::startCalibration);
    connect(ui5->PotCalButton, &QPushButton::released,this,&SpanCalibration::potCal);
    connect(ui5->setTotSpanButton, &QPushButton::released,this,&SpanCalibration::setTotSpan);
    connect(ui5->activatePotCal, &QCheckBox::toggled,this,&SpanCalibration::activatePotCal);
    //window->cl
    closeCallback = [&](){
        timer->start();
        std::cout << "Window was closed" << "\n";
    };
}



void SpanCalibration::startCalibration() {
    //sourcefunction->timer->stop();
    spanCalibrationAllData.open("../AmpCalibrationAll.txt",std::ofstream::out | std::ofstream::trunc);
    for (int j = 120; j < 255 ; j++) {
        XCalData.clear();
        YCalData.clear();
        calibrationMatrix.push_back({0});
        calibrationMatrix.push_back({0});
        sourcefunction->serialWrite(1, 10, j);
        sourcefunction->serialWrite(1, 12, 0); //turns on calibration
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
            ampedVolt = sourcefunction->serialRead(1, 11, 1);
            //std::cout << "Read 1" << "\n";
            calibrationMatrix[2 * gainCounter].push_back(ampedVolt);
            origVolt = sourcefunction->serialRead(1, 11, 2);
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
    spanCalibrationFile.open("../AmpCalibration.txt",std::ofstream::out | std::ofstream::trunc);
    printf("Saving Calibration Info\n");
            for(int i = 0 ; i < ampCodes.size(); i++){
                    spanCalibrationFile << ampCodes[i] << ", " << calSlopes[i] << ", " << calIntercepts[i] << ", " << maxVals[i] << ", " << minVals[i] << "\n";
            }
            spanCalibrationFile.close();
}

void SpanCalibration::plotCal(QVector<double> X, QVector<double> Y) {
    curve1->setSamples(X,Y);
    curve1->attach(ui5->CalibrationPlot);
    ui5->CalibrationPlot->replot();
    QApplication::processEvents();
}

void SpanCalibration::potCal() {
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

}

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
void SpanCalibration::setTotSpan() {
    inchVal = ui5->setTotSpan->value();
    if(potInchCount < 5) {
        potInches.push_back(inchVal);
        int truRead = sourcefunction->serialRead(1, 11, 3);
        potTru.push_back(truRead);
        potInchCount += 1;
        QString newText = QString::number(inchVal) + ", " + QString::number(truRead);
        ui5->Instructions->setText(newText);
    }
    else {
        inchSlope = sourcefunction->LinearRegression(potInches,potTru)[0];
        inchIntercept = sourcefunction->LinearRegression(potInches,potTru)[1];
        potInchCount = 0;
        std::cout << "Slope: " << inchSlope << "\n";
        std::cout << "Intercept: " << inchIntercept << "\n";
    }
    ui5->curSpanDisplay->display(totSpan);
    //ui5->PotCalButton->setEnabled(true);
    ui5->SpanCalButton->setEnabled(true);
}

SpanCalibration::~SpanCalibration()
{
    delete ui5;
}
