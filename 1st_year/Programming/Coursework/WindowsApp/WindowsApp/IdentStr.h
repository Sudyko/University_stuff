#pragma once
#include "str.h"

class IdentStr :public str
{
public:
    IdentStr(int = 0);
    IdentStr(char);
    IdentStr(const char*);
    IdentStr(const str&);
    IdentStr(const IdentStr&);
    ~IdentStr();
    IdentStr& operator = (const IdentStr&);
    char& operator[](int);
    IdentStr operator ~();
    virtual const IdentStr* operator+(const char*);
    friend IdentStr operator +(const IdentStr&, const IdentStr&);
    friend IdentStr operator +(const IdentStr&, const char*);
    friend IdentStr operator +(const char*, const IdentStr&);
    friend bool operator ==(const IdentStr&, const IdentStr&);
};