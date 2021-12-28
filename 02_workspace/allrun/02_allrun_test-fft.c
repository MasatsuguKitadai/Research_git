/******************************************************************************
PROGRAM NAME :allrun_testdata.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/

#include <sys/stat.h>
#include "../programs/01_reverse.c"
#include "../programs/02_drift.c"
#include "../programs/03_average.c"
#include "../programs/04_linear.c"
#include "../programs/05_summary.c"
#include "../programs/06_evaluation.c"
#include "../programs/20_wave-adjuster.c"

/*****************************************************************************/

/** FFT **/
#include "../programs/00_fft.c"
#include "../programs/07-1_fft_drag.c"
#include "../programs/07-2_fft_lift.c"
#include "../programs/08-1_phase-angle_drag.c"
#include "../programs/08-2_phase-angle_lift.c"
#include "../programs/09-fft_net-voltage_ver2.c"
#include "../programs/21-fft_wave-adjuster_ver2.c"
#include "../programs/27-1_wave_fft_drag.c"
#include "../programs/27-2_wave_fft_lift.c"
#include "../programs/28-1_wave_phase-angle_drag.c"
#include "../programs/28-2_wave_phase-angle_lift.c"

/*****************************************************************************/

/** DFT **/

// #include "../programs/00_dft.c"
// #include "../programs/07-3_dft_drag.c"
// #include "../programs/07-4_dft_lift.c"
// #include "../programs/08-3_phase-angle_drag.c"
// #include "../programs/08-4_phase-angle_lift.c"
// #include "../programs/09-dft_net-voltage_ver2.c"
// #include "../programs/21-dft_wave-adjuster_ver2.c"
// #include "../programs/27-3_wave_dft_drag.c"
// #include "../programs/27-4_wave_dft_lift.c"
// #include "../programs/28-3_wave_phase-angle_drag.c"
// #include "../programs/28-4_wave_phase-angle_lift.c"

/*********************************   MAIN   *********************************/
int main()
{
    // make directory
    char dataname[50] = "test-fft";
    int range_angle = 225;
    int split_angle = 16;

    /*****************************************************************************/

    // ディレクトリの作成
    char directoryname[100];
    sprintf(directoryname, "../result/%s", dataname);
    mkdir(directoryname, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    printf("\n---------------------------------------------------------------------------\n\n");

    // 01_reverse
    reverse(dataname, "0");
    reverse(dataname, "225");
    reverse(dataname, "450");
    reverse(dataname, "675");
    reverse(dataname, "900");
    reverse(dataname, "1125");
    reverse(dataname, "1350");
    reverse(dataname, "1575");
    reverse(dataname, "1800");
    reverse(dataname, "2025");
    reverse(dataname, "2250");
    reverse(dataname, "2475");
    reverse(dataname, "2700");
    reverse(dataname, "2925");
    reverse(dataname, "3150");
    reverse(dataname, "3375");

    printf("\n---------------------------------------------------------------------------\n\n");

    // 02_drift
    drift(dataname, "0");
    drift(dataname, "225");
    drift(dataname, "450");
    drift(dataname, "675");
    drift(dataname, "900");
    drift(dataname, "1125");
    drift(dataname, "1350");
    drift(dataname, "1575");
    drift(dataname, "1800");
    drift(dataname, "2025");
    drift(dataname, "2250");
    drift(dataname, "2475");
    drift(dataname, "2700");
    drift(dataname, "2925");
    drift(dataname, "3150");
    drift(dataname, "3375");

    printf("\n---------------------------------------------------------------------------\n\n");

    // 03_average
    average(dataname, "0");
    average(dataname, "225");
    average(dataname, "450");
    average(dataname, "675");
    average(dataname, "900");
    average(dataname, "1125");
    average(dataname, "1350");
    average(dataname, "1575");
    average(dataname, "1800");
    average(dataname, "2025");
    average(dataname, "2250");
    average(dataname, "2475");
    average(dataname, "2700");
    average(dataname, "2925");
    average(dataname, "3150");
    average(dataname, "3375");

    printf("\n---------------------------------------------------------------------------\n\n");

    // 04_linear
    linear(dataname, "0");
    linear(dataname, "225");
    linear(dataname, "450");
    linear(dataname, "675");
    linear(dataname, "900");
    linear(dataname, "1125");
    linear(dataname, "1350");
    linear(dataname, "1575");
    linear(dataname, "1800");
    linear(dataname, "2025");
    linear(dataname, "2250");
    linear(dataname, "2475");
    linear(dataname, "2700");
    linear(dataname, "2925");
    linear(dataname, "3150");
    linear(dataname, "3375");

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