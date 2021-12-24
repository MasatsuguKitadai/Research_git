/******************************************************************************
PROGRAM NAME : sin_wave_maker.c
AUTHER  : masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>

// sin波の配列
double wave_drag[3600];
double wave_lift[3600];

// 円周率の定義
// double pi = 4 * atan(1.0)

FILE *fp, *fp_csv, *fp_dat, *fp_plot, *gp;

/*********************************   MAIN   *********************************/
int waveadjuster_ver2(char date[])
{
    /*****************************************************************************/
    // ディレクトリの作成
    char directoryname_csv[100];
    char directoryname_dat[100];

    sprintf(directoryname_dat, "../result/%s/dat/21_adjust-value_ver2", date);
    sprintf(directoryname_csv, "../result/%s/csv/21_adjust-value_ver2", date);

    mkdir(directoryname_dat, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_csv, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    // ファイルの指定
    char filename_read_1[100];
    char filename_read_2[100];
    char filename_csv[100];
    char filename_dat[100];
    char filename_dat_plot[100];

    sprintf(filename_read_1, "../result/%s/csv/09-2_summary-average/09-2.csv", date);
    sprintf(filename_read_2, "../wave-maker/csv/wave-value.csv");
    sprintf(filename_csv, "../result/%s/csv/21_adjust-value_ver2/21.csv", date);
    sprintf(filename_dat, "../result/%s/dat/21_adjust-value_ver2/21.dat", date);
    sprintf(filename_dat_plot, "../result/%s/dat/21_adjust-value_ver2/21_plot.dat", date);

    /*****************************************************************************/

    double ch0, ch1, ch2;
    double average_value;

    fp = fopen(filename_read_1, "r");
    if (filename_read_1 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    fscanf(fp, "%lf,%lf,%lf", &ch0, &ch1, &ch2);
    // printf("【Average】\t%.3f\t%.3f\t%.3f\n", ch0, ch1, ch2);
    average_value = ch2; // sqrt average

    /*****************************************************************************/

    fp = fopen(filename_read_2, "r");
    if (filename_read_2 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    int i = 0;

    while ((fscanf(fp, "%lf, %lf, %lf", &ch0, &ch1, &ch2)) != EOF)
    {
        // printf("%.3f, %.3f, %.3f\n", ch0, ch1, ch2);
        wave_drag[i] = ch1;
        wave_lift[i] = ch2;
        i = i + 1;
    }

    /*****************************************************************************/

    i = 0;

    // 正弦波 drag (位相 π ズレ)
    // printf("Drag\n");
    for (i = 0; i < 3600; i++)
    {
        wave_drag[i] = wave_drag[i] * average_value;
        // printf("value[%d] = %.3f\n", i, wave_drag[i]);
    }

    // 正弦波 lift (位相 3π/2 ズレ)
    // printf("Lift\n");
    for (i = 0; i < 3600; i++)
    {
        wave_lift[i] = wave_lift[i] * average_value;
        // printf("value[%d] = %.3f\n", i, wave_lift[i]);
    }

    double angle, buf;

    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");
    fp_plot = fopen(filename_dat_plot, "w");

    for (i = 3300; i < 3600; i++)
    {
        buf = i;
        angle = buf / 10;
        angle = angle - 360;
        // printf("angle = %.3f\ti = %d\n", angle, i);
        fprintf(fp_plot, "%lf\t%lf\t%lf\n", angle, wave_drag[i], wave_lift[i]);
    }

    for (i = 0; i < 3600; i++)
    {
        buf = i;
        angle = buf / 10;
        // printf("angle = %.3f\ti = %d\n", angle, i);
        fprintf(fp_csv, "%lf,%lf,%lf\n", angle, wave_drag[i], wave_lift[i]);
        fprintf(fp_dat, "%lf\t%lf\t%lf\n", angle, wave_drag[i], wave_lift[i]);
        fprintf(fp_plot, "%lf\t%lf\t%.3f\n", angle, wave_drag[i], wave_lift[i]);
    }

    fclose(fp_csv);
    fclose(fp_dat);
    fclose(fp_plot);

    /*****************************************************************************/
    // Gnuplot //

    // ディレクトリの作成
    char directoryname_plot[100];

    sprintf(directoryname_plot, "../result/%s/plot/21", date);

    mkdir(directoryname_plot, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    // filename
    char filename_dat_1[100];
    char filename_dat_2[100];
    char filename_dat_3[100];
    char filename_plot_1[100];
    char filename_plot_2[100];

    sprintf(filename_dat_1, "../result/%s/dat/05-1_summary/05-1.dat", date);
    sprintf(filename_dat_2, "../result/%s/dat/09-1_net-voltage/09-1.dat", date);
    sprintf(filename_dat_3, "../result/%s/dat/21_adjust-value_ver2/21_plot.dat", date);

    sprintf(filename_plot_1, "../result/%s/plot/21/21_summary_drag.png", date);
    sprintf(filename_plot_2, "../result/%s/plot/21/21_summary_lift.png", date);

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
    char label_2[100] = "Output otage";

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
    fprintf(gp, "set title '%s (Drag)'\n", label_1);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:2 with points lc 'blue' pt 5 ps 2 title 'Measured (Drag)', '%s' using 1:2 with points lc 'goldenrod' pt 5 ps 2 title 'Corrected (Drag)', '%s' using 1:2 with lines lc 'royalblue' title 'Theoretical (Drag)'\n", filename_dat_1, filename_dat_2, filename_dat_3);

    fflush(gp); // Clean up Data

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
    fprintf(gp, "set yrange [%.3f:%.3f]\n", y_min, y_max);
    fprintf(gp, "set ylabel '%s'offset 1,0.0\n", yylabel_1);
    fprintf(gp, "set title '%s (Lift)'\n", label_1);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:3 with points lc 'red' pt 5 ps 2 title 'Measured (Lift)', '%s' using 1:3 with points lc 'forest-green' pt 5 ps 2 title 'Corrected (Lift)', '%s' using 1:3 with lines lc 'orange' title 'Theoretical (Lift)'\n", filename_dat_1, filename_dat_2, filename_dat_3);

    fflush(gp); // Clean up Data

    pclose(gp);

    printf("\n09\t\tsuccess\n");

    printf("20\t\tsuccess\n");
}

// int main()
// {
//     waveadjuster("testdata");
//     return (0);
// }