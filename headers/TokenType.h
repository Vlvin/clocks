#pragma once

enum TokenType {
  // Single-character tokens.
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, // Single-character tokens.
  COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR, // Single-character tokens.
  MOD, // Single-character tokens.

  // One or two character tokens.
  BANG, BANG_EQUAL,  // One or two character tokens.
  EQUAL, EQUAL_EQUAL,  // One or two character tokens.
  GREATER, GREATER_EQUAL,  // One or two character tokens.
  LESS, LESS_EQUAL,  // One or two character tokens.

  // Literals.
  IDENTIFIER, STRING, NUMBER, // Literals.

  // Keywords.
  AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR, CONST, // Keywords.
  PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE, STATIC, // Keywords.

  T_EOF
};