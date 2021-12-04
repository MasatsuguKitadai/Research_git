/******************************************************************************
PROGRAM NAME :
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FILE *fp;

// 読み込みファイルの指定
char filename_1[100] = "data/0.CSV";
char filename_2[100] = "data_reverse/0_reverse.CSV";

/*********************************   MAIN   *********************************/
int main()
{
    printf("check");

    // 変数宣言
    int i, j;
    int datalength = 0;
    int ch = 3;
    double value[1000][ch];
    double ch0, ch1, ch2; // ch0:drag, ch1:lift, ch2:load-cell

    // 配列の初期化

    for (i = 0; i < 1000; i++)
    {
        for (j = 0; j < 3; j++)
        {
            value[i][j] = 0;
        }
    }

    printf("check");

    // ファイルの読み込み
    fp = fopen(filename_1, "r");
    if (filename_1 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    i = 0;

    while ((fscanf(fp, "%lf, %lf, %lf", &ch0, &ch1, &ch2)) != EOF)
    {
        printf("%lf, %lf, %lf\n", ch0, ch1, ch2);
        value[i][0] = ch0;
        value[i][1] = ch1;
        value[i][2] = ch2;
        i = i + 1;
    }

    fclose(fp);

    datalength = i;
    printf("datalengh = %d\n", datalength);

    // 計算

    for ( i = 0; i < datalength; i++)
    {
        value[i][2] = -1 * value[i][2];
    }

    fp = fopen(filename_2, "w");

    for (i = 0; i < datalength; i++)
    {
        fprintf(fp, "%lf,%lf,%lf\n", value[i][0], value[i][1], value[i][2]);
    }

    fclose(fp);
}