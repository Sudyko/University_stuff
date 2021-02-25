#include <stdlib.h>
#include <stdio.h>

#define ln2 0.69314718

double bin_pow(double num, int power) {
	if (power == 0) return 1;
	else if (power == 1) return num;
	else if (power & 1) return bin_pow(num, power >> 1) * bin_pow(num, power >> 1) * num;
	else return bin_pow(num, power >> 1) * bin_pow(num, power >> 1);
}

double Get_sin(double x, int n) {
	double res, tmp;
	for (int i = n; i > 0; --i) {
		tmp = bin_pow(-1, (i + 1) & 1) * bin_pow(x, (i << 1) - 1);
		for (int j = 2; j <= ((i << 1) - 1); ++j) tmp /= j; // fact 
		res += tmp;
	}
	return res;
}

double Get_Rn(double x, int n) {
	union {
		double doubleVal;
		long long Val;
	}Double;

	Double.doubleVal = x;
	Double.Val -= ((Double.Val >> 52 & 0x7ff) - 1022) << 52; // z calculation
	double eps = (1 - Double.doubleVal) / (1 + Double.doubleVal);
	return 9 * bin_pow(eps, (n << 1) + 1) / ((n << 3) - 4);
}

double Get_ln(double x, int n) {
	union {
		double doubleVal;
		long long Val;
	}Double;

	Double.doubleVal = x;
	long long m = ((Double.Val >> 52 & 0x7ff) - 1022); // Magic m calculation
	Double.Val -= m << 52; // z calculation
	double eps = (1 - Double.doubleVal) / (1 + Double.doubleVal);
	double res = 0;
	double pow = eps;
	for(int i = 1; i <= n; ++i) {	// res += bin_pow(eps, (n << 1) - 1) / ((n << 1) - 1);
		res += pow / ((i << 1) - 1);
		pow *= eps * eps;
	}
	res = m * ln2 - 2 * res;
	return res;
}

void main(int argc, char** argv) {
	// ln (y = ln(kx + t)) and harmonic (y = sin(kx + t)) funcs
	int n = atoi(argv[argc - 1]);
	if (argc == 4) {
		if (atoi(argv[argc - 3]) == 0) { // harmonic
			double x = atof(argv[argc - 2]);
			double Rn = bin_pow(x, (n << 1) + 1);
			for (int i = 2; i <= (n << 1) + 1; ++i) Rn /= i; // fact
			printf("f(x) = %lg\n|Rn| <= |%lg|", Get_sin(x, n), Rn);
		}
		else if (atoi(argv[argc - 3]) == 1) { // ln
			double x = atof(argv[argc - 2]);
			printf("f(x) = %lg\n0 < Rn < %lg", Get_ln(x, n), Get_Rn(x, n));
		}
	}
	else puts("Input error.");
}
