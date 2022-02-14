/******************************************************************************
PROGRAM NAME :
AUTHER  : masatsugu Kitadai
DATE    :
******************************************************************************/

#include "head.h"

/*********************************   MAIN   *********************************/

int RMSE(char date[])
{
    /*****************************************************************************/

    // ディレクトリの作成
    char directoryname[100];
    char directoryname_dat[100];
    char directoryname_csv[100];
    char directoryname_png[100];

    /*****************************************************************************/

    sprintf(directoryname, "../Result/%s/160_Error", date);
    mkdir(directoryname, mode);

    /*****************************************************************************/

    sprintf(directoryname_dat, "../Result/%s/160_Error/dat", date);
    sprintf(directoryname_csv, "../Result/%s/160_Error/csv", date);
    sprintf(directoryname_png, "../Result/%s/160_Error/png", date);

    mkdir(directoryname_dat, mode);
    mkdir(directoryname_csv, mode);
    mkdir(directoryname_png, mode);

    /*****************************************************************************/

    // ファイルの指定
    char filename_read_1[100];
    char filename_read_2[100];
    char filename_read_3[100];

    sprintf(filename_read_1, "../Result/%s/141_Rotation/csv/Rotation.csv", date);
    sprintf(filename_read_2, "../Result/%s/150_Adjust/csv/Adjust.csv", date);
    sprintf(filename_read_3, "../Result/%s/061_Summary/csv/Summary.csv", date);

    char filename_csv[100];
    char filename_dat[100];

    sprintf(filename_csv, "../Result/%s/160_Error/csv/Error.csv", date);
    sprintf(filename_dat, "../Result/%s/160_Error/dat/Error.dat", date);

    /*****************************************************************************/

    int i = 0, j = 0;
    double ch0, ch1, ch2, buf;
    double angle[24];
    double drag[24], lift[24];

    fp = fopen(filename_read_3, "r");
    if (fp == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    while ((fscanf(fp, "%lf, %lf, %lf, %lf", &buf, &ch0, &ch1, &ch2)) != EOF)
    {
        angle[i] = buf;
        drag[i] = ch0;
        lift[i] = ch1;
        // printf("[%d]\t%.3f\t%.3f\n", i, drag_net[i], lift_net[i]);
        i = i + 1;
    }

    fclose(fp);

    /*****************************************************************************/

    double drag_net[24], lift_net[24];

    fp = fopen(filename_read_1, "r");
    if (fp == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    i = 0;

    while ((fscanf(fp, "%lf, %lf, %lf, %lf", &buf, &ch0, &ch1, &ch2)) != EOF)
    {
        angle[i] = buf;
        drag_net[i] = ch0;
        lift_net[i] = ch1;
        // printf("[%d]\t%.3f\t%.3f\n", i, drag_net[i], lift_net[i]);
        i = i + 1;
    }

    fclose(fp);

    printf("\n");

    /*****************************************************************************/

    double angle_theory[24];
    double drag_theory[24], lift_theory[24];

    fp = fopen(filename_read_2, "r");
    if (fp == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    i = 0;

    while ((fscanf(fp, "%lf, %lf, %lf", &buf, &ch0, &ch1)) != EOF)
    {
        if (i % 150 == 0)
        {
            j = i / 150;
            drag_theory[j] = ch0;
            lift_theory[j] = ch1;
            // printf("[%d]\t%.3f\t%.3f\n", j, drag_net_theory[j], lift_net_theory[j]);
        }

        i = i + 1;
    }

    fclose(fp);

    /*****************************************************************************/

    double part[2], part_net[2];
    double error_drag, error_lift, error_drag_net, error_lift_net;

    for (i = 0; i < 2; i++)
    {
        part[i] = 0;
        part_net[i] = 0;
    }

    for (i = 0; i < 24; i++)
    {
        part[0] = (drag[i] - drag_theory[i]) * (drag[i] - drag_theory[i]) + part[0];
        part[1] = (lift[i] - lift_theory[i]) * (lift[i] - lift_theory[i]) + part[1];

        part_net[0] = (drag_net[i] - drag_theory[i]) * (drag_net[i] - drag_theory[i]) + part_net[0];
        part_net[1] = (lift_net[i] - lift_theory[i]) * (lift_net[i] - lift_theory[i]) + part_net[1];
    }

    error_drag = sqrt(part[0] / 24);
    error_lift = sqrt(part[1] / 24);

    error_drag_net = sqrt(part_net[0] / 24);
    error_lift_net = sqrt(part_net[1] / 24);

    printf("\t|  [Vd]\t[Vl]\t| [Vx]\t[Vy]\n");
    printf("[RMSE]\t| %.3f\t%.3f\t| %.3f\t%.3f\n", error_drag, error_lift, error_drag_net, error_lift_net);

    printf("\n30 success\n");
}

int main()
{
    RMSE("1");
    return (0);
}