/******************************************************************************
PROGRAM NAME : sin_wave_maker.c
AUTHER  : masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>

FILE *fp, *fp_csv, *fp_dat;

// 円周率の定義
// #define pi 4 * atan(1.0)

/*********************************   MAIN   *********************************/
int simulater(char date[], int split, int Phi_1, int Phi_2)
{
    // ディレクトリの作成
    char directoryname_dat[100];
    char directoryname_csv[100];
    char directoryname_plot[100];

    sprintf(directoryname_dat, "../result/%s/dat", date);
    sprintf(directoryname_csv, "../result/%s/csv", date);
    sprintf(directoryname_plot, "../result/%s/plot", date);

    mkdir(directoryname_dat, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_csv, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_plot, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    /*****************************************************************************/

    sprintf(directoryname_dat, "../result/%s/dat/05-1_summary", date);
    sprintf(directoryname_csv, "../result/%s/csv/05-1_summary", date);

    mkdir(directoryname_dat, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_csv, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    /*****************************************************************************/

    sprintf(directoryname_dat, "../result/%s/dat/05-2_summary-average", date);
    sprintf(directoryname_csv, "../result/%s/csv/05-2_summary-average", date);

    mkdir(directoryname_dat, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_csv, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    /*****************************************************************************/
    // ファイルの指定
    char filename_csv_1[100];
    char filename_csv_2[100];
    char filename_dat_1[100];
    char filename_dat_2[100];

    sprintf(filename_csv_1, "../result/%s/csv/05-1_summary/05-1.csv", date);
    sprintf(filename_dat_1, "../result/%s/dat/05-1_summary/05-1.dat", date);

    sprintf(filename_csv_2, "../result/%s/csv/05-2_summary-average/05-2.csv", date);
    sprintf(filename_dat_2, "../result/%s/dat/05-2_summary-average/05-2.dat", date);

    /*****************************************************************************/

    int i = 0;
    int j = 0;
    double angle, buf;

    // sin波の配列
    double wave_net[3600];
    double wave_drag[3600];
    double wave_lift[3600];

    double sum[3];
    double ave[3];

    for (i = 0; i < 3; i++)
    {
        sum[i] = 0;
        ave[i] = 0;
    }

    // 正弦波 drag (位相 π ズレ)
    // printf("Drag\n");
    for (i = 0; i < 3600; i++)
    {
        wave_drag[i] = 0.6 * sin((2 * pi / 3600) * (i + 2700 - Phi_1));
        // printf("value[%d] = %lf\n", i, wave_drag[i]);
    }

    // 正弦波 lift (位相 3π/2 ズレ)
    // printf("Lift\n");
    for (i = 0; i < 3600; i++)
    {
        wave_lift[i] = 0.6 * sin((2 * pi / 3600) * (i + 1800 - Phi_2));
        // printf("value[%d] = %lf\n", i, wave_lift[i]);
    }

    /*****************************************************************************/

    fp_csv = fopen(filename_csv_1, "w");
    fp_dat = fopen(filename_dat_1, "w");

    for (j = 0; j < split; j++)
    {
        i = j * 150;
        buf = i;
        angle = buf / 10;

        wave_net[i] = sqrt(wave_drag[i] * wave_drag[i] + wave_lift[i] * wave_lift[i]);

        sum[0] = sum[0] + wave_drag[i];
        sum[1] = sum[1] + wave_lift[i];
        sum[2] = sum[2] + wave_net[i];

        fprintf(fp_csv, "%lf,%lf,%lf,%lf\n", angle, wave_drag[i], wave_lift[i], wave_net[i]);
        fprintf(fp_dat, "%lf\t%lf\t%lf\t%lf\n", angle, wave_drag[i], wave_lift[i], wave_net[i]);
    }

    fclose(fp_csv);
    fclose(fp_dat);

    /*****************************************************************************/

    ave[0] = sum[0] / split;
    ave[1] = sum[1] / split;
    ave[2] = sum[2] / split;

    fp_csv = fopen(filename_csv_2, "w");
    fp_dat = fopen(filename_dat_2, "w");

    fprintf(fp_csv, "%lf,%lf,%lf\n", ave[0], ave[1], ave[2]);
    fprintf(fp_dat, "-30\t%.1f\t%lf\t%lf\n", ave[0], ave[1], ave[2]);
    fprintf(fp_dat, "360\t%.1f\t%lf\t%lf\n", ave[0], ave[1], ave[2]);

    fclose(fp_csv);
    fclose(fp_dat);
}

// int main()
// {
//     wavemaker(200, 150);
//     wavemaker(200, -150);
//     wavemaker(-200, -150);
//     wavemaker(900, 900);
//     return (0);
// }