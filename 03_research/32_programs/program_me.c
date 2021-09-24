/******************************************************************************
PROGRAM NAME :program_ma.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/

// 中央値 範囲
int range_me = 5;

#include "30_median.c"
#include "42_start_me.c"
#include "52_finish_me.c"
#include "62_lerp_me.c"
#include "92_plot_me.c"
/*********************************   MAIN   *********************************/
int main()
{
    // 2021/8/6
    me("C1", "210806");
    me("Groove_A", "210806");
    me("Groove_B", "210806");
    me("Groove_C", "210806");
    me("Groove_D", "210806");
    me("Normal", "210806");
    me("R1_17.9", "210806");
    me("R1_18.6", "210806");
    me("R1_19.3", "210806");

    start("C1", "210806");
    start("Groove_A", "210806");
    start("Groove_B", "210806");
    start("Groove_C", "210806");
    start("Groove_D", "210806");
    start("Normal", "210806");
    start("R1_17.9", "210806");
    start("R1_18.6", "210806");
    start("R1_19.3", "210806");

    finish("C1", "210806");
    finish("Groove_A", "210806");
    finish("Groove_B", "210806");
    finish("Groove_C", "210806");
    finish("Groove_D", "210806");
    finish("Normal", "210806");
    finish("R1_17.9", "210806");
    finish("R1_18.6", "210806");
    finish("R1_19.3", "210806");

    lerp("C1", "210806");
    lerp("Groove_A", "210806");
    lerp("Groove_B", "210806");
    lerp("Groove_C", "210806");
    lerp("Groove_D", "210806");
    lerp("Normal", "210806");
    lerp("R1_17.9", "210806");
    lerp("R1_18.6", "210806");
    lerp("R1_19.3", "210806");

    plot_me("C1", "210806", "C1");
    plot_me("Groove_A", "210806", "Groove A");
    plot_me("Groove_B", "210806", "Groove B");
    plot_me("Groove_C", "210806", "Groove C");
    plot_me("Groove_D", "210806", "Groove D");
    plot_me("Normal", "210806", "Normal");
    plot_me("R1_17.9", "210806", "R1 17.9");
    plot_me("R1_18.6", "210806", "R1 18.6");
    plot_me("R1_19.3", "210806", "R1 19.3");

    return (0);
}