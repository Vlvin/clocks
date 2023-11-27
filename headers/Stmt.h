#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "TokenLiteral.h"
#include "Token.h"
#include "TokenType.h"
#include "Expr.h"
#include "PyUtils.h"

#include "VisitorStmt.h"

using namespace PyUtils;

class VisitorStmt;

class Stmt {
public:
   virtual string acceptstring(VisitorStmt *visitor) = 0;
   virtual TokenLiteral acceptTokenLiteral(VisitorStmt *visitor) = 0;
};

class Expression : public Stmt {
public:
   Expr* expression;
   Expression(Expr* expression);

   string acceptstring(VisitorStmt *visitor);
   TokenLiteral acceptTokenLiteral(VisitorStmt *visitor);

};

class Print : public Stmt {
public:
   Expr* expression;
   Print(Expr* expression);

   string acceptstring(VisitorStmt *visitor);
   TokenLiteral acceptTokenLiteral(VisitorStmt *visitor);

};

class Var : public Stmt {
public:
   Token name;
   Expr* initializer;
   Var(Token name, Expr* initializer);

   string acceptstring(VisitorStmt *visitor);
   TokenLiteral acceptTokenLiteral(VisitorStmt *visitor);

};

class Block : public Stmt {
public:
   vector<Stmt*> statements;
   Block(vector<Stmt*> statements);

   string acceptstring(VisitorStmt *visitor);
   TokenLiteral acceptTokenLiteral(VisitorStmt *visitor);

};

