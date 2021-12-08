/******************************************************************************
PROGRAM NAME :
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

FILE *fp, *fp_dat, *fp_csv, *gp;
/*********************************   MAIN   *********************************/
int auto_average(char angle[])
{
    // 変数宣言
    int i, j, k, l;
    int datalength = 0;
    int ch = 3;
    int data_flame = 5000;
    double value[data_flame][ch];
    double ch0, ch1, ch2; // ch0:drag, ch1:lift, ch2:load-cell

    // 読み込みファイルの指定
    char filename_read[100];
    char filename_csv[100];
    char filename_dat[100];

    sprintf(filename_read, "csv_reverse/%s_reverse.CSV", angle);
    sprintf(filename_csv, "csv_result/%s_average.CSV", angle);
    sprintf(filename_dat, "dat_result/%s_average.dat", angle);
    printf("【%s】\n", angle);

    // 配列の初期化

    for (i = 0; i < data_flame; i++)
    {
        for (j = 0; j < 3; j++)
        {
            value[i][j] = 0;
        }
    }

    // printf("check\n");

    // ファイルの読み込み
    fp = fopen(filename_read, "r");
    if (filename_read == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    i = 0;

    while ((fscanf(fp, "%lf, %lf, %lf", &ch0, &ch1, &ch2)) != EOF)
    {
        // printf("%lf, %lf, %lf\n", ch0, ch1, ch2);
        value[i][0] = ch0;
        value[i][1] = ch1;
        value[i][2] = ch2;
        i = i + 1;
    }

    fclose(fp);

    datalength = i;
    printf("datalengh = %d\n", datalength);

    // 計算

    // 変数の宣言

    int count = 150;
    int average_time[5];
    double sum[3];
    double average_value[5][3];
    double average_value_offset[5];
    double offset;

    for (i = 0; i < 6; i++)
    {
        count = count + 25;

        for (j = 0; j < 3; j++)
        {
            sum[j] = 0;
        }

        for (j = count; j < count + 150 ; j++)
        {
            for (k = 0; k < 3; k++)
            {
                sum[k] = value[j][k] + sum[k];
            }
        }

        count = j;

        for (j = 0; j < 3; j++)
        {
            average_value[i][j] = sum[j] / 150;
        }

        if (i == 0)
        {
            offset = average_value[i][2];
        }

        average_value_offset[i] = average_value[i][2] - offset;

        count = count + 175;
        average_time[i] = count - 250;
        printf("[%d]\t%lf\t%lf\t%lf\t%lf\n", count, average_value[i][0], average_value[i][1], average_value[i][2], average_value_offset[i]);
        // printf("%d\n", average_time[i]);
    }

    // ファイルへの書き込み

    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");

    for (i = 0; i < 6; i++)
    {
        fprintf(fp_csv, "%lf,%lf,%lf\n", average_value_offset[i], average_value[i][0], average_value[i][1]);
        fprintf(fp_dat, "%d\t%lf\t%lf\t%lf\t%lf\n", average_time[i], average_value_offset[i], average_value[i][2], average_value[i][0], average_value[i][1]);
    }

    fclose(fp_csv);
    fclose(fp_dat);

    // plot

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
    auto_average("0");
    // change("30");
    // change("60");
    // change("90");
    // change("120");
    // change("150");
    // change("180");
    // change("210");
    // change("240");
    // change("270");
    // change("300");
    // change("330");

    return (0);
}