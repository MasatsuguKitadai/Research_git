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
    char filename1[100] = "../31_data/calibration/force.csv";
    char filename2[100] = "../31_data/calibration/x-axis.csv";
    char filename3[100] = "../31_data/calibration/y-axis.csv";

    char filename4[100] = "../33_result/calibration/dat/force.dat";
    char filename5[100] = "../33_result/calibration/dat/x-axis.dat";
    char filename6[100] = "../33_result/calibration/dat/y-axis.dat";

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
        // fscanf(fp1, "%lf, %lf, %lf, %lf", &ch1, &ch2, &ch3, &ch4);
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
        // fscanf(fp1, "%lf, %lf, %lf, %lf", &ch1, &ch2, &ch3, &ch4);
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
        // fscanf(fp1, "%lf, %lf, %lf, %lf", &ch1, &ch2, &ch3, &ch4);
        value_3[i][1] = ch1;
        value_3[i][2] = ch2;
        value_3[i][3] = ch3;
        value_3[i][4] = ch4;
        // printf("[%d]\t%lf %lf %lf %lf\n", i, value_3[i][1], value_3[i][2], value_3[i][3], value_3[i][4]);
        i = i + 1;
    }

    fclose(fp3);
    datalong[3] = i;

    // datファイルの作成

    fp4 = fopen(filename4, "w");

    for (i = 0; i < datalong[1]; i++)
    {
        fprintf(fp4, "%lf\t%lf\n", value_1[i][1], value_1[i][2]);
    }

    fclose(fp4);

    fp5 = fopen(filename5, "w");

    for (i = 0; i < datalong[2]; i++)
    {
        fprintf(fp5, "%lf\t%lf\t%lf\t%lf\n", value_2[i][1], value_2[i][2], value_2[i][3], value_2[i][4]);
    }

    fclose(fp5);

    fp6 = fopen(filename6, "w");

    for (i = 0; i < datalong[3]; i++)
    {
        fprintf(fp6, "%lf\t%lf\t%lf\t%lf\n", value_3[i][1], value_3[i][2], value_3[i][3], value_3[i][4]);
    }

    fclose(fp6);

    return (0);
}