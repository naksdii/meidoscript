#include "./lexer/lexer.hpp"
#include "./lexer/token.hpp"
#include <iostream>
int main() {
  // basic setup
  FileManager file("./input.txt");
  Lexer lexer(file.read());
  auto t = lexer.nextToken();
  while (t.getType() != TokenType::ENDOF) {
    std::cout << "[type]: " << t.getType()
              << " |  [literal]: " << (t.getLiteral()!=""?t.getLiteral():" no literal") << std::endl;
    t = lexer.nextToken();
  }
}