#include <stdio.h>
#include "myconio.h"

void Main_Menu_Page();
void exit_program();

int main()
{
    Main_Menu_Page();
    getch();
    return 0;
}

void Main_Menu_Page()
{
    clrscr();
    printf("+");
    for (int i = 0; i < 78; i++)
    {
        printf("-");
    }
    printf("+\n");
    printf("|                                                                              |\n");
    printf("|                         Clinic Appointment Scheduler                         |\n");
    printf("|******************************************************************************|\n");
    printf("|                                                                              |\n");
    printf("|  Are you a:                                                                  |\n");
    printf("|    1. Patient                                                                |\n");
    printf("|    2. Doctor                                                                 |\n");
    printf("|    3. Help                                                                   |\n");
    printf("|    4. Exit                                                                   |\n");
    printf("|                                                                              |\n");
    printf("|******************************************************************************|\n");
    printf("|  Select an option:                                                           |\n");
    printf("+");
    for (int i = 0; i < 78; i++)
    {
        printf("-");
    }
    printf("+\n");
    char option;
    do
    {
        gotoxy(21, 13);
        option = getch();
    } while (!(option == '1' || option == '2' || option == '3' || option == '4'));
    gotoxy(21, 13);
    putchar(option);
    switch (option)
    {
    case '1':
        // Patient Menu Function Call
        break;
    case '2':
        // Doctor Menu Function Call
        break;
    case '3':
        // Help Menu Function Call
        break;
    case '4':
        exit_program();
        break;
    }
}

void exit_program()
{
    clrscr();
    printf("Exiting the program. Goodbye!\n");
    exit(0);
}