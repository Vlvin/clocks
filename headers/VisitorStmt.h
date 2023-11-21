#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "TokenLiteral.h"
#include "Token.h"
#include "TokenType.h"
#include "Stmt.h"

class Expression;
class Print;
class Var;

class VisitorStmt {
public:
   virtual string visitExpressionstring(Expression &stmt) = 0;
   virtual string visitPrintstring(Print &stmt) = 0;
   virtual string visitVarstring(Var &stmt) = 0;

   virtual TokenLiteral visitExpressionTokenLiteral(Expression &stmt) = 0;
   virtual TokenLiteral visitPrintTokenLiteral(Print &stmt) = 0;
   virtual TokenLiteral visitVarTokenLiteral(Var &stmt) = 0;

};

