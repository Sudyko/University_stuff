#include <iostream>
#include <complex>
#include <iomanip>
#include <vector>

using namespace std;

#define DIRECT -1
#define INVERSE 1

typedef complex<double> Complex;

vector<Complex> computeDft(const vector<Complex>& input, char sign) {
    vector<Complex> output;
    size_t n = input.size();
    for (size_t k = 0; k < n; ++k) {
        Complex sum(0, 0);
        for (size_t t = 0; t < n; ++t) sum += input[t] * exp(Complex(0, sign * (double)(M_PI * t * (k << 1) / n)));
        if (sign == 1) sum /= n;
        output.push_back(sum);
    }
    return output;
}

float f(float x) { return pow(sin(2 * x), 2); }
float dfdx(float x) { return 2 * 2 * sin(2 * x) * cos(2 * x); }
float df2dx2(float x) { return 2 * pow(2, 2) * (pow(cos(2 * x), 2) - pow(sin(2 * x), 2)); }

int main() {
    int N = 128;
    vector<Complex> vec(N), dFvec(N), dF2vec(N);
    float a = 1, b = 1 + M_PI / 2, dx = (b - a) / N;
    for (int i = 0; i < N; ++i) vec[i] = Complex(f(a + dx * i), 0);
    vec = computeDft(vec, DIRECT);
    for (int i = 0; i < N; ++i) {
        float k = (M_PI * 2) / (b - a);
        if (i < (N >> 1)) k *= i;
        else if (i == (N >> 1)) k = 0;
        else k *= (i - N);
        dFvec[i] = Complex(-vec[i].imag() * k, vec[i].real() * k);
        dF2vec[i] = Complex(-vec[i].real() * k * k, -vec[i].imag() * k * k);
    }
    vec = computeDft(vec, INVERSE);
    dFvec = computeDft(dFvec, INVERSE);
    dF2vec = computeDft(dF2vec, INVERSE);
    puts("      First derivative    |       Second derivative");
    for (int i = 0; i < N; ++i) cout << setw(25) << dFvec[i] << " | " << setw(25) << dF2vec[i] << endl;
    puts("\n1st derivative error |   2nd derivative error");
    cout.precision(10);
    for (int i = 0; i < N; ++i) cout << fixed << setw(20) << dFvec[i].real() - dfdx(a + dx * i) << " | " << fixed << setw(18) << dF2vec[i].real() - df2dx2(a + dx * i) << endl;
    return 0;
}
