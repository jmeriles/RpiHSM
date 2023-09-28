#include "lowpassfilter2.h"

//Class adapted from https://github.com/curiores/ArduinoTutorials/blob/main/BasicFilters/ArduinoImplementations/LowPass/LowPass2.0/LowPass2.0.ino arduino code


LowPassFilter2::LowPassFilter2(double f0, double fs, bool adaptive)
{
    // f0: cutoff frequency (Hz)
    // fs: sample frequency (Hz)
    // adaptive: boolean flag, if set to 1, the code will automatically set
    // the sample frequency based on the time history.

    omega0 = 6.28318530718*f0;
    dt = 1.0/fs;
    adapt = adaptive;
    tn1 = -dt;
    for(int k = 0; k < 2+1; k++){
      x[k] = 0;
      y[k] = 0;
    }

    gettimeofday(&lptimer, NULL);

    time_in_mill = lptimer.tv_usec;
    time_in_s = lptimer.tv_sec + time_in_mill/1000000.0;
    setCoef();
}

void LowPassFilter2 :: setCoef(){
    if(adapt){
      gettimeofday(&lptimer, NULL);
      time_in_mill = lptimer.tv_usec;
      time_in_s = lptimer.tv_sec + time_in_mill/1000000.0;
      dt = time_in_s - tn1;
      tn1 = time_in_s;
    }

  double alpha = omega0*dt;
  double alphaSq = alpha*alpha;
  double beta[] = {1, sqrt(2), 1};
  double D = alphaSq*beta[0] + 2*alpha*beta[1] + 4*beta[2];

  b[0] = alphaSq/D;
  b[1] = 2*b[0];
  b[2] = b[0];
  a[0] = -(2*alphaSq*beta[0] - 8*beta[2])/D;
  a[1] = -(beta[0]*alphaSq - 2*beta[1]*alpha + 4*beta[2])/D;

}



double LowPassFilter2 :: filt(double xn){
    // Provide me with the current raw value: x
    // I will give you the current filtered value: y
    if(adapt){
      setCoef(); // Update coefficients if necessary
    }
    y[0] = 0;
    x[0] = xn;
    // Compute the filtered values
    for(int k = 0; k < 2; k++){
      y[0] += a[k]*y[k+1] + b[k]*x[k];
    }
    y[0] += b[2]*x[2];

    // Save the historical values
    for(int k = 2; k > 0; k--){
      y[k] = y[k-1];
      x[k] = x[k-1];
    }

    // Return the filtered value
    return y[0];
}
