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
int x_min = 0;
int x_max = 2300;

// range y
int y_min = 0;
int y_max = 2;

// label
const char *xxlabel = "time [s]";
const char *yylabel = "output voltage [V]";
char label[100];

double size;
FILE *gp;

/*********************************   gnuplot   *********************************/
int plot(char angle[])
{
    sprintf(label, "%s",angle);
    sprintf(filename_dat_1, "dat_reverse/%s_reverse.dat", angle);
    sprintf(filename_dat_2, "dat_result/%s_average.dat", angle);
    sprintf(filename_plot, "plot/voltage-time/%s.png", angle);

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
    fprintf(gp, "unset key\n");
    fprintf(gp, "set term pngcairo size 1280, 960 font ',24'\n");
    // fprintf(gp, "set size ratio %lf\n", size);

    fprintf(gp, "set lmargin screen 0.10\n");
    fprintf(gp, "set rmargin screen 0.90\n");
    fprintf(gp, "set tmargin screen 0.90\n");
    fprintf(gp, "set bmargin screen 0.15\n");

    fprintf(gp, "set xrange [%d:%d]\n", x_min, x_max);
    fprintf(gp, "set xlabel '%s'offset 0.0,0\n", xxlabel);
    fprintf(gp, "set yrange [%d:%d]\n", y_min, y_max);
    fprintf(gp, "set ylabel '%s'offset 2,0.0\n", yylabel);
    fprintf(gp, "set title '%s deg'\n", label);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:4 with lines lc 'black' notitle, '%s' using 1:3 with points lc 'red' pt 5 ps 2 notitle\n", filename_dat_1, filename_dat_2);
    fflush(gp); //Clean up Data

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);
}

int main()
{
    plot("0");
    // plot("30");
    // plot("60");
    // plot("90");
    // plot("120");
    // plot("150");
    // plot("180");
    // plot("210");
    // plot("240");
    // plot("270");
    // plot("300");
    // plot("330");

    return (0);
}