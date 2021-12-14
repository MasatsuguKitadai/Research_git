/******************************************************************************
PROGRAM NAME :
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FILE *fp, *fp_dat, *fp_csv;
/*********************************   MAIN   *********************************/
int drift(char date[], char angle[])
{
 // 変数宣言
    int i, j, k, l;
    int datalength = 0;
    int ch = 3;
    int data_flame = 5000;
    double value[data_flame][ch];
    double ch0, ch1, ch2, ch3; // ch0:drag, ch1:lift, ch2:load-cell

    // 読み込みファイルの指定
    char filename_read[100];
    char filename_csv[100];
    char filename_dat[100];

    sprintf(filename_read,"result/%s/csv_reverse/%s_reverse.csv",  date, angle);
    sprintf(filename_csv, "result/%s/csv_drift/%s_drift.csv",   date, angle);
    sprintf(filename_dat, "result/%s/dat_drift/%s_drift.dat",   date, angle);
    printf("【%s】\n", angle);

    // 配列の初期化

    for (i = 0; i < data_flame; i++)
    {
        for (j = 0; j < 3; j++)
        {
            value[i][j] = 0;
        }
    }

    // printf("check\n");

    // ファイルの読み込み
    fp = fopen(filename_read, "r");
    if (filename_read == NULL)
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

    // 平均値の計算

    int count = 150;
    int average_time[5];
    double sum[3];
    double average_value[6][3];
    double offset;

    for (i = 0; i < 6; i++)
    {
        count = count + 25;

        for (j = 0; j < 3; j++)
        {
            sum[j] = 0;
        }

        for (j = count; j < count + 150 ; j++)
        {
            for (k = 0; k < 3; k++)
            {
                sum[k] = value[j][k] + sum[k];
            }
        }

        count = j;

        for (j = 0; j < 3; j++)
        {
            average_value[i][j] = sum[j] / 150;
        }

        count = count + 175;
        average_time[i] = count - 250;
        // printf("[%d]\t%lf\t%lf\t%lf\n", average_time[i], average_value[i][0], average_value[i][1], average_value[i][2]);
        // printf("%d\n", average_time[i]);
    }

    // 補正直線の計算
    double a[3], b[3];

    // 比例定数 a
    for (i = 0; i < 3; i++)
    {
        a[i] = (average_value[5][i] - average_value[0][i]) / (average_time[5] - average_time[0]);
    }

    // 切片 b
    for (i = 0; i < 3; i++)
    {
        b[i] = average_value[0][i] - a[i] * average_time[0];
    }

    // 関数 f
    for (i = 0; i < 3; i++)
    {
        printf("[%d]\tf(x) = %lf x + %lf\n", i, a[i], b[i]);
    }


    // 変数の宣言
    double f[datalength][3], c[datalength][3];

    // 配列の初期化
    for (j = 0; j < datalength; j++)
    {
        f[j][0] = 0;
        f[j][1] = 0;
        f[j][2] = 0;
    }

    // 線形補間の値の計算
    // printf("%s\n", name);
    for (j = 0; j < datalength; j++)
    {
        f[j][0] = a[0] * j + b[0];
        f[j][1] = a[1] * j + b[1];
        f[j][2] = a[2] * j + b[2];
        // printf("[%d]\t%lf\t%lf\n", j, f[j][1], f[j][2]);
    }

    // 補正値の計算
    for (j = 0; j < datalength; j++)
    {
        c[j][0] = value[j][0] - f[j][0];
        c[j][1] = value[j][1] - f[j][1];
        c[j][2] = value[j][2] - f[j][2];
        // printf("[%d]\t%lf\t%lf\n", j, c[j][1], c[j][2]);
    }

    // 書き出し
    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");

    for (j = 0; j < datalength; j++)
    {
        fprintf(fp_csv, "%lf,%lf,%lf\n", c[j][0], c[j][1], c[j][2]);
        fprintf(fp_dat, "%d\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", j, c[j][0], c[j][1], c[j][2], f[j][0], f[j][1], f[j][2]);
    }

    fclose(fp_csv);
    fclose(fp_dat);

}

int main()
{
    // 211208
    // drift("211208", "0");
    // drift("211208", "15");
    // drift("211208", "30");
    // drift("211208", "45");
    // drift("211208", "60");
    // drift("211208", "75");
    // drift("211208", "90");

    // simulation
    drift("simulation_data", "0");
    drift("simulation_data", "15");
    drift("simulation_data", "30");
    drift("simulation_data", "45");
    drift("simulation_data", "60");
    drift("simulation_data", "75");
    drift("simulation_data", "90");
    drift("simulation_data", "105");
    drift("simulation_data", "120");
    drift("simulation_data", "135");
    drift("simulation_data", "150");
    drift("simulation_data", "165");
    drift("simulation_data", "180");
    drift("simulation_data", "195");
    drift("simulation_data", "210");

    return (0);
}