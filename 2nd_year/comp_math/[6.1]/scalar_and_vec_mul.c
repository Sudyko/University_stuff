#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { double** val; int size; } matrix;

void print_matrix(matrix& mat) {
    for (size_t i = 0; i < mat.size; ++i){
        for (size_t j = 0; j < mat.size; ++j) {
            printf("%.2lf ", mat.val[i][j]);
        }
        printf("\n");
    }
}

void init_matrix(matrix& mat) {
    do {
        printf("Set square matrix size:\n");
        scanf("%d", &mat.size);
    } while(mat.size < 1);
    printf("Set matrix numbers NxN\n");
    mat.val = (double**)malloc(sizeof(double*) * mat.size);
    for (size_t i = 0; i < mat.size; ++i) {
        mat.val[i] = (double*)malloc(sizeof(double) * mat.size);
        for (size_t j = 0; j < mat.size; ++j) {
            scanf("%lf", &mat.val[i][j]);
        }
    }
}

void free_matrix(matrix& mat) {
	for (size_t i = 0; i < mat.size; ++i) free(mat.val[i]);
	free(mat.val);
}   

void get_vector(matrix& mat, char* pos, int& num, double* vec) {
    if (!strcmp(pos, "row"))
        for(size_t i = 0; i < mat.size; ++i) vec[i] = mat.val[(num + 1) % mat.size][i];
    else
        for(size_t i = 0; i < mat.size; ++i) vec[i] = mat.val[i][(num + 1) % mat.size];
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

int main(int argc, char** argv) {
    matrix mat = { 0, 0 };
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
        mat.val = (double**)malloc(sizeof(double*) * mat.size);
        for (size_t i = 0; i < mat.size; ++i) {
            mat.val[i] = (double*)malloc(sizeof(double) * mat.size);
            for (size_t j = 0; j < mat.size; ++j) {
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
                double* vec1 = (double*)malloc(sizeof(double) * mat.size);
                double* vec2 = (double*)malloc(sizeof(double) * mat.size);
                get_vector(mat, pos1, num1, vec1);
                get_vector(mat, pos2, num2, vec2);
                result = scalar_mul(vec1, vec2, mat.size);
                printf("%.2lf\n", result);
                free(vec1);
                free(vec2);
            }
        }
        else if (check == '2') {
            if (mat.size == 1) {
                printf("1a\n");
                continue;
            }
            printf("Select row or col that won't be used like \"row 1\" or \"col 2\"\n");
            scanf("%s %d", &pos1, &num1);
            if (mat.size == 2) {
                double vec[2];
                get_vector(mat, pos1, num1, vec);
                if ((num1 & 1) != 1) printf("-%.2lfa + %.2lfb\n", vec[0], vec[1]);
                else printf("%.2lfa - %.2lfb\n", vec[0], vec[1]);
                continue;
            }
            if ((!strcmp(pos1, "row") || !strcmp(pos1, "col")) && mat.size > 2) {
                
            }
        }
        else if (check == '3') init_matrix(mat);
        else if (check == '4') print_matrix(mat);
        else if (check == '5') break;
    }
    free_matrix(mat);
    return 0;
}
