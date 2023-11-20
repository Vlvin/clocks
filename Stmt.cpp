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


Print::Print(Expr* expression)
     : expression(expression) {}

string Print::acceptstring(VisitorStmt *visitor) {   return visitor->visitPrintstring(*this);
}

TokenLiteral Print::acceptTokenLiteral(VisitorStmt *visitor) {   return visitor->visitPrintTokenLiteral(*this);
}


