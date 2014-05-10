#include "mbed.h"
#include "Wifly.h"

//**************
//PUBLIC Methods
//**************
Wifly::Wifly(PinName tx, PinName rx):serial(tx,rx){
    serial.attach(this, &Wifly::onReceive, Serial::RxIrq);
}

Wifly::~Wifly(){
}

void Wifly::init(){
    serial.baud(921600);
}

void Wifly::putc(char c){
    while(!serial.writeable());
    serial.putc(c);
}

void Wifly::send(const char * data,int length){
    for(int i=0; i<length; i++)
        this->putc(data[i]);
}

//***************
//PRIVATE Methods
//***************

void Wifly::onReceive(){
    //printf("Data Received!!\r\n");
    char cmd[255];    
    serial.scanf("", cmd);
    printf("%s\r\n",cmd);
    //this->flush();
}
void Wifly::flush(){
    while(serial.readable()){
        char c = serial.getc();
        printf("%c", c);
        if(c=='\r')printf("\n");
    }
}

bool Wifly::write(char* message){    
    int i=0;
    while(message[i]){
        if(serial.writeable()){
            printf("%c", message[i]);
            serial.putc(message[i++]);
        }
    }
    printf("\n");
    return true;
}

bool Wifly::writeCMD(char* message, char* expected){    
    char buffer [128];
    sprintf (buffer, "%s\r", message);
    return write(buffer);
}

bool Wifly::cmdMode(){
    write("$$$");
    wait(2);
    return true;
}