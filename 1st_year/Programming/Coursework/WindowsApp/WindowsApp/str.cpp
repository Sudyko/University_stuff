#include "iostream"
#include "str.h"

using namespace std;

bool DecChB = true;
char* concStr = new char[256]();
void conc(const char* stats)
{
    int len = -1;
    while (concStr[++len]);
    int appender = -1;
    while (stats[++appender]);
    char* tmp = new char[len + 1];
    strcpy_s(tmp, len + 1, concStr);
    concStr = new char[len + appender + 1];
    if (len > 0) {
        strcpy_s(concStr, len + 1, tmp);
        strcat_s(concStr, len + appender + 1, stats);
    }
    else {
        strcpy_s(concStr, appender + 1, stats);
    }
}
void conc(char* stats)
{
    int len = -1;
    while (concStr[++len]);
    int appender = -1;
    while (stats[++appender]);
    char* tmp = new char[len + 1];
    strcpy_s(tmp, len + 1, concStr);
    concStr = new char[len + appender + 1];
    if (len > 0) {
        strcpy_s(concStr, len + 1, tmp);
        strcat_s(concStr, len + appender + 1, stats);
    }
    else {
        strcpy_s(concStr, appender + 1, stats);
    }
}
str::str(int val) : len(val), pch(new char[len + 1])
{
    if (val == 0) pch[0] = '\0';
    conc("str :: str(int val)\r\n");
}
str::str(char ch) : len(1), pch(new char[len + 1])
{
    pch[0] = ch;
    pch[1] = '\0';
    conc("str :: str(char ch)\r\n");
}
str::~str()
{
    if (pch) delete[] pch;
    conc("str :: ~str\r\n");
}
str::str(const char* s)
{
    len = 0;
    int i = 0;
    while (s[i++]) len++;
    len = --i;
    pch = new char[len + 1];
    strcpy_s(pch, len + 1, s);
    conc("\r\nstr :: str (const char* s)\r\n");
}

str::str(const str& from) :
    len(from.Getlen()),
    pch(new char[from.Getlen() + 1])
{
    strcpy_s(pch, len + 1, from.pch);
    conc("str::str(const str & from)\r\n");
}

str& str::operator=(const str& S)
{
    if (&S != this) {
        len = S.Getlen();
        pch = new char[len + 1];
        strcpy_s(pch, len + 1, S.pch);
    }
    conc("str to str\r\n");
    return *this;
}
void str::show(void)
{
    char* sum;
    char p1[8] = "pch = ";
    char p2[8] = "len = ";
    char* slen = new char[4];
    int newlen = 21 + strlen(pch);
    sum = new char[newlen];
    sum[0] = '\0';
    _itoa_s(len, slen, 4, 10);
    strcat_s(sum, newlen, p1);
    strcat_s(sum, newlen, pch);
    strcat_s(sum, newlen, "\r\n");
    strcat_s(sum, newlen, p2);
    strcat_s(sum, newlen, slen);
    strcat_s(sum, newlen, "\r\n");
    conc(sum);
    delete[]slen;
    delete[]sum;
}
// virtual
const str* str::operator+(const char* ch) {
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
    cout << "const str* str::operator+(const char* ch) " << n << endl;
    str* result = new str(n);
    return result;
};
str str::operator~() {
    char* reverse = new char[len + 1];
    for (int i = len - 1; i >= 0; i--) reverse[i] = pch[len - i - 1];
    reverse[len] = '\0';
    str result = str(reverse);
    char* sum;
    char p1[22] = "str str::operator~() ";
    int newlen = 22 + len + 12;
    sum = new char[newlen];
    sum[0] = '\0';
    strcat_s(sum, newlen, p1);
    strcat_s(sum, newlen, "\r\n");
    strcat_s(sum, newlen, result.get());
    strcat_s(sum, newlen, "\r\n");
    conc(sum);
    delete[]sum;
    return result;
};
void str::clear()
{
    delete pch;
    len = 0;
    pch = new char[1];
    pch[0] = 0;
    conc("str::clear()\r\n");
}