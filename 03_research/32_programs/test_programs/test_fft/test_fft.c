/******************************************************************************
PROGRAM NAME : test_fft.c
AUTHER  : masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FILE *fp1, *fp2, *fp3, *fp4;
const char filename1[100] = "test_data/01_sin_n=128.dat";
const char filename2[100] = "test_data/02_sin_n=256.dat";
const char filename3[100] = "test_data/03_sin_n=128_fft.dat";
const char filename4[100] = "test_data/04_sin_n=256_fft.dat";

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
        }
    }
}

/*********************************   MAIN   *********************************/

int main()
{
    // 変数の作成

    int range1 = 128;
    double value_1[range1], value_i_1[range1];

    // ファイルの読み込み (dat データ) ・格納

    int i;
    int num;

    // n = 128

    i = 0;

    fp1 = fopen(filename1, "r");

    if (filename1 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    while (fscanf(fp1, "%d %lf", &num, &value_1[i]) != EOF)
    {
        // printf("[%d]\t%lf\n", num, value_1[i]);
        value_i_1[i] = 0;
        i = i + 1;
    }

    fclose(fp1);

    // FFTの適用

    double pw, fq, dt;
    dt = 1;

    S_fft(value_1, value_i_1, range1, 1);

    fp3 = fopen(filename3, "w");

    for (i = 0; i < range1; i++)
    {
        pw = sqrt(value_1[i] * value_1[i] + value_i_1[i] * value_i_1[i]); /* パワースペクトル  */
        fq = (double)i / (dt * (double)range1);
        fprintf(fp3, "%lf\t%lf\n", fq, pw);
        // printf("[%d]\tvalue: %lf \tvalue_i: %lf\tpw: %lf\tfq :%lf\n", i, value_1[i], value_i_1[i], pw, fq);
    }

    fclose(fp3);

    /*********************************   n=256   *********************************/

    // n = 256

    int range2 = 256;
    double value_2[range2], value_i_2[range2];

    i = 0;

    fp2 = fopen(filename2, "r");

    if (filename2 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    while (fscanf(fp2, "%d %lf", &num, &value_2[i]) != EOF)
    {
        // printf("[%d]\t%lf\n", num, value_2[i]);
        value_i_2[i] = 0;
        i = i + 1;
    }

    fclose(fp2);

    S_fft(value_2, value_i_2, range2, 1);

    fp4 = fopen(filename4, "w");

    for (i = 0; i < range2; i++)
    {
        pw = sqrt(value_2[i] * value_2[i] + value_i_2[i] * value_i_2[i]); /* パワースペクトル  */
        fq = (double)i / (dt * (double)range2);
        fprintf(fp4, "%lf\t%lf\n", fq, pw);
        printf("[%d]\tvalue: %lf \tvalue_i: %lf\tpw: %lf\tfq :%lf\n", i, value_2[i], value_i_2[i], pw, fq);
    }

    fclose(fp4);
}