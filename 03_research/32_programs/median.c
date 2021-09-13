/******************************************************************************
PROGRAM NAME : ma.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ch 2
#include "setting_files/range.h"

FILE *fp1, *fp2;
/*********************************   MAIN   *********************************/
int ma(char name[], char date[])
{
    // ファイル名の作成

    char filename1[100];
    char filename2[100];

    sprintf(filename1, "..//33_result//%s//raw_data//dat//%s.dat", date, name);     
    sprintf(filename2, "..//33_result//%s//median//%d//dat//%s_me(%d).dat", date, range_me, name, range_me);

    // printf("%s\n",filename1);
    // printf("%s\n",filename2);

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

    // 計算 (中央値)

    int j = 0;
    int a, b, c;
    int x, y, z;
    double w;

    a = (range_me - 1) / 2;
    b = data_long - 2 * a;
    c = a + 1;

    double me_d[b], me_l[b];
    double d[range_me], l[range_me];

    for (i = 0; i < b; i++)
    {
        // printf("\n[%d]\n",i);

        // 指定された範囲の配列を作成
        for (j = 0; j < range_me; j++)
        {
            d[j] = value[i + j][1];
            l[j] = value[i + j][2];
            // printf("[%d]\t%lf\n", j, d[j]);
        }

        // 並び替え
        for (x = 0; x < range_me; x++ )
        {
            // drag
            y = x;
            for (z = x; z < range_me; z++)
            {
                if (d[z] < d[y]) 
                {
                    y = z;
                }
            } 
            if (x < y) 
            {
                w = d[x];
                d[x] = d[y];
                d[y] = w; 
            }

            // lift
            y = x;
            for (z = x; z < range_me; z++)
            {
                if (l[z] < l[y]) 
                {
                    y = z;
                }
            } 
            if (x < y) 
            {
                w = l[x];
                l[x] = l[y];
                l[y] = w; 
            }

            // printf("[%d]\t%lf\t%lf\n", x, d[x], l[x]);
        }

        me_d[i] = d[c];
        me_l[i] = l[c];

        // printf("[%d]\t%lf\t%lf\n", i, me_d[i], me_l[i]);
    }

    // ファイル書き出し

    fp2 = fopen(filename2, "w");

    for (i = 0; i < b; i++)
    {
        fprintf(fp2, "%d\t%lf\t%lf\n", i, me_d[i], me_l[i]);
        // printf("[%d]\t%lf\t%lf\n", i, me_d[i], me_l[i]);
    }

    fclose(fp2);
}

int main()
{
    // 2021/8/6
    ma("C1", "210806");
    ma("Groove_A", "210806");
    ma("Groove_B", "210806");
    ma("Groove_C", "210806");
    ma("Groove_D", "210806");
    ma("Normal", "210806");
    ma("R1_17.9", "210806");
    ma("R1_18.6", "210806");
    ma("R1_19.3", "210806");

    return (0);
}