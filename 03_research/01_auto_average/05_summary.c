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
int summary(char date[])
{
    // ファイル名作成
    char filename_read[100];
    char filename_csv[100];
    char filename_dat[100];

    sprintf(filename_csv,"result/%s/csv_summary/%s_summary.csv",  date, date);
    sprintf(filename_dat,"result/%s/dat_summary/%s_summary.dat",  date, date);

    int i = 0;
    int angle = 0;
    double ch0, ch1, ch2;
    double value[24][3];

    for(i = 0; i < 24; i++)
    {
        angle = 15 * i;
        sprintf(filename_csv,"result/%s/csv_gradient/%d_gradient.csv",  date, angle);
        
        fp = fopen(filename_read, "r");
        if (filename_read == NULL)
        {
            printf("Error! I can't open the file.\n");
            exit(0);
        }

        fscanf(fp, "%lf, %lf, %lf", &ch0, &ch1, &ch2);
        printf("%lf, %lf, %lf\n", ch0, ch1, ch2);
        value[i][0] = ch0; // drag
        value[i][1] = ch1; // lift
        value[i][2] = ch2; // sqrt

        fclose(fp);
    }

    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");

    for (i = 0; i < 24; i++)
    {
        angle = i * 15;
        fprintf(fp_csv, "%d,%lf,%lf,%lf\n", angle, value[i][0], value[i][1], value[i][2]);
        fprintf(fp_dat, "%d\t%lf\t%lf\t%lf\n", angle, value[i][0], value[i][1], value[i][2]);
    }

    fclose(fp_csv);
    fclose(fp_dat);
}

int main()
{
    // simulation
    ("simulation_data");

    return (0);
}