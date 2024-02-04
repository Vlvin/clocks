#pragma once

#include <sys/time.h>
#include <vector>
#include <map>

using namespace std;

#include "LoxCallable.h"
#include "LoxClass.h"
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

class InstanceOf : public LoxCallable {
public:
    virtual int arity() { return 1; } // admin option "any number of arguments"
    virtual TokenLiteral call(Interpreter *interpreter, vector<TokenLiteral> arguments) {
        LoxInstance* target = arguments[0].toInstance();
        if (target != nullptr)
            return TokenLiteral(((target->LClass)->name));
        return TokenLiteral();
    }
    virtual string toString() { return "<native fun instanceOf>"; }
};

class SuperName : public LoxCallable {
public:
    virtual int arity() { return 1; } // admin option "any number of arguments"
    virtual TokenLiteral call(Interpreter *interpreter, vector<TokenLiteral> arguments) {
        LoxClass* targetClass = (LoxClass*)(arguments[0].toCallable());
        if (targetClass != nullptr)
            if (targetClass->superclass != nullptr)
                return TokenLiteral(targetClass->superclass->name);
        delete targetClass;
        LoxInstance* targetInstance = (arguments[0].toInstance());
        if (targetInstance != nullptr)
            if (targetInstance->LClass->superclass != nullptr)
                return TokenLiteral(targetInstance->LClass->superclass->name);
        return TokenLiteral();
    }
    virtual string toString() { return "<native fun superName>"; }
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

// built-in instance Math
// sincos funs
class LoxSin : public LoxCallable {
    virtual int arity() {
        return 1;
    } 
    virtual TokenLiteral call(Interpreter *interpreter, vector<TokenLiteral> arguments) {
        return TokenLiteral(sin(arguments[0].toNumber()));
    }
    virtual string toString() {
        return "<math method radSin>";
    }
};

class LoxCos : public LoxCallable {
    virtual int arity() {
        return 1;
    } 
    virtual TokenLiteral call(Interpreter *interpreter, vector<TokenLiteral> arguments) {
        return TokenLiteral(cos(arguments[0].toNumber()));
    }
    virtual string toString() {
        return "<math method radCos>";
    }
};

class LoxSovSin : public LoxCallable {
    virtual int arity() {
        return 1;
    } 
    virtual TokenLiteral call(Interpreter *interpreter, vector<TokenLiteral> arguments) {
        return TokenLiteral(sin(arguments[0].toNumber()/180*M_PI));
    }
    virtual string toString() {
        return "<math method sin>";
    }
};

class LoxSovCos : public LoxCallable {
    virtual int arity() {
        return 1;
    } 
    virtual TokenLiteral call(Interpreter *interpreter, vector<TokenLiteral> arguments) {
        return TokenLiteral(cos(arguments[0].toNumber()/180*M_PI));
    }
    virtual string toString() {
        return "<math method cos>";
    }
};

class LoxtoRad : public LoxCallable {
    virtual int arity() {
        return 1;
    } 
    virtual TokenLiteral call(Interpreter *interpreter, vector<TokenLiteral> arguments) {
        return TokenLiteral(arguments[0].toNumber()/180*M_PI);
    }
    virtual string toString() {
        return "<math method degToRad>";
    }
};

class LoxtoDeg : public LoxCallable {
    virtual int arity() {
        return 1;
    } 
    virtual TokenLiteral call(Interpreter *interpreter, vector<TokenLiteral> arguments) {
        return TokenLiteral(arguments[0].toNumber()/M_PI*180);
    }
    virtual string toString() {
        return "<math method radToDeg>";
    }
};

class LoxMath : public LoxInstance {
    map<string, TokenLiteral> fields = {
        {"PI", TokenLiteral(3.141593)},
        {"E",  TokenLiteral(2.718281)},
        {"radSin", TokenLiteral(new LoxSin())},
        {"radCos", TokenLiteral(new LoxCos())},
        {"sin", TokenLiteral(new LoxSovSin())},
        {"cos", TokenLiteral(new LoxSovCos())},
        {"radToDeg", TokenLiteral(new LoxtoDeg())},
        {"degToRad", TokenLiteral(new LoxtoRad())}

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
        return TokenLiteral();
    }
    virtual TokenLiteral set(Token name, TokenLiteral value) override {
        Clockwork::error(name, "Can't set fields of native class.");
        return TokenLiteral();
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