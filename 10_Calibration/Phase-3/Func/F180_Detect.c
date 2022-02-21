/******************************************************************************
PROGRAM NAME : sin_wave_maker.c
AUTHER  : masatsugu Kitadai
DATE    :
******************************************************************************/

#include "head.h"

/*********************************   MAIN   *********************************/
void Detect_part1(char date[], double *average_value, double *real, double *imagine, double *power, double *rotation_1, double *rotation_2)
{
    // ファイルの指定

    char filename_read_1[100];
    char filename_read_2[100];
    char filename_read_3[100];
    char filename_read_4[100];

    sprintf(filename_read_1, "../../Phase-2/Result/%s/060_Summary/csv/Summary-Ave.csv", date);
    sprintf(filename_read_2, "../../Phase-2/Result/%s/170_DFT_net-voltage/csv/DFT_net-voltage.csv", date);
    sprintf(filename_read_3, "../../Phase-2/Result/%s/120_Phase-angle_drag/csv/Phase-angle_drag.csv", date);
    sprintf(filename_read_4, "../../Phase-2/Result/%s/130_Phase-angle_lift/csv/Phase-angle_lift.csv", date);

    int range = 24;
    int i = 0;
    int j = 0;
    double re[range], im[range], pw[range];
    double ch0, ch1, ch2, ch3;

    /*****************************************************************************/

    fp = fopen(filename_read_1, "r");
    if (fp == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    fscanf(fp, "%lf,%lf,%lf", &ch0, &ch1, &ch2);
    printf("【Average】\t%.3f\t%.3f\t%.3f\n", ch0, ch1, ch2);
    *average_value = ch2; // sqrt average

    fclose(fp);

    /*****************************************************************************/

    fp = fopen(filename_read_2, "r");
    if (fp == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    while ((fscanf(fp, "%lf,%lf,%lf,%lf", &ch0, &ch1, &ch2, &ch3)) != EOF)
    {
        re[i] = ch1;
        im[i] = ch2;
        pw[i] = ch3;

        i = i + 1;
    }

    fclose(fp);

    /*****************************************************************************/

    *real = re[2];
    *imagine = im[2];
    *power = pw[2];

    fp = fopen(filename_read_3, "r");
    if (fp == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    fscanf(fp, "%lf,%lf", &ch0, &ch1);
    *rotation_1 = (ch1 - 180) / 180 * pi; // sqrt average

    fclose(fp);

    /*****************************************************************************/

    fp = fopen(filename_read_4, "r");
    if (fp == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    fscanf(fp, "%lf,%lf", &ch0, &ch1);
    *rotation_2 = (ch1 - 90) / 180 * pi; // sqrt average

    fclose(fp);

    /*****************************************************************************/
}

void Detect_part2(char date[], double Theta_1, double Theta_2, double average_value, double *real, double *imagine, double *power)
{
    double buf, angle;
    int angle_int;
    int i;
    int range = 24;

    // sin波の配列
    double wave_net[3900];
    double wave_drag_1[3900];
    double wave_drag_2[3900];
    double wave_drag_sum[3900];
    double wave_lift_1[3900];
    double wave_lift_2[3900];
    double wave_lift_sum[3900];

    double theta[2];
    double phi[3900];

    double sum[3];
    double ave[3];

    double half = average_value / 2;

    for (i = 0; i < 3; i++)
    {
        sum[i] = 0;
        ave[i] = 0;
    }

    /*****************************************************************************/

    for (i = 0; i < 3900; i++)
    {
        buf = i;
        phi[i] = pi / 1800 * (i - 300);
        theta[0] = pi / 180 * (Theta_1);
        theta[1] = pi / 180 * (Theta_2);

        wave_drag_1[i] = -half * cos(phi[i]);
        wave_drag_2[i] = -half * cos(phi[i] + theta[0]);
        wave_drag_sum[i] = wave_drag_1[i] + wave_drag_2[i];

        wave_lift_1[i] = -half * sin(phi[i]);
        wave_lift_2[i] = -half * sin(phi[i] + theta[1]);
        wave_lift_sum[i] = wave_lift_1[i] + wave_lift_2[i];

        wave_net[i] = sqrt(wave_drag_sum[i] * wave_drag_sum[i] + wave_lift_sum[i] * wave_lift_sum[i]);
    }

    /*****************************************************************************/

    double wave_net_2[24];

    for (i = 0; i < 24; i++)
    {
        buf = i * 150;
        angle = buf / 10;
        angle_int = angle;
        wave_net_2[i] = wave_net[angle_int * 10];
    }

    /*****************************************************************************/

    double ps[24], as;
    double value_R[24], value_I[24];

    for (i = 0; i < 24; i++)
    {
        value_R[i] = wave_net_2[i] - average_value;
        value_I[i] = 0;
    }

    S_dft(value_R, value_I, range, 1);

    for (i = 0; i < range; i++)
    {
        if (value_R[i] == -0)
        {
            value_R[i] = -1 * value_R[i];
        }
        else if (value_I[i] == -0)
        {
            value_I[i] = -1 * value_I[i];
        }

        ps[i] = value_R[i] * value_R[i] + value_I[i] * value_I[i];    /* パワースペクトル  */
        as = sqrt(value_R[i] * value_R[i] + value_I[i] * value_I[i]); /* 振幅スペクトル  */
        // fq = (double)i / (dt * (double)range);
    }

    // printf("[%.1f, %.1f]\tvalue_Re = %.3f \tvalue_Im = %.3f\t pw: %.3f\n", Theta_1, Theta_2, value_R[2], value_I[2], ps[2]);

    *real = value_R[2];
    *imagine = value_I[2];
    *power = ps[2];
}

void Detect_part3(char date[], double Theta_1, double Theta_2)
{
    /*****************************************************************************/

    // ディレクトリの作成
    char directoryname_1[100];

    /*****************************************************************************/

    // 元ディレクトリの作成
    sprintf(directoryname_1, "../Result/%s/180_Detect", date);

    mkdir(directoryname_1, mode);

    /*****************************************************************************/

    char directoryname_dat_1[100];
    char directoryname_csv_1[100];
    char directoryname_png[100];

    sprintf(directoryname_dat_1, "../Result/%s/180_Detect/dat", date);
    sprintf(directoryname_csv_1, "../Result/%s/180_Detect/csv", date);
    sprintf(directoryname_png, "../Result/%s/180_Detect/png", date);

    mkdir(directoryname_dat_1, mode);
    mkdir(directoryname_csv_1, mode);
    mkdir(directoryname_png, mode);

    /*****************************************************************************/

    // ファイルの指定

    char filename_read_1[100];
    char filename_read_2[100];

    char filename_csv_1[100];
    char filename_csv_2[100];
    char filename_csv_3[100];
    char filename_csv_4[100];

    char filename_dat_1[100];
    char filename_dat_2[100];
    char filename_dat_3[100];
    char filename_dat_4[100];

    sprintf(filename_read_1, "../../Phase-2/Result/%s/060_Summary/csv/Summary-Ave.csv", date);
    sprintf(filename_read_2, "../../Phase-2/Result/%s/170_DFT_net-voltage/csv/DFT_net-voltage.csv", date);

    sprintf(filename_csv_1, "../Result/%s/180_Detect/csv/Detect.csv", date);
    sprintf(filename_dat_1, "../Result/%s/180_Detect/dat/Detect.dat", date);

    sprintf(filename_csv_2, "../Result/%s/180_Detect/csv/Detect-Ave.csv", date);
    sprintf(filename_dat_2, "../Result/%s/180_Detect/dat/Detect-Ave.dat", date);

    sprintf(filename_csv_3, "../Result/%s/180_Detect/csv/Detect-DFT.csv", date);
    sprintf(filename_dat_3, "../Result/%s/180_Detect/dat/Detect-DFT.dat", date);

    sprintf(filename_csv_4, "../Result/%s/180_Detect/csv/Detect-deg.csv", date);
    sprintf(filename_dat_4, "../Result/%s/180_Detect/dat/Detect-deg.dat", date);

    /*****************************************************************************/

    double ch0, ch1, ch2, ch3;
    double average_value;

    fp = fopen(filename_read_1, "r");
    if (fp == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    fscanf(fp, "%lf,%lf,%lf", &ch0, &ch1, &ch2);
    // printf("【Average】\t%.3f\t%.3f\t%.3f\n", ch0, ch1, ch2);
    average_value = ch2; // sqrt average

    fclose(fp);

    /*****************************************************************************/

    int range = 24;
    int i = 0;
    int j = 0;
    double re[range], im[range], net[range];

    fp = fopen(filename_read_2, "r");
    if (fp == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    while ((fscanf(fp, "%lf,%lf,%lf,%lf", &ch0, &ch1, &ch2, &ch3)) != EOF)
    {
        re[i] = ch1;
        im[i] = ch2;
        net[i] = ch3;

        i = i + 1;
    }

    fclose(fp);

    /*****************************************************************************/

    double buf, angle;
    int angle_int;

    // sin波の配列
    double wave_net[3900];
    double wave_drag_1[3900];
    double wave_drag_2[3900];
    double wave_drag_sum[3900];
    double wave_lift_1[3900];
    double wave_lift_2[3900];
    double wave_lift_sum[3900];

    double theta[2];
    double phi[3900];

    double sum[3];
    double ave[3];

    double half = average_value / 2;

    for (i = 0; i < 3; i++)
    {
        sum[i] = 0;
        ave[i] = 0;
    }

    /*****************************************************************************/

    for (i = 0; i < 3900; i++)
    {
        buf = i;
        phi[i] = pi / 1800 * (i - 300);
        theta[0] = pi / 180 * (Theta_1);
        theta[1] = pi / 180 * (Theta_2);

        wave_drag_1[i] = -half * cos(phi[i]);
        wave_drag_2[i] = -half * cos(phi[i] + theta[0]);
        wave_drag_sum[i] = wave_drag_1[i] + wave_drag_2[i];

        wave_lift_1[i] = -half * sin(phi[i]);
        wave_lift_2[i] = -half * sin(phi[i] + theta[1]);
        wave_lift_sum[i] = wave_lift_1[i] + wave_lift_2[i];

        wave_net[i] = sqrt(wave_drag_sum[i] * wave_drag_sum[i] + wave_lift_sum[i] * wave_lift_sum[i]);
    }

    /*****************************************************************************/

    double degree = 0;

    for (i = 0; i < 3900; i++)
    {
        sum[0] = sum[0] + wave_drag_sum[i];
        sum[1] = sum[1] + wave_lift_sum[i];
        sum[2] = sum[2] + wave_net[i];

        ave[0] = sum[0] / 3900;
        ave[1] = sum[1] / 3900;
        ave[2] = sum[2] / 3900;
    }

    fp_csv = fopen(filename_csv_1, "w");
    fp_dat = fopen(filename_dat_1, "w");

    for (i = 0; i < 3900; i++)
    {
        buf = i;
        angle = (buf - 300) / 10;

        fprintf(fp_csv, "%.1f,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n", angle, wave_drag_1[i], wave_drag_2[i], wave_drag_sum[i], wave_lift_1[i], wave_lift_2[i], wave_lift_sum[i], wave_net[i]);
        fprintf(fp_dat, "%.1f\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", angle, wave_drag_1[i], wave_drag_2[i], wave_drag_sum[i], wave_lift_1[i], wave_lift_2[i], wave_lift_sum[i], wave_net[i]);
    }

    fclose(fp_csv);
    fclose(fp_dat);

    /*****************************************************************************/

    fp_csv = fopen(filename_csv_2, "w");
    fp_dat = fopen(filename_dat_2, "w");

    fprintf(fp_csv, "%.lf,%.lf,%.lf\n", ave[0], ave[1], ave[2]);
    fprintf(fp_dat, "-30\t%.1f\t%lf\t%lf\n", ave[0], ave[1], ave[2]);
    fprintf(fp_dat, "360\t%.1f\t%lf\t%lf\n", ave[0], ave[1], ave[2]);

    fclose(fp_csv);
    fclose(fp_dat);

    /*****************************************************************************/

    // printf("\n【Net voltage】\n\n");

    double wave_net_2[24];

    for (i = 0; i < 24; i++)
    {
        buf = i * 150;
        angle = buf / 10;
        angle_int = angle;
        wave_net_2[i] = wave_net[angle_int * 10];

        // printf("[%d]\t%d\t%.3f\n", i, angle_int, wave_net_2[i]);
    }

    /*****************************************************************************/

    printf("---------------------------------------------------------------------------\n\n");
    printf("【 DFT 】\n");

    double ps[24], as;
    double value_R[24], value_I[24];
    int fq;

    for (i = 0; i < 24; i++)
    {
        value_R[i] = wave_net_2[i] - average_value;
        value_I[i] = 0;
    }

    S_dft(value_R, value_I, range, 1);

    fp_csv = fopen(filename_csv_3, "w");
    fp_dat = fopen(filename_dat_3, "w");

    for (i = 0; i < range; i++)
    {
        if (value_R[i] == -0)
        {
            value_R[i] = -1 * value_R[i];
        }
        else if (value_I[i] == -0)
        {
            value_I[i] = -1 * value_I[i];
        }

        ps[i] = value_R[i] * value_R[i] + value_I[i] * value_I[i];    /* パワースペクトル  */
        as = sqrt(value_R[i] * value_R[i] + value_I[i] * value_I[i]); /* 振幅スペクトル  */
        // fq = (double)i / (dt * (double)range);
        fq = i;

        printf("[%d]\tvalue_Re = %.3f \tvalue_Im = %.3f\t pw: %.3f\tfq :%d\n", i, value_R[i], value_I[i], ps[i], fq);

        fprintf(fp_csv, "%d,%lf,%lf,%lf\n", i, value_R[i], value_I[i], ps[i]);
        fprintf(fp_dat, "%d\t%lf\t%lf\t%lf\n", i, value_R[i], value_I[i], ps[i]);
    }

    fclose(fp_csv);
    fclose(fp_dat);

    /*****************************************************************************/

    fp_csv = fopen(filename_csv_4, "w");
    fp_dat = fopen(filename_dat_4, "w");

    fprintf(fp_csv, "%.1f,%.1f\n", Theta_1, Theta_2);
    fprintf(fp_dat, "%.1f\t%.1f\n", Theta_1, Theta_2);

    fclose(fp_csv);
    fclose(fp_dat);

    /*****************************************************************************/

    // Gnuplot //

    /*****************************************************************************/

    // filename
    char filename_plot_1[100];
    char filename_plot_2[100];
    char filename_plot_3[100];

    sprintf(filename_dat_1, "../Result/%s/180_Detect/dat/Detect.dat", date);
    sprintf(filename_dat_2, "../Result/%s/180_Detect/dat/Detect-Ave.dat", date);
    sprintf(filename_plot_1, "../Result/%s/180_Detect/png/Drag.png", date);
    sprintf(filename_plot_2, "../Result/%s/180_Detect/png/Lift.png", date);
    sprintf(filename_plot_3, "../Result/%s/180_Detect/png/Net.png", date);

    /*****************************************************************************/

    // range x
    double x_min = -30;
    double x_max = 360;
    double interval = 30;

    // range y
    double y_min = -1.2;
    double y_max = 1.2;

    // label
    const char *xxlabel = "Angle [deg]";
    const char *yylabel_1 = "Gradient of voltage [V/V]";
    const char *yylabel_2 = "Net output voltage [V/V]";
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
    fprintf(gp, "plot '%s' using 1:2 with lines lc 'royalblue' title 'Drag (1)', '%s' using 1:3 with lines lc 'orangered' title 'Drag (2)', '%s' using 1:4 with lines lc 'magenta' title 'Drag sum'\n", filename_dat_1, filename_dat_1, filename_dat_1);
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
    fprintf(gp, "set yrange [%.3f:%.3f]\n", y_min, y_max);
    fprintf(gp, "set ylabel '%s'offset 1,0.0\n", yylabel_1);
    fprintf(gp, "set title '%s'\n", label_1);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:5 with lines lc 'royalblue' title 'Lift (1)', '%s' using 1:6 with lines lc 'orangered' title 'Lift (2)', '%s' using 1:7 with lines lc 'magenta' title 'Lift sum'\n", filename_dat_1, filename_dat_1, filename_dat_1);
    fflush(gp); // Clean up Data

    // 3枚目

    fprintf(gp, "set output '%s'\n", filename_plot_3);
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
    fprintf(gp, "set yrange [0.5:0.7]\n");
    fprintf(gp, "set ylabel '%s'offset 1,0.0\n", yylabel_2);
    fprintf(gp, "set ytics 0.02\n");
    fprintf(gp, "set title '%s'\n", label_2);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:8 with lines lc 'green' title 'Net voltage', '%s' using 1:4 with lines lc 'grey' title 'Average'\n", filename_dat_1, filename_dat_2);
    fflush(gp); // Clean up Data

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);
}

void Detect()
{
    double net_ave;
    double real_part[2];
    double imaginary_part[2];
    double power_spectrum[2];
    double rotation[2];

    Detect_part1("1", &net_ave, &real_part[0], &imaginary_part[0], &power_spectrum[0], &rotation[0], &rotation[1]);

    printf("Average = %lf\n", net_ave);
    printf("Re : %lf\tIm : %lf\tPw : %lf\n", real_part[0], imaginary_part[0], power_spectrum[0]);
    printf("theta 1 : %lf\ttheta 2 : %lf\n", rotation[0], rotation[1]);
    double theta_x, theta_y;
    double buf;

    int i, j;
    int k = 0;

    for (i = -50; i < 50; i++)
    {
        buf = i;
        theta_x = buf / 10;

        for (j = -50; j < 50; j++)
        {
            buf = j;
            theta_y = buf / 10;
            Detect_part2("1", theta_x, theta_y, net_ave, &real_part[1], &imaginary_part[1], &power_spectrum[1]);

            if (power_spectrum[0] > power_spectrum[1] * 0.99 && power_spectrum[0] < power_spectrum[1] * 1.01)
            {
                printf("[%.1f, %.1f]\tvalue_Re = %.3f \tvalue_Im = %.3f\t pw: %.3f\n", theta_x, theta_y, real_part[1], imaginary_part[1], power_spectrum[1]);

                if (real_part[0] > real_part[1] * 0.99 && real_part[0] < real_part[1] * 1.01)
                {
                    printf("\n[%.1f, %.1f]\tvalue_Re = %.3f \tvalue_Im = %.3f\t pw: %.3f\n", theta_x, theta_y, real_part[1], imaginary_part[1], power_spectrum[1]);

                    // if (imaginary_part[0] + 0.0005 > imaginary_part[1] && imaginary_part[0] - 0.0005 < imaginary_part[1])
                    // {
                    //     Detect_part3("1", theta_x, theta_y);
                    //     k = 1;
                    // }

                    Detect_part3("1", theta_x, theta_y);
                    k = 1;
                    break;
                }
            }
        }

        if (k == 1)
        {
            break;
        }
    }
}

void main()
{
    Detect();
}