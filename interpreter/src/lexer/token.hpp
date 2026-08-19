#pragma once
#include <cstddef>
#include <string>

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


    ARROW,
    DOUBLEARROW,
    DOT,
    COMMA,
    DOUBLECOLON,
    COLON,

    // types
    INT,
    FLOAT,
    IDENT,
    STRING,
    BOOL,
    TYPE,

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
        long long int column = 0;
        long long int line = 0;

    public:

        Token(TokenType type, std::string literal, size_t line, size_t column)
          : type(type)
          , literal(literal)
          , line(line)
          , column(column) {}

        Token(TokenType type, size_t line, size_t column)
          : type(type) {
            this->type = type;
            this->literal = "";
            this->line = line;
            this->column = column;
        }

        Token() {}

        TokenType getType() { return this->type; }

        std::string getLiteral() { return this->literal; }

        long long int getLine() { return this->line; }

        long long int getColumn() { return this->column; }
};
