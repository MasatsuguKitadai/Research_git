/******************************************************************************
PROGRAM NAME :drift_ma.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ch 2
FILE *fp1;
/*********************************   MAIN   *********************************/
int drift_ma(char filename1[])
{
    // ファイルの読み込み

    fp1 = fopen(filename1, "r");
    if (filename1 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    // データの格納

    int i = 0;
    int N = 1000;
    int num, data_long;
    double ch1, ch2;
    double value[N][ch];
    int number[N];

    // ch1:drag, ch2:lift

    while ((fscanf(fp1, "%d\t%lf\t%lf", &num, &ch1, &ch2)) != EOF)
    {
        number[i] = num;
        value[i][1] = ch1;
        value[i][2] = ch2;
        // printf("%d\t%lf\t%lf\n", number[i], value[i][1], value[i][2]);
        i = i + 1;
    }

    fclose(fp1);

    data_long = i; 

    int j = 0;
    int range = 5;
    int a, b;

    a = (range - 1)/2;
    b = data_long - 2*a;

    double ma_d[b],ma_l[b],sum1,sum2;

    for (i = 0; i < b ; i++)
    {
        sum1 = 0;
        sum2 = 0;

        for (j = 0; j < range ; j++)
        {
            sum1 = sum1 + value[i + j][1];
            sum2 = sum2 + value[i + j][2];
            j = j + 1; 
        }
        
        ma_d[i] = sum1 / range;
        ma_l[i] = sum2 / range;

        printf("%d\t%lf\t%lf\n",i,ma_d[i],ma_l[i]);
    }
}