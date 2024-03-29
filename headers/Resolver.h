#pragma once 

#include "VisitorExpr.h"
#include "VisitorStmt.h"
#include "TokenLiteral.h"
#include "Clockswork.h"
#include "Interpreter.h"

#include <vector>
#include <stack>
#include <string>
#include <map>

using namespace std;

class Resolver: public VisitorExpr, public VisitorStmt {

    string modulename;
    enum FunctionType {
        FNONE,
        FUNCTION,
        INITIALIZER,
        METHOD,
        STATICF
    };
    enum ClassType {
        CNONE,
        CLASS,
        SUBCLASS
    };
    FunctionType currentFunction = FunctionType::FNONE;
    ClassType currentClass = ClassType::CNONE;

    Interpreter* interpreter;
    void resolve(Stmt* stmt);
    void resolve(Expr* expr);
    void resolveLocal(Expr* expr, Token name);
    void resolveFunction(Function& function, FunctionType type);
    void beginScope();
    void endScope();
    void declare(Token name);
    void define(Token name);
    vector<map<string, bool>> scopes;

public:
    void resolve(string modulename, vector<Stmt*> statements);
    void resolve(vector<Stmt*> statements);
    Resolver(Interpreter *interpreter);

   virtual string visitExpressionstring(Expression &stmt) override;
   virtual string visitFunctionstring(Function &stmt) override;
   virtual string visitClassstring(Class &stmt) override;
   virtual string visitReturnstring(Return &stmt) override;
   virtual string visitPrintstring(Print &stmt) override;
   virtual string visitVarstring(Var &stmt) override;
   virtual string visitBlockstring(Block &stmt) override;
   virtual string visitIfstring(If &stmt) override;
   virtual string visitWhilestring(While &stmt) override;
   virtual string visitIncludestring(Include &stmt) override;
   
   virtual TokenLiteral visitExpressionTokenLiteral(Expression &stmt) override;
   virtual TokenLiteral visitFunctionTokenLiteral(Function &stmt) override;
   virtual TokenLiteral visitClassTokenLiteral(Class &stmt) override;
   virtual TokenLiteral visitReturnTokenLiteral(Return &stmt) override;
   virtual TokenLiteral visitPrintTokenLiteral(Print &stmt) override;
   virtual TokenLiteral visitVarTokenLiteral(Var &stmt) override;
   virtual TokenLiteral visitBlockTokenLiteral(Block &stmt) override;
   virtual TokenLiteral visitIfTokenLiteral(If &stmt) override;
   virtual TokenLiteral visitWhileTokenLiteral(While &stmt) override;
   virtual TokenLiteral visitIncludeTokenLiteral(Include &stmt) override;

   virtual string visitBinarystring(Binary &expr) override;
   virtual string visitCallstring(Call &expr) override;
   virtual string visitGetstring(Get &expr) override;
   virtual string visitSetstring(Set &expr) override;
   virtual string visitThisstring(This &expr) override;
   virtual string visitSuperstring(Super &expr) override;
   virtual string visitGroupingstring(Grouping &expr) override;
   virtual string visitLiteralstring(Literal &expr) override;
   virtual string visitLogicalstring(Logical &expr) override;
   virtual string visitUnarystring(Unary &expr) override;
   virtual string visitVariablestring(Variable &expr) override;
   virtual string visitAssignstring(Assign &expr) override;

   virtual TokenLiteral visitBinaryTokenLiteral(Binary &expr) override;
   virtual TokenLiteral visitCallTokenLiteral(Call &expr) override;
   virtual TokenLiteral visitGetTokenLiteral(Get &expr) override;
   virtual TokenLiteral visitSetTokenLiteral(Set &expr) override;
   virtual TokenLiteral visitThisTokenLiteral(This &expr) override;
   virtual TokenLiteral visitSuperTokenLiteral(Super &expr) override;
   virtual TokenLiteral visitGroupingTokenLiteral(Grouping &expr) override;
   virtual TokenLiteral visitLiteralTokenLiteral(Literal &expr) override;
   virtual TokenLiteral visitLogicalTokenLiteral(Logical &expr) override;
   virtual TokenLiteral visitUnaryTokenLiteral(Unary &expr) override;
   virtual TokenLiteral visitVariableTokenLiteral(Variable &expr) override;
   virtual TokenLiteral visitAssignTokenLiteral(Assign &expr) override;

};