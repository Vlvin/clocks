#pragma once

#include <sys/time.h>
#include <vector>
#include <map>

using namespace std;

#include "LoxCallable.h"
#include "LoxCallable.h"
#include "LoxInstance.h"
#include "Stmt.h"
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

class LoxType : public LoxCallable {
public:
    virtual int arity() { return 1; } // admin option "any number of arguments"
    virtual TokenLiteral call(Interpreter *interpreter, vector<TokenLiteral> arguments) {
        string line = "";
        for (TokenLiteral argument: arguments) {
            switch (argument.type) {
                case TokenLiteral::STRING:
                    line += "STRING";
                    break;
                case TokenLiteral::NIL:
                    line += "NIL";
                    break;
                case TokenLiteral::NUMBER:
                    line += "NUMBER";
                    break;
                case TokenLiteral::INSTANCE:
                    line += "INSTANCE";
                    break;
                case TokenLiteral::CALLABLE:
                    line += "CALLABLE";
                    break;
                case TokenLiteral::BOOLEAN:
                    line += "BOOLEAN";
                    break;
            }
        };
        return TokenLiteral(line);
    }
    virtual string toString() { return "<native fun type>"; }
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

// built-in instance
class LoxMath : public LoxInstance {
    map<string, TokenLiteral> fields = {
        {"PI", TokenLiteral(3.141593)},
        {"E",  TokenLiteral(2.718281)}
    };
public:
    LoxMath() : LoxInstance(nullptr) {}
    virtual string toString() {
        return "<native class Math";
    }
    virtual TokenLiteral get(Token name) override {
        if (fields.count(name.lexeme) > 0)
            return fields.find(name.lexeme)->second;
        Clockwork::error(name, "Can't find field.");
    }
    virtual TokenLiteral set(Token name, TokenLiteral value) override {
        Clockwork::error(name, "Can't set fields of native class.");
        return "";
    }
};

/** DO NO USE
 * Meme map for native classes
 * System -|
 *         - in -
 *         - out -|
 *                - print
 *                - println 
 *
*/