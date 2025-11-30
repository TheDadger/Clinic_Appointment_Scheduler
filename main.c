#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "myconio.h"

struct patient
{
    char name[50];
    int age;
    char gender[10];
    long long contact_number;
    char address[100];
    int username;
    char password[20];
};

struct doctor
{
    char name[50];
    int age;
    char specialty[50];
    long long contact_number;
    char qualifications[100];
    char institution[100];
    int experience;
    int username;
    char password[20];
};

void Main_Menu_Page();
void exit_program();
void patient_menu();
void doctor_menu();
void help_menu();

void patient_registration();
void patient_login();
void doctor_registration();
void doctor_login();
void patient_dashboard(int);
void doctor_dashboard(int);

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
char category[15][30] = {
    "General Physician",
    "Pediatrician",
    "Dermatologist",
    "Cardiologist",
    "Neurologist",
    "Psychiatrist",
    "Gynecologist",
    "Orthopedic Surgeon",
    "ENT Specialist",
    "Ophthalmologist",
    "Dentist",
    "Radiologist",
    "Anesthesiologist",
    "Urologist",
    "Endocrinologist"};

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
        patient_login();
        break;
    case '2':
        patient_registration();
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
        doctor_login();
        break;
    case '2':
        doctor_registration();
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

void patient_registration()
{
    clrscr();
    FILE *file;
    slow_print_string(border, 6);
    slow_print_string(blank_line, 6);
    slow_print_string("| Patient Register                                                             |\n", 6);
    slow_print_string(frame_line, 6);

    slow_print_string(back_msg, 6);
    slow_print_string(blank_line, 6);
    slow_print_string("| Name:                                                                        |\n", 6);
    slow_print_string("| Age:                                                                         |\n", 6);
    slow_print_string("| Gender(M/F/O):                                                               |\n", 6);
    slow_print_string(blank_line, 6);
    slow_print_string("| Contact Number(10 digits):                                                   |\n", 6);
    slow_print_string("| Address:                                                                     |\n", 6);
    slow_print_string(blank_line, 6);
    slow_print_string(frame_line, 6);
    slow_print_string(blank_line, 6);
    slow_print_string("| Username (Auto-generated) :                                                  |\n", 6);
    slow_print_string("| Password (Min. 4 characters) :                                               |\n", 6);
    slow_print_string("| Confirm Password:                                                            |\n", 6);
    slow_print_string(blank_line, 6);
    slow_print_string(border, 6);

    struct patient temp;

    do
    {
        gotoxy(8, 7);
        fgets(temp.name, sizeof(temp.name), stdin);
        temp.name[strcspn(temp.name, "\r\n")] = 0; // Remove newline character
        if (temp.name[0] == '*')
        {
            patient_menu();
        }
    } while (strlen(temp.name) == 0);

    do
    {
        gotoxy(7, 8);
        char age_str[5];
        slow_print_string("            ", 6); // Clear previous input
        gotoxy(7, 8);
        fgets(age_str, 5, stdin);
        if (temp.name[0] == '*')
        {
            patient_menu();
        }
        temp.age = atoi(age_str);
    } while (temp.age <= 0 || temp.age > 120);

    do
    {
        gotoxy(10, 9);
        slow_print_string("            ", 6); // Clear previous input
        gotoxy(10, 9);
        fgets(temp.gender, sizeof(temp.gender), stdin);
        if (temp.gender[0] == '*')
        {
            patient_menu();
        }
        temp.gender[strcspn(temp.gender, "\r\n")] = 0; // Remove newline character
        for (int i = 0; temp.gender[i] != '\0'; i++)
        {
            temp.gender[i] = tolower(temp.gender[i]);
        }
    } while (!(strcmp(temp.gender, "male") == 0 || strcmp(temp.gender, "female") == 0 || strcmp(temp.gender, "other") == 0 || strcmp(temp.gender, "m") == 0 || strcmp(temp.gender, "f") == 0 || strcmp(temp.gender, "o") == 0));

    do
    {
        gotoxy(18, 11);
        char contact_str[20];
        slow_print_string("                  ", 6); // Clear previous input
        gotoxy(18, 11);
        fgets(contact_str, 20, stdin);
        if (contact_str[0] == '*')
        {
            patient_menu();
        }
        temp.contact_number = atoll(contact_str);
    } while (!(temp.contact_number >= 9000000000 && temp.contact_number <= 9999999999));

    do
    {
        gotoxy(11, 12);
        fgets(temp.address, sizeof(temp.address), stdin);
        if (temp.address[0] == '*')
        {
            patient_menu();
        }
        temp.address[strcspn(temp.address, "\r\n")] = 0; // Remove newline character
    } while (strlen(temp.address) == 0);

    int last_username = 0;

    file = fopen("patient.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    while (fscanf(file, "%49[^|]|%d|%7[^|]|%lld|%100[^|]|%d|%20[^\n]", temp.name, &temp.age, temp.gender, &temp.contact_number, temp.address, &temp.username, temp.password) != EOF)
    {
        last_username = temp.username;
    }
    fclose(file);

    file = fopen("patient.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    temp.username = (((last_username / 10) + 1) * 10) + 9;
    gotoxy(30, 16);
    char username_str[20];
    sprintf(username_str, "%d", temp.username);
    slow_print_string(username_str, 6);

    char initial_password[30];
    do
    {
        gotoxy(33, 17);
        fgets(initial_password, sizeof(initial_password), stdin);
        if (initial_password[0] == '*')
        {
            fclose(file);
            patient_menu();
        }
        initial_password[strcspn(initial_password, "\r\n")] = 0; // Remove newline character
    } while (strlen(initial_password) < 4);

    do
    {
        gotoxy(20, 18);
        fgets(temp.password, sizeof(temp.password), stdin);
        if (temp.password[0] == '*')
        {
            fclose(file);
            patient_menu();
        }
        temp.password[strcspn(temp.password, "\r\n")] = 0; // Remove newline character
    } while (strlen(temp.password) < 4);

    if (strcmp(initial_password, temp.password) != 0)
    {
        gotoxy(8, 19);
        slow_print_string("Passwords do not match! Press any key to retry.", 6);
        getch();
        fclose(file);
        patient_registration();
    }

    fprintf(file, "%s|%d|%s|%lld|%s|%d|%s\n", temp.name, temp.age, temp.gender, temp.contact_number, temp.address, temp.username, temp.password);
    fclose(file);
    gotoxy(8, 19);
    slow_print_string("Registration successful! Press any key to continue.", 6);
    getch();
    patient_login();
}

void patient_login()
{
    clrscr();
    FILE *file;
    struct patient temp;
    slow_print_string(border, 6);
    slow_print_string(blank_line, 6);
    slow_print_string("| Patient Login                                                                |\n", 6);
    slow_print_string(frame_line, 6);

    slow_print_string(back_msg, 6);
    slow_print_string(blank_line, 6);
    slow_print_string("| Username:                                                                    |\n", 6);
    slow_print_string("| Password:                                                                    |\n", 6);
    slow_print_string(blank_line, 6);
    slow_print_string(border, 6);
    file = fopen("patient.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    gotoxy(12, 7);
    char username_input[20];
    fgets(username_input, 20, stdin);
    if (username_input[0] == '*')
    {
        fclose(file);
        patient_menu();
    }
    username_input[strcspn(username_input, "\r\n")] = 0; // Remove newline character
    int username_val = atoi(username_input);

    gotoxy(12, 8);
    char password_input[20];
    fgets(password_input, 20, stdin);
    if (password_input[0] == '*')
    {
        fclose(file);
        patient_menu();
    }
    password_input[strcspn(password_input, "\r\n")] = 0; //
    int user_found = 0;
    while ((fscanf(file, "%49[^|]|%d|%7[^|]|%lld|%100[^|]|%d|%20[^\n]", temp.name, &temp.age, temp.gender, &temp.contact_number, temp.address, &temp.username, temp.password)) != EOF)
    {
        if (temp.username == username_val && strcmp(temp.password, password_input) == 0)
        {
            gotoxy(8, 9);
            slow_print_string("Login successful! Press any key to continue.", 6);
            getch();
            patient_dashboard(temp.username);
            fclose(file);
            user_found = 1;
            break;
        }
    }
    if (user_found == 0)
    {
        gotoxy(8, 9);
        slow_print_string("Invalid username or password! Press any key to retry.", 6);
        getch();
        fclose(file);
        patient_login();
    }
}

void doctor_registration()
{
    clrscr();
    struct doctor temp, scan;
    slow_print_string(border, 6);
    slow_print_string(blank_line, 6);
    slow_print_string("| Doctor Register                                                              |\n", 6);
    slow_print_string(frame_line, 6);

    slow_print_string(back_msg, 6);
    slow_print_string(blank_line, 6);
    slow_print_string("| Name:                                                                        |\n", 6);
    slow_print_string("| Age:                                                                         |\n", 6);
    slow_print_string("| Contact Number:                                                              |\n", 6);
    slow_print_string(blank_line, 6);
    slow_print_string("| Qualifications:                                                              |\n", 6);
    slow_print_string("| Institution:                                                                 |\n", 6);
    slow_print_string("| Experience(In Years):                                                        |\n", 6);
    slow_print_string(blank_line, 6);
    slow_print_string(blank_line, 6);
    slow_print_string(border, 6);

    do
    {
        gotoxy(8, 7);
        fgets(temp.name, sizeof(temp.name), stdin);
        temp.name[strcspn(temp.name, "\r\n")] = 0; // Remove newline character
        if (temp.name[0] == '*')
        {
            doctor_menu();
        }
    } while (strlen(temp.name) == 0);
    gotoxy(8, 30);
    slow_print_string("\n", 6);
    slow_print_string(temp.name, 6);
    do
    {
        gotoxy(7, 8);
        char age_str[5];
        slow_print_string("            ", 6); // Clear previous input
        gotoxy(7, 8);
        fgets(age_str, 5, stdin);
        if (temp.name[0] == '*')
        {
            doctor_menu();
        }
        temp.age = atoi(age_str);
    } while (temp.age <= 0 || temp.age > 120);

    do
    {
        gotoxy(18, 9);
        char contact_str[20];
        slow_print_string("                  ", 6); // Clear previous input
        gotoxy(18, 9);
        fgets(contact_str, 20, stdin);
        if (contact_str[0] == '*')
        {
            doctor_menu();
        }
        temp.contact_number = atoll(contact_str);
    } while (!(temp.contact_number >= 9000000000 && temp.contact_number <= 9999999999));

    do
    {
        gotoxy(18, 11);
        slow_print_string("                     ", 6); // Clear previous input
        gotoxy(18, 11);
        fgets(temp.qualifications, sizeof(temp.qualifications), stdin);
        if (temp.qualifications[0] == '*')
        {
            doctor_menu();
        }
        temp.qualifications[strcspn(temp.qualifications, "\r\n")] = 0; // Remove newline character
        for (int i = 0; temp.qualifications[i] != '\0'; i++)
        {
            temp.qualifications[i] = toupper(temp.qualifications[i]);
        }
    } while (strlen(temp.qualifications) == 0 || (strcmp(temp.qualifications, "MBBS") != 0 && strcmp(temp.qualifications, "MD") != 0 && strcmp(temp.qualifications, "PHD") != 0));

    do
    {
        gotoxy(15, 12);
        fgets(temp.institution, sizeof(temp.institution), stdin);
        if (temp.institution[0] == '*')
        {
            doctor_menu();
        }
        temp.institution[strcspn(temp.institution, "\r\n")] = 0; // Remove newline character
    } while (strlen(temp.institution) == 0);

    do
    {
        gotoxy(24, 13);
        char exp_str[5];
        slow_print_string("            ", 6); // Clear previous input
        gotoxy(24, 13);
        fgets(exp_str, 5, stdin);
        if (exp_str[0] == '*')
        {
            doctor_menu();
        }
        temp.experience = atoi(exp_str);
    } while (temp.experience < 0 || temp.experience > 80);

    clrscr();
    slow_print_string(border, 6);
    slow_print_string(blank_line, 6);
    slow_print_string("| Doctor Register                                                              |\n", 6);
    slow_print_string(frame_line, 6);
    slow_print_string(blank_line, 6);
    slow_print_string("| Choose your specialty:                                                       |\n", 6);
    for (int i = 0; i < 15; i++)
    {
        char spec_line[80];
        char buffer[80];
        sprintf(buffer, "| %2d) %s", i + 1, category[i]);
        slow_print_string(buffer, 6);
        for (int j = 0; j < 79 - strlen(buffer); j++)
        {
            slow_print_string(" ", 6);
        }
        slow_print_string("|\n", 6);
    }
    slow_print_string(blank_line, 6);
    slow_print_string(frame_line, 6);
    slow_print_string(input_msg, 6);
    slow_print_string(border, 6);

    char opt[100];
    int opt_val;
    do
    {
        gotoxy(21, 24);
        slow_print_string("        ", 6); // Clear previous input
        gotoxy(21, 24);
        fgets(opt, 3, stdin);
        if (opt[0] == '*')
        {
            doctor_menu();
        }
        opt[strcspn(opt, "\r\n")] = 0; // Remove newline character
        opt_val = atoi(opt);
    } while (opt_val < 1 || opt_val > 15);
    strcpy(temp.specialty, category[opt_val - 1]);

    clrscr();
    slow_print_string(border, 6);
    slow_print_string(blank_line, 6);
    slow_print_string("| Doctor Register                                                              |\n", 6);
    slow_print_string(frame_line, 6);
    slow_print_string(blank_line, 6);
    slow_print_string("| Username (Auto-generated) :                                                  |\n", 6);
    slow_print_string("| Password (Min. 4 characters) :                                               |\n", 6);
    slow_print_string("| Confirm Password:                                                            |\n", 6);
    slow_print_string(blank_line, 6);
    slow_print_string(border, 6);

    FILE *file;
    int last_username = 0;
    file = fopen("doctor.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    while (fscanf(file, "%[^|]|%d|%[^|]|%lld|%[^|]|%[^|]|%d|%d|%[^\n]", scan.name, &scan.age, scan.specialty, &scan.contact_number, scan.qualifications, scan.institution, &scan.experience, &scan.username, scan.password) != EOF)
    {
        last_username = scan.username;
    }
    fclose(file);

    file = fopen("doctor.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    temp.username = (((last_username / 10) + 1) * 10) + 2;
    gotoxy(30, 6);
    char username_str[20];
    sprintf(username_str, "%d", temp.username);
    slow_print_string(username_str, 6);

    char initial_password[30];
    do
    {
        gotoxy(33, 7);
        fgets(initial_password, sizeof(initial_password), stdin);
        if (initial_password[0] == '*')
        {
            fclose(file);
            doctor_menu();
        }
        initial_password[strcspn(initial_password, "\r\n")] = 0; // Remove newline character
    } while (strlen(initial_password) < 4);
    do
    {
        gotoxy(20, 8);
        fgets(temp.password, sizeof(temp.password), stdin);
        if (temp.password[0] == '*')
        {
            fclose(file);
            doctor_menu();
        }
        temp.password[strcspn(temp.password, "\r\n")] = 0; // Remove newline character
    } while (strlen(temp.password) < 4);
    if (strcmp(initial_password, temp.password) != 0)
    {
        gotoxy(8, 9);
        slow_print_string("Passwords do not match! Press any key to retry.", 6);
        getch();
        fclose(file);
        doctor_registration();
    }
    fprintf(file, "%s|%d|%s|%lld|%s|%s|%d|%d|%s\n", temp.name, temp.age, temp.specialty, temp.contact_number, temp.qualifications, temp.institution, temp.experience, temp.username, temp.password);
    fclose(file);
    gotoxy(8, 9);
    slow_print_string("Registration successful! Press any key to continue.", 6);
    getch();
    doctor_login();
}

void doctor_login()
{
    clrscr();
    slow_print_string(border, 6);
    slow_print_string(blank_line, 6);
    slow_print_string("| Doctor Login                                                                 |\n", 6);
    slow_print_string(frame_line, 6);

    slow_print_string(back_msg, 6);
    slow_print_string(blank_line, 6);
    slow_print_string("| Username:                                                                    |\n", 6);
    slow_print_string("| Password:                                                                    |\n", 6);
    slow_print_string(blank_line, 6);
    slow_print_string(frame_line, 6);

    FILE *file;
    struct doctor temp;
    file = fopen("doctor.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    gotoxy(12, 7);
    char username_input[20];
    fgets(username_input, 20, stdin);
    if (username_input[0] == '*')
    {
        fclose(file);
        doctor_menu();
        return;
    }
    username_input[strcspn(username_input, "\r\n")] = 0; // Remove newline character
    int username_val = atoi(username_input);
    gotoxy(12, 8);
    char password_input[20];
    fgets(password_input, 20, stdin);
    if (password_input[0] == '*')
    {
        fclose(file);
        doctor_menu();
        return;
    }
    password_input[strcspn(password_input, "\r\n")] = 0; //
    int user_found = 0;
    while ((fscanf(file, "%[^|]|%d|%[^|]|%lld|%[^|]|%[^|]|%d|%d|%[^\n]", temp.name, &temp.age, temp.specialty, &temp.contact_number, temp.qualifications, temp.institution, &temp.experience, &temp.username, temp.password)) != EOF)
    {
        if (temp.username == username_val && strcmp(temp.password, password_input) == 0)
        {
            gotoxy(8, 9);
            slow_print_string("Login successful! Press any key to continue.", 6);
            getch();
            doctor_dashboard(temp.username);
            fclose(file);
            user_found = 1;
            break;
        }
    }
    if (user_found == 0)
    {
        gotoxy(8, 9);
        slow_print_string("Invalid username or password! Press any key to retry.", 6);
        getch();
        fclose(file);
        doctor_login();
    }
}

void patient_dashboard(int username)
{
    clrscr();
    slow_print_string(border, 6);
    slow_print_string(blank_line, 6);
    slow_print_string("| Patient Dashboard                                                            |\n", 6);
    slow_print_string(frame_line, 6);

    slow_print_string(back_msg, 6);
    slow_print_string(blank_line, 6);
    slow_print_string("| Welcome to your dashboard!                                                   |\n", 6);
    slow_print_string(blank_line, 6);
    slow_print_string(frame_line, 6);
}

void doctor_dashboard(int username)
{
    clrscr();
    slow_print_string(border, 6);
    slow_print_string(blank_line, 6);
    slow_print_string("| Doctor Dashboard                                                             |\n", 6);
    slow_print_string(frame_line, 6);

    slow_print_string(back_msg, 6);
    slow_print_string(blank_line, 6);
    slow_print_string("| Welcome to your dashboard!                                                   |\n", 6);
    slow_print_string(blank_line, 6);
    slow_print_string(frame_line, 6);
}
