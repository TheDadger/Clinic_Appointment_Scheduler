#include <stdio.h>

int main()
{
    int number = 1109;
    int id = ((number / 10) + 1) * 10 + 9;
    printf("ID: %d\n", id);

    return 0;
}