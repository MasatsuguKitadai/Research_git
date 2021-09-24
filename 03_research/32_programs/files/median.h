// 中央値 範囲
int range_me = 5;

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
sprintf(filename1, "..//33_result//%s//median//%d//dat//%s_me(%d).dat", date, range_me, name, range_me);
sprintf(filename2, "..//33_result//%s//median//%d//drag//01//%s_me(%d)_drag.png", date, range_me, name, range_me);
sprintf(filename3, "..//33_result//%s//median//%d//lift//01//%s_me(%d)_lift.png", date, range_me, name, range_me);

// 開始点特定 (1)
sprintf(filename4, "..//33_result//%s//median//%d//dat//%s_me(%d).dat", date, range_me, name, range_me);
sprintf(filename5, "..//33_result//%s//median//%d//start_point//%s_me(%d)_sp.dat", date, range_me, name, range_me);

// 終了点特定 (1)
sprintf(filename6, "..//33_result//%s//median//%d//finish_point//%s_me(%d)_fp.dat", date, range_me, name, range_me);

// 線形補間
sprintf(filename7, "..//33_result//%s//median//%d//linear_interpolation//%s_me(%d)_lerp.dat", date, range_me, name, range_me);

// グラフ作成
char graphname1[100];
char graphname2[100];
char graphname3[100];
char graphname4[100];
char graphname5[100];
char graphname6[100];

// ファイル名作成
sprintf(graphname1, "..//33_result//%s//median//%d//drag//02//%s_me(%d)_drag_02.png", date, range_me, name, range_me);
sprintf(graphname2, "..//33_result//%s//median//%d//lift//02//%s_me(%d)_lift_02.png", date, range_me, name, range_me);

sprintf(graphname3, "..//33_result//%s//median//%d//drag//03//%s_me(%d)_drag_03.png", date, range_me, name, range_me);
sprintf(graphname4, "..//33_result//%s//median//%d//lift//03//%s_me(%d)_lift_03.png", date, range_me, name, range_me);

sprintf(graphname5, "..//33_result//%s//median//%d//drag//04//%s_me(%d)_drag_04.png", date, range_me, name, range_me);
sprintf(graphname6, "..//33_result//%s//median//%d//lift//04//%s_me(%d)_lift_04.png", date, range_me, name, range_me);