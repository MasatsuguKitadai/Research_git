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
char filename_plot_1[100];
char filename_plot_2[100];

// range x
int x_min = 0;
int x_max = 2300;

// range y
double y_min = -1;
double y_max = 1;

// range y (loadcell)
double y_min_loadcell = -0.5;
double y_max_loadcell = 2;

// label
const char *xxlabel = "time [1/5 s]";
const char *yylabel = "output voltage [V]";
char label[100];

double size;
FILE *gp;

/*********************************   gnuplot   *********************************/
int plot(char date[], char angle[])
{
    sprintf(label, "%s",angle);
    sprintf(filename_dat, "%s/dat_reverse/%s_reverse.dat",    date,  angle);
    sprintf(filename_plot_1, "%s/plot/voltage-time/%s_loadcell.png", date, angle);
    sprintf(filename_plot_2, "%s/plot/voltage-time/%s_strainsensor.png", date, angle);

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
    fflush(gp); //Clean up Data

// 2枚目

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
    fprintf(gp, "plot '%s' using 1:2 with lines lc 'royalblue' title 'drag', '%s' using 1:3 with lines lc 'orange' title 'lift'\n", filename_dat, filename_dat);
    fflush(gp); //Clean up Data

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);
}

int main()
{
    // 211208
    // plot("211208", "0");
    // plot("211208", "15");
    // plot("211208", "30");
    // plot("211208", "45");
    // plot("211208", "60");
    // plot("211208", "75");
    // plot("211208", "90");

    // simulation
    plot("simulation_data", "0");
    plot("simulation_data", "15");
    plot("simulation_data", "30");
    plot("simulation_data", "45");
    plot("simulation_data", "60");
    plot("simulation_data", "75");
    plot("simulation_data", "90");
    plot("simulation_data", "105");
    plot("simulation_data", "120");
    plot("simulation_data", "135");
    plot("simulation_data", "150");
    plot("simulation_data", "165");
    plot("simulation_data", "180");
    plot("simulation_data", "195");
    plot("simulation_data", "210");

    return (0);
}