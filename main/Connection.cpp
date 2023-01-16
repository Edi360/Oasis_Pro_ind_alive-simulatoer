#include "Connection.h"


Connection::Connection(){
  id = 0;
  connection_number = 0;
}

void Connection::no_connection(){
  connection_number = 8;
} //no connection

void Connection::ok_connection(){
  connection_number = 5;

} //ok connection
void Connection::ex_connection(){
  connection_number = 2;

} //excellent connection


int Connection::test_mode(){
  //display status of the connection
  if(connection_number == 2){
    //display green
    qDebug() <<"Excellent Connection";
    return 2;
  }
  else if( connection_number == 5){
    //display yellow
    qDebug() <<"OK Connection";
    return 5;
  }
  else if( connection_number == 8){
    //display red
    qDebug() <<"NO Connection";
    return 8;
  }

  return 0;

  //returns true only if we have a good or excellent connection

} //checks for connection

int Connection::getNum(){return connection_number;}


