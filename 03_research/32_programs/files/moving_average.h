// 移動平均 範囲
int range_ma = 21;

// range y (plot.c)

// 一括指定
const int max = 1;

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
sprintf(filename1, "..//33_result//%s//moving_average//%d//dat//%s_ma(%d).dat", date, range_ma, name, range_ma);
sprintf(filename2, "..//33_result//%s//moving_average//%d//drag//%s_ma(%d)_drag.png", date, range_ma, name, range_ma);
sprintf(filename3, "..//33_result//%s//moving_average//%d//lift//%s_ma(%d)_lift.png", date, range_ma, name, range_ma);

// 開始点特定 (1)
sprintf(filename4, "..//33_result//%s//moving_average//%d//dat//%s_ma(%d).dat", date, range_ma, name, range_ma);
sprintf(filename5, "..//33_result//%s//moving_average//%d//start_point//%s_ma(%d)_sp.dat", date, range_ma, name, range_ma);

// 終了点特定 (1)
sprintf(filename6, "..//33_result//%s//moving_average//%d//finish_point//%s_ma(%d)_fp.dat", date, range_ma, name, range_ma);

// 線形補間
sprintf(filename7, "..//33_result//%s//moving_average//%d//linear_interpolation//%s_ma(%d)_lerp.dat", date, range_ma, name, range_ma);
