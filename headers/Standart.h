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

class LoxExit : public LoxCallable {
public:
    virtual int arity() { return 1; }
    virtual TokenLiteral call(Interpreter *interpreter, vector<TokenLiteral> arguments) {
        exit(arguments[0].toNumber());
        return TokenLiteral();
    }
    virtual string toString() { return "<native fun exit>"; }
};

class LoxPrint : public LoxCallable {
public:
    virtual int arity() { return 1; }
    virtual TokenLiteral call(Interpreter *interpreter, vector<TokenLiteral> arguments) {
        cout << (arguments[0].toString()) << endl;
        return TokenLiteral();
    }
    virtual string toString() { return "<native fun print>"; }
};