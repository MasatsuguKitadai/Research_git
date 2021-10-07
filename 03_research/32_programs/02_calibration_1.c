/******************************************************************************
PROGRAM NAME : calibration_1.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "files/fp.h"
/*********************************   MAIN   *********************************/
int main()
{
    // ファイル名の指定
    char filename1[100] = "../31_data/calibration_1/drag_1.csv";
    char filename2[100] = "../31_data/calibration_1/drag_2.csv";
    char filename3[100] = "../31_data/calibration_1/drag_3.csv";

    // 変数の設定
    int i = 0;
    double ch1, ch2, ch3, ch4;
    double value_1[4][100];

    // ファイルの読み込み
    fp1 = fopen(filename1, "r");
    if (filename1 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    while ((fscanf(fp1, "%lf,%lf,%lf,%lf", &ch1, &ch2, &ch3, &ch4)) != EOF)
    {
        value_1[1][i] = ch1;
        value_1[2][i] = ch2;
        value_1[3][i] = ch3;
        value_1[4][i] = ch4;
        printf("[%d] %lf %lf %lf %lf\n", i, value_1[1][i], value_1[2][i], value_1[3][i], value_1[4][i]);
        i = i + 1;
    }

    fclose(fp1);
}