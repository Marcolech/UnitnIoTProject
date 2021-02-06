#ifndef MARCOLECH_UART_CONTROLLER_H_
#define MARCOLECH_UART_CONTROLLER_H_

#include <stdio.h>
#include <rom.h>
#include <rom_map.h>
#include <interrupt.h>
#include <uart.h>
#include <gpio.h>

#define UART_BUFFER_SIZE 2048

typedef struct UART {
    uint32_t uart;
    eUSCI_UART_Config uartConfig;
    volatile uint8_t buffer[UART_BUFFER_SIZE];
    volatile uint32_t readIndex;
    volatile uint32_t writeIndex;
} UART;

void UART_init(UART *uart);

void UART_write(UART *uart, uint8_t *data, uint32_t size);

uint32_t UART_read(UART *uart, uint8_t *data, uint32_t size);

void UART_printChar(UART *uart, char c);

void UART_printString(UART *uart, char *string);

void UART_printInteger(UART *uart, int integer);

void UART_printf(UART *uart, const char *fs, ...);

int UART_gets(UART *uart, char *b, int size);

uint32_t UART_available(UART *uart);

void UART_flush(UART *uart);

#endif /* MARCOLECH_UART_CONTROLLER_H_ */
