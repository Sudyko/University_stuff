#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))

typedef struct { double** val; int size; } matrix;

matrix init_matrix(matrix to_init, int size) {
	to_init.size = size;
	to_init.val = (double**)malloc(sizeof(double*) * size);
	for (int i = 0; i < size; i++) to_init.val[i] = (double*)malloc(sizeof(double) * size);
	return to_init;
}

void free_matrix(matrix item) {
	for (int i = 0; i < item.size; i++) free(item.val[i]);
	free(item.val);
	item.size = 0;
}

matrix add_lines(matrix item, int from, int to, double coef, char is_col) {
	if (is_col) {
		for (int i = 0; i < item.size; i++) {
			item.val[i][to] += item.val[i][from] * coef;
		}
	}
	else {
		for (int i = 0; i < item.size; i++) {
			item.val[to][i] += item.val[from][i] * coef;
		}
	}
	return item;
}

matrix mul_line(matrix item, int line, double coef, char is_col) {
	if (is_col) {
		for (int i = 0; i < item.size; i++) {
			item.val[i][line] *= coef;
		}
	}
	else {
		for (int i = 0; i < item.size; i++) {
			item.val[line][i] = item.val[line][i] * coef;
		}
	}
	return item;
}

matrix swap_lines(matrix item, int line1, int line2, char is_col) {
	double tmp;
	if (is_col) {
		for (int i = 0; i < item.size; i++) {
			tmp = item.val[i][line1];
			item.val[i][line1] = item.val[i][line2];
			item.val[i][line2] = tmp;
		}
	}
	else {
		for (int i = 0; i < item.size; i++) {
			tmp = item.val[line1][i];
			item.val[line1][i] = item.val[line2][i];
			item.val[line2][i] = tmp;
		}
	}
	return item;
}

int main(int argc, char** argv) {
	matrix input, ext;
	FILE* fin;
	FILE* fout;
	input.size = 0;
	ext.size = 0;
	int size;
	if ((argc == 4) && (argv[1] == "-f")) { //file input
		fin = fopen(argv[2], "r");
		if (fin == NULL) {
			puts("Error while opening file");
			return 3;
		}
		else {
			//read matrix
			fscanf(fin, "%d", &size);
			if (size < 1) {
				puts("Error: matrix size < 1");
				return 2;
			}
			input = init_matrix(input, size);
			ext = init_matrix(ext, size);
			for (size_t i = 0; i < size; i++)
			{
				for (size_t j = 0; j < size; j++)
				{
					fscanf(fin, "%lf", &(input.val[i][j]));
					//fill extended matrix
					if (i == j) ext.val[i][j] = 1;
					else ext.val[i][j] = 0;
				}
			}
		}
		fclose(fin);
	}
	else if (argc == 1) { //console input
		//read matrix
		scanf("%d", &size);
		if (size < 1) {
			puts("Error: matrix size < 1");
			return 2;
		}
		input = init_matrix(input, size);
		ext = init_matrix(ext, size);
		for (size_t i = 0; i < size; i++)
		{
			for (size_t j = 0; j < size; j++)
			{
				scanf("%lf", &(input.val[i][j]));
				//fill extended matrix
				if (i == j) ext.val[i][j] = 1;
				else ext.val[i][j] = 0;
			}
		}
	}
	else puts("Usage:\nNo params - console I/O\nAdd '-f _input _output' for file I/O");
	if (input.size > 0) {
		//process data
		//inverse matrix algorithm itself
		for (size_t i = 0; i < size; i++)
		{
			if (input.val[i][i] == 0) { //zero handle
				char bad = 1;
				for (size_t j = 0; j < size; j++)
				{
					if ((input.val[i][j] != 0) && (input.val[j][i] != 0)) {
						bad = 0;
						swap_lines(input, i, j, 0);
						swap_lines(ext, i, j, 0);
						break;
					}
				}
				if (bad) {
					puts("I guess we cannot find inverse matrix for this one");
					free_matrix(ext);
					free_matrix(input);
					return 5;
				}
			}
			double coef = 1 / input.val[i][i];
			mul_line(input, i, coef, 0);
			mul_line(ext, i, coef, 0);
			for (int j = i + 1; j < size; j++)
			{ //go downwards
				if (input.val[j][i] != 0) {
					coef = 1 / input.val[j][i];
					mul_line(input, j, coef, 0);
					mul_line(ext, j, coef, 0);
					add_lines(input, i, j, -1, 0);
					add_lines(ext, i, j, -1, 0);
				}
				else continue;
			}
			/*for (size_t i = 0; i < size; i++)
			{
				for (size_t j = 0; j < size; j++)
				{
					printf("%lf ", input.val[i][j]);
				}
				puts("");
			}*/
			int inv = size - i - 1;
			if (input.val[inv][inv] == 0) { //zero handle
				char bad = 1;
				for (size_t j = 0; j < size; j++)
				{
					if ((input.val[inv][j] != 0) && (input.val[j][inv] != 0)) {
						bad = 0;
						swap_lines(input, inv, j, 0);
						swap_lines(ext, inv, j, 0);
						break;
					}
				}
				if (bad) {
					puts("I guess we cannot find inverse matrix for this one");
					free_matrix(ext);
					free_matrix(input);
					return 5;
				}
			}

			coef = 1 / input.val[inv][inv];
			mul_line(input, inv, coef, 0);
			mul_line(ext, inv, coef, 0);
			for (int j = inv - 1; j >= 0; j--)
			{ //go upwards
				if (input.val[j][inv] != 0) {
					coef = 1 / input.val[j][inv];
					mul_line(input, j, coef, 0);
					mul_line(ext, j, coef, 0);
					add_lines(input, inv, j, -1, 0);
					add_lines(ext, inv, j, -1, 0);
				}
				else continue;
			}
		}
		//output matrix
		if (argc == 1) { //console
			for (size_t i = 0; i < size; i++)
			{
				for (size_t j = 0; j < size; j++)
				{
					printf("%lf ", ext.val[i][j]);
				}
				puts("");
			}
		}
		else { //file
			fout = fopen(argv[3], "w");
			if (fout == NULL) {
				puts("Error while opening file");
				free_matrix(input);
				free_matrix(ext);
				return 3;
			}
			for (size_t i = 0; i < size; i++)
			{
				for (size_t j = 0; j < size; j++)
				{
					fprintf(fout, "%lf ", ext.val[i][j]);
				}
				fputs("", fout);
			}
			fclose(fout);
		}
		//free mem
		free_matrix(input);
		free_matrix(ext);
	};
	return 0;
}