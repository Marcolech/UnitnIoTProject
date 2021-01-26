#ifndef MARCOLECH_BOOSTERPACKMK2_CONFIG_H_
#define MARCOLECH_BOOSTERPACKMK2_CONFIG_H_

//Analog to digital read configuration
#define BPM2_ADC_MEM_START                  ADC_MEM0
#define BPM2_ADC_MEM_END                    ADC_MEM5


#define BPM2_ACCEL_ADC_MEM_X                ADC_MEM0
#define BPM2_ACCEL_ADC_MEM_Y                ADC_MEM1
#define BPM2_ACCEL_ADC_MEM_Z                ADC_MEM2
#define BPM2_ACCEL_ADC_INTERRUPT            ADC_INT0

#define BPM2_JOYSTICK_ADC_MEM_X             ADC_MEM3
#define BPM2_JOYSTICK_ADC_MEM_Y             ADC_MEM4
#define BPM2_JOYSTICK_ADC_INTERRUPT         ADC_INT3

#define BPM2_MICROPHONE_ADC_MEM_Y           ADC_MEM5
#define BPM2_MICROPHONE_ADC_INTERRUPT       ADC_INT5

#endif /* MARCOLECH_BOOSTERPACKMK2_CONFIG_H_ */
