/* echo_input.h – for C submissions, compile with -include echo_input.h */
#pragma once
#include <stdio.h>

/* Echo input from stdin as it is read */
static inline int echo_getchar(void) {
    int c = getchar();
    if (c != EOF) {
        putchar(c);
        fflush(stdout);
    }
    return c;
}

/* Override standard getchar() */
#define getchar() echo_getchar()
