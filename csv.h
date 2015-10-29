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
	csv::csv(char* path, int byte, char delim);										// �͂��߂�csv�̍s���A�񐔂��`����
	char*** csv::read_csv(char* path, int row, int column, int byte, char delim);	// csv�t�@�C����ǂݍ��݁A�񎟌��z��ɂ��ĕԂ�
	char*** csv::define_matrix(int row, int column, int byte);						// �񎟌��̔z����m�ۂ���B�e���ڂɂ͕����񂪊i�[�����
	char** csv::split(char* str, char delim, int byte, int* itemnum);				// ������str��delim��؂�ŕ������āA�z��ɂ��ĕԂ�
	int csv::count_string_item(char* str, char delim);								// ������ɑ΂��āAdelim��؂�ŗv�f���𐔂���
	int csv::count_csv_item(char* path, char delim);								// csv�f�[�^�̍ŏ��̍s�ɑ΂��āAdelim��؂�ŗv�f���𐔂���
	int csv::count_csv_line(char* path, int itemnum, int byte);						// csv�f�[�^�̍s���𐔂���
	int* csv::count_csv();															// csv�f�[�^�̍s���ƈ�s������̗v�f����Ԃ�
};
#endif    //INC_CSV