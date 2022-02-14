/******************************************************************************
PROGRAM NAME :
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
// #include "head.h"

/*********************************   MAIN   *********************************/
int Summary(char date[], int split)
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
    sprintf(directoryname_1, "../Result/%s/051_Summary", date);
    sprintf(directoryname_2, "../Result/%s/052_Summary-Ave", date);

    mkdir(directoryname_1, mode);
    mkdir(directoryname_2, mode);

    /*****************************************************************************/

    sprintf(directoryname_dat_1, "../Result/%s/051_Summary/dat", date);
    sprintf(directoryname_dat_2, "../Result/%s/052_Summary-Ave/dat", date);
    sprintf(directoryname_csv_1, "../Result/%s/051_Summary/csv", date);
    sprintf(directoryname_csv_2, "../Result/%s/052_Summary-Ave/csv", date);
    sprintf(directoryname_png, "../Result/%s/051_Summary/png", date);

    mkdir(directoryname_dat_1, mode);
    mkdir(directoryname_dat_2, mode);
    mkdir(directoryname_csv_1, mode);
    mkdir(directoryname_csv_2, mode);
    mkdir(directoryname_png, mode);

    /*****************************************************************************/

    // ファイル名作成
    char filename_read[100];
    char filename_csv_1[100];
    char filename_csv_2[100];
    char filename_dat_1[100];
    char filename_dat_2[100];

    sprintf(filename_dat_1, "../Result/%s/051_Summary/dat/Summary.dat", date);
    sprintf(filename_dat_2, "../Result/%s/052_Summary-Ave/dat/Summary-Ave.dat", date);

    sprintf(filename_csv_1, "../Result/%s/051_Summary/csv/Summary.csv", date);
    sprintf(filename_csv_2, "../Result/%s/052_Summary-Ave/csv/Summary-Ave.csv", date);

    int i = 0;
    int angle = 0;
    double angle_double = 0;
    double ch0, ch1, ch2;
    double value[split][3];
    double sum[3];
    double ave[3];

    for (i = 0; i < 3; i++)
    {
        sum[i] = 0;
        ave[i] = 0;
    }

    for (i = 0; i < split; i++)
    {
        angle = i * 360 / split;
        sprintf(filename_read, "../Result/%s/042_Gradient/csv/%d.csv", date, angle);

        fp = fopen(filename_read, "r");
        if (fp == NULL)
        {
            printf("[%d]\tError! I can't open the file.\n\n", angle);
            break;
        }

        fscanf(fp, "%lf, %lf, %lf", &ch0, &ch1, &ch2);
        // printf("【%d】\t%.3f\t%.3f\t%.3f\n", angle, ch0, ch1, ch2);

        value[i][0] = ch0; // drag
        value[i][1] = ch1; // lift
        value[i][2] = ch2; // sqrt

        sum[0] = ch0 + sum[0];
        sum[1] = ch1 + sum[1];
        sum[2] = ch2 + sum[2];

        fclose(fp);
    }

    ave[0] = sum[0] / split;
    ave[1] = sum[1] / split;
    ave[2] = sum[2] / split;

    printf("Average of Drag = %.3f\n", ave[0]);
    printf("Average of Lift = %.3f\n", ave[1]);
    printf("Average of Sqrt = %.3f\n", ave[2]);
    printf("\n");

    // plot用 データファイルの書き出し

    fp_csv = fopen(filename_csv_1, "w");
    fp_dat = fopen(filename_dat_1, "w");

    for (i = 0; i < split; i++)
    {
        angle_double = i * 360 / split;

        fprintf(fp_csv, "%.1f,%.3f,%.3f,%.3f\n", angle_double, value[i][0], value[i][1], value[i][2]);
        fprintf(fp_dat, "%.1f\t%.3f\t%.3f\t%.3f\n", angle_double, value[i][0], value[i][1], value[i][2]);
        // printf("%.3f\t%.3f\t%.3f\t%.3f\n", angle_double, value[i][0], value[i][1], value[i][2]);
    }

    fclose(fp_csv);
    fclose(fp_dat);

    fp_csv = fopen(filename_csv_2, "w");
    fp_dat = fopen(filename_dat_2, "w");

    fprintf(fp_csv, "%.1f,%lf,%lf\n", ave[0], ave[1], ave[2]);
    fprintf(fp_dat, "-30\t%.3f\t%.3f\t%.3f\n", ave[0], ave[1], ave[2]);
    fprintf(fp_dat, "360\t%.3f\t%.3f\t%.3f\n", ave[0], ave[1], ave[2]);

    fclose(fp_csv);
    fclose(fp_dat);

    /*****************************************************************************/

    // Gnuplot //

    // filename
    char filename_plot_1[100];
    char filename_plot_2[100];

    sprintf(filename_dat_1, "../Result/%s/051_Summary/dat/Summary.dat", date);
    sprintf(filename_dat_2, "../Result/%s/052_Summary-Ave/dat/Summary-Ave.dat", date);
    sprintf(filename_plot_1, "../Result/%s/051_Summary/png/Gradient.png", date);
    sprintf(filename_plot_2, "../Result/%s/051_Summary/png/Voltage.png", date);

    /*****************************************************************************/

    // range x
    double x_min = -30;
    double x_max = 360;
    double interval = 30;

    // range y
    double y_min = -0.8;
    double y_max = 0.8;

    // label
    const char *xxlabel = "Theta [deg]";
    const char *yylabel_1 = "Voltage Gradient [-]";
    const char *yylabel_2 = "Net Voltage [-]";
    char label_1[100] = "Gradient value";
    char label_2[100] = "Output voltage";

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

    fprintf(gp, "set output '%s'\n", filename_plot_1);
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
    fprintf(gp, "set ylabel '%s'offset 1,0.0\n", yylabel_1);
    fprintf(gp, "set title '%s'\n", label_1);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:2 with points lc 'blue' pt 5 ps 2 title 'Measured : Drag', '%s' using 1:3 with points lc 'red' pt 5 ps 2 title 'Measured : Lift'\n", filename_dat_1, filename_dat_1);
    fflush(gp); // Clean up Data

    /*****************************************************************************/
    // 2枚目

    fprintf(gp, "set output '%s'\n", filename_plot_2);
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
    fprintf(gp, "set yrange [0.6:0.7]\n");
    fprintf(gp, "set ylabel '%s'offset 1,0.0\n", yylabel_2);
    fprintf(gp, "set ytics 0.02\n");
    fprintf(gp, "set title '%s'\n", label_2);

    // fprintf(gp, "set samples 10000\n");
    // fprintf(gp, "plot 0.63 with lines lc 'grey20' notitle, '%s' using 1:4 with points lc 'green' pt 5 ps 2 notitle\n", filename_dat);
    fprintf(gp, "plot '%s' using 1:4 with points lc 'green' pt 5 ps 2 title 'Net voltage', '%s' using 1:4 with lines lc 'gray40' title 'Average'\n", filename_dat_1, filename_dat_2);
    fflush(gp); // Clean up Data

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);

    printf("05\t\tsuccess\n");
}

// int main()
// {
//     // simulation
//     Summary("1-1", 24);

//     return (0);
// }