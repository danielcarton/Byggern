#ifndef UART_CONTROL_H_
#define UART_CONTROL_H_

void uart_start(unsigned int ubrr);

void uart_transmit(unsigned char ch);

void uart_receive(void);

#endif