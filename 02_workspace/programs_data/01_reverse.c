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
/*****************************************************************************/
int reverse(char date[], char angle[])
{
    /*****************************************************************************/
    // 元ディレクトリの作成
    char directoryname[100];
    char directoryname_csv[100];
    char directoryname_dat[100];
    char directoryname_plot[100];

    sprintf(directoryname, "../result/%s", date);
    sprintf(directoryname_dat, "../result/%s/dat", date);
    sprintf(directoryname_csv, "../result/%s/csv", date);
    sprintf(directoryname_plot, "../result/%s/plot", date);

    mkdir(directoryname, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_dat, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_csv, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_plot, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    /*****************************************************************************/
    // ディレクトリの作成
    sprintf(directoryname_dat, "../result/%s/dat/01_reverse", date);
    sprintf(directoryname_csv, "../result/%s/csv/01_reverse", date);

    mkdir(directoryname_dat, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_csv, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    // ファイルの指定
    char filename_read[100];
    char filename_csv[100];
    char filename_dat[100];

    sprintf(filename_read, "../data/%s/%s.csv", date, angle);
    sprintf(filename_csv, "../result/%s/csv/01_reverse/01_%s.csv", date, angle);
    sprintf(filename_dat, "../result/%s/dat/01_reverse/01_%s.dat", date, angle);

    /*****************************************************************************/

    // 変数宣言
    int i, j;
    int datalength = 0;
    int ch = 3;
    double value[5000][ch];
    double ch0, ch1, ch2; // ch0:drag, ch1:lift, ch2:load-cell

    // 配列の初期化

    for (i = 0; i < 5000; i++)
    {
        for (j = 0; j < 3; j++)
        {
            value[i][j] = 0;
        }
    }

    // printf("check");

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
    // printf("datalengh = %d\n", datalength);

    // 計算

    for (i = 0; i < datalength; i++)
    {
        value[i][2] = -1 * value[i][2];
    }

    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");

    for (i = 0; i < datalength; i++)
    {
        fprintf(fp_csv, "%lf,%lf,%lf\n", value[i][0], value[i][1], value[i][2]);
        fprintf(fp_dat, "%d\t%lf\t%lf\t%lf\n", i, value[i][0], value[i][1], value[i][2]);
    }

    fclose(fp_csv);
    fclose(fp_dat);

    /*****************************************************************************/
    // Gnuplot //

    // ディレクトリの作成
    char directoryname_plot_1[100];
    char directoryname_plot_2[100];

    sprintf(directoryname_plot_1, "../result/%s/plot/01-1_loadcell", date);
    sprintf(directoryname_plot_2, "../result/%s/plot/01-2_strainsensors", date);

    mkdir(directoryname_plot_1, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_plot_2, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    char filename_plot_1[100];
    char filename_plot_2[100];

    sprintf(filename_dat, "../result/%s/dat/01_reverse/01_%s.dat", date, angle);
    sprintf(filename_plot_1, "../result/%s/plot/01-1_loadcell/01_loadcell_%s.png", date, angle);
    sprintf(filename_plot_2, "../result/%s/plot/01-2_strainsensors/01_strainsensors_%s.png", date, angle);

    /*****************************************************************************/

    // range x
    int x_min = 0;
    int x_max = 2300;

    // range y
    double y_min = -1.5;
    double y_max = 1.5;

    // range y (loadcell)
    double y_min_loadcell = -0.5;
    double y_max_loadcell = 2;

    // label
    const char *xxlabel = "time [1/5 s]";
    const char *yylabel = "output voltage [V]";
    char label[100];

    double size;

    sprintf(label, "%s", angle);

    // size
    size = 1;

    /*****************************************************************************/

    if ((gp = popen("gnuplot", "w")) == NULL)
    {
        printf("gnuplot is not here!\n");
        exit(0); // gnuplotが無い場合、異常ある場合は終了
    }

    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
    fprintf(gp, "set output '%s'\n", filename_plot_1);
    // fprintf(gp, "set multiplot\n");
    fprintf(gp, "unset key\n");
    fprintf(gp, "set term pngcairo size 1280, 960 font ',24'\n");
    // fprintf(gp, "set size ratio %lf\n", size);

    fprintf(gp, "set lmargin screen 0.10\n");
    fprintf(gp, "set rmargin screen 0.90\n");
    fprintf(gp, "set tmargin screen 0.90\n");
    fprintf(gp, "set bmargin screen 0.15\n");

    fprintf(gp, "set xrange [%d:%d]\n", x_min, x_max);
    fprintf(gp, "set xlabel '%s'offset 0.0,0\n", xxlabel);
    fprintf(gp, "set yrange [%lf:%lf]\n", y_min_loadcell, y_max_loadcell);
    fprintf(gp, "set ylabel '%s'offset 1,0.0\n", yylabel);
    fprintf(gp, "set title '%s deg'\n", label);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:4 with lines lc 'black' title 'loadcell'\n", filename_dat);
    fflush(gp); // Clean up Data

    /*****************************************************************************/

    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
    fprintf(gp, "set output '%s'\n", filename_plot_2);
    // fprintf(gp, "set multiplot\n");
    fprintf(gp, "set key right top\n");
    fprintf(gp, "set key font ',20'\n");
    fprintf(gp, "set term pngcairo size 1280, 960 font ',24'\n");
    // fprintf(gp, "set size ratio %lf\n", size);

    fprintf(gp, "set lmargin screen 0.10\n");
    fprintf(gp, "set rmargin screen 0.90\n");
    fprintf(gp, "set tmargin screen 0.90\n");
    fprintf(gp, "set bmargin screen 0.15\n");

    fprintf(gp, "set xrange [%d:%d]\n", x_min, x_max);
    fprintf(gp, "set xlabel '%s'offset 0.0,0\n", xxlabel);
    fprintf(gp, "set yrange [%lf:%lf]\n", y_min, y_max);
    fprintf(gp, "set ylabel '%s'offset 1,0.0\n", yylabel);
    fprintf(gp, "set title '%s deg'\n", label);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:2 with lines lc 'blue' title 'Drag', '%s' using 1:3 with lines lc 'red' title 'Lift'\n", filename_dat, filename_dat);
    fflush(gp); // Clean up Data

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);
}

// int main()
// {
//     // simulation
//     reverse("testdata", "0");
//     reverse("testdata", "15");
//     reverse("testdata", "30");
//     reverse("testdata", "45");
//     reverse("testdata", "60");
//     reverse("testdata", "75");
//     reverse("testdata", "90");
//     reverse("testdata", "105");
//     reverse("testdata", "120");
//     reverse("testdata", "135");
//     reverse("testdata", "150");
//     reverse("testdata", "165");
//     reverse("testdata", "180");
//     reverse("testdata", "195");
//     reverse("testdata", "210");
//     reverse("testdata", "225");
//     reverse("testdata", "240");
//     reverse("testdata", "255");
//     reverse("testdata", "270");
//     reverse("testdata", "285");
//     reverse("testdata", "300");
//     reverse("testdata", "315");
//     reverse("testdata", "330");
//     reverse("testdata", "345");

//     return (0);
// }