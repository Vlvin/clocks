#pragma once
#include <iostream>
#include <string>

#include "Token.h"

using namespace std;
class RuntimeException : public exception {
public:
    Token token;
    string message;
    RuntimeException(Token token, string message) 
        : token(token), message(message) {}

};


class Clockwork {
public:    
    static bool hadError;
    static bool hadRuntimeError;
    static void error(int line, string message);
    static void error(Token token, string message);
    static void runtimeError(RuntimeException error);
private:
    static void report(int line, string where, string message);

    
};