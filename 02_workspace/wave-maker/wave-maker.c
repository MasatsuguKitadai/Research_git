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

char filename_read[100];
char filename_csv[100];
char filename_dat[100];

// sin波の配列
double wave_value[3600];
double wave_drag[3600];
double wave_lift[3600];

// sin波の周期 [秒]
int wave1 = 12;

// 円周率の定義
#define pi 4 * atan(1.0)

/*********************************   MAIN   *********************************/
int wavemaker()
{
    /*****************************************************************************/
    // 元ディレクトリの作成
    char directoryname_csv[100];
    char directoryname_dat[100];

    sprintf(directoryname_dat, "dat");
    sprintf(directoryname_csv, "csv");

    mkdir(directoryname_dat, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_csv, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    /*****************************************************************************/

    // ファイルの指定
    char filename_csv[100];
    char filename_dat[100];

    sprintf(filename_csv, "csv/wave-value.csv");
    sprintf(filename_dat, "dat/wave-value.dat");

    /*****************************************************************************/

    // 正弦波の作成

    int i = 0;

    // 正弦波 drag (位相 π ズレ)
    // printf("Drag\n");
    for (i = 0; i < 3600; i++)
    {
        wave_drag[i] = sin((2 * pi / 3600) * (i + 2700));
        // printf("value[%d] = %lf\n", i, wave_drag[i]);
    }

    // 正弦波 lift (位相 3π/2 ズレ)
    // printf("Lift\n");
    for (i = 0; i < 3600; i++)
    {
        wave_lift[i] = sin((2 * pi / 3600) * (i + 1800));
        // printf("value[%d] = %lf\n", i, wave_lift[i]);
    }

    double angle, buf;

    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");

    for (i = 0; i < 3600; i++)
    {
        buf = i;
        angle = buf / 10;
        fprintf(fp_csv, "%lf,%lf,%lf\n", angle, wave_drag[i], wave_lift[i]);
        fprintf(fp_dat, "%lf\t%lf\t%lf\n", angle, wave_drag[i], wave_lift[i]);
    }

    fclose(fp_csv);
    fclose(fp_dat);
}

int main()
{
    wavemaker();
    return (0);
}