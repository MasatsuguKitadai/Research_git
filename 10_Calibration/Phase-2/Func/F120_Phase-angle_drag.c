int Phase_angle_drag(char date[])
{
    /*****************************************************************************/

    // ディレクトリの作成
    char directoryname[100];
    char directoryname_dat[100];
    char directoryname_csv[100];
    char directoryname_png[100];

    /*****************************************************************************/

    sprintf(directoryname, "../Result/%s/120_Phase-angle_drag", date);
    mkdir(directoryname, mode);

    /*****************************************************************************/

    sprintf(directoryname_dat, "../Result/%s/120_Phase-angle_drag/dat", date);
    sprintf(directoryname_csv, "../Result/%s/120_Phase-angle_drag/csv", date);
    sprintf(directoryname_png, "../Result/%s/120_Phase-angle_drag/png", date);

    mkdir(directoryname_dat, mode);
    mkdir(directoryname_csv, mode);
    mkdir(directoryname_png, mode);

    /*****************************************************************************/
    // ファイルの指定
    char filename_read[100];
    char filename_csv[100];
    char filename_dat[100];

    sprintf(filename_read, "../Result/%s/100_DFT_drag/csv/DFT_drag.csv", date);
    sprintf(filename_csv, "../Result/%s/120_Phase-angle_drag/csv/Phase-angle_drag.csv", date);
    sprintf(filename_dat, "../Result/%s/120_Phase-angle_drag/dat/Phase-angle_drag.dat", date);

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
        value[i][0] = buf; // 波数
        value[i][1] = ch0; // パワースペクトル
        value[i][2] = ch1; // 実部
        value[i][3] = ch2; // 虚部
        i = i + 1;
    }

    fclose(fp);

    // 計算

    double gradient;
    double radian;
    double degree;

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

    // printf("pi = %.3f\n", pi);

    printf("[DRAG]\n");
    printf("Im/Re =\t%.3f\n", gradient);
    printf("angle(1) =\t%.3f\t[deg]\n", degree);
    printf("angle(2) =\t%.3f\t[rad]\n\n", radian);

    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");

    fprintf(fp_csv, "%lf,%lf\n", radian, degree);
    fprintf(fp_dat, "%lf\t%lf\n", radian, degree);

    fclose(fp_csv);
    fclose(fp_dat);

    printf("08-3\t\tsuccess\n");
}