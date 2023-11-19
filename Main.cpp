#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

#include "headers/Clockswork.h"
#include "headers/Token.h"
#include "headers/TokenType.h"
#include "headers/TokenLiteral.h"
#include "headers/Scanner.h"
#include "headers/VisitorExpr.h"
#include "headers/Expr.h"
#include "headers/Parser.h"
#include "headers/ASTPrinter.h"

void run(string source) {
    cout << "\nScanning\n";
    Scanner scanner(source);
    vector<Token> tokens = scanner.scanTokens();
    cout << "Parsing\n";

    Parser parser(tokens);
    Expr* expression = parser.parse();
    cout << Clockwork::hadError;

    if (Clockwork::hadError) return;
    cout << "Printing\n";

    cout << ASTPrinter().print(expression) << endl;
}

void runPromt() {
    string line;
    char cline[64];
    for(;;) {
        cout << "\nlox >> ";
        cin.getline(cline,64);
        if (line == string("exit")) return;
        line = string(cline);
        run(line);
        Clockwork::hadError = false;
    }
}

void runFile(string path) {
    fstream file(path, ios::in);
    
    if (!file.is_open()) {
        cout << "LoxError: no such file\n";
        return;
    }

    string text( (std::istreambuf_iterator<char>(file) ),
                       (std::istreambuf_iterator<char>()    ) );;

    run(text);
    if (Clockwork::hadError) exit(65);
}


int main(int argc, char** argv) {
    if (argc < 2) {
        runPromt();
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        cout << "Usage: Lox [path to script.lox]\n      Lox // to start promt\n";
        return 1;
    }
    return 0;
}