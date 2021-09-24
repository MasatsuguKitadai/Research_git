/******************************************************************************
PROGRAM NAME : lerp.c
AUTHER  : masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "files/fp.h"
/*********************************   MAIN   *********************************/
int lerp(char name[], char date[])
{
#include "files/file.h"

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
        value[i][1] = ch1;
        value[i][2] = ch2;
        i = i + 1;
    }

    fclose(fp1);

    data_long = i;

    // 変数の宣言
    int start_num, finish_num, ave_num[2];
    double start_value[2], start_ave[2], finish_value[2], finish_ave[2];

    // ファイルの読み込み (開始点)
    fp5 = fopen(filename5, "r");
    if (filename5 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    fscanf(fp5, "%d\t%lf\t%lf\t%lf\t%lf\t%d", &start_num, &start_value[1], &start_ave[1], &start_value[2], &start_ave[2], &ave_num[1]);

    fclose(fp5);

    // ファイルの読み込み (開始点)
    fp6 = fopen(filename6, "r");
    if (filename6 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    fscanf(fp6, "%d\t%lf\t%lf\t%lf\t%lf\t%d", &finish_num, &finish_value[1], &finish_ave[1], &finish_value[2], &finish_ave[2], &ave_num[2]);

    fclose(fp6);

    // printf("%d\t%lf\t%lf\t%d\t%lf\t%lf\t[%s start]\n", start_num[1], start_value[1], start_ave[1], start_num[2], start_value[2], start_ave[2], name);
    // printf("%d\t%lf\t%lf\t%d\t%lf\t%lf\t[%s finish]\n", finish_num[1], finish_value[1], finish_ave[1], finish_num[2], finish_value[2], finish_ave[2], name);

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

// int main()
// {
//     // 2021/8/6
//     lerp("C1", "210806");
//     lerp("Groove_A", "210806");
//     lerp("Groove_B", "210806");
//     lerp("Groove_C", "210806");
//     lerp("Groove_D", "210806");
//     lerp("Normal", "210806");
//     lerp("R1_17.9", "210806");
//     lerp("R1_18.6", "210806");
//     lerp("R1_19.3", "210806");

//     return (0);
// }