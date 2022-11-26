/** @file */

#ifndef TOKEN_H
#define TOKEN_H

/** Reprezentacja tokena do celów parsera i interpretacji programu. */
struct Token {

/** Kategoria zawartości tokena. */
  enum TokenType {
    None = 256, Number, Plus, Minus, Mul, LParen, RParen, Semi,
    GSign, LSign, ESign, DSign, Comma, Alpha
  };

/** Tworzy czysty token. */
  Token()
    : text("")
    , row(1)
    , col(1)
    , type(None) {}

/** Tworzy Token z argumentów.
@param text zawartość tokena
@param row  znak występowania tokena
@param col  linia występowania tokena
@param type kategoria zawartości tokena */
  Token(const std::string& text, int row, int col, int type)
    : text(text)
    , row(row)
    , col(col)
    , type(type) {}

  std::string text; ///< zawartość tokena
  int row;          ///< znak występowania tokena
  int col;          ///< linia występowania tokena
  int type;         ///< kategoria zawartości tokena
};

#endif
