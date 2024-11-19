#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calculation_randomiser_output.h"
#include "input_and_validation.h"
#include <time.h>
#include <conio.h>"
#define ROWS_MIN 0
#define ROWS_MAX 10
#define RANDOM_MIN -100
#define RANDOM_MAX 100
int main()
{
    do
    {
        srand(time(NULL));

        int rows = validate_int_input("Enter n size of SLAE[1, 10]:\n", ROWS_MIN, ROWS_MAX);
        double epsilon = validate_double_input("Enter precision epsilon [1e-15, 1e-1]:\n", 1e-15, 1e-1);
        double *b = calloc(rows, sizeof(double));
        if(b == NULL) {
            printf("Memory allocation error!!!");
            getch();
            return 1;
        }
        double *x = calloc(rows, sizeof(double));
        if(x == NULL) {
            getch();
            printf("Memory allocation error!!!");
            return 1;
        }
        double *xp = calloc(rows, sizeof(double));
        if(xp == NULL) {
            getch();
            printf("Memory allocation error!!!");
            return 1;
        }
        double **a = calloc(rows, sizeof(double *));
        if(a == NULL) {
            getch();
            printf("Memory allocation error!!!");
            return 1;
        }
        int precision = fabs(log10(epsilon));
        for (int i = 0; i < rows; i++)
        {
            a[i] = calloc(rows, sizeof(double));
        }
        char choice = validate_char_input("Press 'r' to randomly generate the elements or 'm' to enter them manually\n", 'r', 'm');
        switch (choice)
        {
            case 'm':
                for (int i = 0; i < rows; i++)
                {
                    double diagonal_element = 0;
                    double off_diagonal_elements_sum = 0;
                    do
                    {
                        diagonal_element = 0;
                        off_diagonal_elements_sum = 0;
                        for (int j = 0; j < rows; j++)
                        {
                            printf("Enter %d element(a) of row #%d\n", j+1, i+1);
                            a[i][j] = validate_double_input("[-2147483646, 2147483646]: ", -2147483646, 2147483646);
                            if(i == j)
                            {
                                diagonal_element = fabs(a[i][i]);
                            }
                            else
                            {
                                off_diagonal_elements_sum += fabs(a[i][j]);
                            }
                        }
                        if(diagonal_element <= off_diagonal_elements_sum)
                        {
                            printf("Invalid row: a[%d][%d] = %.*lf is not greater than the sum of other elements = %.*lf.\n",
                            i + 1, i + 1, precision, diagonal_element, precision, off_diagonal_elements_sum);
                            printf("Please re-enter the entire row #%d.\n", i + 1);
                        }
                    }
                    while (diagonal_element <= off_diagonal_elements_sum);
                    printf("Enter b of #%d row: \n", i+1);
                    b[i] = validate_double_input("[-2147483646, 2147483646]: ", -2147483646, 2147483646);
                }
                break;
            case 'r':
                generate_random_a_elements(RANDOM_MIN, RANDOM_MAX, a, rows);
                generate_random_b_elements(RANDOM_MIN, RANDOM_MAX, b, rows);
                break;
            default:
                break;
        }
        printf("\n");
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < rows; j++)
            {
                printf("|%*.*lf*x[%02d] ", precision+5, precision, a[i][j], i+1);
            }
            printf(" = %2.*lf", precision, b[i]);
            printf("\n");
        }
        //
        print_elements("b", b, rows, precision);
        printf("\n");
        calculate_slae(a, b, xp, x , rows, epsilon);
        print_elements("x", x ,rows, precision );
        double sum_of_row = 0;
        printf("b after substitution of the value of x\n");
        for (int i = 0; i < rows; i++)
        {
            sum_of_row = 0;
            for (int j = 0; j < rows; j++)
            {
                sum_of_row += a[i][j]*x[j];
            }
            printf("b[%02d] = %.*lf\n", i+1, precision, sum_of_row);
        }
        free(xp);
        free(x);
        free(b);
        for (int i = 0; i < rows; i++)
        {
            free(a[i]);
        }
        free(a);
        printf("Press q to quit, any other key to continue...\n");
    }
    while (getch() != 'q');
    return 0;
}
