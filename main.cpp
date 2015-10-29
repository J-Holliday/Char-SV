#include "csv.h"
#include <stdio.h>

int main(){
	char* path = "C:\\Users\\Tamon\\Desktop\\src_local.txt";
	int byte = 128;

	csv c(path, byte, '\t');
	int* grid = c.count_csv(); // grid[0]:�s��, grid[1]:��
	int row = grid[0];
	int column = grid[1];

	char*** matrix = c.read_csv(path, row, column, byte, '\t');
	printf("���̓f�[�^:\n");
	for (int i = 0; i < row; i++){
		for (int j = 0; j < column; j++){
			printf("%s\t", matrix[i][j]);
		}
		printf("\n");
	}

	return 0;
}