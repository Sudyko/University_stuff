#include <stdlib.h>
#include <stdio.h>

void main(int argc, char** argv) { // Gorner.c
    if (argc >= 4) {
        double prev = atof(argv[1]), eps = atof(argv[argc - 1]);
        printf("%lg ", prev);
        for (int i = 2; i < argc - 1; i++) printf("%lg ", prev = prev * eps + atoi(argv[i]));
    }
    else puts("Minimum 3 arguments: polinominal 'x+a' coefficients and eps");
}