#pragma once
#include "../error/lexError.hpp"
#include "../logger/logger.hpp"
#include "fileManager.hpp"
#include "token.hpp"
#include <iostream>
#include <string>
#include <unordered_map>

/*
 _   _           _         _
(_) | |__   __ _| |_ ___  | | _____  _____ _ __ ___
| | | '_ \ / _` | __/ _ \ | |/ _ \ \/ / _ \ '__/ __|
| | | | | | (_| | ||  __/ | |  __/>  <  __/ |  \__ \
|_| |_| |_|\__,_|\__\___| |_|\___/_/\_\___|_|  |___/

*/

class Lexer {
    private:

        std::string input; // the input string to be tokenized.
        int inputSize;     // dont recalculate ts everytime, CPU is slow.
        size_t rc, column = 0, line = 0;
        Logger logger;
        /*
          probably i should use a hash map for keywords, but for now this
          will do.
        */

        std::unordered_map<std::string, TokenType> keywords = {
            {"let", TokenType::LET},
            {"class", TokenType::CLASS},
            {"const", TokenType::CONST},
            {"fun", TokenType::FUN},
            {"if", TokenType::IF},
            {"else", TokenType::ELSE},
            {"switch", TokenType::SWITCH},
            {"case", TokenType::CASE},
            {"import", TokenType::IMPORT},
            {"from", TokenType::FROM},
            {"export", TokenType::EXPORT},
            {"while", TokenType::WHILE},
            {"for", TokenType::FOR},
            {"break", TokenType::BREAK},
            {"continue", TokenType::CONTINUE}};
        
        std::
        // wa-wa T-T
        /*
        some function to check caracter types.
        */
        bool isWhitespace(char c) {
            return c == ' ' || c == '\t' || c == '\n' || c == '\r';
        }

        bool isDigit(
            char c) { /*i hate the default formatter need tp change it*/
            return c >= '0' && c <= '9';
        }

        bool isLetter(char c) {
            return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
        }

        char peek() {
            if (rc + 1 >= inputSize)
                return '\0';
            return input[rc + 1];
        }

        void skipComment() {
            while (peek() != '\n') {
                next();
            }
            return;
        }

        void skipCommentBlock() {
            while (input[rc] != ']' && peek() != '>') {
                next();
            }
            next();
            return;
        }

        int next() {
            rc++;
            column++;
            if (input[rc] != '\n')
                return rc;
            line++;
            column = 1;
            return rc;
        }

        void throwLexError(std::string msg) {
            throw LexError(msg);
        }

    public:

        Lexer(std::string input, bool debug, std::string log)
          : logger(log, debug) {
            this->input = input;
            this->rc = 0;
            this->line = 1;
            this->column = 1;
            this->inputSize = input.size();
            logger.log("lexer init complete\n");
        };

        Token nextToken();
        /*
        std::vector<Token> tokenize() {
          std::vector<Token> tokens{};
          tokens.clear();
          Token t = nextToken();
          while (t.getType() != TokenType::ENDOF) {
            tokens.push_back(t);
            t = nextToken();
          }
          tokens.push_back(Token(TokenType::ENDOF));
          return tokens;
        }*/
};

inline Token Lexer::nextToken() {
    logger.log("requested next token\n");
    std::string literal = "";

    // EOF and whitespace handling
    while (rc < inputSize && isWhitespace(input[rc])) {
        next();
    }

    if (rc >= inputSize)
        return Token(TokenType::ENDOF, line, column);

    // tokenization logic
    switch (input[rc]) {
        case '+':
            next();
            if (peek() == '+') {
                next();
                return Token(TokenType::INCREMENT, line, column);
            }
            return Token(TokenType::PLUS, line, column);
        case '-':
            next();
            switch (peek()) {
                case '>':
                    next();
                    return Token(TokenType::ARROW,
                                 line,
                                 column); // Damn, this switch drove
                                          // me crazy.
                case '-':
                    next();
                    return Token(TokenType::DECREMENT, line, column);
            }
            return Token(TokenType::MINUS, line, column);

        case '*':
            next();
            if (peek() == '*') {
                next();
                return Token(TokenType::POWER, line, column);
            }
            return Token(TokenType::MULTIPLY, line, column);
        case '/':
            next();
            if (peek() == '/') {
                next();
                skipComment();
                break;
            }
            return Token(TokenType::DIVIDE, line, column);
        case '=':
            next();
            switch (peek()) {
                case '=':
                    next();
                    return Token(TokenType::EQUAL, line, column);
                case '>':
                    if (peek() == '=') {
                        next();
                        return Token(TokenType::GREATER_EQUAL, line, column);
                    }
                    return Token(TokenType::DOUBLEARROW, line, column);
            }
            return Token(TokenType::ASSIGN, line, column);
        case ';':
            next();
            return Token(TokenType::SEMI, line, column);
        case ',':
            next();
            return Token(TokenType::COMMA, line, column);

        case '.':
            next();
            return Token(TokenType::DOT, line, column);
        case ':':
            next();
            if (peek() == ':') {
                next();
                return Token(TokenType::DOUBLECOLON, line, column);
            }
            return Token(TokenType::COLON, line, column);
        case '(':
            next();
            return Token(TokenType::OPENPAREN, line, column);
        case ')':
            next();
            return Token(TokenType::CLOSEPAREN, line, column);
        case '{':
            next();
            return Token(TokenType::OPENCURLY, line, column);
        case '}':
            next();
            return Token(TokenType::CLOSECURLY, line, column);
        case '[':
            next();
            return Token(TokenType::OPENBRACKET, line, column);
        case ']':
            next();
            return Token(TokenType::CLOSEBRACKET, line, column);
        case '<':
            next();
            if (peek() == '[') {
                next();
                skipCommentBlock();
            }
            break;
        default:
            break;
    }
    if (input[rc] == '"') {
        rc++;

        while (rc < input.size() && input[rc] != '"') {
            literal += input[rc++];
        }

        if (rc >= input.size()) {
            throwLexError("String não terminada.");
        }

        rc++;
        return Token(TokenType::STRING, literal, line, column);
    }
    if (isDigit(input[rc])) {
        while (isDigit(input[rc]) && rc != input.length()) {
            literal += input[rc]; // this concatenate the digit to the literal string.
            next();               // maybe it would be better to use substring?
                                  // idk.
        }
        if (input[rc] == '.') {
            for (int i = 0; i < 15 && (isDigit(input[rc]) && rc != input.length()); i++) {
                literal += input[rc];
                next();
            }
            return Token(TokenType::FLOAT, literal, line, column);
        }
        return Token(TokenType::INT, literal, line, column);
    }
    if (isLetter(input[rc])) {
        while ((isLetter(input[rc]) || isDigit(input[rc])) &&
               rc != input.length()) {
            literal += input[rc];
            next();
            // let
        }
        if (keywords.find(literal) != keywords.end()) {
            return Token(keywords[literal], line, column);
        }
        if (typewords.find(literal) != typewords.end())
        if (literal == "True" || literal == "False")
            return Token(TokenType::BOOL, literal, line, column);
        return Token(TokenType::IDENT, literal, line, column);
    }
    return Token(TokenType::ILLEGAL, std::string(1, input[next()]), line, column);
};
