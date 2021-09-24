/******************************************************************************
PROGRAM NAME : finish.c
AUTHER  : masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ch 2
#include "files/fp.h"
/*********************************   MAIN   *********************************/
int finish(char name[], char date[])
{
#include "files/file.h"

    // printf("%s\n",filename4);
    // printf("%s\n",filename6);

    // ファイルの読み込み

    // 停止点特定 範囲
    int range_1 = 150; // 前部の範囲
    int range_2 = 10;  // 後部の範囲

    fp4 = fopen(filename4, "r");
    if (filename4 == NULL)
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

    while ((fscanf(fp4, "%d\t%lf\t%lf", &num, &ch1, &ch2)) != EOF)
    {
        number[i] = num;
        value[i][1] = ch1;
        value[i][2] = ch2;
        // printf("%d\t%lf\t%lf\n", number[i], value[i][1], value[i][2]);
        i = i + 1;
    }

    fclose(fp4);

    data_long = i;

    // 計算 (測定終了点の特定)

    int j, k;
    int range;
    int x, y, z;
    double w;

    range = data_long - (range_1);

    int finish_num;
    double finish_value[ch];
    double top, bottom, sum1, sum2, ave1, ave2;
    double d1[range_1], l1[range_1], d2[range_2], l2[range_2];

    // drag

    finish_num = 0;
    finish_value[1] = 0;
    top = 0;
    bottom = 0;

    for (i = 200; i < range; i++)
    {
        // 配列の初期化

        sum1 = 0;
        ave1 = 0;
        sum2 = 0;
        ave2 = 0;

        // 指定された範囲の配列を作成
        for (j = 0; j < range_1; j++)
        {
            d1[j] = value[i + j][1];
            // printf("[%d]\t%lf\n", j, d1[j]);
        }

        for (k = 1; k < range_2 + 1; k++)
        {
            d2[k] = value[i + range_1 + k][1];
            // printf("[%d]\t%lf\n", k, d2[k]);
        }

        // 並び替え (小さい順)
        for (x = 0; x < range_1; x++)
        {
            // drag
            y = x;
            for (z = x; z < range_1; z++)
            {
                if (d1[z] < d1[y])
                {
                    y = z;
                }
            }
            if (x < y)
            {
                w = d1[x];
                d1[x] = d1[y];
                d1[y] = w;
            }
        }

        // 範囲の最大値・最小値の特定
        if (bottom > d1[0])
        {
            bottom = d1[0];
        }
        if (top < d1[range_1 - 1])
        {
            top = d1[range_1 - 1];
        }

        // 平均値の算出 (前部)
        for (j = 0; j < range_1; j++)
        {
            sum1 = sum1 + d1[j];
        }

        ave1 = sum1 / range_1;

        // 平均値の算出 (後部)
        for (k = 0; k < range_2; k++)
        {
            sum2 = sum2 + d2[k];
        }

        ave2 = sum2 / range_2;

        // (1) drag
        if (ave2 < bottom)
        {
            finish_num = i + range_1 + range_2;
            finish_value[1] = value[finish_num][1];
            break;
        }
    }

    // 終了後からの平均値計算

    int sec = 60;
    int ave_num;
    double sum[2], ave[2];

    // drag
    sum[1] = 0;
    ave[1] = 0;

    for (i = finish_num; i < finish_num + sec; i++)
    {
        sum[1] = sum[1] + value[i][1];
    }

    ave[1] = sum[1] / sec;
    ave_num = finish_num + sec / 2;

    // lift

    finish_value[2] = value[finish_num][2];

    sum[2] = 0;
    ave[2] = 0;

    for (i = finish_num; i < finish_num + sec + 1; i++)
    {
        sum[2] = sum[2] + value[i][2];
    }

    ave[2] = sum[2] / (sec + 1);

    // ファイル書き出し

    fp6 = fopen(filename6, "w");

    fprintf(fp6, "%d\t%lf\t%lf\t%lf\t%lf\t%d\n", finish_num, finish_value[1], ave[1], finish_value[2], ave[2], ave_num);

    fclose(fp6);
}

// int main()
// {
//     // 2021/8/6
//     finish("C1", "210806");
//     finish("Groove_A", "210806");
//     finish("Groove_B", "210806");
//     finish("Groove_C", "210806");
//     finish("Groove_D", "210806");
//     finish("Normal", "210806");
//     finish("R1_17.9", "210806");
//     finish("R1_18.6", "210806");
//     finish("R1_19.3", "210806");

//     return (0);
// }