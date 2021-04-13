#include <iostream>
#include <complex>

using namespace std;

complex<double> f(complex<double> z) { 
    return 4.0 * pow(z, 4) + 2.0 * pow(z, 2) + 1.3;
    //return pow(z, 2) + 2.71;
    //return 2.0 * exp(z) + sqrt(2.0);
}
complex<double> df(complex<double> z) {
    return 4.0 * (z + 4.0 * pow(z, 3));
    //return 2.0 * z;
    //return 2.0 * exp(z);
}

int main() {
    complex<double> z = {1, 1};
    double err = 1e-12, i = 1;
    while(abs(f(z)) > err && ++i) z -= f(z) / df(z);
    cout << "Iteration counter: " << i - 1 << endl << "Root: " << z << endl;
    return 0;
}