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

#include "VisitorExpr.h"

using namespace PyUtils;

class VisitorExpr;

class Expr {
public:
   virtual string acceptstring(VisitorExpr *visitor) = 0;
   virtual TokenLiteral acceptTokenLiteral(VisitorExpr *visitor) = 0;
};

class Binary : public Expr {
public:
   Expr* left;
   Token oper;
   Expr* right;
   Binary(Expr* left, Token oper, Expr* right);

   string acceptstring(VisitorExpr *visitor);
   TokenLiteral acceptTokenLiteral(VisitorExpr *visitor);

};

class Grouping : public Expr {
public:
   Expr* expr;
   Grouping(Expr* expr);

   string acceptstring(VisitorExpr *visitor);
   TokenLiteral acceptTokenLiteral(VisitorExpr *visitor);

};

class Literal : public Expr {
public:
   TokenLiteral value;
   Literal(TokenLiteral value);

   string acceptstring(VisitorExpr *visitor);
   TokenLiteral acceptTokenLiteral(VisitorExpr *visitor);

};

class Logical : public Expr {
public:
   Expr* left;
   Token oper;
   Expr* right;
   Logical(Expr* left, Token oper, Expr* right);

   string acceptstring(VisitorExpr *visitor);
   TokenLiteral acceptTokenLiteral(VisitorExpr *visitor);

};

class Unary : public Expr {
public:
   Token oper;
   Expr* right;
   Unary(Token oper, Expr* right);

   string acceptstring(VisitorExpr *visitor);
   TokenLiteral acceptTokenLiteral(VisitorExpr *visitor);

};

class Variable : public Expr {
public:
   Token name;
   Variable(Token name);

   string acceptstring(VisitorExpr *visitor);
   TokenLiteral acceptTokenLiteral(VisitorExpr *visitor);

};

class Assign : public Expr {
public:
   Token name;
   Expr* value;
   Assign(Token name, Expr* value);

   string acceptstring(VisitorExpr *visitor);
   TokenLiteral acceptTokenLiteral(VisitorExpr *visitor);

};

