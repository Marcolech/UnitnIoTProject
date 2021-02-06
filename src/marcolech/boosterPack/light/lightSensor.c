#include "lightSensor.h"

void LIGHT_init(){
    OPT3001_init();
}

unsigned long int LIGHT_getLux(){
    return OPT3001_getLux();
}