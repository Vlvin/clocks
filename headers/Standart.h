#pragma once

#include <chrono>
#include <ctime>

using namespace std;

#include "LoxCallable.h"



class LoxClock : public LoxCallable {
public:
    virtual int arity() { return 0; }
    virtual TokenLiteral call(Interpreter *interpreter, vector<TokenLiteral> arguments) {
        time_t time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        return TokenLiteral(double(time));
    }
    virtual string toString() { return "<native fun clock>"; }
};