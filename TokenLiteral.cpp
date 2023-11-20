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
        case TokenLiteral::NUMBER:
            return to_string(d);
        case TokenLiteral::STRING:
            return s;
        case TokenLiteral::BOOLEAN:
            return ((d == 1) ? "true" : "false");
    }
    return "nil";
}

double TokenLiteral::toNumber() {
    switch (type) {
        case TokenLiteral::NUMBER:
            return d;
        case TokenLiteral::STRING:
            return NULL;
        case TokenLiteral::BOOLEAN:
            return d;
    }
    return NULL;

}

bool TokenLiteral::equals(TokenLiteral other) {
    return ((this->type == other.type) && (this->toString() == other.toString()));
}