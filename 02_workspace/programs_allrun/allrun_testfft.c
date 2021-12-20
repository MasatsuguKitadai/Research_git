/******************************************************************************
PROGRAM NAME :allrun_testdata.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include "../programs_data/01_reverse.c"
#include "../programs_data/02_drift.c"
#include "../programs_data/03_average.c"
#include "../programs_data/04_linear.c"
#include "../programs_data/05_summary.c"
#include "../programs_data/06_evaluation.c"
#include "../programs_data/07-1_fft_drag.c"
#include "../programs_data/07-2_fft_lift.c"
#include "../programs_data/21_wave-adjuster.c"
/*********************************   MAIN   *********************************/
int main()
{
    // 01_reverse
    reverse("test-fft", "0");
    reverse("test-fft", "22.5");
    reverse("test-fft", "45");
    reverse("test-fft", "67.5");
    reverse("test-fft", "90");
    reverse("test-fft", "112.5");
    reverse("test-fft", "135");
    reverse("test-fft", "157.5");
    reverse("test-fft", "180");
    reverse("test-fft", "205.5");
    reverse("test-fft", "225");
    reverse("test-fft", "247.5");
    reverse("test-fft", "270");
    reverse("test-fft", "292.5");
    reverse("test-fft", "315");
    reverse("test-fft", "337.5");
    reverse("test-fft", "345");

    // 02_drift
    drift("test-fft", "0");
    drift("test-fft", "22.5");
    drift("test-fft", "45");
    drift("test-fft", "67.5");
    drift("test-fft", "90");
    drift("test-fft", "112.5");
    drift("test-fft", "135");
    drift("test-fft", "157.5");
    drift("test-fft", "180");
    drift("test-fft", "205.5");
    drift("test-fft", "225");
    drift("test-fft", "247.5");
    drift("test-fft", "270");
    drift("test-fft", "292.5");
    drift("test-fft", "315");
    drift("test-fft", "337.5");
    drift("test-fft", "345");

    // 03_average
    average("test-fft", "0");
    average("test-fft", "22.5");
    average("test-fft", "45");
    average("test-fft", "67.5");
    average("test-fft", "90");
    average("test-fft", "112.5");
    average("test-fft", "135");
    average("test-fft", "157.5");
    average("test-fft", "180");
    average("test-fft", "205.5");
    average("test-fft", "225");
    average("test-fft", "247.5");
    average("test-fft", "270");
    average("test-fft", "292.5");
    average("test-fft", "315");
    average("test-fft", "337.5");
    average("test-fft", "345");

    // 04_linear
    linear("test-fft", "0");
    linear("test-fft", "22.5");
    linear("test-fft", "45");
    linear("test-fft", "67.5");
    linear("test-fft", "90");
    linear("test-fft", "112.5");
    linear("test-fft", "135");
    linear("test-fft", "157.5");
    linear("test-fft", "180");
    linear("test-fft", "205.5");
    linear("test-fft", "225");
    linear("test-fft", "247.5");
    linear("test-fft", "270");
    linear("test-fft", "292.5");
    linear("test-fft", "315");
    linear("test-fft", "337.5");
    linear("test-fft", "345");

    // 05_summary
    summary("test-fft");

    // 06_evaluation
    evaluation("test-fft");

    // 07-1_fft_drag
    calculate_drag("test-fft", 16);

    // 07-2_fft_lift
    calculate_lift("test-fft", 16);

    // 21_wave-adjuster
    waveadjuster("test-fft");

    return (0);
}