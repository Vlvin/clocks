#include <iostream>
#include <string>

using namespace std;

#include "headers/Clockswork.h"

bool Clockwork::hadError = false;

void Clockwork::error(int line, string message) {
    report(line, "", message);
}

void Clockwork::report(int line, string where, string message) {
    cout << "[line " << line << "] Error " << where << ": " << message << endl; 
}