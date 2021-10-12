/******************************************************************************
PROGRAM NAME :calibration.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include "03_convert.c"
#include "04_plot_calibration.c"
/*********************************   MAIN   *********************************/
int main()
{
    convert();
    plot_calibration();
    return (0);
}