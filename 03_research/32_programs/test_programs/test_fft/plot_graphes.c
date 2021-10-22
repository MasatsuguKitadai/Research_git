/******************************************************************************
PROGRAM NAME :plot.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FILE *gp;

const char filename1[100] = "test_data/sin_n=128.dat";
const char filename2[100] = "test_data/sin_n=256.dat";
const char filename3[100] = "test_data/sin_n=128_fft.dat";
const char filename4[100] = "test_data/sin_n=256_fft.dat";

const char graphname1[100] = "graph/sin_n=128.png";
const char graphname2[100] = "graph/sin_n=256.png";
const char graphname3[100] = "graph/sin_n=128_fft.png";
const char graphname4[100] = "graph/sin_n=256_fft.png";

/*********************************   gnuplot   *********************************/
int main()
{

    if ((gp = popen("gnuplot", "w")) == NULL)
    {
        printf("gnuplot is not here!\n");
        exit(0); // gnuplotが無い場合、異常ある場合は終了
    }

    // graph 1 : Sin wave (n=128)

    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
    fprintf(gp, "set output '%s'\n", graphname1);
    // fprintf(gp, "set multiplot\n");
    fprintf(gp, "unset key\n");
    fprintf(gp, "set term pngcairo size 1280, 960 font ',24'\n");
    // fprintf(gp, "set size ratio %lf\n", size);

    fprintf(gp, "set lmargin screen 0.10\n");
    fprintf(gp, "set rmargin screen 0.90\n");
    fprintf(gp, "set tmargin screen 0.90\n");
    fprintf(gp, "set bmargin screen 0.15\n");

    fprintf(gp, "set xrange [0:128]\n");
    fprintf(gp, "set xlabel 'time [s]'offset 0.0,0\n");
    fprintf(gp, "set yrange [-3:3]\n");
    fprintf(gp, "set ylabel 'amplitude [-]'offset 2,0.0\n");
    fprintf(gp, "set title 'Test Sin Wave'\n");

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:2 with lines lc 'black'\n", filename1);

    fflush(gp); //Clean up Data

    // graph 2 : Sin wave (n=256)

    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
    fprintf(gp, "set output '%s'\n", graphname1);
    // fprintf(gp, "set multiplot\n");
    fprintf(gp, "unset key\n");
    fprintf(gp, "set term pngcairo size 1280, 960 font ',24'\n");
    // fprintf(gp, "set size ratio %lf\n", size);

    fprintf(gp, "set lmargin screen 0.10\n");
    fprintf(gp, "set rmargin screen 0.90\n");
    fprintf(gp, "set tmargin screen 0.90\n");
    fprintf(gp, "set bmargin screen 0.15\n");

    fprintf(gp, "set xrange [0:256]\n");
    fprintf(gp, "set xlabel 'time [s]'offset 0.0,0\n");
    fprintf(gp, "set yrange [-3:3]\n");
    fprintf(gp, "set ylabel 'amplitude [-]'offset 2,0.0\n");
    fprintf(gp, "set title 'Test Sin Wave'\n");

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:2 with lines lc 'black'\n", filename2);

    fflush(gp); //Clean up Data

    // graph 3 : FFT (n=128)

    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
    fprintf(gp, "set output '%s'\n", graphname3);
    // fprintf(gp, "set multiplot\n");
    fprintf(gp, "unset key\n");
    fprintf(gp, "set term pngcairo size 1280, 960 font ',24'\n");
    // fprintf(gp, "set size ratio %lf\n", size);

    fprintf(gp, "set lmargin screen 0.10\n");
    fprintf(gp, "set rmargin screen 0.90\n");
    fprintf(gp, "set tmargin screen 0.90\n");
    fprintf(gp, "set bmargin screen 0.15\n");

    fprintf(gp, "set xrange [0:0.5]\n");
    fprintf(gp, "set xlabel 'time [s]'offset 0.0,0\n");
    fprintf(gp, "set yrange [0:300]\n");
    fprintf(gp, "set ylabel 'amplitude [-]'offset 2,0.0\n");
    fprintf(gp, "set title 'Test Sin Wave'\n");

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:2 with lines lc 'black'\n", filename3);

    fflush(gp); //Clean up Data]

    // graph 4 : FFT (n=256)

    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
    fprintf(gp, "set output '%s'\n", graphname4);
    // fprintf(gp, "set multiplot\n");
    fprintf(gp, "unset key\n");
    fprintf(gp, "set term pngcairo size 1280, 960 font ',24'\n");
    // fprintf(gp, "set size ratio %lf\n", size);

    fprintf(gp, "set lmargin screen 0.10\n");
    fprintf(gp, "set rmargin screen 0.90\n");
    fprintf(gp, "set tmargin screen 0.90\n");
    fprintf(gp, "set bmargin screen 0.15\n");

    fprintf(gp, "set xrange [0:0.5]\n");
    fprintf(gp, "set xlabel 'time [s]'offset 0.0,0\n");
    fprintf(gp, "set yrange [0:300]\n");
    fprintf(gp, "set ylabel 'amplitude [-]'offset 2,0.0\n");
    fprintf(gp, "set title 'Test Sin Wave'\n");

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:2 with lines lc 'black'\n", filename4);

    fflush(gp); //Clean up Data
}