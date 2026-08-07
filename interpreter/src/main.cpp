#include "./lexer/lexer.hpp"
#include "./parser/parser.hpp"
#include <iostream>

int main() {
  // basic setup
  FileManager file("./input.txt");
  Parser parser(file.read(), true, "./logs/debug.log");
  parser.parse();
}