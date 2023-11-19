#pragma once
#include <iostream>
#include <string>

#include "Token.h"

using namespace std;

class Clockwork {
public:    
    static bool hadError;
    static void error(int line, string message);
    static void error(Token token, string message);
private:
    static void report(int line, string where, string message);
};