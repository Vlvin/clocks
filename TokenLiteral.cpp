#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "headers/TokenLiteral.h"
#include "headers/LoxCallable.h"
#include "headers/PyUtils.h"

TokenLiteral::TokenLiteral() : d(), s(), lc(), type(TokenLiteral::NIL) {}


TokenLiteral::TokenLiteral(double d) : d(d), s(), lc(), type(TokenLiteral::NUMBER) {}


TokenLiteral::TokenLiteral(string s) : d(), s(s), lc(), type(TokenLiteral::STRING) {}


TokenLiteral::TokenLiteral(LoxCallable* lc) : d(), s(), lc(lc), type(TokenLiteral::CALLABLE) {}


TokenLiteral::TokenLiteral(bool b) : d(b), s(), lc(), type(TokenLiteral::BOOLEAN) {}

string TokenLiteral::toString() {
    string line;
    switch (type) {
        case TokenLiteral::NUMBER:
            line = to_string(d);
            if (PyUtils::endswith(line, ".000000"))
                line = PyUtils::strrange(line, 0, line.length() - 7);
            return line;
        case TokenLiteral::STRING:
            return s;
        case TokenLiteral::BOOLEAN:
            return ((d == 1) ? "true" : "false");
        case TokenLiteral::CALLABLE:
            return lc->toString();
    }
    return "nil";
}

double TokenLiteral::toNumber() {
    switch (type) {
        case TokenLiteral::NUMBER:
            return d;
        case TokenLiteral::BOOLEAN:
            return d;
    }
    return NULL;
}

LoxCallable* TokenLiteral::toCallable() {
    switch(type) {
        case TokenLiteral::CALLABLE:
            return lc;
    }
    return nullptr;
}

bool TokenLiteral::equals(TokenLiteral other) {
    return ((this->type == other.type) && (this->toString() == other.toString()));
}