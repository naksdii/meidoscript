#pragma once
#include "fileManager.hpp"
#include "token.hpp"
#include <string>
#include <unordered_map>
#include <vector>

/*
 _   _           _         _
(_) | |__   __ _| |_ ___  | | _____  _____ _ __ ___
| | | '_ \ / _` | __/ _ \ | |/ _ \ \/ / _ \ '__/ __|
| | | | | | (_| | ||  __/ | |  __/>  <  __/ |  \__ \
|_| |_| |_|\__,_|\__\___| |_|\___/_/\_\___|_|  |___/

*/

class Lexer {
private:
  std::string input; // the input string to be tokenized.
  int inputSize;     // dont recalculate ts everytime, CPU is slow.
  size_t rc;         // read character

  /*
    probably i should use a hash map for keywords, but for now this will do.
  */

  std::unordered_map<std::string, TokenType> keywords = {
      {"let", TokenType::LET},
      {"class", TokenType::CLASS},
      {"const", TokenType::CONST},
      {"fun", TokenType::FUN},
      {"if", TokenType::IF},
      {"else", TokenType::ELSE},
      {"switch", TokenType::SWITCH},
      {"case", TokenType::CASE},
      {"import", TokenType::IMPORT},
      {"from", TokenType::FROM},
      {"export", TokenType::EXPORT},
      {"while", TokenType::WHILE},
      {"for", TokenType::FOR},
      {"break", TokenType::BREAK},
      {"continue", TokenType::CONTINUE}};

  // wa-wa T-T
  /*
  some function to check caracter types.
  */
  bool isWhitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
  }
  bool isDigit(char c) { /*i hate the default formatter need tp change it*/
    return c >= '0' && c <= '9';
  }
  bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
  }
  char peek() {
    if (rc + 1 >= inputSize)
      return '\0';
    return input[rc + 1];
  }

public:
  Lexer(std::string input) : input(input), rc(0), inputSize(input.size()) {};

  Token nextToken();
  std::vector<Token> tokenize() {
    std::vector<Token> tokens{};
    tokens.clear();
    Token t = nextToken();
    while (t.getType() != TokenType::ENDOF) {
      tokens.push_back(t);
    }
    tokens.push_back(Token(TokenType::ENDOF));
    return tokens;
  }
};

Token Lexer::nextToken() {

  std::string literal = "";

  // EOF and whitespace handling
  while (rc < inputSize && isWhitespace(input[rc])) {
    rc++;
  }

  if (rc >= inputSize)
    return Token(TokenType::ENDOF, "");

  // tokenization logic
  switch (input[rc++]) {
  case '+':
    if (peek() == '+') {
      rc++;
      return Token(TokenType::INCREMENT);
    }
    return Token(TokenType::PLUS);
  case '-':
    switch (peek()) {
    case '>':
      rc++;
      return Token(TokenType::ARROW); // Damn, this switch drove me crazy.
    case '-':
      rc++;
      return Token(TokenType::DECREMENT);
    }
    return Token(TokenType::MINUS, "-");

  case '*':
    if (peek() == '*') {
      rc++;
      return Token(TokenType::POWER);
    }
    return Token(TokenType::MULTIPLY);
  case '/':
    return Token(TokenType::DIVIDE);
  case '=':
    switch (peek()) {
    case '=':
      rc++;
      return Token(TokenType::EQUAL);
    case '>':
      rc++;
      if (peek() == '=') {
        rc++;
        return Token(TokenType::GREATER_EQUAL);
      }
      return Token(TokenType::DOUBLEARROW);
    default:
      break;
    }
    return Token(TokenType::ASSIGN);
  case ';':
    return Token(TokenType::SEMI);
  case '.':
    return Token(TokenType::DOT);
  case ':':
    if (peek() == ':') {
      rc++;
      return Token(TokenType::DOUBLECOLON);
    }
    return Token(TokenType::COLON);
  case '(':
    return Token(TokenType::OPENPAREN);
  case ')':
    return Token(TokenType::CLOSEPAREN);
  case '{':
    return Token(TokenType::OPENCURLY);
  case '}':
    return Token(TokenType::CLOSECURLY);
  case '[':
    return Token(TokenType::OPENBRACKET);
  case ']':
    return Token(TokenType::CLOSEBRACKET);

  default:
    return Token(TokenType::ILLEGAL, std::string(1, input[rc++]));
    break;
  }
  if (isDigit(input[rc])) {
    while (isDigit(input[rc]) && rc != input.length()) {
      literal += input[rc]; // this concatenate the digit to the literal string.
      rc++;                 // maybe it would be better to use substring? idk.
    }
    return Token(TokenType::INT, literal);
  }
  if (isLetter(input[rc])) {
    while ((isLetter(input[rc]) || isDigit(input[rc])) &&
           rc != input.length()) {
      literal += input[rc];
      rc++;
    }
    if (keywords.find(literal) != keywords.end()) {
      return Token(keywords[literal], literal);
    }
    return Token(TokenType::IDENT, literal);
  }
  return Token(TokenType::ILLEGAL, std::string(1, input[rc++]));
}

/*
  u can use the lexer in your own project (probably u wont T-T).
  to use this lexer in your own project, you can do something like this:
  fileManager file("input.txt");
  std::string input = file.read();
  Lexer lexer(input);
  while (true) {
    token t = lexer.nextToken();

    then use t for what the fuck you want.
 }
*/

// example code below to test the lexer.
/*
int main() {
  fileManager file("input.txt");
  std::string input = file.read();
  Lexer lexer(input);
  while (true) {
    token t = lexer.nextToken();

    std::cout << "[Type] " << t.getType()
              << ((((int)t.getType()) < 10) ? "  " : " ") << " | [Literal] "
              << t.getLiteral() << std::endl;
    if (t.getType() == tokenType::ENDOF) {
      break;
    }
  }
  return 0;
}
*/