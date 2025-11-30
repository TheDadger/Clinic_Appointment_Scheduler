#include <stdio.h>
#include "myconio.h"

void slow_print_string(char *str, int d)
{
    while (*str)
    {
        putchar(*str++);
        fflush(stdout);
        delay(d);
    }
}

int main()
{
    char opt[100];
    do
    {
        slow_print_string("        ", 6); // Clear previous input
        fgets(&opt, 3, stdin);
    } while (*opt < '1' || *opt > '15');

    return 0;
}