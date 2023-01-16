#ifndef POWER_H
#define POWER_H

#include <QString>
#include <QDebug>

//#include <iostream>
//#include <string>
#include "Battery.h"

using namespace std;

class Power {

public:
  Power(Battery *b);

  void turn_off(); //turn on the device
  void turn_on(); //turn off the device
  bool get_status(); //get the status
  void soft_off();


private:
  int id;
  bool status;
  Battery *batt;
};
#endif
