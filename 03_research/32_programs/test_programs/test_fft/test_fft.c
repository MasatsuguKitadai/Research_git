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

    int range = 256;
    double data[range], value[range], value_i[range]; 

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
    double row1, row2;

    while ((fscanf(fp, "%d\t%lf\t%lf", &num, &row1, &row2)) != EOF)
    {
        data[i] = row2;
        i = i + 1;
        printf("%d\t%lf\t%lf\n", num, row1, row2);
    }

    fclose(fp);

    // FFTの適用

    S_fft(value, value_i, range, 1);

    double pw, fq, dt;
    dt = 1;

    fp = fopen(filename2, "w");

    for(i = 0; i < range; i++)
    {
        pw = sqrt(value[i] * value[i] + value_i[i] * value_i[i]);  /* パワースペクトル  */
        fq = (double)i / (dt * (double)range);
        fprintf(fp, "%lf\t%lf\n", pw, fq);
        printf("[%d]\t%lf\t%lf\n", i, pw, fq);
    }

    fclose(fp);

}