/** @file */

#include "common.h"
#ifndef CHAR_STREAM_H
#define CHAR_STREAM_H

/** Klasa zajmująca się extrakcją znaków ze streamu. */
class CharStream {

private:

  std::istream* src;  ///< stream źródłowy
  unsigned row;       ///< aktualny wiersz kodu
  unsigned col;       ///< aktualna kolumna kodu
  std::string line;   ///< aktualna linia kodu

public:

/** Tworzy objekt z istniejącego źródła.
@param is stream źródłowy */
  CharStream(std::istream* is);

/** Zwraca aktualny znak.
@return aktualny znak */
  char current_char();

/** Przechodzi do następnego znaku i zwraca go.
@return następny znak */
  char next_char();

/** Zwraca następny znak bez przechodzenia do niego.
@return następny znak */
  char peek();

/** Zwraca aktualny wiersz kodu.
@return aktualny wiersz */
  int current_row();

/** Zwraca aktualną kolumnę kodu.
@return aktualna kolumna */
  int current_col();

/** Zwraca aktualną linijkę kodu.
@return aktualna linia */
  std::string current_line();

/** Sprawdza czy nastąpił koniec kodu.
@return stan EOF streama źródłowego */
  bool is_eof();

/** Przechodzi do następnego wiersza kodu.
  * Pomija puste wiersze. */
  void adv_row();

/** Przechodzi do następnej kolumny kodu.
  * Jeżeli nie zostało więcej znaków w linijce, wywołuje adv_row(). */
  void adv_col();

};

#endif
