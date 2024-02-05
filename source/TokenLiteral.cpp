#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "headers/TokenLiteral.h"
#include "headers/LoxCallable.h"
#include "headers/LoxInstance.h"
#include "headers/PyUtils.h"

TokenLiteral::TokenLiteral() : d(), s(), lc(), li(), type(TokenLiteral::NIL), isReturn(false), isConst(false) {}

TokenLiteral::TokenLiteral(double d) : d(d), s(), lc(), li(), type(TokenLiteral::NUMBER), isReturn(false), isConst(false)  {}

TokenLiteral::TokenLiteral(string s) : d(), s(s), lc(), li(), type(TokenLiteral::STRING), isReturn(false), isConst(false)  {}

TokenLiteral::TokenLiteral(LoxCallable* lc) : d(), s(), lc(lc), li(), type(TokenLiteral::CALLABLE), isReturn(false), isConst(false)  {}

TokenLiteral::TokenLiteral(LoxInstance* li) : d(), s(), lc(), li(li), type(TokenLiteral::INSTANCE), isReturn(false), isConst(false)  {}

TokenLiteral::TokenLiteral(bool b) : d(b), s(), lc(), li(), type(TokenLiteral::BOOLEAN), isReturn(false), isConst(false)  {}


TokenLiteral::TokenLiteral(TokenLiteral tl, vector<bool> flags) : type(tl.type) {
    isConst = false, isReturn = false;
    switch (flags.size()) {
        case 2:
            isConst = flags[1];
        case 1:
            isReturn = flags[0];
    }
    switch (tl.type) {
        case NUMBER:
        case BOOLEAN:
            d = tl.d;
            break;
        case STRING:
            s = tl.s;
            break;
        case CALLABLE:
            lc = tl.lc;
        case INSTANCE:
            li = tl.li;
            break;
        case NIL:
            break;
    }
}

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
        case TokenLiteral::INSTANCE:
            return li->toString();
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

LoxInstance* TokenLiteral::toInstance() {
    switch(type) {
        case TokenLiteral::INSTANCE:
            return li;
    }
    return nullptr;
}

bool TokenLiteral::equals(TokenLiteral other) {
    return ((this->type == other.type) && (this->toString() == other.toString()));
}