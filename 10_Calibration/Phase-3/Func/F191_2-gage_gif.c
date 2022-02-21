/******************************************************************************
PROGRAM NAME :
AUTHER  : masatsugu Kitadai
DATE    :
******************************************************************************/
#include "head.h"

/*********************************   MAIN   *********************************/

int twogage(char date[], int split, double phi_1, double phi_2)
{
    /*****************************************************************************/

    // ディレクトリの作成
    char directoryname_1[100];
    char directoryname_dat_1[100];
    char directoryname_csv_1[100];
    char directoryname_dat_2[100];
    char directoryname_csv_2[100];
    char directoryname_png_1[100];
    char directoryname_png_2[100];

    /*****************************************************************************/

    sprintf(directoryname_1, "../Result/%s/190_2-gage", date);
    mkdir(directoryname_1, mode);

    /*****************************************************************************/

    sprintf(directoryname_dat_1, "../Result/%s/190_2-gage/dat", date);
    sprintf(directoryname_csv_1, "../Result/%s/190_2-gage/csv", date);
    sprintf(directoryname_png_1, "../Result/%s/190_2-gage/png-1", date);
    sprintf(directoryname_png_2, "../Result/%s/190_2-gage/png-2", date);

    mkdir(directoryname_dat_1, mode);
    mkdir(directoryname_csv_1, mode);
    mkdir(directoryname_png_1, mode);
    mkdir(directoryname_png_2, mode);

    /*****************************************************************************/

    // ファイルの指定
    char filename_read_1[100];
    char filename_read_2[100];
    char filename_read_3[100];
    char filename_read_4[100];

    char filename_csv[100];
    char filename_dat[100];

    char filename_csv_average[100];
    char filename_dat_average[100];

    sprintf(filename_read_1, "../Result/%s/180_Detect/csv/Detect-deg.csv", date);
    sprintf(filename_read_2, "../../Phase-2/Result/%s/140_Rotation/csv/Rotation.csv", date);

    sprintf(filename_csv, "../Result/%s/190_2-gage/csv/2-gage.csv", date);
    sprintf(filename_dat, "../Result/%s/190_2-gage/dat/2-gage.dat", date);
    sprintf(filename_csv_average, "../Result/%s/190_2-gage/csv/2-gage-Ave.csv", date);
    sprintf(filename_dat_average, "../Result/%s/190_2-gage/dat/2-gage-Ave.dat", date);

    /*****************************************************************************/

    int i;
    double num;
    double ch0, ch1, ch2;
    double phi[2];

    fp = fopen(filename_read_1, "r");

    if (fp == NULL)
    {
        printf("Error! I can't open the file No1.\n");
        exit(0);
    }

    fscanf(fp, "%lf, %lf", &ch0, &ch1);

    // phi[0] = ch0 * pi / 180;
    // phi[1] = ch1 * pi / 180;

    phi[0] = phi_1 * pi / 180;
    phi[1] = phi_2 * pi / 180;

    printf("Phi[1] = %.3f\tPhi[2] = %.3f\n", phi_1, phi_2);

    fclose(fp);

    /*****************************************************************************/

    // 値の読み込み

    double sum[3], ave[3];

    for (i = 0; i < 3; i++)
    {
        sum[i] = 0;
        ave[i] = 0;
    }

    double angle[split];
    double voltage_drag[split];
    double voltage_lift[split];

    fp = fopen(filename_read_2, "r");

    if (filename_read_2 == NULL)
    {
        printf("Error! I can't open the file No2.\n");
        exit(0);
    }

    // printf("check\n");

    i = 0;

    // printf("【Raw Data】\n");
    // printf("\t[Drag]\t[Lift]\t[Net]\n");

    while ((fscanf(fp, "%lf,%lf,%lf,%lf", &num, &ch0, &ch1, &ch2)) != EOF)
    {
        angle[i] = num;
        voltage_drag[i] = ch0;
        voltage_lift[i] = ch1;
        // printf("[%.1f]\t%.3f\t%.3f\t%.3f\n", angle[i], voltage_drag[i], voltage_lift[i], ch2);
        i = i + 1;
        sum[0] = ch0 + sum[0];
        sum[1] = ch1 + sum[1];
        sum[2] = ch2 + sum[2];
    }

    fclose(fp);

    ave[0] = sum[0] / split;
    ave[1] = sum[1] / split;
    ave[2] = sum[2] / split;

    // printf("=============================\n");
    // printf("[Ave]\t%.3f\t%.3f\t%.3f\n", ave[0], ave[1], ave[2]);

    // printf("\n");

    /*****************************************************************************/

    double rad[split];
    double voltage_x[split];
    double voltage_y[split];
    double voltage_net[split];

    for (i = 0; i < 3; i++)
    {
        sum[i] = 0;
        ave[i] = 0;
    }

    printf("【Corrected Data】\n");
    printf("=============================\n");
    printf("\t[Drag]\t[Lift]\t[Net]\n");

    for (i = 0; i < split; i++)
    {
        rad[i] = angle[i] * pi / 180;
        voltage_x[i] = 2 * cos(rad[i]) / (cos(rad[i]) + cos(rad[i] - phi[0])) * voltage_drag[i];
        voltage_y[i] = 2 * sin(rad[i]) / (sin(rad[i]) + sin(rad[i] - phi[1])) * voltage_lift[i];

        voltage_y[0] = 0;

        voltage_net[i] = sqrt(voltage_x[i] * voltage_x[i] + voltage_y[i] * voltage_y[i]);
        printf("[%.1f]\t%.3f\t%.3f\t%.3f\n", angle[i], voltage_x[i], voltage_y[i], voltage_net[i]);

        sum[0] = voltage_x[i] + sum[0];
        sum[1] = voltage_y[i] + sum[1];
        sum[2] = voltage_net[i] + sum[2];
    }

    ave[0] = sum[0] / split;
    ave[1] = sum[1] / split;
    ave[2] = sum[2] / split;

    double line[2];

    line[0] = ave[2] * 0.97;
    line[1] = ave[2] * 1.03;

    printf("=============================\n");
    printf("[Ave]\t%.3f\t%.3f\t%.3f\n", ave[0], ave[1], ave[2]);

    /*****************************************************************************/

    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");

    for (i = 0; i < split; i++)
    {
        fprintf(fp_csv, "%.1f,%lf,%lf,%lf\n", angle[i], voltage_x[i], voltage_y[i], voltage_net[i]);
        fprintf(fp_dat, "%.1f\t%.3f\t%.3f\t%.3f\n", angle[i], voltage_x[i], voltage_y[i], voltage_net[i]);
    }

    fclose(fp_csv);
    fclose(fp_dat);

    fp_csv = fopen(filename_csv_average, "w");
    fp_dat = fopen(filename_dat_average, "w");

    fprintf(fp_csv, "%lf,%lf,%lf\n", ave[0], ave[1], ave[2]);
    fprintf(fp_dat, "-30\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\n", ave[0], ave[1], ave[2], line[0], line[1]);
    fprintf(fp_dat, "360\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\n", ave[0], ave[1], ave[2], line[0], line[1]);

    fclose(fp_csv);
    fclose(fp_dat);

    /*****************************************************************************/

    // 分散計算

    long double variance = 0;
    double deviation = 0;
    double sum2 = 0;

    for (i = 0; i < 3; i++)
    {
        sum[i] = 0;
        ave[i] = 0;
    }

    for (i = 0; i < split; i++)
    {
        sum[0] = voltage_x[i] + sum[0];
        sum[1] = voltage_y[i] + sum[1];
        sum[2] = voltage_net[i] + sum[2];
    }

    for (i = 0; i < 3; i++)
    {
        ave[i] = sum[i] / split;
        // printf("[%d]\t%.3f\n", i, ave[i]);
    }

    for (i = 0; i < split; i++)
    {
        sum2 = voltage_net[i] * voltage_net[i] + sum2;
    }

    variance = sum2 / split - ave[2] * ave[2];
    deviation = sqrt(variance);

    printf("\n");
    printf("variance \t= %Lf\n", variance);
    printf("deviation\t= %lf\n\n", deviation);

    /*****************************************************************************/

    // Gnuplot //

    /*****************************************************************************/

    // filename
    char filename_plot_1[100];
    char filename_plot_2[100];

    sprintf(filename_plot_1, "../Result/%s/190_2-gage/png-1/Gradient_%.1f_%.1f.png", date, phi_1, phi_2);
    sprintf(filename_plot_2, "../Result/%s/190_2-gage/png-2/Voltage_%.1f_%.1f.png", date, phi_1, phi_2);

    /*****************************************************************************/

    // 追加の読み込みファイル
    char filename_add[100];

    sprintf(filename_add, "../../Phase-2/Result/%s/150_Adjust/dat/Adjust-plot.dat", date);

    /*****************************************************************************/

    // range x
    double x_min = -30;
    double x_max = 360;
    double interval = 30;

    // range y
    double y_min = -0.8;
    double y_max = 0.8;

    // label
    const char *xxlabel = "Angle [deg]";
    const char *yylabel_1 = "Gradient of voltage [-]";
    const char *yylabel_2 = "Net voltage [-]";
    char label_1[100] = "Gradient value";
    char label_2[100];

    sprintf(label_2, "[%.1f , %.1f]", phi_1, phi_2);

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
    fprintf(gp, "plot '%s' using 1:2 with points lc 'blue' pt 5 ps 2 title 'Corrected : Drag', '%s' using 1:3 with points lc 'red' pt 5 ps 2 title 'Corrected : Lift', '%s' using 1:2 with lines lc 'royalblue' title 'Theoretical : Drag', '%s' using 1:3 with lines lc 'orange' title 'Theoretical : Lift'\n", filename_dat, filename_dat, filename_add, filename_add);
    fflush(gp); // Clean up Data

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
    fprintf(gp, "set ylabel '%s'offset 1.5,0.0\n", yylabel_2);
    fprintf(gp, "set ytics 0.02\n");
    fprintf(gp, "set title '%s'\n", label_2);

    // fprintf(gp, "set samples 10000\n");
    // fprintf(gp, "plot 0.63 with lines lc 'grey20' notitle, '%s' using 1:4 with points lc 'green' pt 5 ps 2 notitle\n", filename_dat);
    fprintf(gp, "plot '%s' using 1:4 with points lc 'green' pt 5 ps 2 title 'corrected', '%s' using 1:4 with lines lc 'red' title 'Average', '%s' using 1:5 with lines lc 'gray40' notitle, '%s' using 1:6 with lines lc 'gray40' notitle\n", filename_dat, filename_dat_average, filename_dat_average, filename_dat_average);
    fflush(gp); // Clean up Data

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);

    printf("\n09\t\tsuccess\n");
}

int main()
{
    int split = 24;
    double phi_x, phi_y;
    double voltage_x[split];
    double voltage_y[split];
    double voltage_net[split];

    // printf("[Parameters]\n");
    // printf("phi x = ");
    // scanf("%lf", &phi_x);
    // printf("phi y = ");
    // scanf("%lf", &phi_y);

    int i, j, k, l;
    double buf;
    double average = 0;
    double sum = 0;

    for (i = -5; i < 6; i++)
    {
        buf = i;
        // phi_x = buf / 10;
        phi_x = i;

        for (j = -5; j < 6; j++)
        {
            buf = j;
            // phi_y = buf / 10;
            phi_y = j;

            twogage("1", split, phi_x, phi_y);
        }
    }
    return (0);
}