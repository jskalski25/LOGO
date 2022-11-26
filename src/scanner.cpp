#include "scanner.h"

Scanner::Scanner(CharStream* cs) {
  char_stream = cs;
  next_token();
}

void Scanner::init_token() {
  token = std::make_shared<Token>("",
    char_stream->current_row(),
    char_stream->current_col(),
    Token::None);
}

void Scanner::enter_char() {
  token->text.append(1, current_char());
}

void Scanner::set_text(std::string text) {
  token->text = text;
}

void Scanner::set_type(int type) {
  token->type = type;
}

void Scanner::skip_whitespace() {
  while (std::isspace(current_char())) {
    next_char();
  }
}

std::shared_ptr<Token> Scanner::current_token() {
  return token;
}

std::shared_ptr<Token> Scanner::next_token() {
  skip_whitespace();
  init_token();
  char ch = current_char();
  if (char_stream->is_eof()) {
    set_type(EOF);
    set_text("EOF");
  }
  else if (std::isdigit(ch)) {
    number_literal();
  }
  else if (std::isalpha(ch)) {
    id();
  }
  else if (ch == '+') {
    set_type(Token::Plus);
    enter_char();
    next_char();
  }
  else if (ch == '-') {
    set_type(Token::Minus);
    enter_char();
    next_char();
  }
  else if (ch == '*') {
    set_type(Token::Mul);
    enter_char();
    next_char();
  }
  else if (ch == '(') {
    set_type(Token::LParen);
    enter_char();
    next_char();
  }
  else if (ch == ')') {
    set_type(Token::RParen);
    enter_char();
    next_char();
  }
  else if (ch == ';') {
    set_type(Token::Semi);
    enter_char();
    next_char();
  }
  else if (ch == '>') {
    set_type(Token::GSign);
    enter_char();
    next_char();
  }
  else if (ch == '<') {
    set_type(Token::LSign);
    enter_char();
    next_char();
    ch = current_char();
    if (ch == '>') {
      set_type(Token::DSign);
      enter_char();
      next_char();
    }
  }
  else if (ch == '=') {
    set_type(Token::ESign);
    enter_char();
    next_char();
  }
  else if (ch == ',') {
    set_type(Token::Comma);
    enter_char();
    next_char();
  }
  else {
    syntax_error();
  }
  std::cout << token->text << " ";
  return token;
}

void Scanner::integer_literal() {
  while (std::isdigit(current_char())) {
    enter_char();
    next_char();
  }
}

void Scanner::number_literal() {
  set_type(Token::Number);
  integer_literal();
  if (current_char() == '.') {
    enter_char();
    next_char();
    if (std::isdigit(current_char())) {
      integer_literal();
    }
    else {
      syntax_error();
    }
  }
}

void Scanner::id() {
  set_type(Token::Alpha);
  while (std::isalnum(current_char())) {
    enter_char();
    next_char();
  }
}

void Scanner::syntax_error() {
  std::cerr << "\nScanner error at " << char_stream->current_row()
    << ":" << char_stream->current_col() << " unexpected char \""
    << char_stream->current_char() << "\".\n";
  std::cerr << "Full line:\n" << char_stream->current_line() << "\n";
  for (int i = 0; i < char_stream->current_col()-1; ++i) {
    std::cout << '~';
  }
  std::cout << "^\n";
  exit(1);
}

char Scanner::current_char() {
  return char_stream->current_char();
}

char Scanner::next_char() {
  return char_stream->next_char();
}

char Scanner::peek() {
  return char_stream->peek();
}

std::string Scanner::current_line() {
  return char_stream->current_line();
}
