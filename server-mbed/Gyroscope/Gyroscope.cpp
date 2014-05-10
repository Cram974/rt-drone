#include "mbed.h"
#include "Gyroscope.h"

//**************
//PUBLIC Methods
//**************
Gyroscope::Gyroscope(PinName sda, PinName scl, PinName inter):i2c(sda,scl), interrupt(inter){
    this->address = ITG3200_ADDR_AD0_HIGH;
    this->interrupt.rise(this, &Gyroscope::onDataAvailable);
}
Gyroscope::~Gyroscope(){
}

void Gyroscope::init(){
    i2c.frequency(400000);     //400kHz 400000
    wait_ms(GYROSTART_UP_DELAY);
}

void Gyroscope::read_Sensors(){
    char buffer[8];
    this->read_Raw( TEMP_OUT, buffer, 8 );
    for(int i = 0;i<4;i++)
        this->txyz[i] = (short)((buffer[i*2]<<8)+buffer[i*2+1]);
}

void Gyroscope::read_InterruptStatus(){
    this->int_status = this->read(INT_STATUS);
}


//Setters
void Gyroscope::setWHO_AM_I(char param){
    this->write(WHO_AM_I, param);
    this->address = param;
}
void Gyroscope::setSMPLRT_DIV(char param){
    this->write(SMPLRT_DIV, param);
}
void Gyroscope::setDLPF_FS(char param){
    this->write(DLPF_FS, param);
}
void Gyroscope::setINT_CFG(char param){
    this->write(INT_CFG, param);
}
void Gyroscope::setPWR_MGM(char param){
    this->write(PWR_MGM, param);
}

//Getters
char Gyroscope::getIntStatus(){
    return this->int_status;
}

short Gyroscope::getX(){
    return this->txyz[1];
}
short Gyroscope::getY(){
    return this->txyz[2];
}
short Gyroscope::getZ(){
    return this->txyz[3];
}

short Gyroscope::getTemp(){
    return 35 + (this->txyz[0] + 13200) / 280.0;
    //return this->txyz[0];
}

char Gyroscope::getWHO_AM_I(){
    return this->address;
}
char Gyroscope::getSMPLRT_DIV(){
    return this->read(SMPLRT_DIV);
}
char Gyroscope::getDLPF_FS(){
    return this->read(DLPF_FS);
}
char Gyroscope::getINT_CFG(){
    return this->read(INT_CFG);
}
char Gyroscope::getPWR_MGM(){
    return this->read(PWR_MGM);
}

//***************
//PRIVATE Methods
//***************

void Gyroscope::onDataAvailable(){
    read_Sensors();
}

char Gyroscope::read(char reg_addr){
    char val = 0x00;

    i2c.write((int)((this->address<<1)), &reg_addr, 1);
    i2c.read((int)((this->address<<1)+1), &val, 1);
    return val;
}

void Gyroscope::write(char reg_addr, char val){
    char buff[2];
    buff[0] = reg_addr;
    buff[1] = val;

    i2c.write((int)((this->address<<1)), buff, 2);
}

void Gyroscope::read_Raw(char start_reg_addr, char* buffer, int length){
        i2c.write((int)((this->address<<1)), &start_reg_addr, 1);
        i2c.read((int)((this->address<<1)+1), buffer, length);
}

void Gyroscope::write_Raw(char start_reg_addr, char* buffer, int length){
        char send_buffer[length+1];
        send_buffer[0] = start_reg_addr;
        for(int i =0;i<length;i++){
            send_buffer[i+1] = buffer[i];
        }

        i2c.write((int)((this->address<<1)), send_buffer, 2);
}

