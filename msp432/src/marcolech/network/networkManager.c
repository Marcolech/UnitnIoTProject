#include "networkManager.h"

void NETWORK_init() {
    // set MSP432 to run at 24 MHz
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_24);
    FlashCtl_setWaitState(FLASH_BANK0, 2);
    FlashCtl_setWaitState(FLASH_BANK1, 2);
    PCM_setCoreVoltageLevel(PCM_VCORE1);
}
