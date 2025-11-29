#include <stdio.h>
#include <stdlib.h>
#include "lsh.h"

/* lsh_read_line: a simple dynamic reader. Uses getline if available. */
char *lsh_read_line(void)
{
#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200809L
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t nread;

    nread = getline(&line, &bufsize, stdin);
    if (nread == -1) {
        if (feof(stdin)) {
            /* Ctrl-D or EOF: exit cleanly */
            exit(EXIT_SUCCESS);
        } else {
            perror("lsh: getline");
            exit(EXIT_FAILURE);
        }
    }

    return line;
#else
    int bufsize = LSH_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        c = getchar();

        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = (char)c;
        }
        position++;

        if (position >= bufsize) {
            bufsize += LSH_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
#endif
}
