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
// #include "../programs/07-1_fft_drag.c"
// #include "../programs/07-2_fft_lift.c"
#include "../programs/07-3_dft_drag.c"
#include "../programs/07-4_dft_lift.c"
#include "../programs/08-1_phase-angle_drag.c"
#include "../programs/08-2_phase-angle_lift.c"
// #include "../programs/09_net-voltage.c"
#include "../programs/09_net-voltage_ver2.c"
#include "../programs/20_wave-adjuster.c"
#include "../programs/21_wave-adjuster_ver2.c"
// #include "../programs/27-1_wave_fft_drag.c"
// #include "../programs/27-2_wave_fft_lift.c"
#include "../programs/27-3_wave_dft_drag.c"
#include "../programs/27-4_wave_dft_lift.c"
#include "../programs/28-1_wave_phase-angle_drag.c"
#include "../programs/28-2_wave_phase-angle_lift.c"

/*********************************   MAIN   *********************************/
int directory(char date[])
{
    // ディレクトリの作成
    char directoryname[100];
    sprintf(directoryname, "../result/%s", date);
    mkdir(directoryname, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
}

int main()
{
    // make directory
    directory("testdata");

    printf("\n---------------------------------------------------------------------------\n\n");

    // 01_reverse
    reverse("testdata", "0");
    reverse("testdata", "150");
    reverse("testdata", "300");
    reverse("testdata", "450");
    reverse("testdata", "600");
    reverse("testdata", "750");
    reverse("testdata", "900");
    reverse("testdata", "1050");
    reverse("testdata", "1200");
    reverse("testdata", "1350");
    reverse("testdata", "1500");
    reverse("testdata", "1650");
    reverse("testdata", "1800");
    reverse("testdata", "1950");
    reverse("testdata", "2100");
    reverse("testdata", "2250");
    reverse("testdata", "2400");
    reverse("testdata", "2550");
    reverse("testdata", "2700");
    reverse("testdata", "2850");
    reverse("testdata", "3000");
    reverse("testdata", "3150");
    reverse("testdata", "3300");
    reverse("testdata", "3450");

    printf("\n---------------------------------------------------------------------------\n\n");

    // 02_drift
    drift("testdata", "0");
    drift("testdata", "150");
    drift("testdata", "300");
    drift("testdata", "450");
    drift("testdata", "600");
    drift("testdata", "750");
    drift("testdata", "900");
    drift("testdata", "1050");
    drift("testdata", "1200");
    drift("testdata", "1350");
    drift("testdata", "1500");
    drift("testdata", "1650");
    drift("testdata", "1800");
    drift("testdata", "1950");
    drift("testdata", "2100");
    drift("testdata", "2250");
    drift("testdata", "2400");
    drift("testdata", "2550");
    drift("testdata", "2700");
    drift("testdata", "2850");
    drift("testdata", "3000");
    drift("testdata", "3150");
    drift("testdata", "3300");
    drift("testdata", "3450");

    printf("\n---------------------------------------------------------------------------\n\n");

    // 03_average
    average("testdata", "0");
    average("testdata", "150");
    average("testdata", "300");
    average("testdata", "450");
    average("testdata", "600");
    average("testdata", "750");
    average("testdata", "900");
    average("testdata", "1050");
    average("testdata", "1200");
    average("testdata", "1350");
    average("testdata", "1500");
    average("testdata", "1650");
    average("testdata", "1800");
    average("testdata", "1950");
    average("testdata", "2100");
    average("testdata", "2250");
    average("testdata", "2400");
    average("testdata", "2550");
    average("testdata", "2700");
    average("testdata", "2850");
    average("testdata", "3000");
    average("testdata", "3150");
    average("testdata", "3300");
    average("testdata", "3450");

    printf("\n---------------------------------------------------------------------------\n\n");

    // 04_linear
    linear("testdata", "0");
    linear("testdata", "150");
    linear("testdata", "300");
    linear("testdata", "450");
    linear("testdata", "600");
    linear("testdata", "750");
    linear("testdata", "900");
    linear("testdata", "1050");
    linear("testdata", "1200");
    linear("testdata", "1350");
    linear("testdata", "1500");
    linear("testdata", "1650");
    linear("testdata", "1800");
    linear("testdata", "1950");
    linear("testdata", "2100");
    linear("testdata", "2250");
    linear("testdata", "2400");
    linear("testdata", "2550");
    linear("testdata", "2700");
    linear("testdata", "2850");
    linear("testdata", "3000");
    linear("testdata", "3150");
    linear("testdata", "3300");
    linear("testdata", "3450");

    printf("\n---------------------------------------------------------------------------\n\n");

    // 05_summary
    summary("testdata", 150);

    printf("\n---------------------------------------------------------------------------\n\n");

    // 06_evaluation
    evaluation("testdata", 24);

    printf("\n---------------------------------------------------------------------------\n\n");

    // 07-1_fft_drag
    calculate_drag("testdata", 24);

    printf("\n---------------------------------------------------------------------------\n\n");

    // 08-1_phase-angle_drag
    phase_angle_drag("testdata");

    printf("\n---------------------------------------------------------------------------\n\n");

    // 07-2_fft_lift
    calculate_lift("testdata", 24);

    printf("\n---------------------------------------------------------------------------\n\n");

    // 08-2_phase-angle_lift
    phase_angle_lift("testdata");

    printf("\n---------------------------------------------------------------------------\n\n");

    // 09_net-voltage
    netvoltage("testdata", 150);

    printf("\n---------------------------------------------------------------------------\n\n");

    // 20_wave-adjuster
    waveadjuster("testdata");

    printf("\n---------------------------------------------------------------------------\n\n");

    // 21_wave-adjuster_ver2
    waveadjuster_ver2("testdata");

    printf("\n---------------------------------------------------------------------------\n\n");

    // 27-1_wave_fft_drag
    calculate_drag_theory("testdata", 24);

    printf("\n---------------------------------------------------------------------------\n\n");

    // 28-1_wave_phase-angle_drag
    phase_angle_drag_theory("testdata");

    printf("\n---------------------------------------------------------------------------\n\n");

    // 27-2_wave_fft_lift
    calculate_lift_theory("testdata", 24);

    printf("\n---------------------------------------------------------------------------\n\n");

    // 28-2_wave_phase-angle_lift
    phase_angle_lift_theory("testdata");

    printf("\n---------------------------------------------------------------------------\n\n");

    return (0);
}