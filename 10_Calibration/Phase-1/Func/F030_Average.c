/******************************************************************************
PROGRAM NAME :
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
// #include "head.h"

/*********************************   MAIN   *********************************/
int Average(char date[], char angle[])
{
    /*****************************************************************************/

    // ディレクトリ文字列作成
    char directoryname[100];
    char directoryname_csv[100];
    char directoryname_dat[100];
    char directoryname_png[100];

    /*****************************************************************************/

    // 元ディレクトリの作成
    sprintf(directoryname, "../Result/%s/030_Average", date);
    mkdir(directoryname, mode);

    /*****************************************************************************/

    // ディレクトリの作成
    sprintf(directoryname_dat, "../Result/%s/030_Average/dat", date);
    sprintf(directoryname_csv, "../Result/%s/030_Average/csv", date);
    sprintf(directoryname_png, "../Result/%s/030_Average/png", date);

    mkdir(directoryname_dat, mode);
    mkdir(directoryname_csv, mode);
    mkdir(directoryname_png, mode);

    /*****************************************************************************/

    // ファイルの指定
    char filename_read[100];
    char filename_csv[100];
    char filename_dat[100];

    sprintf(filename_read, "../Result/%s/020_Drift/csv/%s.csv", date, angle);
    sprintf(filename_csv, "../Result/%s/030_Average/csv/%s.csv", date, angle);
    sprintf(filename_dat, "../Result/%s/030_Average/dat/%s.dat", date, angle);

    /*****************************************************************************/

    // 変数宣言
    int i, j, k, l;
    int datalength = 0;
    int ch = 3;
    int data_flame = 5000;
    double value[data_flame][ch];
    double ch0, ch1, ch2; // ch0:drag, ch1:lift, ch2:load-cell
    double time = 0;

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
    if (fp == NULL)
    {
        printf("03\t[%s]\tno data file\n", angle);
        return 1;
    }

    i = 0;

    while ((fscanf(fp, "%lf, %lf, %lf", &ch0, &ch1, &ch2)) != EOF)
    {
        // printf("%.3f, %.3f, %.3f\n", ch0, ch1, ch2);
        value[i][0] = ch0;
        value[i][1] = ch1;
        value[i][2] = ch2;
        i = i + 1;
    }

    fclose(fp);

    datalength = i;
    // printf("datalengh = %d\n", datalength);

    // 計算

    // 変数の宣言

    int count = 300;
    int Average_time[5];
    double sum[3];
    double Average_value[5][3];
    double Average_value_offset[5];
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
            Average_value[i][j] = sum[j] / 150;
        }

        count = count + 325;
        Average_time[i] = count - 400;
        // printf("[%d]\t%.3f\t%.3f\t%.3f\n", Average_time[i], Average_value[i][0], Average_value[i][1], Average_value[i][2]);
        // printf("%d\n", Average_time[i]);
    }

    // ファイルへの書き込み

    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");

    for (i = 0; i < 6; i++)
    {
        time = Average_time[i] * 0.2;
        fprintf(fp_csv, "%lf,%lf,%lf\n", Average_value[i][0], Average_value[i][1], Average_value[i][2]);
        fprintf(fp_dat, "%d\t%lf\t%lf\t%lf\t%.1f\n", Average_time[i], Average_value[i][0], Average_value[i][1], Average_value[i][2], time);
    }

    fclose(fp_csv);
    fclose(fp_dat);

    /*****************************************************************************/
    // Gnupng //

    // ディレクトリの作成

    char directoryname_png_1[100];
    char directoryname_png_2[100];
    char directoryname_png_3[100];

    sprintf(directoryname_png_1, "../Result/%s/030_Average/png/Loadcell", date);
    sprintf(directoryname_png_2, "../Result/%s/030_Average/png/Drag", date);
    sprintf(directoryname_png_3, "../Result/%s/030_Average/png/Lift", date);

    mkdir(directoryname_png_1, mode);
    mkdir(directoryname_png_2, mode);
    mkdir(directoryname_png_3, mode);

    /*****************************************************************************/

    // filename
    char filename_dat_1[100];
    char filename_dat_2[100];
    char filename_png_1[100];
    char filename_png_2[100];
    char filename_png_3[100];

    sprintf(filename_dat_1, "../Result/%s/030_Average/dat/%s.dat", date, angle);
    sprintf(filename_dat_2, "../Result/%s/020_Drift/dat/%s.dat", date, angle);
    sprintf(filename_png_1, "../Result/%s/030_Average/png/Loadcell/%s.png", date, angle);
    sprintf(filename_png_2, "../Result/%s/030_Average/png/Drag/%s.png", date, angle);
    sprintf(filename_png_3, "../Result/%s/030_Average/png/Lift/%s.png", date, angle);

    /*****************************************************************************/

    // range x
    int x_min = 0;
    int x_max = 600;

    // range y
    double y_min = -1;
    double y_max = 1;

    // range y (loadcell)
    double y_min_loadcell = -0.5;
    double y_max_loadcell = 2.5;

    // label
    const char *xxlabel = "Time [s]";
    const char *yylabel = "Output voltage [V]";
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

    // graph : loadcell

    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
    fprintf(gp, "set output '%s'\n", filename_png_1);
    // fprintf(gp, "set multiplot\n");
    fprintf(gp, "set key left top\n");
    fprintf(gp, "set key font ',22'\n");
    fprintf(gp, "set term pngcairo size 1280, 960 font ',27'\n");
    // fprintf(gp, "set size ratio %.3f\n", size);

    fprintf(gp, "set lmargin screen 0.10\n");
    fprintf(gp, "set rmargin screen 0.90\n");
    fprintf(gp, "set tmargin screen 0.90\n");
    fprintf(gp, "set bmargin screen 0.15\n");

    fprintf(gp, "set xrange [%d:%d]\n", x_min, x_max);
    fprintf(gp, "set xlabel '%s'offset 0.0,0\n", xxlabel);
    fprintf(gp, "set yrange [%.3f:%.3f]\n", y_min_loadcell, y_max_loadcell);
    fprintf(gp, "set ylabel '%s'offset 1.0,0.0\n", yylabel);
    fprintf(gp, "set title 'Load cell : %s [deg]'\n", label);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 5:4 with points pt 5 ps 2 lc 'red' title 'Average', '%s' using 8:4 with lines lc 'gray20' title 'Corrected'\n", filename_dat_1, filename_dat_2);
    fflush(gp); // Clean up Data

    // graph : drag

    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
    fprintf(gp, "set output '%s'\n", filename_png_2);
    // fprintf(gp, "set multiplot\n");
    fprintf(gp, "set key left top\n");
    fprintf(gp, "set key font ',22'\n");
    fprintf(gp, "set term pngcairo size 1280, 960 font ',27'\n");
    // fprintf(gp, "set size ratio %.3f\n", size);

    fprintf(gp, "set lmargin screen 0.10\n");
    fprintf(gp, "set rmargin screen 0.90\n");
    fprintf(gp, "set tmargin screen 0.90\n");
    fprintf(gp, "set bmargin screen 0.15\n");

    fprintf(gp, "set xrange [%d:%d]\n", x_min, x_max);
    fprintf(gp, "set xlabel '%s'offset 0.0,0\n", xxlabel);
    fprintf(gp, "set yrange [%.3f:%.3f]\n", y_min, y_max);
    fprintf(gp, "set ylabel '%s'offset 1.0,0.0\n", yylabel);
    fprintf(gp, "set title 'Drag : %s [deg]'\n", label);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 5:2 with points pt 5 ps 2 lc 'red' title 'Average', '%s' using 8:2 with lines lc 'gray20' title 'Corrected'\n", filename_dat_1, filename_dat_2);
    fflush(gp); // Clean up Data

    // graph : lift

    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
    fprintf(gp, "set output '%s'\n", filename_png_3);
    // fprintf(gp, "set multiplot\n");
    fprintf(gp, "set key left top\n");
    fprintf(gp, "set key font ',22'\n");
    fprintf(gp, "set term pngcairo size 1280, 960 font ',27'\n");
    // fprintf(gp, "set size ratio %.3f\n", size);

    fprintf(gp, "set lmargin screen 0.10\n");
    fprintf(gp, "set rmargin screen 0.90\n");
    fprintf(gp, "set tmargin screen 0.90\n");
    fprintf(gp, "set bmargin screen 0.15\n");

    fprintf(gp, "set xrange [%d:%d]\n", x_min, x_max);
    fprintf(gp, "set xlabel '%s'offset 0.0,0\n", xxlabel);
    fprintf(gp, "set yrange [%.3f:%.3f]\n", y_min, y_max_loadcell);
    fprintf(gp, "set ylabel '%s'offset 1.0,0.0\n", yylabel);
    fprintf(gp, "set title 'Lift : %s [deg]'\n", label);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 5:3 with points pt 5 ps 2 lc 'red' title 'Average', '%s' using 8:3 with lines lc 'gray20' title 'Corrected'\n", filename_dat_1, filename_dat_2);
    fflush(gp); // Clean up Data

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);

    printf("03\t[%s]\tsuccess\n", angle);
}

// int main()
// {
//     // simulation
//     Average("1-1", "0");
//     Average("1-1", "15");
//     Average("1-1", "30");
//     Average("1-1", "45");
//     Average("1-1", "60");
//     Average("1-1", "75");
//     Average("1-1", "90");
//     Average("1-1", "105");
//     Average("1-1", "120");
//     Average("1-1", "135");
//     Average("1-1", "150");
//     Average("1-1", "165");
//     Average("1-1", "180");
//     Average("1-1", "195");
//     Average("1-1", "210");
//     Average("1-1", "225");
//     Average("1-1", "240");
//     Average("1-1", "255");
//     Average("1-1", "270");
//     Average("1-1", "285");
//     Average("1-1", "300");
//     Average("1-1", "315");
//     Average("1-1", "330");
//     Average("1-1", "345");

//     return (0);
// }