/******************************************************************************
PROGRAM NAME :summarize.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ch 2
FILE *fp5, *fp6;
/*********************************   MAIN   *********************************/
int summarize(char name[], char date[])
{
    // 設定ファイルのインポート

    // 生データ
    // #include "files/raw_data.h"
    
    // 移動平均
    #include "files/moving_average.h"

    // 中央値
    // #include "files/median.h"

    // ファイルの読み込み

    fp5 = fopen(filename5, "r");
    if (filename5 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    // データの格納

    int num_d, num_l;
    double ch1, ch2;

    fscanf(fp5, "%d\t%lf\t%d\t%lf\n", &num_d, &ch1, &num_l, &ch2); // ch1:drag, ch2:lift

    fclose(fp5);

    // データの書き込み

    fp6 = fopen(filename6, "a");
    if (filename6 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    fprintf(fp6, "%d\t%lf\t%d\t%lf\t%s\n", num_d, ch1, num_l, ch2, name);
    printf("%d\t%lf\t%d\t%lf\t(%s)\n", num_d, ch1, num_l, ch2, name);

    fclose(fp6);
}

int main ()
{
    summarize("C1", "210806");
    summarize("Groove_A", "210806");
    summarize("Groove_B", "210806");
    summarize("Groove_C", "210806");
    summarize("Groove_D", "210806");
    summarize("Normal", "210806");
    summarize("R1_17.9", "210806");
    summarize("R1_18.6", "210806");
    summarize("R1_19.3", "210806");
}