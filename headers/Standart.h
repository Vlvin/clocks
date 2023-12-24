#pragma once

#include <sys/time.h>

using namespace std;

#include "LoxCallable.h"

class LoxClock : public LoxCallable {
public:
    virtual int arity() { return 0; }
    virtual TokenLiteral call(Interpreter *interpreter, vector<TokenLiteral> arguments) {
        timeval t;
        gettimeofday(&t, nullptr);
        double time = t.tv_sec % 60 + (double)t.tv_usec / 1000000;
        return TokenLiteral(time);
    }
    virtual string toString() { return "<native fun clock>"; }
};