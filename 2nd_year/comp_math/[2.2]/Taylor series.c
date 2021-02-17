#include <stdlib.h>
#include <stdio.h>

#define ln2 0.69314718

double bin_pow(double num, int power) {
	if (power == 0) return 1;
	else if (power == 1) return num;
	else if (power & 1) return bin_pow(num, power >> 1) * bin_pow(num, power >> 1) * num;
	else return bin_pow(num, power >> 1) * bin_pow(num, power >> 1);
}

long fact(int num) {
	if (num < 2) return 1;
	long res = 1;
	for (int i = 2; i <= num; ++i) {
		res *= i;
	}
	return res;
}

double Get_ln(double num, int n) {

	union {
		double doubleVal;
		long long Val;
	}Double;

	Double.doubleVal = num;
	long long m = (((Double.Val >> 52) & 0x7ff) - 1022); // Magic m calculation
	Double.Val -= m << 52; // z calculation
	double eps = (1 - Double.doubleVal) / (1 + Double.doubleVal);
	double res = 0;
	for (n; n > 0; --n) {
		res += bin_pow(eps, 2 * n - 1) / (2 * n - 1);
	}
	res = m * ln2 - 2 * res;
	return res;
}

void main(int argc, char** argv) {
	// log (y = log_a(kx + t)) and harmonic (y = sin(kx + t)) funcs
	int n = atoi(argv[argc - 1]);
	double res = 0;
	if (argc == 3) { // harmonic
		double x = atof(argv[argc - 2]);
		for (n; n > 0; --n) {
			res += bin_pow(-1, (n + 1) & 1) * bin_pow(x, 2 * n - 1) / fact(2 * n - 1);
		}
		printf("%lg", res);
	}
	else if (argc == 4) { // log
		double num = atof(argv[argc - 2]);
		double a = atof(argv[argc - 3]);
		double res = Get_ln(num, n) / Get_ln(a, n);
		printf("%lg", res);
	}
	else puts("Input error.");
}