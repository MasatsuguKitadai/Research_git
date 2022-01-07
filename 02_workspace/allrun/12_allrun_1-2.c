/******************************************************************************
PROGRAM NAME :allrun_testdata.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/

#include <sys/stat.h>
#include "../programs/00_dft.c"
#include "../programs_60s/01_reverse_60s.c"
#include "../programs_60s/02_drift_60s.c"
#include "../programs_60s/03_average_60s.c"
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
#include "../programs/09-2_dft_net-voltage_ver2.c"
#include "../programs/21-2_dft_wave-adjuster_ver2.c"
#include "../programs/27-3_wave_dft_drag.c"
#include "../programs/27-4_wave_dft_lift.c"
#include "../programs/28-3_wave_dft_phase-angle_drag.c"
#include "../programs/28-4_wave_dft_phase-angle_lift.c"

/*********************************   MAIN   *********************************/
int main()
{
    // make directory
    char dataname[50] = "1-2";
    int range_angle = 150;
    int split_angle = 24;

    /*****************************************************************************/

    // ディレクトリの作成
    char directoryname[100];
    sprintf(directoryname, "../result/%s", dataname);
    mkdir(directoryname, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    printf("\n---------------------------------------------------------------------------\n\n");

    // 01_reverse
    reverse(dataname, "0");
    reverse(dataname, "150");
    reverse(dataname, "300");
    reverse(dataname, "450");
    reverse(dataname, "600");
    reverse(dataname, "750");
    reverse(dataname, "900");
    reverse(dataname, "1050");
    reverse(dataname, "1200");
    reverse(dataname, "1350");
    reverse(dataname, "1500");
    reverse(dataname, "1650");
    reverse(dataname, "1800");
    reverse(dataname, "1950");
    reverse(dataname, "2100");
    reverse(dataname, "2250");
    reverse(dataname, "2400");
    reverse(dataname, "2550");
    reverse(dataname, "2700");
    reverse(dataname, "2850");
    reverse(dataname, "3000");
    reverse(dataname, "3150");
    reverse(dataname, "3300");
    reverse(dataname, "3450");

    printf("\n---------------------------------------------------------------------------\n\n");

    // 02_drift
    drift(dataname, "0");
    drift(dataname, "150");
    drift(dataname, "300");
    drift(dataname, "450");
    drift(dataname, "600");
    drift(dataname, "750");
    drift(dataname, "900");
    drift(dataname, "1050");
    drift(dataname, "1200");
    drift(dataname, "1350");
    drift(dataname, "1500");
    drift(dataname, "1650");
    drift(dataname, "1800");
    drift(dataname, "1950");
    drift(dataname, "2100");
    drift(dataname, "2250");
    drift(dataname, "2400");
    drift(dataname, "2550");
    drift(dataname, "2700");
    drift(dataname, "2850");
    drift(dataname, "3000");
    drift(dataname, "3150");
    drift(dataname, "3300");
    drift(dataname, "3450");

    printf("\n---------------------------------------------------------------------------\n\n");

    // 03_average
    average(dataname, "0");
    average(dataname, "150");
    average(dataname, "300");
    average(dataname, "450");
    average(dataname, "600");
    average(dataname, "750");
    average(dataname, "900");
    average(dataname, "1050");
    average(dataname, "1200");
    average(dataname, "1350");
    average(dataname, "1500");
    average(dataname, "1650");
    average(dataname, "1800");
    average(dataname, "1950");
    average(dataname, "2100");
    average(dataname, "2250");
    average(dataname, "2400");
    average(dataname, "2550");
    average(dataname, "2700");
    average(dataname, "2850");
    average(dataname, "3000");
    average(dataname, "3150");
    average(dataname, "3300");
    average(dataname, "3450");

    printf("\n---------------------------------------------------------------------------\n\n");

    // 04_linear
    printf("\t\t\t[DRAG]\t[LIFT]\t[NET]\n");
    linear(dataname, "0");
    linear(dataname, "150");
    linear(dataname, "300");
    linear(dataname, "450");
    linear(dataname, "600");
    linear(dataname, "750");
    linear(dataname, "900");
    linear(dataname, "1050");
    linear(dataname, "1200");
    linear(dataname, "1350");
    linear(dataname, "1500");
    linear(dataname, "1650");
    linear(dataname, "1800");
    linear(dataname, "1950");
    linear(dataname, "2100");
    linear(dataname, "2250");
    linear(dataname, "2400");
    linear(dataname, "2550");
    linear(dataname, "2700");
    linear(dataname, "2850");
    linear(dataname, "3000");
    linear(dataname, "3150");
    linear(dataname, "3300");
    linear(dataname, "3450");

    printf("\n---------------------------------------------------------------------------\n\n");

    // 05_summary
    summary(dataname, range_angle);

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