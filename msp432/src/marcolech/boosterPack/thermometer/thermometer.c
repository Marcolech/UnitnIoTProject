#include "thermometer.h"


double THERMO_getKelvin(void){
    return TMP006_getKelvin();
}
double THERMO_getFahrenheit(void){
    return TMP006_getFahrenheit();
}
double THERMO_getCelsius(void){
    return TMP006_getCelsius();
}