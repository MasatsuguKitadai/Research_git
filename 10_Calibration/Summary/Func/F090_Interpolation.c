/******************************************************************************
PROGRAM NAME :
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include "head.h"

// double pi = 4 * atan(1.0);

FILE *fp, *fp_dat, *fp_csv, *gp;
/*********************************   MAIN   *********************************/
int Interpolation(char date[], int split)
{
    // ディレクトリの作成
    char directoryname_1[100];
    char directoryname_dat_1[100];
    char directoryname_csv_1[100];
    char directoryname_png[100];

    /*****************************************************************************/

    // 元ディレクトリの作成
    sprintf(directoryname_1, "../Result/%s/090_Interpolation", date);

    mkdir(directoryname_1, mode);

    /*****************************************************************************/

    sprintf(directoryname_dat_1, "../Result/%s/090_Interpolation/dat", date);
    sprintf(directoryname_csv_1, "../Result/%s/090_Interpolation/csv", date);
    sprintf(directoryname_png, "../Result/%s/090_Interpolation/png", date);

    mkdir(directoryname_dat_1, mode);
    mkdir(directoryname_csv_1, mode);
    mkdir(directoryname_png, mode);

    /*****************************************************************************/

    // filename
    char filename_read[100];
    char filename_csv[100];
    char filename_dat[100];
    char filename_csv_average[100];
    char filename_dat_average[100];

    sprintf(filename_read, "../Result/%s/080_Offset/csv/Offset.csv", date);

    sprintf(filename_csv, "../Result/%s/090_Interpolation/csv/Interpolation.csv", date);
    sprintf(filename_dat, "../Result/%s/090_Interpolation/dat/Interpolation.dat", date);

    sprintf(filename_csv_average, "../Result/%s/090_Interpolation/csv/Interpolation-Ave.csv", date);
    sprintf(filename_dat_average, "../Result/%s/090_Interpolation/dat/Interpolation-Ave.dat", date);

    /*****************************************************************************/

    int i = 0;
    double buf;
    double angle[split];
    double angle_buf[split];
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
        angle[i] = buf;
        angle_buf[i] = buf;
        value[i][0] = ch0; // drag
        value[i][1] = ch1; // lift
        value[i][2] = ch2; // sqrt
        // printf("%.1f, %.3f, %.3f, %.3f\n", angle[i], value[i][0], value[i][1], value[i][2]);
        i = i + 1;
    }

    fclose(fp);

    /*****************************************************************************/
    // 使用する点の特定

    double deg[split];
    double difference[split];
    double tmp[2];

    double point[split];
    int j, k;

    double number[split];

    for (i = 0; i < split; i++)
    {
        number[i] = i * 15;
    }

    for (i = 0; i < split; i++)
    {
        if (angle[i] < -7.5)
        {
            angle_buf[i] = angle_buf[i] + 360;
        }
    }

    for (i = 0; i < split; i++)
    {
        for (j = 0; j < split; j++)
        {
            difference[j] = fabs(number[i] - angle_buf[j]);
            // printf("[%.1f]\t= %.3f\n", angle[i], difference[j]);
        }

        for (j = 0; j < split; ++j)
        {
            for (k = j + 1; k < split; ++k)
            {
                if (difference[j] > difference[k])
                {
                    tmp[0] = difference[j];
                    difference[j] = difference[k];
                    difference[k] = tmp[0];

                    tmp[1] = angle_buf[j];
                    angle_buf[j] = angle_buf[k];
                    angle_buf[k] = tmp[1];
                }
            }
        }

        point[i] = angle_buf[0];
        printf("[%.1f]\t= %.1f\n", number[i], point[i]);
    }

    // for (i = 0; i < split; i++)
    // {
    //     printf("[%d] = %.1f \n", i, angle_buf[i]);
    // }

    printf("\n");

    /*****************************************************************************/
    // ラグランジュ補間

    double x[3], y[3][2];
    double result_drag[split];
    double result_lift[split];
    double result_net[split];
    double part[3];

    double sum[3], ave[3];
    int l, m;

    for (i = 0; i < split; i++)
    {
        for (l = 0; l < split; l++)
        {
            if (point[i] == angle[l])
            {
                j = l - 1;
                m = l;
                k = l + 1;

                x[1] = angle[l];

                if (j == -1)
                {
                    j = split - 1;
                    x[0] = angle[j] - 360;
                }
                else
                {
                    x[0] = angle[j];
                }

                if (k == split)
                {
                    k = 0;
                    x[2] = angle[k] + 360;
                }
                else
                {
                    x[2] = angle[k];
                }
            }
            else if (point[i] == angle[l] + 360)
            {
                j = l - 1;
                m = l;
                k = l + 1;

                x[1] = angle[l] + 360;

                if (j == -1)
                {
                    j = split - 1;
                    x[0] = angle[j];
                }
                else
                {
                    x[0] = angle[j] + 360;
                }

                x[2] = angle[k] + 360;
            }
        }

        printf("[%.1f]\t= %.1f\t|\t%.1f\t%.1f\t%.1f\n", number[i], point[i], x[0], x[1], x[2]);
        // printf("[%.1f]\t=%.1f\n[x]\t%.3f\t%.3f\t%.3f\n", number[i], point[i], x[0], x[1], x[2]);

        // drag 方向
        y[0][0] = value[j][0];
        y[2][0] = value[k][0];
        y[1][0] = value[m][0];

        // printf("[y1]\t%.3f\t%.3f\t%.3f\n", y[0][0], y[1][0], y[2][0]);

        part[0] = (number[i] - x[1]) * (number[i] - x[2]) / ((x[0] - x[1]) * (x[0] - x[2]));
        part[1] = (number[i] - x[0]) * (number[i] - x[2]) / ((x[1] - x[0]) * (x[1] - x[2]));
        part[2] = (number[i] - x[0]) * (number[i] - x[1]) / ((x[2] - x[0]) * (x[2] - x[1]));

        result_drag[i] = part[0] * y[0][0] + part[1] * y[1][0] + part[2] * y[2][0];

        // lift 方向
        y[0][1] = value[j][1];
        y[1][1] = value[m][1];
        y[2][1] = value[k][1];

        // printf("[y]\t%.3f\t%.3f\t%.3f\n\n", y[0][1], y[1][1], y[2][1]);

        result_lift[i] = part[0] * y[0][1] + part[1] * y[1][1] + part[2] * y[2][1];

        result_net[i] = sqrt(result_drag[i] * result_drag[i] + result_lift[i] * result_lift[i]);

        // printf("[%.1f]\t%.3f\t%.3f\t%.3f\n", point[i], result_drag[i], result_lift[i], result_net[i]);

        sum[0] = result_drag[i] + sum[0];
        sum[1] = result_lift[i] + sum[1];
        sum[2] = result_net[i] + sum[2];
    }

    ave[0] = sum[0] / split;
    ave[1] = sum[1] / split;
    ave[2] = sum[2] / split;

    /*****************************************************************************/

    // plot用 データファイルの書き出し

    double angle_double;

    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");

    for (i = 0; i < split; i++)
    {
        fprintf(fp_csv, "%.1f,%lf,%lf,%lf\n", number[i], result_drag[i], result_lift[i], result_net[i]);
        fprintf(fp_dat, "%.1f\t%.3f\t%.3f\t%.3f\n", number[i], result_drag[i], result_lift[i], result_net[i]);
        // printf("%.3f\t%.3f\t%.3f\t%.3f\n", angle_double, value[i][0], value[i][1], value[i][2]);
    }

    fclose(fp_csv);
    fclose(fp_dat);

    fp_csv = fopen(filename_csv_average, "w");
    fp_dat = fopen(filename_dat_average, "w");

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
    sprintf(filename_png_1, "../Result/%s/090_Interpolation/png/Interpolation.png", date);

    /*****************************************************************************/

    // range x
    double x_min = -30;
    double x_max = 360;
    double interval = 30;

    // range y
    double y_min = -0.8;
    double y_max = 0.8;

    // label
    const char *xxlabel = "Phi [deg]";
    const char *yylabel_1 = "Voltage gradient [-]";
    const char *yylabel_2 = "Net voltage [-]";
    char label_1[100] = "Gradient value (interpolated)";
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
    fprintf(gp, "plot '%s' using 1:2 with points lc 'blue' pt 5 ps 2 title 'Offset corrected : Drag', '%s' using 1:3 with points lc 'red' pt 5 ps 2 title 'Offset corrected : Lift'\n", filename_dat, filename_dat);
    fflush(gp); // Clean up Data

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);

    printf("\n12\t\tsuccess\n");
}

int main()
{
    // simulation
    Interpolation("1", 24);

    return (0);
}