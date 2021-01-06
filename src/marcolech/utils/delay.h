#ifndef SRC_MARCOLECH_DELAY_H_
#define SRC_MARCOLECH_DELAY_H_

#include "driverlib.h"
#include "msp.h"

#define DELAY_RUNNING 0
#define DELAY_GONE 1
#define DELAY_TIMER_FREQUENCY_HZ 128000

extern void delay_init(void);

extern void delay(uint32_t sec);

#endif /* SRC_MARCOLECH_DELAY_H_ */
