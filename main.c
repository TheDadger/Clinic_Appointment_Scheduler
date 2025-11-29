#include <stdio.h>
#include <stdlib.h>
#include "myconio.h"

void Main_Menu_Page();
void exit_program();
void patient_menu();
void doctor_menu();
void help_menu();

void slow_print_string(char *str, int d)
{
    while (*str)
    {
        putchar(*str++);
        fflush(stdout);
        delay(d);
    }
}

char border[] = "+------------------------------------------------------------------------------+\n";
char blank_line[] = "|                                                                              |\n";
char frame_line[] = "|******************************************************************************|\n";
char input_msg[] = "|  Select an option:                                                           |\n";
char back_msg[] = "|                                                           (Click * for back) |\n";
char home_msg[] = "|                                                           (Click # for home) |";

int main()
{
    Main_Menu_Page();
    return 0;
}

void Main_Menu_Page()
{
    clrscr();
    char opt;
    slow_print_string(border, 6);
    char title[] = "|                         Clinic Appointment Scheduler                         |\n";
    slow_print_string(title, 5);

    slow_print_string(blank_line, 6);
    slow_print_string(frame_line, 6);

    slow_print_string(blank_line, 6);

    char body[] = "|  Are you a:                                                                  |\n\
|    1. Patient                                                                |\n\
|    2. Doctor                                                                 |\n";
    slow_print_string(body, 6);

    slow_print_string(blank_line, 6);
    slow_print_string("|  3. Help                                                                     |\n", 6);
    slow_print_string("|  4. Exit                                                                     |\n", 6);
    slow_print_string(blank_line, 6);
    slow_print_string(frame_line, 6);
    slow_print_string(input_msg, 6);
    slow_print_string(border, 6);

    do
    {
        gotoxy(21, 14);
        opt = getch();
    } while (!(opt == '1' || opt == '2' || opt == '3' || opt == '4'));
    gotoxy(21, 14);
    putchar(opt);
    switch (opt)
    {
    case '1':
        patient_menu();
        break;
    case '2':
        doctor_menu();
        break;
    case '3':
        help_menu();
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

void patient_menu()
{
    clrscr();
    char opt;
    slow_print_string(border, 6);
    slow_print_string(blank_line, 6);
    slow_print_string("| Patient                                                                      |\n", 6);
    slow_print_string(frame_line, 6);

    slow_print_string(back_msg, 6);
    slow_print_string(blank_line, 6);
    slow_print_string("| 1) Login                                                                     |\n", 6);
    slow_print_string("| 2) Register                                                                  |\n", 6);
    slow_print_string(blank_line, 6);
    slow_print_string(frame_line, 6);
    slow_print_string(input_msg, 6);
    slow_print_string(border, 6);

    do
    {
        gotoxy(21, 11);
        opt = getch();
    } while (!(opt == '1' || opt == '2' || opt == '*'));

    switch (opt)
    {
    case '1':
        // Placeholder for patient login functionality
        break;
    case '2':
        // Placeholder for patient registration functionality
        break;
    case '*':
        Main_Menu_Page();
        break;
    }
}

void doctor_menu()
{
    clrscr();
    char opt;
    slow_print_string(border, 6);
    slow_print_string(blank_line, 6);
    slow_print_string("| Doctor                                                                       |\n", 6);
    slow_print_string(frame_line, 6);

    slow_print_string(back_msg, 6);
    slow_print_string(blank_line, 6);
    slow_print_string("| 1) Login                                                                     |\n", 6);
    slow_print_string("| 2) Register                                                                  |\n", 6);
    slow_print_string(blank_line, 6);
    slow_print_string(frame_line, 6);
    slow_print_string(input_msg, 6);
    slow_print_string(border, 6);

    do
    {
        gotoxy(21, 11);
        opt = getch();
    } while (!(opt == '1' || opt == '2' || opt == '*'));

    switch (opt)
    {
    case '1':
        // Placeholder for doctor login functionality
        break;
    case '2':
        // Placeholder for doctor registration functionality
        break;
    case '*':
        Main_Menu_Page();
        break;
    }
}

void help_menu()
{
    clrscr();
    char opt;

    slow_print_string(border, 6);
    slow_print_string(blank_line, 6);
    slow_print_string("| Help                                                                         |\n", 6);
    slow_print_string(frame_line, 6);
    slow_print_string(back_msg, 6);
    slow_print_string(blank_line, 6);
    slow_print_string("|                       This page is Under Construction!                       |\n", 6);
    slow_print_string(blank_line, 6);
    slow_print_string(border, 6);

    do
    {
        gotoxy(60, 5);
        opt = getch();
    } while (!(opt == '*'));
    Main_Menu_Page();
}
