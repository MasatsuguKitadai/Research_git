/******************************************************************************
PROGRAM NAME :
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/

#include "head.h"

/*********************************   MAIN   *********************************/
int Evaluation(char date[], int split)
{
    /*****************************************************************************/

    // ディレクトリの作成
    char directoryname[100];
    char directoryname_dat[100];
    char directoryname_csv[100];

    /*****************************************************************************/

    // 元ディレクトリの作成
    sprintf(directoryname, "../Result/%s/070_Evaluation", date);

    mkdir(directoryname, mode);

    /*****************************************************************************/

    sprintf(directoryname_dat, "../Result/%s/070_Evaluation/dat", date);
    sprintf(directoryname_csv, "../Result/%s/070_Evaluation/csv", date);

    mkdir(directoryname_dat, mode);
    mkdir(directoryname_csv, mode);

    /*****************************************************************************/

    // filename
    char filename_read[100];
    char filename_csv[100];
    char filename_dat[100];

    sprintf(filename_read, "../Result/%s/061_Summary/csv/Summary.csv", date);
    sprintf(filename_csv, "../Result/%s/070_Evaluation/csv/Evaluation.csv", date);
    sprintf(filename_dat, "../Result/%s/070_Evaluation/dat/Evaluation.dat", date);

    /*****************************************************************************/

    int i = 0;
    double buf;
    int angle[split];
    double ch0, ch1, ch2;
    double value[split][3];

    fp = fopen(filename_read, "r");
    if (fp == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    while ((fscanf(fp, "%lf, %lf, %lf, %lf", &buf, &ch0, &ch1, &ch2)) != EOF)
    {
        // printf("%d, %.3f, %.3f, %.3f\n", buf, ch0, ch1, ch2);
        angle[i] = buf;
        value[i][0] = ch0; // drag
        value[i][1] = ch1; // lift
        value[i][2] = ch2; // sqrt
        i = i + 1;
    }

    fclose(fp);

    // 分散計算

    long double variance = 0;
    double deviation = 0;
    double sum2 = 0;
    double sum[3], ave[3];

    for (i = 0; i < 3; i++)
    {
        sum[i] = 0;
        ave[i] = 0;
    }

    for (i = 0; i < split; i++)
    {
        sum[0] = value[i][0] + sum[0];
        sum[1] = value[i][1] + sum[1];
        sum[2] = value[i][2] + sum[2];
    }

    for (i = 0; i < 3; i++)
    {
        ave[i] = sum[i] / split;
        // printf("[%d]\t%.3f\n", i, ave[i]);
    }

    for (i = 0; i < split; i++)
    {
        sum2 = value[i][2] * value[i][2] + sum2;
    }

    variance = sum2 / split - ave[2] * ave[2];
    deviation = sqrt(variance);

    printf("variance \t= %Lf\n", variance);
    printf("deviation\t= %lf\n\n", deviation);

    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");

    fprintf(fp_csv, "%Lf\t%lf\n", variance, deviation);
    fprintf(fp_dat, "%Lf\t%lf\n", variance, deviation);

    fclose(fp_csv);
    fclose(fp_dat);

    printf("07\t\tsuccess\n");
}

int main()
{
    // simulation
    Evaluation("1", 24);

    return (0);
}