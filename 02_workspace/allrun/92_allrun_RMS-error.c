/******************************************************************************
PROGRAM NAME :allrun_testdata.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/

#include <sys/stat.h>
#include "../programs/00_dft.c"
#include "../programs/06_evaluation.c"
#include "../programs/20-2_wave-adjuster_sim.c"

/*****************************************************************************/

/** DFT **/
#include "../programs/07-3_dft_drag.c"
#include "../programs/07-4_dft_lift.c"
#include "../programs/08-3_dft_phase-angle_drag.c"
#include "../programs/08-4_dft_phase-angle_lift.c"
// #include "../programs/09-2_dft_net-voltage_ver2.c"
#include "../programs/09-3_dft_net-voltage_sim.c"
#include "../programs/10-2_dft-offset.c"
#include "../programs/11_correct-offset.c"
#include "../programs/12_interpolation.c"
#include "../programs/21-3_sim_wave-adjuster_ver2.c"
#include "../programs/27-3_wave_dft_drag.c"
#include "../programs/27-4_wave_dft_lift.c"
#include "../programs/28-3_wave_dft_phase-angle_drag.c"
#include "../programs/28-4_wave_dft_phase-angle_lift.c"
#include "../programs/30_Error.c"

/*****************************************************************************/

// simulater
#include "../programs/90_simulater.c"

