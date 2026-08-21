#pragma once

#include "../expression.hpp"
#include "./../../lexer/token.hpp"

class VariableExpression : public Expression {
    public:

        Token token;
        VariableExpression(Token token)
          : token(token) {};
};
