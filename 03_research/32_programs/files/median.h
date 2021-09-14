// ファイル作成
char filename1[100];
char filename2[100];
char filename3[100];
char filename4[100];
char filename5[100];

// ファイルの指定 (plot)
sprintf(filename1, "..//33_result//%s//median//%d//dat//%s_me(%d).dat", date, range_me, name, range_me);
sprintf(filename2, "..//33_result//%s//median//%d//drag//%s_me(%d)_drag.png", date, range_me, name, range_me);    
sprintf(filename3, "..//33_result//%s//median//%d//lift//%s_me(%d)_lift.png", date, range_me, name, range_me);  

// 開始点特定 (1)
sprintf(filename4, "..//33_result//%s//median//%d//dat//%s_me(%d).dat", date, range_me, name, range_me);
sprintf(filename5, "..//33_result//%s//median//%d//start_point//%s_me(%d)_sp.dat", date, range_me, name, range_me);
// 微妙だった