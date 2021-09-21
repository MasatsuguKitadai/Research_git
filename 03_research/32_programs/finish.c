/******************************************************************************
PROGRAM NAME : identify.c
AUTHER  : masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ch 2
#include "files/fp.h"
/*********************************   identifyIN   *********************************/
int identify(char name[], char date[])
{
#include "files/file.h"

    // printf("%s\n",filename4);
    // printf("%s\n",filename6);

    // ファイルの読み込み

    // 開始点特定 範囲
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

    int finish_num[ch];
    double finish_value[ch];
    double top[ch], bottom[ch], sum1[ch], sum2[ch], ave1[ch], ave2[ch];
    double d1[range_1], l1[range_1], d2[range_2], l2[range_2];

    // drag

    finish_num[1] = 0;
    finish_value[1] = 0;
    top[1] = 0;
    bottom[1] = 0;

    for (i = 200; i < range; i++)
    {
        // 配列の初期化

        sum1[1] = 0;
        ave1[1] = 0;
        sum2[1] = 0;
        ave2[1] = 0;

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
        if (bottom[1] > d1[0])
        {
            bottom[1] = d1[0];
        }
        if (top[1] < d1[range_1 - 1])
        {
            top[1] = d1[range_1 - 1];
        }

        // 平均値の算出 (前部)
        for (j = 0; j < range_1; j++)
        {
            sum1[1] = sum1[1] + d1[j];
        }

        ave1[1] = sum1[1] / range_1;

        // 平均値の算出 (後部)
        for (k = 0; k < range_2; k++)
        {
            sum2[1] = sum2[1] + d2[k];
        }

        ave2[1] = sum2[1] / range_2;

        // (1) drag
        if (ave2[1] < bottom[1])
        {
            finish_num[1] = i + range_1 + range_2;
            finish_value[1] = value[i + range_1 + range_2][1];
            break;
        }
    }

    // lift

    finish_num[2] = 0;
    finish_value[2] = 0;
    top[2] = 0;
    bottom[2] = 0;

    for (i = 200; i < range; i++)
    {
        // 配列の初期化

        sum1[2] = 0;
        ave1[2] = 0;
        sum2[2] = 0;
        ave2[2] = 0;

        // 指定された範囲の配列を作成
        for (j = 0; j < range_1; j++)
        {
            l1[j] = value[i + j][2];
            // printf("[%d]\t%lf\t%lf\n", j, d1[j], l1[j]);
        }

        for (k = 1; k < range_2 + 1; k++)
        {
            l2[k] = value[i + range_1 + k][2];
            // printf("[%d]\t%lf\t%lf\n", k, d2[k], l2[k]);
        }

        // 並び替え (小さい順)
        for (x = 0; x < range_1; x++)
        {
            // lift
            y = x;
            for (z = x; z < range_1; z++)
            {
                if (l1[z] < l1[y])
                {
                    y = z;
                }
            }
            if (x < y)
            {
                w = l1[x];
                l1[x] = l1[y];
                l1[y] = w;
            }
            // printf("[%d]\t%lf\t%lf\n", x, d[x], l[x]);
        }
        // printf("[%d]\t%lf\t%lf\n", i, me_d[i], me_l[i]);

        // 範囲の最大値・最小値の特定
        if (bottom[1] > l1[0])
        {
            bottom[1] = l1[0];
        }
        if (top[1] < l1[range_1 - 1])
        {
            top[1] = l1[range_1 - 1];
        }

        // 平均値の算出 (前部)
        for (j = 0; j < range_1; j++)
        {
            sum1[2] = sum1[2] + l1[j];
        }

        ave1[2] = sum1[2] / range_1;

        // 平均値の算出 (後部)
        for (k = 0; k < range_2; k++)
        {
            sum2[2] = sum2[2] + l2[k];
        }

        ave2[2] = sum2[2] / range_2;

        // (1) lift
        if (ave2[2] > top[2])
        {
            finish_num[2] = i + range_1 + range_2;
            finish_value[2] = value[i + range_1 + range_2][2];
            break;
        }
    }

    printf("[%d]\t%lf\t[%d]\t%lf\t(%s)\n", finish_num[1], finish_value[1], finish_num[2], finish_value[2], name);

    // drag 終了後からの平均値計算

    int omit = 30;
    double sum, ave;
    sum = 0;
    ave = 0;

    for (i = finish_num[1]; i < data_long - omit; i++)
    {
        sum = sum + value[i][1];
    }

    ave = sum / (data_long - omit - finish_num[1]);

    // printf("[%d]\tvalue : %lf\taverage : %lf\t sum : %lf\t(%s)\n", finish_num[1], finish_value[1], ave, sum, name);

    // ファイル書き出し

    fp5 = fopen(filename6, "w");

    // fprintf(fp5, "model, drag, drag, lift, lift\n", );
    // fprintf(fp5, "%s, (sec), (v), (sec), (v)\n", );
    fprintf(fp5, "%d\t%lf\t%d\t%lf\n", finish_num[1], finish_value[1], finish_num[2], finish_value[2]);
    // fprintf(fp5, "前:%d\t後:%d\n", range_1, range_2);

    fclose(fp5);

    fp8 = fopen(filename8, "w");

    fprintf(fp8, "%d\t%lf\n", finish_num[1], ave);

    fclose(fp8);
}

int main()
{
    // 2021/8/6
    identify("C1", "210806");
    identify("Groove_A", "210806");
    identify("Groove_B", "210806");
    identify("Groove_C", "210806");
    identify("Groove_D", "210806");
    identify("Normal", "210806");
    identify("R1_17.9", "210806");
    identify("R1_18.6", "210806");
    identify("R1_19.3", "210806");

    return (0);
}