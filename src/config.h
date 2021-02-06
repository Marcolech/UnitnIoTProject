#ifndef UNITNIOTPROJECT_CONFIG_H
#define UNITNIOTPROJECT_CONFIG_H

#include "driverlib.h"

/* UART Configuration Parameter.
 * These values were calculated using the online calculator that TI provides at:
 * http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html
 * (msp432 use the same chip as 430)
 */
eUSCI_UART_Config UART115200Config =
        {
                EUSCI_A_UART_CLOCKSOURCE_SMCLK,
                13,
                0,
                37,
                EUSCI_A_UART_NO_PARITY,
                EUSCI_A_UART_LSB_FIRST,
                EUSCI_A_UART_ONE_STOP_BIT,
                EUSCI_A_UART_MODE,
                EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION
        };

eUSCI_UART_Config UART9600Config =
        {
                EUSCI_A_UART_CLOCKSOURCE_SMCLK,
                156,
                4,
                0,
                EUSCI_A_UART_NO_PARITY,
                EUSCI_A_UART_LSB_FIRST,
                EUSCI_A_UART_ONE_STOP_BIT,
                EUSCI_A_UART_MODE,
                EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION,
        };

// network
#define NETWORK_WIFI_SSID "YourWifiSSID"
#define NETWORK_WIFI_PASSWORD "WifiPassword"
#define NETWORK_UDP_SERVER_IP "192.168.1.100"
#define NETWORK_UDP_SERVER_PORT 25000

#define BOARD_ROOM "MyRoom"
#define BOARD_LUX_THRESHOLD_LIGHT_ON 400
#define BOARD_LUX_THRESHOLD_LIGHT_OFF 700


#endif //UNITNIOTPROJECT_CONFIG_H
