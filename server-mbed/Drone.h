#ifndef DRONE_H
#define DRONE_H

#include "mbed.h"
#include "Gyroscope/Gyroscope.h"
#include "Accelerometre/ADXL345_I2C.h"
#include "Wifi/Wifly.h"
#include "Motor/Motor.h"

class Drone{
    public:
        Drone();
        ~Drone();
        void init();
        void run();
        
    private:
        void handleData();
        void onReceive();
        void attach_rx(bool null);
        
        Serial wifi;
        Gyroscope gyro;
        ADXL345_I2C accel;
        Motor motor0;
        Motor motor1;
        
        PwmOut led0;
        PwmOut led1;
        DigitalOut led2;
        DigitalOut led3;
        
        char buffer[256];
        int buf_pos;
        //Motor motor2;
        //Motor motor3;
};

#endif
