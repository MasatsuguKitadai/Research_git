int Phase_angle_lift(char date[])
{
    /*****************************************************************************/

    // ディレクトリの作成
    char directoryname[100];
    char directoryname_dat[100];
    char directoryname_csv[100];
    char directoryname_png[100];

    /*****************************************************************************/

    sprintf(directoryname, "../Result/%s/130_Phase-angle_lift", date);
    mkdir(directoryname, mode);

    /*****************************************************************************/

    sprintf(directoryname_dat, "../Result/%s/130_Phase-angle_lift/dat", date);
    sprintf(directoryname_csv, "../Result/%s/130_Phase-angle_lift/csv", date);
    sprintf(directoryname_png, "../Result/%s/130_Phase-angle_lift/png", date);

    mkdir(directoryname_dat, mode);
    mkdir(directoryname_csv, mode);
    mkdir(directoryname_png, mode);

    /*****************************************************************************/

    // ファイルの指定
    char filename_read[100];
    char filename_csv[100];
    char filename_dat[100];

    sprintf(filename_read, "../Result/%s/110_DFT_lift/csv/DFT_lift.csv", date);
    sprintf(filename_csv, "../Result/%s/130_Phase-angle_lift/csv/Phase-angle_lift.csv", date);
    sprintf(filename_dat, "../Result/%s/130_Phase-angle_lift/dat/Phase-angle_lift.dat", date);

    /*****************************************************************************/

    int i;
    int buf;
    double ch0, ch1, ch2;
    double value[100][4];

    fp = fopen(filename_read, "r");

    if (fp == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    i = 0;

    while ((fscanf(fp, "%d, %lf, %lf, %lf", &buf, &ch0, &ch1, &ch2)) != EOF)
    {
        // printf("[%d]\t%.3f\t%.3f\t%.3f\n", buf, ch0, ch1, ch2);
        value[i][0] = buf;
        value[i][1] = ch0;
        value[i][2] = ch1;
        value[i][3] = ch2;
        i = i + 1;
    }

    fclose(fp);

    // printf("\n");

    // 計算

    double gradient;
    double radian = 0;
    double degree = 0;

    gradient = value[1][3] / value[1][2];
    radian = atan2(value[1][3], value[1][2]);
    degree = 180 * radian / pi;

    if (degree == -90)
    {
        degree = 90;
    }
    else if (degree == -180)
    {
        degree = 180;
    }

    printf("[LIFT]\n");
    printf("Im/Re =\t%.3f\n", gradient);
    printf("angle(1) =\t%.3f\t[deg]\n", degree);
    printf("angle(2) =\t%.3f\t[rad]\n\n", radian);

    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");

    fprintf(fp_csv, "%lf,%lf\n", radian, degree);
    fprintf(fp_dat, "%lf\t%lf\n", radian, degree);

    fclose(fp_csv);
    fclose(fp_dat);

    printf("08-4\t\tsuccess\n");
}