#include <iostream>

using namespace std;
#include "headers/Executioner.h"

static Executioner executioner = Executioner();
int main(int argc, char** argv) {
    if (argc < 2) {
        executioner.runPromt();
    } else if (argc == 2) {
        executioner.runFile(argv[1]);
    } else {
        cout << "Usage: Lox [path to script.lox]\n      Lox // to start promt\n";
        return 1;
    }
    return 0;
}