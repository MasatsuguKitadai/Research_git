/******************************************************************************
PROGRAM NAME : 07_fft.c
AUTHER  : masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "files/fp.h"

FILE *fp;
const char filename[100] = "../../31_data/test_data/sin_n=256.dat";

/*********************************   MAIN   *********************************/

int main()
{

#include "files/fft.h"

// n=256の正弦波について

    // 変数の作成

    int range = 256;
    double value[range], value_i[range]; 

    // ファイルの読み込み (dat データ)

    fp = fopen(filename, "r");
    if (filename == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    // データの格納

    int i = 0;
    int num;
    double row1, row2;

    while ((fscanf(fp, "%d\t%lf\t%lf", &num, &row1, &row2)) != EOF)
    {
        value[i] = row2;
        i = i + 1;
        printf("%d\t%lf\t%lf\n", num, row1, row2);
    }

    fclose(fp);

    S_fft(value, value_i, range, 1);
}