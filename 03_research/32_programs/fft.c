/******************************************************************************
PROGRAM NAME :fft.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ch 2
const char *read_file = "../31_data/210806/csv/Normal.CSV";
FILE *fp;
/*********************************   MAIN   *********************************/
int main(void)
{
    int i, j;

    // ファイルの読み込み

    fp = fopen(read_file, "r");
    if (read_file == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    // データの格納

    int N = 1000;
    double ch1, ch2;
    double value[N][ch];

    // ch1:drag, ch2:lift

    i = 0;

    while ((fscanf(fp, "%lf, %lf", &ch1, &ch2)) != EOF)
    {
        value[i][1] = ch1;
        value[i][2] = ch2;
        printf("[%d] %lf %lf\n", i, value[i][1], value[i][2]);
        i = i + 1;
    }

    // 計算

    int k, n;
    const double pi = acos(-1); //円周率の設定
    double re_d, re_l, im_d, im_l, dft_d, dft_l;

    i = 0;

    for(n=0; n<N; n++) {
        re_d=0;
        re_l=0;
        im_d=0;
        im_l=0;

        for(k=0; k<N; k++) {
            re_d += value[i][1]*cos(2*pi*k*n/N);
            im_d += -value[i][1]*sin(2*pi*k*n/N);
            re_l += value[i][2]*cos(2*pi*k*n/N);
            im_l += -value[i][2]*sin(2*pi*k*n/N);
        }

        dft_d = sqrt(re_d*re_d+im_d*im_d);
        dft_l = sqrt(re_l*re_l+im_l*im_l);

    printf("[%d] %f %lf\n", n, dft_d, dft_l);
        i = i + 1;
    }

    fclose(fp);

    return (0);
}
