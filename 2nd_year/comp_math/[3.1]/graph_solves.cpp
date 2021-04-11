#include <stdio.h>
#include <math.h>
#include <fstream>
using namespace std;

double f1(double x) { return 5 * pow(x, 4) - 2 * pow(x, 3) + 3 * pow(x, 2) + x - 4; }

double f2(double x) { return pow(x, 5) - 3 * pow(x, 4) + 7 * pow(x, 2) + x - 8; }

int main() {
    ofstream fout1("file1.csv"), fout2("file2.csv");
    puts("\n [!] Interval: from -10 to 10; Step: 0.01\n [!] f1(x) = 5x^4-2x^3+3x^2+x-4; Output: file1.csv\n [!] f2(x) = x^5-3x^4+7x^2+x-8; Output: file2.csv\n");
    fout1 << "x;y" << endl;
    fout2 << "x;y" << endl;
    for(int i = -1000; i <= 1000; ++i) {
        double k = i / 100 + 0.01 * (i % 100);
        double kp = (i - 1) / 100 + 0.01 * ((i - 1) % 100);
        fout1 << k << ";" << f1(k) << endl;
        fout2 << k << ";" << f2(k) << endl;
        if(f1(kp) * f1(k) <= 0) printf(" [+] f1(x) > Solution located between %lf and %lf\n", kp, k);
        if(f2(kp) * f2(k) <= 0) printf(" [+] f2(x) > Solution located between %lf and %lf\n", kp, k);
    }
    fout1.close();
    fout2.close();
    return 0;
}