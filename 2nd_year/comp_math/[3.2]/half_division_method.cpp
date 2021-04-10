#include <stdio.h>
#include <math.h>

using namespace std;

double ff(char choice, double x) {
    if (choice == 1) return (2 * pow(x, 3) + pow(x, 2) - 7);
    else if (choice == 2) {
        if (x < 0 || x > 6.2832) {
            puts("Incorrect interval");
            exit(0);
        }
        else return 5 * cos(3 * x) + 0.5 * x - 2;
    }
    else if (choice == 3) return pow(x, 5) - 2 * pow(x, 4) + 6 * pow(x, 2) + 2 * x - 4;
    else if (choice == 4) return pow(x, 3) - 0.2 * pow(x, 2) - 0.2 * x - 1.2;
    else if (choice == 5) return log(abs(pow(x, 3)) + 1) + pow(x, 3) - 2;
}

int main() {
    puts("Choose equation:\n1) 2x^3 + x^2 - 7 = 0\n2) 5cos(3x) + 0.5x = 2\n3) x^5 - 2x^4 + 6x^2 + 2x - 4 = 0\n4) x^3 - 0.2x^2 - 0.2x - 1.2 = 0\n5) ln(|x^3| + 1) + x^3 = 2");
    int choice = 0;
    while(!choice) {
        scanf("%d", &choice);
        if (choice < 1 || choice > 5) choice = 0;
    }
    puts("Write left and right limits");
    double a, b, xm, sigm, f_a, f_b;
    scanf("%lf %lf", &a, &b);
    f_a = ff(choice, a);
    f_b = ff(choice, b);
    if (f_a * f_b > 0) {
        puts("No roots into an interval");
        return 0;
    }
    puts("Write error");
    scanf("%lf", &sigm);
    while((b - a) > sigm) {
        xm = (a + b) / 2;
        double f_xm = ff(choice, xm);
        if (f_a * f_xm < 0) {
            b = xm;
            f_b = f_xm;
        }
        else {
            a = xm;
            f_a = f_xm;
        }
    }
    xm = (a + b) / 2;
    printf("Root: %lf\n", xm);
    return 0;
}