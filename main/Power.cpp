#include "Power.h"

Power::Power(Battery *b){
  id = 1;
  status = false;
  batt = b;
}

//turn on the device
void Power::turn_on(){
  status = true;
  qDebug()  <<"Machine Turned On";
  //display battery level on the graph
  qDebug() <<"Battery Life: "<<batt->get_battery_life();
}

//turn off the device
void Power::turn_off(){
  qDebug()  <<"Turning off Machine..";
  status = false;
}

void Power::soft_off(){
  qDebug() <<"Performing Soft Off..";
  //graph scrolls from 8 to 1
  for(int i = 8; i > 0; i--){
    qDebug()  <<i;
  }
  qDebug() <<"Session Ended";
}

bool Power::get_status(){
  return status;
} //get the status
