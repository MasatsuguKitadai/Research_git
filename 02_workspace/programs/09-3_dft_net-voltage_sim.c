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

int netvoltage(char date[], int range, int split)
{
    /*****************************************************************************/
    // ディレクトリの作成
    char directoryname_dat[100];
    char directoryname_csv[100];
    char directoryname_dat_2[100];
    char directoryname_csv_2[100];

    sprintf(directoryname_dat, "../result/%s/dat/09-3_net-voltage", date);
    sprintf(directoryname_csv, "../result/%s/csv/09-3_net-voltage", date);
    sprintf(directoryname_dat_2, "../result/%s/dat/09-4_summary-average", date);
    sprintf(directoryname_csv_2, "../result/%s/csv/09-4_summary-average", date);

    mkdir(directoryname_dat, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_csv, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_dat_2, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_csv_2, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    // ファイルの指定
    char filename_read_1[100];
    char filename_read_2[100];
    char filename_read_3[100];
    char filename_read_4[100];

    char filename_csv[100];
    char filename_dat[100];

    char filename_csv_average[100];
    char filename_dat_average[100];

    sprintf(filename_read_1, "../result/%s/csv/08-3_phase-angle_drag/08-3.csv", date);
    sprintf(filename_read_2, "../result/%s/csv/08-4_phase-angle_lift/08-4.csv", date);
    sprintf(filename_read_3, "../result/%s/csv/12_interpolation/12-1.csv", date);

    sprintf(filename_csv, "../result/%s/csv/09-3_net-voltage/09-3.csv", date);
    sprintf(filename_dat, "../result/%s/dat/09-3_net-voltage/09-3.dat", date);
    sprintf(filename_csv_average, "../result/%s/csv/09-4_summary-average/09-4.csv", date);
    sprintf(filename_dat_average, "../result/%s/dat/09-4_summary-average/09-4.dat", date);

    /*****************************************************************************/

    int i;
    double num;
    double ch0, ch1, ch2;
    double angle_drag[2];
    double angle_lift[2];
    double sum[3], ave[3];

    for (i = 0; i < 3; i++)
    {
        sum[i] = 0;
        ave[i] = 0;
    }

    /*****************************************************************************/

    fp = fopen(filename_read_1, "r");

    if (fp == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    fscanf(fp, "%lf, %lf", &ch0, &ch1);

    // printf("(Drag)\t%.3f [rad] / \t%.1f [deg]\n", ch0, ch1);
    angle_drag[0] = ch0; // radian
    angle_drag[1] = ch1; // degree

    fclose(fp);

    /*****************************************************************************/

    fp = fopen(filename_read_2, "r");

    if (fp == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    fscanf(fp, "%lf, %lf", &ch0, &ch1);

    // printf("(Lift)\t%.3f [rad] / \t%.1f [deg]\n", ch0, ch1);
    angle_lift[0] = ch0; // radian
    angle_lift[1] = ch1; // degree

    fclose(fp);

    // printf("\n");

    /*****************************************************************************/

    // 位相差の算出

    double angle_drag_theory[2];
    double angle_lift_theory[2];

    angle_drag_theory[0] = pi;
    angle_lift_theory[0] = pi / 2;

    // printf("(Drag)\t%.1f [rad]\n", angle_drag_theory[0]);
    // printf("(Lift)\t%.1f [rad]\n\n", angle_lift_theory[0]);

    angle_drag_theory[1] = 180;
    angle_lift_theory[1] = 90;

    double angle_drag_difference[2];
    double angle_lift_difference[2];

    angle_drag_difference[0] = angle_drag[0] - angle_drag_theory[0];
    angle_lift_difference[0] = angle_lift[0] - angle_lift_theory[0];

    angle_drag_difference[1] = angle_drag[1] - angle_drag_theory[1];
    angle_lift_difference[1] = angle_lift[1] - angle_lift_theory[1];

    printf("[Difference]=================\n\n");

    printf("(Drag)\t%.1f [rad]\n", angle_drag_difference[0]);
    printf("(Lift)\t%.1f [rad]\n", angle_lift_difference[0]);

    printf("(Drag)\t%.1f [deg]\n", angle_drag_difference[1]);
    printf("(Lift)\t%.1f [deg]\n", angle_lift_difference[1]);

    printf("\n=============================\n");

    /*****************************************************************************/
    // 傾きの読み込み

    double angle[split];
    double voltage_drag[split];
    double voltage_lift[split];

    fp = fopen(filename_read_3, "r");

    if (filename_read_3 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    // printf("check\n");

    i = 0;

    printf("【Raw Data】\n");
    printf("\t[Drag]\t[Lift]\t[Net]\n");

    while ((fscanf(fp, "%lf,%lf,%lf,%lf", &num, &ch0, &ch1, &ch2)) != EOF)
    {
        angle[i] = num;
        voltage_drag[i] = ch0;
        voltage_lift[i] = ch1;
        printf("[%.1f]\t%.3f\t%.3f\t%.3f\n", angle[i], voltage_drag[i], voltage_lift[i], ch2);
        i = i + 1;
        sum[0] = ch0 + sum[0];
        sum[1] = ch1 + sum[1];
        sum[2] = ch2 + sum[2];
    }

    fclose(fp);

    ave[0] = sum[0] / split;
    ave[1] = sum[1] / split;
    ave[2] = sum[2] / split;

    printf("=============================\n");
    printf("[Ave]\t%.3f\t%.3f\t%.3f\n", ave[0], ave[1], ave[2]);

    printf("\n");

    /*****************************************************************************/
    double voltage_x[split];
    double voltage_y[split];
    double voltage_y_2[split];
    double voltage_net[split];

    double buf[2];
    double s[2];
    double c[2];
    double t[2];

    for (i = 0; i < 3; i++)
    {
        sum[i] = 0;
        ave[i] = 0;
    }

    // printf("cos = %lf\n", cos(angle_drag_difference[0]));
    // printf("sin = %lf\n", sin(angle_lift_difference[0]));
    // printf("\n");

    printf("【Corrected Data】\n");
    printf("=============================\n");
    printf("\t[Drag]\t[Lift]\t[Net]\n");

    s[0] = sin(-1 * angle_drag_difference[0]);
    c[0] = cos(-1 * angle_drag_difference[0]);

    s[1] = sin(-1 * angle_lift_difference[0]);
    c[1] = cos(-1 * angle_lift_difference[0]);

    // printf("\n[sin]\t[cos]\t| [sin]\t[cos]\n");
    // printf("%.3f\t%.3f\t| %.3f\t%.3f\n\n", s[0], c[0], s[1], c[1]);

    for (i = 0; i < split; i++)
    {
        voltage_x[i] = (voltage_drag[i] * c[1] - voltage_lift[i] * s[0]) / (c[0] * c[1] + s[0] * s[1]);
        voltage_y[i] = -(c[0] / s[0]) * voltage_x[i] + voltage_drag[i] / s[0];
        voltage_y_2[i] = -(s[1] / c[1]) * voltage_x[i] + voltage_lift[i] / c[1];
        voltage_net[i] = sqrt((voltage_x[i] * voltage_x[i]) + (voltage_y[i] * voltage_y[i]));

        //　平均値の算出

        sum[0] = voltage_x[i] + sum[0];
        sum[1] = voltage_y[i] + sum[1];
        sum[2] = voltage_net[i] + sum[2];

        // printf("[%.1f]\t%.3f\t%.3f\t%.3f\t\t%.3f\n", angle[i], voltage_x[i], voltage_y[i], voltage_net[i], voltage_y_2[i]);
        printf("[%.1f]\t%.3f\t%.3f\t%.3f\n", angle[i], voltage_x[i], voltage_y[i], voltage_net[i]);
    }

    ave[0] = sum[0] / split;
    ave[1] = sum[1] / split;
    ave[2] = sum[2] / split;

    printf("=============================\n");
    printf("[Ave]\t%.3f\t%.3f\t%.3f\n", ave[0], ave[1], ave[2]);

    /*****************************************************************************/

    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");

    for (i = 0; i < split; i++)
    {
        fprintf(fp_csv, "%.1f,%lf,%lf,%lf\n", angle[i], voltage_x[i], voltage_y[i], voltage_net[i]);
        fprintf(fp_dat, "%.1f\t%.3f\t%.3f\t%.3f\n", angle[i], voltage_x[i], voltage_y[i], voltage_net[i]);
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

    // 分散計算

    long double variance = 0;
    double deviation = 0;
    double sum2 = 0;

    for (i = 0; i < 3; i++)
    {
        sum[i] = 0;
        ave[i] = 0;
    }

    for (i = 0; i < split; i++)
    {
        sum[0] = voltage_x[i] + sum[0];
        sum[1] = voltage_y[i] + sum[1];
        sum[2] = voltage_net[i] + sum[2];
    }

    for (i = 0; i < 3; i++)
    {
        ave[i] = sum[i] / split;
        // printf("[%d]\t%.3f\n", i, ave[i]);
    }

    for (i = 0; i < split; i++)
    {
        sum2 = voltage_net[i] * voltage_net[i] + sum2;
    }

    variance = sum2 / split - ave[2] * ave[2];
    deviation = sqrt(variance);

    printf("\n");
    printf("variance \t= %Lf\n", variance);
    printf("deviation\t= %lf\n\n", deviation);

    /*****************************************************************************/

    // Gnuplot //

    // ディレクトリの作成

    char directoryname_plot[100];

    sprintf(directoryname_plot, "../result/%s/plot/09", date);
    mkdir(directoryname_plot, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    /*****************************************************************************/

    // filename
    char filename_plot_1[100];
    char filename_plot_2[100];

    sprintf(filename_plot_1, "../result/%s/plot/09/09_summary-wave-net.png", date);
    sprintf(filename_plot_2, "../result/%s/plot/09/09_summary-outputvoltage-net.png", date);

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
    fprintf(gp, "set key font ',22'\n");
    fprintf(gp, "set term pngcairo size 1280, 960 font ',27'\n");
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
    fprintf(gp, "plot '%s' using 1:2 with points lc 'blue' pt 5 ps 2 title 'Measured (Drag)', '%s' using 1:3 with points lc 'red' pt 5 ps 2 title 'Measured (Lift)'\n", filename_dat, filename_dat);
    fflush(gp); // Clean up Data

    // 2枚目

    fprintf(gp, "set output '%s'\n", filename_plot_2);
    // fprintf(gp, "set multiplot\n");
    fprintf(gp, "set key left top\n");
    fprintf(gp, "set key font ',22'\n");
    fprintf(gp, "set term pngcairo size 1280, 960 font ',27'\n");
    // fprintf(gp, "set size ratio %.3f\n", size);

    fprintf(gp, "set lmargin screen 0.10\n");
    fprintf(gp, "set rmargin screen 0.90\n");
    fprintf(gp, "set tmargin screen 0.90\n");
    fprintf(gp, "set bmargin screen 0.15\n");

    fprintf(gp, "set xrange [%.3f:%.3f]\n", x_min, x_max);
    fprintf(gp, "set xlabel '%s'offset 0.0,0\n", xxlabel);
    fprintf(gp, "set xtics %.3f\n", interval);
    fprintf(gp, "set yrange [0.95:1.05]\n");

    fprintf(gp, "set ylabel '%s'offset 1.5,0.0\n", yylabel_2);
    fprintf(gp, "set ytics 0.01\n");
    fprintf(gp, "set title '%s'\n", label_2);

    // fprintf(gp, "set samples 10000\n");
    // fprintf(gp, "plot 0.63 with lines lc 'grey20' notitle, '%s' using 1:4 with points lc 'green' pt 5 ps 2 notitle\n", filename_dat);
    fprintf(gp, "plot '%s' using 1:4 with points lc 'green' pt 5 ps 2 notitle, '%s' using 1:4 with lines lc 'gray40' title 'Average'\n", filename_dat, filename_dat_average);
    fflush(gp); // Clean up Data

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);

    printf("\n09\t\tsuccess\n");
}

// int main()
// {
// netvoltage("test-fft", 225);
// return (0);
// }