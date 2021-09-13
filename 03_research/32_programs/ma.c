/******************************************************************************
PROGRAM NAME : ma.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ch 2
#include "files/range.h"

FILE *fp1, *fp2;
/*********************************   MAIN   *********************************/
int ma(char name[], char date[])
{
    // ファイル名の作成

    char filename1[100];
    char filename2[100];

    sprintf(filename1, "..//33_result//%s//raw_data//dat//%s.dat", date, name);
    sprintf(filename2, "..//33_result//%s//moving_average//%d//dat//%s_ma(%d).dat", date, range_ma, name, range_ma);

    // printf("%s\n",filename1);
    // printf("%s\n",filename2);

    // ファイルの読み込み

    fp1 = fopen(filename1, "r");
    if (filename1 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    // データの格納

    int i = 0;
    int N = 1000;
    int num, data_long;
    double ch1, ch2;
    double value[N][ch];
    int number[N];

    // ch1:drag, ch2:lift

    while ((fscanf(fp1, "%d\t%lf\t%lf", &num, &ch1, &ch2)) != EOF)
    {
        number[i] = num;
        value[i][1] = ch1;
        value[i][2] = ch2;
        // printf("%d\t%lf\t%lf\n", number[i], value[i][1], value[i][2]);
        i = i + 1;
    }

    fclose(fp1);

    data_long = i;

    // 計算 (移動平均)

    int j = 0;
    int a, b;

    a = (range_ma - 1) / 2;
    b = data_long - 2 * a;

    double ma_d[b], ma_l[b], sum1, sum2;

    for (i = 0; i < b; i++)
    {
        sum1 = 0;
        sum2 = 0;

        for (j = 0; j < range_ma; j++)
        {
            sum1 = sum1 + value[i + j][1];
            sum2 = sum2 + value[i + j][2];
            j = j + 1;
        }

        ma_d[i] = sum1 / range_ma;
        ma_l[i] = sum2 / range_ma;
    }

    // ファイル書き出し

    fp2 = fopen(filename2, "w");

    for (i = 0; i < b; i++)
    {
        fprintf(fp2, "%d\t%lf\t%lf\n", i, ma_d[i], ma_l[i]);
        printf("[%d]\t%lf\t%lf\n", i, ma_d[i], ma_l[i]);
    }

    fclose(fp2);
}

int main()
{
    // 2021/8/6
    ma("C1", "210806");
    ma("Groove_A", "210806");
    ma("Groove_B", "210806");
    ma("Groove_C", "210806");
    ma("Groove_D", "210806");
    ma("Normal", "210806");
    ma("R1_17.9", "210806");
    ma("R1_18.6", "210806");
    ma("R1_19.3", "210806");

    return (0);
}