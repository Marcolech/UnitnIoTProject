#include "accelerometer.h"

//Call this operations in ADC14_IRQHandler()
void BPM2_accel_ADC14_IRQHandler(uint64_t status) {
    //ADC_MEM conversion completed
    if (status & BPM2_ACCEL_ADC_INTERRUPT) {
        // Store ADC14 conversion results
        uint16_t x = ADC14_getResult(BPM2_ACCEL_ADC_MEM_X);
        uint16_t y = ADC14_getResult(BPM2_ACCEL_ADC_MEM_Y);
        uint16_t z = ADC14_getResult(BPM2_ACCEL_ADC_MEM_Z);

        BPM2_accel_onNewData(x, y, z);
    }
}