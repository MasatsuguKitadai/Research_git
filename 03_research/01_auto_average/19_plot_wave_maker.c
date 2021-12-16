/******************************************************************************
PROGRAM NAME :plot.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// filename
char filename_dat[100];
char filename_dat_wave[100];
char filename_plot[100];

// range x
double x_min = -30;
double x_max = 360;
double interval = 30;

// range y
double y_min = -0.8;
double y_max = 0.8;

// label
const char *xxlabel = "Angle [deg]";
const char *yylabel = "Gradient of voltage [V/V]";
char label[100] = "Gradient value";

double size;
FILE *gp;

/*********************************   gnuplot   *********************************/
int plot(char date[])
{
    sprintf(filename_dat, "result/%s/05_dat_summary/%s_summary.dat", date, date);
    sprintf(filename_dat_wave, "result/%s/09_dat_wave/%s_wave.dat", date, date);
    sprintf(filename_plot, "result/%s/plot/wave_maker/summary_1_ver2.png", date);

    // size
    size = 1;

    if ((gp = popen("gnuplot", "w")) == NULL)
    {
        printf("gnuplot is not here!\n");
        exit(0); // gnuplotが無い場合、異常ある場合は終了
    }

    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");

    fprintf(gp, "set output '%s'\n", filename_plot);
    // fprintf(gp, "set multiplot\n");
    fprintf(gp, "set key left top\n");
    fprintf(gp, "set key font ',20'\n");
    fprintf(gp, "set term pngcairo size 1280, 960 font ',24'\n");
    // fprintf(gp, "set size ratio %lf\n", size);

    fprintf(gp, "set lmargin screen 0.10\n");
    fprintf(gp, "set rmargin screen 0.90\n");
    fprintf(gp, "set tmargin screen 0.90\n");
    fprintf(gp, "set bmargin screen 0.15\n");

    fprintf(gp, "set xrange [%lf:%lf]\n", x_min, x_max);
    fprintf(gp, "set xlabel '%s'offset 0.0,0\n", xxlabel);
     fprintf(gp,"set xtics %lf\n", interval);
    fprintf(gp, "set yrange [%lf:%lf]\n", y_min, y_max);
    fprintf(gp, "set ylabel '%s'offset 1,0.0\n", yylabel);
    fprintf(gp, "set title '%s'\n", label);

    // fprintf(gp, "set samples 10000\n");
    // fprintf(gp, "plot '%s' using 1:2 with points lc 'blue' pt 5 ps 2 notitle, '%s' using 1:3 with points lc 'red' pt 5 ps 2 notitle, '%s' using 1:2 with points lc 'royalblue' pt 5 ps 2 notitle, '%s' using 1:3 with points lc 'orange' pt 5 ps 2 notitle\n", filename_dat, filename_dat, filename_dat_wave, filename_dat_wave);
    fprintf(gp, "plot '%s' using 1:2 with points lc 'blue' pt 5 ps 2 title 'measured (Drag)', '%s' using 1:3 with points lc 'red' pt 5 ps 2 title 'measured (Lift)', '%s' using 1:2 with lines lc 'royalblue' title 'Theoretical (Drag)', '%s' using 1:3 with lines lc 'orange' title 'Theoretical (Lift)'\n", filename_dat, filename_dat, filename_dat_wave, filename_dat_wave);
    fflush(gp); //Clean up Data

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);
}

int main()
{
    // 211208
    // plot("211208");

    // simulation
    plot("simulation_data");

    return (0);
}