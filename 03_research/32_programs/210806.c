/******************************************************************************
PROGRAM NAME :program_ma.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include "40_start.c"
#include "50_finish.c"
#include "60_lerp.c"
#include "90_plot.c"
/*********************************   MAIN   *********************************/
int main()
{
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

    plot("C1", "210806", "C1");
    plot("Groove_A", "210806", "Groove A");
    plot("Groove_B", "210806", "Groove B");
    plot("Groove_C", "210806", "Groove C");
    plot("Groove_D", "210806", "Groove D");
    plot("Normal", "210806", "Normal");
    plot("R1_17.9", "210806", "R1 17.9");
    plot("R1_18.6", "210806", "R1 18.6");
    plot("R1_19.3", "210806", "R1 19.3");

    return (0);
}