#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calculation.h"
#include "validation.h"
#include <time.h>
#include <conio.h>
int main()
{
    do
    {
        srand(time(NULL));
        int rows = validate_int_input("Enter n size of SLAE\n", 1, 3200);
        double epsilon = validate_double_input("Enter precision epsilon:\n", 1e-15, 1e-1);
        double *b = calloc(rows, sizeof(double));
        double *x = calloc(rows, sizeof(double));
        double *xp = calloc(rows, sizeof(double));
        double **a = calloc(rows, sizeof(double *));
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
                    printf("Enter %d elements(a) of row #%d\n", i+1, i+1);
                    for (int j = 0; j < rows; j++)
                    {
                        a[i][j] = validate_double_input("[-2147483646, 2147483646]: ", -2147483646, 2147483646);
                    }
                    printf("Enter b of #%d row: \n", i+1);
                    b[i] = validate_double_input("[-2147483646, 2147483646]: ", -2147483646, 2147483646);
                }
            case 'r':
                generate_random_a_elements(-2147483646.0, 2147483646.0, a, rows, epsilon);
            generate_random_b_elements(-2147483646.0, 2147483646.0, b, rows, epsilon);
            default:
        }
        printf(">>-----------------------------------------*-----------------------------------------<<\n");
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < rows; j++)
            {
                printf("%lf ||\t", a[i][j]);
            }
            printf("\n");
        }

        printf(">>-----------------------------------------*-----------------------------------------<<\n");
        calculate_slae(a, b, xp, x , rows, epsilon);

        for (int i = 0; i < rows; i++)
        {
            printf("x[%d] = %.*lf\n", i+1, (int)fabs(log10(epsilon)), x[i]);
        }
        //freeing memory
        free(xp);
        free(x);
        free(b);
        for (int i = 0; i < rows; i++)
        {
            free(a[i]);
        }
        free(a);
        printf("Press q to quit, any other key to continue...");
    }
    while (getch() != 'q');
    return 0;
}
