/******************************************************************************
PROGRAM NAME :
AUTHER  : masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 円周率の定義
#define pi 4 * atan(1.0)

/*********************************   FFT   *********************************/

void S_fft(double ak[], double bk[], int n, int ff)
{
    /* ff=1 for FFT, ff=-1 for Inverse FT */
    int i, j, k, k1, num, nhalf, phi, phi0, rot[n];
    double s, sc, c, a0, b0, tmp;

    for (i = 0; i < n; i++)
    {
        rot[i] = 0;
    }

    nhalf = n / 2;
    num = n / 2;
    sc = (2.0 * pi) / (double)n;

    while (num >= 1)
    {
        for (j = 0; j < n; j += (2 * num))
        {
            phi = rot[j] / 2;
            phi0 = phi + nhalf;

            for (k = j; k < j + num; k++)
            {
                k1 = k + num;
                a0 = ak[k1] * cos(sc * (double)phi) - bk[k1] * ff * sin(sc * (double)(phi));
                b0 = ak[k1] * ff * sin(sc * (double)(phi)) + bk[k1] * cos(sc * (double)phi);
                ak[k1] = ak[k] - a0;
                bk[k1] = bk[k] - b0;
                ak[k] = ak[k] + a0;
                bk[k] = bk[k] + b0;
                rot[k] = phi;
                rot[k1] = phi0;
            }
        }
        num = num / 2;
    }

    if (ff < 0)
    {
        for (i = 0; i < n; i++)
        {
            ak[i] /= (double)n;
            bk[i] /= (double)n;
        }
    }

    for (i = 0; i < n - 1; i++)
    {
        if ((j = rot[i]) > i)
        {
            tmp = ak[i];
            ak[i] = ak[j];
            ak[j] = tmp;
            tmp = bk[i];
            bk[i] = bk[j];
            bk[j] = tmp;
            bk[i] = -bk[i];
        }
    }
}