#include "./lexer/lexer.hpp"
#include "./parser/parser.hpp"
#include <iostream>

int main() {
  // basic setup
  FileManager file("./input.txt");
  Lexer lexer(file.read());

  Parser parser(lexer);
  parser.parse();
}