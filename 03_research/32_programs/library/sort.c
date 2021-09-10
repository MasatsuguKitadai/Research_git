/******************************************************************************
PROGRAM NAME :sort.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ch 2
FILE *fp1, *fp2;
/*********************************   MAIN   *********************************/

int sort(char filename_1[], char filename_2[])
{
    int i, j;

    // ファイルの読み込み

    fp1 = fopen(filename_1, "r");
    if (filename_1 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    // データの格納

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

    fp2 = fopen(filename_2, "w");

    for (j = 0; j < i; j++)
    {
        fprintf(fp2, "%d\t%lf\t%lf\n", j,  value[j][1], value[j][2] );
    }

    fclose(fp2);

    return (0);
}

int main()
{
    // 210806
    // sort("../31_data/210806/C1.CSV", "../34_result/210806/raw_data/dat/C1.dat");
    // sort("../31_data/210806/Groove_A.CSV", "../34_result/210806/raw_data/dat/Groove_A.dat");
    // sort("../31_data/210806/Groove_B.CSV", "../34_result/210806/raw_data/dat/Groove_B.dat");
    // sort("../31_data/210806/Groove_C.CSV", "../34_result/210806/raw_data/dat/Groove_C.dat");
    // sort("../31_data/210806/Groove_D.CSV", "../34_result/210806/raw_data/dat/Groove_D.dat");
    // sort("../31_data/210806/Normal.CSV", "../34_result/210806/raw_data/dat/Normal.dat");
    // sort("../31_data/210806/R1_17.9.CSV", "../34_result/210806/raw_data/dat/R1_17.9.dat");
    // sort("../31_data/210806/R1_18.6.CSV", "../34_result/210806/raw_data/dat/R1_18.6.dat");
    // sort("../31_data/210806/R1_19.3.CSV", "../34_result/210806/raw_data/dat/R1_19.3.dat");
}
