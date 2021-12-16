/******************************************************************************
PROGRAM NAME :
AUTHER  : masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FILE *fp, *fp_csv, *fp_dat;

// 円周率の定義
#define pi 4 * atan(1.0)

char filename_read[100];
char filename_dat[100];
char filename_csv[100];

/*********************************   MAIN   *********************************/

int phase_angle(char date[])
{
    sprintf(filename_read ,"result/%s/07_csv_fft/%s_fft_drag.csv",  date, date);
    sprintf(filename_csv ,"result/%s/08_phase_angle/%s.csv", date, date);
    sprintf(filename_dat ,"result/%s/08_phase_angle/%s.dat", date, date);

    int i;
    int buf;
    double ch0, ch1, ch2;
    double value[100][4];

    fp = fopen(filename_read, "r");

    if (filename_read == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    i = 0;

    while ((fscanf(fp, "%d, %lf, %lf, %lf", &buf, &ch0, &ch1, &ch2)) != EOF)
    {
        printf("[%d]\t%lf\t%lf\t%lf\n", buf, ch0, ch1, ch2);
        value[i][0] = buf;
        value[i][1] = ch0;
        value[i][2] = ch1;
        value[i][3] = ch2;
        i = i + 1;
    }

    fclose(fp);

    // 計算

    double gradient;
    double phase_angle;
    double angle;

    gradient = value[1][3] / value[1][2];
    phase_angle = atan(gradient);
    angle = phase_angle * pi / 180;

    printf("angle =\t%lf\n", phase_angle);

    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");

    // fprintf(fp_csv, "%lf\t%lf\t%lf\t%lf\n", );
    // fprintf(fp_dat, "%lf\t%lf\t%lf\t%lf\n", );
    // printf("[%d]\tvalue: %lf \tvalue_: %lf\tpw: %lf\tfq :%lf\n", i, value[i], value_i[i], ps, fq);

    fclose(fp_csv);
    fclose(fp_dat);
}

int main()
{
    phase_angle("simulation_data");
    return (0);
}