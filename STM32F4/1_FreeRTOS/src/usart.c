#include <ctype.h>
#include <string.h>
#include "usart.h"



#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void vprint(const char *fmt, va_list argp)
{
    char string[200];
    if(0 < vsprintf(string,fmt,argp)) // build string
    {
        USART_Printf(USART6, string); // send message via UART
    }
}

void my_printf(const char *fmt, ...) // custom printf() function
{
    va_list argp;
    va_start(argp, fmt);
    vprint(fmt, argp);
    va_end(argp);
}

/* Initialize the USART6. */
void setup_usart(void) {
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Enable the GPIOA peripheral clock. */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    /* Make PC6, PC7 as alternative function of USART6. */
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);

    /* Initialize PC6, PC7.  */
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* Enable the USART6 peripheral clock. */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

    /* Initialize USART6 with
     * 115200 buad rate,
     * 8 data bits,
     * 1 stop bit,
     * no parity check,
     * none flow control.
     */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART6, &USART_InitStructure);

    /* Enable USART6. */
    USART_Cmd(USART6, ENABLE);

    /* Enable USART6 RX interrupt. */
    //USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);
    /* Enable USART6 in NVIC vector. */
    //NVIC_EnableIRQ(USART6_IRQn);
}

/* Send bytes array with designated length through USART. */
ssize_t USART_Send(USART_TypeDef *USARTx, void *buf, ssize_t l) {
    ssize_t i = 0;
    uint8_t *pBuf;

    pBuf = buf;

    /* Send with blocking mode. */
    for(i=0; i<l; i++) {
        while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
        USART_SendByte(USARTx, (uint16_t)(pBuf[i]));
    }
    return i;
}

/* Print the string through USART with blocking. */
void USART_Printf(USART_TypeDef* USARTx, char *str) {
    USART_Send(USARTx, str, strlen(str));
}

/* USART6 IRQ handler. */
void USART6_IRQHandler(void) {
    char c[] = "\0";

    /* USART6 RX interrupt. */
    if(USART6->SR & USART_SR_RXNE) {
        c[0] = USART_ReadByte(USART6);
        if (c[0] == '\r')
        {
            c[1] = '\n';
        }

        USART_Printf(USART6, c);
    }
}
