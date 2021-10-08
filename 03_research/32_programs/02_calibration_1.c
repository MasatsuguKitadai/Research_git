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
    // char filename1[100] = "../31_data/calibration_1/lift_1.csv";
    // char filename2[100] = "../31_data/calibration_1/lift_2.csv";
    // char filename3[100] = "../31_data/calibration_1/lift_3.csv";

    // 変数の設定
    int i = 0;
    double ch1, ch2, ch3, ch4;
    double value_1[10][4];

    // ファイルの読み込み
    fp = fopen(filename1, "r");
    if (filename1 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    for (i = 0; i < 10; i++)
    // while ((fscanf(fp, "%lf, %lf, %lf, %lf", &ch1, &ch2, &ch3, &ch4)) != EOF)
    {
        fscanf(fp1, "%lf, %lf, %lf, %lf", &ch1, &ch2, &ch3, &ch4);
        value_1[i][1] = ch1;
        value_1[i][2] = ch2;
        value_1[i][3] = ch3;
        value_1[i][4] = ch4;
        printf("[%d]\t%lf %lf %lf %lf\n", i, value_1[i][1], value_1[i][2], value_1[i][3], value_1[i][4]);
        i = i + 1;
    }

    fclose(fp);
}