#include "../Func/head.h"
#include "../Func/F061_Summary-2.c"
#include "../Func/F071_Evaluation.c"
#include "../Func/F081_Offset.c"
#include "../Func/F091_Interpolation.c"
#include "../Func/F141_Rotation.c"
#include "../Func/F151_Adjust.c"
#include "../Func/F180_Force.c"

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
    sprintf(directoryname, "../Result/%s", dataname);
    mkdir(directoryname, mode);

    double x, y;
    x = 0.08;
    y = 0.06;

    int number = 5;

    /*****************************************************************************/

    printf("\n---------------------------------------------------------------------------\n\n");

    Force(dataname);

    printf("\n---------------------------------------------------------------------------\n\n");

    Summary(dataname, number, split_angle);

    printf("\n---------------------------------------------------------------------------\n\n");

    Evaluation(dataname, split_angle);

    printf("\n---------------------------------------------------------------------------\n\n");

    Offset(dataname, split_angle, x, y);

    printf("\n---------------------------------------------------------------------------\n\n");

    Interpolation(dataname, split_angle);

    printf("\n---------------------------------------------------------------------------\n\n");

    Rotation(dataname, split_angle);

    printf("\n---------------------------------------------------------------------------\n\n");

    Adjust(dataname);

    printf("\n---------------------------------------------------------------------------\n\n");

    return (0);
}