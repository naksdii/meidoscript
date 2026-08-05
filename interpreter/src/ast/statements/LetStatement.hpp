#pragma once

#include "../statement.hpp"
#include "./../../lexer/token.hpp"
#include "./../expression.hpp"
#include <memory>
#include <string>
#include <utility>

class LetStatement : public Statement {
    private:

        Token name;
        std::unique_ptr<Expression> initializer;

    public:

        LetStatement(Token name, std::unique_ptr<Expression> initializer)
          : name(name)
          , initializer(std::move(initializer)) {}
};