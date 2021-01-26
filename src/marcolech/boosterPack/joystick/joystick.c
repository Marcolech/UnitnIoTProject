#include "joystick.h"

//Call this operations in ADC14_IRQHandler()
void BPM2_joystick_ADC14_IRQHandler(uint64_t status)
{
    // ADC MEM conversion completed
    if (status & BPM2_JOYSTICK_ADC_INTERRUPT)
    {
        //Store ADC14 conversion results
        uint16_t x = ADC14_getResult(BPM2_JOYSTICK_ADC_MEM_X);
        uint16_t y = ADC14_getResult(BPM2_JOYSTICK_ADC_MEM_Y);

        //Determine if JoyStick button is pressed
        int buttonPressed = 0;
        if (!(P4IN & GPIO_PIN1))
        {
            buttonPressed = 1;
        }

        BPM2_joystick_onNewData(x, y, buttonPressed);
    }
}
