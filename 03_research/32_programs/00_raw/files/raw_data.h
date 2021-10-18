// 移動平均 範囲
int range_ma = 11;

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
char filename9[100];
char filename10[100];
char filename11[100];
char filename12[100];

// ファイルの指定 (plot)
sprintf(filename1, "..//33_result//%s//raw_data//dat//%s.dat", date, name);
sprintf(filename2, "..//33_result//%s//raw_data//drag//01//%s_drag.png", date, name);
sprintf(filename3, "..//33_result//%s//raw_data//lift//01//%s_lift.png", date, name);

// 開始点特定 (1)
sprintf(filename4, "..//..//33_result//%s//moving_average//%d//dat//%s_ma(%d).dat", date, range_ma, name, range_ma);
sprintf(filename5, "..//..//33_result//%s//moving_average//%d//start//%s_ma(%d)_s.dat", date, range_ma, name, range_ma);

// 終了点特定 (1)
sprintf(filename6, "..//33_result//%s//raw_data//finish//%s_f.dat", date, name);

// 線形補間
sprintf(filename7, "..//33_result//%s//raw_data//lerp//%s_lerp.dat", date, name);

// グラフ作成
char graphname1[100];
char graphname2[100];
char graphname3[100];
char graphname4[100];
char graphname5[100];
char graphname6[100];

// FFT 結果 (moving average n=11 から)
sprintf(filename9,  "..//..//33_result//%s//moving_average//%d//fft//drag_1//%s_ma(%d)_fft_drag_1.dat", date, range_ma, name, range_ma);
sprintf(filename10, "..//..//33_result//%s//moving_average//%d//fft//drag_2//%s_ma(%d)_fft_drag_2.dat", date, range_ma, name, range_ma);
sprintf(filename11, "..//..//33_result//%s//moving_average//%d//fft//lift_1//%s_ma(%d)_fft_lift_1.dat", date, range_ma, name, range_ma);
sprintf(filename12, "..//..//33_result//%s//moving_average//%d//fft//lift_2//%s_ma(%d)_fft_lift_2.dat", date, range_ma, name, range_ma);

// ファイル名作成
sprintf(graphname1, "..//33_result//%s//raw_data//drag//02//%s_drag_02.png", date, name);
sprintf(graphname2, "..//33_result//%s//raw_data//lift//02//%s_lift_02.png", date, name);

sprintf(graphname3, "..//33_result//%s//raw_data//drag//03//%s_drag_03.png", date, name);
sprintf(graphname4, "..//33_result//%s//raw_data//lift//03//%s_lift_03.png", date, name);

sprintf(graphname5, "..//33_result//%s//raw_data//drag//04//%s_drag_04.png", date, name);
sprintf(graphname6, "..//33_result//%s//raw_data//lift//04//%s_lift_04.png", date, name);

sprintf(graphname10, "..//..//33_result//%s//raw_data//graph//lift//06//%s_lift_06.png", date, range_ma, name, range_ma);
sprintf(graphname11, "..//..//33_result//%s//raw_data//graph//drag//07//%s_drag_07.png", date, range_ma, name, range_ma);
sprintf(graphname12, "..//..//33_result//%s//raw_data//graph//lift//07//%s_lift_07.png", date, range_ma, name, range_ma);
sprintf(graphname13, "..//..//33_result//%s//raw_data//graph//lift//07//%s_lift_07.png", date, range_ma, name, range_ma);
