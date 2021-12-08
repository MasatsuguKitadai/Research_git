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
int sqrt(char date[], char angle[])
{
 // 変数宣言
    int i, j, k, l;
    int ch = 2;
    double gradient_value[ch];
    double ch0, ch1; // ch0:drag, ch1:lift

    // 読み込みファイルの指定
    char filename_read[100];
    char filename_csv[100];
    char filename_dat[100];

    sprintf(filename_read,"%s/csv_gradient/%s_gradient.CSV",  date, angle);
    sprintf(filename_csv, "%s/csv_sqrt/%s_sqrt.CSV",   date, angle);
    sprintf(filename_dat, "%s/dat_sqrt/%s_sqrt.dat",   date, angle);
    printf("【%s】\n", angle);

    // ファイルの読み込み
    fp = fopen(filename_read, "r");
    if (filename_read == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }


    fscanf(fp, "%lf, %lf", &ch0, &ch1)) != EOF)
    gradient_value[0] = ch0;
    gradient_value[1] = ch1;

    fclose(fp);

    // 計算

    double sqrt[];


    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");

    for (i = 0; i < n; i++)
    {
        fprintf(fp_csv, "%lf,%lf\n", result_drag[i], result_lift[i]);
        fprintf(fp_dat, "%d\t%lf\t%lf\n", i, result_drag[i], result_lift[i]);
    }

    fclose(fp_csv);
    fclose(fp_dat);


}

int main()
{
    // 211208
    linear("211208", "0");
    linear("211208", "15");
    linear("211208", "30");
    linear("211208", "45");
    linear("211208", "60");
    linear("211208", "75");
    linear("211208", "90");

    return (0);
}