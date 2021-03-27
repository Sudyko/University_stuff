#include <complex>
#include <iostream>
#include <fstream>

using namespace std;

typedef struct { complex<double>** val; int row; int col; } matrix;

void init_matrix(matrix& mat, ifstream& fin) {
	mat.val = (complex<double>**)malloc(sizeof(complex<double>*) * mat.row);
	for (size_t i = 0; i < mat.row; ++i) {
		mat.val[i] = (complex<double>*)malloc(sizeof(complex<double>) * mat.col);
		for (size_t j = 0; j < mat.col; ++j) {
			fin >> mat.val[i][j];
		}
	}
}

void init_matrix(matrix& mat) {
	mat.val = (complex<double>**)malloc(sizeof(complex<double>*) * mat.row);
	for (size_t i = 0; i < mat.row; ++i) {
		mat.val[i] = (complex<double>*)malloc(sizeof(complex<double>) * mat.col);
		for (size_t j = 0; j < mat.col; ++j) {
			cin >> mat.val[i][j];
		}
	}
}

void copy_matrix(matrix& mat, matrix& result) {
	result = { 0, mat.row, mat.col };
	result.val = (complex<double>**)malloc(sizeof(complex<double>*) * result.row);
	for (size_t i = 0; i < result.row; ++i) {
		result.val[i] = (complex<double>*)malloc(sizeof(complex<double>) * result.col);
		for (size_t j = 0; j < result.col; ++j) {
			result.val[i][j] = mat.val[i][j];
		}
	}
}

void free_matrix(matrix& matrix) {
	for (size_t i = 0; i < matrix.row; ++i) free(matrix.val[i]);
	free(matrix.val);
}

void arithm_matrix(matrix& mat_1, matrix& mat_2, char op, matrix& result) {
	for (size_t i = 0; i < result.row; ++i) {
		for (size_t j = 0; j < result.col; ++j) {
			if (op != '2') result.val[i][j] += mat_2.val[i][j];
			else result.val[i][j] -= mat_2.val[i][j];
		}
	}
}

void mul_matrix_by_num(matrix& mat, complex<double>& num, matrix& result) {
	for (size_t i = 0; i < mat.row; ++i) {
		for (size_t j = 0; j < mat.col; ++j) {
			result.val[i][j] *= num;
		}
	}
}

void mul_mat_by_mat(matrix& mat_1, matrix& mat_2, matrix& result) {
	result = { 0, mat_1.row, mat_2.col };
	result.val = (complex<double>**)malloc(sizeof(complex<double>*) * result.row);
	for (size_t i = 0; i < result.row; ++i) {
		result.val[i] = (complex<double>*)malloc(sizeof(complex<double>) * result.col);
		for (size_t j = 0; j < result.col; ++j) {
			result.val[i][j] = 0;
			for (size_t k = 0; k < mat_2.row; ++k)
				result.val[i][j] += mat_1.val[i][k] * mat_2.val[k][j];
		}
	}
}

void print_matrix(matrix mat) {
	for (size_t i = 0; i < mat.row; ++i) {
		for (size_t j = 0; j < mat.col; ++j) {
			cout << mat.val[i][j] << " ";
		}
		cout << endl;
	}
}

int main(int argc, char** argv) {
	matrix matrix_1 = { 0, 0, 0 }, matrix_2 = { 0, 0, 0 };
	if (argc == 2) { //file input
		ifstream fin(argv[1]);
		if (!fin.is_open()) {
			puts("Error: incorrect file name.");
			return 2;
		}
		fin >> matrix_1.row >> matrix_1.col;
		if (matrix_1.row < 1 || matrix_1.col < 1) {
			puts("Error: matrix_1 row_num or col_num < 1");
			return 2;
		}
		init_matrix(matrix_1, fin);
		fin >> matrix_2.row >> matrix_2.col;
		if (matrix_2.row < 1 || matrix_2.col < 1) {
			puts("Error: matrix_2 row_num or col_num < 1");
			return 2;
		}
		init_matrix(matrix_2, fin);
		fin.close();
	}
	else if (argc == 1) { // console input
		scanf("%d %d", &matrix_1.row, &matrix_1.col);
		if (matrix_1.row < 1 || matrix_1.col < 1) {
			puts("Error: matrix_1 row_num or col_num < 1");
			return 2;
		}
		init_matrix(matrix_1);
		scanf("%d %d", &matrix_2.row, &matrix_2.col);
		if (matrix_2.row < 1 || matrix_2.col < 1) {
			puts("Error: matrix_2 row_num or col_num < 1");
			return 2;
		}
		init_matrix(matrix_2);
	}
	else {
		puts("Wrong num of arguments.");
		return 2;
	}
	while (true) {
		char check;
		matrix result = { 0, 0, 0 };
		cout << "[1] Sum matrix." << endl
			<< "[2] Ded. matrix." << endl
			<< "[3] Mul. by comp. num." << endl
			<< "[4] Mul. matrix by matrix." << endl
			<< "[5] Exit." << endl;
		cin >> check;
		if (check == '1' || check == '2') {
			if (matrix_1.row == matrix_2.row && matrix_1.col == matrix_2.col) {
				copy_matrix(matrix_1, result);
				arithm_matrix(matrix_1, matrix_2, check, result);
				print_matrix(result);
			}
			else puts("Error: matrix_1 and matrix_2 have different sizes.");
		}
		else if (check == '3') {
			complex<double> num;
			cout << "Type comp. num." << endl;
			cin >> num; // Does it need check?
			copy_matrix(matrix_1, result);
			mul_matrix_by_num(matrix_1, num, result);
			print_matrix(result);
		}
		else if (check == '4') {
			if (matrix_1.row == matrix_2.col && matrix_1.col == matrix_2.row) {
				mul_mat_by_mat(matrix_1, matrix_2, result);
				print_matrix(result);
			}
			else puts("Error: matrix_1 or matrix_2 has wrong size.");
		}
		else if (check == '5') break;
		if(result.val) free_matrix(result);
	}
	free_matrix(matrix_1);
	free_matrix(matrix_2);
	return 0;
}
