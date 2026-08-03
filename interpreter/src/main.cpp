#include "./lexer/lexer.hpp"

int main() {
  // basic setup
  FileManager file("./input.txt");
  Lexer lexer(file.read());
	
}