/*********************************   MAIN   *********************************/
int main()
{
    char dataname[50];
    char filename[100];
    int range_angle = 150;
    int split_angle = 24;
    double x, y;
    double theta_1, theta_2;

    theta_1 = 0;
    theta_2 = 0;

    sprintf(dataname, "Interpolation_error");

    /*****************************************************************************/

    // ディレクトリの作成
    char directoryname[100];
    sprintf(directoryname, "../result/%s", dataname);
    mkdir(directoryname, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    sprintf(directoryname, "../result/%s/dat", dataname);
    mkdir(directoryname, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    sprintf(directoryname, "../result/%s/plot", dataname);
    mkdir(directoryname, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    /*****************************************************************************/

    int i = 0;
    int j = 0;
    double buf_1, buf_2;
    int range = 50;

    double ch0, ch1;

    double theory[2];
    double error[2];

    theory[0] = 90;
    theory[1] = 180;

    char filename_read_1[100];
    char filename_read_2[100];

    sprintf(filename, "../result/%s/dat/error_%d.dat", dataname, range);
    sprintf(dataname, "simulation_error");

    for (i = 0; i < range; i++)
    {
        buf_1 = i;
        x = buf_1 / 10;

        for (j = 0; j < range; j++)
        {
            buf_2 = j;
            y = buf_2 / 10;

            // ディレクトリの作成
            sprintf(directoryname, "../result/%s", dataname);
            mkdir(directoryname, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

            // simulater
            simulater(dataname, split_angle, x, y, theta_1, theta_2);

            printf("\n---------------------------------------------------------------------------\n\n");

            // 06_evaluation
            evaluation(dataname, split_angle);

            printf("\n---------------------------------------------------------------------------\n\n");

            // 11_correct-offset
            correct_offset(dataname, split_angle, x, y);

            printf("\n---------------------------------------------------------------------------\n\n");

            // 12_interpolation
            interpolation(dataname, split_angle);

            printf("\n---------------------------------------------------------------------------\n\n");

            // 07-1_fft_drag
            calculate_drag(dataname, split_angle);

            printf("\n---------------------------------------------------------------------------\n\n");

            // 08-1_phase-angle_drag
            phase_angle_drag(dataname);

            printf("\n---------------------------------------------------------------------------\n\n");

            // 07-2_fft_lift
            calculate_lift(dataname, split_angle);

            printf("\n---------------------------------------------------------------------------\n\n");

            // 08-2_phase-angle_lift
            phase_angle_lift(dataname);

            printf("\n---------------------------------------------------------------------------\n\n");

            // 09_net-voltage
            netvoltage(dataname, range_angle, split_angle);

            printf("\n---------------------------------------------------------------------------\n\n");

            // 10_dft-offset
            offset(dataname, split_angle);

            printf("\n---------------------------------------------------------------------------\n\n");

            // 20_wave-adjuster
            waveadjuster(dataname);

            printf("\n---------------------------------------------------------------------------\n\n");

            // 21_wave-adjuster_ver2
            waveadjuster_ver2(dataname);

            printf("\n---------------------------------------------------------------------------\n\n");

            // 27-1_wave_fft_drag
            calculate_drag_theory(dataname, split_angle);

            printf("\n---------------------------------------------------------------------------\n\n");

            // 28-1_wave_phase-angle_drag
            phase_angle_drag_theory(dataname);

            printf("\n---------------------------------------------------------------------------\n\n");

            // 27-2_wave_fft_lift
            calculate_lift_theory(dataname, split_angle);

            printf("\n---------------------------------------------------------------------------\n\n");

            // 28-2_wave_phase-angle_lift
            phase_angle_lift_theory(dataname);

            printf("\n---------------------------------------------------------------------------\n\n");

            // 30_Error
            RMSE(dataname);

            printf("\n---------------------------------------------------------------------------\n\n");

            /*****************************************************************************/

            sprintf(filename_read_1, "../result/%s/csv/08-3_phase-angle_drag/08-3.csv", dataname);
            sprintf(filename_read_2, "../result/%s/csv/08-4_phase-angle_lift/08-4.csv", dataname);

            /*****************************************************************************/

            fp = fopen(filename_read_1, "r");
            if (fp == NULL)
            {
                printf("no data file\n");
                return 1;
            }
            fscanf(fp, "%lf, %lf", &ch0, &ch1);

            error[0] = ch0 * 180 / pi - 90;

            fclose(fp);

            /*****************************************************************************/

            fp = fopen(filename_read_2, "r");
            if (fp == NULL)
            {
                printf("no data file\n");
                return 1;
            }

            fscanf(fp, "%lf, %lf", &ch0, &ch1);

            error[0] = ch0 * 180 / pi;

            fclose(fp);

            /*****************************************************************************/

            fp = fopen(filename, "a");

            fprintf(fp, "%.2f\t%.2f\t%.3f\t%.3f\n", x, y, error[0], error[1]);

            fclose(fp);

            /*****************************************************************************/
        }
    }

    /*****************************************************************************/
    // Gnuplot //

    // ディレクトリの作成
    char filename_plot_1[100];
    char filename_plot_2[100];

    sprintf(filename_plot_1, "../result/%s/plot/map_drag.png", dataname);
    sprintf(filename_plot_2, "../result/%s/plot/map_drag.png", dataname);

    /*****************************************************************************/

    // range x
    double x_min = 0;
    int x_max = range / 100;

    // range y
    double y_min = 0;
    double y_max = 10;

    // label
    char label[100] = "";
    char xxlabel[100] = "delta y";
    char yylabel[100] = "delta x";

    double size;

    char cb_label = "Error [deg]";
    double cb_min = 10;
    double cb_max = 0;

    /*****************************************************************************/

    if ((gp = popen("gnuplot", "w")) == NULL)
    {
        printf("gnuplot is not here!\n");
        exit(0); // gnuplotが無い場合、異常ある場合は終了
    }

    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");

    fprintf(gp, "set output '%s'\n", filename_plot_1);
    fprintf(gp, "set multiplot\n");
    fprintf(gp, "set key left top\n");
    fprintf(gp, "set key font ',22'\n");
    fprintf(gp, "set term pngcairo size 1280, 960 font ',27'\n");

    fprintf(gp, "set lmargin screen 0.10\n");
    fprintf(gp, "set rmargin screen 0.90\n");
    fprintf(gp, "set tmargin screen 0.90\n");
    fprintf(gp, "set bmargin screen 0.15\n");

    fprintf(gp, "set xrange [%.3f:%d]\n", x_min, x_max);
    fprintf(gp, "set xlabel '%s'offset 0.0,0\n", xxlabel);
    fprintf(gp, "set xtics 1\n");
    fprintf(gp, "set yrange [%.3f:%.3f]\n", y_min, y_max);
    fprintf(gp, "set ylabel '%s'offset 1,0.0\n", yylabel);
    fprintf(gp, "set title '%s (drag)'\n", label);

    fprintf(gp, "set cblabel '%s'offset 0.0,0.0\n", cb_label);
    fprintf(gp, "set cbrange['%d':'%d']\n", cb_min, cb_max);
    fprintf(gp, "set palette rgbformulae 22,13,-31\n");

    fprintf(gp, "set pm3d map\n"); // <steps in scan>,<steps between scans>

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "splot '%s' using 1:2:3 with  pm3d notitle\n", filename_dat);
    fflush(gp); // Clean up Data

    /*****************************************************************************/

    fprintf(gp, "set output '%s'\n", filename_plot_2);
    fprintf(gp, "set multiplot\n");
    fprintf(gp, "set key left top\n");
    fprintf(gp, "set key font ',22'\n");
    fprintf(gp, "set term pngcairo size 1280, 960 font ',27'\n");

    fprintf(gp, "set lmargin screen 0.10\n");
    fprintf(gp, "set rmargin screen 0.90\n");
    fprintf(gp, "set tmargin screen 0.90\n");
    fprintf(gp, "set bmargin screen 0.15\n");

    fprintf(gp, "set xrange [%.3f:%d]\n", x_min, x_max);
    fprintf(gp, "set xlabel '%s'offset 0.0,0\n", xxlabel);
    fprintf(gp, "set xtics 1\n");
    fprintf(gp, "set yrange [%.3f:%.3f]\n", y_min, y_max);
    fprintf(gp, "set ylabel '%s'offset 1,0.0\n", yylabel);
    fprintf(gp, "set title '%s (drag)'\n", label);

    fprintf(gp, "set cblabel '%s'offset 0.0,0.0\n", cb_label);
    fprintf(gp, "set cbrange['%d':'%d']\n", cb_min, cb_max);
    fprintf(gp, "set palette rgbformulae 22,13,-31\n");

    fprintf(gp, "set pm3d map\n"); // <steps in scan>,<steps between scans>

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "splot '%s' using 1:2:4 with  pm3d notitle\n", filename_dat);
    fflush(gp); // Clean up Data

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);

    return (0);
}