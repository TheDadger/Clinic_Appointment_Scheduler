#ifndef MYCONIO_H
#define MYCONIO_H

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

// --------------------------
// Clear screen
// --------------------------
#define clrscr() printf("\033[2J\033[H")

// --------------------------
// Move cursor to (x,y)
// x = column, y = row
// --------------------------
#define gotoxy(x, y) printf("\033[%d;%dH", (y), (x))

// --------------------------
// getch() - read single char without Enter
// --------------------------
int getch(void)
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt); // get current terminal settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);        // disable buffered input & echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // apply new settings
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore old settings
    return ch;
}

// --------------------------
// getche() - like getch but echoes key
// --------------------------
int getche(void)
{
    int ch = getch();
    putchar(ch);
    return ch;
}

// --------------------------
// kbhit() - check if a key has been pressed
// --------------------------
int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // disable buffered input & echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);          // get file status flags
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK); // set non-blocking

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore terminal
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

// --------------------------
// delay() - simple millisecond delay
// --------------------------
#include <time.h>
void delay(int milliseconds)
{
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds * (CLOCKS_PER_SEC / 1000))
        ;
}

#endif
