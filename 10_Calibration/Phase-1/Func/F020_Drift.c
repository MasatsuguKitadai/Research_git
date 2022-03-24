int Drift(char date[], char angle[])
{
    /*****************************************************************************/

    // ディレクトリ文字列作成
    char directoryname[100];
    char directoryname_csv[100];
    char directoryname_dat[100];
    char directoryname_png[100];

    /*****************************************************************************/

    // 元ディレクトリの作成
    sprintf(directoryname, "../Result/%s/020_Drift", date);
    mkdir(directoryname, mode);

    /*****************************************************************************/

    // ディレクトリの作成
    sprintf(directoryname_dat, "../Result/%s/020_Drift/dat", date);
    sprintf(directoryname_csv, "../Result/%s/020_Drift/csv", date);
    sprintf(directoryname_png, "../Result/%s/020_Drift/png", date);

    mkdir(directoryname_dat, mode);
    mkdir(directoryname_csv, mode);
    mkdir(directoryname_png, mode);

    /*****************************************************************************/

    // ファイルの指定
    char filename_read[100];
    char filename_csv[100];
    char filename_dat[100];

    sprintf(filename_read, "../Result/%s/010_Reverse/csv/%s.csv", date, angle);
    sprintf(filename_csv, "../Result/%s/020_Drift/csv/%s.csv", date, angle);
    sprintf(filename_dat, "../Result/%s/020_Drift/dat/%s.dat", date, angle);

    /*****************************************************************************/

    // 変数宣言
    int i, j, k, l;
    int datalength = 0;
    int ch = 3;
    int data_flame = 5000;
    double value[data_flame][ch];
    double ch0, ch1, ch2, ch3; // ch0:drag, ch8:lift, ch2:load-cell
    double time = 0;

    // 配列の初期化

    for (i = 0; i < data_flame; i++)
    {
        for (j = 0; j < 3; j++)
        {
            value[i][j] = 0;
        }
    }

    // printf("check\n");

    // ファイルの読み込み
    fp = fopen(filename_read, "r");
    if (fp == NULL)
    {
        printf("02\t[%s]\tno data file\n", angle);
        return 1;
    }

    i = 0;

    while ((fscanf(fp, "%lf, %lf, %lf", &ch0, &ch1, &ch2)) != EOF)
    {
        // printf("%.3f, %.3f, %.3f\n", ch0, ch1, ch2);
        value[i][0] = ch0;
        value[i][1] = ch1;
        value[i][2] = ch2;
        i = i + 1;
    }

    fclose(fp);

    datalength = i;
    // printf("datalengh = %d\n", datalength);

    // 平均値の計算

    int count = 300;
    int average_time[5];
    double sum[3];
    double average_value[6][3];
    double offset;

    for (i = 0; i < 6; i++)
    {
        count = count + 25;

        for (j = 0; j < 3; j++)
        {
            sum[j] = 0;
        }

        for (j = count; j < count + 150; j++)
        {
            for (k = 0; k < 3; k++)
            {
                sum[k] = value[j][k] + sum[k];
            }
        }

        count = j;

        for (j = 0; j < 3; j++)
        {
            average_value[i][j] = sum[j] / 150;
        }

        count = count + 325;
        average_time[i] = count - 400;
        // printf("[%d]\t%.3f\t%.3f\t%.3f\n", average_time[i], average_value[i][0], average_value[i][1], average_value[i][2]);
        // printf("%d\n", average_time[i]);
    }

    // 補正直線の計算
    double a[3], b[3];

    // 比例定数 a
    for (i = 0; i < 3; i++)
    {
        a[i] = (average_value[5][i] - average_value[0][i]) / (average_time[5] - average_time[0]);
    }

    // 切片 b
    for (i = 0; i < 3; i++)
    {
        b[i] = average_value[0][i] - a[i] * average_time[0];
    }

    // 関数 f
    for (i = 0; i < 3; i++)
    {
        // printf("[%d]\tf(x) = %.3f x + %.3f\n", i, a[i], b[i]);
    }

    // 変数の宣言
    double f[datalength][3], c[datalength][3];

    // 配列の初期化
    for (j = 0; j < datalength; j++)
    {
        f[j][0] = 0;
        f[j][1] = 0;
        f[j][2] = 0;
    }

    // 線形補間の値の計算
    // printf("%s\n", name);
    for (j = 0; j < datalength; j++)
    {
        f[j][0] = a[0] * j + b[0];
        f[j][1] = a[1] * j + b[1];
        f[j][2] = a[2] * j + b[2];
        // printf("[%d]\t%.3f\t%.3f\n", j, f[j][1], f[j][2]);
    }

    // 補正値の計算
    for (j = 0; j < datalength; j++)
    {
        c[j][0] = value[j][0] - f[j][0];
        c[j][1] = value[j][1] - f[j][1];
        c[j][2] = value[j][2] - f[j][2];
        // printf("[%d]\t%.3f\t%.3f\n", j, c[j][1], c[j][2]);
    }

    // 書き出し
    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");

    for (j = 0; j < datalength; j++)
    {
        time = j * 0.2;
        fprintf(fp_csv, "%lf,%lf,%lf\n", c[j][0], c[j][1], c[j][2]);
        fprintf(fp_dat, "%d\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%.1f\n", j, c[j][0], c[j][1], c[j][2], f[j][0], f[j][1], f[j][2], time);
    }

    fclose(fp_csv);
    fclose(fp_dat);

    /*****************************************************************************/
    // Gnuplot //

    // ディレクトリの作成

    char directoryname_png_1[100];
    char directoryname_png_2[100];
    char directoryname_png_3[100];

    sprintf(directoryname_png_1, "../Result/%s/020_Drift/png/Loadcell", date);
    sprintf(directoryname_png_2, "../Result/%s/020_Drift/png/Drag", date);
    sprintf(directoryname_png_3, "../Result/%s/020_Drift/png/Lift", date);

    mkdir(directoryname_png_1, mode);
    mkdir(directoryname_png_2, mode);
    mkdir(directoryname_png_3, mode);

    /*****************************************************************************/

    // filename
    char filename_dat_1[100];
    char filename_dat_2[100];

    sprintf(filename_dat_1, "../Result/%s/010_Reverse/dat/%s.dat", date, angle);
    sprintf(filename_dat_2, "../Result/%s/020_Drift/dat/%s.dat", date, angle);

    char filename_png_1[100];
    char filename_png_2[100];
    char filename_png_3[100];

    sprintf(filename_png_1, "../Result/%s/020_Drift/png/Loadcell/%s.png", date, angle);
    sprintf(filename_png_2, "../Result/%s/020_Drift/png/Drag/%s.png", date, angle);
    sprintf(filename_png_3, "../Result/%s/020_Drift/png/Lift/%s.png", date, angle);

    /*****************************************************************************/

    // range x
    int x_min = 0;
    int x_max = 600;

    // range y
    double y_min = -1;
    double y_max = 1;

    // range y (loadcell)
    double y_min_loadcell = -0.5;
    double y_max_loadcell = 2.5;

    // label
    const char *xxlabel = "Time [s]";
    const char *yylabel = "Output voltage [V]";
    char label[100];

    double size;

    double angle_2 = 0;

    angle_2 = atoi(angle);
    angle_2 = angle_2;
    sprintf(label, "%0.f", angle_2);

    // size
    size = 1;

    /*****************************************************************************/

    if ((gp = popen("gnuplot", "w")) == NULL)
    {
        printf("gnuplot is not here!\n");
        exit(0); // gnuplotが無い場合、異常ある場合は終了
    }

    // graph : loadcell

    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
    fprintf(gp, "set output '%s'\n", filename_png_1);
    // fprintf(gp, "set multiplot\n");
    fprintf(gp, "set key left top\n");
    fprintf(gp, "set key font ',22'\n");
    fprintf(gp, "set term pngcairo size 1280, 960 font ',27'\n");
    // fprintf(gp, "set size ratio %.3f\n", size);

    fprintf(gp, "set lmargin screen 0.10\n");
    fprintf(gp, "set rmargin screen 0.90\n");
    fprintf(gp, "set tmargin screen 0.90\n");
    fprintf(gp, "set bmargin screen 0.15\n");

    fprintf(gp, "set xrange [%d:%d]\n", x_min, x_max);
    fprintf(gp, "set xlabel '%s'offset 0.0,0\n", xxlabel);
    fprintf(gp, "set yrange [%.3f:%.3f]\n", y_min_loadcell, y_max_loadcell);
    fprintf(gp, "set ylabel '%s'offset 1.0,0.0\n", yylabel);
    fprintf(gp, "set title 'Load cell : %s [deg]'\n", label);

    // fprintf(gp, "set samples 10000\n");
    // fprintf(gp, "plot '%s' using 8:4 with lines lc 'gray70' notitle, '%s' using 8:4 with lines lc 'gray20' notitle\n", filename_dat_1, filename_dat_2);
    fprintf(gp, "plot '%s' using 5:4 with lines lc 'gray70' title 'Raw data', '%s' using 8:4 with lines lc 'gray20' title 'Corrected', '%s' using 8:7 with lines lc 'red' title 'Correction line'\n", filename_dat_1, filename_dat_2, filename_dat_2);
    fflush(gp); // Clean up Data

    /*****************************************************************************/

    // graph : drag

    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
    fprintf(gp, "set output '%s'\n", filename_png_2);
    // fprintf(gp, "set multiplot\n");
    fprintf(gp, "set key left top\n");
    fprintf(gp, "set key font ',22'\n");
    fprintf(gp, "set term pngcairo size 1280, 960 font ',27'\n");
    // fprintf(gp, "set size ratio %.3f\n", size);

    fprintf(gp, "set lmargin screen 0.10\n");
    fprintf(gp, "set rmargin screen 0.90\n");
    fprintf(gp, "set tmargin screen 0.90\n");
    fprintf(gp, "set bmargin screen 0.15\n");

    fprintf(gp, "set xrange [%d:%d]\n", x_min, x_max);
    fprintf(gp, "set xlabel '%s'offset 0.0,0\n", xxlabel);
    fprintf(gp, "set yrange [%.3f:%.3f]\n", y_min, y_max);
    fprintf(gp, "set ylabel '%s'offset 1.0,0.0\n", yylabel);
    fprintf(gp, "set title 'Drag : %s [deg]'\n", label);

    // fprintf(gp, "set samples 10000\n");
    // fprintf(gp, "plot '%s' using 8:2 with lines lc 'gray70' notitle, '%s' using 8:2 with lines lc 'gray20' notitle\n", filename_dat_1, filename_dat_2);
    fprintf(gp, "plot '%s' using 5:2 with lines lc 'gray70' title 'Raw data', '%s' using 8:2 with lines lc 'gray20' title 'Corrected', '%s' using 8:5 with lines lc 'red' title 'Correction line'\n", filename_dat_1, filename_dat_2, filename_dat_2);
    fflush(gp); // Clean up Data

    /*****************************************************************************/

    // graph : lift

    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
    fprintf(gp, "set output '%s'\n", filename_png_3);
    // fprintf(gp, "set multiplot\n");
    fprintf(gp, "set key left top\n");
    fprintf(gp, "set key font ',22'\n");
    fprintf(gp, "set term pngcairo size 1280, 960 font ',27'\n");
    // fprintf(gp, "set size ratio %.3f\n", size);

    fprintf(gp, "set lmargin screen 0.10\n");
    fprintf(gp, "set rmargin screen 0.90\n");
    fprintf(gp, "set tmargin screen 0.90\n");
    fprintf(gp, "set bmargin screen 0.15\n");

    fprintf(gp, "set xrange [%d:%d]\n", x_min, x_max);
    fprintf(gp, "set xlabel '%s'offset 0.0,0\n", xxlabel);
    fprintf(gp, "set yrange [%.3f:%.3f]\n", y_min, y_max_loadcell);
    fprintf(gp, "set ylabel '%s'offset 1.0,0.0\n", yylabel);
    fprintf(gp, "set title 'Lift : %s [deg]'\n", label);

    fprintf(gp, "plot '%s' using 5:3 with lines lc 'gray70' title 'Raw data', '%s' using 8:3 with lines lc 'gray20' title 'Corrected', '%s' using 8:6 with lines lc 'red' title 'Correction line'\n", filename_dat_1, filename_dat_2, filename_dat_2);
    fflush(gp); // Clean up Data

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);

    printf("02\t[%s]\tsuccess\n", angle);
}