/******************************************************************************
PROGRAM NAME :
AUTHER  : masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>

// 円周率の定義
#define pi 4 * atan(1.0)

char filename_read[100];
char filename_dat[100];
char filename_csv[100];

FILE *fp, *fp_csv, *fp_dat, *gp;

/*********************************   FFT   *********************************/

void S_fft_1(double ak[], double bk[], int n, int ff)
{
    /* ff=1 for FFT, ff=-1 for Inverse FT */
    int i, j, k, k1, num, nhalf, phi, phi0, rot[n];
    double s, sc, c, a0, b0, tmp;

    for (i = 0; i < n; i++)
    {
        rot[i] = 0;
    }

    nhalf = n / 2;
    num = n / 2;
    sc = (2.0 * pi) / (double)n;

    while (num >= 1)
    {
        for (j = 0; j < n; j += (2 * num))
        {
            phi = rot[j] / 2;
            phi0 = phi + nhalf;

            for (k = j; k < j + num; k++)
            {
                k1 = k + num;
                a0 = ak[k1] * cos(sc * (double)phi) - bk[k1] * ff * sin(sc * (double)(phi));
                b0 = ak[k1] * ff * sin(sc * (double)(phi)) + bk[k1] * cos(sc * (double)phi);
                ak[k1] = ak[k] - a0;
                bk[k1] = bk[k] - b0;
                ak[k] = ak[k] + a0;
                bk[k] = bk[k] + b0;
                rot[k] = phi;
                rot[k1] = phi0;
            }
        }
        num = num / 2;
    }

    if (ff < 0)
    {
        for (i = 0; i < n; i++)
        {
            ak[i] /= (double)n;
            bk[i] /= (double)n;
        }
    }

    for (i = 0; i < n - 1; i++)
    {
        if ((j = rot[i]) > i)
        {
            tmp = ak[i];
            ak[i] = ak[j];
            ak[j] = tmp;
            tmp = bk[i];
            bk[i] = bk[j];
            bk[j] = tmp;
        }
    }
}

/*********************************   MAIN   *********************************/

int calculate_drag(char date[], int range)
{
    /*****************************************************************************/
    // ディレクトリの作成
    char directoryname_csv[100];
    char directoryname_dat[100];

    sprintf(directoryname_dat, "../result/%s/dat/07-1_fft-drag", date);
    sprintf(directoryname_csv, "../result/%s/csv/07-1_fft-drag", date);

    mkdir(directoryname_dat, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    mkdir(directoryname_csv, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    // ファイルの指定
    char filename_read[100];
    char filename_csv[100];
    char filename_dat[100];

    sprintf(filename_read, "../result/%s/csv/05-1_summary/05-1.csv", date);
    sprintf(filename_csv, "../result/%s/csv/07-1_fft-drag/07-1.csv", date);
    sprintf(filename_dat, "../result/%s/dat/07-1_fft-drag/07-1.dat", date);

    /*****************************************************************************/

    // 変数の作成

    double value[range], value_i[range];

    // ファイルの読み込み (dat データ) ・格納

    int i;
    int buf;
    double ch0, ch1, ch2;

    for (i = 0; i < range; i++)
    {
        value[i] = 0;
        value_i[i] = 0;
    }

    i = 0;

    fp = fopen(filename_read, "r");

    if (filename_read == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    // printf("check\n");

    while ((fscanf(fp, "%d, %lf, %lf, %lf", &buf, &ch0, &ch1, &ch2)) != EOF)
    {
        // printf("[%d]\t%lf\t%lf\t%lf\n", buf, ch0, ch1, ch2);
        value[i] = ch0;
        i = i + 1;
    }

    fclose(fp);

    // FFTの適用

    double ps, as, dt;
    int fq;
    dt = 1;

    S_fft_1(value, value_i, range, 1);

    fp_csv = fopen(filename_csv, "w");
    fp_dat = fopen(filename_dat, "w");

    for (i = 0; i < range; i++)
    {
        ps = value[i] * value[i] + value_i[i] * value_i[i];       /* パワースペクトル  */
        as = sqrt(value[i] * value[i] + value_i[i] * value_i[i]); /* 振幅スペクトル  */
        // fq = (double)i / (dt * (double)range);
        fq = i;
        fprintf(fp_csv, "%d,%lf,%lf,%lf\n", fq, ps, value[i], value_i[i]);
        fprintf(fp_dat, "%d\t%lf\t%lf\t%lf\n", fq, ps, value[i], value_i[i]);
        printf("[%d]\tvalue: %lf \tvalue_: %lf\tpw: %lf\tfq :%d\n", i, value[i], value_i[i], ps, fq);
    }

    fclose(fp_csv);
    fclose(fp_dat);

    /*****************************************************************************/
    // Gnuplot //

    // ディレクトリの作成
    char directoryname_plot[100];

    sprintf(directoryname_plot, "../result/%s/plot/07", date);

    mkdir(directoryname_plot, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);

    char filename_plot[100];

    sprintf(filename_dat, "../result/%s/dat/07-1_fft-drag/07-1.dat", date);
    sprintf(filename_plot, "../result/%s/plot/07/07-1.png", date);

    /*****************************************************************************/

    // range x
    double x_min = 0;
    int x_max = range / 2;

    // range y
    double y_min = 0;
    double y_max = 100;

    // label
    char label[100] = "FFT";
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

    fprintf(gp, "set output '%s'\n", filename_plot);
    // fprintf(gp, "set multiplot\n");
    fprintf(gp, "set key left top\n");
    fprintf(gp, "set key font ',20'\n");
    fprintf(gp, "set term pngcairo size 1280, 960 font ',24'\n");
    // fprintf(gp, "set size ratio %lf\n", size);

    fprintf(gp, "set lmargin screen 0.10\n");
    fprintf(gp, "set rmargin screen 0.90\n");
    fprintf(gp, "set tmargin screen 0.90\n");
    fprintf(gp, "set bmargin screen 0.15\n");

    fprintf(gp, "set xrange [%lf:%d]\n", x_min, x_max);
    fprintf(gp, "set xlabel '%s'offset 0.0,0\n", xxlabel);
    fprintf(gp, "set yrange [%lf:%lf]\n", y_min, y_max);
    fprintf(gp, "set ylabel '%s'offset 0,0.0\n", yylabel);
    fprintf(gp, "set title '%s (drag)'\n", label);

    // fprintf(gp, "set samples 10000\n");
    fprintf(gp, "plot '%s' using 1:2 with lines lc 'black' notitle\n", filename_dat);
    fflush(gp); // Clean up Data

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);
}

// int main()
// {
//     calculate_drag("testdata", 32);

//     return (0);
// }