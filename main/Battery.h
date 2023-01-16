#ifndef BATTERY_H
#define BATTERY_H

#include <QString>
#include <QDebug>

//#include <iostream>
//#include <string>

using namespace std;

class Battery {

public:
  //initialize a battery with given life
  Battery(int l);

  void updateBattery(int x); //update the battery life after session is run
  void critically_low(); //critically low batterry
  void low_battery(); //low battery
  void ok_battery(); //sufficient battery
  int battery_depletion(int duration, int intensity, bool connection); //calculates and updates battery level
  int get_battery_life();
  int getState();

private:
  int id;
  int life;
  int state;
};
#endif
