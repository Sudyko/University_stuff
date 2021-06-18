#pragma once
#include "iostream"

extern bool DecChB;

extern char* concStr;
void conc(const char* stats);
void conc(char* stats);

class str {
protected:
    int len;
    char* pch;
public:
    str(int = 0);
    str(char);
    str(const str&);
    str(const char*);
    str& operator =(const str& S);
    str operator~();
    char* get(void) const { return pch; }
    ~str();
    void clear();
    void show(void);
    char* Getstr(void) const { return pch; }
    int Getlen(void) const { return len; }
    virtual const str* operator+(const char*);
};