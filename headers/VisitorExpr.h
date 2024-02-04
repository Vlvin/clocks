#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "TokenLiteral.h"
#include "Token.h"
#include "TokenType.h"
#include "Expr.h"

class Binary;
class Call;
class Get;
class Set;
class Super;
class This;
class Grouping;
class Literal;
class Logical;
class Unary;
class Variable;
class Assign;

class VisitorExpr {
public:
   virtual string visitBinarystring(Binary &expr) = 0;
   virtual string visitCallstring(Call &expr) = 0;
   virtual string visitGetstring(Get &expr) = 0;
   virtual string visitSetstring(Set &expr) = 0;
   virtual string visitSuperstring(Super &expr) = 0;
   virtual string visitThisstring(This &expr) = 0;
   virtual string visitGroupingstring(Grouping &expr) = 0;
   virtual string visitLiteralstring(Literal &expr) = 0;
   virtual string visitLogicalstring(Logical &expr) = 0;
   virtual string visitUnarystring(Unary &expr) = 0;
   virtual string visitVariablestring(Variable &expr) = 0;
   virtual string visitAssignstring(Assign &expr) = 0;

   virtual TokenLiteral visitBinaryTokenLiteral(Binary &expr) = 0;
   virtual TokenLiteral visitCallTokenLiteral(Call &expr) = 0;
   virtual TokenLiteral visitGetTokenLiteral(Get &expr) = 0;
   virtual TokenLiteral visitSetTokenLiteral(Set &expr) = 0;
   virtual TokenLiteral visitSuperTokenLiteral(Super &expr) = 0;
   virtual TokenLiteral visitThisTokenLiteral(This &expr) = 0;
   virtual TokenLiteral visitGroupingTokenLiteral(Grouping &expr) = 0;
   virtual TokenLiteral visitLiteralTokenLiteral(Literal &expr) = 0;
   virtual TokenLiteral visitLogicalTokenLiteral(Logical &expr) = 0;
   virtual TokenLiteral visitUnaryTokenLiteral(Unary &expr) = 0;
   virtual TokenLiteral visitVariableTokenLiteral(Variable &expr) = 0;
   virtual TokenLiteral visitAssignTokenLiteral(Assign &expr) = 0;

};

