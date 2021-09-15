// 移動平均 範囲
int range_ma = 11;

// ファイル作成
char filename1[100];
char filename2[100];
char filename3[100];
char filename4[100];
char filename5[100];

// ファイルの指定 (plot)
sprintf(filename1, "..//33_result//%s//moving_average//%d//dat//%s_ma(%d).dat", date, range_ma, name, range_ma);
sprintf(filename2, "..//33_result//%s//moving_average//%d//drag//%s_ma(%d)_drag.png", date, range_ma, name, range_ma);    
sprintf(filename3, "..//33_result//%s//moving_average//%d//lift//%s_ma(%d)_lift.png", date, range_ma, name, range_ma);  

// 開始点特定 (1)
sprintf(filename4, "..//33_result//%s//moving_average//%d//dat//%s_ma(%d).dat", date, range_ma, name, range_ma);
sprintf(filename5, "..//33_result//%s//moving_average//%d//start_point//%s_ma(%d)_sp.dat", date, range_ma, name, range_ma);
// なんとなく良い感じかも