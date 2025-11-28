#include <stdio.h>
#include "myconio.h"

void Main_Menu_function();

void main()
{
    Main_Menu_function();
    getch();
}

void Main_Menu_function()
{
    clrscr();
    for (int i = 0; i < 50; i++)
    {
        printf("-");
    }
}