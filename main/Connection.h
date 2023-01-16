#ifndef CONNECTION_H
#define CONNECTION_H


#include "QDebug"

using namespace std;

class Connection {

public:
  Connection();

 int getNum();

  void no_connection(); //no connection
  void ok_connection(); //ok connection
  void ex_connection(); //excellent connection
  int test_mode(); //checks for connection

private:
  int id;
  int connection_number;
};
#endif
