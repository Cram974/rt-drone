#include "Drone.h"

Drone::Drone():wifi(p13,p14), 
               gyro(p9, p10, p11),
               accel(p9, p10),
               motor0(p21),
               motor1(p22),
               led0(LED1),
               led1(LED2),
               led2(LED3),
               led3(LED4){
}

Drone::~Drone(){
}

void Drone::init(){
    accel.setPowerControl(0x00);
    accel.setDataFormatControl(0x0B);
    accel.setDataRate(ADXL345_3200HZ);
    accel.setPowerControl(MeasurementMode);
    
    gyro.init();
    gyro.setSMPLRT_DIV(SRD_NONE);//Pas de Sample Rate Divider
    gyro.setDLPF_FS(DLPF_BW098_SR1|FS_RANGE2000);//Full scale +/-2000
    gyro.setINT_CFG(INT_DATA_AVBLE_EN|INT_READ_ANYREG);//Activation des interruptions
    gyro.setPWR_MGM(PW_INTERNALOSC);//Utilisation de l'oscillateur interne
    
    motor0.init();
    motor1.init();
    
    buf_pos = 0;
    
    wifi.baud(57600);
    this->attach_rx(true);
    
    led0=0;
    led1=0;
    
    wait(1);
    
}

void Drone::attach_rx(bool null) {
    if (!null)
        wifi.attach(NULL);
    else
         wifi.attach(this, &Drone::onReceive, Serial::RxIrq);
}

void Drone::onReceive(){   
    char c = wifi.getc();
    
    if(c!='$'){
        buffer[buf_pos++] = c;
    }
    
    buffer[buf_pos] = 0;
    
    if(c=='$')
        this->handleData();
}

void Drone::handleData(){
    switch(buffer[0]){
        case 's':
            int percent = 0;
            if(sscanf(buffer, "set motor speed 1 %i$", &percent)){
                led0 = percent/100.0;
                motor0.setSpeed(percent);
                led1 = percent/100.0;
                motor1.setSpeed(percent);
            }
            break;
        default:
            printf("%s\r\n", buffer); 
            break;
    }
    
    buf_pos = 0;
}

void Drone::run(){
    int readings[3] = {0, 0, 0};
    while(1){
        //read sensors
        gyro.read_Sensors();
        accel.getOutput(readings);
        
        this->attach_rx(false);
        //send gyroscope values
        wifi.printf("set gyro 3 %i %i %i$", gyro.getX(), gyro.getY(), gyro.getZ());
        
        //send accelerometer values
        wifi.printf("set acc 3 %i %i %i$", readings[0], readings[1], readings[2]);
        this->attach_rx(true);
        wait(0.01);
    }
}

