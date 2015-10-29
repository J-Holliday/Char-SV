#define _CRT_SECURE_NO_WARNINGS
#include "csv.h"
#include <string.h>
#include <iostream>

#define TENTATIVE_LINE_BYTE 1024 // 1�s�ǂݍ��ލۂɊm�ۂ���o�C�g���Bcount_csv_line�ł̂ݎg�p

csv::csv(char* path, int byte, char delim){
	// �͂��߂�csv�̍s���A�񐔂��`����
	// path:CSV�t�@�C���̃p�X, byte:1���ڂ�����̊��蓖�ăo�C�g��

	csv_item = count_csv_item(path, delim);
	csv_line = count_csv_line(path, csv_item, byte);
}

char*** csv::read_csv(char* path, int row, int column, int byte, char delim){
	// CSV�t�@�C������񎟌��z����쐬���ĕԂ�
	// path:CSV�t�@�C���̃p�X, row:CSV�̍s��, column:CSV�̃t�B�[���h��, byte:1���ڂ�����̊��蓖�ăo�C�g��

	FILE *fp;
	char* s;
	s = (char*)calloc(column*byte + column, sizeof(char));

	fp = fopen(path, "r");
	if (fp == NULL){
		printf("%s���J���܂���\n", path);
		return NULL;
	}

	int line = 0;
	int itemnum = 0;
	char** splited;
	char*** matrix = define_matrix(row, column, byte);
	while (fgets(s, column*byte + column, fp) != NULL){ // 1�s������̍ő啶����:column*byte+column
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
	// �s��row * ��column , 1���ڂ�����̊��蓖�ăo�C�g��byte�̍s����쐬

	char*** matrix; // *matrix�͕�����, *�͗�, *�͍s 
	// �z��𓮓I�m��
	matrix = (char***)calloc(row, sizeof(char**));
	for (int i = 0; i < row; i++){
		matrix[i] = (char**)calloc(byte * column, sizeof(char*));
		for (int j = 0; j < column; j++)
			matrix[i][j] = (char*)calloc(byte, sizeof(char));
	}

	return matrix;
}

char** csv::split(char* str, char delim, int byte, int* itemnum){
	// ������str���Adelim��؂�̕�����z��ɂ��ĕԂ�
	// str:�����Ώۂ̕�����, delim:��������, byte:��v�f������̊��蓖�ăo�C�g��, *itemnum:������̗v�f��

	// �z��𓮓I�m��
	char** data;
	int row = count_string_item(str, delim); // �srow�͗v�f��
	*itemnum = row; // �v�f����Ԃ�
	data = (char**)calloc(row, sizeof(char*));
	for (int i = 0; i < row; i++)
		data[i] = (char*)calloc(byte, sizeof(char));

	// �z��ɕ��������
	int ii = 0;
	int row_current = 0;
	int column_byte = 0; // �s�̉������ڂ����o�C�g�Ŏw��
	char* item;
	item = (char*)malloc(sizeof(char)*byte);
	while (1){
		if (str[ii] == delim || str[ii] == '\n'){
			*(item + column_byte) = '\0';
			strcpy(data[row_current], item); // �z��v�f�ւ̕��������̊j
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
	// ������str��delim��؂�ɂ����Ƃ��̗v�f����Ԃ�

	int i = 0;
	int delimnum = 0;
	while (str[i] != '\n'){ // EOF �̔���͂ł��Ȃ��_�ɒ��ӁI �ǂݍ��݃t�@�C���͍ŏI�s��[EOF]�P�ƂŒu������
		if (str[i] == delim)
			delimnum++;
		i++;
	}
	return delimnum + 1;
}

int csv::count_csv_item(char* path, char delim){
	// CSV�̃t�B�[���h����Ԃ��B�K���N���X�̒��ň�ԍŏ��ɌĂԕK�v������
	// path:CSV�t�@�C���̃p�X

	FILE *fp;
	char s[TENTATIVE_LINE_BYTE];

	fp = fopen(path, "r");
	if (fp == NULL){
		printf("%s���J���܂���\n", path);
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
	// CSV�̍s����Ԃ��Bitemnum���K�v�Ȃ��߁Acount_csv_item����ɌĂ�ł͂Ȃ�Ȃ�

	FILE *fp;
	char* s;
	s = (char*)calloc(itemnum*byte + itemnum, sizeof(char));

	fp = fopen(path, "r");
	if (fp == NULL){
		printf("%s���J���܂���\n", path);
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