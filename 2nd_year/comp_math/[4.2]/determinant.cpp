#include <iostream>
#include <fstream>
#include <string.h>
#include <complex>

using namespace std;

typedef struct { double** val; int size; } matrix;
typedef struct { complex<double>** val; int size; } complex_matrix;

void err(const char* msg, int code) { puts(msg); exit(code); };

void free_matrix(matrix* mat) {
	for (size_t i = 0; i < (*mat).size; ++i) if((*mat).val[i]) free((*mat).val[i]);
	free((*mat).val);
}

void free_complex_matrix(complex_matrix* mat) {
    for (size_t i = 0; i < (*mat).size; ++i) if((*mat).val[i]) free((*mat).val[i]);
	free((*mat).val);
}

void init_matrix(matrix* mat) {
    puts("Fill the matrix.");
    (*mat).val = (double**)malloc(sizeof(double*) * (*mat).size);
    for (size_t i = 0; i < (*mat).size; ++i) {
        (*mat).val[i] = (double*)malloc(sizeof(double) * (*mat).size);
        for (size_t j = 0; j < (*mat).size; ++j) scanf("%lf", &(*mat).val[i][j]);
    } 
}

void init_complex_matrix(complex_matrix* mat) {
    puts("Fill the matrix");
    (*mat).val = (complex<double>**)malloc(sizeof(complex<double>*) * (*mat).size);
    for (size_t i = 0; i < (*mat).size; ++i) {
        (*mat).val[i] = (complex<double>*)malloc(sizeof(complex<double>) * (*mat).size);
        for (size_t j = 0; j < (*mat).size; ++j) cin >> (*mat).val[i][j];
    }
}

void init_matrix_via_file(matrix* mat, ifstream& fin) {
    (*mat).val = (double**)malloc(sizeof(double*) * (*mat).size);
    for (size_t i = 0; i < (*mat).size; ++i) {
        (*mat).val[i] = (double*)malloc(sizeof(double) * (*mat).size);
        for (size_t j = 0; j < (*mat).size; ++j) fin >> (*mat).val[i][j];
    }
}

void init_complex_matrix_via_file(complex_matrix* mat, ifstream& fin) {
    (*mat).val = (complex<double>**)malloc(sizeof(complex<double>*) * (*mat).size);
    for (size_t i = 0; i < (*mat).size; ++i) {
        (*mat).val[i] = (complex<double>*)malloc(sizeof(complex<double>) * (*mat).size);
        for (size_t j = 0; j < (*mat).size; ++j) fin >> (*mat).val[i][j];
    }
}

double get_det_via_gauss_method(matrix mat) { // determinant via Gauss method
    double ratio, det = 1;
    if (mat.size == 1) return mat.val[0][0];
    else if(mat.size == 2) return mat.val[0][0] * mat.val[1][1] - mat.val[1][0] * mat.val[0][1];
    else {
        for(size_t i = 0; i < mat.size; ++i) {
            if (mat.val[i][i] == 0) return 0;
            for (size_t j = i + 1; j < mat.size; ++j) {
                ratio = mat.val[j][i] / mat.val[i][i];
                for (size_t k = 0; k < mat.size; ++k) mat.val[j][k] -= ratio * mat.val[i][k];
            }
            det *= mat.val[i][i];
        }
    }
    return det;
}

char isWeakZero(double num) {
	if (num == 0) return 1;
	else return 0;
}

char isWeakZero_comp(complex<double> num) {
    complex<double> null = { 0, 0 };
    if (num == null) return 1;
    else return 0;
}

void add_lines(matrix* mat, int from, int to, double coef) {
	for (size_t i = 0; i < (*mat).size; ++i) (*mat).val[to][i] += (*mat).val[from][i] * coef;
}

void add_comp_lines(complex_matrix* mat, int from, int to, complex<double> coef) {
    for (size_t i = 0; i < (*mat).size; ++i) (*mat).val[to][i] += (*mat).val[from][i] * coef;
}

