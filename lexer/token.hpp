#pragma once
#include "tokenType.hpp"
#include <string>
class token {
private:
  tokenType type;
  std::string literal;

public:
  token(tokenType type, std::string literal) {
    this->type = type;
    this->literal = literal;
  }
  tokenType getType() {
      return this->type;
  }
  std::string getTypeName() {
      switch (this->type) {
      case tokenType::ILLEGAL:
        return "ILLEGAL";
      case tokenType::ENDOF:
        return "ENDOF";
      case tokenType::INT:
        return "INT";
      case tokenType::IDENT:
        return "IDENT";
      case tokenType::PLUS:
        return "PLUS";
      case tokenType::MINUS:
        return "MINUS";
      case tokenType::MULTIPLY:
        return "MULTIPLY";
      case tokenType::DIVIDE:
        return "DIVIDE";
      case tokenType::ASSIGN:
        return "ASSIGN";
      case tokenType::SEMI:
        return "SEMI";
      default:
        return "UNKNOWN";
      }
  }
  std::string getLiteral() { return this->literal; }
};