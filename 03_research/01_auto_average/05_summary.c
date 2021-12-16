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
    char filename_csv_ave[100];
    char filename_dat[100];
    char filename_dat_ave[100];

    sprintf(filename_csv,"result/%s/05_csv_summary/%s_summary.csv",  date, date);
    sprintf(filename_dat,"result/%s/05_dat_summary/%s_summary.dat",  date, date);
    sprintf(filename_csv_ave,"result/%s/05_csv_summary/%s_summary_ave.csv",  date, date);
    sprintf(filename_dat_ave,"result/%s/05_dat_summary/%s_summary_ave.dat",  date, date);

    int i = 0;
    int angle = 0;
    double ch0, ch1, ch2;
    double value[24][3];
    double sum[3];
    double ave[3];

    for (i = 0; i < 3; i++)
    {
        sum[i] = 0;
        ave[i] = 0;
    }
    

    for(i = 0; i < 24; i++)
    {
        angle = 15 * i;
        sprintf(filename_read,"result/%s/04_csv_gradient/%d_gradient.csv",  date, angle);

        fp = fopen(filename_read, "r");
        if (filename_read == NULL)
        {
            printf("Error! I can't open the file.\n");
            exit(0);
        }

        fscanf(fp, "%lf, %lf, %lf", &ch0, &ch1, &ch2);
        printf("【%d】\t%lf\t%lf\t%lf\n", angle, ch0, ch1, ch2);
        value[i][0] = ch0; // drag
        value[i][1] = ch1; // lift
        value[i][2] = ch2; // sqrt

        sum[0] = ch0 + sum[0];
        sum[1] = ch1 + sum[1];
        sum[2] = ch2 + sum[2];

        fclose(fp);
    }

    ave[0] = sum[0] / 24;
    ave[1] = sum[1] / 24;
    ave[2] = sum[2] / 24;

    printf("average of drag = %lf\n", ave[0]);
    printf("average of lift = %lf\n", ave[1]);
    printf("average of sqrt = %lf\n", ave[2]);


// plot用 データファイルの書き出し

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

    fp_csv = fopen(filename_csv_ave, "w");
    fp_dat = fopen(filename_dat_ave, "w");

    fprintf(fp_csv, "%lf\t%lf\t%lf\n", ave[0], ave[1], ave[2]);
    fprintf(fp_dat, "-30\t%lf\t%lf\t%lf\n", ave[0], ave[1], ave[2]);
    fprintf(fp_dat, "360\t%lf\t%lf\t%lf\n", ave[0], ave[1], ave[2]);

    fclose(fp_csv);
    fclose(fp_dat);
}

int main()
{
    // simulation
    summary("simulation_data");

    return (0);
}