#pragma once

#include "../expression.hpp"
#include "./../../lexer/token.hpp"


class LiteralExpression : public Expression {
    public:

        Token token;
        LiteralExpression(Token token)
          : token(token) {};
};