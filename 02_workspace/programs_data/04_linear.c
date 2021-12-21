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
int linear(char date[], char angle[])
{
    /*****************************************************************************/
    // ディレクトリの作成
    char directoryname_dat_1[100];
    char directoryname_dat_2[100];
    char directoryname_csv_1[100];
    char directoryname_csv_2[100];

    sprintf(directoryname_dat_1, "../result/%s/dat/04-1_linear", date);
    sprintf(directoryname_dat_2, "../result/%s/dat/04-2_gradient", date);
    sprintf(directoryname_csv_1, "../result/%s/csv/04-1_linear", date);
    sprintf(directoryname_csv_2, "../result/%s/csv/04-2_gradient", date);

    mkdir(directoryname_dat_1, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_dat_2, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_csv_1, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_csv_2, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    /*****************************************************************************/

    // ファイルの指定
    char filename_read[100];
    char filename_csv_1[100];
    char filename_csv_2[100];
    char filename_dat_1[100];
    char filename_dat_2[100];

    sprintf(filename_read, "../result/%s/csv/03_average/03_%s.csv", date, angle);
    sprintf(filename_csv_1, "../result/%s/csv/04-1_linear/04-1_%s.csv", date, angle);
    sprintf(filename_dat_1, "../result/%s/dat/04-1_linear/04-1_%s.dat", date, angle);
    sprintf(filename_csv_2, "../result/%s/csv/04-2_gradient/04-2_%s.csv", date, angle);
    sprintf(filename_dat_2, "../result/%s/dat/04-2_gradient/04-2_%s.dat", date, angle);

    // printf("【%s】\n", angle);

    /*****************************************************************************/

    // 変数宣言
    int i, j, k, l;
    int datalength = 0;
    int ch = 3;
    int data_flame = 6;
    double average_value[data_flame][ch];
    double ch0, ch1, ch2, ch3; // ch0:drag, ch1:lift, ch2:load-cell

    // 配列の初期化

    for (i = 0; i < data_flame; i++)
    {
        for (j = 0; j < 3; j++)
        {
            average_value[i][j] = 0;
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
        average_value[i][0] = ch0;
        average_value[i][1] = ch1;
        average_value[i][2] = ch2;
        i = i + 1;
    }

    fclose(fp);

    datalength = i;
    // printf("datalengh = %d\n", datalength);

    // 計算

    int n = 3;
    double result_drag[n];
    double result_lift[n];

    double a1[2], b1, sqrt_value;
    double sum1, sum2, sum3, sum4;

    // 近似直線の計算(drag)
    a1[0] = 0;
    b1 = 0;
    sum1 = 0;
    sum2 = 0;
    sum3 = 0;
    sum4 = 0;

    for (i = 0; i < datalength; i++)
    {
        sum1 = sum1 + average_value[i][2];
        sum2 = sum2 + average_value[i][0];
        sum3 = sum3 + (average_value[i][2] * average_value[i][2]);
        sum4 = sum4 + (average_value[i][2] * average_value[i][0]);
    }

    a1[0] = (datalength * sum4 - sum1 * sum2) / (datalength * sum3 - sum1 * sum1);
    b1 = (sum3 * sum2 - sum4 * sum1) / (datalength * sum3 - sum1 * sum1);

    // printf("f[x] = %lf x + %lf\t[loadcell - drag]\n", a1[0], b1);

    for (i = 0; i < n; i++)
    {
        result_drag[i] = a1[0] * i + b1;
    }

    // 近似直線の計算(lift)
    a1[1] = 0;
    b1 = 0;
    sum1 = 0;
    sum2 = 0;
    sum3 = 0;
    sum4 = 0;

    for (i = 0; i < datalength - 1; i++)
    {
        sum1 = sum1 + average_value[i][2];
        sum2 = sum2 + average_value[i][1];
        sum3 = sum3 + (average_value[i][2] * average_value[i][2]);
        sum4 = sum4 + (average_value[i][2] * average_value[i][1]);
    }

    a1[1] = (datalength * sum4 - sum1 * sum2) / (datalength * sum3 - sum1 * sum1);
    b1 = (sum3 * sum2 - sum4 * sum1) / (datalength * sum3 - sum1 * sum1);

    sqrt_value = sqrt((a1[0] * a1[0]) + (a1[1] * a1[1]));

    // printf("f[x] = %lf x + %lf\t[loadcell - lift]\t%lf\n", a1[1], b1, sqrt_value);

    for (i = 0; i < n; i++)
    {
        result_lift[i] = a1[1] * i + b1;
    }

    fp_csv = fopen(filename_csv_1, "w");
    fp_dat = fopen(filename_dat_1, "w");

    for (i = 0; i < n; i++)
    {
        fprintf(fp_csv, "%lf,%lf\n", result_drag[i], result_lift[i]);
        fprintf(fp_dat, "%d\t%lf\t%lf\n", i, result_drag[i], result_lift[i]);
    }

    fclose(fp_csv);
    fclose(fp_dat);

    fp_dat = fopen(filename_dat_2, "w");
    fp_csv = fopen(filename_csv_2, "w");

    fprintf(fp_csv, "%lf,%lf,%lf\n", a1[0], a1[1], sqrt_value);
    fprintf(fp_dat, "%lf\t%lf\t%lf\n", a1[0], a1[1], sqrt_value);

    fclose(fp_csv);
    fclose(fp_dat);

    /*****************************************************************************/
    // Gnuplot //

    // ディレクトリの作成

    char directoryname_plot[100];

    sprintf(directoryname_plot, "../result/%s/plot/04", date);
    mkdir(directoryname_plot, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    /*****************************************************************************/

    // filename
    char filename_plot[100];

    sprintf(filename_dat_1, "../result/%s/dat/03_average/03_%s.dat", date, angle);
    sprintf(filename_dat_2, "../result/%s/dat/04-1_linear/04-1_%s.dat", date, angle);
    sprintf(filename_plot, "../result/%s/plot/04/04_linear_%s.png", date, angle);

    /*****************************************************************************/

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

    /*****************************************************************************/

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
    fflush(gp); // Clean up Data

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);

    printf("04\t[%s]\tsuccess\n", angle);

}

// int main()
// {
//     // simulation
//     linear("testdata", "0");
//     linear("testdata", "15");
//     linear("testdata", "30");
//     linear("testdata", "45");
//     linear("testdata", "60");
//     linear("testdata", "75");
//     linear("testdata", "90");
//     linear("testdata", "105");
//     linear("testdata", "120");
//     linear("testdata", "135");
//     linear("testdata", "150");
//     linear("testdata", "165");
//     linear("testdata", "180");
//     linear("testdata", "195");
//     linear("testdata", "210");
//     linear("testdata", "225");
//     linear("testdata", "240");
//     linear("testdata", "255");
//     linear("testdata", "270");
//     linear("testdata", "285");
//     linear("testdata", "300");
//     linear("testdata", "315");
//     linear("testdata", "330");
//     linear("testdata", "345");

//     return (0);
// }