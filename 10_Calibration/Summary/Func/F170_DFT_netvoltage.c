/******************************************************************************
PROGRAM NAME :
AUTHER  : masatsugu Kitadai
DATE    :
******************************************************************************/
#include "head.h"

/*********************************   MAIN   *********************************/

int DFT_netvoltage(char date[], int split)
{
    /*****************************************************************************/

    // ディレクトリの作成
    char directoryname[100];
    char directoryname_dat[100];
    char directoryname_csv[100];
    char directoryname_png[100];

    /*****************************************************************************/

    sprintf(directoryname, "../Result/%s/170_DFT_net-voltage", date);
    mkdir(directoryname, mode);

    /*****************************************************************************/

    sprintf(directoryname_dat, "../Result/%s/170_DFT_net-voltage/dat", date);
    sprintf(directoryname_csv, "../Result/%s/170_DFT_net-voltage/csv", date);
    sprintf(directoryname_png, "../Result/%s/170_DFT_net-voltage/png", date);

    mkdir(directoryname_dat, mode);
    mkdir(directoryname_csv, mode);
    mkdir(directoryname_png, mode);

    /*****************************************************************************/

    // ファイルの指定
    char filename_read_1[100];
    char filename_read_2[100];
    char filename_csv[100];
    char filename_dat[100];

    sprintf(filename_read_1, "../Result/%s/140_Rotation/csv/Rotation.csv", date);
    sprintf(filename_read_2, "../Result/%s/140_Rotation/csv/Rotation-Ave.csv", date);

    sprintf(filename_csv, "../Result/%s/170_DFT_net-voltage/csv/DFT_net-voltage.csv", date);
    sprintf(filename_dat, "../Result/%s/170_DFT_net-voltage/dat/DFT_net-voltage.dat", date);

    /*****************************************************************************/

    int i;
    double average;
    double ch0, ch1, ch2, ch3;
    double angle[split];
    double value_x[split];
    double value_y[split];
    double value_net[split];

    fp = fopen(filename_read_1, "r");

    if (fp == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    i = 0;

    while ((fscanf(fp, "%lf, %lf, %lf, %lf", &ch0, &ch1, &ch2, &ch3)) != EOF)
    {
        // printf("[%.1f]\t%.3f\t%.3f\t%.3f\n", ch0, ch1, ch2, ch3);
        angle[i] = ch0;
        value_x[i] = ch1;
        value_y[i] = ch2;
        value_net[i] = ch3;
        i = i + 1;
    }

    fclose(fp);

    fp = fopen(filename_read_2, "r");

    if (fp == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    fscanf(fp, "%lf, %lf, %lf", &ch0, &ch1, &ch2);
    {
        average = ch2;
    }

    fclose(fp);

    /*****************************************************************************/
    double value_R[split];
    double value_I[split];

    for (i = 0; i < split; i++)
    {
        value_R[i] = value_net[i] - average;
        value_I[i] = 0;
    }

    S_dft(value_R, value_I, split, 1);

    /*****************************************************************************/

    double ps[split];

    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");

    for (i = 0; i < split; i++)
    {
        ps[i] = value_R[i] * value_R[i] + value_I[i] * value_I[i];
        printf("[%d]\tvalue_Re = %.3f \tvalue_Im = %.3f\t pw: %.3f\n", i, value_R[i], value_I[i], ps[i]);
        fprintf(fp_dat, "%d\t%lf\t%lf\t%lf\n", i, value_R[i], value_I[i], ps[i]);
        fprintf(fp_csv, "%d,%lf,%lf,%lf\n", i, value_R[i], value_I[i], ps[i]);
    }

    fclose(fp_csv);
    fclose(fp_dat);

    /*****************************************************************************/

    // Gnuplot //

    /*****************************************************************************/

    // filename
    char filename_plot[100];

    sprintf(filename_plot, "../Result/%s/170_DFT_net-voltage/png/DFT_net-voltage.png", date);

    /*****************************************************************************/

    // range x
    double x_min = 0;
    double x_max = 12;
    double interval = 1;

    // range y
    double y_min = 0;
    double y_max = 0.10;

    // label
    const char *xxlabel = "Number of waves [-]";
    const char *yylabel = "Power [-]";
    char label[100] = "DFT (net voltage)";

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
    fprintf(gp, "set key font ',22'\n");
    fprintf(gp, "set term pngcairo size 1280, 960 font ',27'\n");
    // fprintf(gp, "set size ratio %.3f\n", size);

    fprintf(gp, "set lmargin screen 0.10\n");
    fprintf(gp, "set rmargin screen 0.90\n");
    fprintf(gp, "set tmargin screen 0.90\n");
    fprintf(gp, "set bmargin screen 0.15\n");

    fprintf(gp, "set xrange [%.3f:%.3f]\n", x_min, x_max);
    fprintf(gp, "set xlabel '%s'offset 0.0,0\n", xxlabel);
    fprintf(gp, "set xtics %.3f\n", interval);
    fprintf(gp, "set yrange [%.3f:%.3f]\n", y_min, y_max);
    fprintf(gp, "set ylabel '%s'offset 1.5,0.0\n", yylabel);
    fprintf(gp, "set title '%s'\n", label);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:4 with lines lc 'black' notitle \n", filename_dat);
    fflush(gp); // Clean up Data

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);

    printf("\n10\t\tsuccess\n");
}

int main()
{
    DFT_netvoltage("1", 24);
    return (0);
}