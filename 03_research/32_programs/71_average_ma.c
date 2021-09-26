/******************************************************************************
PROGRAM NAME :average.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ch 2
#include "files/fp.h"
int range_ma = 11;
/*********************************   MAIN   *********************************/
int average(char name[], char date[])
{
#include "files/moving_average.h"

    // 補正ファイルの読み込み

    fp = fopen(filename7, "r");
    if (filename7 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }
    // データの格納

    int i = 0;
    int N = 1000;
    int num, data_long;
    double ch1, ch2, ch3, ch4;
    double value[N][ch];
    int number[N];

    // ch1:drag, ch2:lift

    while ((fscanf(fp, "%d\t%lf\t%lf\t%lf\t%lf", &num, &ch1, &ch2, &ch3, &ch4)) != EOF)
    {
        number[i] = num;
        value[i][1] = ch2;
        value[i][2] = ch4;
        // printf("%d\t%lf\t%lf\n", number[i], value[i][1], value[i][2]);
        i = i + 1;
    }

    fclose(fp);

    data_long = i;

    int start_num, finish_num, average_num;
    double buf1, buf2, buf3, buf4;

    start_num = 0;
    finish_num = 0;

    // 起動時刻の読み込み
    
    fp = fopen(filename5, "r");
    if (filename5 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }
    // データの格納

    fscanf(fp, "%d\t%lf\t%lf\t%lf\t%lf\t%d", &start_num, &buf1, &buf2, &buf3, &buf4, &average_num);

    fclose(fp);

    // 停止時刻の読み込み
    
    fp = fopen(filename6, "r");
    if (filename6 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }
    // データの格納

    fscanf(fp, "%d\t%lf\t%lf\t%lf\t%lf\t%d", &finish_num, &buf1, &buf2, &buf3, &buf4, &average_num);

    fclose(fp);

    // 計算

    // (1) 基準の平均値

    // 測定開始直後・終了直前のスキップ
    int skip1 = 30;

    double sum_zero[2];
    double ave_zero[2];
    int j = 0;

    sum_zero[1] = 0;
    sum_zero[2] = 0;
    ave_zero[1] = 0;
    ave_zero[2] = 0;

    for (i = skip1; i < start_num; i++)
    {
        sum_zero[1] = sum_zero[1] + value[i][1];
        sum_zero[2] = sum_zero[2] + value[i][2];
        j  = j + 1;
    }

    for (i = finish_num; i < data_long - skip1; i++)
    {
        sum_zero[1] = sum_zero[1] + value[i][1];
        sum_zero[2] = sum_zero[2] + value[i][2];
        j = j + 1;
    }
    
    ave_zero[1] = sum_zero[1] / j;
    ave_zero[2] = sum_zero[2] / j;

    // (2) 出力の平均値
    int skip2 = 60;

    double sum_output[2];
    double ave_output[2];
    int k = 0;

    sum_output[1] = 0;
    sum_output[2] = 0;
    ave_output[1] = 0;
    ave_output[2] = 0;

    for (i = start_num + skip2; i < finish_num - skip2; i++)
    {
        sum_output[1] = sum_output[1] + value[i][1];
        sum_output[2] = sum_output[2] + value[i][2];
        k = k + 1;
    }

    ave_output[1] = sum_output[1] / k;
    ave_output[2] = sum_output[2] / k;

    // 書き出し
    printf("ZERO\t[drag] %lf \t%lf \t[lift] %lf \t%lf \t[%s]\n", ave_zero[1], ave_output[1], ave_zero[2], ave_output[2], name);
}

int main ()
{
    // 2021/8/6
    average("C1", "210806");
    average("Groove_A", "210806");
    average("Groove_B", "210806");
    average("Groove_C", "210806");
    average("Groove_D", "210806");
    average("Normal", "210806");
    average("R1_17.9", "210806");
    average("R1_18.6", "210806");
    average("R1_19.3", "210806");
}