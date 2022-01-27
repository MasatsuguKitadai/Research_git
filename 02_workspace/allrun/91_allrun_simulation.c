/******************************************************************************
PROGRAM NAME : sin_wave_maker.c
AUTHER  : masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
#include "../programs/00_dft.c"
#include "../programs/91_simulater.c"

FILE *fp, *fp_csv, *fp_dat, *gp;

// 円周率の定義
#define pi 4 * atan(1.0)

/*********************************   MAIN   *********************************/
int main()
{
    char dataname[50] = "simulation_sensors";

    // ディレクトリの作成
    char directoryname[100];

    sprintf(directoryname, "../result/%s", dataname);
    mkdir(directoryname, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    char directoryname_dat[100];
    char directoryname_csv[100];
    char directoryname_plot[100];

    sprintf(directoryname_dat, "../result/%s/dat", dataname);
    sprintf(directoryname_csv, "../result/%s/csv", dataname);
    sprintf(directoryname_plot, "../result/%s/plot", dataname);

    mkdir(directoryname_dat, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_csv, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_plot, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    /*****************************************************************************/

    sprintf(directoryname_dat, "../result/%s/dat/wave", dataname);
    sprintf(directoryname_csv, "../result/%s/csv/wave", dataname);

    mkdir(directoryname_dat, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_csv, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    /*****************************************************************************/

    sprintf(directoryname_dat, "../result/%s/dat/average", dataname);
    sprintf(directoryname_csv, "../result/%s/csv/average", dataname);

    mkdir(directoryname_dat, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_csv, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    /*****************************************************************************/
    sprintf(directoryname_dat, "../result/%s/dat/dft", dataname);
    sprintf(directoryname_csv, "../result/%s/csv/dft", dataname);

    mkdir(directoryname_dat, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_csv, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    /*****************************************************************************/
    double theta_x, theta_y;

    // printf("[Parameters]\n");
    // printf("Theta x = ");
    // scanf("%lf", &theta_x);
    // printf("Theta y = ");
    // scanf("%lf", &theta_y);
    // printf("\n");

    int i, j;
    int num = 500;

    for (i = 0; i < num; i++)
    {
        for (j = 0; j < num; j++)
        {
            theta_x = i * 0.01;
            theta_y = j * 0.01;
            simulater(dataname, theta_x, theta_y);
        }
    }

    return (0);
}