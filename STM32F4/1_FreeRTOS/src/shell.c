#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "usart.h"
#include "shell.h"

#define LINE_BUFSIZE 1024

static char get_char()
{
    char c[] = "\0";

    do {
        if (USART6->SR & USART_SR_RXNE) {
            c[0] = USART_ReadByte(USART6);
        }
    } while (c[0] == '\0');

    USART_SendByte(USART6, c[0]);
    return c[0];
}

int read_line(char * buffer)
{
    int position = 0;
    char c;

    while (1) {
        // Read a character
        c = get_char();

        if (c == '\r') {
            buffer[position++] = '\n';
            buffer[position++] = '\r';
            buffer[position] = '\0';
            return 0;
        } else {
            buffer[position] = c;
        }
        position++;
    }
}


void shell_task()
{
    int status = 0;
    char line[LINE_BUFSIZE];

    memset(line, '\0', LINE_BUFSIZE);

    do {
        my_printf("> ");
        read_line(line);
        my_printf("got: %s", line);
    }while (status == 0);
}
