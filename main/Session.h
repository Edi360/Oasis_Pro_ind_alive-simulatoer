#ifndef SESSION_H
#define SESSION_H

#include "QDebug"
#include "QDate"
#include "QTime"

using namespace std;

class Session{

    public:
        //constructor:
        Session();
        Session(int i, int dur, int in, int s);

        //getters+
        int get_duration();
        QDate get_date();
        QTime get_time();
        int get_intensity();
        int get_int();

        //setters
        void set_duration(int);
        void set_date(QDate);
        void set_time(QTime);
        void set_intensity(int);
        void set_int(int);

        //functions
        void print();

    private:
        int id; //uniqe id for the session
        int duration;//the length of time the session last for
        QDate date;//the date that the session was held ############ date type may be incorrect #############
        QTime time;//the time the sesion was held ################## time type may be incorrect #############
        int intensity;// the intensity of the session (goes hand in habd with type)
        int st;//this stores the type of session




};

#endif // SESSION_H
