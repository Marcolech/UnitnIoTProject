#include "boosterPack.h"

void BPM2_initHardware()
{
    // *********************************************************
    // Init I2C and temperature sensor
    // *********************************************************
    I2C_init();
    TMP006_init();

    // *********************************************************
    // Initializing ADC (ADCOSC/64/8)
    // *********************************************************
    // Setting reference voltage to 2.5  and enabling reference
    MAP_REF_A_setReferenceVoltage(REF_A_VREF2_5V);
    MAP_REF_A_enableReferenceVoltage();
    //enable analog to digital converter module
    ADC14_enableModule();
    ADC14_initModule(ADC_CLOCKSOURCE_ADCOSC,
                     ADC_PREDIVIDER_64,
                     ADC_DIVIDER_8,
                     0);

    // *********************************************************
    // Configures ADC input
    // *********************************************************

    //accelerometer
    GPIO_setAsPeripheralModuleFunctionInputPin(BPM2_ACCEL_X_PORT,
                                               BPM2_ACCEL_X_PORT,
                                               GPIO_TERTIARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionInputPin(BPM2_ACCEL_Y_PORT,
                                               BPM2_ACCEL_Y_PORT,
                                               GPIO_TERTIARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionInputPin(BPM2_ACCEL_Z_PORT,
                                               BPM2_ACCEL_Z_PORT,
                                               GPIO_TERTIARY_MODULE_FUNCTION);

    //joystick
    GPIO_setAsPeripheralModuleFunctionInputPin(BPM2_JOYSTICK_X_PORT,
                                               BPM2_JOYSTICK_X_PIN,
                                               GPIO_TERTIARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionInputPin(BPM2_JOYSTICK_Y_PORT,
                                               BPM2_JOYSTICK_Y_PIN,
                                               GPIO_TERTIARY_MODULE_FUNCTION);

    // *********************************************************
    // Configuring ADC Memory with repeat
    // with internal 2.5v reference
    // *********************************************************
    // enable multi sequence mode
    ADC14_configureMultiSequenceMode(BPM2_ADC_MEM_START,
                                     BPM2_ADC_MEM_END,
                                     true);
    // accelerometer
    ADC14_configureConversionMemory(BPM2_ACCEL_ADC_MEM_X,
                                    ADC_VREFPOS_AVCC_VREFNEG_VSS,
                                    BPM2_ACCEL_X_ANALOG,
                                    ADC_NONDIFFERENTIAL_INPUTS);
    ADC14_configureConversionMemory(BPM2_ACCEL_ADC_MEM_Y,
                                    ADC_VREFPOS_AVCC_VREFNEG_VSS,
                                    BPM2_ACCEL_Y_ANALOG,
                                    ADC_NONDIFFERENTIAL_INPUTS);
    ADC14_configureConversionMemory(BPM2_ACCEL_ADC_MEM_Z,
                                    ADC_VREFPOS_AVCC_VREFNEG_VSS,
                                    BPM2_ACCEL_Z_ANALOG,
                                    ADC_NONDIFFERENTIAL_INPUTS);
    // joystick
    ADC14_configureConversionMemory(BPM2_JOYSTICK_ADC_MEM_X,
                                    ADC_VREFPOS_AVCC_VREFNEG_VSS,
                                    BPM2_JOYSTICK_X_ANALOG,
                                    ADC_NONDIFFERENTIAL_INPUTS);

    ADC14_configureConversionMemory(BPM2_JOYSTICK_ADC_MEM_Y,
                                    ADC_VREFPOS_AVCC_VREFNEG_VSS,
                                    BPM2_JOYSTICK_Y_ANALOG,
                                    ADC_NONDIFFERENTIAL_INPUTS);

    // *********************************************************
    // Enabling the interrupt when a conversion on channel 5 (end of sequence)
    // is complete and enabling conversions
    // *********************************************************
    MAP_ADC14_enableInterrupt(BPM2_ACCEL_ADC_INTERRUPT|BPM2_JOYSTICK_ADC_INTERRUPT);

    //Enabling Interrupts
    MAP_Interrupt_enableInterrupt(INT_ADC14);
    MAP_Interrupt_enableMaster();

    //Setting up the sample timer to automatically step through the sequence convert
    MAP_ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);

    //Triggering the start of the sample
    MAP_ADC14_enableConversion();
    MAP_ADC14_toggleConversionTrigger();
}
