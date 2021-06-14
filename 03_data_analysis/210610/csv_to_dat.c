/******************************************************************************
PROGRAM NAME :2-2.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define CH 4
#define data_long 20000
double value[data_long][CH];
int number[data_long];
char date[20];
char time[20];
char text_1[20];
char text_2[20];
char file_name[100];
char file_name[100];
// char read_file_csv[100];
// char read_file_dat[100];
char buf[128];
int omit = 33; // Number of lines to skip
const char *file_csv = "after_1.CSV";
const char *file_dat = "after_1.dat";
FILE *input_file;
FILE *output_file;

/*********************************   MAIN   *********************************/
double main()
{
    int i, j, tim, num, ch1;
    double ch2, ch3, ch4, ch5;

    // 読み込むファイルを指定する

    /*
    printf("ファイル名：");
    scanf("%s", file_name);
    printf("1\n");

    // 入力・出力ファイル名の指定

    sprintf(read_file_csv, "%s.CSV", file_name);
    printf("2\n");
*/

    // Array initialization
    for (i = 0; i < data_long; i++)
    {
        number[i] = 0;

        for (j = 0; j < CH; j++)
        {
            value[i][j] = 0;
        }
    }

    input_file = fopen(file_csv, "r");

    if (file_csv == NULL)
    {
        printf("I can't open the file!\n");
        exit(0);
    }

    // Transrate the point of pointer
    for (i = 0; i < omit; i++)
    {
        fgets(buf, sizeof(buf), input_file);
    }

    for (i = 0; i < data_long; i++)
    {
        fscanf(input_file, "%d, %[^,], %[^,], %d, %lf, %lf, %lf, %lf, %[^,], %[^,]", &num, date, time, &ch1, &ch2, &ch3, &ch4, &ch5, text_1, text_2);

        number[i] = ch1;
        value[i][0] = ch2;
        value[i][1] = ch3;
        value[i][2] = ch4;
        value[i][3] = ch5;

        // check the programs
        printf("%d\t%d\t%lf\t%lf\t%lf\t%lf\n", i + 1, ch1, ch2, ch3, ch4, ch5);
        // printf("%d\t%d\t%lf\t%lf\t%lf\t%lf\n", i + 1, number[i], value[i][0], value[i][1], value[i][2], value[i][3]);
    }

    // sprintf(read_file_dat, "%s.dat", file_name);

    output_file = fopen(file_dat, "w");
    if (file_dat == NULL)
    {
        printf("I can't open the file!\n");
        exit(0);
    }

    for (i = 0; i < data_long; i++)
    {
        fprintf(output_file, "%d\t%d\t%lf\t%lf\t%lf\t%lf\n", i + 1, number[i], value[i][0], value[i][1], value[i][2], value[i][3]);
    }

    fclose(input_file);
    fclose(output_file);

    return (0);
}
