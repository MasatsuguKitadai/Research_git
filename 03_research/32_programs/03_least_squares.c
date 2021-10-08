/******************************************************************************
PROGRAM NAME : calibration.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "files/fp.h"
#define g 9.81;
/*********************************   MAIN   *********************************/
int main()
{
    // ファイル名の指定
    char filename1[100] = "../31_data/calibration/dat/load.dat";
    char filename2[100] = "../31_data/calibration/dat/load_least-squares.dat";

    // 変数の設定
    int i, j;
    int datalong;
    double ch1, ch2;
    double value[10][2];

    // 配列の初期化
    for (i = 0; i < 10; i++)
    {
        for ( j = 0; j < 2; j++)
        {
            value[i][j] = 0;
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
    while ((fscanf(fp1, "%lf\t%lf", &ch1, &ch2)) != EOF)
    {
        // fscanf(fp1, "%lf, %lf, %lf, %lf", &ch1, &ch2, &ch3, &ch4);
        value[i][1] = ch1;
        value[i][2] = ch2;
        // printf("[%d]\t%lf %lf\n", i, value_1[i][1], value_1[i][2]);
        i = i + 1;
    }

    fclose(fp1);

    datalong = i;

    // 計算
    double a , b;
    double sum1, sum2, sum3, sum4;

    // 変数の初期化
    a = 0;
    b = 0;
    sum1 = 0;
    sum2 = 0;
    sum3 = 0;
    sum4 = 0;
    
    // それぞれの合計の計算
    for ( i = 0; i < datalong; i++)
    {
        sum1 = sum1 + value[i][1];
        sum2 = sum2 + value[i][2];
        sum3 = sum3 + (value[i][1] * value[i][1]);
        sum4 = sum4 + (value[i][1] * value[i][2]);
    }

    a = (datalong * sum4 - sum1 * sum2)/(datalong * sum3 - sum1 * sum1);
    b = (sum3 * sum2 - sum4 * sum1)/(datalong * sum3 - sum1 * sum1);
    
    printf("f[x] = %lf x + %lf\n", a, b);

    // 範囲内のデータ計算

    double n[datalong], result[datalong];

    for (i = 0; i < datalong; i++)
    {
        n[i] = 0.05 * i - 0.05;
        result[i] = a * n[i] + b;
    }
    

    // データの書き出し
    fp2 = fopen(filename2, "w");

    for (i = 0; i < datalong; i++)
    {
        fprintf(fp2, "%lf\t%lf\n",  n[i], result[i]);
    }

    fclose(fp2);

    return (0);
}