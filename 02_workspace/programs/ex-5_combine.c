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
int combine(char date[], int range, char model[], int num)
{
    /*****************************************************************************/
    // ディレクトリの作成
    char directoryname_dat[100];
    char directoryname_csv[100];

    sprintf(directoryname_dat, "../result/%s/dat", date);
    sprintf(directoryname_csv, "../result/%s/csv", date);

    mkdir(directoryname_dat, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_csv, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    char directoryname_dat_1[100];
    char directoryname_dat_2[100];
    char directoryname_csv_1[100];
    char directoryname_csv_2[100];

    sprintf(directoryname_dat_1, "../result/%s/dat/05-1_summary", date);
    sprintf(directoryname_dat_2, "../result/%s/dat/05-2_summary-average", date);
    sprintf(directoryname_csv_1, "../result/%s/csv/05-1_summary", date);
    sprintf(directoryname_csv_2, "../result/%s/csv/05-2_summary-average", date);

    mkdir(directoryname_dat_1, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_dat_2, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_csv_1, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_csv_2, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    /*****************************************************************************/

    // 分割
    int split = 3600 / range;
    // printf("split = %d\n", range);

    // ファイル名作成
    char filename_read[100];
    char filename_csv_1[100];
    char filename_csv_2[100];
    char filename_dat_1[100];
    char filename_dat_2[100];

    sprintf(filename_dat_1, "../result/%s/dat/05-1_summary/05-1.dat", date);
    sprintf(filename_csv_1, "../result/%s/csv/05-1_summary/05-1.csv", date);
    sprintf(filename_dat_2, "../result/%s/dat/05-2_summary-average/05-2.dat", date);
    sprintf(filename_csv_2, "../result/%s/csv/05-2_summary-average/05-2.csv", date);

    int i, j;

    int count = 0;
    double buf, ch0, ch1, ch2;
    double value[num][split][3];
    double value_sum[split][3];
    double value_ave[split][3];
    double angle_double = 0;
    double sum[3], ave[3];

    for (i = 0; i < 3; i++)
    {
        sum[i] = 0;
        ave[i] = 0;
    }

    for (i = 0; i < split; i++)
    {
        for (j = 0; j < 3; j++)
        {
            value_sum[i][j] = 0;
            value_ave[i][j] = 0;
        }
    }

    for (i = 0; i < num; i++)
    {
        count = i + 1;
        sprintf(filename_read, "../result/%s-%d/csv/05-1_summary/05-1.csv", model, count);

        fp = fopen(filename_read, "r");
        if (fp == NULL)
        {
            printf("[%s-%d]\tError! I can't open the file.\n\n", model, count);
            break;
        }

        printf("[ %s-%d ]\n", model, count);

        for (j = 0; j < split; j++)
        {
            fscanf(fp, "%lf, %lf, %lf, %lf", &buf, &ch0, &ch1, &ch2);
            printf("【%.1f】\t%.3f\t%.3f\t%.3f\n", buf, ch0, ch1, ch2);

            value[i][j][0] = ch0; // drag
            value[i][j][1] = ch1; // lift
            value[i][j][2] = ch2; // sqrt
        }

        printf("\n");

        fclose(fp);
    }

    for (i = 0; i < split; i++)
    {
        for (j = 0; j < num; j++)
        {
            value_sum[i][0] = value[j][i][0] + value_sum[i][0];
            value_sum[i][1] = value[j][i][1] + value_sum[i][1];
            value_sum[i][2] = value[j][i][2] + value_sum[i][2];
        }

        value_ave[i][0] = value_sum[i][0] / num;
        value_ave[i][1] = value_sum[i][1] / num;
        value_ave[i][2] = value_sum[i][2] / num;

        sum[0] = value_ave[i][0] + sum[0];
        sum[1] = value_ave[i][1] + sum[1];
        sum[2] = value_ave[i][2] + sum[2];
    }

    ave[0] = sum[0] / split;
    ave[1] = sum[1] / split;
    ave[2] = sum[2] / split;

    // plot用 データファイルの書き出し

    printf("[ Average ]\n");

    fp_csv = fopen(filename_csv_1, "w");
    fp_dat = fopen(filename_dat_1, "w");

    for (i = 0; i < split; i++)
    {
        angle_double = i * range;
        angle_double = angle_double / 10;

        fprintf(fp_csv, "%.1f,%lf,%lf,%lf\n", angle_double, value_ave[i][0], value_ave[i][1], value_ave[i][2]);
        fprintf(fp_dat, "%.1f\t%.3f\t%.3f\t%.3f\n", angle_double, value_ave[i][0], value_ave[i][1], value_ave[i][2]);
        printf("【%.1f】\t%.3f\t%.3f\t%.3f\n", angle_double, value_ave[i][0], value_ave[i][1], value_ave[i][2]);
    }

    fclose(fp_csv);
    fclose(fp_dat);

    fp_csv = fopen(filename_csv_2, "w");
    fp_dat = fopen(filename_dat_2, "w");

    fprintf(fp_csv, "%.1f,%lf,%lf\n", ave[0], ave[1], ave[2]);
    fprintf(fp_dat, "-30\t%.3f\t%.3f\t%.3f\n", ave[0], ave[1], ave[2]);
    fprintf(fp_dat, "360\t%.3f\t%.3f\t%.3f\n", ave[0], ave[1], ave[2]);

    fclose(fp_csv);
    fclose(fp_dat);

    /*****************************************************************************/

    // Gnuplot //

    // ディレクトリの作成

    char directoryname_plot[100];

    sprintf(directoryname_plot, "../result/%s/plot/", date);
    mkdir(directoryname_plot, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

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

    printf("\nex-1\t\tsuccess\n");
}
