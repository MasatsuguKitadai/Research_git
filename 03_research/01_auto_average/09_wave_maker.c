/******************************************************************************
PROGRAM NAME : sin_wave_maker.c
AUTHER  : masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FILE *fp, *fp_csv, *fp_dat;

char filename_read[100];
char filename_csv[100];
char filename_dat[100];

// sin波の配列
double wave_value[360];
double wave_drag[360];
double wave_lift[360];

// sin波の周期 [秒]
int wave1 = 12;

// 円周率の定義
#define pi 4 * atan(1.0)

/*********************************   MAIN   *********************************/
int wave_maker(char date[])
{

    sprintf(filename_read,"result/%s/05_dat_summary/%s_summary_ave.dat",  date, date);
    sprintf(filename_csv, "result/%s/09_csv_wave/%s_wave.csv",  date, date);
    sprintf(filename_dat, "result/%s/09_dat_wave/%s_wave.dat",  date, date);

    int buf;
    double ch0, ch1, ch2;
    double average_value;

    fp = fopen(filename_read, "r");
    if (filename_read == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    fscanf(fp, "%d\t%lf\t%lf\t%lf", &buf, &ch0, &ch1, &ch2);
    printf("【Average】\t%lf\t%lf\t%lf\n", ch0, ch1, ch2);
    average_value = ch2; // sqrt average

    // 正弦波の作成

    int i = 0;

    // 正弦波 drag (位相 π ズレ)
    // printf("Drag\n");
    for (i = 0; i < 360; i++)
    {
        wave_drag[i] = sin((2 * pi/360) * (i + 270));
        wave_drag[i] = wave_drag[i] * average_value;
        // printf("value[%d] = %lf\n", i, wave_drag[i]);
    }

    // 正弦波 lift (位相 3π/2 ズレ)
    // printf("Lift\n");
    for (i = 0; i < 360; i++)
    {
        wave_lift[i] = sin((2 * pi/360) * (i + 180));
        wave_lift[i] = wave_lift[i] * average_value;
        // printf("value[%d] = %lf\n", i, wave_lift[i]);
    }

    int angle;

    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");

    for (i = 0; i < 24; i++)
    {
        angle = i * 15;
        fprintf(fp_csv, "%d,%lf,%lf\n", angle,  wave_drag[angle], wave_lift[angle]);
        fprintf(fp_dat, "%d\t%lf\t%lf\n", angle, wave_drag[angle], wave_lift[angle]);
    }

    fclose(fp_csv);
    fclose(fp_dat);

}

int main()
{
    wave_maker("simulation_data");
    return(0);
}