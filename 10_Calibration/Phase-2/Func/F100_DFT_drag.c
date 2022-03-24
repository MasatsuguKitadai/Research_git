int DFT_drag(char date[], int range)
{
    // ディレクトリの作成
    char directoryname[100];
    char directoryname_dat[100];
    char directoryname_csv[100];
    char directoryname_png[100];

    /*****************************************************************************/

    sprintf(directoryname, "../Result/%s/100_DFT_drag", date);
    mkdir(directoryname, mode);

    /*****************************************************************************/

    sprintf(directoryname_dat, "../Result/%s/100_DFT_drag/dat", date);
    sprintf(directoryname_csv, "../Result/%s/100_DFT_drag/csv", date);
    sprintf(directoryname_png, "../Result/%s/100_DFT_drag/png", date);

    mkdir(directoryname_dat, mode);
    mkdir(directoryname_csv, mode);
    mkdir(directoryname_png, mode);

    /*****************************************************************************/
    // ファイルの指定
    char filename_read[100];
    char filename_csv[100];
    char filename_dat[100];

    sprintf(filename_read, "../Result/%s/090_Interpolation/csv/Interpolation.csv", date);
    sprintf(filename_csv, "../Result/%s/100_DFT_drag/csv/DFT_drag.csv", date);
    sprintf(filename_dat, "../Result/%s/100_DFT_drag/dat/DFT_drag.dat", date);

    /*****************************************************************************/

    // 変数の作成

    double value[range], value_i[range];

    // ファイルの読み込み (dat データ) ・格納

    int i;
    double buf;
    double ch0, ch1, ch2;

    for (i = 0; i < range; i++)
    {
        value[i] = 0;
        value_i[i] = 0;
    }

    i = 0;

    fp = fopen(filename_read, "r");

    if (fp == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    // printf("check\n");

    while ((fscanf(fp, "%lf, %lf, %lf, %lf", &buf, &ch0, &ch1, &ch2)) != EOF)
    {
        // printf("[%.1f]\t%.3f\t%.3f\t%.3f\n", buf, ch0, ch1, ch2);
        value[i] = ch0;
        i = i + 1;
    }

    fclose(fp);

    // dftの適用

    double ps, as, dt;
    int fq;
    dt = 1;

    S_dft(value, value_i, range, 1);

    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");

    for (i = 0; i < range; i++)
    {
        if (value[i] == -0)
        {
            value[i] = -1 * value[i];
        }
        else if (value_i[i] == -0)
        {
            value_i[i] = -1 * value_i[i];
        }

        ps = value[i] * value[i] + value_i[i] * value_i[i];       /* パワースペクトル  */
        as = sqrt(value[i] * value[i] + value_i[i] * value_i[i]); /* 振幅スペクトル  */
        // fq = (double)i / (dt * (double)range);
        fq = i;

        fprintf(fp_csv, "%d,%lf,%lf,%lf\n", fq, ps, value[i], value_i[i]);
        fprintf(fp_dat, "%d\t%lf\t%lf\t%lf\n", fq, ps, value[i], value_i[i]);
        printf("[%d]\tvalue_Re = %.3f \tvalue_Im = %.3f\t pw: %.3f\tfq :%d\n", i, value[i], value_i[i], ps, fq);
    }

    fclose(fp_csv);
    fclose(fp_dat);

    printf("\n");

    /*****************************************************************************/
    // Gnuplot //

    char filename_png[100];

    sprintf(filename_dat, "../Result/%s/100_DFT_drag/dat/DFT_drag.dat", date);
    sprintf(filename_png, "../Result/%s/100_DFT_drag/png/DFT_drag.png", date);

    /*****************************************************************************/

    // range x
    double x_min = 0;
    int x_max = range / 2;

    // range y
    double y_min = 0;
    double y_max = 100;

    // label
    char label[100] = "DFT";
    char xxlabel[100] = "Number of waves [-]";
    char yylabel[100] = "Power [-]";

    double size;

    // size
    size = 1;

    /*****************************************************************************/

    if ((gp = popen("gnuplot", "w")) == NULL)
    {
        printf("gnuplot is not here!\n");
        exit(0); // gnuplotが無い場合、異常ある場合は終了
    }

    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");

    fprintf(gp, "set output '%s'\n", filename_png);
    // fprintf(gp, "set multiplot\n");
    fprintf(gp, "set key left top\n");
    fprintf(gp, "set key font ',22'\n");
    fprintf(gp, "set term pngcairo size 1280, 960 font ',27'\n");
    // fprintf(gp, "set size ratio %.3f\n", size);

    fprintf(gp, "set lmargin screen 0.10\n");
    fprintf(gp, "set rmargin screen 0.90\n");
    fprintf(gp, "set tmargin screen 0.90\n");
    fprintf(gp, "set bmargin screen 0.15\n");

    fprintf(gp, "set xrange [%.3f:%d]\n", x_min, x_max);
    fprintf(gp, "set xlabel '%s'offset 0.0,0\n", xxlabel);
    fprintf(gp, "set xtics 1\n");
    fprintf(gp, "set yrange [%.3f:%.3f]\n", y_min, y_max);
    fprintf(gp, "set ylabel '%s'offset 1,0.0\n", yylabel);
    fprintf(gp, "set title '%s (drag)'\n", label);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:2 with lines lc 'black' notitle\n", filename_dat);
    fflush(gp); // Clean up Data

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);

    printf("07-3\t\tsuccess\n");
}