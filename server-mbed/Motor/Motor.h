#ifndef MOTOR_H
#define MOTOR_H
#include "mbed.h"

class Motor{
    public:
        Motor(PinName p);
        ~Motor();
        
        void init();
        void setSpeed(float percent);
      
    private:
        PwmOut esc;
        
};

#endif
