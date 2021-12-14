/******************************************************************************
PROGRAM NAME :
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FILE *fp, *fp_dat, *fp_csv;
/*********************************   MAIN   *********************************/
int reverse(char date[], char angle[])
{
    // 読み込みファイルの指定
    char filename_read[100];
    char filename_csv[100];
    char filename_dat[100];

    sprintf(filename_read, "data/%s/%s.csv", date, angle);
    sprintf(filename_csv, "result/%s/csv_reverse/%s_reverse.csv", date, angle);
    sprintf(filename_dat, "result/%s/dat_reverse/%s_reverse.dat", date, angle);

    // 変数宣言
    int i, j;
    int datalength = 0;
    int ch = 3;
    double value[5000][ch];
    double ch0, ch1, ch2; // ch0:drag, ch1:lift, ch2:load-cell

    // 配列の初期化

    for (i = 0; i < 5000; i++)
    {
        for (j = 0; j < 3; j++)
        {
            value[i][j] = 0;
        }
    }

    // printf("check");

    // ファイルの読み込み
    fp = fopen(filename_read, "r");
    if (filename_read == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    i = 0;

    while ((fscanf(fp, "%lf, %lf, %lf", &ch0, &ch1, &ch2)) != EOF)
    {
        // printf("%lf, %lf, %lf\n", ch0, ch1, ch2);
        value[i][0] = ch0;
        value[i][1] = ch1;
        value[i][2] = ch2;
        i = i + 1;
    }

    fclose(fp);

    datalength = i;
    // printf("datalengh = %d\n", datalength);

    // 計算

    for ( i = 0; i < datalength; i++)
    {
        value[i][2] = -1 * value[i][2];
    }

    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");

    for (i = 0; i < datalength; i++)
    {
        fprintf(fp_csv, "%lf,%lf,%lf\n", value[i][0], value[i][1], value[i][2]);
        fprintf(fp_dat, "%d\t%lf\t%lf\t%lf\n", i, value[i][0], value[i][1], value[i][2]);
    }

    fclose(fp_csv);
    fclose(fp_dat);
}

int main()
{
    // 211207
    // reverse("211207", "0");
    // reverse("211207", "0_sample_10");

    // 211208
    // reverse("211208", "0");
    // reverse("211208", "15");
    // reverse("211208", "30");
    // reverse("211208", "45");
    // reverse("211208", "60");
    // reverse("211208", "75");
    // reverse("211208", "90");

    // simulation
    reverse("simulation_data", "0");
    reverse("simulation_data", "15");
    reverse("simulation_data", "30");
    reverse("simulation_data", "45");
    reverse("simulation_data", "60");
    reverse("simulation_data", "75");
    reverse("simulation_data", "90");
    reverse("simulation_data", "105");
    reverse("simulation_data", "120");
    reverse("simulation_data", "135");
    reverse("simulation_data", "150");
    reverse("simulation_data", "165");
    reverse("simulation_data", "180");
    reverse("simulation_data", "195");
    reverse("simulation_data", "210");
    reverse("simulation_data", "225");
    reverse("simulation_data", "240");
    reverse("simulation_data", "255");
    reverse("simulation_data", "270");
    reverse("simulation_data", "285");
    reverse("simulation_data", "300");
    reverse("simulation_data", "315");
    reverse("simulation_data", "330");
    reverse("simulation_data", "345");
    return (0);
}