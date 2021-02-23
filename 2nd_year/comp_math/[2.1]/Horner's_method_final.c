#include <stdlib.h>
#include <stdio.h>

double bin_pow(double num, int power) {
    if (power == 0) return 1;
    else if (power == 1) return num;
    else if (power & 1) return bin_pow(num, power >> 1) * bin_pow(num, power >> 1) * num;
    else return bin_pow(num, power >> 1) * bin_pow(num, power >> 1);
}

void main(int argc, char** argv) {
    if (argc >= 4) {
        double prev = atof(argv[1]), eps = atof(argv[argc - 1]);
        double* nums = new double[argc - 2];
        double result = 0;
        nums[0] = prev;
        for (int i = 2; i < argc - 1; i++) {
            prev = prev * eps + atoi(argv[i]);
            nums[i - 1] = prev;
        }
        if (eps < 0) printf("(x - (%lg))(", eps);
        else printf("(x + (%lg))(", eps);
        int k = argc - 4;
        for (int i = 0; i < argc - 4; ++i) {
            printf("(%lg) * x^%d + ", nums[i], k--);
        }
        printf("(%lg)) + (%lg)\n", nums[argc - 4], nums[argc - 3]);
        k = argc - 3;
        for (int i = 1; i < argc - 1; ++i) {
            result += atof(argv[i]) * bin_pow(eps, k--);
        }
        printf("%lg == %lg", result, nums[argc - 3]);
        delete[] nums;
    }
    else puts("Minimum 3 arguments: polinominal 'x+a' coefficients and eps");
}