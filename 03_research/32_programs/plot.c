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

double size;
FILE *fp1, *fp2;
FILE *gp;
/*********************************   gnuplot   *********************************/
int plot(char filename1[], char filename2[], char filename3[])
{
    const char *xxlabel = "time [s]";
    const char *yylabel = "output [V]";

    // size
    size = 1;

    if ((gp = popen("gnuplot", "w")) == NULL)
    {
        printf("gnuplot is not here!\n");
        exit(0); // gnuplotが無い場合、異常ある場合は終了
    }

    //PNG image drag

    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
    fprintf(gp, "set output '%s_drag.png'\n", filename2);
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
    fprintf(gp, "set title '%s drag'\n", filename3);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:2 with lines lc 'black'\n", filename1);

    fflush(gp); //Clean up Data

    // PNG image lift

    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
    fprintf(gp, "set output '%s_lift.png'\n", filename2);
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
    fprintf(gp, "set title '%s lift'\n", filename3);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:3 with lines lc 'black'\n", filename1);

    fflush(gp); //Clean up Data

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);
}

int main()
{
    // y軸範囲の設定に注意!!

    // 生データ プロット

    // plot("..//33_result//210806//raw_data//dat//C1.dat", "..//33_result//210806//raw_data//png//C1", " C1");
    // plot("..//33_result//210806//raw_data//dat//Groove_A.dat", "..//33_result//210806//raw_data//png//Groove_A", " Groove A");
    // plot("..//33_result//210806//raw_data//dat//Groove_B.dat", "..//33_result//210806//raw_data//png//Groove_B", " Groove B");
    // plot("..//33_result//210806//raw_data//dat//Groove_C.dat", "..//33_result//210806//raw_data//png//Groove_C", " Groove C");
    // plot("..//33_result//210806//raw_data//dat//Groove_D.dat", "..//33_result//210806//raw_data//png//Groove_D", " Groove D");
    // plot("..//33_result//210806//raw_data//dat//Normal.dat", "..//33_result//210806//raw_data//png//Normal", " Normal");
    // plot("..//33_result//210806//raw_data//dat//R1_17.9.dat", "..//33_result//210806//raw_data//png//R1_17.9", " R1 17.9");
    // plot("..//33_result//210806//raw_data//dat//R1_18.6.dat", "..//33_result//210806//raw_data//png//R1_18.6", " R1 18.6");
    // plot("..//33_result//210806//raw_data//dat//R1_19.3.dat", "..//33_result//210806//raw_data//png//R1_19.3", " R1 19.3");

    // 移動平均 (全体) プロット

    // plot("..//33_result//210806//moving_average//dat//C1_ma.dat", "..//33_result//210806//moving_average//png//C1_ma", " C1 MA(21)");
    // plot("..//33_result//210806//moving_average//dat//Groove_A_ma.dat", "..//33_result//210806//moving_average//png//Groove_A_ma", " Groove A MA(21)");
    // plot("..//33_result//210806//moving_average//dat//Groove_B_ma.dat", "..//33_result//210806//moving_average//png//Groove_B_ma", " Groove B MA(21)");
    // plot("..//33_result//210806//moving_average//dat//Groove_C_ma.dat", "..//33_result//210806//moving_average//png//Groove_C_ma", " Groove C MA(21)");
    // plot("..//33_result//210806//moving_average//dat//Groove_D_ma.dat", "..//33_result//210806//moving_average//png//Groove_D_ma", " Groove D MA(21)");
    // plot("..//33_result//210806//moving_average//dat//Normal_ma.dat", "..//33_result//210806//moving_average//png//Normal_ma", " Normal MA(21)");
    // plot("..//33_result//210806//moving_average//dat//R1_17.9_ma.dat", "..//33_result//210806//moving_average//png//R1_17.9_ma", " R1 17.9 MA(21)");
    // plot("..//33_result//210806//moving_average//dat//R1_18.6_ma.dat", "..//33_result//210806//moving_average//png//R1_18.6_ma", " R1 18.6 MA(21)");
    // plot("..//33_result//210806//moving_average//dat//R1_19.3_ma.dat", "..//33_result//210806//moving_average//png//R1_19.3_ma", " R1 19.3 MA(21)");

    return (0);
}
