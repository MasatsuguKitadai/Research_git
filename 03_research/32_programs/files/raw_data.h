// range y (plot.c)

// 一括指定
const int max = 3;

// drag
int y_min1 = -max;
int y_max1 = max;

// lift
int y_min2 = -max;
int y_max2 = max;

// ファイル作成
char filename1[100];
char filename2[100];
char filename3[100];
char filename4[100];
char filename5[100];
char filename6[100];
char filename7[100];
char filename8[100];

// ファイルの指定 (plot)
sprintf(filename1, "..//33_result//%s//raw_data//dat//%s.dat", date, name);
sprintf(filename2, "..//33_result//%s//raw_data//drag//%s_drag.png", date, name);
sprintf(filename3, "..//33_result//%s//raw_data//lift//%s_lift.png", date, name);

// 開始点特定 (1)
sprintf(filename4, "..//33_result//%s//raw_data//dat//%s.dat", date, name);
sprintf(filename5, "..//33_result//%s//raw_data//start_point//%s_sp.dat", date, name);

// 終了点特定 (1)
sprintf(filename6, "..//33_result//%s//raw_data//finish_point//%s_fp.dat", date, name);

// 開始点を含む点までの平均値
sprintf(filename7, "..//33_result//%s//raw_data//start_average//%s_sa.dat", date, name);

// 終了点後部の平均値
sprintf(filename8, "..//33_result//%s//raw_data//finish_average//%s_fa.dat", date, name);
