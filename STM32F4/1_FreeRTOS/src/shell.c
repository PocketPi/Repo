#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "usart.h"
#include "shell.h"

#define LINE_BUFSIZE    1024
#define MAX_ARGC        16
#define MAX_CMDS        16
#define MAX_CMDNAME_LEN 32

typedef int (*cb_t) (int argc, char ** argv);

typedef struct {
  char name[MAX_CMDNAME_LEN];
  cb_t cb;
} cmd_t;

static cmd_t cmds[MAX_CMDS];

char prompt[10] = "> ";


int getopt_example(int argc, char **argv) {

    /* Reset optind to enable calling the getopt multiple times */
    optind = 1;
    while (1) {
        int c;

        c = getopt(argc, argv, "ab:");
        if (c == -1) {
            break;
        }
        switch (c) {
        case 'a':
            my_printf ("User has invoked with -a.\r\n");
            break;
        case 'b':
            my_printf ("User has invoked with -b %s.\r\n", optarg);
            break;
        case '?':
        default:
            my_printf ("Usage: %s [-a] [-b <something>].\r\n", argv[0]);
            break;
        }
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

    if (isascii(c[0])) {
        USART_SendByte(USART6, c[0]);
        return c[0];
    }
    return 0;
}

static int read_line(char * buffer, size_t buffer_size) {
    size_t position = 0;
    char c = '\0';

    while (1) {
        // Read a character
        c = get_char();
        buffer[position] = c;

        if ((c == '\r') || (c == '\n')) {
            buffer[position] = '\0';
            my_printf("\n");
            return 0;
        }
        position++;
        if (position == buffer_size) {
            return -1;
        }
    }
}

size_t parse_line(
        char           *buffer,     ///< In/Out : Modifiable String Buffer To Tokenise
        size_t         *argc,       ///< Out    : Argument Count
        char           *argv[],     ///< Out    : Argument String Vector Array
        const size_t    argv_length ///< In     : Maximum Count For `*argv[]`
    )
{ /* Tokenise string buffer into argc and argv format (req: string.h) */
    size_t i = 0;
    for (i = 0 ; i < argv_length ; i++)
    { /* Fill argv via strtok_r() */
        if ( NULL == (argv[i] = strtok_r( NULL, " ", &buffer)) ) break;
    }
    *argc = i;
    return i; // Argument Count
}

void set_prompt(char * buffer) {
    memcpy(prompt, buffer, sizeof(prompt));
}

static void show_prompt() {
    my_printf("%s", prompt);
}

void exec_cmd(int argc, char **argv) {
    for(int ii = 0; ii<MAX_CMDS; ii++) {
        if(strncmp(argv[0], cmds[ii].name, MAX_CMDNAME_LEN) == 0) {
            cmds[ii].cb(argc, argv);
        }
    }
}

int add_cmd(char * name, cb_t cb) {
    if (name != NULL) {
        strncpy(cmds[0].name, name, MAX_CMDNAME_LEN);
    } else {
        return -1;
    }
    if (cb != NULL) {
        cmds[0].cb = cb;
    } else {
        return -2;
    }
    return 0;
}

void shell_task() {

    add_cmd("getopt", getopt_example);

    int status = 0;
    char command_line[LINE_BUFSIZE];
    size_t argc;
    char *argv[MAX_ARGC];

    memset(command_line, '\0', LINE_BUFSIZE);

    do {
        show_prompt();
        status = read_line(command_line, sizeof(command_line));
        parse_line(command_line, &argc, argv, MAX_ARGC);
        exec_cmd(argc, argv);
    } while (status == 0);
}
