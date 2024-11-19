#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include "calculation_randomiser_output.h"
#include "input_and_validation.h"

#define ROWS_MIN 1
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
        double *x = calloc(rows, sizeof(double));
        double *xp = calloc(rows, sizeof(double));
        double **a = calloc(rows, sizeof(double *));
        if (!b || !x || !xp || !a)
        {
            printf("Memory allocation error!\n");
            free_arrays(b, x, xp, a, rows);
            getch();
            return 1;
        }
        for (int i = 0; i < rows; i++)
        {
            a[i] = calloc(rows, sizeof(double));
            if (!a[i])
            {
                printf("Memory allocation error!\n");
                free_arrays(b, x, xp, a, rows);
                getch();
                return 1;
            }
        }

        int precision = fabs(log10(epsilon));
        char choice = validate_char_input("Press 'r' to randomly generate the elements or 'm' to enter them manually\n", 'r', 'm');

        switch (choice)
        {
        case 'm':
            double diagonal_element = 0;
            double off_diagonal_elements_sum = 0;
            for (int i = 0; i < rows; i++)
            {
                diagonal_element = 0.0;
                do
                {
                    off_diagonal_elements_sum = 0.0;
                    printf("Enter %d element(s) of row #%d\n", rows, i + 1);
                    for (int j = 0; j < rows; j++)
                    {
                        a[i][j] = validate_double_input("[-2147483646, 2147483646]: ", -2147483646.0, 2147483646.0);
                        if (i == j)
                        {
                            diagonal_element = fabs(a[i][j]);
                        }
                        else
                        {
                            off_diagonal_elements_sum += fabs(a[i][j]);
                        }
                    }
                    if (diagonal_element <= off_diagonal_elements_sum)
                    {
                        printf("Invalid row: a[%d][%d] = %.*lf is not greater than the sum of other elements = %.*lf.\n",
                               i + 1, i + 1, precision, diagonal_element, precision, off_diagonal_elements_sum);
                        printf("Please re-enter the entire row #%d.\n", i + 1);
                    }
                } while (diagonal_element <= off_diagonal_elements_sum);
                printf("Enter b of #%d row: \n", i + 1);
                b[i] = validate_double_input("[-2147483646, 2147483646]: ", -2147483646, 2147483646);
            }
            break;

        case 'r':
            generate_random_a_elements(RANDOM_MIN, RANDOM_MAX, a, rows);
            generate_random_b_elements(RANDOM_MIN, RANDOM_MAX, b, rows);
            break;

        default:
            printf("Error\n");
            free_arrays(b, x, xp, a, rows);
            return 1;
        }

        printf("\nMatrix:\n");
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < rows; j++)
            {
                printf("|%*.*lf*x[%02d] ", precision + 5, precision, a[i][j], j + 1);
            }
            printf(" = %.*lf\n", precision, b[i]);
        }

        calculate_slae(a, b, xp, x, rows, epsilon);

        printf("\nSolution x:\n");
        print_elements("x", x, rows, precision);

        printf("\nb after substitution of the value of x and difference delta b:\n");
        double sum_of_row = 0;
        for (int i = 0; i < rows; i++)
        {
            sum_of_row = 0;
            for (int j = 0; j < rows; j++)
            {
                sum_of_row += a[i][j] * x[j];
            }
            printf("b[%02d] = %.*lf\t delta b[%02d] = %.*e\n", i + 1, precision, sum_of_row, i+1, precision, fabs(sum_of_row - b[i]));
        }

        free_arrays(b, x, xp, a, rows);

        printf("Press q to quit, any other key to continue...\n");
    } while (getch() != 'q');
    return 0;
}
