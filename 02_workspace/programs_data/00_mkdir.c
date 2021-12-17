/******************************************************************************
PROGRAM NAME :
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>

FILE *fp;
/*********************************   MAIN   *********************************/
int directries(char date[])
{
    char directoryname_00[100];
    char directoryname_00_csv[100];
    char directoryname_00_dat[100];
    char directoryname_00_plot[100];

    char directoryname_01_dat[100];
    char directoryname_01_csv[100];
    char directoryname_01_plot[100];

    char directoryname_02_dat[100];
    char directoryname_02_csv[100];
    char directoryname_02_plot[100];

    char directoryname_03_dat[100];
    char directoryname_03_csv[100];
    char directoryname_03_plot[100];

    char directoryname_04_dat[100];
    char directoryname_04_csv[100];
    char directoryname_04_plot[100];

    char directoryname_05_dat[100];
    char directoryname_05_csv[100];
    char directoryname_05_plot[100];

    char directoryname_06_dat[100];
    char directoryname_06_csv[100];
    char directoryname_06_plot[100];

    char directoryname_07_dat[100];
    char directoryname_07_csv[100];
    char directoryname_07_plot[100];

    char directoryname_08_dat[100];
    char directoryname_08_csv[100];
    char directoryname_08_plot[100];

    char directoryname_09_dat[100];
    char directoryname_09_csv[100];
    char directoryname_09_plot[100];

    char directoryname_10_dat[100];
    char directoryname_10_csv[100];

    char directoryname_11_dat[100];
    char directoryname_11_csv[100];

    char directoryname_12_dat[100];
    char directoryname_12_csv[100];

    char directoryname_13_dat[100];
    char directoryname_13_csv[100];

    char directoryname_14_dat[100];
    char directoryname_14_csv[100];

    char directoryname_15_dat[100];
    char directoryname_15_csv[100];

    char directoryname_16_dat[100];
    char directoryname_16_csv[100];

    char directoryname_17_dat[100];
    char directoryname_17_csv[100];

    char directoryname_18_dat[100];
    char directoryname_18_csv[100];

    char directoryname_19_dat[100];
    char directoryname_19_csv[100];

    char directoryname_20_dat[100];
    char directoryname_20_csv[100];

    sprintf(directoryname_00, "../result/%s", date);
    sprintf(directoryname_00_dat, "../result/%s/dat", date);
    sprintf(directoryname_00_csv, "../result/%s/csv", date);
    sprintf(directoryname_00_csv, "../result/%s/plot", date);

    sprintf(directoryname_01_csv, "../result/%s/csv/01_reverse", date);
    sprintf(directoryname_01_dat, "../result/%s/dat/01_reverse", date);
    sprintf(directoryname_01_plot, "../result/%s/plot/01_reverse", date);

    sprintf(directoryname_02_csv, "../result/%s/csv/02_drift", date);
    sprintf(directoryname_02_dat, "../result/%s/dat/02_drift", date);
    sprintf(directoryname_02_plot, "../result/%s/plot/02_drift", date);

    sprintf(directoryname_03_csv, "../result/%s/csv/03_average", date);
    sprintf(directoryname_03_dat, "../result/%s/dat/03_average", date);
    sprintf(directoryname_03_plot, "../result/%s/plot/03_average", date);

    sprintf(directoryname_04_csv, "../result/%s/csv/04_gradient", date);
    sprintf(directoryname_04_dat, "../result/%s/dat/04_gradient", date);
    sprintf(directoryname_04_plot, "../result/%s/plot/04_gradient", date);

    sprintf(directoryname_05_csv, "../result/%s/csv/05_summary", date);
    sprintf(directoryname_05_dat, "../result/%s/dat/05_summary", date);
    sprintf(directoryname_05_plot, "../result/%s/plot/05_summary", date);

    sprintf(directoryname_06_csv, "../result/%s/csv/06_evaluation", date);
    sprintf(directoryname_06_dat, "../result/%s/dat/06_evaluation", date);
    sprintf(directoryname_06_plot, "../result/%s/plot/06_evaluation", date);

    sprintf(directoryname_07_csv, "../result/%s/csv/07_fft", date);
    sprintf(directoryname_07_dat, "../result/%s/dat/07_fft", date);
    sprintf(directoryname_07_plot, "../result/%s/plot/07_fft", date);

    sprintf(directoryname_08_csv, "../result/%s/csv/08_phase-angle", date);
    sprintf(directoryname_08_dat, "../result/%s/dat/08_phase-angle", date);
    sprintf(directoryname_08_plot, "../result/%s/plot/08_phase-angle", date);

    // sprintf(directoryname_09_csv, "../result/%s/csv/", date;
    // sprintf(directoryname_10_csv, "../result/%s/csv/", date;
    // sprintf(directoryname_11_csv, "../result/%s/csv/", date;
    // sprintf(directoryname_12_csv, "../result/%s/csv/", date;
    // sprintf(directoryname_13_csv, "../result/%s/csv/", date;
    // sprintf(directoryname_14_csv, "../result/%s/csv/", date;
    // sprintf(directoryname_15_csv, "../result/%s/csv/", date;
    // sprintf(directoryname_16_csv, "../result/%s/csv/", date;
    // sprintf(directoryname_17_csv, "../result/%s/csv/", date;
    // sprintf(directoryname_18_csv, "../result/%s/csv/", date;
    // sprintf(directoryname_19_csv, "../result/%s/csv/", date;
    // sprintf(directoryname_20_csv, "../result/%s/csv/", date;

    mkdir(directoryname_00, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_00_dat, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_00_csv, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    mkdir(directoryname_01_dat, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_01_csv, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    mkdir(directoryname_02_dat, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_02_csv, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    mkdir(directoryname_03_dat, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_03_csv, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    mkdir(directoryname_04_dat, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_04_csv, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    mkdir(directoryname_05_dat, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_05_csv, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    mkdir(directoryname_06_dat, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_06_csv, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    mkdir(directoryname_07_dat, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_07_csv, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    mkdir(directoryname_08_dat, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_08_csv, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
}

int main()
{
    directries("testdata");
    return (0);
}