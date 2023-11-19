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


Unary::Unary(Token oper, Expr* right)
     : oper(oper),right(right) {}

string Unary::acceptstring(VisitorExpr *visitor) {   return visitor->visitUnarystring(*this);
}

TokenLiteral Unary::acceptTokenLiteral(VisitorExpr *visitor) {   return visitor->visitUnaryTokenLiteral(*this);
}


