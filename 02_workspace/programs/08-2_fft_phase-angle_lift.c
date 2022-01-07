/******************************************************************************
PROGRAM NAME :
AUTHER  : masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>

FILE *fp, *fp_csv, *fp_dat;

// 円周率の定義
// double pi = 4 * atan(1.0);

char filename_read[100];
char filename_dat[100];
char filename_csv[100];

/*********************************   MAIN   *********************************/

int phase_angle_lift(char date[])
{
    /*****************************************************************************/
    // ディレクトリの作成
    char directoryname_dat[100];
    char directoryname_csv[100];

    sprintf(directoryname_dat, "../result/%s/dat/08-2_phase-angle_lift", date);
    sprintf(directoryname_csv, "../result/%s/csv/08-2_phase-angle_lift", date);

    mkdir(directoryname_dat, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_csv, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    // ファイルの指定
    char filename_read[100];
    char filename_csv[100];
    char filename_dat[100];

    sprintf(filename_read, "../result/%s/csv/07-2_fft-lift/07-2.csv", date);
    sprintf(filename_csv, "../result/%s/csv/08-2_phase-angle_lift/08-2.csv", date);
    sprintf(filename_dat, "../result/%s/dat/08-2_phase-angle_lift/08-2.dat", date);

    /*****************************************************************************/

    int i;
    int buf;
    double ch0, ch1, ch2;
    double value[100][4];

    fp = fopen(filename_read, "r");

    if (fp == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    i = 0;

    while ((fscanf(fp, "%d, %lf, %lf, %lf", &buf, &ch0, &ch1, &ch2)) != EOF)
    {
        // printf("[%d]\t%.3f\t%.3f\t%.3f\n", buf, ch0, ch1, ch2);
        value[i][0] = buf;
        value[i][1] = ch0;
        value[i][2] = ch1;
        value[i][3] = ch2;
        i = i + 1;
    }

    fclose(fp);

    // printf("\n");

    // 計算

    double gradient;
    double radian = 0;
    double degree = 0;

    gradient = value[1][3] / value[1][2];
    radian = atan2(value[1][3], value[1][2]);
    degree = 180 * radian / pi;

    if (degree == -90)
    {
        degree = 90;
    }
    else if (degree == -180)
    {
        degree = 180;
    }

    printf("[LIFT]\n");
    printf("Im/Re =\t%.3f\n", gradient);
    printf("angle(1) =\t%.3f\t[deg]\n\n", degree);
    printf("angle(2) =\t%.3f\t[rad]\n\n", radian);

    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");

    fprintf(fp_csv, "%lf,%lf\n", radian, degree);
    fprintf(fp_dat, "%lf\t%lf\n", radian, degree);

    fclose(fp_csv);
    fclose(fp_dat);

    printf("08-2\t\tsuccess\n");
}

// int main()
// {
//     phase_angle_lift("test-fft");
//     return (0);
// }