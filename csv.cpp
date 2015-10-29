#define _CRT_SECURE_NO_WARNINGS
#include "csv.h"
#include <string.h>
#include <iostream>

#define TENTATIVE_LINE_BYTE 1024 // 1行読み込む際に確保するバイト数。count_csv_lineでのみ使用

csv::csv(char* path, int byte, char delim){
	// はじめにcsvの行数、列数を定義する
	// path:CSVファイルのパス, byte:1項目あたりの割り当てバイト数

	csv_item = count_csv_item(path, delim);
	csv_line = count_csv_line(path, csv_item, byte);
}

char*** csv::read_csv(char* path, int row, int column, int byte, char delim){
	// CSVファイルから二次元配列を作成して返す
	// path:CSVファイルのパス, row:CSVの行数, column:CSVのフィールド数, byte:1項目あたりの割り当てバイト数

	FILE *fp;
	char* s;
	s = (char*)calloc(column*byte + column, sizeof(char));

	fp = fopen(path, "r");
	if (fp == NULL){
		printf("%sが開けません\n", path);
		return NULL;
	}

	int line = 0;
	int itemnum = 0;
	char** splited;
	char*** matrix = define_matrix(row, column, byte);
	while (fgets(s, column*byte + column, fp) != NULL){ // 1行あたりの最大文字数:column*byte+column
		splited = split(s, delim, byte, &itemnum);
		for (int i = 0; i < itemnum; i++){
			char* buf = splited[i];
			sprintf(matrix[line][i], "%s", splited[i]);
		}
		line++;
	}

	fclose(fp);

	return matrix;
}

char*** csv::define_matrix(int row, int column, int byte){
	// 行数row * 列数column , 1項目あたりの割り当てバイト数byteの行列を作成

	char*** matrix; // *matrixは文字列, *は列, *は行 
	// 配列を動的確保
	matrix = (char***)calloc(row, sizeof(char**));
	for (int i = 0; i < row; i++){
		matrix[i] = (char**)calloc(byte * column, sizeof(char*));
		for (int j = 0; j < column; j++)
			matrix[i][j] = (char*)calloc(byte, sizeof(char));
	}

	return matrix;
}

char** csv::split(char* str, char delim, int byte, int* itemnum){
	// 文字列strを、delim区切りの文字列配列にして返す
	// str:分割対象の文字列, delim:分割文字, byte:一要素あたりの割り当てバイト数, *itemnum:分割後の要素数

	// 配列を動的確保
	char** data;
	int row = count_string_item(str, delim); // 行rowは要素数
	*itemnum = row; // 要素数を返す
	data = (char**)calloc(row, sizeof(char*));
	for (int i = 0; i < row; i++)
		data[i] = (char*)calloc(byte, sizeof(char));

	// 配列に文字列を代入
	int ii = 0;
	int row_current = 0;
	int column_byte = 0; // 行の何文字目かをバイトで指す
	char* item;
	item = (char*)malloc(sizeof(char)*byte);
	while (1){
		if (str[ii] == delim || str[ii] == '\n'){
			*(item + column_byte) = '\0';
			strcpy(data[row_current], item); // 配列要素への文字列代入の核
			row_current++;
			column_byte = 0;
			if (str[ii] == '\n') break;
		}
		else{
			*(item + column_byte) = str[ii];
			column_byte++;
		}
		ii++;
	}

	return data;
}

int csv::count_string_item(char* str, char delim){
	// 文字列strをdelim区切りにしたときの要素数を返す

	int i = 0;
	int delimnum = 0;
	while (str[i] != '\n'){ // EOF の判定はできない点に注意！ 読み込みファイルは最終行に[EOF]単独で置くこと
		if (str[i] == delim)
			delimnum++;
		i++;
	}
	return delimnum + 1;
}

int csv::count_csv_item(char* path, char delim){
	// CSVのフィールド数を返す。必ずクラスの中で一番最初に呼ぶ必要がある
	// path:CSVファイルのパス

	FILE *fp;
	char s[TENTATIVE_LINE_BYTE];

	fp = fopen(path, "r");
	if (fp == NULL){
		printf("%sが開けません\n", path);
		return NULL;
	}

	int item = 0;
	while (fgets(s, TENTATIVE_LINE_BYTE, fp) != NULL){
		item = count_string_item(s, delim);
		break;
	}

	fclose(fp);

	return item;
}

int csv::count_csv_line(char* path, int itemnum, int byte){
	// CSVの行数を返す。itemnumが必要なため、count_csv_itemより先に呼んではならない

	FILE *fp;
	char* s;
	s = (char*)calloc(itemnum*byte + itemnum, sizeof(char));

	fp = fopen(path, "r");
	if (fp == NULL){
		printf("%sが開けません\n", path);
		return NULL;
	}

	int line = 0;
	while (fgets(s, itemnum*byte + itemnum, fp) != NULL){
		line++;
	}

	fclose(fp);

	return line;
}

int* csv::count_csv(){
	int res[2] = { csv_line, csv_item };
	return res;
}