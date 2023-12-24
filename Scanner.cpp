#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#include "headers/Clockswork.h"
#include "headers/Token.h"
#include "headers/TokenType.h"
#include "headers/TokenLiteral.h"
#include "headers/Scanner.h"

Scanner::Scanner(string source) 
        : source(source) {}

map<string, TokenType> const Scanner::keywords = {
    {"and",    AND},
    {"class",  CLASS},
    {"else",   ELSE},
    {"false",  FALSE},
    {"for",    FOR},
    {"fun",    FUN},
    {"if",     IF},
    {"nil",    NIL},
    {"or",     OR},
    {"dPrint",  PRINT}, // will work even if globals are broken
    {"return", RETURN},
    {"super",  SUPER},
    {"this",   THIS},
    {"true",   TRUE},
    {"var",    VAR},
    {"while",  WHILE}
};

vector<Token> Scanner::scanTokens() {
    while(!isAtEnd()) {


        start = current;
        scanToken();
    }

    tokens.push_back(Token(T_EOF, "", TokenLiteral(), line));
    return tokens;
}

bool Scanner::isAtEnd() {
    return current >= source.length();
}

bool Scanner::match(char expected) {
    if (isAtEnd()) return false;
    if (source[current] != expected) return false;
    current++;
    return true;
}

bool Scanner::isDigit(char c) {
    return ((c >= '0') && (c <= '9'));
}

bool Scanner::isAlpha(char c) {
    return (((c >= 'a') && (c <= 'z')) || 
            ((c >= 'A') && (c <= 'Z')) ||
             (c == '_'));
}

bool Scanner::isAlphaNumeric(char c) {
    return (isAlpha(c) || isDigit(c));
}

char Scanner::advance() {
    return source[current++];
}

char Scanner::peek() {
    if(isAtEnd()) return '\0';
    return source[current];
}

char Scanner::peekNext() {
    if ((current + 1 >= source.length())) return '\0';
    return source[current+1];
}

void Scanner::addToken(TokenType type) {
    addToken(type, TokenLiteral());
}

void Scanner::addToken(TokenType type, TokenLiteral literal) {
    string text = source.substr(start, current-start);
    tokens.push_back(Token(type, text, literal, line));
}

void Scanner::str() {
    while ((peek() != '"') && (!isAtEnd())) {
        if (peek() == '\n') line++;
        advance();
    }

    if (isAtEnd()) {
        Clockwork::error(line, "Unterminated string");
        return;
    }

    advance();

    string value = source.substr(start+1, (current - 1) - (start + 1));
    addToken(STRING, value);
}

void Scanner::num() {
    while(isDigit(peek())) advance();

    if ((peek() == '.') && (isDigit(peekNext()))) advance();

    while(isDigit(peek())) advance();

    addToken(TokenType::NUMBER, stod(source.substr(start, current - start)));

}

void Scanner::identifier() {
    while (isAlphaNumeric(peek())) advance();

    string text = source.substr(start, current-start);
    TokenType type = (keywords.find(text))->second;
    if (type == NULL) type = IDENTIFIER;
    addToken(type);
}

void Scanner::scanToken() {
    char c = advance();
    switch (c) {
        case '(': addToken(LEFT_PAREN); break;
        case ')': addToken(RIGHT_PAREN); break;
        case '{': addToken(LEFT_BRACE); break;
        case '}': addToken(RIGHT_BRACE); break;
        case ',': addToken(COMMA); break;
        case '.': addToken(DOT); break;
        case '-': addToken(MINUS); break;
        case '+': addToken(PLUS); break;
        case ';': addToken(SEMICOLON); break;
        case '*': addToken(STAR); break; 
        case '!':
            addToken(match('=') ? BANG_EQUAL : BANG);
            break;
        case '=':
            addToken(match('=') ? EQUAL_EQUAL : EQUAL);
            break;
        case '<':
            addToken(match('=') ? LESS_EQUAL : LESS);
            break;
        case '>':
            addToken(match('=') ? GREATER_EQUAL : GREATER);
            break;
        case '/':
            if (match('/')) {
                while (peek() != '\n' && !isAtEnd()) advance();
            } else {
                if (match('*')) {
                    while (true) {
                        if (peek() == '\n') line++;
                        if (isAtEnd()) break;
                        if ((advance() == '*' && peek() == '/')) {
                            advance();
                            break;
                        }
                    }
                } else {
                    addToken(SLASH);
                }
            }
            break;
        case ' ':
        case '\r':
        case '\t':
            break;

        case '\n':
            line++;
            break;
        case '"': str(); break;
        default:
            if (isDigit(c)) {
                num();
            } else if (isAlpha(c)) {
                identifier();
            } else {
            Clockwork::error(line, "unexpected character.");
            }
            break;
    }

}
