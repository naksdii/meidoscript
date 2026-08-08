#pragma once

#include "../ast/all.hpp"
#include "../error/parseError.hpp"
#include "../lexer/lexer.hpp"
#include "../logger/logger.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Parser {
    private:


        std::vector<Token> tokens;
        size_t current = 0;
        Lexer lexer;
        Logger logger;

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

        void throwParseError() {
            std::string msg = "encontrou algum token invalido: ";
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
                logger.log("declared " + name.getLiteral() + "\n");
                return std::make_unique<LetStatement>(name, nullptr);
            }
            consume(TokenType::ASSIGN);

            auto initializer = parseExpression();

            consume(TokenType::SEMI);
            logger.log("declared " + name.getLiteral() + " as something\n");
            return std::make_unique<LetStatement>(name, std::move(initializer));
        }

        std::unique_ptr<Statement> parse_CONST() {
            consume(TokenType::CONST);

            Token name = consume(TokenType::IDENT);

            consume(TokenType::ASSIGN);

            auto initializer = parseExpression();

            consume(TokenType::SEMI);
            logger.log("declared constant " + name.getLiteral() + " as something\n");
            return std::make_unique<ConstStatement>(name, std::move(initializer));
        }

        std::unique_ptr<Statement> parse_FUN() {
            consume(TokenType::FUN);

            Token name = consume(TokenType::IDENT);
            Token returnType;
            if (match(TokenType::ASSIGN)) {
                returnType = consume(TokenType::IDENT);
            }
            consume(TokenType::OPENCURLY);
            std::vector<std::pair<Expression, std::string>> parameters;
            while () {
                auto initializer = parseExpression();
            }
            consume(TokenType::SEMI);
            logger.log("declared function " + name.getLiteral() + "\n");
            return std::make_unique<ConstStatement>(name, std::move(initializer));
        }

        std::unique_ptr<Expression> parsePrimaryExpression() {
            if (match(TokenType::INT)) {
                return std::make_unique<LiteralExpression>(previous());
            }
            if (match(TokenType::BOOL)) {
                return std::make_unique<LiteralExpression>(previous());
            }
            if (match(TokenType::IDENT)) {
                return std::make_unique<VariableExpression>(previous());
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
            return nullptr; // just beacuse the is a warning here and this fixes it
        }

        std::unique_ptr<Expression> parseUnary() {
            if (match(TokenType::MINUS) ||
                match(TokenType::NOT)) {
                Token op = previous();

                auto expr = parseUnary();

                return std::make_unique<UnaryExpression>(
                    op,
                    std::move(expr));
            }

            return parsePrimaryExpression();
        }

        std::unique_ptr<Expression> parseMultiplication() {
            auto left = parseUnary();

            while (match(TokenType::MULTIPLY) || match(TokenType::DIVIDE)) {
                Token op = previous();

                auto right = parseUnary();

                left = std::make_unique<BinaryExpression>(
                    std::move(left),
                    op,
                    std::move(right));
            }

            return left;
        }

        std::unique_ptr<Expression> parseAddition() {
            auto left = parseMultiplication();

            while (match(TokenType::PLUS) || match(TokenType::MINUS)) {
                Token op = previous();

                auto right = parseMultiplication();

                left = std::make_unique<BinaryExpression>(
                    std::move(left),
                    op,
                    std::move(right));
            }

            return left;
        }

        std::unique_ptr<Expression> parseComparison() {
            auto left = parseEquality();

            while (match(TokenType::LESS) || match(TokenType::GREATER) || match(TokenType::LESS_EQUAL) || match(TokenType::GREATER_EQUAL)) {
                Token op = previous();

                auto right = parseEquality();

                left = std::make_unique<BinaryExpression>(
                    std::move(left),
                    op,
                    std::move(right));
            }

            return left;
        }

        std::unique_ptr<Expression> parseEquality() {
            auto left = parseAddition();

            while (match(TokenType::EQUAL) || match(TokenType::NOT_EQUAL)) {
                Token op = previous();

                auto right = parseAddition();

                left = std::make_unique<BinaryExpression>(
                    std::move(left),
                    op,
                    std::move(right));
            }

            return left;
        }

        std::unique_ptr<Expression> parseLogical() {
            auto left = parseEquality();

            while (match(TokenType::AND) || match(TokenType::OR)) {
                Token op = previous();
                auto right = parseEquality();

                left = std::make_unique<BinaryExpression>(
                    std::move(left),
                    op,
                    std::move(right));
            }

            return left;
        }

        std::unique_ptr<Expression> parseExpression() {
            return parseLogical();
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

        Parser(std::string filePath, bool debugmode, std::string logpath)
          : logger(logpath, debugmode)
          , lexer(filePath, debugmode, logpath) {

            logger.log("parser init complete\n");
        }

        void parse() {
            logger.log("started parsing\n");
            Token currentToken = lexer.nextToken();

            while (currentToken.getType() != TokenType::ENDOF) {
                tokens.push_back(currentToken);
                currentToken = lexer.nextToken();
                logger.log("found a token from type: " + std::to_string(currentToken.getType()) + "\n");
            }
            tokens.push_back(currentToken);
            try {
                switch (tokens.at(0).getType()) {
                    case TokenType::LET:
                        logger.log("found a LET case;\n");
                        parse_LET();
                        break;
                    case TokenType::CONST:
                        logger.log("found a CONST case;\n");
                        parse_CONST();
                        break;
                    case TokenType::FUN:
                        logger.log("found a FUN case;\n");
                        parse_FUN();
                    default:
                        throwParseError();
                        break;
                }
            } catch (const ParseError &e) {
                std::cout << e.what() << "";
                logger.log(e.what());
                std::exit(-67);
            }

            logger.log("okay;\n");
        }
};
