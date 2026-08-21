#pragma once

#include "../statement.hpp"
#include "./../../lexer/token.hpp"
#include <utility>
#include <vector>

class DeclareFunctionStatement : public Statement {
    private:

        Token funName;
        std::vector<std::pair<TokenType, std::string>> paramList;
        Token returnType;
        std::vector<Statement> statements;

    public:

        DeclareFunctionStatement(Token name, std::vector<std::pair<TokenType, std::string>> paramList, Token returnType, std::vector<Statement> statements)
          : funName(name)
          , paramList(paramList)
          , returnType(returnType)
          , statements(statements) {}
};