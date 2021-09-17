/******************************************************************************
PROGRAM NAME : finish_avergae.c
AUTHER  : masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ch 2
#include "files/fp.h"
/*********************************   MAIN   *********************************/
int finish_average(char name[], char date[])
{
    // 設定ファイルのインポート

#include "files/file.h"

    // ファイルの読み込み

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

    // 終了点データの格納

    int finish_num[ch];
    double finish_value[ch];

    fp6 = fopen(filename6, "r");
    if (filename6 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    fscanf(fp6, "%d\t%lf\t%d\t%lf", &finish_num[1], &finish_value[1], &finish_num[2], &finish_value[2]);
    // printf("%d\t%lf\t%d\t%lf\t(%s)\n",finish_num[1], finish_value[1], finish_num[2], finish_value[2], name);

    fclose(fp6);

    // 計算 (終了点後の平均値の算出)

    int omit = 30;
    double sum, ave;
    sum = 0;
    ave = 0;

    for (i = finish_num[1]; i < data_long - omit; i++)
    {
        sum = sum + value[i][1];
    }

    ave = sum / (data_long - omit - finish_num[1]);
    printf("[%d]\tvalue : %lf\taverage : %lf\t sum : %lf\t(%s)\n", finish_num[1], finish_value[1], ave, sum, name);

    // 書き出し

    fp8 = fopen(filename8, "w");

    fprintf(fp8, "%d\t%lf\n", finish_num[1], ave);

    fclose(fp8);
}

int main()
{
    // 2021/8/6
    finish_average("C1", "210806");
    finish_average("Groove_A", "210806");
    finish_average("Groove_B", "210806");
    finish_average("Groove_C", "210806");
    finish_average("Groove_D", "210806");
    finish_average("Normal", "210806");
    finish_average("R1_17.9", "210806");
    finish_average("R1_18.6", "210806");
    finish_average("R1_19.3", "210806");

    return (0);
}