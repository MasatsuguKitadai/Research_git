/******************************************************************************
PROGRAM NAME :graph.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ch 2
const char *read_file = "../../31_data/210806/Normal.CSV";
FILE *fp1, *fp2;
/*********************************   graph   *********************************/
int graph(char filename1[], char filename2[])
{
    //  入力ファイル
    if ((fp1 = fopen(filename1, "r")) == NULL)
    {
        printf("FILE1 not open\n");
        return -1;
    }

    // 出力ファイル
    if ((fp2 = fopen(filename2, "w")) == NULL)
    {
        printf("FILE2 not open\n");
        return -1;
    }

    // データの読み込み

    int i, j, N = 1000;
    double ch1, ch2;
    double value[N][ch];

    while ((fscanf(fp1, "%lf, %lf", &ch1, &ch2)) != EOF)
    {
        value[i][1] = ch1;
        value[i][2] = ch2;
        printf("[%d] %lf %lf\n", i, value[i][1], value[i][2]);
        i = i + 1;
    }

    // gnuplot

    if ((gp = popen("gnuplot", "w")) == NULL)
    {
        printf("gnuplot is not here!\n");
        exit(0); // gnuplotが無い場合、異常ある場合は終了
    }

    return 0;
}