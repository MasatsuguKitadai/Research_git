
/******************************************************************************
PROGRAM NAME : 07_fft.c
AUTHER  : masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "files/fp.h"

/*********************************   MAIN   *********************************/

#include "files/fft.h"

int fft(char name[], char date[])
{
#include "files/raw_data.h"

    // ファイルの読み込み (dat データ)

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
    double value[N][2];
    int number[N];

    // ch1:drag, ch2:lift

    while ((fscanf(fp1, "%d\t%lf\t%lf", &num, &ch1, &ch2)) != EOF)
    {
        number[i] = num;
        value[i][0] = ch1;
        value[i][1] = ch2;
        i = i + 1;
    }

    fclose(fp1);

    data_long = i;

    // 変数の宣言
    int start_num, finish_num, ave_num[2];
    double start_value[2], start_ave[2], finish_value[2], finish_ave[2];

    // ファイルの読み込み (開始点)
    fp13 = fopen(filename13, "r");
    if (filename13 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    fscanf(fp13, "%d\t%lf\t%lf\t%lf\t%lf\t%d", &start_num, &start_value[0], &start_ave[0], &start_value[1], &start_ave[1], &ave_num[0]);

    fclose(fp13);

    printf("%d\t%lf\t%lf\t%lf\t%lf\t[%s start]\n", start_num, start_value[0], start_ave[0], start_value[1], start_ave[1], name);

    // 計算

    // fftの範囲指定

    int range_1, range_2;

    range_1 = 128;
    range_2 = 128;

    int start_1, start_2;

    start_1 = start_num - (range_1 + 30);
    start_2 = start_num + 60;

    int j;

    double pw, fq, dt;
    dt = 1;

    // range_1

    double value_drag_1[range_1], value_lift_1[range_1];
    double value_drag_i_1[range_1], value_lift_i_1[range_1];

    j = 0;
    for (i = start_1; i < start_1 + range_1; i++)
    {
        value_drag_1[j] = value[i][0];
        value_lift_1[j] = value[i][1];
        value_drag_i_1[j] = 0;
        value_lift_i_1[j] = 0;
        // printf("[%d]\t%lf\t%lf\n", j, value_drag_1[j], value_lift_1[j]);
        j = j + 1;
    }

    S_fft(value_drag_1, value_drag_i_1, range_1, 1);

    // FFT - drag : range_1

    fp9 = fopen(filename9, "w");

    for (i = 0; i < range_1; i++)
    {
        // printf("[%d]\t%lf\t%lf\n", i, value_drag_1[i], value_drag_i_1[i]);
        pw = sqrt(value_drag_1[i] * value_drag_1[i] + value_drag_i_1[i] * value_drag_i_1[i]); /* パワースペクトル  */
        fq = (double)i / (dt * (double)range_1);
        fprintf(fp9, "%lf\t%lf\n", pw, fq);
        // printf("[%d]\t%lf\t%lf\n", i, pw, fq);
    }

    fclose(fp9);

    // FFT - lift : range_1

    S_fft(value_lift_1, value_lift_i_1, range_1, 1);

    fp11 = fopen(filename11, "w");

    for (i = 0; i < range_1; i++)
    {
        pw = sqrt(value_lift_1[i] * value_lift_1[i] + value_lift_i_1[i] * value_lift_i_1[i]); /* パワースペクトル  */
        fq = (double)i / (dt * (double)range_1);
        fprintf(fp11, "%lf\t%lf\n", pw, fq);
        // printf("[%d]\t%lf\t%lf\n", i, pw, fq);
    }

    fclose(fp11);

    // range_2

    double value_drag_2[range_2], value_lift_2[range_2];
    double value_drag_i_2[range_2], value_lift_i_2[range_2];

    j = 0;
    for (i = start_2; i < start_2 + range_2; i++)
    {
        value_drag_2[j] = value[i][0];
        value_lift_2[j] = value[i][1];
        value_drag_i_2[j] = 0;
        value_lift_i_2[j] = 0;
        // printf("[%d]\t%lf\t%lf\n", j, value_drag_2[j], value_lift_2[j]);
        j = j + 1;
    }

    // FFT - drag : range_2

    S_fft(value_drag_2, value_drag_i_2, range_2, 1);

    fp10 = fopen(filename10, "w");

    for (i = 0; i < range_2; i++)
    {
        // printf("[%d]\t%lf\t%lf\n", i, value_drag_2[i], value_drag_i_2[i]);
        pw = sqrt(value_drag_2[i] * value_drag_2[i] + value_drag_i_2[i] * value_drag_i_2[i]); /* パワースペクトル  */
        fq = (double)i / (dt * (double)range_2);
        fprintf(fp10, "%lf\t%lf\n", pw, fq);
        // printf("[%d]\t%lf\t%lf\n", i, pw, fq);
    }

    fclose(fp10);

    // FFT - lift : range_2

    S_fft(value_lift_2, value_lift_i_2, range_2, 1);

    fp12 = fopen(filename12, "w");

    for (i = 0; i < range_2; i++)
    {
        pw = sqrt(value_lift_2[i] * value_lift_2[i] + value_lift_i_2[i] * value_lift_i_2[i]); /* パワースペクトル  */
        fq = (double)i / (dt * (double)range_2);
        fprintf(fp12, "%lf\t%lf\n", pw, fq);
        // printf("[%d]\t%lf\t%lf\n", i, pw, fq);
    }

    fclose(fp12);
}

int main()
{
    // 2021/8/6
    fft("C1", "210806");
    fft("Groove_A", "210806");
    fft("Groove_B", "210806");
    fft("Groove_C", "210806");
    fft("Groove_D", "210806");
    fft("Normal", "210806");
    fft("R1_17.9", "210806");
    fft("R1_18.6", "210806");
    fft("R1_19.3", "210806");

    return (0);
}