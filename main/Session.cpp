#include "Session.h"

//constructor:
Session::Session(){//date and time havent been set up
	id=-1;
	duration=0;
	intensity=0;
    st=0;
}

Session::Session(int i, int dur, int in, int s){//date and time havent been set up
	id=i;
	duration=dur;
	intensity=in;
    st=s;
}

//getters
int Session::get_duration(){return duration;}

int Session::get_intensity(){return intensity;}

int Session::get_int(){return st;}

//setters
void Session::set_duration(int d){duration=d;}

void Session::set_intensity(int i){intensity=i;}

void Session::set_int(int s){st=s;}

//functions
void Session::print(){
    qDebug()<<" duration: "<<duration<<"\n intensity: "<<intensity<<"\n type: "<<st;

}








