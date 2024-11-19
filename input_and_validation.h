#ifndef VALIDATION_H
#define VALIDATION_H
#include <conio.h>
int validate_int_input(char *prompt, int min, int max)
{
    int value = 0 ;
    int input = 0;
    do
    {
        printf("%s", prompt);
        input = scanf("%d", &value);
        if (input != 1 || value < min || value > max)
        {
            printf("Invalid input. Please enter a valid number.\n");
        }
        fflush(stdin);
    }
    while (input != 1 || value < min || value > max);
    return value;
}
double validate_double_input(const char *prompt, double min, double max)
{
    double value = 0 ;
    int input = 0;
    do
    {
        printf("%s", prompt);
        input = scanf("%lf", &value);
        if (input != 1 || value < min || value > max)
        {
            printf("Invalid input. Please enter a valid number.\n");
        }
        fflush(stdin);
    }
    while (input != 1 || value < min || value > max);
    return value;
}
double validate_char_input(char *prompt, char choice_1, char choice_2)
{
    char user_choice = 0;
    do
    {
        printf("%s", prompt);
        user_choice = getch();
        if (user_choice != choice_1 && user_choice != choice_2)
        {
            printf("Invalid input.\n");
        }
        fflush(stdin);
    }
    while (user_choice != choice_1 && user_choice != choice_2);
    return user_choice;
}
void free_arrays(double *b, double *x, double *xp, double **a, int rows)
{
    free(xp);
    free(x);
    free(b);
    for (int i = 0; i < rows; i++)
    {
        free(a[i]);
    }
    free(a);
}
#endif
