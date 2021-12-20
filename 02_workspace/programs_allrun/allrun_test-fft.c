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
#include "../programs_data/22-1_wave_fft_drag.c"
#include "../programs_data/22-2_wave_fft_lift.c"

/*********************************   MAIN   *********************************/
int main()
{
    // // 01_reverse
    // reverse("test-fft", "0");
    // reverse("test-fft", "225");
    // reverse("test-fft", "450");
    // reverse("test-fft", "675");
    // reverse("test-fft", "900");
    // reverse("test-fft", "1125");
    // reverse("test-fft", "1350");
    // reverse("test-fft", "1575");
    // reverse("test-fft", "1800");
    // reverse("test-fft", "2025");
    // reverse("test-fft", "2250");
    // reverse("test-fft", "2475");
    // reverse("test-fft", "2700");
    // reverse("test-fft", "2925");
    // reverse("test-fft", "3150");
    // reverse("test-fft", "3375");

    // // 02_drift
    // drift("test-fft", "0");
    // drift("test-fft", "225");
    // drift("test-fft", "450");
    // drift("test-fft", "675");
    // drift("test-fft", "900");
    // drift("test-fft", "1125");
    // drift("test-fft", "1350");
    // drift("test-fft", "1575");
    // drift("test-fft", "1800");
    // drift("test-fft", "2025");
    // drift("test-fft", "2250");
    // drift("test-fft", "2475");
    // drift("test-fft", "2700");
    // drift("test-fft", "2925");
    // drift("test-fft", "3150");
    // drift("test-fft", "3375");

    // // 03_average
    // average("test-fft", "0");
    // average("test-fft", "225");
    // average("test-fft", "450");
    // average("test-fft", "675");
    // average("test-fft", "900");
    // average("test-fft", "1125");
    // average("test-fft", "1350");
    // average("test-fft", "1575");
    // average("test-fft", "1800");
    // average("test-fft", "2025");
    // average("test-fft", "2250");
    // average("test-fft", "2475");
    // average("test-fft", "2700");
    // average("test-fft", "2925");
    // average("test-fft", "3150");
    // average("test-fft", "3375");

    // // 04_linear
    // linear("test-fft", "0");
    // linear("test-fft", "225");
    // linear("test-fft", "450");
    // linear("test-fft", "675");
    // linear("test-fft", "900");
    // linear("test-fft", "1125");
    // linear("test-fft", "1350");
    // linear("test-fft", "1575");
    // linear("test-fft", "1800");
    // linear("test-fft", "2025");
    // linear("test-fft", "2250");
    // linear("test-fft", "2475");
    // linear("test-fft", "2700");
    // linear("test-fft", "2925");
    // linear("test-fft", "3150");
    // linear("test-fft", "3375");

    // // 05_summary
    // summary("test-fft", 225);

    // // 06_evaluation
    // evaluation("test-fft");

    // 07-1_fft_drag
    calculate_drag("test-fft", 16);

    // 07-2_fft_lift
    calculate_lift("test-fft", 16);

    // 21_wave-adjuster
    waveadjuster("test-fft");

    // 22-1_wave_fft_drag
    calculate_drag_theory("test-fft", 16);

    // 22-2_wave_fft_lift
    calculate_lift_theory("test-fft", 16);

    return (0);
}