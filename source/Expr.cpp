// Generated by ASTGen

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "headers/Token.h"
#include "headers/Expr.h"
#include "headers/TokenLiteral.h"
#include "headers/VisitorExpr.h"

Binary::Binary(Expr* left, Token oper, Expr* right)
     : left(left),oper(oper),right(right) {}

string Binary::acceptstring(VisitorExpr *visitor) {   return visitor->visitBinarystring(*this);
}

TokenLiteral Binary::acceptTokenLiteral(VisitorExpr *visitor) {   return visitor->visitBinaryTokenLiteral(*this);
}


Call::Call(Expr* callee, Token paren, vector<Expr*> arguments)
     : callee(callee),paren(paren),arguments(arguments) {}

string Call::acceptstring(VisitorExpr *visitor) {   return visitor->visitCallstring(*this);
}

TokenLiteral Call::acceptTokenLiteral(VisitorExpr *visitor) {   return visitor->visitCallTokenLiteral(*this);
}


Get::Get(Expr* object, Token name)
     : object(object),name(name) {}

string Get::acceptstring(VisitorExpr *visitor) {   return visitor->visitGetstring(*this);
}

TokenLiteral Get::acceptTokenLiteral(VisitorExpr *visitor) {   return visitor->visitGetTokenLiteral(*this);
}


Set::Set(Expr* object, Token name, Expr* value)
     : object(object),name(name),value(value) {}

string Set::acceptstring(VisitorExpr *visitor) {   return visitor->visitSetstring(*this);
}

TokenLiteral Set::acceptTokenLiteral(VisitorExpr *visitor) {   return visitor->visitSetTokenLiteral(*this);
}


Super::Super(Token keyword)
     : keyword(keyword) {}

string Super::acceptstring(VisitorExpr *visitor) {   return visitor->visitSuperstring(*this);
}

TokenLiteral Super::acceptTokenLiteral(VisitorExpr *visitor) {   return visitor->visitSuperTokenLiteral(*this);
}


This::This(Token keyword)
     : keyword(keyword) {}

string This::acceptstring(VisitorExpr *visitor) {   return visitor->visitThisstring(*this);
}

TokenLiteral This::acceptTokenLiteral(VisitorExpr *visitor) {   return visitor->visitThisTokenLiteral(*this);
}


Grouping::Grouping(Expr* expr)
     : expr(expr) {}

string Grouping::acceptstring(VisitorExpr *visitor) {   return visitor->visitGroupingstring(*this);
}

TokenLiteral Grouping::acceptTokenLiteral(VisitorExpr *visitor) {   return visitor->visitGroupingTokenLiteral(*this);
}


Literal::Literal(TokenLiteral value)
     : value(value) {}

string Literal::acceptstring(VisitorExpr *visitor) {   return visitor->visitLiteralstring(*this);
}

TokenLiteral Literal::acceptTokenLiteral(VisitorExpr *visitor) {   return visitor->visitLiteralTokenLiteral(*this);
}


Logical::Logical(Expr* left, Token oper, Expr* right)
     : left(left),oper(oper),right(right) {}

string Logical::acceptstring(VisitorExpr *visitor) {   return visitor->visitLogicalstring(*this);
}

TokenLiteral Logical::acceptTokenLiteral(VisitorExpr *visitor) {   return visitor->visitLogicalTokenLiteral(*this);
}


Unary::Unary(Token oper, Expr* right)
     : oper(oper),right(right) {}

string Unary::acceptstring(VisitorExpr *visitor) {   return visitor->visitUnarystring(*this);
}

TokenLiteral Unary::acceptTokenLiteral(VisitorExpr *visitor) {   return visitor->visitUnaryTokenLiteral(*this);
}


Variable::Variable(Token name)
     : name(name) {}

string Variable::acceptstring(VisitorExpr *visitor) {   return visitor->visitVariablestring(*this);
}

TokenLiteral Variable::acceptTokenLiteral(VisitorExpr *visitor) {   return visitor->visitVariableTokenLiteral(*this);
}


Assign::Assign(Token name, Expr* value)
     : name(name),value(value) {}

string Assign::acceptstring(VisitorExpr *visitor) {   return visitor->visitAssignstring(*this);
}

TokenLiteral Assign::acceptTokenLiteral(VisitorExpr *visitor) {   return visitor->visitAssignTokenLiteral(*this);
}


