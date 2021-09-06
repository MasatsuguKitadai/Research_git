#include <stdio.h>

int main()
{
    //ファイル構造体へのポインタを宣言
    FILE *fp;
    char str[1024];

    //01.cppを読み込みモードで開く
    //ファイル名は自分でつけたファイル名を書いてください
    fp = fopen("data/210806/normal.csv", "r");

    //ファイルオープンに失敗したとき
    if (fp == NULL)
    {
        //失敗を表示し終了
        printf("ファイルオープン失敗\n");
        return -1;
    }

    //fgetsの戻り値がnullになるまで続ける
    //strにファイルからバイト取得し格納
    while ((fgets(str, 256, fp)) != NULL)
    {
        //格納された文字を出力
        printf("%s", str);
    }

    //ファイルを閉じる
    fclose(fp);
    return 0;
}