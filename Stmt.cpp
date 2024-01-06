#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "headers/Token.h"
#include "headers/Stmt.h"
#include "headers/TokenLiteral.h"
#include "headers/VisitorStmt.h"

Expression::Expression(Expr* expression)
     : expression(expression) {}

string Expression::acceptstring(VisitorStmt *visitor) {   return visitor->visitExpressionstring(*this);
}

TokenLiteral Expression::acceptTokenLiteral(VisitorStmt *visitor) {   return visitor->visitExpressionTokenLiteral(*this);
}


Function::Function(Token name, vector<Token> params, vector<Stmt*> body)
     : name(name),params(params),body(body) {}

string Function::acceptstring(VisitorStmt *visitor) {   return visitor->visitFunctionstring(*this);
}

TokenLiteral Function::acceptTokenLiteral(VisitorStmt *visitor) {   return visitor->visitFunctionTokenLiteral(*this);
}


Class::Class(Token name, vector<Function*> methods)
     : name(name),methods(methods) {}

string Class::acceptstring(VisitorStmt *visitor) {   return visitor->visitClassstring(*this);
}

TokenLiteral Class::acceptTokenLiteral(VisitorStmt *visitor) {   return visitor->visitClassTokenLiteral(*this);
}


Return::Return(Token keyword, Expr* value)
     : keyword(keyword),value(value) {}

string Return::acceptstring(VisitorStmt *visitor) {   return visitor->visitReturnstring(*this);
}

TokenLiteral Return::acceptTokenLiteral(VisitorStmt *visitor) {   return visitor->visitReturnTokenLiteral(*this);
}


Print::Print(Expr* expression)
     : expression(expression) {}

string Print::acceptstring(VisitorStmt *visitor) {   return visitor->visitPrintstring(*this);
}

TokenLiteral Print::acceptTokenLiteral(VisitorStmt *visitor) {   return visitor->visitPrintTokenLiteral(*this);
}


Var::Var(Token name, Expr* initializer)
     : name(name),initializer(initializer) {}

string Var::acceptstring(VisitorStmt *visitor) {   return visitor->visitVarstring(*this);
}

TokenLiteral Var::acceptTokenLiteral(VisitorStmt *visitor) {   return visitor->visitVarTokenLiteral(*this);
}


Block::Block(vector<Stmt*> statements)
     : statements(statements) {}

string Block::acceptstring(VisitorStmt *visitor) {   return visitor->visitBlockstring(*this);
}

TokenLiteral Block::acceptTokenLiteral(VisitorStmt *visitor) {   return visitor->visitBlockTokenLiteral(*this);
}


If::If(Expr* condition, Stmt* thenBranch, Stmt* elseBranch)
     : condition(condition),thenBranch(thenBranch),elseBranch(elseBranch) {}

string If::acceptstring(VisitorStmt *visitor) {   return visitor->visitIfstring(*this);
}

TokenLiteral If::acceptTokenLiteral(VisitorStmt *visitor) {   return visitor->visitIfTokenLiteral(*this);
}


While::While(Expr* condition, Stmt* body)
     : condition(condition),body(body) {}

string While::acceptstring(VisitorStmt *visitor) {   return visitor->visitWhilestring(*this);
}

TokenLiteral While::acceptTokenLiteral(VisitorStmt *visitor) {   return visitor->visitWhileTokenLiteral(*this);
}


