/******************************************************************************
PROGRAM NAME :
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>

FILE *fp, *fp_dat, *fp_csv, *gp;
/*********************************   MAIN   *********************************/
int correct_offset(char date[], int split, double delta_y, double delta_x)
{
    /*****************************************************************************/
    // ディレクトリの作成
    char directoryname_dat[100];
    char directoryname_csv[100];

    sprintf(directoryname_dat, "../result/%s/dat/11_offset-correct", date);
    sprintf(directoryname_csv, "../result/%s/csv/11_offset-correct", date);

    mkdir(directoryname_dat, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_csv, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    /*****************************************************************************/

    // filename
    char filename_read[100];
    char filename_csv[100];
    char filename_dat[100];

    sprintf(filename_read, "../result/%s/csv/05-1_summary/05-1.csv", date);
    // sprintf(filename_csv, "../result/%s/csv/11_offset-correct/11.csv", date);
    // sprintf(filename_dat, "../result/%s/dat/11_offset-correct/11.dat", date);

    sprintf(filename_csv, "../result/%s/csv/05-1_summary/05-1.csv", date);
    sprintf(filename_dat, "../result/%s/dat/05-1_summary/05-1.dat", date);

    /*****************************************************************************/

    int i = 0;
    double buf;
    int angle[split];
    double ch0, ch1, ch2;
    double value[split][3];

    fp = fopen(filename_read, "r");
    if (fp == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    while ((fscanf(fp, "%lf, %lf, %lf, %lf", &buf, &ch0, &ch1, &ch2)) != EOF)
    {
        // printf("%.1f, %.3f, %.3f, %.3f\n", buf, ch0, ch1, ch2);
        angle[i] = buf;
        value[i][0] = ch0; // drag
        value[i][1] = ch1; // lift
        value[i][2] = ch2; // sqrt
        i = i + 1;
    }

    fclose(fp);

    /*****************************************************************************/

    double F[split][3];
    double psi[split], phi[split], theta[split];
    double r = 25; // 供試体の半径

    printf("\t[psi]\tF[x]\tF[y]\tF[net]\n");

    for (i = 0; i < split; i++)
    {
        theta[i] = 150 * i * pi / 1800;
        phi[i] = theta[i] - asin((cos(theta[i]) * delta_y - sin(theta[i]) * delta_x) / r);
        psi[i] = -1 * theta[i] + phi[i];

        F[i][0] = value[i][0] / cos(psi[i]);
        F[i][1] = value[i][1] / cos(psi[i]);
        F[i][2] = sqrt(F[i][0] * F[i][0] + F[i][1] * F[i][1]);

        theta[i] = theta[i] * 180 / pi;
        psi[i] = psi[i] * 180 / pi;
        printf("[%.1f]\t%.3f\t%.3f\t%.3f\t%.3f\n", theta[i], phi[i], F[i][0], F[i][1], F[i][2]);
    }

    /*****************************************************************************/

    // plot用 データファイルの書き出し

    double angle_double;

    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");

    for (i = 0; i < split; i++)
    {
        angle_double = i * 150;
        angle_double = angle_double / 10;

        fprintf(fp_csv, "%.1f,%lf,%lf,%lf\n", angle_double, F[i][0], F[i][1], F[i][2]);
        fprintf(fp_dat, "%.1f\t%.3f\t%.3f\t%.3f\n", angle_double, F[i][0], F[i][1], F[i][2]);
        // printf("%.3f\t%.3f\t%.3f\t%.3f\n", angle_double, value[i][0], value[i][1], value[i][2]);
    }

    fclose(fp_csv);
    fclose(fp_dat);

    printf("\n11\t\tsuccess\n");
}

// int main()
// {
//     // simulation
//     evaluation("testdata");

//     return (0);
// }