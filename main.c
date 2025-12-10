#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
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
    char name[30];
    int age;
    char specialty[20];
    long long contact_number;
    char qualifications[5];
    char institution[30];
    int experience;
    int username;
    char password[20];
};

struct availability
{
    int username;
    char day[15];
    int time_slot;
    int token;
};

struct appointment
{
    int doctor_username;
    int patient_username;
    char date[20]; // "2025-01-30"
    int time_slot;
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
void doctor_bio();
void doctor_appointments(int);
void doctor_availability(int);
void patient_info(char *, int, char *, long long, char *, int, char *);
void patient_booking(int);
void patient_history(int);
void decrease_token(int doctor_username, char *day, int time_slot);
void change_token_delta(int doctor_username, const char *day, int time_slot, int delta);
int add_appointment_record(int doctor_username, int patient_username, const char *date, int time_slot);
int delete_appointment_record(int doctor_username, int patient_username, const char *date, int time_slot);

void slow_print_string(char *str)
{
    while (*str)
    {
        putchar(*str++);
        fflush(stdout);
        delay(4);
    }
}

int compare_date(char *date)
{
    int y, m, d;
    sscanf(date, "%d-%d-%d", &y, &m, &d);

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    if (y == (t->tm_year + 1900) &&
        m == (t->tm_mon + 1) &&
        d == t->tm_mday)
        return 0; // today

    if (y > (t->tm_year + 1900))
        return 1;
    if (y < (t->tm_year + 1900))
        return -1;

    if (m > (t->tm_mon + 1))
        return 1;
    if (m < (t->tm_mon + 1))
        return -1;

    if (d > t->tm_mday)
        return 1;
    if (d < t->tm_mday)
        return -1;

    return 0;
}

char border[] = "+------------------------------------------------------------------------------+\n";
char blank_line[] = "|                                                                              |\n";
char frame_line[] = "|******************************************************************************|\n";
char input_msg[] = "|  Select an option:                                                           |\n";
char back_msg[] = "|                                                           (Click * for back) |\n";
char home_msg[] = "|                                                           (Click # for home) |\n";
char category[15][20] = {"General Physician", "Pediatrician", "Dermatologist", "Cardiologist", "Neurologist", "Psychiatrist", "Gynecologist", "Orthopedic Surgeon", "ENT Specialist", "Ophthalmologist", "Dentist", "Radiologist", "Anesthesiologist", "Urologist", "Endocrinologist"};
char week_day[8][10] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "All"};

int main()
{
    Main_Menu_Page();
    return 0;
}

void Main_Menu_Page()
{
    clrscr();
    char opt;
    slow_print_string(border);
    char title[] = "|                         Clinic Appointment Scheduler                         |\n";
    slow_print_string(title);

    slow_print_string(blank_line);
    slow_print_string(frame_line);

    slow_print_string(blank_line);

    char body[] = "|  Are you a:                                                                  |\n\
|    1. Patient                                                                |\n\
|    2. Doctor                                                                 |\n";
    slow_print_string(body);

    slow_print_string(blank_line);
    slow_print_string("|  3. Help                                                                     |\n");
    slow_print_string("|  4. Exit                                                                     |\n");
    slow_print_string(blank_line);
    slow_print_string(frame_line);
    slow_print_string(input_msg);
    slow_print_string(border);

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
    slow_print_string(border);
    slow_print_string(blank_line);
    slow_print_string("| Patient                                                                      |\n");
    slow_print_string(frame_line);

    slow_print_string(back_msg);
    slow_print_string(blank_line);
    slow_print_string("| 1) Login                                                                     |\n");
    slow_print_string("| 2) Register                                                                  |\n");
    slow_print_string(blank_line);
    slow_print_string(frame_line);
    slow_print_string(input_msg);
    slow_print_string(border);

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
    slow_print_string(border);
    slow_print_string(blank_line);
    slow_print_string("| Doctor                                                                       |\n");
    slow_print_string(frame_line);

    slow_print_string(back_msg);
    slow_print_string(blank_line);
    slow_print_string("| 1) Login                                                                     |\n");
    slow_print_string("| 2) Register                                                                  |\n");
    slow_print_string(blank_line);
    slow_print_string(frame_line);
    slow_print_string(input_msg);
    slow_print_string(border);

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

    slow_print_string(border);
    slow_print_string(blank_line);
    slow_print_string("| Help                                                                         |\n");
    slow_print_string(frame_line);
    slow_print_string(back_msg);
    slow_print_string(blank_line);
    slow_print_string("|                       This page is Under Construction!                       |\n");
    slow_print_string(blank_line);
    slow_print_string(border);

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
    slow_print_string(border);
    slow_print_string(blank_line);
    slow_print_string("| Patient Register                                                             |\n");
    slow_print_string(frame_line);

    slow_print_string(back_msg);
    slow_print_string(blank_line);
    slow_print_string("| Name:                                                                        |\n");
    slow_print_string("| Age:                                                                         |\n");
    slow_print_string("| Gender (Male/Female/Other):                                                 |\n");
    slow_print_string(blank_line);
    slow_print_string("| Contact Number (10 digits):                                                 |\n");
    slow_print_string("| Address:                                                                     |\n");
    slow_print_string(blank_line);
    slow_print_string(frame_line);
    slow_print_string(blank_line);
    slow_print_string("| Username (Auto-generated) :                                                  |\n");
    slow_print_string("| Password (Min. 4 characters) :                                               |\n");
    slow_print_string("| Confirm Password:                                                            |\n");
    slow_print_string(blank_line);
    slow_print_string(border);

    struct patient temp;
    memset(&temp, 0, sizeof(temp));

    // --- Name ---
    do
    {
        gotoxy(8, 7);
        fgets(temp.name, sizeof(temp.name), stdin);
        temp.name[strcspn(temp.name, "\r\n")] = 0; // Remove newline
        if (temp.name[0] == '*')
        {
            patient_menu();
            return;
        }
    } while (strlen(temp.name) == 0);

    // --- Age ---
    do
    {
        gotoxy(7, 8);
        slow_print_string("    "); // clear old input
        gotoxy(7, 8);
        char age_str[5];
        fgets(age_str, sizeof(age_str), stdin);
        if (age_str[0] == '*')
        {
            patient_menu();
            return;
        }
        temp.age = atoi(age_str);
    } while (temp.age <= 0 || temp.age > 120);

    // --- Gender ---
    do
    {
        gotoxy(25, 9);
        slow_print_string("       "); // clear old input
        gotoxy(25, 9);
        fgets(temp.gender, sizeof(temp.gender), stdin);
        if (temp.gender[0] == '*')
        {
            patient_menu();
            return;
        }
        temp.gender[strcspn(temp.gender, "\r\n")] = 0;
        for (int i = 0; temp.gender[i]; i++)
            temp.gender[i] = tolower(temp.gender[i]);
    } while (!(strcmp(temp.gender, "male") == 0 || strcmp(temp.gender, "female") == 0 || strcmp(temp.gender, "other") == 0 || strcmp(temp.gender, "m") == 0 || strcmp(temp.gender, "f") == 0 || strcmp(temp.gender, "o") == 0));

    // --- Contact Number ---
    do
    {
        gotoxy(28, 11);
        slow_print_string("            "); // clear old input
        gotoxy(28, 11);
        char contact_str[20];
        fgets(contact_str, sizeof(contact_str), stdin);
        if (contact_str[0] == '*')
        {
            patient_menu();
            return;
        }
        temp.contact_number = atoll(contact_str);
    } while (!(temp.contact_number >= 9000000000 && temp.contact_number <= 9999999999));

    // --- Address ---
    do
    {
        gotoxy(11, 12);
        fgets(temp.address, sizeof(temp.address), stdin);
        if (temp.address[0] == '*')
        {
            patient_menu();
            return;
        }
        temp.address[strcspn(temp.address, "\r\n")] = 0;
    } while (strlen(temp.address) == 0);

    // --- Compute new username ---
    int last_username = 9; // default if no file
    struct patient last;
    file = fopen("patient.txt", "r");
    if (file)
    {
        while (fscanf(file, "%49[^|]|%d|%7[^|]|%lld|%100[^|]|%d|%20[^\n]",
                      last.name, &last.age, last.gender, &last.contact_number,
                      last.address, &last.username, last.password) != EOF)
        {
            // only track last valid username
            if (last.username > last_username)
                last_username = last.username;
        }
        fclose(file);
    }

    temp.username = (((last_username / 10) + 1) * 10) + 9;

    // --- Display auto-generated username ---
    gotoxy(30, 16);
    char username_str[20];
    sprintf(username_str, "%d", temp.username);
    slow_print_string(username_str);

    // --- Password ---
    char initial_password[30];
    do
    {
        gotoxy(33, 17);
        fgets(initial_password, sizeof(initial_password), stdin);
        if (initial_password[0] == '*')
        {
            patient_menu();
            return;
        }
        initial_password[strcspn(initial_password, "\r\n")] = 0;
    } while (strlen(initial_password) < 4);

    do
    {
        gotoxy(20, 18);
        fgets(temp.password, sizeof(temp.password), stdin);
        if (temp.password[0] == '*')
        {
            patient_menu();
            return;
        }
        temp.password[strcspn(temp.password, "\r\n")] = 0;
    } while (strlen(temp.password) < 4);

    if (strcmp(initial_password, temp.password) != 0)
    {
        gotoxy(8, 19);
        slow_print_string("Passwords do not match! Press any key to retry.");
        getch();
        patient_registration();
        return;
    }

    // --- Save to file ---
    file = fopen("patient.txt", "a");
    if (!file)
    {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "%s|%d|%s|%lld|%s|%d|%s\n",
            temp.name, temp.age, temp.gender, temp.contact_number,
            temp.address, temp.username, temp.password);
    fclose(file);

    gotoxy(8, 19);
    slow_print_string("Registration successful! Press any key to continue.");
    getch();
    patient_login();
}

