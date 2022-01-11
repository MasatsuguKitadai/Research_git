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
int correct_offset(char date[], int split, double delta_y, double delta_x)
{
    /*****************************************************************************/
    // ディレクトリの作成
    char directoryname_dat[100];
    char directoryname_csv[100];

    sprintf(directoryname_dat, "../result/%s/dat/11_offset-correct", date);
    sprintf(directoryname_csv, "../result/%s/csv/11_offset-correct", date);

    mkdir(directoryname_dat, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_csv, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    /*****************************************************************************/

    // filename
    char filename_read[100];
    char filename_csv[100];
    char filename_dat[100];
    char filename_csv_average[100];
    char filename_dat_average[100];

    sprintf(filename_read, "../result/%s/csv/05-1_summary/05-1.csv", date);

    sprintf(filename_csv, "../result/%s/csv/11_offset-correct/11-1.csv", date);
    sprintf(filename_dat, "../result/%s/dat/11_offset-correct/11-1.dat", date);

    sprintf(filename_csv_average, "../result/%s/csv/11_offset-correct/11-2.csv", date);
    sprintf(filename_dat_average, "../result/%s/dat/11_offset-correct/11-2.dat", date);

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
        // printf("%.1f, %.3f, %.3f, %.3f\n", buf, ch0, ch1, ch2);
        angle[i] = buf;
        value[i][0] = ch0; // drag
        value[i][1] = ch1; // lift
        value[i][2] = ch2; // sqrt
        i = i + 1;
    }

    fclose(fp);

    /*****************************************************************************/

    double F[split][3];
    double phi[split], psi[split];
    long double alfa[split];
    double r = 25; // 供試体の半径

    double degree;
    double sum[3], ave[3];

    for (i = 0; i < 3; i++)
    {
        sum[i] = 0;
        ave[i] = 0;
    }

    printf("\t[Alfa]\tF[x]\tF[y]\tF[net]\n");

    for (i = 0; i < split; i++)
    {
        phi[i] = pi / 180 * angle[i];

        alfa[i] = asinl((delta_x * sin(phi[i]) + delta_y * cos(phi[i])) / r);
        psi[i] = phi[i] - alfa[i];

        F[i][0] = value[i][0] / cos(alfa[i]);
        F[i][1] = value[i][1] / cos(alfa[i]);
        F[i][2] = sqrt(F[i][0] * F[i][0] + F[i][1] * F[i][1]);

        phi[i] = phi[i] * 180 / pi;
        degree = 180 / pi * alfa[i];
        printf("[%.1f]\t%.3f\t%.3f\t%.3f\t%.3f\n", phi[i], degree, F[i][0], F[i][1], F[i][2]);

        sum[0] = F[i][0] + sum[0];
        sum[1] = F[i][1] + sum[1];
        sum[2] = F[i][2] + sum[2];
    }

    ave[0] = sum[0] / split;
    ave[1] = sum[1] / split;
    ave[2] = sum[2] / split;

    /*****************************************************************************/

    // plot用 データファイルの書き出し

    double angle_double;

    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");

    for (i = 0; i < split; i++)
    {
        angle_double = i * 150;
        angle_double = angle_double / 10;

        fprintf(fp_csv, "%.1f,%lf,%lf,%lf\n", angle_double, F[i][0], F[i][1], F[i][2]);
        fprintf(fp_dat, "%.1f\t%.3f\t%.3f\t%.3f\n", angle_double, F[i][0], F[i][1], F[i][2]);
        // printf("%.3f\t%.3f\t%.3f\t%.3f\n", angle_double, value[i][0], value[i][1], value[i][2]);
    }

    fclose(fp_csv);
    fclose(fp_dat);

    fp_csv = fopen(filename_csv_average, "w");
    fp_dat = fopen(filename_dat_average, "w");

    fprintf(fp_csv, "%lf,%lf,%lf\n", ave[0], ave[1], ave[2]);
    fprintf(fp_dat, "-30\t%.3f\t%.3f\t%.3f\n", ave[0], ave[1], ave[2]);
    fprintf(fp_dat, "360\t%.3f\t%.3f\t%.3f\n", ave[0], ave[1], ave[2]);

    fclose(fp_csv);
    fclose(fp_dat);

    /*****************************************************************************/

    // Gnuplot //

    // ディレクトリの作成

    char directoryname_plot[100];

    sprintf(directoryname_plot, "../result/%s/plot/11", date);
    mkdir(directoryname_plot, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    /*****************************************************************************/

    // filename
    char filename_plot_1[100];

    sprintf(filename_plot_1, "../result/%s/plot/11/11_offset-correct.png", date);

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
    fprintf(gp, "plot '%s' using 1:2 with points lc 'blue' pt 5 ps 2 title 'Offset corrected (Drag)', '%s' using 1:3 with points lc 'red' pt 5 ps 2 title 'Offset corrected (Lift)'\n", filename_dat, filename_dat);
    fflush(gp); // Clean up Data

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);

    printf("\n11\t\tsuccess\n");
}

// int main()
// {
//     // simulation
//     evaluation("testdata");

//     return (0);
// }