double get_det_via_operations(matrix mat) { // determinant via elementary matrix operations
    double det = 1;
    if (mat.size == 1) return mat.val[0][0];
    else if(mat.size == 2) return mat.val[0][0] * mat.val[1][1] - mat.val[1][0] * mat.val[0][1];
    else {
        for(size_t i = 0; i < mat.size; ++i) {
            for (int j = i + 1; j < mat.size; j++) {
                if (isWeakZero(mat.val[j][i]) == 0) {
                    double coef = mat.val[j][i] / mat.val[i][i];
                    add_lines(&mat, i, j, -coef);
                }
                else continue;
		    }
        }
        for (size_t i = 0; i < mat.size; ++i) det *= mat.val[i][i];
    }
    return det;
}

complex<double> get_complex_det_via_operaions(complex_matrix mat) { // complex determinant via elementary matrix operations
    complex<double> det = { 1, 0 };
    if (mat.size == 1) return mat.val[0][0];
    else if(mat.size == 2) return mat.val[0][0] * mat.val[1][1] - mat.val[1][0] * mat.val[0][1];
    else {
        for(size_t i = 0; i < mat.size; ++i) {
            for (int j = i + 1; j < mat.size; j++) {
                if (isWeakZero_comp(mat.val[j][i]) == 0) {
                    complex<double> coef = mat.val[j][i] / mat.val[i][i];
                    add_comp_lines(&mat, i, j, -coef);
                }
                else continue;
		    }
        }
        for (size_t i = 0; i < mat.size; ++i) det *= mat.val[i][i];
    }
    return det;
}

int main(int argc, char** argv) {
    if (argc != 3 && argc != 1) err("Error: wrong number of arguments.", 1);
    else if (argc == 3) {
		ifstream fin(argv[argc - 1]);
		if (!fin.is_open()) err("Error: incorrect file name.", 2);
		if (!strcmp(argv[1], "-c")) {
            complex_matrix mat;
            fin >> mat.size;
            if (mat.size < 1) {
                fin.close();
                err("Error: matrix size < 1", 3);
            }
            init_complex_matrix_via_file(&mat, fin);
            fin.close();
            cout << "Complex determinant: " << get_complex_det_via_operaions(mat) << endl;
            free_complex_matrix(&mat);
            return 0;
        }
        else if(!strcmp(argv[1], "-r")) {
            matrix mat;
            fin >> mat.size;
            if (mat.size < 1) {
                fin.close();
                err("Error: matrix size < 1", 3);
            }
            init_matrix_via_file(&mat, fin);
            printf("Determinant via elementary matrix operations: %lf\n", get_det_via_operations(mat));
            printf("Determinant via Gauss method: %.4lf\n", get_det_via_gauss_method(mat));
            free_matrix(&mat);
            return 0;
        }
        else {
            fin.close();
            err("Error: incorrect opening file | example: a.exe -r matrix.txt", 2);
        }
    }
    else {
        while (1) {
            char check = 0;
            puts("Choose type of matrix:\n[1] Real matrix\n[2] Complex matrix\n[3] Exit");
            scanf(" %c", &check);
            if (check == '1') {
                matrix mat;
                puts("Set matrix size");
                scanf("%d", &mat.size);
                if (mat.size < 1) err("Error: matrix size < 1", 3);
                init_matrix(&mat);
                printf("Determinant via elementary matrix operations: %lf\n", get_det_via_operations(mat));
                printf("Determinant via Gauss method: %.4lf\n", get_det_via_gauss_method(mat));
                free_matrix(&mat);
            }
            else if (check == '2') {
                complex_matrix mat;
                puts("Set matrix size");
                scanf("%d", &mat.size);
                if (mat.size < 1) err("Error: matrix size < 1", 3);
                init_complex_matrix(&mat);
                cout << "Complex determinant: " << get_complex_det_via_operaions(mat) << endl;
                free_complex_matrix(&mat);
            }
            else if (check == '3') break;
            puts("");
        }
    }
    return 0;
}