void patient_login()
{
    clrscr();
    FILE *file;
    struct patient temp;
    slow_print_string(border);
    slow_print_string(blank_line);
    slow_print_string("| Patient Login                                                                |\n");
    slow_print_string(frame_line);

    slow_print_string(back_msg);
    slow_print_string(blank_line);
    slow_print_string("| Username:                                                                    |\n");
    slow_print_string("| Password:                                                                    |\n");
    slow_print_string(blank_line);
    slow_print_string(border);
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
            slow_print_string("Login successful! Press any key to continue.");
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
        slow_print_string("Invalid username or password! Press any key to retry.");
        getch();
        fclose(file);
        patient_login();
    }
}

void doctor_registration()
{
    clrscr();
    struct doctor temp, scan;
    slow_print_string(border);
    slow_print_string(blank_line);
    slow_print_string("| Doctor Register                                                              |\n");
    slow_print_string(frame_line);

    slow_print_string(back_msg);
    slow_print_string(blank_line);
    slow_print_string("| Name:                                                                        |\n");
    slow_print_string("| Age:                                                                         |\n");
    slow_print_string("| Contact Number:                                                              |\n");
    slow_print_string(blank_line);
    slow_print_string("| Qualifications:                                                              |\n");
    slow_print_string("| Institution:                                                                 |\n");
    slow_print_string("| Experience(In Years):                                                        |\n");
    slow_print_string(blank_line);
    slow_print_string(blank_line);
    slow_print_string(border);

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
    do
    {
        gotoxy(7, 8);
        char age_str[5];
        slow_print_string("            "); // Clear previous input
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
        slow_print_string("                  "); // Clear previous input
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
        slow_print_string("                     "); // Clear previous input
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
        slow_print_string("            "); // Clear previous input
        gotoxy(24, 13);
        fgets(exp_str, 5, stdin);
        if (exp_str[0] == '*')
        {
            doctor_menu();
        }
        temp.experience = atoi(exp_str);
    } while (temp.experience < 0 || temp.experience > 80);

    clrscr();
    slow_print_string(border);
    slow_print_string(blank_line);
    slow_print_string("| Doctor Register                                                              |\n");
    slow_print_string(frame_line);
    slow_print_string(blank_line);
    slow_print_string("| Choose your specialty:                                                       |\n");
    for (int i = 0; i < 15; i++)
    {
        char spec_line[80];
        char buffer[80];
        sprintf(buffer, "| %2d) %s", i + 1, category[i]);
        slow_print_string(buffer);
        for (int j = 0; j < 79 - strlen(buffer); j++)
        {
            slow_print_string(" ");
        }
        slow_print_string("|\n");
    }
    slow_print_string(blank_line);
    slow_print_string(frame_line);
    slow_print_string(input_msg);
    slow_print_string(border);

    char opt[100];
    int opt_val;
    do
    {
        gotoxy(21, 24);
        slow_print_string("        "); // Clear previous input
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
    slow_print_string(border);
    slow_print_string(blank_line);
    slow_print_string("| Doctor Register                                                              |\n");
    slow_print_string(frame_line);
    slow_print_string(blank_line);
    slow_print_string("| Username (Auto-generated) :                                                  |\n");
    slow_print_string("| Password (Min. 4 characters) :                                               |\n");
    slow_print_string("| Confirm Password:                                                            |\n");
    slow_print_string(blank_line);
    slow_print_string(border);

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
    slow_print_string(username_str);

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
        slow_print_string("Passwords do not match! Press any key to retry.");
        getch();
        fclose(file);
        doctor_registration();
    }
    fprintf(file, "%s|%d|%s|%lld|%s|%s|%d|%d|%s\n", temp.name, temp.age, temp.specialty, temp.contact_number, temp.qualifications, temp.institution, temp.experience, temp.username, temp.password);
    fclose(file);
    gotoxy(8, 9);
    slow_print_string("Registration successful! Press any key to continue.");
    getch();
    doctor_login();
}

void doctor_login()
{
    clrscr();
    slow_print_string(border);
    slow_print_string(blank_line);
    slow_print_string("| Doctor Login                                                                 |\n");
    slow_print_string(frame_line);

    slow_print_string(back_msg);
    slow_print_string(blank_line);
    slow_print_string("| Username:                                                                    |\n");
    slow_print_string("| Password:                                                                    |\n");
    slow_print_string(blank_line);
    slow_print_string(border);
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
            slow_print_string("Login successful! Press any key to continue.");
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
        slow_print_string("Invalid username or password! Press any key to retry.");
        getch();
        fclose(file);
        doctor_login();
    }
}

