#include "../Func/head.h"
#include "../Func/F010_Reverse.c"
#include "../Func/F020_Drift.c"
#include "../Func/F030_Average.c"
#include "../Func/F040_Linear.c"
#include "../Func/F050_Summary-1.c"

/*********************************   MAIN   *********************************/
int main()
{
    // make directory
    char dataname[50];
    int split_angle = 24;

    printf("Data name : ");
    scanf("%s", dataname);

    // ディレクトリの作成
    char directoryname[100];
    sprintf(directoryname, "../result/%s", dataname);
    mkdir(directoryname, mode);

    /*****************************************************************************/

    printf("\n---------------------------------------------------------------------------\n\n");

    // 010_Reverse
    Reverse(dataname, "0");
    Reverse(dataname, "15");
    Reverse(dataname, "30");
    Reverse(dataname, "45");
    Reverse(dataname, "60");
    Reverse(dataname, "75");
    Reverse(dataname, "90");
    Reverse(dataname, "105");
    Reverse(dataname, "120");
    Reverse(dataname, "135");
    Reverse(dataname, "150");
    Reverse(dataname, "165");
    Reverse(dataname, "180");
    Reverse(dataname, "195");
    Reverse(dataname, "210");
    Reverse(dataname, "225");
    Reverse(dataname, "240");
    Reverse(dataname, "255");
    Reverse(dataname, "270");
    Reverse(dataname, "285");
    Reverse(dataname, "300");
    Reverse(dataname, "315");
    Reverse(dataname, "330");
    Reverse(dataname, "345");

    printf("\n---------------------------------------------------------------------------\n\n");

    // 020_Drift
    Drift(dataname, "0");
    Drift(dataname, "15");
    Drift(dataname, "30");
    Drift(dataname, "45");
    Drift(dataname, "60");
    Drift(dataname, "75");
    Drift(dataname, "90");
    Drift(dataname, "105");
    Drift(dataname, "120");
    Drift(dataname, "135");
    Drift(dataname, "150");
    Drift(dataname, "165");
    Drift(dataname, "180");
    Drift(dataname, "195");
    Drift(dataname, "210");
    Drift(dataname, "225");
    Drift(dataname, "240");
    Drift(dataname, "255");
    Drift(dataname, "270");
    Drift(dataname, "285");
    Drift(dataname, "300");
    Drift(dataname, "315");
    Drift(dataname, "330");
    Drift(dataname, "345");

    printf("\n---------------------------------------------------------------------------\n\n");

    // 030_Average
    Average(dataname, "0");
    Average(dataname, "15");
    Average(dataname, "30");
    Average(dataname, "45");
    Average(dataname, "60");
    Average(dataname, "75");
    Average(dataname, "90");
    Average(dataname, "105");
    Average(dataname, "120");
    Average(dataname, "135");
    Average(dataname, "150");
    Average(dataname, "165");
    Average(dataname, "180");
    Average(dataname, "195");
    Average(dataname, "210");
    Average(dataname, "225");
    Average(dataname, "240");
    Average(dataname, "255");
    Average(dataname, "270");
    Average(dataname, "285");
    Average(dataname, "300");
    Average(dataname, "315");
    Average(dataname, "330");
    Average(dataname, "345");

    printf("\n---------------------------------------------------------------------------\n\n");

    // 040_Linear
    printf("\t\t[DRAG]\t[LIFT]\t[NET]\n");
    Linear(dataname, "0");
    Linear(dataname, "15");
    Linear(dataname, "30");
    Linear(dataname, "45");
    Linear(dataname, "60");
    Linear(dataname, "75");
    Linear(dataname, "90");
    Linear(dataname, "105");
    Linear(dataname, "120");
    Linear(dataname, "135");
    Linear(dataname, "150");
    Linear(dataname, "165");
    Linear(dataname, "180");
    Linear(dataname, "195");
    Linear(dataname, "210");
    Linear(dataname, "225");
    Linear(dataname, "240");
    Linear(dataname, "255");
    Linear(dataname, "270");
    Linear(dataname, "285");
    Linear(dataname, "300");
    Linear(dataname, "315");
    Linear(dataname, "330");
    Linear(dataname, "345");

    printf("\n---------------------------------------------------------------------------\n\n");

    // 050_Summary
    Summary(dataname, split_angle);

    return (0);
}