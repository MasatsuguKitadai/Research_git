/******************************************************************************
PROGRAM NAME :allrun_testdata.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/

#include <sys/stat.h>
#include "../programs/00_dft.c"
#include "../programs/01_reverse.c"
#include "../programs/02_drift.c"
#include "../programs/03_average.c"
#include "../programs/04_linear.c"
#include "../programs/05_summary.c"
#include "../programs/06_evaluation.c"
#include "../programs/20_wave-adjuster.c"

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
#include "../programs/21-2_dft_wave-adjuster_ver2.c"
#include "../programs/27-3_wave_dft_drag.c"
#include "../programs/27-4_wave_dft_lift.c"
#include "../programs/28-3_wave_dft_phase-angle_drag.c"
#include "../programs/28-4_wave_dft_phase-angle_lift.c"

/*****************************************************************************/

// simulater
#include "../programs/91_simulater-rotation.c"

/*********************************   MAIN   *********************************/
int main()
{
    char dataname[50];
    int range_angle = 150;
    int split_angle = 24;
    double theta_1, theta_2;

    printf("[Parameters]\n");
    printf("Theta x = ");
    scanf("%lf", &theta_1);
    printf("Theta y = ");
    scanf("%lf", &theta_2);
    printf("\n");

    sprintf(dataname, "rotation_x=%.1f_y=%.1f", theta_1, theta_2);

    /*****************************************************************************/

    // ディレクトリの作成
    char directoryname[100];
    sprintf(directoryname, "../result/%s", dataname);
    mkdir(directoryname, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    /*****************************************************************************/

    // simulater
    simulater(dataname, split_angle, theta_1, theta_2);

    printf("\n---------------------------------------------------------------------------\n\n");

    // 06_evaluation
    evaluation(dataname, split_angle);

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

    return (0);
}