#pragma once
#include <iostream>
#include <string>

using namespace std;

class Clockwork {
public:    
    static bool hadError;
    static void error(int line, string message);
private:
    static void report(int line, string where, string message);
};