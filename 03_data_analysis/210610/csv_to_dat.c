/******************************************************************************
PROGRAM NAME :csv_to_dat.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define CH 12
#define data_long 20000
const char *read_file_01 = "data.csv";
const char *read_file_02 = "data.dat";
double value[data_long][CH];
char buf[128]; //
FILE *input_file01;
FILE *input_file02;
/*********************************   MAIN   *********************************/
double main()
{
    int i, j;
    double ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9, ch10, ch11, ch12;

    // Array initialization
    for (i = 0; i < data_long; i++)
    {
        for (j = 0; j < CH; j++)
        {
            value[i][j] = 0;
        }
    }

    input_file01 = fopen(read_file_01, "r");
    if (read_file_01 == NULL)
    {
        printf("I can't open the file!\n");
        exit(0);
    }

    printf("test\n");

    for (i = 0; i < data_long; i++)
    {
        fscanf(input_file01, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf%lf,%lf", &ch1, &ch2, &ch3, &ch4, &ch5, &ch6, &ch7, &ch8, &ch9, &ch10, &ch11, &ch12);
        value[i][0] = ch1;
        value[i][1] = ch2;
        value[i][2] = ch3;
        value[i][3] = ch4;
        value[i][4] = ch5;
        value[i][5] = ch6;
        value[i][6] = ch7;
        value[i][7] = ch8;
        value[i][8] = ch9;
        value[i][9] = ch10;
        value[i][10] = ch11;
        value[i][11] = ch12;

        // check the programs
        printf("%lf", value[i][0]);
    }
    // printf("\n");
    fclose(input_file01);

    return (0);
}
