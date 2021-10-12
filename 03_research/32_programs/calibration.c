/******************************************************************************
PROGRAM NAME :calibration.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include "sub_programs/03_convert.c"
#include "sub_programs/04_plot_calibration.c"
/*********************************   MAIN   *********************************/
int main()
{
    convert();
    plot_calibration();
    return (0);
}