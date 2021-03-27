#include <stdio.h>
#include <stdlib.h>

typedef struct { double** val; int size } matrix;

void init_matrix(matrix& mat) {
    do {
        printf("Set square matrix size:\n");
        scanf("%d", &mat.size);
    } while(mat.size < 1);
    printf("Set matrix numbers NxN\n");
    mat.val = (double*)malloc(sizeof(double) * mat.size);
    for (size_t i = 0; i < mat.size; ++i) {
        mat.val[i] = (double*)malloc(sizeof(double) * mat.size);
        for (size_t j = 0; j < mat.size; ++j) {
            scanf("%f", &mat.val[i][j]);
        }
    }
}

void free_matrix(matrix& mat) {
	for (size_t i = 0; i < mat.size; ++i) free(mat.val[i]);
	free(mat.val);
}

int main(int argc; char** argv) {
    matrix mat = { 0, 0, 0 };
    if (argc == 2) { // file input
        FILE* fin;
        fin = fopen(argv[argc - 1], "r");
        if (fin == NULL) return 2;
        fscanf(fin, "%d", &mat.size);
        if (mat.size < 1) {
            puts("Wrong matrix size!");
            fclose(fin);
            return 2;
        }
        mat.val = (double*)malloc(sizeof(double) * mat.size);
        for (size_t i = 0; i < mat.size; ++i) {
            mat.val[i] = (double*)malloc(sizeof(double) * mat.size);
            for (size_t j = 0; j < mat.size; ++j) {
                fscanf(fin, "%f", &mat.val[i][j]);
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
        printf("1) scalar multiply\n2) vector multiply\n3) change matrix\n4) exit\n>");
        scanf("%c", &check);
        if (check == '1') {

        }
        else if (check == '2') {

        }
        else if (check == '3') init_matrix(mat);
        else if (check == '4') break;
    }
    free_matrix(mat);
    return 0;
}