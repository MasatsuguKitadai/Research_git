/******************************************************************************
PROGRAM NAME : 
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FILE *fp;

// 読み込みファイルの指定
char filename_1[100] = "test_data/0_test_reverse.CSV";
char filename_3[100] = "test_result/0_test_result_changetime_reverse.CSV";

/*********************************   MAIN   *********************************/
int main()
{
    // 変数宣言
    int i, j, k, l;
    int datalength = 0;
    int ch = 3;
    double value[1000][ch];
    double ch0, ch1, ch2; // ch0:drag, ch1:lift, ch2:load-cell

    // 配列の初期化

    for (i = 0; i < 1000; i++)
    {
        for (j = 0; j < 3; j++)
        {
            value[i][j] = 0;
        }
    }

    printf("check");

    // ファイルの読み込み
    fp = fopen(filename_1, "r");
    if (filename_1 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    i = 0;

    while ((fscanf(fp, "%lf, %lf, %lf", &ch0, &ch1, &ch2)) != EOF)
    {
        // printf("%lf, %lf, %lf\n", ch0, ch1, ch2);
        value[i][0] = ch0;
        value[i][1] = ch1;
        value[i][2] = ch2;
        i = i + 1;
    }

    fclose(fp);

    datalength = i;
    printf("datalengh = %d\n", datalength);

    // 計算

    // (1) 変化点の特定

    // 変数の宣言

    int change_time[4];
    double change_value[4];

    int x, y, z;
    double w;
    int range_1 = 30;
    int range_2 = 10;
    int range = datalength - range_1;
    double top, bottom, sum1, sum2, ave1, ave2;
    double x1[range_1], x2[range_2];
    double gap = 0.03;

    l = 0;

    for (i = 20; i < range; i++)
    {
        // 配列の初期化

        sum1 = 0;
        ave1 = 0;
        sum2 = 0;
        ave2 = 0;

        // 指定された範囲の配列を作成
        for (j = 0; j < range_1; j++)
        {
            x1[j] = value[i + j][2];
            // printf("[%d]\t%lf\n", j, x1[j]);
        }

        for (k = 1; k < range_2 + 1; k++)
        {
            x2[k] = value[i + range_1 + k][2];
            // printf("[%d]\t%lf\n", k, x2[k]);
        }

        // 並び替え (小さい順)
        for (x = 0; x < range_1; x++)
        {
            // drag
            y = x;
            for (z = x; z < range_1; z++)
            {
                if (x1[z] < x1[y])
                {
                    y = z;
                }
            }
            if (x < y)
            {
                w = x1[x];
                x1[x] = x1[y];
                x1[y] = w;
            }
        }

        // 範囲の最大値・最小値の特定
        bottom = x1[0];
        top = x1[range_1 - 1];

        // 平均値の算出 (前部)
        for (j = 0; j < range_1; j++)
        {
            sum1 = sum1 + x1[j];
        }

        ave1 = sum1 / range_1;

        // 平均値の算出 (後部)
        for (k = 0; k < range_2; k++)
        {
            sum2 = sum2 + x2[k];
        }

        ave2 = sum2 / range_2;

        // 比較

        if (ave2 > top + gap)
        {
            change_time[l] = i + range_1;
            change_value[l] = value[change_time[l]][2];
            printf("%d\t%lf\n", change_time[l], change_value[l]);
            i = i + 20;
            l = l + 1;
        }

    }

    fp = fopen(filename_3, "w");

    for (i = 0; i < 4; i++)
    {
        fprintf(fp, "%d,%lf\n", change_time[i], change_value[i]);
    }

    fclose(fp);
}