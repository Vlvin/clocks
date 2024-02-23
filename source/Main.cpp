#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <signal.h> 


using namespace std;

#include "headers/Clockswork.h"
#include "headers/Token.h"
#include "headers/TokenType.h" 
#include "headers/TokenLiteral.h"
#include "headers/Environment.h"
#include "headers/Scanner.h"
#include "headers/VisitorExpr.h"
#include "headers/VisitorStmt.h"
#include "headers/Expr.h"
#include "headers/Stmt.h"
#include "headers/Parser.h" 
#include "headers/ASTPrinter.h"
#include "headers/Interpreter.h"
#include "headers/Resolver.h"

static Interpreter interpreter = Interpreter();
void run(string modulename, string source) {
    Scanner scanner(source);
    vector<Token> tokens = scanner.scanTokens(modulename);
    vector<Stmt*> statements = {};
    Parser parser(tokens);
    try {
        statements = parser.parse(modulename);
    } catch (ParseError error) {
        return;
    }


    if (Clockwork::hadError) return;

    Resolver resolver(&interpreter);
    resolver.resolve(modulename, statements);    
    if (Clockwork::hadError) return;
    interpreter.interpret(modulename, statements);
}

void runPromt() {
    string line;
    char cline[64];
    for(;;) {
        cout << "\nlox >> ";
        cin.getline(cline,64);
        line = string(cline);
        if (line == string("exit")) return;
        run("", line);
        Clockwork::hadError = false;
        Clockwork::hadRuntimeError = false;
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

    run(path, text);
    if (Clockwork::hadError) exit(65);
    if (Clockwork::hadRuntimeError) exit(70);
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