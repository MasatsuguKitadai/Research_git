/******************************************************************************
PROGRAM NAME : test_fft.c
AUTHER  : masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FILE *fp;
const char filename1[100] = "test_data/sin_n=128.dat";
const char filename2[100] = "test_data/sin_n=256.dat";
const char filename3[100] = "test_data/sin_n=128_fft.dat";
const char filename4[100] = "test_data/sin_n=256_fft.dat";

/*********************************   MAIN   *********************************/

int main()
{

#include "fft.h"

    // n=256の正弦波について

    // 変数の作成

    int range1 = 128;
    double data[range1], value[range1], value_i[range1];

    int range2 = 128;
    double data_2[range2], value_2[range2], value_i_2[range2];

    // ファイルの読み込み (dat データ)

    fp = fopen(filename1, "r");
    if (filename1 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    // データの格納

    int i = 0;
    int num;

    while (fscanf(fp, "%d %lf", &num, &value[i]) != EOF)
    {
        // value[i] = value_sin;
        // printf("[%d]\t%lf\n", num, value[i]);
        i = i + 1;
    }

    fclose(fp);

    // FFTの適用

    S_fft(value, value_i, range1, 1);

    double pw, fq, dt;
    dt = 1;

    fp = fopen(filename3, "w");

    for (i = 0; i < range1; i++)
    {
        pw = sqrt(value[i] * value[i] + value_i[i] * value_i[i]); /* パワースペクトル  */
        fq = (double)i / (dt * (double)range1);
        fprintf(fp, "%lf\t%lf\n", pw, fq);
        printf("[%d]\tvalue: %lf\tvalue_i: %lf\tpw: %lf\tfq :%lf\n", i, value[i], value_i[i], pw, fq);
    }

    fclose(fp);
}