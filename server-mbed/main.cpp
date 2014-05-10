#include "mbed.h"
#include "Drone.h"

int main() {
    Drone drone;
    drone.init();
    drone.run();
}
