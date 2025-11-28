#include <stdio.h>
#include "myconio.h"

int main()
{
    clrscr();
    gotoxy(10, 5);
    printf("Press any key to continue...\n");

    while (!kbhit())
    {
        // waiting for key press
    }

    int ch = getch();
    gotoxy(10, 7);
    printf("You pressed: %c\n", ch);

    return 0;
}