#ifndef UART_CONTROL_H_
#define UART_CONTROL_H_

void uart_start(unsigned int ubrr);

int uart_transmit(unsigned char ch);

int uart_recieve(void);


#endif /* UART_CONTROL_H_ */