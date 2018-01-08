
#ifndef __SOFT_UART_H
#define __SOFT_UART_H

#define Baudrate              1200                      //bps
#define OneBitDelay           (1000000 / Baudrate)
#define DataBitCount          8                         // no parity, no flow control

//Function Declarations
void InitSoftUART(void);
unsigned char UART_Receive(void);
void UART_Transmit(const char);


#endif