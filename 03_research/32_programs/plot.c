/******************************************************************************
PROGRAM NAME :plot.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int x_min = -50;
int x_max = 750;

// drag
int y_min1 = -3;
int y_max1 = 3;

// lift
int y_min2 = -3;
int y_max2 = 3;

// label
const char *xxlabel = "time [s]";
const char *yylabel = "output [V]";

// ファイル名の作成
char filename1[100];
char filename2[100];
char filename3[100];
char label[100];

double size;
FILE *fp1, *fp2;
FILE *gp;

/*********************************   gnuplot   *********************************/
int plot(char name[] ,char date[], char label_name[])
{
    #include "setting_files/range.h"            // それぞれのデータの範囲指定

    // #include "setting_files/raw_data.h"      // 生データ
    // #include "setting_files/moving_average.h"   // 移動平均
    // #include "setting_files/median.h"           // 中央値

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
    fprintf(gp, "plot '%s' using 1:2 with lines lc 'black', 0 lc 'red'\n", filename1);

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

    // 直線 (y=0)

    // fprintf(gp, "f1(x) = 0\n");

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:3 with lines lc 'black', 0 lc 'red'\n", filename1);

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
