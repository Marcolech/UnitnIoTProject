#include "esp8266.h"

bool ESP8266_waitForAnswer(UART *uart) {
    uint32_t c;
    uint32_t i = 0;

    uint32_t tries = ESP8266_RECEIVE_TRIES;

    while (tries) {
        if (UART_available(uart)) {
            while (UART_available(uart)) {
                UART_read(uart, (uint8_t *) &c, 1);

                if (i > ESP8266_BUFFER_SIZE) {
                    return false;
                } else {
                    uart->buffer[i++] = (char) c;
                }
            }

            uart->buffer[i] = 0;
            return true;
        }
        tries--;
        delay(1);
    }

    return false;
}

bool ESP8266_checkUartCommunication(UART *uart) {
    UART_printf(uart, "%s\r\n", AT);

    if (!ESP8266_waitForAnswer(uart)) {
        return false;
    }

    if (strstr((char *) uart->buffer, "OK") == NULL) {
        return false;
    }

    return true;
}

bool ESP8266_setWifiMode(UART *uart, char wifiMode) {
    UART_printf(uart, "%s=%c\r\n", AT_CWMODE, wifiMode);

    if (!ESP8266_waitForAnswer(uart)) {
        return false;
    }

    if (strstr((char *) uart->buffer, "OK") == NULL) {
        return false;
    }

    return true;
}

bool ESP8266_availableAPs(UART *uart) {
    UART_printf(uart, "%s\r\n", AT_CWLAP);
    delay(10);
    if (!ESP8266_waitForAnswer(uart)) {
        return false;
    }

    if (strstr((char *) uart->buffer, "OK") == NULL) {
        return false;
    }

    return true;
}

bool ESP8266_connectToAP(UART *uart, char *SSID, char *Password) {
    UART_printf(uart, "%s=\"%s\",\"%s\"\r\n", AT_CWJAP, SSID, Password);

    delay(5);
    if (!ESP8266_waitForAnswer(uart)) {
        return false;
    }

    if (strstr((char *) uart->buffer, "OK") == NULL) {
        return false;
    }

    return true;
}

bool ESP8266_establishConnection(UART *uart, char id, uint8_t type, char *address, char *port) {
    char ct[3];

    switch (type) {
        case ESP8266_TCP:
            ct[0] = 'T';
            ct[1] = 'C';
            ct[2] = 'P';
            break;
        case ESP8266_UDP:
            ct[0] = 'U';
            ct[1] = 'D';
            ct[2] = 'P';
            break;
        default:
            return false;
    }

    UART_printf(uart, "%s=%c,\"%s\",\"%s\",%s\r\n", AT_CIPSTART, id, ct, address, port);

    delay(20);
    if (!ESP8266_waitForAnswer(uart)) {
        return false;
    }

    if (strstr((char *) uart->buffer, "OK") == NULL) {
        return false;
    }

    return true;
}

bool ESP8266_sendData(UART *uart, char id, char *data, uint32_t dataSize) {
    char size[5];

    sprintf(size, "%lu", dataSize);
    UART_printf(uart, "%s=%c,%s\r\n", AT_CIPSEND, id, size);

    delay(5);
    if (!ESP8266_waitForAnswer(uart)) {
        return false;
    }

    if (strstr((char *) uart->buffer, ">") == NULL) {
        return false;
    }

    UART_printf(uart, data);

    delay(5);
    if (!ESP8266_waitForAnswer(uart)) {
        return false;
    }

    if (strstr((char *) uart->buffer, "OK") == NULL) {
        return false;
    }

    return true;
}
