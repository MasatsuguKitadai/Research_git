/******************************************************************************
PROGRAM NAME :
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FILE *fp, *fp_dat, *fp_csv;
/*********************************   MAIN   *********************************/
int auto_average(char date[], char angle[])
{
    // 変数宣言
    int i, j, k, l;
    int datalength = 0;
    int ch = 3;
    int data_flame = 5000;
    double value[data_flame][ch];
    double ch0, ch1, ch2; // ch0:drag, ch1:lift, ch2:load-cell

    // 読み込みファイルの指定
    char filename_read[100];
    char filename_csv[100];
    char filename_dat[100];

    sprintf(filename_read,"%s/csv_reverse/%s_reverse.CSV",  date, angle);
    sprintf(filename_csv, "%s/csv_result/%s_average.CSV",   date, angle);
    sprintf(filename_dat, "%s/dat_result/%s_average.dat",   date, angle);
    printf("【%s】\n", angle);

    // 配列の初期化

    for (i = 0; i < data_flame; i++)
    {
        for (j = 0; j < 3; j++)
        {
            value[i][j] = 0;
        }
    }

    // printf("check\n");

    // ファイルの読み込み
    fp = fopen(filename_csv, "r");
    if (filename_read == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    i = 0;

    while ((fscanf(fp, "%lf, %lf, %lf", &ch0, &ch1, &ch2)) != EOF)
    {
        // printf("%lf, %lf, %lf\n", ch0, ch1, ch2);
        value[i][0] = ch0;
        value[i][1] = ch1;
        value[i][2] = ch2;
        i = i + 1;
    }

    fclose(fp);

    datalength = i;
    printf("datalengh = %d\n", datalength);

    // 計算
    double a[2], b[2];

    // 比例定数 a
    a[1] = (finish_ave[1] - start_ave[1]) / (ave_num[2] - ave_num[1]);
    a[2] = (finish_ave[2] - start_ave[2]) / (ave_num[2] - ave_num[1]);

    // 切片 b
    b[1] = start_ave[1] - a[1] * ave_num[1];
    b[2] = start_ave[2] - a[2] * ave_num[1];

    // 関数 f
    // printf("f(x) = %lf x + %lf \tdrag\t%s\n", a[1], b[1], name);
    // printf("f(x) = %lf x + %lf \tlift\t%s\n", a[2], b[2], name);

    // 変数の宣言
    int j, range;
    double f[data_long][2], c[data_long][2];

    // 配列の初期化
    for (j = 0; j < data_long; j++)
    {
        f[j][1] = 0;
        f[j][2] = 0;
    }

    // 線形補間の値の計算
    // printf("%s\n", name);
    for (j = 0; j < data_long; j++)
    {
        f[j][1] = a[1] * j + b[1];
        f[j][2] = a[2] * j + b[2];
        // printf("[%d]\t%lf\t%lf\n", j, f[j][1], f[j][2]);
    }

    // 補正値の計算
    for (j = 0; j < data_long; j++)
    {
        c[j][1] = value[j][1] - f[j][1];
        c[j][2] = value[j][2] - f[j][2];
        // printf("[%d]\t%lf\t%lf\n", j, c[j][1], c[j][2]);
    }

    // 書き出し
    fp7 = fopen(filename7, "w");

    for (j = 0; j < data_long; j++)
    {
        fprintf(fp7, "%d\t%lf\t%lf\t%lf\t%lf\n", j, f[j][1], c[j][1], f[j][2], c[j][2]);
    }

    fclose(fp7);

}