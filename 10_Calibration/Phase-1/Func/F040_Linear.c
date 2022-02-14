/******************************************************************************
PROGRAM NAME :
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
// #include "head.h"

/*********************************   MAIN   *********************************/
int Linear(char date[], char angle[])
{
    /*****************************************************************************/

    // ディレクトリの作成
    char directoryname_1[100];
    char directoryname_2[100];
    char directoryname_dat_1[100];
    char directoryname_dat_2[100];
    char directoryname_csv_1[100];
    char directoryname_csv_2[100];
    char directoryname_png[100];

    /*****************************************************************************/

    // 元ディレクトリの作成
    sprintf(directoryname_1, "../Result/%s/041_Line", date);
    sprintf(directoryname_2, "../Result/%s/042_Gradient", date);
    mkdir(directoryname_1, mode);
    mkdir(directoryname_2, mode);

    /*****************************************************************************/

    // ディレクトリの作成

    sprintf(directoryname_dat_1, "../Result/%s/041_Line/dat", date);
    sprintf(directoryname_dat_2, "../Result/%s/042_Gradient/dat", date);
    sprintf(directoryname_csv_1, "../Result/%s/041_Line/csv", date);
    sprintf(directoryname_csv_2, "../Result/%s/042_Gradient/csv", date);
    sprintf(directoryname_png, "../Result/%s/041_Line/png", date);

    mkdir(directoryname_dat_1, mode);
    mkdir(directoryname_dat_2, mode);
    mkdir(directoryname_csv_1, mode);
    mkdir(directoryname_csv_2, mode);
    mkdir(directoryname_png, mode);

    /*****************************************************************************/

    // ファイルの指定
    char filename_read[100];
    char filename_csv_1[100];
    char filename_csv_2[100];
    char filename_dat_1[100];
    char filename_dat_2[100];

    sprintf(filename_read, "../Result/%s/030_Average/csv/%s.csv", date, angle);
    sprintf(filename_csv_1, "../Result/%s/041_Line/csv/%s.csv", date, angle);
    sprintf(filename_dat_1, "../Result/%s/041_Line/dat/%s.dat", date, angle);
    sprintf(filename_csv_2, "../Result/%s/042_Gradient/csv/%s.csv", date, angle);
    sprintf(filename_dat_2, "../Result/%s/042_Gradient/dat/%s.dat", date, angle);

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
    if (fp == NULL)
    {
        printf("04\t[%s]\tno data file\n", angle);
        return 1;
    }

    i = 0;

    while ((fscanf(fp, "%lf, %lf, %lf", &ch0, &ch1, &ch2)) != EOF)
    {
        // printf("%.3f, %.3f, %.3f\n", ch0, ch1, ch2);
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
    double Result_drag[n];
    double Result_lift[n];

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

    // printf("f[x] = %.3f x + %.3f\t[loadcell - drag]\n", a1[0], b1);

    for (i = 0; i < n; i++)
    {
        Result_drag[i] = a1[0] * i + b1;
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

    // printf("f[x] = %.3f x + %.3f\t[loadcell - lift]\t%.3f\n", a1[1], b1, sqrt_value);

    for (i = 0; i < n; i++)
    {
        Result_lift[i] = a1[1] * i + b1;
    }

    fp_csv = fopen(filename_csv_1, "w");
    fp_dat = fopen(filename_dat_1, "w");

    for (i = 0; i < n; i++)
    {
        fprintf(fp_csv, "%lf,%lf\n", Result_drag[i], Result_lift[i]);
        fprintf(fp_dat, "%d\t%lf\t%lf\n", i, Result_drag[i], Result_lift[i]);
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

    /*****************************************************************************/

    // filename
    char filename_plot[100];

    sprintf(filename_dat_1, "../Result/%s/030_Average/dat/%s.dat", date, angle);
    sprintf(filename_dat_2, "../Result/%s/041_Line/dat/%s.dat", date, angle);
    sprintf(filename_plot, "../Result/%s/041_Line/png/%s.png", date, angle);

    /*****************************************************************************/

    // range x
    double x_min = 0;
    double x_max = 2;

    // range y
    double y_min = -1;
    double y_max = 1;

    // label
    const char *xxlabel = "Loadcell [V]";
    const char *yylabel = "Strain-sensor [V]";
    char label[100];
    double size;

    double angle_2 = 0;

    angle_2 = atoi(angle);
    angle_2 = angle_2;
    sprintf(label, "%0.f", angle_2);

    // size
    size = 1;

    /*****************************************************************************/

    if ((gp = popen("gnuplot", "w")) == NULL)
    {
        printf("gnuplot is not here!\n");
        exit(0); // gnuplotが無い場合、異常ある場合は終了
    }

    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");

    fprintf(gp, "set output '%s'\n", filename_plot);
    // fprintf(gp, "set multiplot\n");
    fprintf(gp, "set key left top\n");
    fprintf(gp, "set key font ',22'\n");
    fprintf(gp, "set term pngcairo size 1280, 960 font ',27'\n");
    // fprintf(gp, "set size ratio %.3f\n", size);

    fprintf(gp, "set lmargin screen 0.10\n");
    fprintf(gp, "set rmargin screen 0.90\n");
    fprintf(gp, "set tmargin screen 0.90\n");
    fprintf(gp, "set bmargin screen 0.15\n");

    fprintf(gp, "set xrange [%.3f:%.3f]\n", x_min, x_max);
    fprintf(gp, "set xlabel '%s'offset 1.0,0\n", xxlabel);
    fprintf(gp, "set yrange [%.3f:%.3f]\n", y_min, y_max);
    fprintf(gp, "set ylabel '%s'offset 1,0.0\n", yylabel);
    fprintf(gp, "set title '%s [deg]'\n", label);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:2 with lines lc 'blue' notitle, '%s' using 1:3 with lines lc 'red' notitle, '%s' using 4:2 with points lc 'blue' pt 5 ps 2 title 'drag', '%s' using 4:3 with points lc 'red' pt 5 ps 2 title 'lift'\n", filename_dat_2, filename_dat_2, filename_dat_1, filename_dat_1);
    fflush(gp); // Clean up Data

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);

    printf("04\t[%s]\t", angle);
    printf("%.3lf\t%.3f\t%.3f\n", a1[0], a1[1], sqrt_value);
}

// int main()
// {
//     // simulation
//     Linear("1-1", "0");
//     Linear("1-1", "15");
//     Linear("1-1", "30");
//     Linear("1-1", "45");
//     Linear("1-1", "60");
//     Linear("1-1", "75");
//     Linear("1-1", "90");
//     Linear("1-1", "105");
//     Linear("1-1", "120");
//     Linear("1-1", "135");
//     Linear("1-1", "150");
//     Linear("1-1", "165");
//     Linear("1-1", "180");
//     Linear("1-1", "195");
//     Linear("1-1", "210");
//     Linear("1-1", "225");
//     Linear("1-1", "240");
//     Linear("1-1", "255");
//     Linear("1-1", "270");
//     Linear("1-1", "285");
//     Linear("1-1", "300");
//     Linear("1-1", "315");
//     Linear("1-1", "330");
//     Linear("1-1", "345");

//     return (0);
// }