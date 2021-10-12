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
char filename1[100] = "../33_result/calibration/dat/force.dat";
char filename2[100] = "../33_result/calibration/dat/x-axis.dat";
char filename3[100] = "../33_result/calibration/dat/y-axis.dat";
char filename4[100] = "../33_result/calibration/dat/x-force.dat";
char filename5[100] = "../33_result/calibration/dat/y-force.dat";
char filename6[100] = "../33_result/calibration/dat/force&line_1.dat";
char filename7[100] = "../33_result/calibration/dat/force&line_2.dat";

// pngファイル名
char graphname1[100] = "../33_result/calibration/graph/01_force.png";
char graphname2[100] = "../33_result/calibration/graph/03_length-output_x.png";
char graphname3[100] = "../33_result/calibration/graph/04_length-output_y.png";
char graphname4[100] = "../33_result/calibration/graph/05_strainsensor-loadcell_x.png";
char graphname5[100] = "../33_result/calibration/graph/06_strainsensor-loadcell_y.png";
char graphname6[100] = "../33_result/calibration/graph/02_force&line.png";
char graphname7[100] = "../33_result/calibration/graph/07_strainsensor-forces.png";
char graphname8[100] = "../33_result/calibration/graph/08_strainsensor-forces&line.png";

/*********************************   gnuplot   *********************************/
int plot_calibration()
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
#include "plot/13.h"

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);
}
