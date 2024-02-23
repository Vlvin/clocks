#include <iostream>
#include <string>

using namespace std;

#include "headers/Clockswork.h"
#include "headers/Token.h"

bool Clockwork::hadError = false;
bool Clockwork::hadRuntimeError = false;

void Clockwork::error(int line, string message) {
    report(line, "", message);
}

void Clockwork::error(Token token, string message) {
    if (token.type == T_EOF) {
        report(token.line, " at end ", message);
    } else {
        report(token.line, " at '" + token.lexeme + "' ", message);
    }
}

void Clockwork::error(string modulename, int line, string message) {
        report(modulename, line, "", message);
}

void Clockwork::error(string modulename, Token token, string message) {
    if (token.type == T_EOF) {
        report(modulename, token.line, " at end ", message);
    } else {
        report(modulename, token.line, " at '" + token.lexeme + "' ", message);
    }
}

void Clockwork::runtimeError(RuntimeException error) {
    cout << "In [" << error.modulename << "]: [line " << error.token.line << "]" << " " << error.message << endl;
    hadRuntimeError = true;
}

void Clockwork::report(int line, string where, string message) {
    cout << "[line " << line << "] Error" << where << ": " << message << endl; 
    hadError = true;
}

void Clockwork::report(string modulename, int line, string where, string message) {
    cout << "In [" << modulename << "]: [line " << line << "] Error" << where << ": " << message << endl; 
    hadError = true;
}