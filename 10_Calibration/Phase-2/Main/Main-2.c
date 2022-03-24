#include "../Func/head.h"
#include "../Func/F060_Summary-2.c"
#include "../Func/F070_Evaluation.c"
#include "../Func/F080_Offset.c"
#include "../Func/F090_Interpolation.c"
#include "../Func/F100_DFT_drag.c"
#include "../Func/F110_DFT_lift.c"
#include "../Func/F120_Phase-angle_drag.c"
#include "../Func/F130_Phase-angle_lift.c"
#include "../Func/F140_Rotation.c"
#include "../Func/F150_Adjust.c"
#include "../Func/F160_Error.c"
#include "../Func/F170_DFT_net-voltage.c"

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

    double x, y;
    x = 0.08;
    y = 0.06;

    int number = 5;

    /*****************************************************************************/

    printf("\n---------------------------------------------------------------------------\n\n");

    Summary(dataname, number, split_angle);

    printf("\n---------------------------------------------------------------------------\n\n");

    Evaluation(dataname, split_angle);

    printf("\n---------------------------------------------------------------------------\n\n");

    Offset(dataname, split_angle, x, y);

    printf("\n---------------------------------------------------------------------------\n\n");

    Interpolation(dataname, split_angle);

    printf("\n---------------------------------------------------------------------------\n\n");

    DFT_drag(dataname, split_angle);

    printf("\n---------------------------------------------------------------------------\n\n");

    DFT_lift(dataname, split_angle);

    printf("\n---------------------------------------------------------------------------\n\n");

    Phase_angle_drag(dataname);

    printf("\n---------------------------------------------------------------------------\n\n");

    Phase_angle_lift(dataname);

    printf("\n---------------------------------------------------------------------------\n\n");

    Rotation(dataname, split_angle);

    printf("\n---------------------------------------------------------------------------\n\n");

    Adjust(dataname);

    printf("\n---------------------------------------------------------------------------\n\n");

    RMSE(dataname);

    printf("\n---------------------------------------------------------------------------\n\n");

    DFT_netvoltage(dataname, split_angle);

    return (0);
}