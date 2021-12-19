/******************************************************************************
PROGRAM NAME :
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>

FILE *fp, *fp_dat, *fp_csv, *gp;
/*********************************   MAIN   *********************************/
int average(char date[], char angle[])
{
    /*****************************************************************************/
    // ディレクトリの作成
    char directoryname_csv[100];
    char directoryname_dat[100];

    sprintf(directoryname_dat, "../result/%s/dat/03_average", date);
    sprintf(directoryname_csv, "../result/%s/csv/03_average", date);

    mkdir(directoryname_dat, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_csv, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    /*****************************************************************************/

    // ファイルの指定
    char filename_read[100];
    char filename_csv[100];
    char filename_dat[100];

    sprintf(filename_read, "../result/%s/csv/02_drift/02_%s.csv", date, angle);
    sprintf(filename_csv, "../result/%s/csv/03_average/03_%s.csv", date, angle);
    sprintf(filename_dat, "../result/%s/dat/03_average/03_%s.dat", date, angle);

    printf("【%s】\n", angle);

    /*****************************************************************************/

    // 変数宣言
    int i, j, k, l;
    int datalength = 0;
    int ch = 3;
    int data_flame = 5000;
    double value[data_flame][ch];
    double ch0, ch1, ch2; // ch0:drag, ch1:lift, ch2:load-cell

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

        for (j = count; j < count + 150; j++)
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

        count = count + 175;
        average_time[i] = count - 250;
        printf("[%d]\t%lf\t%lf\t%lf\n", average_time[i], average_value[i][0], average_value[i][1], average_value[i][2]);
        // printf("%d\n", average_time[i]);
    }

    // ファイルへの書き込み

    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");

    for (i = 0; i < 6; i++)
    {
        fprintf(fp_csv, "%lf,%lf,%lf\n", average_value[i][0], average_value[i][1], average_value[i][2]);
        fprintf(fp_dat, "%d\t%lf\t%lf\t%lf\n", average_time[i], average_value[i][0], average_value[i][1], average_value[i][2]);
    }

    fclose(fp_csv);
    fclose(fp_dat);

    /*****************************************************************************/
    // Gnuplot //

    // ディレクトリの作成

    char directoryname_plot_1[100];
    char directoryname_plot_2[100];
    char directoryname_plot_3[100];

    sprintf(directoryname_plot_1, "../result/%s/plot/03-1_loadcell", date);
    sprintf(directoryname_plot_2, "../result/%s/plot/03-2_drag", date);
    sprintf(directoryname_plot_3, "../result/%s/plot/03-3_lift", date);

    mkdir(directoryname_plot_1, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_plot_2, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_plot_3, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    /*****************************************************************************/

    // filename
    char filename_dat_1[100];
    char filename_dat_2[100];
    char filename_plot_1[100];
    char filename_plot_2[100];
    char filename_plot_3[100];

    sprintf(filename_dat_1, "../result/%s/dat/03_average/03_%s.dat", date, angle);
    sprintf(filename_dat_2, "../result/%s/dat/02_drift/02_%s.dat", date, angle);
    sprintf(filename_plot_1, "../result/%s/plot/03-1_loadcell/03_loadcell_average_%s.png", date, angle);
    sprintf(filename_plot_2, "../result/%s/plot/03-2_drag/03_drag_average_%s.png", date, angle);
    sprintf(filename_plot_3, "../result/%s/plot/03-3_lift/03_lift_average_%s.png", date, angle);

    /*****************************************************************************/

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
    char label_loadcell[100];
    char label_drag[100];
    char label_lift[100];

    double size;

    sprintf(label_loadcell, "%s deg (loadcell)", angle);
    sprintf(label_drag, "%s deg (drag)", angle);
    sprintf(label_lift, "%s deg (lift)", angle);

    /*****************************************************************************/

    // size
    size = 1;

    if ((gp = popen("gnuplot", "w")) == NULL)
    {
        printf("gnuplot is not here!\n");
        exit(0); // gnuplotが無い場合、異常ある場合は終了
    }

    // graph : loadcell

    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
    fprintf(gp, "set output '%s'\n", filename_plot_1);
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
    fprintf(gp, "set yrange [%lf:%lf]\n", y_min_loadcell, y_max_loadcell);
    fprintf(gp, "set ylabel '%s'offset 0.5,0.0\n", yylabel);
    fprintf(gp, "set title '%s '\n", label_loadcell);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:4 with points pt 5 ps 2 lc 'red' title 'average', '%s' using 1:4 with lines lc 'gray20' title 'corrected'\n", filename_dat_1, filename_dat_2);
    fflush(gp); // Clean up Data

    // graph : drag

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
    fprintf(gp, "set ylabel '%s'offset 0.5,0.0\n", yylabel);
    fprintf(gp, "set title '%s '\n", label_drag);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:2 with points pt 5 ps 2 lc 'red' title 'average', '%s' using 1:2 with lines lc 'gray20' title 'corrected'\n", filename_dat_1, filename_dat_2);
    fflush(gp); // Clean up Data

    // graph : lift

    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
    fprintf(gp, "set output '%s'\n", filename_plot_3);
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
    fprintf(gp, "set ylabel '%s'offset 0.5,0.0\n", yylabel);
    fprintf(gp, "set title '%s '\n", label_lift);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:3 with points pt 5 ps 2 lc 'red' title 'average', '%s' using 1:3 with lines lc 'gray20' title 'corrected'\n", filename_dat_1, filename_dat_2);
    fflush(gp); // Clean up Data

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);
}

// int main()
// {
//     // simulation
//     average("testdata", "0");
//     average("testdata", "15");
//     average("testdata", "30");
//     average("testdata", "45");
//     average("testdata", "60");
//     average("testdata", "75");
//     average("testdata", "90");
//     average("testdata", "105");
//     average("testdata", "120");
//     average("testdata", "135");
//     average("testdata", "150");
//     average("testdata", "165");
//     average("testdata", "180");
//     average("testdata", "195");
//     average("testdata", "210");
//     average("testdata", "225");
//     average("testdata", "240");
//     average("testdata", "255");
//     average("testdata", "270");
//     average("testdata", "285");
//     average("testdata", "300");
//     average("testdata", "315");
//     average("testdata", "330");
//     average("testdata", "345");

//     return (0);
// }