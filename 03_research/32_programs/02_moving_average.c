/******************************************************************************
PROGRAM NAME : ma.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ch 2
#include "files/fp.h"
/*********************************   MAIN   *********************************/
int ma(char name[], char date[])
{
    // 設定ファイルのインポート
    #include "files/moving_average.h"

    // ファイル名の作成

    char filename[100];
    sprintf(filename, "..//33_result//%s//raw_data//dat//%s.dat", date, name);

    // printf("%s\n",filename);
    // printf("%s\n",filename1);

    // ファイルの読み込み

    fp = fopen(filename, "r");
    if (filename == NULL)
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

    while ((fscanf(fp, "%d\t%lf\t%lf", &num, &ch1, &ch2)) != EOF)
    {
        number[i] = num;
        value[i][1] = ch1;
        value[i][2] = ch2;
        // printf("%d\t%lf\t%lf\n", number[i], value[i][1], value[i][2]);
        i = i + 1;
    }

    fclose(fp);

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

    fp1 = fopen(filename1, "w");

    for (i = 0; i < b; i++)
    {
        fprintf(fp1, "%d\t%lf\t%lf\n", i, ma_d[i], ma_l[i]);
        // printf("[%d]\t%lf\t%lf\n", i, ma_d[i], ma_l[i]);
    }

    fclose(fp1);
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