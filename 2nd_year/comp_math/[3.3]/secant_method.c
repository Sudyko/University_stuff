#include <stdio.h>
#include <math.h>

double f(double x) {
    return pow(5, x) * sqrt(pow(8, (x-1))) - 189;
    //return pow(x, 3) - pow(x, 2) + 2 * x - 5;
    //return 2 * log10(pow(x, 2)) - 5 * pow(log10(x), 2) + 4;
    //return 2 * sin(2 * x) - cos(3 * x) - 0.5;
    //return 2 * pow(x, 3) - 7 * pow(x, 2) - 7 * x - 2.5;
}

double df2(double x) {
    return sqrt(2) * pow(5, x) * (pow(log(8), 2) + 4 * pow(log(5), 2) + 4 * log(5) * log(8)) * sqrt(pow(8, x)) / 16;
    //return 6 * x - 2;
    //return (2 * (5 * log10(x) - 5 / log(10)) - 2) / (pow(x, 2) * log(10));
    //return (-8 * sin(2 * x) + 9 * cos(3 * x));
    //return (2 * (6 * x - 7));
}

int main() {
    puts("Write right, left limits and desired accuracy:");
    double a, b, d, x, sigm;
    scanf("%lf %lf %lf", &a, &b, &sigm);
    if (fabs(b - a) <= sigm) {
        puts("Error: small segment or big error");
        return 1;
    }
    else if(f(a) * f(b) >= 0) {
        puts("Error: the same sign at the ends of the interval. Choose different interval.");
        return 2;
    }
    if (df2(b) * f(b) < 0) x = a;
    if (df2(a) * f(a) < 0) x = b;
    do {
        d = x;
        x = a - f(a) * (b - a) / (f(b) - f(a));
        d = fabs(d - x);
        if (f(x) * f(b) < 0) a = x;
        if (f(x) * f(a) < 0) b = x;
    } while (d > sigm);
    printf("Root: %lf\nF(x) = %lf\n", x, f(x));
    return 0;
}