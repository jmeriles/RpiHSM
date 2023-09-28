#ifndef PSAS_UI_H
#define PSAS_UI_H
#include <QMainWindow>

namespace Ui2{
    class PSAS_UI;
}

class PSAS_UI : public QMainWindow
{
    Q_OBJECT

public:
    explicit PSAS_UI(QWidget *parent = nullptr);
    ~PSAS_UI();
    Ui2::PSAS_UI *ui;

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
    void setAmp();
    void setFreq();
    void sinTest();
    void sweep();
    void reqloops();
    void calForce();
    void PSAS_Window();


signals:
    void sendSignal(int value);


private:


private slots:
    void update();

};

#endif // PSAS_UI_H
