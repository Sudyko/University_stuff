#include <complex>
#include <iostream>

using namespace std;

typedef struct { complex<double>** val; int row; int col; } matrix;

void init_matrix(matrix& matrix) {
	scanf("%d %d", &matrix.row, &matrix.col);
	if (matrix.row < 1 || matrix.col < 1) {
		puts("Error: matrix row_num or col_num < 1");
		exit(2);
	}
	matrix.val = (complex<double>**)malloc(sizeof(complex<double>*) * matrix.row);
	for (size_t i = 0; i < matrix.row; i++) {
		matrix.val[i] = (complex<double>*)malloc(sizeof(complex<double>) * matrix.col);
		for (size_t j = 0; j < matrix.col; j++) {
			cin >> matrix.val[i][j];
		}
	}
}

void free_matrix(matrix& matrix) {
	for (size_t i = 0; i < matrix.row; ++i) free(matrix.val[i]);
	free(matrix.val);
}

matrix arithm_matrix(matrix& mat_1, matrix& mat_2, char op) {
	matrix tmp = mat_1;
	for (size_t i = 0; i < tmp.row; ++i) {
		for (size_t j = 0; j < tmp.row; ++j) {
			if (op != '2') tmp.val[i][j] += mat_2.val[i][j];
			else tmp.val[i][j] -= mat_2.val[i][j];
		}
	}
	return tmp;
}

matrix mul_matrix_by_num(matrix& mat, complex<double>& num) {
	matrix tmp = mat;
	for (size_t i = 0; i < mat.row; ++i) {
		for (size_t j = 0; j < mat.row; ++j) {
			tmp.val[i][j] *= num;
		}
	}
	return tmp;
}

matrix mul_mat_by_mat(matrix& mat_1, matrix& mat_2) {
	matrix tmp = { 0, mat_1.row, mat_2.col };
	tmp.val = (complex<double>**)malloc(sizeof(complex<double>*) * tmp.row);
	for (size_t i = 0; i < tmp.row; ++i) {
		tmp.val[i] = (complex<double>*)malloc(sizeof(complex<double>) * tmp.col);
		for (size_t j = 0; j < tmp.col; ++j) {
			tmp.val[i][j] = 0;
			for (size_t k = 0; k < mat_2.row; ++k)
				tmp.val[i][j] += mat_1.val[i][k] * mat_2.val[k][j];
		}
	}
	return tmp;
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
	matrix matrix_1, matrix_2;
	/*FILE* fin;
	FILE* fout;
	if ((argc == 4) && (argv[1] == "-f")) { //file input
		fin = fopen(argv[2], "r");
		fout = fopen(argv[3], "w");
		if ((fin == NULL) || (fout == NULL)) {
			puts("Error while opening files");
			return 3;
		}
		else {
			//read matrix
		}
	}*/
	if (argc == 1) { // console input
		init_matrix(matrix_1);
		init_matrix(matrix_2);
		while (true) {
			char check;
			cout << "[1] Сложение матриц" << endl
				<< "[2] Разность матриц" << endl
				<< "[3] Умножение на комп. число" << endl
				<< "[4] Произведение 2-ух матриц" << endl
				<< "[5] Выход" << endl;
			cin >> check;
			if (check == '1' || check == '2') {
				if (matrix_1.row == matrix_2.row && matrix_1.col == matrix_2.col)
					print_matrix(arithm_matrix(matrix_1, matrix_2, check));
				else puts("Error: matrix_1 and matrix_2 have different sizes.");
			}
			else if (check == '3') {
				complex<double> num;
				cout << "Введите комп. число" << endl;
				cin >> num;
				print_matrix(mul_matrix_by_num(matrix_1, num));
			}
			else if (check == '4') {
				if (matrix_1.row == matrix_2.col && matrix_1.col == matrix_2.row) {
					print_matrix(mul_mat_by_mat(matrix_1, matrix_2));
				} else puts("Error: matrix_1 or matrix_2 has wrong size.");
			}
			else if (check == '5') break;
		}
		free_matrix(matrix_1);
		free_matrix(matrix_2);
	}
	return 0;
}
