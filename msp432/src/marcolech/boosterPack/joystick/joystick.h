#ifndef MARCOLECH_BOOSTERPACKMK2_JOYSTICK_H_
#define MARCOLECH_BOOSTERPACKMK2_JOYSTICK_H_

#include "stdint.h"
#include "driverlib.h"
#include "msp.h"
#include <marcolech/boosterPack/config.h>


//Joystick
//X   P6.0    A15     ADC_MEM3
//Y   P4.4    A9      ADC_MEM4

#define BPM2_JOYSTICK_X_PORT        GPIO_PORT_P6
#define BPM2_JOYSTICK_X_PIN         GPIO_PIN0
#define BPM2_JOYSTICK_X_ANALOG      ADC_INPUT_A15

#define BPM2_JOYSTICK_Y_PORT        GPIO_PORT_P4
#define BPM2_JOYSTICK_Y_PIN         GPIO_PIN4
#define BPM2_JOYSTICK_Y_ANALOG      ADC_INPUT_A9

//Call this operations in ADC14_IRQHandler()
void BPM2_joystick_ADC14_IRQHandler(uint64_t status);

//define this to get new data
extern void BPM2_joystick_onNewData(uint16_t x, uint16_t y, int pressed);

#endif // MARCOLECH_BOOSTERPACKMK2_JOYSTICK_H_
