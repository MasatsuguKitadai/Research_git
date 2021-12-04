/******************************************************************************
PROGRAM NAME :
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FILE *fp;
/*********************************   MAIN   *********************************/
int change(char angle[])
{
    // 変数宣言
    int i, j, k, l;
    int datalength = 0;
    int ch = 3;
    double value[1000][ch];
    double ch0, ch1, ch2; // ch0:drag, ch1:lift, ch2:load-cell

    // 読み込みファイルの指定
    char filename_1[100];
    char filename_2[100];

    sprintf(filename_1, "data_reverse/%s_reverse.CSV", angle);
    sprintf(filename_2, "result/%s_change.CSV", angle);

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

    int count;
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

    double result_sum[3];
    double result_ave[3];

    // 配列の初期化

    l = 0;

    for (count = 20; count < range; count++)
    {
        // 配列の初期化

        sum1 = 0;
        ave1 = 0;
        sum2 = 0;
        ave2 = 0;

        // 指定された範囲の配列を作成
        for (i = 0; i < range_1; i++)
        {
            x1[i] = value[count + i][2];
            // printf("[%d]\t%lf\n", i, x1[i]);
        }

        for (j = 1; j < range_2 + 1; j++)
        {
            x2[j] = value[count + range_1 + j][2];
            // printf("[%d]\t%lf\n", j, x2[j]);
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
        for (i = 0; i < range_1; i++)
        {
            sum1 = sum1 + x1[i];
        }

        ave1 = sum1 / range_1;

        // 平均値の算出 (後部)
        for (j = 0; j < range_2; j++)
        {
            sum2 = sum2 + x2[j];
        }

        ave2 = sum2 / range_2;

        // 比較

        if (ave2 > top + gap)
        {
            change_time[k] = count + range_1;
            change_value[k] = value[change_time[k]][2];
            printf("starttime = %d\n", change_time[k]);
            count = change_time[k];
            k = k + 1;


            for (i = 0; i < 3; i++)
            {
                result_sum[i] = 0;
                result_ave[i] = 0;
            }

            // (3) 平均値の計算
            for ( i = 0; i < 3; i++)
            {
                for (j = count - 10; j < count; j++)
                {
                    result_sum[i] = result_sum[i] + value[j][i];
                }

                result_ave[i] = result_sum[i] / 10;
                printf("[%d]\t%lf\n", i, result_ave[i]);
            }
            printf("\n");
        }
    }

    fp = fopen(filename_2, "w");

    for (i = 0; i < 4; i++)
    {
        fprintf(fp, "%d,%lf\n", change_time[i], change_value[i]);
    }

    fclose(fp);
}

int main()
{
    change("0");
    change("30");
    change("60");
    change("90");
    change("120");
    change("150");
    change("180");
    change("210");
    change("240");
    change("270");
    change("300");
    change("330");

    return (0);
}