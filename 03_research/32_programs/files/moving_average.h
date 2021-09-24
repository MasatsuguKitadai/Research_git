// 移動平均 範囲
int range_ma = 5;

// range y (plot.c)

// 一括指定
const int max = 2;

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
sprintf(filename2, "..//33_result//%s//moving_average//%d//drag//01//%s_ma(%d)_drag_01.png", date, range_ma, name, range_ma);
sprintf(filename3, "..//33_result//%s//moving_average//%d//lift//01//%s_ma(%d)_lift_01.png", date, range_ma, name, range_ma);

// 開始点特定 (1)
sprintf(filename4, "..//33_result//%s//moving_average//%d//dat//%s_ma(%d).dat", date, range_ma, name, range_ma);
sprintf(filename5, "..//33_result//%s//moving_average//%d//start_point//%s_ma(%d)_sp.dat", date, range_ma, name, range_ma);

// 終了点特定 (1)
sprintf(filename6, "..//33_result//%s//moving_average//%d//finish_point//%s_ma(%d)_fp.dat", date, range_ma, name, range_ma);

// 線形補間
sprintf(filename7, "..//33_result//%s//moving_average//%d//linear_interpolation//%s_ma(%d)_lerp.dat", date, range_ma, name, range_ma);

// グラフ作成
char graphname1[100];
char graphname2[100];
char graphname3[100];
char graphname4[100];
char graphname5[100];
char graphname6[100];

// ファイル名作成
sprintf(graphname1, "..//33_result//%s//moving_average//%d//drag//02//%s_ma(%d)_drag_02.png", date, range_ma, name, range_ma);
sprintf(graphname2, "..//33_result//%s//moving_average//%d//lift//02//%s_ma(%d)_lift_02.png", date, range_ma, name, range_ma);

sprintf(graphname3, "..//33_result//%s//moving_average//%d//drag//03//%s_ma(%d)_drag_03.png", date, range_ma, name, range_ma);
sprintf(graphname4, "..//33_result//%s//moving_average//%d//lift//03//%s_ma(%d)_lift_03.png", date, range_ma, name, range_ma);

sprintf(graphname5, "..//33_result//%s//moving_average//%d//drag//04//%s_ma(%d)_drag_04.png", date, range_ma, name, range_ma);
sprintf(graphname6, "..//33_result//%s//moving_average//%d//lift//04//%s_ma(%d)_lift_04.png", date, range_ma, name, range_ma);