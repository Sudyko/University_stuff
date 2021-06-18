#pragma warning(disable : 4996)
#include "iostream"
#include "DecStr.h"

using namespace std;

DecStr::DecStr(int val) :str(val)
{
    len = 1;
    pch[0] = '0';
    pch[1] = '\0';
    char* sum;
    char p1[40] = "DecStr::DecStr(int val):str(val), val=";
    char* sval = new char[4];
    _itoa_s(val, sval, 4, 10);
    int newlen = 42 + strlen(sval);
    sum = new char[newlen];
    sum[0] = '\0';
    strcat_s(sum, newlen, p1);
    strcat_s(sum, newlen, sval);
    strcat_s(sum, newlen, "\n\r");
    conc(sum);
    delete[]sval;
    delete[]sum;
}
DecStr::~DecStr() { conc("\r\nDecStr::~DecStr()\r\n"); }
DecStr::DecStr(const char* Str) :str(Str)
{
    long long int DecCh = 0;
    if (!((pch[0] >= '0' && pch[0] <= '9') || pch[0] == '-' || pch[0] == '+')) {
        char* sum;
        char p1[30] = "\n\rBad Symbol, pch[0]=";
        char p2[2];
        p2[0] = pch[0];
        p2[1] = '\0';
        int newlen = 34;
        sum = new char[newlen];
        sum[0] = '\0';
        strcat_s(sum, newlen, p1);
        strcat_s(sum, newlen, p2);
        strcat_s(sum, newlen, "\r\n");
        conc(sum);
        delete[]sum;

        if (pch) delete[] pch;
        len = 0;
        pch = new char[len + 1];
        pch[0] = '\0';
        return;
    }
    for (int i = 1; i < len; i++) {
        if (!(pch[i] >= '0' && pch[i] <= '9')) {
            char* sum;
            char p1[19] = "\r\nBad string, pch[";
            char p2[2];
            char p3[3] = "]=";
            p2[0] = pch[i];
            p2[1] = '\0';
            char* si = new char[4];
            _itoa_s(i, si, 4, 10);
            sum = new char[28];
            sum[0] = '\0';
            strcat_s(sum, 28, p1);
            strcat_s(sum, 28, si);
            strcat_s(sum, 28, p3);
            strcat_s(sum, 28, p2);
            strcat_s(sum, 28, "\r\n");
            conc(sum);
            delete[]si;
            delete[]sum;
            if (pch) delete[] pch;
            len = 0;
            pch = new char[len + 1];
            pch[0] = '\0';
            return;
        }
    }
    if (DecChB == true) {
        for (int i = 1; i < len; i++) {
            if ((pch[i] >= '0' && pch[i] <= '9') || (pch[0] == '-' && pch[0] == '+')) {
                DecCh = _atoi64(pch);
                if (DecCh > 2147483647) { DecCh = 2147483647; }
                else if (DecCh < -2147483647) { DecCh = -2147483647; }
                _i64toa(DecCh, pch, 10);
            }
        }
    }
    conc("DecStr::DecStr(const char* Str):str(Str)\r\n");
}
DecStr::DecStr(const DecStr& from) : str(from.Getstr()) { conc("DecStr::DecStr(const DecStr& from): str(from.Getstr())\r\n"); }
DecStr& DecStr::operator=(const DecStr& Ds)
{
    if (&Ds != this) {
        delete[] pch;
        len = strlen(Ds.pch);
        pch = new char[len + 1];
        strcpy_s(pch, len + 1, Ds.pch);
    }
    conc("DecStr& DecStr::operator=(const DecStr& Ds)\r\n");
    return *this;
}
DecStr operator +(const DecStr& pobj1, const DecStr& pobj2)
{
    long long int num1, num2;
    DecStr tmp(pobj1);
    num1 = _atoi64(tmp.Getstr());
    num2 = _atoi64(pobj2.Getstr());
    char* pTmpCh;
    long long int A = num1 + num2;

    if (tmp.len >= pobj2.len) { pTmpCh = new char[tmp.len + 2]; }
    else { pTmpCh = new char[pobj2.len + 2]; }

    _i64toa(A, pTmpCh, 10);
    if (tmp.pch) delete[] tmp.pch;
    tmp.pch = pTmpCh;
    cout << tmp.pch << endl;
    tmp.len = strlen(tmp.pch);
    char* sum;
    char* stmp = new char[20];
    char p1[7] = "len = ";
    char p2[63] = "DecStr operator + (const DecStr& pobj1, const DecStr& pobj2)\r\n";
    sum = new char[90];
    sum[0] = '\0';
    _itoa_s(tmp.Getlen(), stmp, 20, 10);
    strcat_s(sum, 90, p1);
    strcat_s(sum, 90, stmp);
    strcat_s(sum, 90, "\r\n");
    strcat_s(sum, 90, p2);
    conc(sum);
    delete[]stmp;
    delete[]sum;
    DecChB = false;
    return DecStr(pTmpCh);
}
DecStr operator -(const DecStr& pobj1, const DecStr& pobj2)
{
    long long int num1, num2;
    DecStr tmp(pobj1);
    num1 = _atoi64(tmp.Getstr());
    num2 = _atoi64(pobj2.Getstr());
    char* pTmpCh;
    long long int A = num1 - num2;

    if (tmp.len >= pobj2.len) { pTmpCh = new char[tmp.len + 2]; }
    else { pTmpCh = new char[pobj2.len + 2]; }

    _i64toa(A, pTmpCh, 10);
    if (tmp.pch) delete[] tmp.pch;
    tmp.pch = pTmpCh;
    cout << tmp.pch << endl;
    tmp.len = strlen(tmp.pch);
    char* sum;
    char* stmp = new char[20];
    char p1[7] = "len = ";
    char p2[63] = "DecStr operator - (const DecStr& pobj1, const DecStr& pobj2)\r\n";
    sum = new char[90];
    sum[0] = '\0';
    _itoa_s(tmp.len, stmp, 20, 10);
    strcat_s(sum, 90, p1);
    strcat_s(sum, 90, stmp);
    strcat_s(sum, 90, "\r\n");
    strcat_s(sum, 90, p2);
    conc(sum);
    delete[]stmp;
    delete[]sum;
    DecChB = false;
    return tmp;
}
int operator ==(const DecStr& pobj1, const DecStr& pobj2)
{
    int num1, num2;
    DecStr tmp(pobj1);
    num1 = atoi(tmp.Getstr());
    num2 = atoi(pobj2.Getstr());
    if (num1 == num2) { conc("[DecStr] Objects are equal\r\n"); }
    else { conc("[DecStr] Objects are not equal\r\n"); }
    conc("int operator == (const DecStr& pobj1, const DecStr& pobj2)\r\n");
    return 1;
}