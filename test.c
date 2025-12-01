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

int main()
{
    FILE *file;
    struct doctor temp;
    file = fopen("doctor.txt", "r");
    int username = 22;
    while (fscanf(file, "%[^|]|%d|%[^|]|%lld|%[^|]|%[^|]|%d|%d|%[^\n]", temp.name, &temp.age, temp.specialty, &temp.contact_number, temp.qualifications, temp.institution, &temp.experience, &temp.username, temp.password) != EOF)
    {
        if (temp.username == username)
        {
            break;
        }
    }

    printf("DEBUG: Name='%s'\n", temp.name);
    printf("DEBUG: Specialty='%s'\n", temp.specialty);
    printf("DEBUG: Institution='%s'\n", temp.institution);
    printf("DEBUG: Password='%s'\n", temp.password);
    fclose(file);
    return 0;
}