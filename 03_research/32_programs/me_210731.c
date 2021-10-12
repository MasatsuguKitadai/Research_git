/******************************************************************************
PROGRAM NAME :program_ma.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
// 中央値 範囲
int range_me = 11;

#include "mainprograms/30_median.c"
#include "mainprograms/42_start_me.c"
#include "mainprograms/52_finish_me.c"
#include "mainprograms/62_lerp_me.c"
#include "mainprograms/72_average_me.c"
#include "mainprograms/92_plot_me.c"
/*********************************   MAIN   *********************************/
int main()
{
    // 2021/8/6
    // me("C1", "210731");
    // me("Groove_A", "210731");
    // me("Groove_B", "210731");
    // me("Groove_C", "210731");
    // me("Groove_D", "210731");
    // me("Normal", "210731");
    // me("R1_17.9", "210731");
    // me("R1_18.6", "210731");
    // me("R1_19.3", "210731");

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

    average("C1", "210731");
    average("Groove_A", "210731");
    average("Groove_B", "210731");
    average("Groove_C", "210731");
    average("Groove_D", "210731");
    average("Normal", "210731");
    average("R1_17.9", "210731");
    average("R1_18.6", "210731");
    average("R1_19.3", "210731");

    plot_me("C1", "210731", "C1");
    plot_me("Groove_A", "210731", "Groove A");
    plot_me("Groove_B", "210731", "Groove B");
    plot_me("Groove_C", "210731", "Groove C");
    plot_me("Groove_D", "210731", "Groove D");
    plot_me("Normal", "210731", "Normal");
    plot_me("R1_17.9", "210731", "R1 17.9");
    plot_me("R1_18.6", "210731", "R1 18.6");
    plot_me("R1_19.3", "210731", "R1 19.3");

    return (0);
}