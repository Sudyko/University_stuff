#include <complex>
#include <iostream>
#include <fstream>

using namespace std;

typedef struct { complex<double>** val; int row; int col; } matrix;

char init_matrix(matrix& mat, ifstream& fin) {
	complex<double>** alloc = (complex<double>**)calloc(mat.row, sizeof(complex<double>*));
	if (alloc) mat.val = alloc;
	else {
		puts("Memory allocation error");
		return 1;
	}
	for (size_t i = 0; i < mat.row; ++i) {
		complex<double>* nalloc = (complex<double>*)calloc(mat.col, sizeof(complex<double>));
		if (nalloc) mat.val[i] = nalloc;
		else {
			puts("Memory allocation error");
			return 1;
		}
		for (size_t j = 0; j < mat.col; ++j) {
			bool flag = true;
			while (flag){
				fin >> mat.val[i][j]; 
				flag = fin.fail();
				if (flag){
					fin.clear();
					fin.ignore(32767, '\n');
				}
			}
		}
	}
	return 0;
}

char init_matrix(matrix& mat) {
	complex<double>** alloc = (complex<double>**)calloc(mat.row, sizeof(complex<double>*));
	if (alloc) mat.val = alloc;
	else {
		puts("Memory allocation error");
		return 1;
	}
	for (size_t i = 0; i < mat.row; ++i) {
		complex<double>* nalloc = (complex<double>*)calloc(mat.col, sizeof(complex<double>));
		if (nalloc) mat.val[i] = nalloc;
		else {
			puts("Memory allocation error");
			return 1;
		}
		for (size_t j = 0; j < mat.col; ++j) {
			bool flag = true;
			while (flag){
				cin >> mat.val[i][j]; 
				flag = cin.fail();
				if (flag){
					cin.clear();
					cin.ignore(32767, '\n');
				}
			}
		}
	}
	return 0;
}

char copy_matrix(matrix& mat, matrix& result) {
	result = { 0, mat.row, mat.col };
	complex<double>** alloc = (complex<double>**)calloc(result.row, sizeof(complex<double>*));
	if (alloc) result.val = alloc;
	else {
		puts("Memory allocation error");
		return 1;
	}
	for (size_t i = 0; i < result.row; ++i) {
		complex<double>* nalloc = (complex<double>*)calloc(result.col, sizeof(complex<double>));
		if (nalloc) result.val[i] = nalloc;
		else {
			puts("Memory allocation error");
			return 1;
		}
		for (size_t j = 0; j < result.col; ++j) {
			result.val[i][j] = mat.val[i][j];
		}
	}
	return 0;
}

void free_matrix(matrix& Matrix) {
	for (size_t i = 0; i < Matrix.row; ++i) if(Matrix.val[i]) free(Matrix.val[i]);
	free(Matrix.val);
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

char mul_mat_by_mat(matrix& mat_1, matrix& mat_2, matrix& result) {
	result = { 0, mat_1.row, mat_2.col };
	complex<double>** alloc = (complex<double>**)calloc(result.row, sizeof(complex<double>*));
	if (alloc) result.val = alloc;
	else {
		puts("Memory allocation error");
		return 1;
	}
	for (size_t i = 0; i < result.row; ++i) {
		complex<double>* nalloc = (complex<double>*)calloc(result.col, sizeof(complex<double>));
		if (nalloc) result.val[i] = nalloc;
		else {
			puts("Memory allocation error");
			return 1;
		}
		for (size_t j = 0; j < result.col; ++j) {
			result.val[i][j] = 0;
			for (size_t k = 0; k < mat_2.row; ++k)
				result.val[i][j] += mat_1.val[i][k] * mat_2.val[k][j];
		}
	}
	return 0;
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
		bool flag = true;
		while (flag){
			fin >> matrix_1.row >> matrix_1.col; 
			flag = fin.fail();
			if (flag){
				fin.clear();
				fin.ignore(32767, '\n');
			}
		}
		if (matrix_1.row < 1 || matrix_1.col < 1) {
			puts("Error: matrix_1 row_num or col_num < 1");
			return 2;
		}
		char bad_alloc = init_matrix(matrix_1, fin);
		if (bad_alloc) {
			free_matrix(matrix_1);
			return 10;
		};
		while (flag){
			fin >> matrix_2.row >> matrix_2.col; 
			flag = fin.fail();
			if (flag){
				fin.clear();
				fin.ignore(32767, '\n');
			}
		}
		if (matrix_2.row < 1 || matrix_2.col < 1) {
			puts("Error: matrix_2 row_num or col_num < 1");
			return 2;
		}
		bad_alloc = init_matrix(matrix_2, fin);
		if (bad_alloc) {
			free_matrix(matrix_1);
			free_matrix(matrix_2);
			return 10;
		};
		fin.close();
	}
	else if (argc == 1) { // console input
		scanf("%d %d", &matrix_1.row, &matrix_1.col);
		if (matrix_1.row < 1 || matrix_1.col < 1) {
			puts("Error: matrix_1 row_num or col_num < 1");
			return 2;
		}
		char bad_alloc = init_matrix(matrix_1);
		if (bad_alloc) {
			free_matrix(matrix_1);
			return 10;
		};
		scanf("%d %d", &matrix_2.row, &matrix_2.col);
		if (matrix_2.row < 1 || matrix_2.col < 1) {
			puts("Error: matrix_2 row_num or col_num < 1");
			return 2;
		}
		bad_alloc = init_matrix(matrix_2);
		if (bad_alloc) {
			free_matrix(matrix_1);
			free_matrix(matrix_2);
			return 10;
		};
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
		cin.ignore(32767, '\n');
		if (check == '1' || check == '2') {
			if (matrix_1.row == matrix_2.row && matrix_1.col == matrix_2.col) {
				char bad_alloc = copy_matrix(matrix_1, result);
				if (bad_alloc){
					free_matrix(matrix_1);
					free_matrix(matrix_2);
					free_matrix(result);
					return 10;
				}
				arithm_matrix(matrix_1, matrix_2, check, result);
				print_matrix(result);
			}
			else puts("Error: matrix_1 and matrix_2 have different sizes.");
		}
		else if (check == '3') {
			complex<double> num;
			cout << "Type comp. num." << endl;
			bool flag = true;
			while (flag){
				cin >> num; // Does it need check?
				flag = cin.fail();
				if (flag){
					cin.clear();
					cin.ignore(32767, '\n');
				}
			}
			char bad_alloc = copy_matrix(matrix_1, result);
			if (bad_alloc){
				free_matrix(matrix_1);
				free_matrix(matrix_2);
				free_matrix(result);
				return 10;
			}
			mul_matrix_by_num(matrix_1, num, result);
			print_matrix(result);
		}
		else if (check == '4') {
			if (matrix_1.row == matrix_2.col && matrix_1.col == matrix_2.row) {
				char bad_alloc = mul_mat_by_mat(matrix_1, matrix_2, result);
				if (bad_alloc) {
					free_matrix(matrix_2);
					free_matrix(matrix_1);
					free_matrix(result);
					return 10;
				}
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
