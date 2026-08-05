#pragma once

#include "../expression.hpp"
#include "./../../lexer/token.hpp"

#include <memory>
#include <string>
#include <utility>

class VariableExpression : public Expression {
    public:

        Token token;
        VariableExpression(Token token)
          : token(token) {};
};

class LiteralExpression : public Expression {
    public:

        Token token;
        LiteralExpression(Token token)
          : token(token) {};
};