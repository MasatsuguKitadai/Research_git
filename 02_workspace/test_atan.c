/******************************************************************************
PROGRAM NAME :allrun_testdata.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/

#include <sys/stat.h>
#include <stdio.h>
#include <math.h>

/*********************************   MAIN   *********************************/
int main()
{
    double value_tan = 0;
    double value_atan = 0;
    double radian = 0;
    double degree = 0;
    int i = 0;
    int j = 0;

    double pi = 0;
    pi = 4 * atan(1.0);

    for (i = 0; i < 90; i++)
    {
        // j = i - 90;
        // radian = pi / 180 * j;
        radian = pi / 180 * i;
        value_tan = tan(radian);
        // value_tan = tan(j);
        value_atan = atan(value_tan);
        degree = 180 * atan(value_tan) / pi;
        // degree = 180 / pi * value_atan;

        // printf("tan[%d] \t=\t%lf\n", i - 90, value_tan);
        printf("tan[%d]\t\t=\t%lf\n", i, value_tan);
        // printf("arc[%d] \t=\t%lf\n", i - 90, value_atan);
        printf("arc[%lf]\t=\t%lf\n", value_tan, value_atan);
        printf("degree \t=\t%lf\n", degree);

        printf("\n");
        printf("------------------------------------------------\n");
        printf("\n");
    }

    double value_1 = 0;
    value_1 = atan(1);
    printf("atan(1) = %lf\n", value_1);
    printf("\n");

    return (0);
}