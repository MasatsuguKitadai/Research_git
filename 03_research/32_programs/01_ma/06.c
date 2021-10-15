/******************************************************************************
PROGRAM NAME : calibration.c
AUTHER  : Masatsugu Kitadai
DATE    :
******************************************************************************/
// 移動平均 範囲
int range_ma = 11;

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "files/fp.h"

#define rho 998.233 // kg/m3 (20c)
#define u 0.025     // m/s
/*********************************   MAIN   *********************************/
int convert_1(char name[], char date[])
{
#include "files/moving_average.h"

    int i, num;
    double ch1, ch2, ch3, ch4;
    double value[4];

    // ファイルの読み込み
    fp8 = fopen(filename8, "r");
    if (filename8 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    fscanf(fp8, "%d\t%lf\t%lf\t%lf\t%lf", &num, &ch1, &ch2, &ch3, &ch4);

    value[0] = ch1;
    value[1] = ch2;
    value[2] = ch3;
    value[3] = ch4;

    // printf("%lf\t%lf\t%lf\t%lf\t[%s]\n", value[0], value[1], value[2], value[3], name);

    fclose(fp8);

    // 近似式の係数の読み込み
    char filename[100] = "..//..//33_result//convert//dat//formula.dat";
    double a[3], b[3];

    fp = fopen(filename, "r");
    if (filename == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    i = 0;

    while ((fscanf(fp, "%lf\t%lf", &ch1, &ch2)) != EOF)
    {
        a[i] = ch1;
        b[i] = ch2;
        // printf("%lf\t%lf\n", a[i], b[i]);
        i = i + 1;
    }

    fclose(fp);

    // 荷重の計算

    double convert[2];

    convert[0] = a[1] * value[1];
    convert[1] = a[2] * value[3];

    printf("%lf\t%lf\t[%s]\n", convert[0], convert[1], name);

    // Cd・Cl値の計算

    double cd, cl;
    double s1;

    s1 = 0.025 * 0.0186; // m2

    cd = 2 * convert[0] / (rho * u * u * s1); 
    cl = 2 * convert[1] / (rho * u * u * s1); 

    // printf("%lf\t%lf\t[%s]\n", cd, cl, name);

    return (0);
}

// トレッド 17.9 mm
int convert_2(char name[], char date[])
{
#include "files/moving_average.h"

    int i, num;
    double ch1, ch2, ch3, ch4;
    double value[4];

    // ファイルの読み込み
    fp8 = fopen(filename8, "r");
    if (filename8 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    fscanf(fp8, "%d\t%lf\t%lf\t%lf\t%lf", &num, &ch1, &ch2, &ch3, &ch4);

    value[0] = ch1;
    value[1] = ch2;
    value[2] = ch3;
    value[3] = ch4;

    // printf("%lf\t%lf\t%lf\t%lf\t[%s]\n", value[0], value[1], value[2], value[3], name);

    fclose(fp8);

    // 近似式の係数の読み込み
    char filename[100] = "..//..//33_result//convert//dat//formula.dat";
    double a[3], b[3];

    fp = fopen(filename, "r");
    if (filename == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    i = 0;

    while ((fscanf(fp, "%lf\t%lf", &ch1, &ch2)) != EOF)
    {
        a[i] = ch1;
        b[i] = ch2;
        // printf("%lf\t%lf\n", a[i], b[i]);
        i = i + 1;
    }

    fclose(fp);

    // 荷重の計算

    double convert[2];

    convert[0] = a[1] * value[1];
    convert[1] = a[2] * value[3];

    printf("%lf\t%lf\t[%s]\n", convert[0], convert[1], name);

    // Cd・Cl値の計算

    double cd, cl;
    double s2;

    s2 = 0.025 * 0.0179; // m2

    cd = 2 * convert[0] / (rho * u * u * s2); 
    cl = 2 * convert[1] / (rho * u * u * s2); 

    // printf("%lf\t%lf\t[%s]\n", cd, cl, name);

    return (0);
}

// トレッド 19.3 mm
int convert_3(char name[], char date[])
{
#include "files/moving_average.h"

    int i, num;
    double ch1, ch2, ch3, ch4;
    double value[4];

    // ファイルの読み込み
    fp8 = fopen(filename8, "r");
    if (filename8 == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    fscanf(fp8, "%d\t%lf\t%lf\t%lf\t%lf", &num, &ch1, &ch2, &ch3, &ch4);

    value[0] = ch1;
    value[1] = ch2;
    value[2] = ch3;
    value[3] = ch4;

    // printf("%lf\t%lf\t%lf\t%lf\t[%s]\n", value[0], value[1], value[2], value[3], name);

    fclose(fp8);

    // 近似式の係数の読み込み
    char filename[100] = "..//..//33_result//convert//dat//formula.dat";
    double a[3], b[3];

    fp = fopen(filename, "r");
    if (filename == NULL)
    {
        printf("Error! I can't open the file.\n");
        exit(0);
    }

    i = 0;

    while ((fscanf(fp, "%lf\t%lf", &ch1, &ch2)) != EOF)
    {
        a[i] = ch1;
        b[i] = ch2;
        // printf("%lf\t%lf\n", a[i], b[i]);
        i = i + 1;
    }

    fclose(fp);

    // 荷重の計算

    double convert[2];

    convert[0] = a[1] * value[1];
    convert[1] = a[2] * value[3];

    printf("%lf\t%lf\t[%s]\n", convert[0], convert[1], name);

    // Cd・Cl値の計算

    double cd, cl;
    double s3;

    s3 = 0.025 * 0.0193; // m2

    cd = 2 * convert[0] / (rho * u * u * s3); 
    cl = 2 * convert[1] / (rho * u * u * s3); 

    // printf("%lf\t%lf\t[%s]\n", cd, cl, name);

    return (0);
}

int main()
{
    convert_1("Normal", "210806");
    convert_1("Groove_A", "210806");
    convert_1("Groove_B", "210806");
    convert_1("Groove_C", "210806");
    convert_1("Groove_D", "210806");
    convert_1("C1", "210806");
    convert_2("R1_17.9", "210806");
    convert_1("R1_18.6", "210806");
    convert_3("R1_19.3", "210806");

    printf("\n");
    
    convert_1("Normal", "210731");
    convert_1("Groove_A", "210731");
    convert_1("Groove_B", "210731");
    convert_1("Groove_C", "210731");
    convert_1("Groove_D", "210731");
    convert_1("C1", "210731");
    convert_2("R1_17.9", "210731");
    convert_1("R1_18.6", "210731");
    convert_3("R1_19.3", "210731");
}