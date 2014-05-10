#ifndef GYRO_H
#define GYRO_H

#include "mbed.h"
#include "Gyro_def.h"

//API for 
//GYROSCOPE MODEL ITG3200

class Gyroscope{
    public:
        Gyroscope(PinName sda, PinName scl, PinName inter);
        ~Gyroscope();

        void init();

        void read_Sensors();
        void read_InterruptStatus();

        //Setters
        void setWHO_AM_I(char param);
        void setSMPLRT_DIV(char param);
        void setDLPF_FS(char param);
        void setINT_CFG(char param);
        void setPWR_MGM(char param);

        //Getters
        char  getIntStatus();
        short getX();
        short getY();
        short getZ();
        short getTemp();

        char getWHO_AM_I();
        char getSMPLRT_DIV();
        char getDLPF_FS();
        char getINT_CFG();
        char getPWR_MGM();

    private:
        I2C i2c;
        InterruptIn interrupt;
        
        char address;
        char int_status;
        short txyz[4];
        
        void onDataAvailable();
        
        char read(char reg_addr);
        void write(char reg_addr, char val);
        void read_Raw(char start_reg_addr, char* buffer, int length);
        void write_Raw(char start_reg_addr, char* buffer, int length);
};

#endif

