/******************************************************************************
PROGRAM NAME :plot.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// filename
char filename_dat_1[100];
char filename_dat_2[100];
char filename_dat_3[100];
char filename_dat_4[100];
char filename_plot_1[100];
char filename_plot_2[100];

// range x
double x_min = 0;
double x_max = 16;

// range y
double y_min = 0;
double y_max = 80;

// label
char label[100] = "FFT";
char xxlabel[100] = "Number of waves [-]";
char yylabel[100] = "Power [-]";

double size;
FILE *gp;

/*********************************   gnuplot   *********************************/
int plot(char date[])
{
    sprintf(filename_dat_1, "result/%s/07_dat_fft/%s_fft_drag.dat", date, date);
    sprintf(filename_dat_2, "result/%s/07_dat_fft/%s_fft_lift.dat", date, date);
    sprintf(filename_dat_3, "result/%s/52_dat_wave_fft/%s_wave_fft_drag.dat", date, date);
    sprintf(filename_dat_4, "result/%s/52_dat_wave_fft/%s_wave_fft_lift.dat", date, date);
    sprintf(filename_plot_1, "result/%s/plot/wave_maker/fft_summary_drag.png", date);
    sprintf(filename_plot_2, "result/%s/plot/wave_maker/fft_summary_lift.png", date);

    if ((gp = popen("gnuplot", "w")) == NULL)
    {
        printf("gnuplot is not here!\n");
        exit(0); // gnuplotが無い場合、異常ある場合は終了
    }

    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");

    fprintf(gp, "set output '%s'\n", filename_plot_1);
    // fprintf(gp, "set multiplot\n");
    fprintf(gp, "set key right top\n");
    fprintf(gp, "set key font ',20'\n");
    fprintf(gp, "set term pngcairo size 1280, 960 font ',24'\n");
    // fprintf(gp, "set size ratio %lf\n", size);

    fprintf(gp, "set lmargin screen 0.10\n");
    fprintf(gp, "set rmargin screen 0.90\n");
    fprintf(gp, "set tmargin screen 0.90\n");
    fprintf(gp, "set bmargin screen 0.15\n");

    fprintf(gp, "set xrange [%lf:%lf]\n", x_min, x_max);
    fprintf(gp, "set xlabel '%s'offset 0.0,0\n", xxlabel);
    fprintf(gp, "set yrange [%lf:%lf]\n", y_min, y_max);
    fprintf(gp, "set ylabel '%s'offset 0,0.0\n", yylabel);
    fprintf(gp, "set title '%s (drag)'\n", label);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:2 with lines lc 'red' title 'Measured (Drag)', '%s' using 1:2 with lines lc 'green' title 'Theorical (Drag)' \n", filename_dat_1, filename_dat_3);
    fflush(gp); // Clean up Data

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

    fprintf(gp, "set xrange [%lf:%lf]\n", x_min, x_max);
    fprintf(gp, "set xlabel '%s'offset 0.0,0\n", xxlabel);
    fprintf(gp, "set yrange [%lf:%lf]\n", y_min, y_max);
    fprintf(gp, "set ylabel '%s'offset 0,0.0\n", yylabel);
    fprintf(gp, "set title '%s (lift)'\n", label);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:2 with lines lc 'blue' title 'Measured (Lift)', '%s' using 1:2 with lines lc 'orange' title 'Theorical (Lift)' \n", filename_dat_2, filename_dat_4);
    fflush(gp); // Clean up Data

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);
}

int main()
{
    // simulation
    plot("simulation_data");
}