// Generated by ASTGen

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
class Function;
class Class;
class Return;
class Print;
class Var;
class Block;
class If;
class While;
class Include;

class VisitorStmt {
public:
   virtual string visitExpressionstring(Expression &stmt) = 0;
   virtual string visitFunctionstring(Function &stmt) = 0;
   virtual string visitClassstring(Class &stmt) = 0;
   virtual string visitReturnstring(Return &stmt) = 0;
   virtual string visitPrintstring(Print &stmt) = 0;
   virtual string visitVarstring(Var &stmt) = 0;
   virtual string visitBlockstring(Block &stmt) = 0;
   virtual string visitIfstring(If &stmt) = 0;
   virtual string visitWhilestring(While &stmt) = 0;
   virtual string visitIncludestring(Include &stmt) = 0;

   virtual TokenLiteral visitExpressionTokenLiteral(Expression &stmt) = 0;
   virtual TokenLiteral visitFunctionTokenLiteral(Function &stmt) = 0;
   virtual TokenLiteral visitClassTokenLiteral(Class &stmt) = 0;
   virtual TokenLiteral visitReturnTokenLiteral(Return &stmt) = 0;
   virtual TokenLiteral visitPrintTokenLiteral(Print &stmt) = 0;
   virtual TokenLiteral visitVarTokenLiteral(Var &stmt) = 0;
   virtual TokenLiteral visitBlockTokenLiteral(Block &stmt) = 0;
   virtual TokenLiteral visitIfTokenLiteral(If &stmt) = 0;
   virtual TokenLiteral visitWhileTokenLiteral(While &stmt) = 0;
   virtual TokenLiteral visitIncludeTokenLiteral(Include &stmt) = 0;

};

