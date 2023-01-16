#include "Machine.h"
#include <sys/types.h>

//constructor:
Machine::Machine(){
    temp=Session();
    recorded=0;
    curr_int=0;
    state=0;
    bat=new Battery(100);
    pow= new Power(bat);
    con = new Connection();
    //flag = false;
}

//getters

int Machine::getState(){
    return state;
}

void Machine::setRecorded(int i){
    recorded = i;
}

int Machine::getTempInt(){
    return temp.get_intensity();
}

void Machine::setTemp(Session s){
    temp = s;
}
void Machine::setCurrInt(int i){
    curr_int = i;
}

Session* Machine::get_recorded_session(){
    return recorded_sessions;
}

Session Machine::get_session(int i){
    return recorded_sessions[i];
}

string Machine::session_string(Session s,int i){
    string st;


    string type;
    switch(s.get_int()){
        case 1:
            type="met";
            break;
        case 2:
            type="sub-delta";
            break;

        case 3:
            type="delta";
            break;

        case 4:
            type="sub";
            break;
        default:
            type="null";
        break;

    }
    st=""+to_string(i)+" Rec: Duration="+to_string(s.get_duration())+", Intensity="+to_string(s.get_intensity())+", Type="+type;


    return st;

}

int Machine::get_recorded(){return recorded;}

int Machine::getcurrInt(){return curr_int;}

Session Machine::get_temp(){return temp;}

Battery* Machine::get_battary(){return bat;}

Power* Machine::get_power(){return pow;}

void Machine::updateBattery(double x){bat->updateBattery(x);}

void Machine::critically_low(){bat->critically_low();}

void Machine::low_battery(){bat->low_battery();}

void Machine::ok_battery(){bat->ok_battery();}

bool Machine::checkOffState(){
    if(state == 0){
        return true;
    }
    return false;
}

bool Machine::battery_depletion(int duration, int intensity, bool connection){return bat->battery_depletion(duration,intensity,connection);}

int Machine::get_battery_life(){return bat->get_battery_life();}



//functions
void Machine::setState(int i){
    state = i;
}

void Machine::setStateOff(){
    state = 0;
}

void Machine::setTempInt(int i){
    temp.set_intensity(i);

}

void Machine::setTempDur(int i){
    temp.set_duration(i);

}
void Machine::setTempType(int i){
    temp.set_int(i);
}

bool Machine::add_recorded_session(Session s){

    if (recorded>=ARR_SIZE){
        qDebug()  <<"recorded sessions at maximum capacity";
        return false;
    }

    recorded_sessions[recorded]=s;
    qDebug()  <<"session has succesfuly been recorded";
    return true;

}

bool Machine::start_session(Session s){

    if (bat->battery_depletion(temp.get_duration(),temp.get_intensity(),true)<=0 && temp.get_duration()!=-1){// i set the connectiovity to true teporarily
             qDebug()  <<"Battery is not sufficuent";

            return false;
    }

    if (temp.get_duration()==-1){
            qDebug() <<"Intensisty is "<<temp.get_intensity()<<", the machine will turn of when the battery dies or you turn of the machine";
            QThread::sleep(bat->battery_depletion(temp.get_duration(),temp.get_intensity(),true));

            return true;
        }


    if (con->getNum()==8){
        qDebug() <<"Error: No connection";
        return false;

    }

    int intensity=s.get_intensity();
    int duration=s.get_duration();//gets duration of the session
    int sid=(duration/((intensity*2)-1));//this is the single intensity duration which isa the duration of time spoent on a single intensity
//    this->flag = true;
//    pid = fork();
//    ttp = getpid();
//    if(pid==0){
//        for(int i =1; i<intensity+1; i++){
//            curr_int=1;
//            QThread::sleep(sid);

//        }


    for (int i=1;i<intensity+1;i++){//loop which gradualy increases the intendsity over half the duration of time
        curr_int=i;
        qDebug()<<i;
        QThread::sleep(sid);


    }

    for (int i=intensity;i>0;i--){//loop which gradualy decreases the intendsity over half the duration of time
        intensity=i;
        qDebug()<<i;
        QThread::sleep(sid);
    }

    if (temp.get_duration()!=-1){
           bat->updateBattery(bat->battery_depletion(temp.get_duration(),temp.get_intensity(),true));
           qDebug() <<"Battery level: " << bat->get_battery_life();
       }

    qDebug()<<"Session completed";
    state=0;
    temp=Session();
    return true;
}



bool Machine::ok_button(){

    if (state==1){//when in duration setting state

        //#### if the system stays in this state for too long it turns off ###############

        if (temp.get_duration()==0){//if the user has not clkicked one of the onscrean duration buttons
            qDebug()  <<"Error: A duration has not been selected";
            return false;
        }


        state=2;// changes machione state to the intesity and type selection state

        return true;
    }

    else if (state==2){//when in intensity and type setting state
        if (temp.get_int()==0){//if the user has not clkicked one of the onscrean sesson type buttons
            qDebug()  <<"Error: A session type has not been selected";
            return false;
        }

        if (temp.get_intensity()==0){//if the user has not clkicked one of the onscrean intensity
            qDebug()  <<"Error: An intensity has not been selected";
            return false;
        }

        state=3;//changes the machine to the connectivity test state






        return true;
    }

    if (state==3){

        if (con->getNum()<=0){
            qDebug() <<"Error: connection test hasnt been run";
            return false;
        }

        state=4;

        qDebug() <<"Session running";

        if (start_session(temp)==false){
            qDebug() <<"session failed: battery level cannot support the chosen settings";
            state=1;

            qDebug() <<"after session start";
            temp=Session();

        }

        pow->soft_off();
        return true;

    }

    else if (state==6){


        state=3;
        return true;
    }

    else if (state==5){//when a recorded session is selected to be played
        if ((temp.get_int()==0) || temp.get_intensity()==0 || temp.get_duration()==0){
            qDebug() <<"Error: recorded Session is not runnable";
            return false;
        }

        state=3;
        return true;
    }

    return false;

}

bool Machine::record_session(){
    if (recorded>=ARR_SIZE){//checks if array is full
        qDebug()  <<"Error: array of reccorded sessions is full, cant add any sessions";
        return false;
    }

    recorded_sessions[recorded]=temp;
    recorded++;

    return true;
}

bool Machine::unrecord_session(){
    if (recorded){//checks if array is empty
        qDebug()  <<"Error: array of reccorded sessions is empty, cant remove any sessions";
        return false;
    }

    recorded_sessions[recorded]=Session();
    recorded--;
    return true;
}

bool Machine::record_button(bool b){
    if (b){// if the button is toggled
        return record_session();
    }

    return unrecord_session();
}

bool Machine::replay_button(bool b,string s){
    if (b){// if the button is toggled
        int si = atoi(&s[0]);
        temp=recorded_sessions[si];
        state=3;
        return true;
    }

    state=1;
    temp=Session();

    return true;

}


void Machine::no_connection(){
    con->no_connection();
}

void Machine::ok_connection(){
    con->ok_connection();
}

void Machine::ex_connection(){
    con->ex_connection();
}





int Machine::connectionButton(){
//    con->no_connection();
    con->ok_connection();
//    con->ex_connection();
    return con->test_mode();
}

void Machine::turnOff(){
    pow->turn_off();
}

void Machine::turnOn(){
    pow->turn_on();
}

int Machine::getBatteryLevel(){
    return bat->get_battery_life();
}

int Machine::getBatteryState(){
    bat->getState();
}








