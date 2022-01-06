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
int simulater(char date[], int split, int delta_y, int delta_x)
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

    /*****************************************************************************/
    // オフセット考慮

    double r = 25; // 供試体の半径
    double theta[3600];
    double phi[3600];
    double psi[3600];

    for (i = 0; i < 3600; i++)
    {
        buf = i;
        theta[i] = pi / 1800 * i;
        phi[i] = theta[i] - asin((cos((2 * pi / 3600) * i) * delta_y - sin((2 * pi / 3600) * i) * delta_x) / r);
        psi[i] = -1 * theta[i] + phi[i];
        wave_drag[i] = -0.64 * cos(psi[i]) * cos(phi[i]);
        wave_lift[i] = -0.64 * cos(psi[i]) * sin(phi[i]);
        wave_net[i] = sqrt(wave_drag[i] * wave_drag[i] + wave_lift[i] * wave_lift[i]);
    }

    /*****************************************************************************/

    double degree = 0;

    printf("\t[phi]\t[Drag]\t[Lift]\t[Net]\n");

    fp_csv = fopen(filename_csv_1, "w");
    fp_dat = fopen(filename_dat_1, "w");

    for (j = 0; j < split; j++)
    {
        i = j * 150;
        buf = i;
        angle = buf / 10;

        sum[0] = sum[0] + wave_drag[i];
        sum[1] = sum[1] + wave_lift[i];
        sum[2] = sum[2] + wave_net[i];

        degree = 180 / pi * phi[i];

        fprintf(fp_csv, "%lf,%lf,%lf,%lf\n", angle, wave_drag[i], wave_lift[i], wave_net[i]);
        fprintf(fp_dat, "%lf\t%lf\t%lf\t%lf\n", angle, wave_drag[i], wave_lift[i], wave_net[i]);
        printf("[%.1f]\t%.3f\t%.3f\t%.3f\t%.3f\n", angle, degree, wave_drag[i], wave_lift[i], wave_net[i]);
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

    /*****************************************************************************/

    // Gnuplot //

    // ディレクトリの作成

    sprintf(directoryname_plot, "../result/%s/plot/05", date);
    mkdir(directoryname_plot, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    /*****************************************************************************/

    // filename
    char filename_plot_1[100];
    char filename_plot_2[100];

    sprintf(filename_dat_1, "../result/%s/dat/05-1_summary/05-1.dat", date);
    sprintf(filename_dat_2, "../result/%s/dat/05-2_summary-average/05-2.dat", date);
    sprintf(filename_plot_1, "../result/%s/plot/05/05_summary-wave.png", date);
    sprintf(filename_plot_2, "../result/%s/plot/05/05_summary-outputvoltage.png", date);

    /*****************************************************************************/

    // range x
    double x_min = -30;
    double x_max = 360;
    double interval = 30;

    // range y
    double y_min = -0.8;
    double y_max = 0.8;

    // label
    const char *xxlabel = "Angle [deg]";
    const char *yylabel_1 = "Gradient of voltage [V/V]";
    const char *yylabel_2 = "Net output voltage [V/V]";
    char label_1[100] = "Gradient value";
    char label_2[100] = "Output voltage";

    double size;

    /*****************************************************************************/

    // size
    size = 1;

    if ((gp = popen("gnuplot", "w")) == NULL)
    {
        printf("gnuplot is not here!\n");
        exit(0); // gnuplotが無い場合、異常ある場合は終了
    }

    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");

    fprintf(gp, "set output '%s'\n", filename_plot_1);
    // fprintf(gp, "set multiplot\n");
    fprintf(gp, "set key left top\n");
    fprintf(gp, "set key font ',20'\n");
    fprintf(gp, "set term pngcairo size 1280, 960 font ',24'\n");
    // fprintf(gp, "set size ratio %.3f\n", size);

    fprintf(gp, "set lmargin screen 0.10\n");
    fprintf(gp, "set rmargin screen 0.90\n");
    fprintf(gp, "set tmargin screen 0.90\n");
    fprintf(gp, "set bmargin screen 0.15\n");

    fprintf(gp, "set xrange [%.3f:%.3f]\n", x_min, x_max);
    fprintf(gp, "set xlabel '%s'offset 0.0,0\n", xxlabel);
    fprintf(gp, "set xtics %.3f\n", interval);
    fprintf(gp, "set yrange [%.3f:%.3f]\n", y_min, y_max);
    fprintf(gp, "set ylabel '%s'offset 1,0.0\n", yylabel_1);
    fprintf(gp, "set title '%s'\n", label_1);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:2 with points lc 'blue' pt 5 ps 2 title 'Measured (Drag)', '%s' using 1:3 with points lc 'red' pt 5 ps 2 title 'Measured (Lift)'\n", filename_dat_1, filename_dat_1);
    fflush(gp); // Clean up Data

    // 2枚目

    fprintf(gp, "set output '%s'\n", filename_plot_2);
    // fprintf(gp, "set multiplot\n");
    fprintf(gp, "set key left top\n");
    fprintf(gp, "set key font ',20'\n");
    fprintf(gp, "set term pngcairo size 1280, 960 font ',24'\n");
    // fprintf(gp, "set size ratio %.3f\n", size);

    fprintf(gp, "set lmargin screen 0.10\n");
    fprintf(gp, "set rmargin screen 0.90\n");
    fprintf(gp, "set tmargin screen 0.90\n");
    fprintf(gp, "set bmargin screen 0.15\n");

    fprintf(gp, "set xrange [%.3f:%.3f]\n", x_min, x_max);
    fprintf(gp, "set xlabel '%s'offset 0.0,0\n", xxlabel);
    fprintf(gp, "set xtics %.3f\n", interval);
    fprintf(gp, "set yrange [0.6:0.7]\n");
    fprintf(gp, "set ylabel '%s'offset 1,0.0\n", yylabel_2);
    fprintf(gp, "set ytics 0.02\n");
    fprintf(gp, "set title '%s'\n", label_2);

    // fprintf(gp, "set samples 10000\n");
    // fprintf(gp, "plot 0.63 with lines lc 'grey20' notitle, '%s' using 1:4 with points lc 'green' pt 5 ps 2 notitle\n", filename_dat);
    fprintf(gp, "plot '%s' using 1:4 with points lc 'green' pt 5 ps 2 notitle, '%s' using 1:4 with lines lc 'gray40' title 'Average'\n", filename_dat_1, filename_dat_2);
    fflush(gp); // Clean up Data

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);
}

// int main()
// {
//     simulater("simulation_x=1_y=1", 24, 1, 1);
//     return (0);
// }