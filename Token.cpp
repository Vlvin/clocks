#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "headers/Token.h"
#include "headers/TokenType.h"
#include "headers/TokenLiteral.h"


Token::Token(TokenType type, string lexeme, TokenLiteral literal, int line) 
        : type(type), lexeme(lexeme), literal(literal), line(line) {}

const char* Token::TTT[41] = {
  // Single-character tokens.
  "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE",
  "COMMA", "DOT", "MINUS", "PLUS", "SEMICOLON", "SLASH", "STAR",

  // One or two character tokens.
  "BANG", "BANG_EQUAL",
  "EQUAL", "EQUAL_EQUAL",
  "GREATER", "GREATER_EQUAL",
  "LESS", "LESS_EQUAL",

  // Literals.
  "IDENTIFIER", "STRING", "NUMBER",

  // Keywords.
  "AND", "CLASS", "ELSE", "FALSE", "FUN", "FOR", "IF", "NIL", "OR", "CONST",
  "PRINT", "RETURN", "SUPER", "THIS", "TRUE", "VAR", "WHILE", "STATIC",

  "T_EOF"
    
};

string Token::toString() {
    return string(TTT[type]) + " " + lexeme + " " + literal.toString() + " " + to_string(line);
}