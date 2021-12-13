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
int average(char date[], char angle[])
{
    // 変数宣言
    int i, j, k, l;
    int datalength = 0;
    int ch = 3;
    int data_flame = 5000;
    double value[data_flame][ch];
    double ch0, ch1, ch2; // ch0:drag, ch1:lift, ch2:load-cell

    // 読み込みファイルの指定
    char filename_read[100];
    char filename_csv[100];
    char filename_dat[100];

    sprintf(filename_read,"%s/csv_drift/%s_drift.csv",  date, angle);
    sprintf(filename_csv, "%s/csv_average/%s_average.csv",   date, angle);
    sprintf(filename_dat, "%s/dat_average/%s_average.dat",   date, angle);
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

    // 計算

    // 変数の宣言

    int count = 150;
    int average_time[5];
    double sum[3];
    double average_value[5][3];
    double average_value_offset[5];
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
        printf("[%d]\t%lf\t%lf\t%lf\n", average_time[i], average_value[i][0], average_value[i][1], average_value[i][2]);
        // printf("%d\n", average_time[i]);
    }

    // ファイルへの書き込み

    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");

    for (i = 0; i < 6; i++)
    {
        fprintf(fp_csv, "%lf,%lf,%lf\n", average_value[i][0], average_value[i][1], average_value[i][2]);
        fprintf(fp_dat, "%d\t%lf\t%lf\t%lf\n", average_time[i], average_value[i][0], average_value[i][1], average_value[i][2]);
    }

    fclose(fp_csv);
    fclose(fp_dat);
}

int main()
{
    // 211208
    // average("211208", "0");
    // average("211208", "15");
    // average("211208", "30");
    // average("211208", "45");
    // average("211208", "60");
    // average("211208", "75");
    // average("211208", "90");

    // simulation
    average("simulation_data", "0");
    average("simulation_data", "15");
    average("simulation_data", "30");
    average("simulation_data", "45");
    average("simulation_data", "60");
    average("simulation_data", "75");
    average("simulation_data", "90");
    average("simulation_data", "105");
    average("simulation_data", "120");
    average("simulation_data", "135");
    average("simulation_data", "150");
    average("simulation_data", "165");
    average("simulation_data", "180");
    average("simulation_data", "195");
    average("simulation_data", "210");

    return (0);
}