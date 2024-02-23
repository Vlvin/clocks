#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#include "Clockswork.h"
#include "Token.h"
#include "TokenType.h"
#include "TokenLiteral.h"

class Scanner {
    string source, modulename;
    vector<Token> tokens;
    int start = 0;
    int current = 0;
    int line = 1;

public:
    Scanner(string source);

    vector<Token> scanTokens(string modulename);

private:
    static map<string, TokenType> const keywords;

    bool isAtEnd();
    bool match(char expected);
    bool isDigit(char c);
    bool isAlpha(char c);
    bool isAlphaNumeric(char c);

    void scanToken();
    void addToken(TokenType type);
    void addToken(TokenType type, TokenLiteral literal);
    void str();
    void num();
    void identifier();

    char advance();
    char peek();
    char peekNext();

};