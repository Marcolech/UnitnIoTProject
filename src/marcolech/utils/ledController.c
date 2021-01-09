#include "ledController.h"

void LED_init(Led *led) {
    GPIO_setAsOutputPin(led->port, led->pin);
    LED_off(led);
}

void RGBLED_init(RgbLed *rgbLed) {
    LED_init(&rgbLed->red);
    LED_init(&rgbLed->green);
    LED_init(&rgbLed->blue);
}

void LED_on(Led *led) {
    GPIO_setOutputHighOnPin(led->port, led->pin);
}

void LED_off(Led *led) {
    GPIO_setOutputLowOnPin(led->port, led->pin);
}