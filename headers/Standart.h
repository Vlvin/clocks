#pragma once

#include <sys/time.h>

using namespace std;

#include "LoxCallable.h"
#include "Clockswork.h"

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
    virtual int arity() { return -1; }
    virtual TokenLiteral call(Interpreter *interpreter, vector<TokenLiteral> arguments) {
        if (arguments.size() == 0)
            exit(0);
        exit(arguments[0].toNumber());
        return TokenLiteral();
    }
    virtual string toString() { return "<native fun exit>"; }
};

class LoxPrint : public LoxCallable {
public:
    virtual int arity() { return -253; } // admin option "any number of arguments"
    virtual TokenLiteral call(Interpreter *interpreter, vector<TokenLiteral> arguments) {
        string line = "";
        for (TokenLiteral argument: arguments) {
            line += argument.toString() + " ";
        }
        line = line.substr(0, line.length()-1);
        cout << line << endl;
        return TokenLiteral();
    }
    virtual string toString() { return "<native fun print>"; }
};