/******************************************************************************
PROGRAM NAME : sin_wave_maker.c
AUTHER  : masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FILE *fp;
const char filename1[100] = "test_data/sin_n=128.dat";
const char filename2[100] = "test_data/sin_n=256.dat";

// sin波の配列
double value_128[128];
double value_256[256];

double sin_wave_1[256];
double sin_wave_2[256];

// sin波の周期 [秒]
int wave1 = 128;
int wave2 = 64;

// 円周率の定義
#define pi 4 * atan(1.0)

/*********************************   MAIN   *********************************/

int main()
{

    int i = 0;
    for (i = 0; i < 256; i++)
    {
        sin_wave_1[i] = sin(2 * pi * i / wave1);
        sin_wave_2[i] = sin(2 * pi * i / wave2);

        // printf("[%d]\t%lf\t%lf\n", i, sin_wave_1[i], sin_wave_2[i]);
    }

    fp = fopen(filename1, "w");

    for (i = 0; i < 128; i++)
    {
        value_128[i] = sin_wave_1[i] + sin_wave_2[i];
        fprintf(fp, "%d\t%lf\n", i, value_128[i]);
    }

    fclose(fp);

    fp = fopen(filename2, "w");

    for (i = 0; i < 256; i++)
    {
        value_256[i] = 2 * (sin_wave_1[i] + sin_wave_2[i]);
        fprintf(fp, "%d\t%lf\n", i, value_256[i]);
    }

    fclose(fp);
}