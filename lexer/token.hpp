#include <string>
#pragma once

enum class TokenType {
  // math operators
  ASSIGN,
  PLUS,
  MINUS,
  MULTIPLY,
  DIVIDE,
  POWER,

  INCREMENT,
  DECREMENT,

  //  math comparation
  LESS_EQUAL,
  LESS,
  GREATER,
  GREATER_EQUAL,
  EQUAL,
  NOT_EQUAL,

  //  logic operators
  OR,
  AND,
  NOT,

  // format
  ENDOF,
  SPACE,
  SEMI,
  ILLEGAL,

  // delimitation
  OPENBRACKET,
  CLOSEBRACKET,
  OPENPAREN,
  CLOSEPAREN,
  OPENCURLY,
  CLOSECURLY,

  // idk how to call these things
  ARROW,
  DOUBLEARROW,
  DOT,
  DOUBLECOLON,
  COLON,

  // types
  INT,
  IDENT,

  // keywords
  LET,
  CLASS,
  CONST,
  FUN,
  RETURN,
  IF,
  ELSE,
  SWITCH,
  CASE,
  IMPORT,
  FROM,
  EXPORT,
  // 67
  WHILE,
  FOR,
  BREAK,
  CONTINUE
};

class Token {
private:
  TokenType type;
  std::string literal;

public:
  Token(TokenType type, std::string literal) {
    this->type = type;
    this->literal = literal;
  }
  Token(TokenType type) {
    this->type = type;
    this->literal = "";
  }
  TokenType getType() { return this->type; }
  std::string getLiteral() { return this->literal; }
};
