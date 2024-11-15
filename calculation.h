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
void generate_random_a_elements(double min, double max, double **arr, int rows, double epsilon)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            arr[i][j] = min + rand() / (double)RAND_MAX * (max - min) + min + rand() / (double)RAND_MAX * (max - min) / log10(epsilon);
        }
    }
}
void generate_random_b_elements(double min, double max, double *arr, int rows, double epsilon)
{
    for (int i = 0; i < rows; i++)
    {
        arr[i]= min + (rand() / (double)RAND_MAX) * (max - min) + min + rand() / (double)RAND_MAX * (max - min) / log10(epsilon);
    }
}
#endif
