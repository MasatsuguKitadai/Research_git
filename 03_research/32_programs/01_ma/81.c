/******************************************************************************
PROGRAM NAME : calibration.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
// 移動平均 範囲
int range_ma = 11;

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "files/fp.h"
/*********************************   MAIN   *********************************/
int convert(char name[], char date[])
{
#include "files/moving_average.h"

    int i, num;
    double ch1, ch2, ch3, ch4;
    double value[4];

    // ファイルの読み込み
    fp8 = fopen(filename8, "r");
    if (filename8 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    fscanf(fp8, "%d\t%lf\t%lf\t%lf\t%lf", &num, &ch1, &ch2, &ch3, &ch4);

    value[0] = ch1;
    value[1] = ch2;
    value[2] = ch3;
    value[3] = ch4;

    printf("%lf\t%lf\t%lf\t%lf\t[%s]\n", value[0], value[1], value[2], value[3], name);

    fclose(fp8);

    // 近似式の係数の読み込み
    char filename[100] = "..//..//33_result//convert//dat//formula.dat";
    double a[3], b[3];

    fp = fopen(filename, "r");
    if (filename == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    i = 0;

    while ((fscanf(fp, "%lf\t%lf", &ch1, &ch2)) != EOF)
    {
        a[i] = ch1;
        b[i] = ch2;
        // printf("%lf\t%lf\n", a[i], b[i]);
        i = i + 1;
    }

    fclose(fp);

    double convert[4];

    convert[0] = value[0];
    convert[1] = a[1] * value[1];
    convert[2] = value[2];
    convert[3] = a[2] * value[3];

    return (0);
}

int main()
{
    convert("C1", "210806");
    convert("Groove_A", "210806");
    convert("Groove_B", "210806");
    convert("Groove_C", "210806");
    convert("Groove_D", "210806");
    convert("Normal", "210806");
    convert("R1_17.9", "210806");
    convert("R1_18.6", "210806");
    convert("R1_19.3", "210806");
}