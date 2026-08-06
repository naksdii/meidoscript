#pragma once
#include "../lexer/lexer.hpp"
#include <stdexcept>

class LexError : public std::runtime_error {
    public:

        LexError(const std::string &msg)
          : std::runtime_error(msg) {}
};