#ifndef LOWPASSFILTER2_H
#define LOWPASSFILTER2_H


#include </usr/include/python3.9/Python.h>
#include </usr/include/python3.9/numpy/ndarraytypes.h>
#include </usr/include/python3.9/numpy/ndarrayobject.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <iostream>
#include <fstream>




class LowPassFilter2 {
public:
  LowPassFilter2(double f0, double fs, bool adaptive);
  void setCoef();
  double filt(double xn);

private:
  double a[2];
  double b[2+1];
  double x[2+1]; // Raw values
  double y[2+1]; // Filtered values
  double time_in_mill;
  double time_in_s;
  struct timeval lptimer;
  double omega0;
  double dt;
  bool adapt;
  double tn1 = 0;

};


#endif // LOWPASSFILTER2_H
