#include <stdio.h>
#include <stdlib.h>

void Get_new_matrix(double** matrix, int size, int row, int col, double** newMatrix) {
	int offsetRow = 0;
	int offsetCol = 0;
	for (int i = 0; i < size - 1; i++) {
		if (i == row) {
			offsetRow = 1;
		}

		offsetCol = 0;
		for (int j = 0; j < size - 1; j++) {
			if (j == col) {
				offsetCol = 1;
			}
			newMatrix[i][j] = matrix[i + offsetRow][j + offsetCol];
		}
	}
}

double Get_det(double** matrix, int size) {
	double det = 0;
	int degree = 1;
	if (size == 1) return matrix[0][0];
	else if (size == 2) return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	else {
		double** newMatrix = (double**)malloc(sizeof(double*) * size - 1);
		for (size_t i = 0; i < size - 1; i++) newMatrix[i] = (double*)malloc(sizeof(double) * size - 1);

		for (size_t j = 0; j < size; j++) {
			Get_new_matrix(matrix, size, 0, j, newMatrix);
			det = det + (degree * matrix[0][j] * Get_det(newMatrix, size - 1));
			degree = -degree;
		}
		for (size_t i = 0; i < size - 1; i++) free(newMatrix[i]);
		free(newMatrix);
	}

	return det;
}

int main() {
	// console input
	int size;
	char flag = 1;
	double res = 0;
	scanf("%d", &size);
	if (size < 1) {
		puts("Error: matrix size < 1");
		return 2;
	}
	else if (size == 1) {
		scanf("%lg", &res);
		printf("det = %lg", res);
		return 0;
	}
	double** input = (double**)malloc(sizeof(double*) * size); // allocation and filling matrix
	for (size_t i = 0; i < size; i++) {
		input[i] = (double*)malloc(sizeof(double) * size);
		for (size_t j = 0; j < size; j++) {
			scanf("%lg", &(input[i][j]));
		}
	}
	if (size == 2) {
		res += input[0][0] * input[1][1];
		res -= input[1][0] * input[0][1];
		printf("det = %lg", res);
		flag = 0;
	}
	if (flag) printf("det = %lg", Get_det(input, size));
	for (size_t i = 0; i < size; i++) free(input[i]); // free memory
	free(input);
	return 0;
}
