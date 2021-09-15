/******************************************************************************
PROGRAM NAME :plot.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "files/fp.h"

// range x
int x_min = -50;
int x_max = 750;

// label
const char *xxlabel = "time [s]";
const char *yylabel = "output [V]";
char label[100];

double size;
FILE *gp;

/*********************************   gnuplot   *********************************/
int plot(char name[], char date[], char label_name[])
{
    // 生データ
    // #include "files/raw_data.h"
    // sprintf(label, "%s", label_name);

    // 移動平均
    #include "files/moving_average.h"
    sprintf(label, "%s  Ma (%d)", label_name, range_ma); 

    // 中央値
    // #include "files/median.h"
    // sprintf(label, "%s  Me (%d)", label_name, range_me); s

    // size
    size = 1;

    if ((gp = popen("gnuplot", "w")) == NULL)
    {
        printf("gnuplot is not here!\n");
        exit(0); // gnuplotが無い場合、異常ある場合は終了
    }

    //PNG image drag

    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
    fprintf(gp, "set output '%s'\n", filename2);
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
    fprintf(gp, "set yrange [%d:%d]\n", y_min1, y_max1);
    fprintf(gp, "set ylabel '%s'offset 0,0.0\n", yylabel);
    fprintf(gp, "set title '%s drag'\n", label);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:2 with lines lc 'black', '%s' using 1:2 with points pt 5 ps 2 lc 'blue', '%s' using 1:2 with points pt 5 ps 2 lc 'blue', 0 lc 'dark-grey'\n", filename1, filename5, filename7);

    fflush(gp); //Clean up Data

    // PNG image lift

    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
    fprintf(gp, "set output '%s'\n", filename3);
    fprintf(gp, "unset key\n");
    fprintf(gp, "set term pngcairo size 1280, 960 font ',24'\n");
    // fprintf(gp, "set size ratio %lf\n", size);

    fprintf(gp, "set lmargin screen 0.10\n");
    fprintf(gp, "set rmargin screen 0.90\n");
    fprintf(gp, "set tmargin screen 0.90\n");
    fprintf(gp, "set bmargin screen 0.15\n");

    fprintf(gp, "set xrange [%d:%d]\n", x_min, x_max);
    fprintf(gp, "set xlabel '%s'offset 0.0,0\n", xxlabel);
    fprintf(gp, "set yrange [%d:%d]\n", y_min2, y_max2);
    fprintf(gp, "set ylabel '%s'offset 0,0.0\n", yylabel);
    fprintf(gp, "set title '%s lift'\n", label);

    // fprintf(gp, "set samples 10000\n");
    // fprintf(gp, "plot '%s' using 1:3 with lines lc 'black', 0 lc 'red'\n", filename1);
    fprintf(gp, "plot '%s' using 1:3 with lines lc 'black', '%s' using 3:4 with points pt 5 ps 2 lc 'blue', '%s' using 3:4 with points pt 5 ps 2 lc 'blue', 0 lc 'dark-grey'\n", filename1, filename5, filename7);

    fflush(gp); //Clean up Data

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);
}

int main()
{
    // y軸範囲の設定に注意!!

    plot("C1", "210806", "C1");
    plot("Groove_A", "210806", "Groove A");
    plot("Groove_B", "210806", "Groove B");
    plot("Groove_C", "210806", "Groove C");
    plot("Groove_D", "210806", "Groove D");
    plot("Normal", "210806", "Normal");
    plot("R1_17.9", "210806", "R1 17.9");
    plot("R1_18.6", "210806", "R1 18.3");
    plot("R1_19.3", "210806", "R1 19.3");

    return (0);
}
