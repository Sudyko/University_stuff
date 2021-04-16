#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { double** val; int row; int col; } matrix;

void print_matrix(matrix& mat) {
    for (size_t i = 0; i < mat.row; ++i) {
        for (size_t j = 0; j < mat.col; ++j) {
            printf("%.2lf ", mat.val[i][j]);
        }
        printf("\n");
    }
}

void init_matrix(matrix& mat) {
    do {
        printf("Set square matrix size:\n");
        scanf("%d", &mat.row);
    } while (mat.row < 1);
    mat.col = mat.row;
    printf("Set matrix numbers NxN\n");
    mat.val = (double**)malloc(sizeof(double*) * mat.row);
    for (size_t i = 0; i < mat.row; ++i) {
        mat.val[i] = (double*)malloc(sizeof(double) * mat.col);
        for (size_t j = 0; j < mat.col; ++j) {
            scanf("%lf", &mat.val[i][j]);
        }
    }
}

void free_matrix(matrix& mat) {
    for (size_t i = 0; i < mat.row; ++i) free(mat.val[i]);
    free(mat.val);
}

void get_vector(matrix& mat, char* pos, int& num, double* vec) {
    if (!strcmp(pos, "row"))
        for (size_t i = 0; i < mat.row; ++i) vec[i] = mat.val[(num + 1) % mat.row][i];
    else
        for (size_t i = 0; i < mat.col; ++i) vec[i] = mat.val[i][(num + 1) % mat.col];
}

double scalar_mul(double* vec1, double* vec2, int& size) {
    double sum = 0;
    for (size_t i = 0; i < size; ++i) sum += vec1[i] * vec2[i];
    return sum;
}

void print_name(int n) {
    char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";
    int k = n, count = 0;
    do {
        k /= 26;
        ++count;
    } while (k > 0);
    char* res = (char*)malloc(sizeof(char) * count);
    k = 0;
    do {
        res[k++] = alphabet[n % 26];
        n /= 26;
    } while ((--n + 1) > 0);
    for (count -= 1; count >= 0; --count) printf("%c", res[count]);
    free(res);
}

void get_new_matrix(matrix& mat, int size, int row, int col, matrix& new_mat) {
    int offsetRow = 0;
    int offsetCol = 0;
    for (size_t i = 0; i < size - 1; ++i) {
        if (i == row) offsetRow = 1;
        offsetCol = 0;
        for (size_t j = 0; j < size - 1; ++j) {
            if (j == col) offsetCol = 1;
            new_mat.val[i][j] = mat.val[i + offsetRow][j + offsetCol];
        }
    }
}

double get_det(matrix& mat, int size) {
    double det = 0;
    int degree = 1;
    if (size == 1) return mat.val[0][0];
    else if (size == 2) return mat.val[0][0] * mat.val[1][1] - mat.val[0][1] * mat.val[1][0];
    else {
        matrix new_mat = { 0, size - 1, size - 1 };
        new_mat.val = (double**)malloc(sizeof(double*) * size - 1);
        for (size_t i = 0; i < size - 1; ++i) new_mat.val[i] = (double*)malloc(sizeof(double) * size - 1);
        for (size_t j = 0; j < size; ++j) {
            get_new_matrix(mat, size, 0, j, new_mat);
            det += degree * mat.val[0][j] * get_det(new_mat, size - 1);
            degree = -degree;
        }
        free_matrix(new_mat);
    }
    return det;
}

int main(int argc, char** argv) {
    matrix mat = { 0, 0 };
    if (argc == 2) { // file input
        FILE* fin;
        fin = fopen(argv[argc - 1], "r");
        if (fin == NULL) return 2;
        fscanf(fin, "%d", &mat.row);
        if (mat.row < 1) {
            puts("Wrong matrix size!");
            fclose(fin);
            return 2;
        }
        mat.col = mat.row;
        mat.val = (double**)malloc(sizeof(double*) * mat.row);
        for (size_t i = 0; i < mat.row; ++i) {
            mat.val[i] = (double*)malloc(sizeof(double) * mat.col);
            for (size_t j = 0; j < mat.col; ++j) {
                fscanf(fin, "%lf", &mat.val[i][j]);
            }
        }
        fclose(fin);
    }
    else if (argc == 1) init_matrix(mat);
    else {
        puts("Wrong num of arguments!");
        return 2;
    }
    while (true) {
        char check;
        char pos1[4] = { 0 }, pos2[4] = { 0 };
        int num1, num2;
        double result;
        printf("[1] scalar multiply\n[2] vector multiply\n[3] change matrix\n[4] print matrix\n[5] exit\n");
        scanf(" %c", &check);
        if (check == '1') {
            scanf("%s %d %s %d", &pos1, &num1, &pos2, &num2);
            if ((!strcmp(pos1, "row") || !strcmp(pos1, "col")) && (!strcmp(pos2, "row") || !strcmp(pos2, "col"))) {
                double* vec1 = (double*)malloc(sizeof(double) * mat.row);
                double* vec2 = (double*)malloc(sizeof(double) * mat.row);
                get_vector(mat, pos1, num1, vec1);
                get_vector(mat, pos2, num2, vec2);
                result = scalar_mul(vec1, vec2, mat.row);
                printf("%.2lf\n", result);
                free(vec1);
                free(vec2);
            }
        }
        else if (check == '2') {
            if (mat.row == 1) {
                printf("1a\n");
                continue;
            }
            printf("Select row or col that won't be used like \"row 1\" or \"col 2\"\n");
            scanf("%s %d", &pos1, &num1);
            if (mat.row == 2) {
                double vec[2];
                get_vector(mat, pos1, num1, vec);
                if ((num1 & 1) != 1) printf("-%.2lfa + %.2lfb\n", vec[0], vec[1]);
                else printf("%.2lfa - %.2lfb\n", vec[0], vec[1]);
                continue;
            }
            else if (mat.row > 2) {
                matrix new_mat = { 0, mat.row - 1, mat.row - 1 };
                new_mat.val = (double**)malloc(sizeof(double*) * new_mat.row);
                for (size_t i = 0; i < new_mat.row; ++i) new_mat.val[i] = (double*)malloc(sizeof(double) * new_mat.row);
                if (!strcmp(pos1, "row")) {
                    for (size_t i = 0; i < mat.row; ++i) {
                        get_new_matrix(mat, mat.row, num1 - 1, i, new_mat);
                        double det = get_det(new_mat, new_mat.row);
                        if (i & 1) printf("- (%.2lf)", det);
                        else printf("+ (%.2lf)", det);
                        print_name(i);
                        printf(" ");
                    }
                    puts("");
                }
                else {
                    for (int i = 0; i < mat.row; ++i) {
                        get_new_matrix(mat, mat.row, i, num1 - 1, new_mat);
                        double det = get_det(new_mat, new_mat.row);
                        if (i & 1) printf("- (%.2lf)", det);
                        else printf("+ (%.2lf)", det);
                        print_name(i);
                        printf(" ");
                    }   
                    puts("");
                }
                free_matrix(new_mat);
            }
            else continue;
        }
        else if (check == '3') {
            free_matrix(mat);
            init_matrix(mat);
        }
        else if (check == '4') print_matrix(mat);
        else if (check == '5') break;
    }
    free_matrix(mat);
    return 0;
}
