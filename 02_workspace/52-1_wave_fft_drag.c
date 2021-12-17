/******************************************************************************
PROGRAM NAME :
AUTHER  : masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FILE *fp, *fp_csv, *fp_dat;

// 円周率の定義
#define pi 4 * atan(1.0)

char filename_read[100];
char filename_dat[100];
char filename_csv[100];

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
        }
    }
}

/*********************************   MAIN   *********************************/

int calculate(char date[])
{

    sprintf(filename_read, "result/%s/51_csv_wave/%s_wave.csv", date, date);
    sprintf(filename_csv, "result/%s/52_csv_wave_fft/%s_wave_fft_drag.csv", date, date);
    sprintf(filename_dat, "result/%s/52_dat_wave_fft/%s_wave_fft_drag.dat", date, date);

    // 変数の作成

    int range = 32;
    double value[range], value_i[range];

    // ファイルの読み込み (dat データ) ・格納

    int i;
    int buf;
    double ch0, ch1;

    for (i = 0; i < range; i++)
    {
        value[i] = 0;
        value_i[i] = 0;
    }

    i = 0;

    fp = fopen(filename_read, "r");

    if (filename_read == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    // printf("check\n");

    while ((fscanf(fp, "%d, %lf, %lf", &buf, &ch0, &ch1)) != EOF)
    {
        // printf("[%d]\t%lf\t%lf\t%lf\n", buf, ch0, ch1);
        value[i] = ch0;
        i = i + 1;
    }

    fclose(fp);

    // FFTの適用

    double ps, as, dt;
    int fq;
    dt = 1;

    S_fft(value, value_i, range, 1);

    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");

    for (i = 0; i < range; i++)
    {
        ps = value[i] * value[i] + value_i[i] * value_i[i];       /* パワースペクトル  */
        as = sqrt(value[i] * value[i] + value_i[i] * value_i[i]); /* 振幅スペクトル  */
        // fq = (double)i / (dt * (double)range);
        fq = i;
        fprintf(fp_csv, "%d,%lf,%lf,%lf\n", fq, ps, value[i], value_i[i]);
        fprintf(fp_dat, "%d\t%lf\t%lf\t%lf\n", fq, ps, value[i], value_i[i]);
        printf("[%d]\tvalue: %lf \tvalue_: %lf\tpw: %lf\tfq :%d\n", i, value[i], value_i[i], ps, fq);
    }

    fclose(fp_csv);
    fclose(fp_dat);
}

int main()
{
    calculate("simulation_data");

    return (0);
}