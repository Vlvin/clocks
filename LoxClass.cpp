#include "headers/LoxClass.h"
#include "headers/LoxInstance.h"
#include "headers/LoxFunction.h"

#include <vector>

LoxClass::LoxClass(string name, map<string, LoxFunction*> statics, map<string, LoxFunction*> methods) : name(name), statics(statics), methods(methods) {}

int LoxClass::arity() {
    LoxFunction *constructor = findMethod("constructor");
    if (constructor == nullptr) return 0;
    return constructor->arity();
}

LoxFunction* LoxClass::findStaticMethod(string name) {
    if (statics.count(name) > 0) {
        return statics.find(name)->second;
    }
    return nullptr;
}

LoxFunction* LoxClass::findMethod(string name) {
    if (methods.count(name) > 0) {
        return methods.find(name)->second;
    }
    return findStaticMethod(name);
}

TokenLiteral LoxClass::call(Interpreter *interpreter, vector<TokenLiteral> arguments) {
    LoxInstance *instance = new LoxInstance(this);
    LoxFunction *constructor = findMethod("constructor");
    if (constructor != nullptr) {
        ((constructor->bind(instance)).toCallable())->call(interpreter, arguments);
    }
    return TokenLiteral(instance);
}

string LoxClass::toString() {
    return "<class " + name + ">";
}