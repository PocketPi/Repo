#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "usart.h"
#include "shell.h"

#define LINE_BUFSIZE    1024
#define MAX_ARGC        16

char prompt[10] = "> ";


static int valid_char(char input_char) {
    if (
        ((input_char > 31) &&    // Space to
        (input_char < 128)) ||   // ~
        (input_char == 13)      // Carriage return
        ) {
        return 1;
    }
    return 0;
}

static char get_char() {
    char c[] = "\0";

    do {
        if (USART6->SR & USART_SR_RXNE) {
            c[0] = USART_ReadByte(USART6);
        }
    } while (c[0] == '\0');

    if (valid_char(c[0])) {
        USART_SendByte(USART6, c[0]);
        return c[0];
    }
    return 0;
}

static int read_line(char * buffer, size_t buffer_size) {
    size_t position = 0;
    char c;

    while (1) {
        // Read a character
        c = get_char();
        buffer[position] = c;

        if (c == '\r') {
            buffer[++position] = '\n';
            buffer[++position] = '\0';
            my_printf("\n");
            return 0;
        }
        position++;
        if (position == buffer_size) {
            return -1;
        }
    }
}

static int parse_line(char * buffer, size_t buffer_size) {
    (void)buffer_size;
    size_t argc = 0;
    char *argv[MAX_ARGC];

    char *token = strtok(buffer, " ");

    while((token != NULL) && (argc < MAX_ARGC)) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }
    argv[argc] = '\0';

    return 0;
}

void set_prompt(char * buffer) {
    memcpy(prompt, buffer, sizeof(prompt));
}

static void show_prompt() {
    my_printf("%s", prompt);
}

void shell_task() {
    int status = 0;
    char line[LINE_BUFSIZE];

    memset(line, '\0', LINE_BUFSIZE);

    do {
        show_prompt();
        status = read_line(line, sizeof(line));
        parse_line(line, sizeof(line));
    }while (status == 0);
}
