/******************************************************************************
PROGRAM NAME :sort.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ch 2
#include "files/fp.h"
/*********************************   MAIN   *********************************/
int sort(char name[], char date[])
{
    // ファイル名の作成

    char filename1[100];
    char filename2[100];

    sprintf(filename1, "../31_data/%s/%s.CSV", date, name);
    sprintf(filename2, "../33_result/%s/raw_data/dat/%s.dat", date, name);

    // ファイルの読み込み

    fp1 = fopen(filename1, "r");
    if (filename1 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    // データの格納

    int i, j;
    int N = 1000;
    double ch1, ch2;
    double value[N][ch];

    // ch1:drag, ch2:lift

    i = 0;

    while ((fscanf(fp1, "%lf, %lf", &ch1, &ch2)) != EOF)
    {
        value[i][1] = ch1;
        value[i][2] = ch2;
        // printf("[%d] %lf %lf\n", i, value[i][1], value[i][2]);
        i = i + 1;
    }

    fclose(fp1);

    // datファイルに出力

    fp2 = fopen(filename2, "w");

    for (j = 0; j < i; j++)
    {
        fprintf(fp2, "%d\t%lf\t%lf\n", j, value[j][1], value[j][2]);
    }

    fclose(fp2);

    return (0);
}

int main()
{
    /* 210806 */
    sort("C1", "210806");
    sort("Groove_A", "210806");
    sort("Groove_B", "210806");
    sort("Groove_C", "210806");
    sort("Groove_D", "210806");
    sort("Normal", "210806");
    sort("R1_17.9", "210806");
    sort("R1_18.6", "210806");
    sort("R1_19.3", "210806");
}
