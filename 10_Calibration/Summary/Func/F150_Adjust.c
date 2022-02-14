/******************************************************************************
PROGRAM NAME : sin_wave_maker.c
AUTHER  : masatsugu Kitadai
DATE    :
******************************************************************************/
#include "head.h"

/*********************************   MAIN   *********************************/
int Adjust(char date[])
{
    /*****************************************************************************/
    // ディレクトリの作成
    char directoryname[100];
    char directoryname_dat[100];
    char directoryname_csv[100];
    char directoryname_png[100];

    /*****************************************************************************/

    sprintf(directoryname, "../Result/%s/150_Adjust", date);
    mkdir(directoryname, mode);

    /*****************************************************************************/

    sprintf(directoryname_dat, "../Result/%s/150_Adjust/dat", date);
    sprintf(directoryname_csv, "../Result/%s/150_Adjust/csv", date);
    sprintf(directoryname_png, "../Result/%s/150_Adjust/png", date);

    mkdir(directoryname_dat, mode);
    mkdir(directoryname_csv, mode);
    mkdir(directoryname_png, mode);

    /*****************************************************************************/
    // ファイルの指定
    char filename_read[100];
    char filename_csv[100];
    char filename_dat_1[100];
    char filename_dat_2[100];

    sprintf(filename_read, "../Result/%s/060_Summary/csv/Summary-Ave.csv", date);
    sprintf(filename_csv, "../Result/%s/150_Adjust/csv/Adjust.csv", date);
    sprintf(filename_dat_1, "../Result/%s/150_Adjust/dat/Adjust.dat", date);
    sprintf(filename_dat_2, "../Result/%s/150_Adjust/dat/Adjust-plot.dat", date);

    /*****************************************************************************/

    double ch0, ch1, ch2;
    double average_value;

    fp = fopen(filename_read, "r");
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

    int i = 0;
    int max = 3600;
    double wave_drag[3600];
    double wave_lift[3600];
    double angle_1 = 0;
    double angle_2 = 0;

    for (i = 0; i < max; i++)
    {
        angle_1 = (i + 1800) * pi / 1800;
        angle_2 = (i + 900) * pi / 1800;

        wave_drag[i] = cos(angle_1);
        wave_lift[i] = cos(angle_2);
    }

    /*****************************************************************************/

    // 正弦波 drag (位相 π ズレ)
    // printf("Drag\n");
    for (i = 0; i < max; i++)
    {
        wave_drag[i] = wave_drag[i] * average_value;
        // printf("value[%d] = %.3f\n", i, wave_drag[i]);
    }

    // 正弦波 lift (位相 3π/2 ズレ)
    // printf("Lift\n");
    for (i = 0; i < max; i++)
    {
        wave_lift[i] = wave_lift[i] * average_value;
        // printf("value[%d] = %.3f\n", i, wave_lift[i]);
    }

    double angle, buf;

    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat_1, "w");
    fp_plot = fopen(filename_dat_2, "w");

    for (i = 3300; i < 3600; i++)
    {
        buf = i;
        angle = buf / 10;
        angle = angle - 360;
        // printf("angle = %.3f\ti = %d\n", angle, i);
        fprintf(fp_plot, "%lf\t%lf\t%lf\n", angle, wave_drag[i], wave_lift[i]);
    }

    for (i = 0; i < 3600; i++)
    {
        buf = i;
        angle = buf / 10;
        // printf("angle = %.3f\ti = %d\n", angle, i);
        fprintf(fp_csv, "%lf,%lf,%lf\n", angle, wave_drag[i], wave_lift[i]);
        fprintf(fp_dat, "%lf\t%lf\t%lf\n", angle, wave_drag[i], wave_lift[i]);
        fprintf(fp_plot, "%lf\t%lf\t%.3f\n", angle, wave_drag[i], wave_lift[i]);
    }

    fclose(fp_csv);
    fclose(fp_dat);
    fclose(fp_plot);

    /*****************************************************************************/
    // Gnuplot //

    // filename
    char filename_dat_3[100];
    char filename_dat_4[100];
    char filename_dat_5[100];

    char filename_plot_1[100];
    char filename_plot_2[100];
    char filename_plot_3[100];
    char filename_plot_4[100];
    char filename_plot_5[100];
    char filename_plot_6[100];
    char filename_plot_7[100];
    char filename_plot_8[100];
    char filename_plot_9[100];

    sprintf(filename_dat_1, "../Result/%s/060_Summary/dat/Summary.dat", date);
    sprintf(filename_dat_2, "../Result/%s/140_Rotation/dat/Rotation.dat", date);
    sprintf(filename_dat_3, "../Result/%s/150_Adjust/dat/Adjust-plot.dat", date);
    sprintf(filename_dat_4, "../Result/%s/080_Offset/dat/Offset.dat", date);
    sprintf(filename_dat_5, "../Result/%s/090_Interpolation/dat/Interpolation.dat", date);

    sprintf(filename_plot_1, "../Result/%s/150_Adjust/png/Raw-data_drag.png", date);
    sprintf(filename_plot_2, "../Result/%s/150_Adjust/png/Raw-data_lift.png", date);
    sprintf(filename_plot_3, "../Result/%s/150_Adjust/png/Rotation_drag.png", date);
    sprintf(filename_plot_4, "../Result/%s/150_Adjust/png/Rotation_lift.png", date);
    sprintf(filename_plot_5, "../Result/%s/150_Adjust/png/Offset_drag.png", date);
    sprintf(filename_plot_6, "../Result/%s/150_Adjust/png/Offset_lift.png", date);
    sprintf(filename_plot_7, "../Result/%s/150_Adjust/png/Interpolated_drag.png", date);
    sprintf(filename_plot_8, "../Result/%s/150_Adjust/png/Interpolated_lift.png", date);
    sprintf(filename_plot_9, "../Result/%s/150_Adjust/png/Summary.png", date);

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
    const char *yylabel_1 = "Gradient of voltage [V/V]";
    const char *yylabel_2 = "Net output voltage [V/V]";
    char label_1[100] = "Gradient value";
    char label_2[100] = "Output otage";

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

    /*****************************************************************************/

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
    fprintf(gp, "set title '%s (Drag)'\n", label_1);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:2 with points lc 'blue' pt 5 ps 2 title 'Measured (Drag)', '%s' using 1:2 with lines lc 'royalblue' title 'Theoretical (Drag)'\n", filename_dat_1, filename_dat_3);

    fflush(gp); // Clean up Data

    /*****************************************************************************/

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
    fprintf(gp, "set title '%s (Lift)'\n", label_1);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:3 with points lc 'red' pt 5 ps 2 title 'Measured (Lift)', '%s' using 1:3 with lines lc 'orangered' title 'Theoretical (Lift)'\n", filename_dat_1, filename_dat_3);

    fflush(gp); // Clean up Data

    /*****************************************************************************/

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
    fprintf(gp, "set yrange [%.3f:%.3f]\n", y_min, y_max);
    fprintf(gp, "set ylabel '%s'offset 1,0.0\n", yylabel_1);
    fprintf(gp, "set title '%s (Drag)'\n", label_1);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:2 with points lc 'navy' pt 5 ps 2 title 'Corrected (Drag)', '%s' using 1:2 with lines lc 'royalblue' title 'Theoretical (Drag)'\n", filename_dat_2, filename_dat_3);

    fflush(gp); // Clean up Data

    /*****************************************************************************/

    fprintf(gp, "set output '%s'\n", filename_plot_4);
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
    fprintf(gp, "set title '%s (Lift)'\n", label_1);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:3 with points lc 'orange-red' pt 5 ps 2 title 'Corrected (Lift)', '%s' using 1:3 with lines lc 'orange' title 'Theoretical (Lift)'\n", filename_dat_2, filename_dat_3);

    fflush(gp); // Clean up Data

    /*****************************************************************************/

    fprintf(gp, "set output '%s'\n", filename_plot_5);
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
    fprintf(gp, "set title '%s (Drag)'\n", label_1);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:2 with points lc 'navy' pt 5 ps 2 title 'Corrected (Drag)', '%s' using 1:2 with lines lc 'royalblue' title 'Theoretical (Drag)'\n", filename_dat_4, filename_dat_3);

    fflush(gp); // Clean up Data

    /*****************************************************************************/

    fprintf(gp, "set output '%s'\n", filename_plot_6);
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
    fprintf(gp, "set title '%s (Lift)'\n", label_1);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:3 with points lc 'orange-red' pt 5 ps 2 title 'Corrected (Lift)', '%s' using 1:3 with lines lc 'orange' title 'Theoretical (Lift)'\n", filename_dat_4, filename_dat_3);

    fflush(gp); // Clean up Data

    /*****************************************************************************/

    fprintf(gp, "set output '%s'\n", filename_plot_7);
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
    fprintf(gp, "set title '%s (Drag)'\n", label_1);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:2 with points lc 'navy' pt 5 ps 2 title 'Corrected (Drag)', '%s' using 1:2 with lines lc 'royalblue' title 'Theoretical (Drag)'\n", filename_dat_5, filename_dat_3);

    fflush(gp); // Clean up Data

    /*****************************************************************************/

    fprintf(gp, "set output '%s'\n", filename_plot_8);
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
    fprintf(gp, "set title '%s (Lift)'\n", label_1);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:3 with points lc 'orange-red' pt 5 ps 2 title 'Corrected (Lift)', '%s' using 1:3 with lines lc 'orange' title 'Theoretical (Lift)'\n", filename_dat_5, filename_dat_3);

    fflush(gp); // Clean up Data

    /*****************************************************************************/

    fprintf(gp, "set output '%s'\n", filename_plot_9);
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
    fprintf(gp, "plot '%s' using 1:2 with points lc 'navy' pt 5 ps 2 title 'Corrected (Drag)', '%s' using 1:3 with points lc 'orange-red' pt 5 ps 2 title 'Corrected (Lift)', '%s' using 1:2 with lines lc 'royalblue' title 'Theoretical (Drag)', '%s' using 1:3 with lines lc 'orange' title 'Theoretical (Lift)'\n", filename_dat_2, filename_dat_2, filename_dat_3, filename_dat_3);

    fflush(gp); // Clean up Data

    /*****************************************************************************/

    pclose(gp);

    printf("21\t\tsuccess\n");
}

int main()
{
    Adjust("1");
    return (0);
}