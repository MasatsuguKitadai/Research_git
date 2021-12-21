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
/*********************************   MAIN   *********************************/
int main()
{
    // 01_reverse
    reverse("testdata", "0");
    reverse("testdata", "15");
    reverse("testdata", "30");
    reverse("testdata", "45");
    reverse("testdata", "60");
    reverse("testdata", "75");
    reverse("testdata", "90");
    reverse("testdata", "105");
    reverse("testdata", "120");
    reverse("testdata", "135");
    reverse("testdata", "150");
    reverse("testdata", "165");
    reverse("testdata", "180");
    reverse("testdata", "195");
    reverse("testdata", "210");
    reverse("testdata", "225");
    reverse("testdata", "240");
    reverse("testdata", "255");
    reverse("testdata", "270");
    reverse("testdata", "285");
    reverse("testdata", "300");
    reverse("testdata", "315");
    reverse("testdata", "330");
    reverse("testdata", "345");

    // 02_drift
    drift("testdata", "0");
    drift("testdata", "15");
    drift("testdata", "30");
    drift("testdata", "45");
    drift("testdata", "60");
    drift("testdata", "75");
    drift("testdata", "90");
    drift("testdata", "105");
    drift("testdata", "120");
    drift("testdata", "135");
    drift("testdata", "150");
    drift("testdata", "165");
    drift("testdata", "180");
    drift("testdata", "195");
    drift("testdata", "210");
    drift("testdata", "225");
    drift("testdata", "240");
    drift("testdata", "255");
    drift("testdata", "270");
    drift("testdata", "285");
    drift("testdata", "300");
    drift("testdata", "315");
    drift("testdata", "330");
    drift("testdata", "345");

    // 03_average
    average("testdata", "0");
    average("testdata", "15");
    average("testdata", "30");
    average("testdata", "45");
    average("testdata", "60");
    average("testdata", "75");
    average("testdata", "90");
    average("testdata", "105");
    average("testdata", "120");
    average("testdata", "135");
    average("testdata", "150");
    average("testdata", "165");
    average("testdata", "180");
    average("testdata", "195");
    average("testdata", "210");
    average("testdata", "225");
    average("testdata", "240");
    average("testdata", "255");
    average("testdata", "270");
    average("testdata", "285");
    average("testdata", "300");
    average("testdata", "315");
    average("testdata", "330");
    average("testdata", "345");

    // 04_linear
    linear("testdata", "0");
    linear("testdata", "15");
    linear("testdata", "30");
    linear("testdata", "45");
    linear("testdata", "60");
    linear("testdata", "75");
    linear("testdata", "90");
    linear("testdata", "105");
    linear("testdata", "120");
    linear("testdata", "135");
    linear("testdata", "150");
    linear("testdata", "165");
    linear("testdata", "180");
    linear("testdata", "195");
    linear("testdata", "210");
    linear("testdata", "225");
    linear("testdata", "240");
    linear("testdata", "255");
    linear("testdata", "270");
    linear("testdata", "285");
    linear("testdata", "300");
    linear("testdata", "315");
    linear("testdata", "330");
    linear("testdata", "345");

    // 05_summary
    summary("testdata");

    // 06_evaluation
    evaluation("testdata");

    return (0);
}