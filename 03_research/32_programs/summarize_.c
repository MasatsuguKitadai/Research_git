/******************************************************************************
PROGRAM NAME :summarize.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ch 2
char filename1[100];
char filename2[100];
FILE *fp1;
/*********************************   MAIN   *********************************/
int read(char name[], char number[])
{
    // 設定ファイルのインポート

    // 生データ
    // #include "files/raw_data.h"
    
    // 移動平均
    #include "files/moving_average.h"

    // 中央値
    // #include "files/median.h"

    // ファイルの読み込み

    fp1 = fopen(filename1, "r");
    if (filename1 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    // データの格納

    int num_d, num_l;
    double ch1, ch2;

    fscanf(fp1, "%d\t%lf\t%d\t%lf\n", &num_d, &ch1, &num_l, &ch2) // ch1:drag, ch2:lift
    
    fclose(fp1);

    // データの書き込み


}

// int main ()
// {
//     // test
//     read("..//..//33_result//210806//raw_data//dat//C1.dat");
// }