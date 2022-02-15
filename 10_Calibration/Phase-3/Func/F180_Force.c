/******************************************************************************
PROGRAM NAME :
AUTHER  : masatsugu Kitadai
DATE    :
******************************************************************************/
// #include "head.h"

/*********************************   MAIN   *********************************/

int Force(char date[])
{
    /*****************************************************************************/

    // ディレクトリの作成
    char directoryname[100];
    char directoryname_dat[100];
    char directoryname_csv[100];
    char directoryname_png[100];

    /*****************************************************************************/

    sprintf(directoryname, "../Result/%s/180_Force", date);
    mkdir(directoryname, mode);

    /*****************************************************************************/

    sprintf(directoryname_dat, "../Result/%s/180_Force/dat", date);
    sprintf(directoryname_csv, "../Result/%s/180_Force/csv", date);
    sprintf(directoryname_png, "../Result/%s/180_Force/png", date);

    mkdir(directoryname_dat, mode);
    mkdir(directoryname_csv, mode);
    mkdir(directoryname_png, mode);

    /*****************************************************************************/

    // ファイルの指定
    char filename_read_1[100];
    char filename_read_2[100];
    char filename_csv[100];
    char filename_dat[100];

    sprintf(filename_read_1, "../Data/force.csv");
    sprintf(filename_read_2, "../../Phase-2/Result/%s/140_Rotation/csv/Rotation-Ave.csv", date);

    sprintf(filename_csv, "../Result/%s/180_Force/csv/Force.csv", date);
    sprintf(filename_dat, "../Result/%s/180_Force/dat/Force.dat", date);

    /*****************************************************************************/

    int i = 0;
    int datalength = 0;
    double g = 9.807;
    double ch0, ch1, ch2;
    double net;
    double nut[11], voltage[11];

    fp = fopen(filename_read_1, "r");

    if (filename_read_1 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    while ((fscanf(fp, "%lf, %lf", &ch0, &ch1)) != EOF)
    {
        nut[i] = ch0 / 1000 * g; // 荷重からニュートンへの変換
        voltage[i] = ch1;
        i = i + 1;
    }

    datalength = i;

    fclose(fp);

    /*****************************************************************************/

    fp = fopen(filename_read_2, "r");

    fscanf(fp, "%lf, %lf, %lf", &ch0, &ch1, &ch2);

    net = ch2;

    fclose(fp);

    /*****************************************************************************/

    double value[2];
    double part[2];
    double average[2];

    for (i = 0; i < 2; i++)
    {
        value[i] = 0;
        part[i] = 0;
        average[i] = 0;
    }

    for (i = 0; i < datalength; i++)
    {
        value[0] = voltage[i] + value[0]; // 電圧
        value[1] = nut[i] + value[1];     // 荷重
    }

    average[0] = value[0] / datalength;
    average[1] = value[1] / datalength;

    for (i = 0; i < datalength; i++)
    {
        part[0] = (voltage[i] - average[0]) * (nut[i] - average[1]) + part[0];
        part[1] = (voltage[i] - average[0]) * (voltage[i] - average[0]) + part[1];
    }

    double a, b;

    a = part[0] / part[1];
    b = average[1] - a * average[0];

    printf("f(x) = %.3f x + %.3f [N/V]\t", a, b);
    printf("(Newton / Load cell voltage)\n");

    /*****************************************************************************/

    double c;

    c = a / net;
    printf("C = %.3f [N/V]\n", c);

    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");

    fprintf(fp_csv, "%lf\t%lf", c, a);
    fprintf(fp_dat, "%lf\t%lf", c, a);

    fclose(fp_csv);
    fclose(fp_dat);
}

// int main()
// {
//     Force("1");
//     return (0);
// }