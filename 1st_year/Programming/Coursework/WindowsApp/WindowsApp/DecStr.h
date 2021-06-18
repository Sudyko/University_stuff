#pragma once
#include "str.h"
#include "iostream"

class DecStr :public str
{
public:
    DecStr(int = 0);
    DecStr(const char*);
    DecStr(const DecStr&);
    ~DecStr();
    DecStr& operator=(const DecStr&);
    bool canchar(void) {
        bool i = true;
        if (Getlen() >= 1) { conc("bool canchar(void)\r\n"); conc("Yes.\r\n"); return i; }
        else { i = false; conc("bool canchar(void)\r\n"); conc("No.\r\n"); return i; }
    }
    friend DecStr operator +(const DecStr&, const DecStr&);
    friend DecStr operator -(const DecStr&, const DecStr&);
    friend int operator ==(const DecStr&, const DecStr&);
};