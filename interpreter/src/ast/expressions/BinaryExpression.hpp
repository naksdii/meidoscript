#pragma once
#include "../../lexer/lexer.hpp"
#include "../expression.hpp"
#include <memory>
#include <utility>

class BinaryExpression : public Expression {
    public:

        std::unique_ptr<Expression> left;
        Token op;
        std::unique_ptr<Expression> right;

        BinaryExpression(
            std::unique_ptr<Expression> left,
            Token op,
            std::unique_ptr<Expression> right)
          : left(std::move(left))
          , op(op)
          , right(std::move(right)) {}
};