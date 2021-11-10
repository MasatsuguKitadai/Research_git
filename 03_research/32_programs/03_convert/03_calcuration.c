/******************************************************************************
PROGRAM NAME : calcuration.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "files/fp.h"
#define g 9.81;
/*********************************   MAIN   *********************************/
int calcuration()
{
    // 入力ファイル名
    char filename1[100] = "../31_data/convert/force.csv";
    char filename2[100] = "../31_data/convert/x-axis.csv";
    char filename3[100] = "../31_data/convert/y-axis.csv";

    // 出力ファイル名
    char filename4[100] = "../33_result/convert/dat/x-force.dat";
    char filename5[100] = "../33_result/convert/dat/y-force.dat";
    char filename6[100] = "../33_result/convert/dat/force&line_1.dat";
    char filename7[100] = "../33_result/convert/dat/force&line_2.dat";
    char filename8[100] = "../33_result/convert/dat/formula.dat";

    // 入力ファイル名(オフセット)
    char filename9[100] = "../33_result/convert/dat/offset_211109.dat";

    // 変数の設定
    int i, j;
    double ch1, ch2, ch3, ch4;
    int datalong[3];
    double value_1[20][4];
    double value_2[20][4];
    double value_3[20][4];

    // 配列の初期化
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 4; j++)
        {
            value_1[i][j] = 0;
            value_2[i][j] = 0;
            value_3[i][j] = 0;
        }
    }

    // Model-loadcell <Drag>

    // ファイルの読み込み
    fp1 = fopen(filename1, "r");
    if (filename1 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    // printf("%s\n", filename1);
    i = 0;
    while ((fscanf(fp1, "%lf, %lf", &ch1, &ch2)) != EOF)
    {
        value_1[i][1] = ch1 / 1000 * g;
        value_1[i][2] = ch2;
        // printf("[%d]\t%lf %lf\n", i, value_1[i][1], value_1[i][2]);
        i = i + 1;
    }

    fclose(fp1);
    
    datalong[1] = i;

    // Model-loadcell <Drag>

    // ファイルの読み込み
    fp2 = fopen(filename2, "r");
    if (filename2 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    // printf("\n%s\n", filename2);
    i = 0;
    while ((fscanf(fp2, "%lf, %lf, %lf, %lf", &ch1, &ch2, &ch3, &ch4)) != EOF)
    {
        value_2[i][1] = ch1;
        value_2[i][2] = ch2;
        value_2[i][3] = ch3;
        value_2[i][4] = ch4;
        // printf("[%d]\t%lf %lf %lf %lf\n", i, value_2[i][1], value_2[i][2], value_2[i][3], value_2[i][4]);
        i = i + 1;
    }

    fclose(fp2);

    datalong[2] = i;

    // Model-loadcell <Drag>

    // ファイルの読み込み
    fp3 = fopen(filename3, "r");
    if (filename3 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    // printf("\n%s\n", filename3);
    i = 0;
    while ((fscanf(fp3, "%lf, %lf, %lf, %lf", &ch1, &ch2, &ch3, &ch4)) != EOF)
    {
        value_3[i][1] = ch1;
        value_3[i][2] = ch2;
        value_3[i][3] = ch3;
        value_3[i][4] = ch4;
        // printf("[%d]\t%lf %lf %lf %lf\n", i, value_3[i][1], value_3[i][2], value_3[i][3], value_3[i][4]);
        i = i + 1;
    }

    fclose(fp3);

    datalong[3] = i;

    // ファイルの読み込み (offset)
    fp9 = fopen(filename9, "r");
    if (filename9 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }
    
    double offset;

    fscanf(fp3, "%lf", &ch1);
    offset = ch1;
    // printf("%lf\n", offset);

    // 計算
    double a1, b1;
    double sum1, sum2, sum3, sum4;

    // 変数の初期化
    a1 = 0;
    b1 = 0;
    sum1 = 0;
    sum2 = 0;
    sum3 = 0;
    sum4 = 0;

    // 近似直線の計算
    for (i = 0; i < datalong[1]; i++)
    {
        sum1 = sum1 + value_1[i][2];
        sum2 = sum2 + value_1[i][1];
        sum3 = sum3 + (value_1[i][2] * value_1[i][2]);
        sum4 = sum4 + (value_1[i][2] * value_1[i][1]);
    }

    a1 = (datalong[1] * sum4 - sum1 * sum2) / (datalong[1] * sum3 - sum1 * sum1);
    b1 = (sum3 * sum2 - sum4 * sum1) / (datalong[1] * sum3 - sum1 * sum1);

    printf("f[x] = %lf x + %lf\t[output - force]\n", a1, b1);

    // load-cell - force 近似式の計算
    int n = 6;
    double result[n];

    for (i = 0; i < n; i++)
    {
        result[i] = a1 * (i - 1) + b1;
    }

    // datファイルへの書き込み

    fp6 = fopen(filename6, "w");

    for (i = 0; i < n; i++)
    {
        fprintf(fp6, "%d\t%lf\n", i - 1, result[i]);
    }

    fclose(fp6);

    // 荷重への換算
    double result_x[datalong[2]][2];
    double result_y[datalong[3]][2];

    // <drag>
    for (i = 0; i < datalong[2]; i++)
    {
        result_x[i][1] = value_2[i][3];
        result_x[i][2] = a1 * value_2[i][2] + b1;
        // printf("[%d]\t%lf\t%lf\n", i, result_x[i][1], result_x[i][2]);
    }

    // 近似式の作成
    double a2, b2;

    // 変数の初期化
    a2 = 0;
    b2 = 0;
    sum1 = 0;
    sum2 = 0;
    sum3 = 0;
    sum4 = 0;

    // 近似直線の計算（最小二乗法）
    for (i = 0; i < datalong[2]; i++)
    {
        sum1 = sum1 + result_x[i][1];
        sum2 = sum2 + result_x[i][2];
        sum3 = sum3 + (result_x[i][1] * result_x[i][1]);
        sum4 = sum4 + (result_x[i][1] * result_x[i][2]);
    }

    a2 = (datalong[2] * sum4 - sum1 * sum2) / (datalong[2] * sum3 - sum1 * sum1);
    b2 = (sum3 * sum2 - sum4 * sum1) / (datalong[2] * sum3 - sum1 * sum1);

    printf("f[x] = %lf x + %lf\t[input - force (drag)]\n", a2, b2);

    // datファイルの作成
    fp4 = fopen(filename4, "w");

    for (i = 0; i < datalong[2]; i++)
    {
        fprintf(fp4, "%lf\t%lf\n", result_x[i][1], result_x[i][2]);
    }

    fclose(fp4);

    // <lift>
    for (i = 0; i < datalong[3]; i++)
    {
        result_y[i][1] = value_3[i][4];
        result_y[i][2] = a1 * value_3[i][2] + b1;
        // printf("[%d]\t%lf\t%lf\n", i, result_y[i][1], result_y[i][2]);
    }

    // 近似式の作成
    double a3, b3;

    // 変数の初期化
    a3 = 0;
    b3 = 0;
    sum1 = 0;
    sum2 = 0;
    sum3 = 0;
    sum4 = 0;

    // 近似直線の計算
    for (i = 0; i < datalong[3]; i++)
    {
        sum1 = sum1 + result_y[i][1];
        sum2 = sum2 + result_y[i][2];
        sum3 = sum3 + (result_y[i][1] * result_y[i][1]);
        sum4 = sum4 + (result_y[i][1] * result_y[i][2]);
    }

    a3 = (datalong[3] * sum4 - sum1 * sum2) / (datalong[3] * sum3 - sum1 * sum1);
    b3 = (sum3 * sum2 - sum4 * sum1) / (datalong[3] * sum3 - sum1 * sum1);

    printf("f[x] = %lf x + %lf\t[input - force (lift)]\n", a3, b3);

    // datファイルの作成
    fp5 = fopen(filename5, "w");

    for (i = 0; i < datalong[3]; i++)
    {
        fprintf(fp5, "%lf\t%lf\n", result_y[i][1], result_y[i][2]);
    }

    fclose(fp5);

    // 近似直線の計算
    int count = 15;
    double formula_x[count];
    double formula_y[count];

    for (i = 0; i < count; i++)
    {
        formula_x[i] = a2 * (i - 7) + b2;
        formula_y[i] = a3 * (i - 7) + b3;
    }

    fp7 = fopen(filename7, "w");

    for (i = 0; i < count; i++)
    {
        fprintf(fp7, "%d\t%lf\t%lf\n", i - 7, formula_x[i], formula_y[i]);
    }

    fclose(fp7);

    // 近似式・係数出力

    fp8 = fopen(filename8, "w");

    fprintf(fp8, "%lf\t%lf\n", a1, b1);
    fprintf(fp8, "%lf\t%lf\n", a2, b2);
    fprintf(fp8, "%lf\t%lf\n", a3, b3);

    fclose(fp8);

    return (0);
}