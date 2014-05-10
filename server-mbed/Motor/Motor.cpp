#include "Motor.h"

Motor::Motor(PinName p):esc(p){
}

Motor::~Motor(){
}

void Motor::init(){
    esc.period_ms(22);
    //5sec --> mode programmation
    //3sec par menu
}

void Motor::setSpeed(float percent){
    if(0 <= percent && percent <= 100)
        esc.pulsewidth_us(1000 + percent*10);
}