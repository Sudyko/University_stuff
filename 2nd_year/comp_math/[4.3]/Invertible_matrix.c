#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { double** val; int size; } matrix;

char isWeakZero(double num) {
	if (num == 0) return 1;//if (num > -1e-10 && num < 1e-10) return 1;
	else return 0;
}

void err(int code, const char* msg) { puts(msg); exit(code); }

char init_matrix(matrix& to_init, int size) {
	to_init.size = size;
	double** alloc = (double**)malloc(sizeof(double*) * size);
	if (alloc) to_init.val = alloc;
	else return 1;
	for (int i = 0; i < size; i++) {
		double* nalloc = (double*)malloc(sizeof(double) * size);
		if (nalloc) to_init.val[i] = nalloc;
		else return 1;
	}
	return 0;
}

void free_matrix(matrix item) {
	while (item.size--) if (item.val[item.size]) free(item.val[item.size]);
	if (item.val) free(item.val);
}

void add_lines(matrix& item, int from, int to, double coef) {
	for (int i = 0; i < item.size; i++) item.val[to][i] += item.val[from][i] * coef;
}

void mul_line(matrix& item, int line, double coef) {
	for (int i = 0; i < item.size; i++) item.val[line][i] = item.val[line][i] * coef;
}

void swap_lines(matrix& item, int line1, int line2) {
	for (int i = 0; i < item.size; i++) {
		double tmp = item.val[line1][i];
		item.val[line1][i] = item.val[line2][i];
		item.val[line2][i] = tmp;
	}
}

char check_matrix(matrix init, matrix inv) {
	for (size_t i = 0; i < init.size; i++)
		for (size_t j = 0; j < init.size; j++) {
			double check = 0;
			for (size_t k = 0; k < init.size; k++) check += init.val[i][k] * inv.val[k][j];
			if (check != 1 && i == j) return 0; // ������� ���������
			else if (check != 0 && i != j) return 0; // �������� ���������
		};
	return 1;
}

int main(int argc, char** argv) {
	matrix input, ext, init;
	FILE* f_in = stdin, * fout = stdout; // console i/o by default
	input.size = (int)(input.val = 0);
	init = ext = input;
	int size;
	if ((argc == 4) && (strcmp(argv[1], "-f") == 0)) { //file input
		if ((f_in = fopen(argv[2], "r")) == NULL) err(3, "Error while opening input file");
	}
	else if (argc != 1) err(0, "Usage:\nConsole I/O - no params\nFile I/O - '-f _input _output'");
	//read matrix
	fscanf(f_in, "%d", &size);
	if (size < 1) err(2, "Error: matrix size < 1");
	char bad_alloc = init_matrix(input, size) + init_matrix(ext, size) + init_matrix(init, size);
	if (bad_alloc) {
		free_matrix(input);
		free_matrix(init);
		free_matrix(ext);
		err(16, "Memory allocation error");
	}
	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size; j++) {
			fscanf(f_in, "%lf", &(input.val[i][j]));
			init.val[i][j] = input.val[i][j]; // fill backup matrix
			//fill extended matrix
			if (i == j) ext.val[i][j] = 1;
			else ext.val[i][j] = 0;
		};
	if (argc > 1) fclose(f_in);
	//process data
	//inverse matrix algorithm itself
	for (size_t i = 0; i < size; i++) {
		if (isWeakZero(input.val[i][i])) { //zero handle
			input.val[i][i] = 0;
			char bad = 1;
			size_t j = i;
			while (bad && ++j < size)
				if ((isWeakZero(input.val[i][j]) == 0) && (isWeakZero(input.val[j][i]) == 0)) {
					bad = 0;
					swap_lines(input, i, j);
					swap_lines(ext, i, j);
				};
			if (bad) {
				free_matrix(input);
				free_matrix(ext);
				free_matrix(init);
				err(5, "I guess we cannot find inverse matrix for this one");
			}
		}
		for (int j = i + 1; j < size; j++) { //go downwards
			if (isWeakZero(input.val[j][i]) == 0) {
				double coef = input.val[j][i] / input.val[i][i];
				add_lines(input, i, j, -coef);
				add_lines(ext, i, j, -coef);
			}
			else continue;
		}
		int inv = size - i - 1;
		if (isWeakZero(input.val[inv][inv])) { //zero handle
			input.val[inv][inv] = 0;
			char bad = 1;
			for (int j = inv - 1; j >= 0; j--) {
				if ((isWeakZero(input.val[inv][j]) != 1) && (isWeakZero(input.val[j][inv]) != 1)) {
					bad = 0;
					swap_lines(input, inv, j);
					swap_lines(ext, inv, j);
					break;
				}
			}
			if (bad) {
				free_matrix(input);
				free_matrix(ext);
				free_matrix(init);
				err(5, "I guess we cannot find inverse matrix for this one");
			}
		}
		for (int j = inv - 1; j >= 0; j--) { //go upwards
			if (input.val[j][inv] != 0) {
				double coef = input.val[j][inv] / input.val[inv][inv];
				add_lines(input, inv, j, -coef);
				add_lines(ext, inv, j, -coef);
			}
			else continue;
		}
	}
	for (int i = 0; i < size; i++) {
		double coef = 1 / input.val[i][i];
		mul_line(input, i, coef);
		mul_line(ext, i, coef);
	}
	//check matrix
	if (check_matrix(init, ext) == 0) {
		free_matrix(input);
		free_matrix(ext);
		free_matrix(init);
		err(6, "Error: algorithm returned incorrect matrix");
	}
	//output matrix
	if (argc > 1) { //file output
		if ((fout = fopen(argv[3], "w")) == NULL) {
			free_matrix(input);
			free_matrix(ext);
			free_matrix(init);
			err(3, "Error while opening file");
		}
	}
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++)
			fprintf(fout, "%.10lf ", ext.val[i][j]);
		fputs("\n", fout);
	}
	if (argc > 1) fclose(fout);
	//free mem
	free_matrix(input);
	free_matrix(ext);
	free_matrix(init);
	return 0;
}
