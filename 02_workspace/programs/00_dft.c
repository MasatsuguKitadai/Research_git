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
    double r;
    double i;

    for (k = 0; k < n; k++)
    {
        r = 0;
        i = 0;
        for (j = 0; j < n; n++)
        {
            r += ak[j] * cos((2 * M_PI * k * j) / n);
            i -= ak[j] * sin((2 * M_PI * k * j) / n);
        }
        ak[k] = r;
        bk[k] = i;
    }
}