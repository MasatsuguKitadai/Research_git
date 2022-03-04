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
char filename9[100];
char filename10[100];
char filename11[100];
char filename12[100];
char filename13[100];

// ファイルの指定 (plot)
sprintf(filename1, "..//..//33_result//%s//moving_average//%d//dat//%s_ma(%d).dat", date, range_ma, name, range_ma);
sprintf(filename2, "..//..//33_result//%s//moving_average//%d//graph//drag//01//%s_ma(%d)_drag_01.png", date, range_ma, name, range_ma);
sprintf(filename3, "..//..//33_result//%s//moving_average//%d//graph//lift//01//%s_ma(%d)_lift_01.png", date, range_ma, name, range_ma);

// 開始点特定 (1)
sprintf(filename4, "..//..//33_result//%s//moving_average//%d//dat//%s_ma(%d).dat", date, range_ma, name, range_ma);
sprintf(filename5, "..//..//33_result//%s//moving_average//%d//start//%s_ma(%d)_s.dat", date, range_ma, name, range_ma);

// 終了点特定 (1)
sprintf(filename6, "..//..//33_result//%s//moving_average//%d//finish//%s_ma(%d)_f.dat", date, range_ma, name, range_ma);

// 線形補間
sprintf(filename7, "..//..//33_result//%s//moving_average//%d//lerp//%s_ma(%d)_lerp.dat", date, range_ma, name, range_ma);

// 平均値の計算
sprintf(filename8, "..//..//33_result//%s//moving_average//%d//average//%s_ma(%d)_average.dat", date, range_ma, name, range_ma);

// FFT 結果
sprintf(filename9, "..//..//33_result//%s//moving_average//%d//fft//drag_1//%s_ma(%d)_fft_drag_1.dat", date, range_ma, name, range_ma);
sprintf(filename10, "..//..//33_result//%s//moving_average//%d//fft//drag_2//%s_ma(%d)_fft_drag_2.dat", date, range_ma, name, range_ma);
sprintf(filename11, "..//..//33_result//%s//moving_average//%d//fft//lift_1//%s_ma(%d)_fft_lift_1.dat", date, range_ma, name, range_ma);
sprintf(filename12, "..//..//33_result//%s//moving_average//%d//fft//lift_2//%s_ma(%d)_fft_lift_2.dat", date, range_ma, name, range_ma);

// raw_data 用
sprintf(filename13, "..//..//33_result//%s//raw_data//start_ma(%d)//%s_ma(%d)_s_rawdata_ver.dat", date, range_ma, name, range_ma);

// グラフ作成
char graphname1[100];
char graphname2[100];
char graphname3[100];
char graphname4[100];
char graphname5[100];
char graphname6[100];
char graphname7[100];
char graphname8[100];

char graphname9[100];
char graphname10[100];
char graphname11[100];
char graphname12[100];

// ファイル名作成
sprintf(graphname1, "..//..//33_result//%s//moving_average//%d//graph//drag//02//%s_ma(%d)_drag_02.png", date, range_ma, name, range_ma);
sprintf(graphname2, "..//..//33_result//%s//moving_average//%d//graph//lift//02//%s_ma(%d)_lift_02.png", date, range_ma, name, range_ma);
sprintf(graphname3, "..//..//33_result//%s//moving_average//%d//graph//drag//03//%s_ma(%d)_drag_03.png", date, range_ma, name, range_ma);
sprintf(graphname4, "..//..//33_result//%s//moving_average//%d//graph//lift//03//%s_ma(%d)_lift_03.png", date, range_ma, name, range_ma);
sprintf(graphname5, "..//..//33_result//%s//moving_average//%d//graph//drag//04//%s_ma(%d)_drag_04.png", date, range_ma, name, range_ma);
sprintf(graphname6, "..//..//33_result//%s//moving_average//%d//graph//lift//04//%s_ma(%d)_lift_04.png", date, range_ma, name, range_ma);
sprintf(graphname7, "..//..//33_result//%s//moving_average//%d//graph//drag//05//%s_ma(%d)_drag_05.png", date, range_ma, name, range_ma);
sprintf(graphname8, "..//..//33_result//%s//moving_average//%d//graph//lift//05//%s_ma(%d)_lift_05.png", date, range_ma, name, range_ma);
sprintf(graphname9, "..//..//33_result//%s//moving_average//%d//graph//drag//06//%s_ma(%d)_drag_06.png", date, range_ma, name, range_ma);
sprintf(graphname10, "..//..//33_result//%s//moving_average//%d//graph//lift//06//%s_ma(%d)_lift_06.png", date, range_ma, name, range_ma);
sprintf(graphname11, "..//..//33_result//%s//moving_average//%d//graph//drag//07//%s_ma(%d)_drag_07.png", date, range_ma, name, range_ma);
sprintf(graphname12, "..//..//33_result//%s//moving_average//%d//graph//lift//07//%s_ma(%d)_lift_07.png", date, range_ma, name, range_ma);
