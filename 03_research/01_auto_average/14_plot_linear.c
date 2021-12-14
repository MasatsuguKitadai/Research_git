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
char filename_plot[100];

// range x
double x_min = 0;
double x_max = 1.6;

// range y
double y_min = -0.8;
double y_max = 0.8;

// label
const char *xxlabel = "loadcell voltage [V]";
const char *yylabel = "strain-sensor voltage [V]";
char label[100];

double size;
FILE *gp;

/*********************************   gnuplot   *********************************/
int plot(char date[], char angle[])
{
    sprintf(label, "%s",angle);
    sprintf(filename_dat_1, "result/%s/dat_average/%s_average.dat", date, angle);
    sprintf(filename_dat_2, "result/%s/dat_linear/%s_linear.dat", date, angle);
    sprintf(filename_plot, "result/%s/plot/linear/%s_linear.png", date, angle);

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
    fprintf(gp, "set yrange [%lf:%lf]\n", y_min, y_max);
    fprintf(gp, "set ylabel '%s'offset 0,0.0\n", yylabel);
    fprintf(gp, "set title '%s deg'\n", label);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:2 with lines lc 'blue' notitle, '%s' using 1:3 with lines lc 'red' notitle, '%s' using 4:2 with points lc 'blue' pt 5 ps 2 title 'drag', '%s' using 4:3 with points lc 'red' pt 5 ps 2 title 'lift'\n", filename_dat_2, filename_dat_2, filename_dat_1, filename_dat_1);
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
    plot("simulation_data", "225");
    plot("simulation_data", "240");
    plot("simulation_data", "255");
    plot("simulation_data", "270");
    plot("simulation_data", "285");
    plot("simulation_data", "300");
    plot("simulation_data", "315");
    plot("simulation_data", "330");
    plot("simulation_data", "345");

    return (0);
}