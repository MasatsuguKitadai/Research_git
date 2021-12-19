/******************************************************************************
PROGRAM NAME :
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>

FILE *fp, *fp_dat, *fp_csv, *gp;
/*********************************   MAIN   *********************************/
int evaluation(char date[])
{
    /*****************************************************************************/
    // ディレクトリの作成
    char directoryname_dat[100];
    char directoryname_csv[100];

    sprintf(directoryname_dat, "../result/%s/dat/06_evaluation", date);
    sprintf(directoryname_csv, "../result/%s/csv/06_evaluation", date);

    mkdir(directoryname_dat, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_csv, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    /*****************************************************************************/

    // filename
    char filename_read[100];
    char filename_csv[100];
    char filename_dat[100];

    sprintf(filename_read, "../result/%s/csv/05-1_summary/05-1.csv", date);
    sprintf(filename_csv, "../result/%s/csv/06_evaluation/06.csv", date);
    sprintf(filename_dat, "../result/%s/dat/06_evaluation/06.dat", date);

    /*****************************************************************************/

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

// int main()
// {
//     // simulation
//     evaluation("testdata");

//     return (0);
// }