/******************************************************************************
PROGRAM NAME :program_ma.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
// 移動平均 範囲
int range_ma = 11;

#include "20_moving_average.c"
#include "41_start_ma.c"
#include "51_finish_ma.c"
#include "61_lerp_ma.c"
#include "91_plot_ma.c"
/*********************************   MAIN   *********************************/
int main()
{
    // 2021/7/31
    // ma("C1", "210731");
    // ma("Groove_A", "210731");
    // ma("Groove_B", "210731");
    // ma("Groove_C", "210731");
    // ma("Groove_D", "210731");
    // ma("Normal", "210731");
    // ma("R1_17.9", "210731");
    // ma("R1_18.6", "210731");
    // ma("R1_19.3", "210731");

    start("C1", "210731");
    start("Groove_A", "210731");
    start("Groove_B", "210731");
    start("Groove_C", "210731");
    start("Groove_D", "210731");
    start("Normal", "210731");
    start("R1_17.9", "210731");
    start("R1_18.6", "210731");
    start("R1_19.3", "210731");

    finish("C1", "210731");
    finish("Groove_A", "210731");
    finish("Groove_B", "210731");
    finish("Groove_C", "210731");
    finish("Groove_D", "210731");
    finish("Normal", "210731");
    finish("R1_17.9", "210731");
    finish("R1_18.6", "210731");
    finish("R1_19.3", "210731");

    lerp("C1", "210731");
    lerp("Groove_A", "210731");
    lerp("Groove_B", "210731");
    lerp("Groove_C", "210731");
    lerp("Groove_D", "210731");
    lerp("Normal", "210731");
    lerp("R1_17.9", "210731");
    lerp("R1_18.6", "210731");
    lerp("R1_19.3", "210731");

    plot_ma("C1", "210731", "C1");
    plot_ma("Groove_A", "210731", "Groove A");
    plot_ma("Groove_B", "210731", "Groove B");
    plot_ma("Groove_C", "210731", "Groove C");
    plot_ma("Groove_D", "210731", "Groove D");
    plot_ma("Normal", "210731", "Normal");
    plot_ma("R1_17.9", "210731", "R1 17.9");
    plot_ma("R1_18.6", "210731", "R1 18.6");
    plot_ma("R1_19.3", "210731", "R1 19.3");

    return (0);
}