/******************************************************************************
PROGRAM NAME :calibration.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include "03_convert/03_calcuration.c"
#include "03_convert/04_plot_calibration.c"
/*********************************   MAIN   *********************************/
int main()
{
    convert();
    plot_calibration();
    return (0);
}