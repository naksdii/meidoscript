#pragma once
#include "../../lexer/lexer.hpp"
#include "../expression.hpp"
#include <memory>
#include <utility>

class UnaryExpression : public Expression {
    public:

        Token op;
        std::unique_ptr<Expression> value;

        UnaryExpression(
            Token op,
            std::unique_ptr<Expression> value)
          : op(op)
          , value(std::move(value)) {}
};