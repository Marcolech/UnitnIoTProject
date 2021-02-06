#ifndef MARCOLECH_LEDCONTROLLER_H
#define MARCOLECH_LEDCONTROLLER_H

#include <stdint.h>
#include "driverlib.h"

typedef struct Led {
    uint_fast8_t port;
    uint_fast16_t pin;
} Led;

typedef struct RgbLed {
    Led red;
    Led green;
    Led blue;
} RgbLed;

void LED_init(Led *led);

void RGBLED_init(RgbLed *rgbLed);

void LED_on(Led *led);

void LED_off(Led *led);

#endif //MARCOLECH_LEDCONTROLLER_H
