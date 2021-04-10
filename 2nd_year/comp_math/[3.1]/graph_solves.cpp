#include <iostream>
#include <fstream>
using namespace std;

double f1(double x) { return 5*x*x*x*x-2*x*x*x+3*x*x+x-4; }

double f2(double x) { return x*x*x*x*x-3*x*x*x*x+7*x*x+x-8; }

int main()
{
    ofstream fout1("file1.csv");
    ofstream fout2("file2.csv");
    cout << endl << " [!] Interval: from -10 to 10; Step: 0.01" << endl;
    cout << " [!] f1(x) = 5x^4-2x^3+3x^2+x-4; Output: file1.csv" << endl;
    cout << " [!] f2(x) = x^5-3x^4+7x^2+x-8; Output: file2.csv" << endl << endl;
    fout1 << "x;y" << endl;
    fout2 << "x;y" << endl;
    for(int i = -1000; i <= 1000; i++)
    {
        double k = i / 100 + 0.01 * (i % 100);
        double kp = (i - 1) / 100 + 0.01 * ((i - 1) % 100);
        fout1 << k << ";" << f1(k) << endl;
        fout2 << k << ";" << f2(k) << endl;
        if(f1(kp) * f1(k) <= 0)
        {
            cout << " [+] f1(x) > Solution located between " << kp << " and " << k << endl;
        }
        if(f2(kp) * f2(k) <= 0)
        {
            cout << " [+] f2(x) > Solution located between " << kp << " and " << k << endl;
        }
    }
    fout1.close();
    fout2.close();
    return 0;
}