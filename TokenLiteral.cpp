#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "headers/TokenLiteral.h"

TokenLiteral::TokenLiteral() : d(), s(), type(TokenLiteral::NIL) {}


TokenLiteral::TokenLiteral(double d) : d(d), s(), type(TokenLiteral::NUMBER) {}


TokenLiteral::TokenLiteral(string s) : d(), s(s), type(TokenLiteral::STRING) {}


TokenLiteral::TokenLiteral(bool b) : d(b), s(), type(TokenLiteral::BOOLEAN) {}

string TokenLiteral::toString() {
    switch (type) {
        case TokenLiteral::NIL:
            return "nil";
            break;
        case TokenLiteral::NUMBER:
            return to_string(d);
            break;
        case TokenLiteral::STRING:
            return s;
            break;
        case TokenLiteral::BOOLEAN:
            return ((d == 1) ? "true" : "false");
            break;
    }
}

double TokenLiteral::toNumber() {
    switch (type) {
        case TokenLiteral::NIL:
            return NULL;
            break;
        case TokenLiteral::NUMBER:
            return d;
            break;
        case TokenLiteral::STRING:
            return NULL;
            break;
        case TokenLiteral::BOOLEAN:
            return d;
            break;
    }

}