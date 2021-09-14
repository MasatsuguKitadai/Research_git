// グラフの範囲 (y軸) (plot.c)

// おまけ
const int max = 3;

// drag
int y_min1 = -max;
int y_max1 = max;

// lift
int y_min2 = -max;
int y_max2 = max;

// 移動平均 範囲 (moving_aveage.c)
int range_ma = 11;

// 中央値 範囲 (median.c)
int range_me = 21;

// 開始点特定 範囲 (identify.c)
int range_1 = 100; // 前部の範囲
int range_2 = 10;  // 後部の範囲