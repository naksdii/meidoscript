#pragma once

#include "../ast/expression.hpp"
#include "../ast/expressions/PrimaryExpression.hpp"
#include "../ast/statement.hpp"
#include "../ast/statements/LetStatement.hpp"
#include "../error/parseError.hpp"
#include "../lexer/fileManager.hpp"
#include "../lexer/lexer.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Parser {
    private:

        bool debug = true;

        std::vector<Token> tokens;
        size_t current = 0;
        Lexer lexer;
        std::string debugPath = "debug.log";
        FileManager debugLog = FileManager(debugPath);

        struct expr {};

        void throwParseError(TokenType type) {
            std::string msg = "Esperava: ";
            msg.append(std::to_string(type));
            msg.append("\nin line: ");
            msg.append(std::to_string(tokens[current].getLine()));
            msg.append(", in column: ");
            msg.append(std::to_string(tokens[current].getColumn()));
            msg.append("\n");
            throw ParseError(msg);
        }

        void throwExprParseError() {
            std::string msg = "Esperava uma expressão valida em ";
            msg.append("\nin line: ");
            msg.append(std::to_string(tokens[current].getLine()));
            msg.append(", in column: ");
            msg.append(std::to_string(tokens[current].getColumn()));
            msg.append("\n");
            throw ParseError(msg);
        }

        std::unique_ptr<Statement> parse_LET() {
            consume(TokenType::LET);

            Token name = consume(TokenType::IDENT);

            if (match(TokenType::SEMI)) {
                std::cout << "\ndeclared " << name.getLiteral() << "\n";
                return std::make_unique<LetStatement>(name, nullptr);
            }
            consume(TokenType::ASSIGN);

            auto initializer = parseExpression();

            consume(TokenType::SEMI);
            std::cout << "\ndeclared " << name.getLiteral() << " as something\n";
            return std::make_unique<LetStatement>(name, std::move(initializer));
        }

        std::unique_ptr<Expression> parsePrimaryExpression() {
            if (match(TokenType::INT)) {
                return std::make_unique<LiteralExpression>(previous());
            }
            if (match(TokenType::BOOL)) {
                return std::make_unique<LiteralExpression>(previous());
            }
            if (match(TokenType::IDENT)) {
                return std::make_unique<LiteralExpression>(previous());
            }
            if (match(TokenType::FLOAT)) {
                return std::make_unique<LiteralExpression>(previous());
            }
            if (match(TokenType::OPENPAREN)) {
                auto expr = parseExpression();

                consume(TokenType::CLOSEPAREN);

                return expr;
            }
            throwExprParseError();
        }

        std::unique_ptr<Expression> parseExpression() {
            return parsePrimaryExpression();
        }

        Token &peek() { return tokens[current]; }

        Token &previous() { return tokens[current - 1]; }

        Token advance() {
            if (current < tokens.size())
                current++;
            return previous();
        }

        bool match(TokenType type) {
            if (peek().getType() != type)
                return false;

            advance();
            return true;
        }

        Token consume(TokenType type) {
            if (peek().getType() != type) {
                throwParseError(type);
            }

            return advance();
        }

    public:

        Parser(Lexer lexer)
          : lexer(lexer) {
            debugLog.clean();
            debugLog.write("parser init complete\n");
        }

        void parse() {
            debugLog.write("started parsing\n");
            Token currentToken = lexer.nextToken();

            while (currentToken.getType() != TokenType::ENDOF) {
                tokens.push_back(currentToken);
                currentToken = lexer.nextToken();
                debugLog.write("found a token from type: "+std::to_string(currentToken.getType())+"\n");
            }
            tokens.push_back(currentToken);
            try {
                switch (tokens.at(0).getType()) {
                    case TokenType::LET:
                        debugLog.write("found a LET case;\n");
                        parse_LET();
                }
            } catch (const ParseError &e) {
                std::cout << e.what() << '\n';
                std::abort();
            }

            debugLog.write("okay;\n");
        }
};
