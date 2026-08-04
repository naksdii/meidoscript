#include <cstddef>
#include <string>
#pragma once

enum TokenType {
  // math
  // operators
  ASSIGN,
  PLUS,
  MINUS,
  MULTIPLY,
  DIVIDE,
  POWER,

  INCREMENT,
  DECREMENT,

  //  math
  //  comparation
  LESS_EQUAL,
  LESS,
  GREATER,
  GREATER_EQUAL,
  EQUAL,
  NOT_EQUAL,

  //  logic
  //  operators
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

  // idk
  // how
  // to
  // call
  // these
  // things
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
    size_t column;
    size_t line;

  public:
    Token(TokenType type,
          std::string literal,
          size_t line,
          size_t column)
      : type(type)
      , literal(literal)
      , line(line)
      , column(column) {}

    Token(TokenType type, size_t line, size_t column)
      : type(type) {
      this->type = type;
      this->literal = "";
    }

    TokenType getType() { return this->type; }

    std::string getLiteral() { return this->literal; }

    size_t getLine() { return this->line; }

    size_t getColumn() { return this->column; }
};
