#include <stdio.h>
#include <stdlib.h>

typedef struct { double** val; int size; } matrix;

matrix init_matrix(matrix to_init, int size) {
	to_init.size = size;
	to_init.val = (double**)malloc(sizeof(double*) * size);
	for (int i = 0; i < size; i++) to_init.val[i] = (double*)malloc(sizeof(double) * size);
	return to_init;
}

int main() {
	// console input
	int size;
	matrix input;
	scanf("%d", size);
	if (size < 1) {
		puts("Error: matrix size < 1");
		return 2;
	}
	input = init_matrix(input, size);
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) {
			scanf("%lf", &(input.val[i][j]));
		}
	}
	return 0;
}