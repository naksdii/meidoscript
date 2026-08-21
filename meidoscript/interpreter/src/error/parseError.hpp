#pragma once 
#include "../lexer/lexer.hpp"
#include <stdexcept>

class ParseError : public std::runtime_error {
  public:

    ParseError(const std::string &msg)
      : std::runtime_error(msg) {}
};