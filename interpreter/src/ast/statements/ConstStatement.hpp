#pragma once

#include "../statement.hpp"
#include "./../../lexer/token.hpp"
#include "./../expression.hpp"
#include <memory>
#include <utility>

class ConstStatement : public Statement {
    private:

        Token name;
        std::unique_ptr<Expression> initializer;

    public:

        ConstStatement(Token name, std::unique_ptr<Expression> initializer)
          : name(name)
          , initializer(std::move(initializer)) {}
};