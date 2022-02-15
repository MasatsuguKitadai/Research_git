/******************************************************************************
PROGRAM NAME :
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
// #include "head.h"

/*********************************   MAIN   *********************************/
int Offset(char date[], int split, double delta_x, double delta_y)
{
    /*****************************************************************************/

    // ディレクトリの作成
    char directoryname_1[100];
    char directoryname_dat_1[100];
    char directoryname_csv_1[100];
    char directoryname_png[100];

    /*****************************************************************************/

    // 元ディレクトリの作成
    sprintf(directoryname_1, "../Result/%s/081_Offset", date);

    mkdir(directoryname_1, mode);

    /*****************************************************************************/

    sprintf(directoryname_dat_1, "../Result/%s/081_Offset/dat", date);
    sprintf(directoryname_csv_1, "../Result/%s/081_Offset/csv", date);
    sprintf(directoryname_png, "../Result/%s/081_Offset/png", date);

    mkdir(directoryname_dat_1, mode);
    mkdir(directoryname_csv_1, mode);
    mkdir(directoryname_png, mode);

    /*****************************************************************************/

    // filename
    char filename_read[100];
    char filename_csv_1[100];
    char filename_dat_1[100];
    char filename_csv_2[100];
    char filename_dat_2[100];

    sprintf(filename_read, "../Result/%s/061_Summary/csv/Summary.csv", date);

    sprintf(filename_csv_1, "../Result/%s/081_Offset/csv/Offset.csv", date);
    sprintf(filename_dat_1, "../Result/%s/081_Offset/dat/Offset.dat", date);

    sprintf(filename_csv_2, "../Result/%s/081_Offset/csv/Offset-Ave.csv", date);
    sprintf(filename_dat_2, "../Result/%s/081_Offset/dat/Offset-Ave.dat", date);

    /*****************************************************************************/

    int i = 0;
    double buf;
    double angle[split];
    double ch0, ch1, ch2;
    double value[split][3];

    fp = fopen(filename_read, "r");
    if (fp == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    while ((fscanf(fp, "%lf, %lf, %lf, %lf", &buf, &ch0, &ch1, &ch2)) != EOF)
    {
        // printf("%.1f, %.3f, %.3f, %.3f\n", buf, ch0, ch1, ch2);
        angle[i] = buf;
        value[i][0] = ch0; // drag
        value[i][1] = ch1; // lift
        value[i][2] = ch2; // sqrt
        i = i + 1;
    }

    fclose(fp);

    /*****************************************************************************/

    double F[split][3];
    double phi[split], psi[split];
    double alpha[split];
    double r = 25; // 供試体の半径

    double degree[split];
    double sum[3], ave[3];

    for (i = 0; i < 3; i++)
    {
        sum[i] = 0;
        ave[i] = 0;
    }

    printf("\t[Phi]\t[Drag]\t[Lift]\t[Net]\n");

    for (i = 0; i < split; i++)
    {
        phi[i] = pi / 180 * angle[i];

        alpha[i] = -1 * asin((delta_y * sin(phi[i]) - delta_x * cos(phi[i])) / r);
        psi[i] = phi[i] - alpha[i];

        F[i][0] = value[i][0] / cos(alpha[i]);
        F[i][1] = value[i][1] / cos(alpha[i]);
        F[i][2] = sqrt(F[i][0] * F[i][0] + F[i][1] * F[i][1]);

        phi[i] = phi[i] * 180 / pi;
        degree[i] = 180 / pi * psi[i];
        printf("[%.1f]\t%.1f\t%.3f\t%.3f\t%.3f\n", phi[i], degree[i], F[i][0], F[i][1], F[i][2]);

        sum[0] = F[i][0] + sum[0];
        sum[1] = F[i][1] + sum[1];
        sum[2] = F[i][2] + sum[2];
    }

    /*****************************************************************************/

    // plot用 データファイルの書き出し

    double angle_double;

    fp_csv = fopen(filename_csv_1, "w");
    fp_dat = fopen(filename_dat_1, "w");

    for (i = 0; i < split; i++)
    {
        angle_double = i * 150;
        angle_double = angle_double / 10;

        fprintf(fp_csv, "%lf,%lf,%lf,%lf\n", degree[i], F[i][0], F[i][1], F[i][2]);
        fprintf(fp_dat, "%.3f\t%.3f\t%.3f\t%.3f\n", degree[i], F[i][0], F[i][1], F[i][2]);
        // printf("%.3f\t%.3f\t%.3f\t%.3f\n", angle_double, value[i][0], value[i][1], value[i][2]);
    }

    fclose(fp_csv);
    fclose(fp_dat);

    ave[0] = sum[0] / split;
    ave[1] = sum[1] / split;
    ave[2] = sum[2] / split;

    fp_csv = fopen(filename_csv_2, "w");
    fp_dat = fopen(filename_dat_2, "w");

    fprintf(fp_csv, "%lf,%lf,%lf\n", ave[0], ave[1], ave[2]);
    fprintf(fp_dat, "-30\t%.3f\t%.3f\t%.3f\n", ave[0], ave[1], ave[2]);
    fprintf(fp_dat, "360\t%.3f\t%.3f\t%.3f\n", ave[0], ave[1], ave[2]);

    fclose(fp_csv);
    fclose(fp_dat);

    /*****************************************************************************/

    // Gnuplot //

    /*****************************************************************************/

    // filename
    char filename_png_1[100];
    sprintf(filename_png_1, "../Result/%s/081_Offset/png/Offset.png", date);

    /*****************************************************************************/

    // range x
    double x_min = -30;
    double x_max = 360;
    double interval = 30;

    // range y
    double y_min = -0.15;
    double y_max = 0.15;

    // label
    const char *xxlabel = "Theta [deg]";
    const char *yylabel_1 = "Force [N/V]";
    const char *yylabel_2 = "Net force [N/V]";
    char label_1[100] = "Gradient value";
    char label_2[100] = "Force";

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

    fprintf(gp, "set xrange [%.3f:%.3f]\n", x_min, x_max);
    fprintf(gp, "set xlabel '%s'offset 0.0,0\n", xxlabel);
    fprintf(gp, "set xtics %.3f\n", interval);
    fprintf(gp, "set yrange [%.3f:%.3f]\n", y_min, y_max);
    fprintf(gp, "set ylabel '%s'offset 1,0.0\n", yylabel_1);
    fprintf(gp, "set title '%s'\n", label_1);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:2 with points lc 'blue' pt 5 ps 2 title 'Offset corrected : Drag', '%s' using 1:3 with points lc 'red' pt 5 ps 2 title 'Offset corrected : Lift'\n", filename_dat_1, filename_dat_1);
    fflush(gp); // Clean up Data

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);

    printf("\n11\t\tsuccess\n");
}

// int main()
// {
//     // simulation
//     Offset("1", 24, 0.06, 0.08);

//     return (0);
// }