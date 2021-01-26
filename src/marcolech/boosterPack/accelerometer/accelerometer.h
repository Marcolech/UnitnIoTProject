#ifndef MARCOLECH_BOOSTERPACKMK2_ACCELEROMETER_H_
#define MARCOLECH_BOOSTERPACKMK2_ACCELEROMETER_H_

#include "stdint.h"
#include "driverlib.h"
#include "msp.h"
#include <marcolech/boosterPack/config.h>

//Accelerometer
//X   P6.1    A14     ADC_MEM0
//Y   P4.0    A13     ADC_MEM1
//Z   P4.2    A11     ADC_MEM2

#define BPM2_ACCEL_X_PORT       GPIO_PORT_P6
#define BPM2_ACCEL_X_PIN        GPIO_PIN1
#define BPM2_ACCEL_X_ANALOG     ADC_INPUT_A14

#define BPM2_ACCEL_Y_PORT       GPIO_PORT_P4
#define BPM2_ACCEL_Y_PIN        GPIO_PIN0
#define BPM2_ACCEL_Y_ANALOG     ADC_INPUT_A13

#define BPM2_ACCEL_Z_PORT       GPIO_PORT_P4
#define BPM2_ACCEL_Z_PIN        GPIO_PIN2
#define BPM2_ACCEL_Z_ANALOG     ADC_INPUT_A11


//Call this operations in ADC14_IRQHandler()
void BPM2_accel_ADC14_IRQHandler(uint64_t status);

//define this to get new data
extern void BPM2_accel_onNewData(uint16_t x, uint16_t y, uint16_t z);

#endif /* MARCOLECH_BOOSTERPACKMK2_ACCELEROMETER_H_ */
