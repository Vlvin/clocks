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

class Function : public Stmt {
public:
   Token name;
   vector<Token> params;
   vector<Stmt*> body;
   bool isConst;
   Function(Token name, vector<Token> params, vector<Stmt*> body, bool isConst);

   string acceptstring(VisitorStmt *visitor);
   TokenLiteral acceptTokenLiteral(VisitorStmt *visitor);

};

class Class : public Stmt {
public:
   Token name;
   vector<Function*> statics;
   vector<Function*> methods;
   Class(Token name, vector<Function*> statics, vector<Function*> methods);

   string acceptstring(VisitorStmt *visitor);
   TokenLiteral acceptTokenLiteral(VisitorStmt *visitor);

};

class Return : public Stmt {
public:
   Token keyword;
   Expr* value;
   Return(Token keyword, Expr* value);

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
   bool isConst;
   Var(Token name, Expr* initializer, bool isConst);

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

class If : public Stmt {
public:
   Expr* condition;
   Stmt* thenBranch;
   Stmt* elseBranch;
   If(Expr* condition, Stmt* thenBranch, Stmt* elseBranch);

   string acceptstring(VisitorStmt *visitor);
   TokenLiteral acceptTokenLiteral(VisitorStmt *visitor);

};

class While : public Stmt {
public:
   Expr* condition;
   Stmt* body;
   While(Expr* condition, Stmt* body);

   string acceptstring(VisitorStmt *visitor);
   TokenLiteral acceptTokenLiteral(VisitorStmt *visitor);

};

