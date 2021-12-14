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
int linear(char date[], char angle[])
{
 // 変数宣言
    int i, j, k, l;
    int datalength = 0;
    int ch = 3;
    int data_flame = 6;
    double average_value[data_flame][ch];
    double ch0, ch1, ch2, ch3; // ch0:drag, ch1:lift, ch2:load-cell

    // 読み込みファイルの指定
    char filename_read[100];
    char filename_csv_1[100];
    char filename_csv_2[100];
    char filename_dat_1[100];
    char filename_dat_2[100];

    sprintf(filename_read,"result/%s/csv_average/%s_average.csv",  date, angle);
    sprintf(filename_csv_1, "result/%s/csv_linear/%s_linear.csv",   date, angle);
    sprintf(filename_dat_1, "result/%s/dat_linear/%s_linear.dat",   date, angle);
    sprintf(filename_csv_2, "result/%s/csv_gradient/%s_gradient.csv",   date, angle);
    sprintf(filename_dat_2, "result/%s/dat_gradient/%s_gradient.dat",   date, angle);
    printf("【%s】\n", angle);

    // 配列の初期化

    for (i = 0; i < data_flame; i++)
    {
        for (j = 0; j < 3; j++)
        {
            average_value[i][j] = 0;
        }
    }

    // printf("check\n");

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
        average_value[i][0] = ch0;
        average_value[i][1] = ch1;
        average_value[i][2] = ch2;
        i = i + 1;
    }

    fclose(fp);

    datalength = i;
    printf("datalengh = %d\n", datalength);

    // 計算

    int n = 3;
    double result_drag[n];
    double result_lift[n];

    double a1[2], b1, sqrt_value;
    double sum1, sum2, sum3, sum4;

    // 近似直線の計算(drag)
    a1[0] = 0;
    b1 = 0;
    sum1 = 0;
    sum2 = 0;
    sum3 = 0;
    sum4 = 0;

    for (i = 0; i < datalength; i++)
    {
        sum1 = sum1 + average_value[i][2];
        sum2 = sum2 + average_value[i][0];
        sum3 = sum3 + (average_value[i][2] * average_value[i][2]);
        sum4 = sum4 + (average_value[i][2] * average_value[i][0]);
    }

    a1[0] = (datalength * sum4 - sum1 * sum2) / (datalength * sum3 - sum1 * sum1);
    b1 = (sum3 * sum2 - sum4 * sum1) / (datalength * sum3 - sum1 * sum1);

    printf("f[x] = %lf x + %lf\t[loadcell - drag]\n", a1[0], b1);

    for (i = 0; i < n; i++)
    {
        result_drag[i] = a1[0] * i + b1;
    }

   // 近似直線の計算(lift)
    a1[1] = 0;
    b1 = 0;
    sum1 = 0;
    sum2 = 0;
    sum3 = 0;
    sum4 = 0;

    for (i = 0; i < datalength - 1; i++)
    {
        sum1 = sum1 + average_value[i][2];
        sum2 = sum2 + average_value[i][1];
        sum3 = sum3 + (average_value[i][2] * average_value[i][2]);
        sum4 = sum4 + (average_value[i][2] * average_value[i][1]);
    }

    a1[1] = (datalength * sum4 - sum1 * sum2) / (datalength * sum3 - sum1 * sum1);
    b1 = (sum3 * sum2 - sum4 * sum1) / (datalength * sum3 - sum1 * sum1);

    sqrt_value = sqrt((a1[0] * a1[0]) + (a1[1] * a1[1]));

    printf("f[x] = %lf x + %lf\t[loadcell - lift]\t%lf\n", a1[1], b1, sqrt_value);

    for (i = 0; i < n; i++)
    {
        result_lift[i] = a1[1] * i + b1;
    }

    fp_csv = fopen(filename_csv_1, "w");
    fp_dat = fopen(filename_dat_1, "w");

    for (i = 0; i < n; i++)
    {
        fprintf(fp_csv, "%lf,%lf\n", result_drag[i], result_lift[i]);
        fprintf(fp_dat, "%d\t%lf\t%lf\n", i, result_drag[i], result_lift[i]);
    }

    fclose(fp_csv);
    fclose(fp_dat);

    fp_dat = fopen(filename_dat_2, "w");
    fp_csv = fopen(filename_csv_2, "w");

    fprintf(fp_csv, "%lf,%lf,%lf\n", a1[0], a1[1], sqrt_value);
    fprintf(fp_dat, "%lf\t%lf\t%lf\n", a1[0], a1[1], sqrt_value);

    fclose(fp_csv);
    fclose(fp_dat);

}

int main()
{
    // 211208
    // linear("211208", "0");
    // linear("211208", "15");
    // linear("211208", "30");
    // linear("211208", "45");
    // linear("211208", "60");
    // linear("211208", "75");
    // linear("211208", "90");

    // simulation
    linear("simulation_data", "0");
    linear("simulation_data", "15");
    linear("simulation_data", "30");
    linear("simulation_data", "45");
    linear("simulation_data", "60");
    linear("simulation_data", "75");
    linear("simulation_data", "90");
    linear("simulation_data", "105");
    linear("simulation_data", "120");
    linear("simulation_data", "135");
    linear("simulation_data", "150");
    linear("simulation_data", "165");
    linear("simulation_data", "180");
    linear("simulation_data", "195");
    linear("simulation_data", "210");
    linear("simulation_data", "225");
    linear("simulation_data", "240");
    linear("simulation_data", "255");
    linear("simulation_data", "270");
    linear("simulation_data", "285");
    linear("simulation_data", "300");
    linear("simulation_data", "315");
    linear("simulation_data", "330");
    linear("simulation_data", "345");

    return (0);
}