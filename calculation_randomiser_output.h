#ifndef X_I_CALCULATIONS_H
#define X_I_CALCULATIONS_H
void calculate_slae(double **a, double *b, double *xp, double *x, int rows, double epsilon)
{
    int iterations = 0;
    double max_delta = 0;
    do
    {
        for (int i = 0; i < rows; i++) {
            double sum = 0;
            for (int j = 0; j < rows; j++) {
                if (j != i) {
                    sum += a[i][j] * xp[j];
                }
            }
            x[i] = (b[i] - sum) / a[i][i];
            double delta = fabs(x[i] - xp[i]);
            if (delta > max_delta)
            {
                max_delta = delta;
            }
        }
        for (int i = 0; i < rows; i++)
        {
            xp[i] = x[i];
        }
        iterations++;
    }
    while (max_delta < epsilon);
}
void generate_random_a_elements(double min, double max, double **arr, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            arr[i][j] = (double)rand() + (rand() + (rand() / (double)RAND_MAX)) / (RAND_MAX + 1.0);
        }
    }
}
void generate_random_b_elements(double min, double max, double *arr, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        arr[i]= (double)rand() + (rand() + (rand() / (double)RAND_MAX)) / (RAND_MAX + 1.0);
    }
}
void print_elements(char *label, double *arr, int rows, int precision)
{
    for (int i = 0; i < rows; i++)
    {
        printf("%s[%d] = %.*lf\n", label, i+1, precision, arr[i]);
    }
}
#endif