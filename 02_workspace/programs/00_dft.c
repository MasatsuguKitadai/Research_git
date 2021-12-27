/******************************************************************************
PROGRAM NAME :
AUTHER  : masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double pi = 4 * atan(1.0);

/*********************************   FFT   *********************************/

void S_dft(double ak[], double bk[], int n, int ff)
{

    /* ff=1 for FFT, ff=-1 for Inverse FT */
    // ak = 実部, bk = 虚部, n = データ数

    int j, k;
    double r, i;
    double result_R[n], result_I[n];

    for (k = 0; k < n; k++)
    {
        r = 0;
        i = 0;

        for (j = 0; j < n; j++)
        {
            // printf("value[%d]\t%.3f", j, ak[j]);
            r = r + ak[j] * cos(-2 * pi * k * j / n);
            i = i + ak[j] * sin(-2 * pi * k * j / n);
        }

        result_R[k] = r;
        result_I[k] = i;
    }

    for (k = 0; k < n; k++)
    {
        ak[k] = result_R[k];
        bk[k] = result_I[k];
    }
}