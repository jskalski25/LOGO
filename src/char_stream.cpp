#include "char_stream.h"

CharStream::CharStream(std::istream* is) {
  src = is;
  row = 0;
  col = 1;
  adv_row();
}

char CharStream::current_char() {
  return line[col-1];
}

char CharStream::next_char() {
  adv_col();
  return current_char();
}

char CharStream::peek() {
  if (col < line.length()) {
    return line[col];
  }
  return 0;
}

int CharStream::current_row() {
  return row;
}

int CharStream::current_col() {
  return col;
}

std::string CharStream::current_line() {
  return line;
}

void CharStream::adv_row() {
  ++row;
  col = 1;
  std::getline(*src, line);
  if (col >= line.length() && !is_eof()) {
    adv_row();
  }
}

bool CharStream::is_eof() {
  return src->eof();
}

void CharStream::adv_col() {
  if (col < line.length()) {
    ++col;
  }
  else {
    adv_row();
  }
}
