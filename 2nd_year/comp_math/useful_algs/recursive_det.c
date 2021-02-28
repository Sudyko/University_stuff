#include <stdio.h>
#include <stdlib.h>

double Get_det(double** matrix, int size) {
	if (size == 1) return matrix[0][0];
	else if (size == 2) return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	else {
		int sub_j;
		int minor_sign = 1;
		int res = 0;
		double** sub_matrix = (double**)malloc(sizeof(double*) * size - 1);
		for (size_t i = 0; i < size; i++) sub_matrix[i] = (double*)malloc(sizeof(double) * size - 1);
		for (int i = 0; i < size; i++) {
			sub_j = 0;
			for (int j = 0; j < size; j++)
				if (i != j)
					sub_matrix[sub_j++] = matrix[j] + 1;

			res = res + minor_sign * matrix[i][0] * Get_det(sub_matrix, size - 1);
			minor_sign = -minor_sign;
		};
		for (size_t i = 0; i < size - 1; i++) free(sub_matrix[i]);
		free(sub_matrix);
		return res;
	}
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
