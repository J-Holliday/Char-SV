#ifndef _INC_CSV
#define _INC_CSV

#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
using namespace std;

class csv
{
private:
	int csv_line, csv_item;
public:
	csv::csv(char* path, int byte, char delim);										// はじめにcsvの行数、列数を定義する
	char*** csv::read_csv(char* path, int row, int column, int byte, char delim);	// csvファイルを読み込み、二次元配列にして返す
	char*** csv::define_matrix(int row, int column, int byte);						// 二次元の配列を確保する。各項目には文字列が格納される
	char** csv::split(char* str, char delim, int byte, int* itemnum);				// 文字列strをdelim区切りで分割して、配列にして返す
	int csv::count_string_item(char* str, char delim);								// 文字列に対して、delim区切りで要素数を数える
	int csv::count_csv_item(char* path, char delim);								// csvデータの最初の行に対して、delim区切りで要素数を数える
	int csv::count_csv_line(char* path, int itemnum, int byte);						// csvデータの行数を数える
	int* csv::count_csv();															// csvデータの行数と一行あたりの要素数を返す
};
#endif    //INC_CSV