#include <iostream>
#include <string>

using namespace std;

#include "headers/Clockswork.h"
#include "headers/Token.h"

bool Clockwork::hadError = false;

void Clockwork::error(int line, string message) {
    report(line, "", message);
}

void Clockwork::error(Token token, string message) {
    if (token.type = T_EOF) {
        report(token.line, " at end ", message);
    } else {
        report(token.line, " at '" + token.lexeme + "' ", message);
    }
}

void Clockwork::report(int line, string where, string message) {
    cout << "[line " << line << "] Error " << where << ": " << message << endl; 
    hadError = true;
}