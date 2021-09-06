/******************************************************************************
PROGRAM NAME :frequency_analysis.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define ch 2
const char *read_file = "../../data/210806/Normal.CSV";
FILE *fp;
/*****************************************************************************/
int omit = 31;
char buf[128];
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

    printf("omit success!\n");

    // データの格納

    double ch1, ch2;
    double value[1000][ch];

    i = 0;

    while ((fscanf(fp, "%lf, %lf", &ch1, &ch2)) != EOF)
    {
        value[i][1] = ch1;
        value[i][2] = ch2;
        printf("[%d] %lf %lf\n", i, value[i][1], value[i][2]);
        i = i + 1;
    }

    // 計算

    fclose(fp);

    return (0);
}
