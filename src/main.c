#include "config.h"
#include "driverlib.h"
#include "msp.h"

#include <marcolech/utils/delay.h>
#include <marcolech/utils/ledController.h>
#include <marcolech/network/networkManager.h>
#include <marcolech/boosterPack/boosterPack.h>

UART esp8266Uart;
UART pc;
Led debugLed;
RgbLed rgbLed;

volatile bool running = true;

void init() {
    // stop watchdog timer
    MAP_WDT_A_holdTimer();

    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_24);

    // Set the core voltage level to VCORE1
    PCM_setCoreVoltageLevel(PCM_VCORE1);

    // Set 2 flash wait states for Flash bank 0 and 1
    FlashCtl_setWaitState(FLASH_BANK0, 2);
    FlashCtl_setWaitState(FLASH_BANK1, 2);

    // Initializes Clock System
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);

    // Init delay functionality
    delay_init();

    // LED CONFIG
    // debug led
    debugLed.port = GPIO_PORT_P1;
    debugLed.pin = GPIO_PIN0;
    LED_init(&debugLed);
    // rgb led
    rgbLed.red.port = GPIO_PORT_P2;
    rgbLed.red.pin = GPIO_PIN6;
    rgbLed.green.port = GPIO_PORT_P2;
    rgbLed.green.pin = GPIO_PIN4;
    rgbLed.blue.port = GPIO_PORT_P5;
    rgbLed.blue.pin = GPIO_PIN6;
    RGBLED_init(&rgbLed);

    // Esp8266 uart communication
    esp8266Uart.uart = EUSCI_A2_BASE;
    esp8266Uart.uartConfig = UART115200Config;
    UART_init(&esp8266Uart);

    // USB communication
    pc.uart = EUSCI_A0_BASE;
    pc.uartConfig = UART9600Config;
    UART_init(&pc);

    // init booster pack hardware
    BPM2_initHardware();

    // Init network library
    NETWORK_init();

    MAP_Interrupt_enableMaster();
}

bool wifiConnectToAP(UART *wifi) {
    UART_flush(wifi);
    delay(1);
    if (!ESP8266_checkUartCommunication(wifi)) {
        UART_printString(&pc, "No serial connection to wifi board\r\n");
        return false;
    }


    if (!ESP8266_factoryReset(wifi)) {
        UART_printString(&pc, "Error factory reset\r\n");
        return false;
    }
    UART_flush(wifi);
    delay(1);

    // set client wifi mode
    if (!ESP8266_setWifiMode(wifi, ESP8266_WIFI_MODE_CLIENT)) {
        UART_printString(&pc, "Error setting wifi mode\r\n");
        return false;
    }

    // connect to AP
    if (!ESP8266_connectToAP(wifi, NETWORK_WIFI_SSID, NETWORK_WIFI_PASSWORD)) {
        UART_printString(&pc, "Error connecting to wifi\r\n");
        return false;
    }


    return true;

}

bool wifiSendData(UART *wifi) {
    LED_on(&debugLed);
    UART_flush(wifi);
    delay(1);

    // open connection
    if (!ESP8266_establishSingleConnection(wifi, ESP8266_UDP, NETWORK_UDP_SERVER_IP, NETWORK_UDP_SERVER_PORT)) {
        UART_printString(&pc, "Error connecting udp server\r\n");
        return false;
    }


    long double temp = THERMO_getCelsius();
    int intTemp = (int) temp;
    UART_printf(&pc, "Temperature: %d\r\n", intTemp);

    char buffer[2048];

    sprintf(buffer, "{\"site\":\"%s\",\"field\":\"%s\",\"value\":%d}", BOARD_ROOM, "temperature", intTemp);
    unsigned int bufferLen = strlen(buffer);
//    UART_printf(&pc, "Sending [%d]: |%s|\r\n", bufferLen, buffer);

    // send data
    if (!ESP8266_sendDataSingleConnection(wifi, buffer, bufferLen)) {
        UART_printString(&pc, "Error sending data to udp server\r\n");
        return false;
    }

    // close connection
    if (!ESP8266_closeConnection(wifi)) {
        UART_printString(&pc, "Error closing udp connection\r\n");
        return false;
    }
    LED_off(&debugLed);

    return true;
}

void run() {

    LED_on(&debugLed);
    if (wifiConnectToAP(&esp8266Uart)) {
        LED_off(&debugLed);

        while (wifiSendData(&esp8266Uart) != false) {
            delay(5);
        }


    }
}

int main(void) {
    init();
    UART_printString(&pc, "Init done\r\n");

    while (running) {
        run();

        UART_printString(&pc, "Connection error, reconnect\r\n");
    }

    UART_printString(&pc, "Go sleep\r\n");
    PCM_gotoLPM0();
}

void BPM2_accel_onNewData(uint16_t x, uint16_t y, uint16_t z) {
//    UART_printf(&pc, "Coordinates [%d,%d,%d]\n\r", x, y, z);
}

void BPM2_joystick_onNewData(uint16_t x, uint16_t y, int pressed) {
//    UART_printf(&pc, "Joystick [%d,%d,%d]\n\r", x, y, pressed);
}

void ADC14_IRQHandler(void) {
    uint64_t status;

    status = MAP_ADC14_getEnabledInterruptStatus();
    MAP_ADC14_clearInterruptFlag(status);

    BPM2_accel_ADC14_IRQHandler(status);
    BPM2_joystick_ADC14_IRQHandler(status);

}
