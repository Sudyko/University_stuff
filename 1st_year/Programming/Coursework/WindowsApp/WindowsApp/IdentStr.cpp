#include "iostream"
#include "IdentStr.h"

using namespace std;

IdentStr::IdentStr(int val) : str(val)
{
    char* sum;
    char p1[45] = "IdentStr :: IdentStr(int val):str(val), val=";
    char* sval = new char[4];
    _itoa_s(val, sval, 4, 10);
    sum = new char[52];
    sum[0] = '\0';
    strcat_s(sum, 52, p1);
    strcat_s(sum, 52, sval);
    strcat_s(sum, 52, "\r\n");
    conc(sum);
    delete[]sum;
    delete[]sval;
}
IdentStr::IdentStr(char ch) : str(ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_')
        conc("IdentStr :: IdentStr(char ch):str(val)\r\n");
    else {
        if (pch) delete[] pch;
        len = 0;
        pch = new char[len + 1];
        pch[0] = '\0';
        conc("Bad symbol!\r\n");
    }
}
IdentStr::IdentStr(const str& from)
{
    len = from.Getlen();
    if ((from.Getstr()[0] >= 'a' && from.Getstr()[0] <= 'z') ||
        (from.Getstr()[0] >= 'A' && from.Getstr()[0] <= 'Z') || from.Getstr()[0] == '_') {
        for (int i = 1; i < from.Getlen(); i++) {
            if ((from.Getstr()[i] >= 'a' && from.Getstr()[i] <= 'z') ||
                (from.Getstr()[i] >= 'A' && from.Getstr()[i] <= 'Z') || from.Getstr()[i] == '_' || (from.Getstr()[i] >= '0' && from.Getstr()[i] <= '9'))
                cout << from.Getstr()[i];
            else {
                if (pch) delete[] pch;
                len = 0;
                pch = new char[len + 1];
                pch[0] = '\0';
                conc("Bad symbol!\r\n");
                break;
            }
        }
        pch = new char[len + 1];
        for (int i = 0; i < len; i++) {
            pch[i] = from.Getstr()[i];
        }
        pch[len] = '\0';
        conc("IdentStr :: IdentStr(const str& from)\r\n");
    }

    else {
        if (pch) delete[] pch;
        len = 0;
        pch = new char[len + 1];
        pch[0] = '\0';
        conc("Bad symbol!\r\n");
    }
}
IdentStr::IdentStr(const char* ch) : str(ch)
{
    int chL = -1;
    while (ch[++chL]);

    if ((ch[0] >= 'a' && ch[0] <= 'z') ||
        (ch[0] >= 'A' && ch[0] <= 'Z') || ch[0] == '_')
    {
        for (int i = 1; i < chL; i++) {
            if ((ch[i] >= 'a' && ch[i] <= 'z') ||
                (ch[i] >= 'A' && ch[i] <= 'Z') || ch[i] == '_' || (ch[i] >= '0' && ch[i] <= '9'));
            else {
                if (pch) delete[] pch;
                len = 0;
                pch = new char[len + 1];
                pch[0] = '\0';
                conc("Bad symbol!\r\n");
                break;
            }
        }
        pch = new char[len + 1];
        for (int i = 0; i < len; i++) {
            pch[i] = ch[i];
        }
        pch[len] = '\0';
        conc("IdentStr :: IdentStr(const char* ch):str(val)\r\n");
    }

    else {
        if (pch) delete[] pch;
        len = 0;
        pch = new char[len + 1];
        pch[0] = '\0';
        conc("Bad symbol!\r\n");
    }
}
IdentStr::IdentStr(const IdentStr& from) : str(from) { conc("IdentStr :: IdentStr(const IdentStr& from): str(from)\r\n"); }
IdentStr::~IdentStr() { conc("\r\nIdentStr :: ~IdentStr\r\n"); }
IdentStr& IdentStr::operator=(const IdentStr& S)
{
    if (&S != this) {
        delete[] pch;
        len = strlen(S.pch);
        pch = new char[len + 1];
        strcpy_s(pch, len + 1, S.pch);
    }
    conc("IdentStr& IdentStr::operator=(const IdentStr& S)\r\n");
    return *this;
}
char& IdentStr::operator[](int index)
{
    char* sum;
    if (index >= 0 && index < len) {
        char p1[40] = "char& IdentStr::operator[](int index)\r\n";
        char p2[2];
        p2[0] = pch[index];
        p2[1] = '\0';
        sum = new char[52];
        sum[0] = '\0';
        strcat_s(sum, 52, p1);
        strcat_s(sum, 52, p2);
        strcat_s(sum, 52, "\r\n");
        conc(sum);
        delete[]sum;
        return pch[index];
    }
    return pch[0];
}
IdentStr IdentStr::operator ~ ()
{
    int i, j;
    char tmp;
    for (i = 0, j = len - 1; i < len / 2; i++, j--) {
        tmp = pch[i];
        pch[i] = pch[j];
        pch[j] = tmp;
    }
    conc("IdentStr IdentStr::operator ~ ()\r\n");
    return *this;
}
IdentStr operator +(const IdentStr& pobj1, const IdentStr& pobj2)
{
    IdentStr tmp1(pobj2);
    IdentStr tmp(pobj1.Getlen() + tmp1.Getlen());
    int     i = 0, j = 0;
    while (tmp.pch[i++] = pobj1.pch[j++]);
    --i;
    j = 0;
    while (tmp.pch[i++] = tmp1.pch[j++]);
    conc("IdentStr operator + (const IdentStr& pobj1, const cahr* pobj2)\r\n");
    return tmp;
}
IdentStr operator +(const IdentStr& pobj1, const char* pobj2)
{
    IdentStr tmp1(pobj2);
    IdentStr tmp(pobj1.Getlen() + tmp1.Getlen());
    int i = 0, j = 0;
    while (tmp.pch[i++] = pobj1.pch[j++]);
    --i;
    j = 0;
    while (tmp.pch[i++] = tmp1.pch[j++]);
    conc("IdentStr operator + (const IdentStr& pobj1, const char* pobj2)\r\n");
    return tmp;
}
IdentStr operator +(const char* pobj1, const IdentStr& pobj2)
{
    IdentStr tmp1(pobj1);
    if (tmp1.len == 0) {
        IdentStr tmp(pobj2.Getlen());
        int i = 0, j = 0;
        while (tmp.pch[i++] = pobj2.pch[j++]);
        conc("IdentStr operator + (const char* pobj1, const IdentStr& pobj2)\r\n");
        return tmp;
    }
    else {
        IdentStr tmp((int)strlen(pobj1) + pobj2.Getlen());
        int i = 0, j = 0;
        while (tmp.pch[i++] = *pobj1++)
            --i;
        while (tmp.pch[i++] = pobj2.pch[j++]);
        conc("IdentStr operator + (const char* pobj1, const IdentStr& pobj2)\r\n");
        return tmp;
    }
}
bool operator ==(const IdentStr& pobj1, const IdentStr& pobj2)
{
    char tmp = pobj1.Getlen();
    char tmp1 = pobj2.Getlen();
    bool z(true);
    if (tmp > tmp1);
    else tmp = tmp1;
    for (int i = 0; i <= tmp; i++) {
        if (pobj1.pch[i] != pobj2.pch[i]) { conc("[IdentStr] Objects are not equal\r\n"); z = false; break; }
    }
    if (z) { conc("[IdentStr] Objects are equal\r\n"); }
    conc("IdentStr operator == (const IdentStr& pobj1, const IdentStr& pobj2)\r\n");
    return z;
}
// virtual
const IdentStr* IdentStr::operator+(const char* ch) {
    int leng = 0;
    while (ch[leng++]);
    char* s = new char[leng];
    for (int i = 0; i < leng; i++) s[i] = ch[i];
    char* n = new char[len + leng + 1];
    int i = -1;
    while (pch[++i]) n[i] = pch[i];
    i = -1;
    while (s[++i]) n[len + i] = s[i];
    n[len + i] = '\0';
    cout << "Result is IdentStr " << n << endl;
    IdentStr* result = new IdentStr(n);
    return result;
};