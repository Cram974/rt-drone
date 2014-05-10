#ifndef WIFLY_H
#define WIFLY_H

#include "mbed.h"

class Wifly{
    public:
        Wifly(PinName tx, PinName rx);
        ~Wifly();

        void init();
        void putc(char c);
        void send(const char * data,int length);

        //Setters
        //Getters

    private:
        Serial serial;

        void flush();
        void onReceive();
        bool wait_Data();
        bool write(char* message);
        bool writeCMD(char* message, char* ack=NULL);
        bool cmdMode();
};

#endif