void patient_dashboard(int username)
{
    clrscr();
    slow_print_string(border);
    slow_print_string(blank_line);
    slow_print_string(blank_line);
    slow_print_string(frame_line);

    slow_print_string(home_msg);
    slow_print_string(blank_line);
    slow_print_string("| 1) Your Info                                                                 |\n");
    slow_print_string("| 2) Book Appointment                                                          |\n");
    slow_print_string("| 3) Appointment History                                                       |\n");
    slow_print_string(blank_line);
    slow_print_string("| 4) Logout                                                                    |\n");
    slow_print_string(blank_line);
    slow_print_string(frame_line);
    slow_print_string(input_msg);
    slow_print_string(border);

    FILE *file;
    struct patient temp;
    file = fopen("patient.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    while (fscanf(file, "%49[^|]|%d|%7[^|]|%lld|%100[^|]|%d|%20[^\n]", temp.name, &temp.age, temp.gender, &temp.contact_number, temp.address, &temp.username, temp.password) != EOF)
    {
        if (temp.username == username)
        {
            break;
        }
    }
    char welcome_msg[100];
    if (temp.name[0] == '\n')
    {
        for (int i = 0; temp.name[i] != '\0'; i++)
        {
            temp.name[i] = temp.name[i + 1];
        }
    }
    sprintf(welcome_msg, "Welcome %s!", temp.name);
    gotoxy(3, 3);
    slow_print_string(welcome_msg);

    char opt;
    do
    {
        gotoxy(21, 14);
        opt = getch();
    } while (!(opt == '1' || opt == '2' || opt == '3' || opt == '4' || opt == '#'));

    switch (opt)
    {
    case '1':
        patient_info(temp.name, temp.age, temp.gender, temp.contact_number, temp.address, temp.username, temp.password);
        break;
    case '2':
        patient_booking(temp.username);
        break;
    case '3':
        patient_history(temp.username);
        break;
    case '4':
        fclose(file);
        patient_login();
        break;
    case '#':
        fclose(file);
        Main_Menu_Page();
        break;
    }
}

void doctor_dashboard(int username)
{
    clrscr();
    slow_print_string(border);
    slow_print_string(blank_line);
    slow_print_string(blank_line);
    slow_print_string(frame_line);

    slow_print_string(home_msg);
    slow_print_string(blank_line);
    slow_print_string("| 1) Your Bio                                                                  |\n");
    slow_print_string("| 2) Appointments                                                              |\n");
    slow_print_string("| 3) Availability                                                              |\n");
    slow_print_string(blank_line);
    slow_print_string("| 4) Logout                                                                    |\n");
    slow_print_string(blank_line);
    slow_print_string(frame_line);
    slow_print_string(input_msg);
    slow_print_string(border);

    FILE *file;
    struct doctor temp;
    file = fopen("doctor.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    while (fscanf(file, "%[^|]|%d|%[^|]|%lld|%[^|]|%[^|]|%d|%d|%[^\n]", temp.name, &temp.age, temp.specialty, &temp.contact_number, temp.qualifications, temp.institution, &temp.experience, &temp.username, temp.password) != EOF)
    {
        if (temp.username == username)
        {
            break;
        }
    }
    char welcome_msg[80];
    if (temp.name[0] == '\n')
    {
        for (int i = 0; temp.name[i] != '\0'; i++)
        {
            temp.name[i] = temp.name[i + 1];
        }
    }
    sprintf(welcome_msg, "Welcome Dr. %s!", temp.name);
    gotoxy(3, 3);
    slow_print_string(welcome_msg);

    char opt;
    do
    {
        gotoxy(21, 14);
        opt = getch();
    } while (!(opt == '1' || opt == '2' || opt == '3' || opt == '4' || opt == '#'));

    switch (opt)
    {
    case '1':
        doctor_bio(temp.username);
        break;
    case '2':
        doctor_appointments(temp.username);
        break;
    case '3':
        doctor_availability(temp.username);
        break;
    case '4':
        fclose(file);
        doctor_login();
        break;
    case '#':
        fclose(file);
        Main_Menu_Page();
        break;
    }
}

void doctor_bio(int username)
{
    clrscr();
    struct doctor temp;
    FILE *file;
    file = fopen("doctor.txt", "r");
    while (fscanf(file, "%[^|]|%d|%[^|]|%lld|%[^|]|%[^|]|%d|%d|%[^\n]", temp.name, &temp.age, temp.specialty, &temp.contact_number, temp.qualifications, temp.institution, &temp.experience, &temp.username, temp.password) != EOF)
    {
        if (temp.username == username)
        {
            break;
        }
    }

    slow_print_string(border);
    slow_print_string(blank_line);
    slow_print_string(blank_line);
    slow_print_string(frame_line);
    slow_print_string(back_msg);
    slow_print_string(blank_line);
    slow_print_string(blank_line);
    slow_print_string(blank_line);
    slow_print_string(blank_line);
    slow_print_string(blank_line);
    slow_print_string(blank_line);
    slow_print_string(blank_line);
    slow_print_string(blank_line);
    slow_print_string(blank_line);
    slow_print_string(border);

    if (temp.name[0] == '\n')
    {
        for (int i = 0; temp.name[i] != '\0'; i++)
        {
            temp.name[i] = temp.name[i + 1];
        }
    }
    gotoxy(3, 3);
    slow_print_string(temp.name);
    slow_print_string(" Bio");

    char username_str[15];
    gotoxy(2, 6);
    sprintf(username_str, "Username: %d", temp.username);
    slow_print_string(username_str);
    gotoxy(2, 7);
    char name_str[60];

    sprintf(name_str, "Name: %s", temp.name);

    slow_print_string(name_str);
    gotoxy(2, 8);
    char age_str[10];
    sprintf(age_str, "Age: %d", temp.age);
    slow_print_string(age_str);
    gotoxy(2, 9);
    char spec[40];
    sprintf(spec, "Specialty: %s", temp.specialty);
    slow_print_string(spec);
    gotoxy(2, 10);
    char contact_str[30];
    sprintf(contact_str, "Contact Number: %lld", temp.contact_number);
    slow_print_string(contact_str);
    gotoxy(2, 11);
    char qual[25];
    sprintf(qual, "Qualifications: %s", temp.qualifications);
    slow_print_string(qual);
    gotoxy(2, 12);
    char inst[100];
    sprintf(inst, "Institution: %s", temp.institution);
    slow_print_string(inst);
    gotoxy(2, 13);
    char experience_str[30];
    sprintf(experience_str, "Experience: %d years", temp.experience);
    slow_print_string(experience_str);

    while (1)
    {
        char opt = getch();
        if (opt == '*')
        {
            doctor_dashboard(username);
            break;
        }
    }
}

void doctor_appointments(int username)
{
    while (1)
    {
        clrscr();
        slow_print_string(border);
        slow_print_string(blank_line);
        slow_print_string("| Doctor Appointment Schedule                                                  |\n");
        slow_print_string(frame_line);
        slow_print_string(back_msg);
        slow_print_string(blank_line);

        FILE *fp = fopen("appointments.txt", "r");
        if (!fp)
        {
            slow_print_string("| No appointments found.                                                       |\n");
            slow_print_string(border);
            getch();
            doctor_dashboard(username);
            return;
        }

        struct appointment all[200];
        int count = 0;

        struct appointment temp;

        while (fscanf(fp, "%d|%d|%[^|]|%d\n", &temp.doctor_username, &temp.patient_username, temp.date, &temp.time_slot) != EOF)
        {
            if (temp.doctor_username != username)
                continue;

            if (compare_date(temp.date) >= 0)
            {
                all[count++] = temp;
            }
        }

        fclose(fp);

        if (count == 0)
        {
            slow_print_string("| No upcoming appointments.                                                    |\n");
            slow_print_string(border);
            getch();
            doctor_dashboard(username);
            return;
        }

        // Sorting by date
        for (int i = 0; i < count - 1; i++)
        {
            for (int j = i + 1; j < count; j++)
            {
                if (strcmp(all[i].date, all[j].date) > 0)
                {
                    struct appointment t = all[i];
                    all[i] = all[j];
                    all[j] = t;
                }
            }
        }

        // Display list
        slow_print_string("| No |      Patient Name     |    Date     |   Slot                            |\n");
        slow_print_string(frame_line);

        for (int i = 0; i < count; i++)
        {
            // Fetch patient name
            FILE *pf = fopen("patient.txt", "r");
            struct patient pt;
            char pname[50];
            strcpy(pname, "Unknown"); // default

            while (fscanf(pf, "%49[^|]|%d|%7[^|]|%lld|%100[^|]|%d|%20[^\n]",
                          pt.name, &pt.age, pt.gender, &pt.contact_number,
                          pt.address, &pt.username, pt.password) != EOF)
            {
                if (pt.username == all[i].patient_username)
                {
                    strncpy(pname, pt.name, sizeof(pname) - 1);
                    pname[sizeof(pname) - 1] = '\0'; // safety
                    if (pname[0] == '\n')
                    {
                        for (int i = 0; pname[i] != '\0'; i++)
                        {
                            pname[i] = pname[i + 1];
                        }
                    }
                    break;
                }
            }
            fclose(pf);

            char time_slot[20];
            switch (all[i].time_slot)
            {
            case 1:
                strcpy(time_slot, "7am-10am");
                break;
            case 2:
                strcpy(time_slot, "12pm-3pm");
                break;
            case 3:
                strcpy(time_slot, "5pm-8pm");
                break;
            }

            char line[150];
            sprintf(line,
                    "| %-2d | %-20s | %s | %-9s |\n",
                    i + 1, pname, all[i].date, time_slot);

            slow_print_string(line);
        }

        slow_print_string(frame_line);
        slow_print_string("| Enter appointment number to CANCEL or '*' to go back: ");

        char choice[10];

        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = 0; // remove newline

        if (choice[0] == '*')
        {
            doctor_dashboard(username);
            return;
        }

        int num = atoi(choice);

        if (num < 1 || num > count)
            continue; // invalid → redisplay

        // CONFIRM CANCEL
        slow_print_string("\n| Are you sure you want to cancel? (y/n): ");
        char c = getch();

        if (c != 'y' && c != 'Y')
            continue;

        // ---- REWRITE FILE WITHOUT SELECTED APPOINTMENT ----
        FILE *in = fopen("appointments.txt", "r");
        FILE *out = fopen("temp.txt", "w");

        int index = num - 1;

        while (fscanf(in, "%d|%d|%[^|]|%d\n",
                      &temp.doctor_username,
                      &temp.patient_username,
                      temp.date,
                      &temp.time_slot) != EOF)
        {
            if (temp.doctor_username == all[index].doctor_username &&
                temp.patient_username == all[index].patient_username &&
                strcmp(temp.date, all[index].date) == 0 &&
                temp.time_slot == all[index].time_slot)
            {
                // Skip this one → cancel
                continue;
            }

            fprintf(out, "%d|%d|%s|%d\n",
                    temp.doctor_username,
                    temp.patient_username,
                    temp.date,
                    temp.time_slot);
        }

        fclose(in);
        fclose(out);

        remove("appointments.txt");
        rename("temp.txt", "appointments.txt");

        slow_print_string("\n| Appointment cancelled successfully! |\n");
        slow_print_string(frame_line);
        getch();

        // Loop again → show updated list
    }
}

void doctor_availability(int username)
{
    clrscr();
    FILE *file;
    struct availability temp, check;
    slow_print_string(border);
    slow_print_string(blank_line);
    slow_print_string("| Doctor Weekly Routine                                                        |\n");
    slow_print_string(frame_line);

    slow_print_string(back_msg);
    slow_print_string(blank_line);
    slow_print_string("| Select Days:                                                                 |\n");
    slow_print_string(blank_line);
    slow_print_string(blank_line);
    slow_print_string(blank_line);
    slow_print_string(blank_line);
    slow_print_string(blank_line);
    slow_print_string(blank_line);
    slow_print_string(blank_line);
    slow_print_string(blank_line);
    slow_print_string(blank_line);
    slow_print_string(frame_line);
    slow_print_string(input_msg);
    slow_print_string(border);

    int y = 8;
    for (int i = 0; i < 8; i++)
    {
        gotoxy(2, y);
        printf("%d) ", i + 1);
        fflush(stdout);
        slow_print_string(week_day[i]);
        y++;
    }
    int opt;
    while (1)
    {
        gotoxy(21, 18);
        opt = getch();
        if (opt == '*')
        {
            doctor_dashboard(username);
            break;
        }
        int option = opt - '0';
        if (option >= 1 && option <= 8)
        {
            strcpy(temp.day, week_day[option - 1]);
            break;
        }
    }

    clrscr();
    slow_print_string(border);
    slow_print_string(blank_line);
    slow_print_string("| Available Shift                                                              |\n");
    slow_print_string(frame_line);
    slow_print_string(blank_line);
    slow_print_string("| Choose your Available Shift:                                                 |\n");
    slow_print_string("|    1) 7am to 10am                                                            |\n");
    slow_print_string("|    2) 12pm to 3pm                                                            |\n");
    slow_print_string("|    3) 5pm to 8pm                                                             |\n");
    slow_print_string("|    4) All Shifts                                                             |\n");
    slow_print_string(blank_line);
    slow_print_string(frame_line);
    slow_print_string(input_msg);
    slow_print_string(border);

    char opt_1;
    while (1)
    {
        gotoxy(21, 13);
        opt_1 = getch();
        if (opt_1 == '*')
        {
            doctor_dashboard(username);
            break;
        }
        int option = opt_1 - '0';
        if (option >= 1 && option <= 4)
        {
            temp.time_slot = option;
            break;
        }
    }
    file = fopen("doctors_availability.txt", "r");
    while (fscanf(file, "%d|%[^|]|%d|%d\n", &check.username, check.day, &check.time_slot, &check.token) != EOF)
    {
        if (check.username == username && check.time_slot == temp.time_slot && strcmp(check.day, temp.day) == 0)
        {
            gotoxy(8, 11);
            slow_print_string("This Day and Shift is already saved. Press any key to continue!");
            getch();
            doctor_dashboard(username);
            fclose(file);
        }

        else
        {

            file = fopen("doctors_availability.txt", "a");
            temp.token = 6;
            fprintf(file, "%d|%s|%d|%d\n", username, temp.day, temp.time_slot, temp.token);
            fclose(file);
            gotoxy(8, 11);
            slow_print_string("Availability Preferences Updated. Press any key to continue!");
            getch();
            doctor_dashboard(username);
        }
    }
}

void patient_info(char *name, int age, char *gender, long long contact_number, char *address, int username, char *password)
{
    clrscr();
    slow_print_string(border);
    slow_print_string(blank_line);
    slow_print_string(blank_line);
    slow_print_string(frame_line);
    slow_print_string(back_msg);
    slow_print_string(blank_line);
    slow_print_string(blank_line);
    slow_print_string(blank_line);
    slow_print_string(blank_line);
    slow_print_string(blank_line);
    slow_print_string(blank_line);
    slow_print_string(blank_line);
    slow_print_string(blank_line);
    slow_print_string(border);

    gotoxy(3, 3);
    slow_print_string(name);
    slow_print_string(" Info");

    char username_str[30];
    gotoxy(2, 6);
    sprintf(username_str, "Username: %d", username);
    slow_print_string(username_str);
    gotoxy(2, 7);
    char name_str[100];
    sprintf(name_str, "Name: %s", name);
    slow_print_string(name_str);
    gotoxy(2, 8);
    char age_str[20];
    sprintf(age_str, "Age: %d", age);
    slow_print_string(age_str);
    gotoxy(2, 9);
    char spec[50];
    sprintf(spec, "Gender: %s", gender);
    slow_print_string(spec);
    gotoxy(2, 10);
    char contact_str[30];
    sprintf(contact_str, "Contact Number: %lld", contact_number);
    slow_print_string(contact_str);
    gotoxy(2, 11);
    char qual[100];
    sprintf(qual, "Address: %s", address);
    slow_print_string(qual);

    gotoxy(2, 12);
    char pass[100];
    sprintf(pass, "Password: %s", password);
    slow_print_string(pass);
    while (1)
    {
        char opt = getch();
        if (opt == '*')
        {
            patient_dashboard(username);
            break;
        }
    }
}

void patient_booking(int username)
{
    clrscr();
    slow_print_string(border);
    slow_print_string(blank_line);
    slow_print_string("| Choose a specialty:                                                          |\n");
    slow_print_string(frame_line);
    slow_print_string(back_msg);
    slow_print_string(blank_line);
    struct doctor temp;
    struct availability check, verify;

    for (int i = 0; i < 15; i++)
    {
        char spec_line[80];
        char buffer[80];
        sprintf(buffer, "| %2d) %s", i + 1, category[i]);
        slow_print_string(buffer);
        for (int j = 0; j < 79 - strlen(buffer); j++)
        {
            slow_print_string(" ");
        }
        slow_print_string("|\n");
    }
    slow_print_string(blank_line);
    slow_print_string(frame_line);
    slow_print_string(input_msg);
    slow_print_string(border);

    char opt[100];
    int opt_val;
    char choosed_specialty[100];
    do
    {
        gotoxy(21, 24);
        slow_print_string("        "); // Clear previous input
        gotoxy(21, 24);
        fgets(opt, 3, stdin);
        if (opt[0] == '*')
        {
            patient_dashboard(username);
        }
        opt[strcspn(opt, "\r\n")] = 0; // Remove newline character
        opt_val = atoi(opt);
    } while (opt_val < 1 || opt_val > 15);
    strcpy(choosed_specialty, category[opt_val - 1]);

    clrscr();
    time_t now = time(NULL);
    time_t tomorrow_time = now + 86400;
    time_t next_day_time = now + 2 * 86400;
    struct tm t = *localtime(&now);
    struct tm tomorrow = *localtime(&tomorrow_time);
    struct tm next_day = *localtime(&next_day_time);

    slow_print_string(border);
    slow_print_string(blank_line);
    slow_print_string("| Choose Date:                                                                 |\n");
    slow_print_string(frame_line);
    slow_print_string(back_msg);
    slow_print_string(blank_line);
    slow_print_string("| 1. Today (          )                                                        |\n");
    slow_print_string("| 2. Tomorrow (          )                                                     |\n");
    slow_print_string("| 3. Day After Tomorrow (          )                                           |\n");
    slow_print_string(blank_line);
    slow_print_string(frame_line);
    slow_print_string(input_msg);
    slow_print_string(border);
    gotoxy(13, 7);
    char date_today[12], date_tomorrow[12], date_next_day[12];
    sprintf(date_today, "%04d-%02d-%02d", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday);
    slow_print_string(date_today);
    gotoxy(16, 8);
    sprintf(date_tomorrow, "%04d-%02d-%02d", tomorrow.tm_year + 1900, tomorrow.tm_mon + 1, tomorrow.tm_mday);
    slow_print_string(date_tomorrow);
    gotoxy(26, 9);
    sprintf(date_next_day, "%04d-%02d-%02d", next_day.tm_year + 1900, next_day.tm_mon + 1, next_day.tm_mday);
    slow_print_string(date_next_day);
    char opt_1;
    char date[11];
    do
    {
        gotoxy(21, 12);
        opt_1 = getch();
    } while (!(opt_1 == '1' || opt_1 == '2' || opt_1 == '3' || opt_1 == '*'));
    switch (opt_1)
    {
    case '1':
        strcpy(check.day, week_day[t.tm_wday]);
        strcpy(date, date_today);
        break;
    case '2':
        strcpy(check.day, week_day[tomorrow.tm_wday]);
        strcpy(date, date_tomorrow);
        break;
    case '3':
        strcpy(check.day, week_day[next_day.tm_wday]);
        strcpy(date, date_next_day);
        break;
    case '*':
        patient_dashboard(username);
        break;
    }

    clrscr();
    slow_print_string(border);
    slow_print_string(blank_line);
    slow_print_string("| Choose Shift:                                                                |\n");
    slow_print_string(frame_line);
    slow_print_string(back_msg);
    slow_print_string(blank_line);
    slow_print_string("| 1. 7am to 10am                                                               |\n");
    slow_print_string("| 2. 12pm to 3pm                                                               |\n");
    slow_print_string("| 3. 5pm to 8pm                                                                |\n");
    slow_print_string(blank_line);
    slow_print_string(frame_line);
    slow_print_string(input_msg);
    slow_print_string(border);
    char opt_2;
    do
    {
        gotoxy(21, 12);
        opt_2 = getch();
    } while (!(opt_2 == '1' || opt_2 == '2' || opt_2 == '3' || opt_2 == '*'));
    if (opt_2 == '*')
    {
        patient_dashboard(username);
    }
    check.time_slot = opt_2 - '0';

    /* ---- CHOOSE DOCTOR (Serial Number, Not Username) ---- */

    clrscr();
    slow_print_string(border);
    slow_print_string(blank_line);
    slow_print_string("| Choose a Doctor:                                                             |\n");
    slow_print_string(frame_line);
    slow_print_string(blank_line);

    FILE *file, *fp;

    int found = 0;
    int y = 6;
    int serial = 1;

    /* Array to store mapping from serial → doctor username */
    int doctor_list[200]; // supports up to 200 doctors

    file = fopen("doctor.txt", "r");
    if (file == NULL)
    {
        gotoxy(8, 11);
        slow_print_string("No doctors registered yet. Press any key to continue!");
        getch();
        patient_dashboard(username);
        return;
    }

    while (fscanf(file, "%49[^|]|%d|%49[^|]|%lld|%99[^|]|%99[^|]|%d|%d|%19[^\n]",
                  temp.name, &temp.age, temp.specialty, &temp.contact_number,
                  temp.qualifications, temp.institution, &temp.experience,
                  &temp.username, temp.password) != EOF)
    {
        if (strcmp(choosed_specialty, temp.specialty) == 0)
        {
            fp = fopen("doctors_availability.txt", "r");
            if (fp == NULL)
                continue;

            if (temp.username <= 0 || strlen(temp.name) == 0)
                continue;

            while (fscanf(fp, "%d|%14[^|]|%d|%d\n",
                          &verify.username, verify.day,
                          &verify.time_slot, &verify.token) != EOF)
            {
                if (verify.username == temp.username &&
                    (verify.time_slot == check.time_slot || verify.time_slot == 4) &&
                    (strcmp(verify.day, check.day) == 0 || strcmp(verify.day, "All") == 0) &&
                    verify.token > 0)

                {
                    char info[256];
                    if (temp.name[0] == '\n')
                    {
                        for (int i = 0; temp.name[i] != '\0'; i++)
                        {
                            temp.name[i] = temp.name[i + 1];
                        }
                    }
                    sprintf(info, "|  %2d) Dr. %s  ", serial, temp.name);

                    doctor_list[serial] = temp.username;

                    gotoxy(0, y);
                    slow_print_string(info);

                    for (int i = 0; i < 79 - strlen(info); i++)
                        slow_print_string(" ");
                    slow_print_string("|\n");

                    found = 1;
                    serial++;
                    y++;
                }
            }
            fclose(fp);
        }
    }

    fclose(file);

    if (!found)
    {
        slow_print_string(blank_line);
        slow_print_string("| No available doctors found for the selected date/shift.                      |");
        getch();
        patient_dashboard(username);
        return;
    }

    slow_print_string(blank_line);
    slow_print_string(frame_line);
    slow_print_string(input_msg);
    slow_print_string(border);

    int selected_serial = 0;
    do
    {
        gotoxy(21, y + 2);
        scanf("%d", &selected_serial);
    } while (selected_serial < 1 || selected_serial >= serial);

    /* ---- SHOW DOCTOR DETAILS & ASK CONFIRM ---- */

    int chosen_username = doctor_list[selected_serial];

    /* Retrieve full doctor info again */
    file = fopen("doctor.txt", "r");
    struct doctor chosen;
    while (fscanf(file, "%49[^|]|%d|%49[^|]|%lld|%99[^|]|%99[^|]|%d|%d|%19[^\n]",
                  chosen.name, &chosen.age, chosen.specialty, &chosen.contact_number,
                  chosen.qualifications, chosen.institution, &chosen.experience,
                  &chosen.username, chosen.password) != EOF)
    {
        if (chosen.username == chosen_username)
            break;
    }
    fclose(file);

    /* Confirmation Page */
    clrscr();
    slow_print_string(border);
    slow_print_string(blank_line);
    slow_print_string("| Doctor Details:                                                              |\n");
    slow_print_string(frame_line);
    slow_print_string(blank_line);

    char line[200];
    if (chosen.name[0] == '\n')
    {
        for (int i = 0; chosen.name[i] != '\0'; i++)
        {
            chosen.name[i] = chosen.name[i + 1];
        }
    }
    sprintf(line, "| Name: Dr. %s", chosen.name);
    slow_print_string(line);
    for (int i = strlen(line); i < 79; i++)
        slow_print_string(" ");
    slow_print_string("|\n");

    sprintf(line, "| Specialty: %s", chosen.specialty);
    slow_print_string(line);
    for (int i = strlen(line); i < 79; i++)
        slow_print_string(" ");
    slow_print_string("|\n");

    sprintf(line, "| Experience: %d years", chosen.experience);
    slow_print_string(line);
    for (int i = strlen(line); i < 79; i++)
        slow_print_string(" ");
    slow_print_string("|\n");

    sprintf(line, "| Qualification: %s", chosen.qualifications);
    slow_print_string(line);
    for (int i = strlen(line); i < 79; i++)
        slow_print_string(" ");
    slow_print_string("|\n");

    sprintf(line, "| Institution: %s", chosen.institution);
    slow_print_string(line);
    for (int i = strlen(line); i < 79; i++)
        slow_print_string(" ");
    slow_print_string("|\n");

    slow_print_string(blank_line);
    slow_print_string(frame_line);
    slow_print_string("| Confirm Booking? (Y/N)                                                       |\n");
    slow_print_string(border);

    char confirm;
    do
    {
        gotoxy(25, 13);
        confirm = getch();
    } while (!(confirm == 'Y' || confirm == 'y' || confirm == 'N' || confirm == 'n'));

    if (confirm == 'N' || confirm == 'n')
    {
        patient_dashboard(username);
        return;
    }

    // SAVE APPOINTMENT
    FILE *save = fopen("appointments.txt", "a");
    fprintf(save, "%d|%d|%s|%d\n",
            chosen_username, username, date, check.time_slot);
    fclose(save);

    // REDUCE TOKEN
    decrease_token(chosen_username, check.day, check.time_slot);

    clrscr();
    slow_print_string(border);
    slow_print_string(blank_line);
    slow_print_string("| Appointment Booked Successfully! Press any key to continue.                  |\n");
    slow_print_string(frame_line);
    getch();
    patient_dashboard(username);
    return;
}

void patient_history(int username)
{
    clrscr();
    slow_print_string(border);
    slow_print_string(blank_line);
    slow_print_string("| Appointment History                                                          |\n");
    slow_print_string(frame_line);
    slow_print_string(back_msg);
    slow_print_string(blank_line);
    slow_print_string("| 1. Current Appointments                                                      |\n");
    slow_print_string("| 2. Past Appointments                                                         |\n");
    slow_print_string(blank_line);
    slow_print_string(frame_line);
    slow_print_string(input_msg);
    slow_print_string(border);

    char opt;
    do
    {
        gotoxy(21, 11);
        opt = getch();

        if (opt == '*')
        {
            patient_dashboard(username);
            return;
        }

        if (opt == '1' || opt == '2')
            break;
    } while (1);

    /* Prepare heading */
    clrscr();
    slow_print_string(border);
    slow_print_string(blank_line);

    if (opt == '1')
        slow_print_string("| Current Appointments                                                         |\n");
    else
        slow_print_string("| Past Appointments                                                            |\n");

    slow_print_string(frame_line);
    slow_print_string(blank_line);

    /* Load appointments into an array for selection */
    FILE *fp = fopen("appointments.txt", "r");
    if (!fp)
    {
        slow_print_string("| No appointment history found.                                                |\n");
        slow_print_string(border);
        getch();
        patient_dashboard(username);
        return;
    }

    struct appointment list[200];
    int list_count = 0;
    struct appointment temp;
    int y = 6;
    int found = 0;

    while (fscanf(fp, "%d|%d|%[^|]|%d\n",
                  &temp.doctor_username, &temp.patient_username, temp.date, &temp.time_slot) != EOF)
    {
        if (temp.patient_username != username)
            continue;

        int cmp = compare_date(temp.date);
        if ((opt == '1' && cmp >= 0) || (opt == '2' && cmp < 0))
        {
            /* store into list for later selection */
            if (list_count < 200)
            {
                list[list_count++] = temp;
            }

            /* display row: lookup doctor */
            struct doctor doc;
            memset(&doc, 0, sizeof(doc));
            FILE *df = fopen("doctor.txt", "r");
            if (df)
            {
                while (fscanf(df, "%[^|]|%d|%[^|]|%lld|%[^|]|%[^|]|%d|%d|%[^\n]",
                              doc.name, &doc.age, doc.specialty, &doc.contact_number,
                              doc.qualifications, doc.institution, &doc.experience,
                              &doc.username, doc.password) != EOF)
                {
                    if (doc.username == temp.doctor_username)
                        break;
                }
                fclose(df);
            }

            if (doc.name[0] == '\n')
            {
                for (int i = 0; doc.name[i] != '\0'; i++)
                    doc.name[i] = doc.name[i + 1];
            }

            char time[20];
            switch (temp.time_slot)
            {
            case 1:
                strcpy(time, "7am to 10am");
                break;
            case 2:
                strcpy(time, "12pm to 3pm");
                break;
            default:
                strcpy(time, "5pm to 8pm");
                break;
            }

            char line[120];
            int serial = list_count; /* 1-based index */
            /* Build left part; we'll pad to reach column 79 then add trailing '|' */
            snprintf(line, sizeof(line), "| %2d) Dr.%s  |  %s  | Slot %s ",
                     serial, doc.name, temp.date, time);

            gotoxy(0, y++);
            slow_print_string(line);
            for (int i = 0; i < 79 - (int)strlen(line); i++)
                slow_print_string(" ");
            slow_print_string("|\n");
            found = 1;
        }
    }
    fclose(fp);

    if (!found)
    {
        slow_print_string("| No records found.                                                            |\n");
        slow_print_string(border);
        getch();
        patient_dashboard(username);
        return;
    }

    /* Show input prompt to select a serial (or '*' to go back) */
    slow_print_string(blank_line);
    slow_print_string(frame_line);
    slow_print_string("| Select appointment number (or '*' to go back)                                |\n");
    slow_print_string(frame_line);
    slow_print_string(input_msg);
    slow_print_string(border);

    int sel = -1;
    do
    {
        gotoxy(21, y + 4);
        char buf[16];
        if (!fgets(buf, sizeof(buf), stdin))
        {
            patient_dashboard(username);
            return;
        }
        if (buf[0] == '*')
        {
            patient_dashboard(username);
            return;
        }
        sel = atoi(buf);
    } while (sel < 1 || sel > list_count);

    /* selected appointment is list[sel-1] */
    struct appointment chosen = list[sel - 1];

    if (opt == '1')
    {
        /* Current appointment: show options Cancel or Reschedule (80-char lines) */
        clrscr();
        slow_print_string(border);
        slow_print_string(blank_line);
        slow_print_string("| Appointment Options                                                          |\n");
        slow_print_string(frame_line);
        slow_print_string(blank_line);
        slow_print_string("| 1. Cancel Appointment                                                        |\n");
        slow_print_string("| 2. Reschedule Appointment                                                    |\n");
        slow_print_string(blank_line);
        slow_print_string(frame_line);
        slow_print_string(input_msg);
        slow_print_string(border);

        char opt2;
        do
        {
            gotoxy(21, 10);
            opt2 = getch();
        } while (!(opt2 == '1' || opt2 == '2' || opt2 == '*'));

        if (opt2 == '*')
        {
            patient_dashboard(username);
            return;
        }

        if (opt2 == '1')
        {
            /* Cancel — ask confirmation */
            clrscr();
            slow_print_string(border);
            slow_print_string(blank_line);
            slow_print_string("| Confirm Cancellation? (Y/N)                                                  |\n");
            slow_print_string(frame_line);
            slow_print_string(border);

            char c;
            do
            {
                c = getch();
            } while (!(c == 'Y' || c == 'y' || c == 'N' || c == 'n'));

            if (c == 'N' || c == 'n')
            {
                patient_dashboard(username);
                return;
            }

            /* delete appointment and increase token for doctor */
            int del = delete_appointment_record(chosen.doctor_username, chosen.patient_username, chosen.date, chosen.time_slot);
            if (del)
            {
                /* Derive weekday name from chosen.date (YYYY-MM-DD) */
                int y1, m1, d1;
                char dayname[16] = "";
                if (sscanf(chosen.date, "%d-%d-%d", &y1, &m1, &d1) == 3)
                {
                    struct tm tmdate = {0};
                    tmdate.tm_year = y1 - 1900;
                    tmdate.tm_mon = m1 - 1;
                    tmdate.tm_mday = d1;
                    mktime(&tmdate); /* fill tm_wday */
                    const char *week_day[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
                    strcpy(dayname, week_day[tmdate.tm_wday]);
                }
                else
                {
                    /* fallback: use "All" so change_token_delta won't fail silently */
                    strcpy(dayname, "All");
                }

                change_token_delta(chosen.doctor_username, dayname, chosen.time_slot, +1);

                clrscr();
                slow_print_string(border);
                slow_print_string(blank_line);
                slow_print_string("| Appointment cancelled successfully. Press any key to continue.               |\n");
                slow_print_string(frame_line);
                slow_print_string(border);
                getch();
                patient_dashboard(username);
                return;
            }
            else
            {
                clrscr();
                slow_print_string(border);
                slow_print_string(blank_line);
                slow_print_string("| Failed to cancel appointment. Press any key to continue.                    |\n");
                slow_print_string(frame_line);
                slow_print_string(border);
                getch();
                patient_dashboard(username);
                return;
            }
        }
        else if (opt2 == '2')
        {
            /* Reschedule flow: book a new appointment in same specialty (any doctor) */
            struct doctor orig_doc;
            memset(&orig_doc, 0, sizeof(orig_doc));
            FILE *df = fopen("doctor.txt", "r");
            if (df)
            {
                while (fscanf(df, "%[^|]|%d|%[^|]|%lld|%[^|]|%[^|]|%d|%d|%[^\n]",
                              orig_doc.name, &orig_doc.age, orig_doc.specialty, &orig_doc.contact_number,
                              orig_doc.qualifications, orig_doc.institution, &orig_doc.experience,
                              &orig_doc.username, orig_doc.password) != EOF)
                {
                    if (orig_doc.username == chosen.doctor_username)
                        break;
                }
                fclose(df);
            }

            /* DATE selection */
            clrscr();
            time_t now = time(NULL);
            time_t tomorrow_time = now + 86400;
            time_t next_day_time = now + 2 * 86400;
            struct tm t = *localtime(&now);
            struct tm tomorrow = *localtime(&tomorrow_time);
            struct tm next_day = *localtime(&next_day_time);
            char date_today[12], date_tomorrow[12], date_next_day[12];
            sprintf(date_today, "%04d-%02d-%02d", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday);
            sprintf(date_tomorrow, "%04d-%02d-%02d", tomorrow.tm_year + 1900, tomorrow.tm_mon + 1, tomorrow.tm_mday);
            sprintf(date_next_day, "%04d-%02d-%02d", next_day.tm_year + 1900, next_day.tm_mon + 1, next_day.tm_mday);

            slow_print_string(border);
            slow_print_string(blank_line);
            slow_print_string("| Choose Date:                                                                 |\n");
            slow_print_string(frame_line);
            slow_print_string(back_msg);
            slow_print_string(blank_line);
            slow_print_string("| 1. Today (          )                                                        |\n");
            slow_print_string("| 2. Tomorrow (          )                                                     |\n");
            slow_print_string("| 3. Day After Tomorrow (          )                                           |\n");
            slow_print_string(blank_line);
            slow_print_string(frame_line);
            slow_print_string(input_msg);
            slow_print_string(border);
            gotoxy(13, 7);
            slow_print_string(date_today);
            gotoxy(16, 8);
            slow_print_string(date_tomorrow);
            gotoxy(26, 9);
            slow_print_string(date_next_day);

            char optd;
            char sel_date[12];
            char sel_dayname[16];
            struct availability chk;
            do
            {
                gotoxy(21, 12);
                optd = getch();
            } while (!(optd == '1' || optd == '2' || optd == '3' || optd == '*'));
            if (optd == '*')
            {
                patient_dashboard(username);
                return;
            }
            if (optd == '1')
            {
                strcpy(sel_date, date_today);
                strcpy(sel_dayname, week_day[t.tm_wday]);
            }
            else if (optd == '2')
            {
                strcpy(sel_date, date_tomorrow);
                strcpy(sel_dayname, week_day[tomorrow.tm_wday]);
            }
            else
            {
                strcpy(sel_date, date_next_day);
                strcpy(sel_dayname, week_day[next_day.tm_wday]);
            }

            /* SHIFT selection */
            clrscr();
            slow_print_string(border);
            slow_print_string(blank_line);
            slow_print_string("| Choose Shift:                                                                |\n");
            slow_print_string(frame_line);
            slow_print_string(back_msg);
            slow_print_string(blank_line);
            slow_print_string("| 1. 7am to 10am                                                               |\n");
            slow_print_string("| 2. 12pm to 3pm                                                               |\n");
            slow_print_string("| 3. 5pm to 8pm                                                                |\n");
            slow_print_string(blank_line);
            slow_print_string(frame_line);
            slow_print_string(input_msg);
            slow_print_string(border);

            char optsh;
            do
            {
                gotoxy(21, 12);
                optsh = getch();
            } while (!(optsh == '1' || optsh == '2' || optsh == '3' || optsh == '*'));
            if (optsh == '*')
            {
                patient_dashboard(username);
                return;
            }
            chk.time_slot = optsh - '0';

            /* LIST doctors of the same specialty with token>0 */
            clrscr();
            slow_print_string(border);
            slow_print_string(blank_line);
            slow_print_string("| Choose Doctor (Available)                                                     |\n");
            slow_print_string(frame_line);
            slow_print_string(blank_line);

            FILE *df2 = fopen("doctor.txt", "r");
            int serial = 1;
            int doc_map[200];
            int y2 = 6;
            struct doctor td;
            if (df2)
            {
                while (fscanf(df2, "%[^|]|%d|%[^|]|%lld|%[^|]|%[^|]|%d|%d|%[^\n]",
                              td.name, &td.age, td.specialty, &td.contact_number,
                              td.qualifications, td.institution, &td.experience,
                              &td.username, td.password) != EOF)
                {
                    if (strcmp(td.specialty, orig_doc.specialty) != 0)
                        continue;

                    /* check availability for this date/day and shift */
                    FILE *avf = fopen("doctors_availability.txt", "r");
                    struct availability av;
                    int ok = 0;
                    if (avf)
                    {
                        while (fscanf(avf, "%d|%14[^|]|%d|%d\n", &av.username, av.day, &av.time_slot, &av.token) != EOF)
                        {
                            if (av.username == td.username &&
                                (av.time_slot == chk.time_slot || av.time_slot == 4) &&
                                (strcmp(av.day, sel_dayname) == 0 || strcmp(av.day, "All") == 0) &&
                                av.token > 0)
                            {
                                ok = 1;
                                break;
                            }
                        }
                        fclose(avf);
                    }
                    if (!ok)
                        continue;

                    char info[200];
                    snprintf(info, sizeof(info), "|  %2d) Dr. %s  ", serial, td.name);
                    doc_map[serial] = td.username;
                    gotoxy(0, y2++);
                    slow_print_string(info);
                    for (int i = 0; i < 79 - (int)strlen(info); i++)
                        slow_print_string(" ");
                    slow_print_string("|\n");
                    serial++;
                }
                fclose(df2);
            }

            if (serial == 1)
            {
                slow_print_string("| No available doctors found for the selected date/shift.                      |\n");
                slow_print_string(border);
                getch();
                patient_dashboard(username);
                return;
            }

            slow_print_string(blank_line);
            slow_print_string(frame_line);
            slow_print_string(input_msg);
            slow_print_string(border);

            int sel_doc = 0;
            do
            {
                gotoxy(21, y2 + 2);
                char b2[16];
                if (!fgets(b2, sizeof(b2), stdin))
                {
                    patient_dashboard(username);
                    return;
                }
                sel_doc = atoi(b2);
            } while (sel_doc < 1 || sel_doc >= serial);

            int new_doctor_username = doc_map[sel_doc];

            /* Confirm booking of new appointment */
            clrscr();
            slow_print_string(border);
            slow_print_string(blank_line);
            slow_print_string("| Confirm Reschedule to new appointment? (Y/N)                                 |\n");
            slow_print_string(frame_line);
            slow_print_string(border);

            char conf;
            do
            {
                conf = getch();
            } while (!(conf == 'Y' || conf == 'y' || conf == 'N' || conf == 'n'));
            if (conf == 'N' || conf == 'n')
            {
                patient_dashboard(username);
                return;
            }

            /* Add new appointment */
            if (!add_appointment_record(new_doctor_username, username, sel_date, chk.time_slot))
            {
                clrscr();
                slow_print_string(border);
                slow_print_string(blank_line);
                slow_print_string("| Failed to book new appointment. Press any key to continue.                   |\n");
                slow_print_string(frame_line);
                slow_print_string(border);
                getch();
                patient_dashboard(username);
                return;
            }

            /* Decrease token of new doctor by 1 */
            change_token_delta(new_doctor_username, sel_dayname, chk.time_slot, -1);

            /* Delete old appointment and increase old doctor's token by 1 */
            if (delete_appointment_record(chosen.doctor_username, chosen.patient_username, chosen.date, chosen.time_slot))
            {
                int y1, m1, d1;
                char oldday[16] = "All";
                if (sscanf(chosen.date, "%d-%d-%d", &y1, &m1, &d1) == 3)
                {
                    struct tm tmdate = {0};
                    tmdate.tm_year = y1 - 1900;
                    tmdate.tm_mon = m1 - 1;
                    tmdate.tm_mday = d1;
                    mktime(&tmdate);
                    const char *week_day[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
                    strcpy(oldday, week_day[tmdate.tm_wday]);
                }
                change_token_delta(chosen.doctor_username, oldday, chosen.time_slot, +1);
            }

            clrscr();
            slow_print_string(border);
            slow_print_string(blank_line);
            slow_print_string("| Rescheduled successfully. Press any key to continue.                         |\n");
            slow_print_string(frame_line);
            slow_print_string(border);
            getch();
            patient_dashboard(username);
            return;
        } /* end reschedule */
    }
    else /* opt == '2' -> past appointment selected */
    {
        /* Past appointment: offer Follow-up to same doctor */
        clrscr();
        slow_print_string(border);
        slow_print_string(blank_line);
        slow_print_string("| Past Appointment Options                                                      |\n");
        slow_print_string(frame_line);
        slow_print_string(blank_line);
        slow_print_string("| 1. Book Follow-up with same doctor                                           |\n");
        slow_print_string("| 2. Back                                                                      |\n");
        slow_print_string(blank_line);
        slow_print_string(frame_line);
        slow_print_string(input_msg);
        slow_print_string(border);

        char optp;
        do
        {
            gotoxy(21, 12);
            optp = getch();
        } while (!(optp == '1' || optp == '2' || optp == '*'));
        if (optp == '*' || optp == '2')
        {
            patient_dashboard(username);
            return;
        }

        if (optp == '1')
        {
            /* Pre-fill doctor = chosen.doctor_username. Let user pick date/shift */
            struct doctor same;
            memset(&same, 0, sizeof(same));
            FILE *df = fopen("doctor.txt", "r");
            if (df)
            {
                while (fscanf(df, "%[^|]|%d|%[^|]|%lld|%[^|]|%[^|]|%d|%d|%[^\n]",
                              same.name, &same.age, same.specialty, &same.contact_number,
                              same.qualifications, same.institution, &same.experience,
                              &same.username, same.password) != EOF)
                {
                    if (same.username == chosen.doctor_username)
                        break;
                }
                fclose(df);
            }

            /* Date selection (today/tomorrow/next) */
            clrscr();
            time_t now2 = time(NULL);
            time_t tomorrow_time2 = now2 + 86400;
            time_t next_day_time2 = now2 + 2 * 86400;
            struct tm t2 = *localtime(&now2);
            struct tm tomorrow2 = *localtime(&tomorrow_time2);
            struct tm next_day2 = *localtime(&next_day_time2);
            char date_today2[12], date_tomorrow2[12], date_next_day2[12];
            sprintf(date_today2, "%04d-%02d-%02d", t2.tm_year + 1900, t2.tm_mon + 1, t2.tm_mday);
            sprintf(date_tomorrow2, "%04d-%02d-%02d", tomorrow2.tm_year + 1900, tomorrow2.tm_mon + 1, tomorrow2.tm_mday);
            sprintf(date_next_day2, "%04d-%02d-%02d", next_day2.tm_year + 1900, next_day2.tm_mon + 1, next_day2.tm_mday);
            char chosen_dayname[16];
            char chosen_date[12];

            slow_print_string(border);
            slow_print_string(blank_line);
            slow_print_string("| Choose Date for Follow-up:                                                    |\n");
            slow_print_string(frame_line);
            slow_print_string(back_msg);
            slow_print_string(blank_line);
            slow_print_string("| 1. Today (          )                                                        |\n");
            slow_print_string("| 2. Tomorrow (          )                                                     |\n");
            slow_print_string("| 3. Day After Tomorrow (          )                                           |\n");
            slow_print_string(blank_line);
            slow_print_string(frame_line);
            slow_print_string(input_msg);
            slow_print_string(border);
            gotoxy(13, 7);
            slow_print_string(date_today2);
            gotoxy(16, 8);
            slow_print_string(date_tomorrow2);
            gotoxy(26, 9);
            slow_print_string(date_next_day2);

            char optd2;
            do
            {
                gotoxy(21, 12);
                optd2 = getch();
            } while (!(optd2 == '1' || optd2 == '2' || optd2 == '3' || optd2 == '*'));
            if (optd2 == '*')
            {
                patient_dashboard(username);
                return;
            }
            if (optd2 == '1')
            {
                strcpy(chosen_date, date_today2);
                strcpy(chosen_dayname, week_day[t2.tm_wday]);
            }
            else if (optd2 == '2')
            {
                strcpy(chosen_date, date_tomorrow2);
                strcpy(chosen_dayname, week_day[tomorrow2.tm_wday]);
            }
            else
            {
                strcpy(chosen_date, date_next_day2);
                strcpy(chosen_dayname, week_day[next_day2.tm_wday]);
            }

            /* Shift selection */
            clrscr();
            slow_print_string(border);
            slow_print_string(blank_line);
            slow_print_string("| Choose Shift:                                                                |\n");
            slow_print_string(frame_line);
            slow_print_string(back_msg);
            slow_print_string(blank_line);
            slow_print_string("| 1. 7am to 10am                                                               |\n");
            slow_print_string("| 2. 12pm to 3pm                                                               |\n");
            slow_print_string("| 3. 5pm to 8pm                                                                |\n");
            slow_print_string(blank_line);
            slow_print_string(frame_line);
            slow_print_string(input_msg);
            slow_print_string(border);

            char optsh2;
            do
            {
                gotoxy(21, 13);
                optsh2 = getch();
            } while (!(optsh2 == '1' || optsh2 == '2' || optsh2 == '3' || optsh2 == '*'));
            if (optsh2 == '*')
            {
                patient_dashboard(username);
                return;
            }
            int chosen_slot = optsh2 - '0';

            /* Check availability for same doctor & chosen_dayname & slot */
            int available = 0;
            FILE *avf = fopen("doctors_availability.txt", "r");
            struct availability av;
            if (avf)
            {
                while (fscanf(avf, "%d|%14[^|]|%d|%d\n", &av.username, av.day, &av.time_slot, &av.token) != EOF)
                {
                    if (av.username == same.username &&
                        (av.time_slot == chosen_slot || av.time_slot == 4) &&
                        (strcmp(av.day, chosen_dayname) == 0 || strcmp(av.day, "All") == 0) &&
                        av.token > 0)
                    {
                        available = 1;
                        break;
                    }
                }
                fclose(avf);
            }

            if (!available)
            {
                clrscr();
                slow_print_string(border);
                slow_print_string(blank_line);
                slow_print_string("| Selected doctor not available for that date/shift. Press any key.           |\n");
                slow_print_string(frame_line);
                slow_print_string(border);
                getch();
                patient_dashboard(username);
                return;
            }

            /* Confirm follow-up booking */
            clrscr();
            slow_print_string(border);
            slow_print_string(blank_line);
            slow_print_string("| Confirm Follow-up booking? (Y/N)                                             |\n");
            slow_print_string(frame_line);
            slow_print_string(border);
            char conf2;
            do
            {
                conf2 = getch();
            } while (!(conf2 == 'Y' || conf2 == 'y' || conf2 == 'N' || conf2 == 'n'));
            if (conf2 == 'N' || conf2 == 'n')
            {
                patient_dashboard(username);
                return;
            }

            /* Add appointment and decrease token */
            if (!add_appointment_record(same.username, username, chosen_date, chosen_slot))
            {
                clrscr();
                slow_print_string(border);
                slow_print_string(blank_line);
                slow_print_string("| Failed to book follow-up. Press any key to continue.                         |\n");
                slow_print_string(frame_line);
                slow_print_string(border);
                getch();
                patient_dashboard(username);
                return;
            }

            change_token_delta(same.username, chosen_dayname, chosen_slot, -1);

            clrscr();
            slow_print_string(border);
            slow_print_string(blank_line);
            slow_print_string("| Follow-up booked successfully. Press any key to continue.                    |\n");
            slow_print_string(frame_line);
            slow_print_string(border);
            getch();
            patient_dashboard(username);
            return;
        }
    }

    /* Fallback: return to dashboard */
    patient_dashboard(username);
}

void decrease_token(int doctor_username, char *day, int time_slot)
{
    FILE *fp = fopen("doctors_availability.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    struct availability av;

    if (!fp || !temp)
        return;

    while (fscanf(fp, "%d|%14[^|]|%d|%d\n",
                  &av.username,
                  av.day,
                  &av.time_slot,
                  &av.token) != EOF)
    {
        if (av.username == doctor_username &&
            av.time_slot == time_slot &&
            strcmp(av.day, day) == 0)
        {
            if (av.token > 0)
                av.token--; // decrease token count
        }

        fprintf(temp, "%d|%s|%d|%d\n",
                av.username,
                av.day,
                av.time_slot,
                av.token);
    }

    fclose(fp);
    fclose(temp);

    remove("doctors_availability.txt");
    rename("temp.txt", "doctors_availability.txt");
}

void change_token_delta(int doctor_username, const char *day, int time_slot, int delta)
{
    FILE *fp = fopen("doctors_availability.txt", "r");
    FILE *tmp = fopen("temp_avail.txt", "w");
    struct availability av;

    if (!fp || !tmp)
    {
        if (fp)
            fclose(fp);
        if (tmp)
            fclose(tmp);
        return;
    }

    while (fscanf(fp, "%d|%14[^|]|%d|%d\n",
                  &av.username, av.day, &av.time_slot, &av.token) != EOF)
    {
        if (av.username == doctor_username &&
            av.time_slot == time_slot &&
            strcmp(av.day, day) == 0)
        {
            int newtok = av.token + delta;
            if (newtok < 0)
                newtok = 0;
            av.token = newtok;
        }
        fprintf(tmp, "%d|%s|%d|%d\n",
                av.username, av.day, av.time_slot, av.token);
    }

    fclose(fp);
    fclose(tmp);
    remove("doctors_availability.txt");
    rename("temp_avail.txt", "doctors_availability.txt");
}

int add_appointment_record(int doctor_username, int patient_username, const char *date, int time_slot)
{
    FILE *fp = fopen("appointments.txt", "a");
    if (!fp)
        return 0;
    fprintf(fp, "%d|%d|%s|%d\n", doctor_username, patient_username, date, time_slot);
    fclose(fp);
    return 1;
}

int delete_appointment_record(int doctor_username, int patient_username, const char *date, int time_slot)
{
    FILE *fp = fopen("appointments.txt", "r");
    FILE *tmp = fopen("temp_appt.txt", "w");
    struct appointment a;
    int deleted = 0;

    if (!fp || !tmp)
    {
        if (fp)
            fclose(fp);
        if (tmp)
            fclose(tmp);
        return 0;
    }

    while (fscanf(fp, "%d|%d|%[^|]|%d\n",
                  &a.doctor_username, &a.patient_username, a.date, &a.time_slot) != EOF)
    {
        if (!deleted &&
            a.doctor_username == doctor_username &&
            a.patient_username == patient_username &&
            strcmp(a.date, date) == 0 &&
            a.time_slot == time_slot)
        {
            /* skip (delete) this one */
            deleted = 1;
            continue;
        }
        fprintf(tmp, "%d|%d|%s|%d\n",
                a.doctor_username, a.patient_username, a.date, a.time_slot);
    }

    fclose(fp);
    fclose(tmp);

    remove("appointments.txt");
    rename("temp_appt.txt", "appointments.txt");

    return deleted;
}
