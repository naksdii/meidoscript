#include "../lexer/lexer.hpp"
#include <iostream>
#include <stdexcept>

class Parser {
    private:

        Lexer lexer;

        void parse_LET() {
            Token ID = lexer.nextToken();
            if (ID.getType() != TokenType::IDENT) {
            }
        }

    public:

        Parser(Lexer lexer)
            : lexer(lexer) {}

        void parse() {
            Token currentToken = lexer.nextToken();
            switch (currentToken.getType()) {
                case TokenType::LET:
                    parse_LET();
            }
        }
};
