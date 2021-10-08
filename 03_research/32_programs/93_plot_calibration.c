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

// csvファイル名
char filename1[100] = "../31_data/calibration/dat/load.dat";
char filename2[100] = "../31_data/calibration/dat/x-axis.dat";
char filename3[100] = "../31_data/calibration/dat/y-axis.dat";
char filename4[100] = "../31_data/calibration/dat/load_least-squares.dat";

// pngファイル名
char graphname1[100] = "../33_result/calibration/01_load.png";
char graphname2[100] = "../33_result/calibration/02_length-sensors_x-axis.png";
char graphname3[100] = "../33_result/calibration/03_length-sensors_y-axis.png";
char graphname4[100] = "../33_result/calibration/04_strainsensor-loadcell_x-axis.png";    
char graphname5[100] = "../33_result/calibration/05_strainsensor-loadcell_y-axis.png";
char graphname6[100] = "../33_result/calibration/06_load-leastsquares.png";

/*********************************   gnuplot   *********************************/
int main()
{
    // size
    size = 1;

    if ((gp = popen("gnuplot", "w")) == NULL)
    {
        printf("gnuplot is not here!\n");
        exit(0); // gnuplotが無い場合、異常ある場合は終了
    }

    #include "plot/11.h"
    #include "plot/12.h"

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);

}
