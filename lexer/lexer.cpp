#include "fileManager.hpp"
#include "token.hpp"
#include "tokenType.hpp"
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>

class Lexer {
private:
  std::string input;
  int inputSize;
  size_t rc; /*read character*/
  std::unordered_map<std::string, std::function<bool(char)>> identifiers;
  bool isWhitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
  }
  bool isDigit(char c) { return c >= '0' && c <= '9'; }
  bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
  }

public:
  Lexer(std::string input) : input(input), rc(0), inputSize(input.size()) {};

  token nextToken() {

    std::string literal = "";
    if (rc >= inputSize)
      return token(tokenType::ENDOF, "");

    if (isWhitespace(input[rc])) {
      while (isWhitespace(input[rc])) {
        rc++;
        if (rc >= inputSize)
          return token(tokenType::ENDOF, "");
      }
      token t = token(tokenType::SPACE, " ");
    }

    switch (input[rc]) {
    case '+':
      rc++;
      return token(tokenType::PLUS, "+");
    case '-':
      rc++;
      return token(tokenType::MINUS, "-");
    case '*':
      rc++;
      return token(tokenType::MULTIPLY, "*");
    case '/':
      rc++;
      return token(tokenType::DIVIDE, "/");
    case '=':
      rc++;
      return token(tokenType::ASSIGN, "=");
    case ';':
      rc++;
      return token(tokenType::SEMI, ";");
    default:
      break;
    }
    if (isDigit(input[rc])) {
      while (isDigit(input[rc]) && rc != input.length()) {
        literal += input[rc];
        rc++;
      }
      return token(tokenType::INT, literal);
    }
    if (isLetter(input[rc])) {
      while (isLetter(input[rc]) && rc != input.length()) {
        literal += input[rc];
        rc++;
      }
      return token(tokenType::IDENT, literal);
    }
    return token(tokenType::ILLEGAL, std::string(1, input[rc++]));
  };
};

int main() {
  fileManager file("input.txt");
  std::string input = file.read();
  Lexer lexer(input);
  while (true) {
    token t = lexer.nextToken();
    std::string typeName = t.getTypeName();
    std::cout << "[Type] "
              << typeName.append(std::string(10 - typeName.length(), ' '))
              << " | [Literal] " << t.getLiteral() << std::endl;
    if (t.getType() == tokenType::ENDOF) {
      break;
    }
  }
  return 0;
}