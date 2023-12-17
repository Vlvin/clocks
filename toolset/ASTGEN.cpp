#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "PyUtils.h"

using namespace std;
using namespace PyUtils;

vector<string> exprtypes = {
    "Binary   : Expr* left, Token oper, Expr* right",
    "Call     : Expr* callee, Token paren, vector<Expr*> arguments",
    "Grouping : Expr* expr",
    "Literal  : TokenLiteral value",
    "Logical  : Expr* left, Token oper, Expr* right",
    "Unary    : Token oper, Expr* right",
    "Variable : Token name",
    "Assign   : Token name, Expr* value"
};


vector<string> stmtypes = {
    "Expression : Expr* expression",
    "Function   : Token name, vector<Token> params, vector<Stmt*> body",
    "Print      : Expr* expression",
    "Var        : Token name, Expr* initializer",
    "Block      : vector<Stmt*> statements",
    "If         : Expr* condition, Stmt* thenBranch, Stmt* elseBranch",
    "While      : Expr* condition, Stmt* body"
};

vector<string> retutypes = {
    "string",
    "TokenLiteral"
};

void defAST(string dirname, string baseName, vector<string> types, vector<string> retypes) {
    string path = dirname + '/';
    string wPath = path + trim(baseName) + ".cpp";
    string hPath = path + "headers/" + trim(baseName) + ".h";

    fstream wout(wPath, ios::out | ios::trunc), hout(hPath, ios::out | ios::trunc);


    // HEADER CONSTRUCT
    hout << "#pragma once\n"
         << "#include <iostream>\n"
         << "#include <string>\n"
         // global include in header file here
         << "#include <vector>\n\n"

         << "using namespace std;\n\n"

         << "#include \"TokenLiteral.h\"\n"
         << "#include \"Token.h\"\n"
         << "#include \"TokenType.h\"\n"
         << "#include \"Expr.h\"\n"
         << "#include \"PyUtils.h\"\n\n"
         << "#include \"Visitor" << trim(baseName) << ".h\"\n\n"
         // place local include in header here

         << "using namespace PyUtils;\n\n";

            hout << "class Visitor" << trim(baseName) << ";\n";

    hout << '\n';


    hout << "class " << baseName << " {\n"; // start of main class definition

    hout << "public:\n";
    // inner abstract funs
    for (string retype: retypes) {
            hout << "   virtual " << retype << " accept" <<  trim(retype) << "(Visitor" << trim(baseName) << " *visitor) = 0;\n";
    }
    hout << "};\n\n"; // end of main class definition


    // Son classes definition
    for (string type: types) {
        string sonT = trim(split(type,':')[0]);
        string args = trim(split(type,':')[1]);

        hout << "class " << sonT << " : public " << baseName << " {\n";  // start of son class definition


        hout << "public:\n";

        // members
        for (string arg: split(args,',')) {
            hout << "   " << trim(arg) << ";\n";
        }


        hout << "   " << sonT << "(" << args << ");\n\n";

        for (string retype: retypes) {
            hout << "   " << retype << " accept" << trim(retype) << "(Visitor" << trim(baseName) << " *visitor);\n";
        }

        hout << "\n};\n\n";
    }

    // MAIN CONSTRUCT
    wout << "#include <iostream>\n"
         << "#include <string>\n"
         << "#include <vector>\n\n"

         << "using namespace std;\n\n"
         
         << "#include \"headers/Token.h\"\n"
         << "#include \"headers/" << trim(baseName) << ".h\"\n"
         << "#include \"headers/TokenLiteral.h\"\n"
         << "#include \"headers/Visitor" << baseName << ".h\"\n\n";

    for (string type: types) {
        string sonT = trim(split(type,':')[0]);
        string args = trim(split(type,':')[1]);
        wout << sonT << "::" << sonT << "(" << args << ")\n     : ";

        // Constructor
        for (int i = 0; i < split(args,',').size(); i++) {
            string arg = split(args,',')[i];
            string argN = split(arg,' ')[1];
            string argT = split(arg,' ')[0];
            wout << argN << "(" << argN << ")" << ((i >= (split(args,',').size()-1)) ? " {}\n\n" : ",");
        }


        // All types accept
        for (string retype: retypes) {
            wout << retype << " " << sonT << "::accept" << trim(retype) << "(Visitor" << trim(baseName) << " *visitor) {"
                 << "   return visitor->visit" << sonT << trim(retype) << "(*this);\n}\n\n";
        }
        wout << '\n';
    }

    // QUIT CONSTRUCT
    hout.close(); wout.close();
}

void defV(string dirname, string baseName, vector<string> types, vector<string> retypes) {
    string path = dirname + '/';
    string hPath = path + "headers/" + "Visitor" + trim(baseName) + ".h";

    fstream hout(hPath, ios::out | ios::trunc);

    // HEADER CONSTRUCT
    hout << "#pragma once\n"
         << "#include <iostream>\n"
         << "#include <string>\n"
         // global include in header file here
         << "#include <vector>\n\n"

         << "using namespace std;\n\n"

         << "#include \"TokenLiteral.h\"\n"
         << "#include \"Token.h\"\n"
         << "#include \"TokenType.h\"\n"
         << "#include \"" << trim(baseName) << ".h\"\n\n";
         // place local include in header here

        for (string type: types) {
            hout << "class " << trim(split(type,':')[0]) << ";\n";
        }

    hout << '\n';


    hout << "class Visitor" << trim(baseName) << " {\n"; // start of main class definition

    hout << "public:\n";
    // inner abstract funs
    for (string retype: retypes) {
        for (string type: types) {
                hout << "   virtual " << retype << " visit" << trim(split(type,':')[0]) <<  trim(retype) << "(" << trim(split(type,':')[0]) << " &" << lcase(trim(baseName)) << ") = 0;\n";
        }
        hout << '\n';
    }
    hout << "};\n\n"; // end of main class definition

    // QUIT CONSTRUCT
    hout.close();
}


int main() {
    defAST(".","Expr", exprtypes, retutypes);
    defV(".","Expr", exprtypes, retutypes);

    defAST(".","Stmt", stmtypes, retutypes);
    defV(".","Stmt", stmtypes, retutypes);
}

/*
schematic
int main() {
    defAST("Expr", "", exprtypes, retutypes)
    defAST("Stmt", "", stmtypes, retutypes)

    defVisitor()
    defCVisitor()
}
*/