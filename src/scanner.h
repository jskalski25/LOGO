/** @file */

#ifndef SCANNER_H
#define SCANNER_H

#include "common.h"
#include "char_stream.h"
#include "token.h"

/** Klasa wykorzystuje CharStream do extrakcji tokenów z pliku. */
class Scanner {
private:
  CharStream* char_stream;      ///< kod źródłowy
  std::shared_ptr<Token> token; ///< wskaźnik do aktualnego tokena

/** Wymienia aktualny token na nowy. */
  void init_token();

/** Dodaje aktualny znak z kodu do tekstu tokena. */
  void enter_char();

/** Zamienia tekst tokena.
@param text nowy tekst tokena */
  void set_text(std::string text);

/** Zamienia typ tokena.
@param type nowy typ tokena */
  void set_type(int type);

/** Skanuje następną liczbę całkowitą. */
  void integer_literal();

/** Skanuje następną liczbę zmiennoprzecinkową. */
  void number_literal();

/** Skanuje następne słowo. */
  void id();

/** Zakańcza działanie programu i wypisuje wiadomość błędu. */
  void syntax_error();

public:

/** Tworzy Scanner z CharStreama.
@param cs wskaźnik do CharStreama */
  Scanner(CharStream* cs);

/** Zwraca wskaźnik do aktualnego tokena.
@return wskaźnik do aktualnego tokena */
  std::shared_ptr<Token> current_token();

/** Analizuje następny token ze źródła.
@return wskaźnik do następnego tokena */
  std::shared_ptr<Token> next_token();

/** Pomija znaki białe do oporu. */
  void skip_whitespace();

/** Wywołuje metodę CharStreama.
@return aktualny znak ze źródła */
  char current_char();

/** Wywołuje metodę CharStreama.
@return następny znak ze źródła */
  char next_char();

/** Wywołuje metodę CharStreama.
@return następny znak ze źródła */
  char peek();

/** Wywołuje metodę CharStreama.
@return aktualna linia ze źródła */
  std::string current_line();

};

#endif
