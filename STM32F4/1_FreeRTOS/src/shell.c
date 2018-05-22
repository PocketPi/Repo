#include <ctype.h>
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

static void parse_line(char * command_line, size_t *argcp, char ***argvp) {

    char *rest = command_line;
    size_t argc = 0;
    char *argv[MAX_ARGC];

    char *token;

    while(((token = strtok_r(rest, " ", &rest)) != NULL) && (argc < MAX_ARGC)) {
        argv[argc] = token;
        argc++;
    }
    //argv[argc] = '\0';

    *argcp = argc;
    *argvp = argv;
}

void set_prompt(char * buffer) {
    memcpy(prompt, buffer, sizeof(prompt));
}

static void show_prompt() {
    my_printf("%s", prompt);
}

int getopt_example(int argc, char **argv) {

    for(int i=0;i<argc;i++)
        my_printf("argv[%d]: %s\r\n", i, argv[i]);

    while (1) {
        char c;

        c = getopt (argc, argv, "ab:");
        if (c == -1) {
            /* We have finished processing all the arguments. */
            break;
        }
        switch (c) {
        case 'a':
            printf ("User has invoked with -a.\n");
            break;
        case 'b':
            printf ("User has invoked with -b %s.\n", optarg);
            break;
        case '?':
        default:
            printf ("Usage: %s [-a] [-b <something>].\n", argv[0]);
        }
    }

    /* Other code omitted */
    return 0;
}

void shell_task() {
    int status = 0;
    char command_line[LINE_BUFSIZE];
    size_t argc;
    char **argv;

    memset(command_line, '\0', LINE_BUFSIZE);

    do {
        show_prompt();
        status = read_line(command_line, sizeof(command_line));
        parse_line(command_line, &argc, &argv);
        for (size_t i=0; i<argc; i++)
            my_printf("argc: %d, argv[%d]: %s\r\n", argc, i, argv[i]);
        getopt_example(argc, argv);
    } while (status == 0);
}
