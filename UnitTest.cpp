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
#include "headers/VisitorStmt.h"
#include "headers/Stmt.h"
#include "headers/Expr.h"
#include "headers/Parser.h"
#include "headers/ASTPrinter.h"
#include "headers/PyUtils.h"

using namespace PyUtils;

bool test(string source, string expected) {
    Scanner scanner(source);
    vector<Token> tokens = scanner.scanTokens();

    Parser parser(tokens);
    vector<Stmt*> expression = parser.parse();
    string got = ASTPrinter().print(expression);

    if (Clockwork::hadError) return false;

    if(expected != got) {
        cout << "Test " << source << " Failed " 
             << expected << " expected but " 
             << got << " got\n";
        return false;
    }
    return true;
}

int main(int argc, char** argv) {
    bool ret = true;
    if (argc == 2) {
        fstream cases(argv[1]);
        char caso[256];
        while (cases.getline(caso, 256)) {
            string cppase = string(caso);
            try {
            string casinp = split(cppase,':')[0], casex = split(cppase,':')[1];
            if(!test(casinp, casex)) ret = false;
            } catch (...) {
                return false;
            }
        }
        if (ret) cout << "Test.OK\n";
    } else {
        cout << "Usage: test [path to cases]\n";
        return 1;
    }
    return 0;
    
}