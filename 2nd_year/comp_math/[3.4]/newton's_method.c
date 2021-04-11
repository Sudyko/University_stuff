#include <stdio.h>
#include <math.h>

#define PI 3.1415926535

/* Equations:
2 * log10(x) - cos(x) = 0
2 * pow(x, 3) - 5 * pow(x, 2) - 1 = 0
2 * pow(sin(2 * x), 3) - cos(x) = 0
pow(x, 5) - 3 * pow(x, 4) + 8 * pow(x, 2) + 2 * x - 7 = 0
0.5 * pow(x, 2) + 5 * cos(2 * x) - 2 = 0
*/

double f(double x) { return 0.5 * pow(x, 2) + 5 * cos(2 * x) - 2; }
double df(double x) { return x - 10 * sin(2 * x); }
double d2f(double x) { return 1 - 20 * cos(2 * x); }

int main() {
    double x0, xn; // approximations for calculation root
    double a = -PI, b = -2, eps = 0.0001; // limits and accuracy
    if (f(a) * f(b) > 0) puts("Error: no roots in this interval");
    else {
        if (f(a) * d2f(a) > 0) x0 = a; // start point (a or b)
        else x0 = b;
        xn = x0 - f(x0) / df(x0); // first approximation
        while(fabs(x0 - xn) > eps) xn = (x0 = xn) - f(x0) / df(x0); // Newton's method
        printf("Root: %lf\n", xn);
    }
    return 0;
}