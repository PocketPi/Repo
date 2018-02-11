#ifndef __USART_H__
#define __USART_H__

#include <sys/types.h>
#include "stm32f4xx_conf.h"

/* Initialize the USART6. */
void setup_usart(void);
/* USART read 1 byte. */
#define USART_ReadByte(USARTx)      (USART_ReceiveData(USARTx))
/* USART send 1 byte. */
#define USART_SendByte(USARTx, b)   (USART_SendData(USARTx, b))
/* Send bytes array with designated length through USART. */
ssize_t USART_Send(USART_TypeDef *, void *, ssize_t);
/* Print the string through USART with blocking. */
void USART_Printf(USART_TypeDef* USARTx, char *str);

void my_printf(const char *fmt, ...); // custom printf() function


#endif
