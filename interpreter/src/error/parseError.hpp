#include "../lexer/lexer.hpp"
#include <stdexcept>

class ParseError : public std::runtime_error {
    public:

        ParseError(Token &tok, const std::string &msg)
            : std::runtime_error(
                  "Linha " + std::to_string(tok.getLine()) +
                  ", coluna " + std::to_string(tok.getColumn()) +
                  ": " + msg) {}
};