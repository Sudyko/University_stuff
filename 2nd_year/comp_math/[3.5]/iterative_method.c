#include <stdio.h>
#include <math.h>

double iter(double F(double x), double x0, const double eps) {
    int i = 0;
    double x1;
    if (F(x0) != x0) {
        while (1) {
            i++;
            x1 = F(x0);
            if (abs(x1 - x0) <= eps) break;
            x0 = x1;
            if ((x1 != 0) && (x1/x1 != 1)) {
                puts("Error: divergence");
                break;
            }
        }
    }
    else {
        puts("Message: x0 = x");
        x1 = x0;
    }
    return x1;
}

double F1(double x) { return cos(x) - 0.1 + x; }
double F2(double x) { return pow((1000 - x), (1.0/3)); }
double F3(double x) { return pow((pow(x,4) + pow(x,2) + x + 5), (1.0/5)); }
double F4(double x) { return pow((x + 1), (1.0 / 3)); }
double F5(double x) { return sqrt(2.25*x - log(x)*x); }

int main() {
    const double eps = 0.001, x0 = 10; // Error and start point
    printf("f1 = %lf\nf2 = %lf\nf3 = %lf\nf4 = %lf\nf5 = %lf\n", 
    iter(F1, x0, eps), iter(F2, x0, eps), iter(F3, x0, eps), iter(F4, x0, eps), iter(F5, 1.5, eps));
    return 0;
}
