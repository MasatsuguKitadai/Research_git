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
int variance(char date[])
{
    // ファイル名作成
    char filename_read[100];
    char filename_csv[100];
    char filename_dat[100];

    sprintf(filename_read, "result/%s/05_csv_summary/%s_summary.csv", date, date);
    sprintf(filename_csv, "result/%s/06_csv_evaluation/%s_evaluation.csv", date, date);
    sprintf(filename_dat, "result/%s/06_dat_evaluation/%s_evaluation.dat", date, date);

    int i = 0;
    int buf;
    int angle[24];
    double ch0, ch1, ch2;
    double value[24][3];

    fp = fopen(filename_read, "r");
    if (filename_read == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    while ((fscanf(fp, "%d, %lf, %lf, %lf", &buf, &ch0, &ch1, &ch2)) != EOF)
    {
        // printf("%d, %lf, %lf, %lf\n", buf, ch0, ch1, ch2);
        angle[i] = buf;
        value[i][0] = ch0; // drag
        value[i][1] = ch1; // lift
        value[i][2] = ch2; // sqrt
        i = i + 1;
    }

    fclose(fp);

    // 分散計算

    double variance = 0;
    double deviation = 0;
    double sum2 = 0;
    double sum[3], ave[3];

    for (i = 0; i < 3; i++)
    {
        sum[i] = 0;
        ave[i] = 0;
    }

    for (i = 0; i < 24; i++)
    {
        sum[0] = value[i][0] + sum[0];
        sum[1] = value[i][1] + sum[1];
        sum[2] = value[i][2] + sum[2];
    }

    for (i = 0; i < 3; i++)
    {
        ave[i] = sum[i] / 24;
        printf("[%d]\t%lf\n", i, ave[i]);
    }

    for (i = 0; i < 24; i++)
    {
        sum2 = value[i][2] * value[i][2] + sum2;
    }

    variance = sum2 / 24 - ave[2] * ave[2];
    deviation = sqrt(variance);

    printf("variance \t= %lf\n", variance);
    printf("deviation\t= %lf\n", deviation);

    // plot用 データファイルの書き出し

    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");

    fprintf(fp_csv, "%lf\t%lf\n", variance, deviation);
    fprintf(fp_dat, "%lf\t%lf\n", variance, deviation);

    fclose(fp_csv);
    fclose(fp_dat);
}

int main()
{
    // simulation
    variance("simulation_data");

    return (0);
}