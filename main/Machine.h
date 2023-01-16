#ifndef MACHINE_H
#define MACHINE_H

#include "QThread"
#include "QDebug"

#include "Session.h"
#include "Battery.h"
#include "Power.h"
#include "Connection.h"
#include "sys/types.h"
#include "unistd.h"

#define ARR_SIZE 50

using namespace std;

class Machine{

    public:
        //constructor:
        Machine();

        //getters
        Session* get_recorded_session();//retuns the entire recorded sessions array
        Session get_session(int i);//retuns the sessioj in the recorded sessions array with the index inputed
        int get_recorded();
        Session get_temp();
        Battery* get_battary();
        Power* get_power();
        int getState();
        string session_string(Session s,int i);

        //setters
        void setState(int);
        void setRecorded(int);
        void setTemp(Session);
        void setCurrInt(int);

        void setTempInt(int);
        void setTempDur(int);
        void setTempType(int);
        int getTempInt();


        //functions
        bool add_recorded_session(Session s);//this function takes in a session that will be added to the recorded sessions array if the session is successfuly added to the array it will return true but if it fails to add the session it will return false
        bool start_session(Session s);//this functuiion takes in a session which it will run
        bool ok_button();//this functon programs the functionality for the ok button, the button will respond differently depending on the state the machine is in
        bool session_setup_button();//Sets the machine into the duration selection state which is the state the computer is in once it comes on
        bool record_session();//this button records the current session about to start
        bool unrecord_session();//this function is for when the record button is toggled off whoich will remove the session from the list of recorded sessions
        bool record_button(bool);//this is the button that is linked to the record button, if clicked will record the session if clicked again (toggled off) will remove the record of the session from the array
        bool replay_button(bool,string s);//this is the buttoin which sets the machine into the replay state and give the user access into the recorded sessions
        void no_connection(); //setts the connectivity to no conmnection
        void ok_connection(); //sets the connectivity to ok connection
        void ex_connection(); //sets the connetivity to excellent connection
        bool checkOffState();
        void setStateOff();
        int getBatteryLevel();
        int getBatteryState();
        int getcurrInt();

        void updateBattery(double x); //update the battery life after session is run
        void critically_low(); //critically low batterry
        void low_battery(); //low battery
        void ok_battery(); //sufficient battery
        bool battery_depletion(int duration, int intensity, bool connection); //calculates and updates battery level
        int get_battery_life();
        int connectionButton();
        void turnOff();
        void turnOn();
        //void start();

        //pid_t pid;
        //int ttp;
        //bool flag;


    private:
        Session recorded_sessions[ARR_SIZE]; //stores and array of recorded sessions
        int recorded; //this is the number of recorded sessions
        Session temp;// this is the temporary session that stores the infor ation for the session that the user will be running
        int curr_int;//while a session is going on this variable keeps track of the currently experienced intensity
        int state;//this is the variable that tracks what is currently happening in the machine, represented
        Battery* bat;//battery pointer
        Power* pow;
        Connection* con;




};

#endif // MACHINE_H
