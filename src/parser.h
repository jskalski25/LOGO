/** @file */

#ifndef PARSER_H
#define PARSER_H

#include "common.h"
#include "scanner.h"
#include "token.h"
#include "ast.h"

/** Klasa buduje AST z tokenów od Scannera. */
class Parser {
private:
  Scanner* scanner; ///< wykorzystywany Scanner

/** Wywołuje metodę Scannera.
@return wskaźnik do aktualnego tokena */
  std::shared_ptr<Token> current_token();

/** Wywołuje metodę Scannera.
@return wskaźnik do następnego tokena */
  std::shared_ptr<Token> next_token();

/** Sprawdza czy token jest danego typu.
  * Jeżeli to prawda, przechodzi do następnego inaczej, wywołuje błąd.
@param type spodziewany typ tokena */
  void match(int type);

/** Zakańcza działanie programu i wypisuje wiadomość błędu. */
  void syntax_error();

public:

/** Tworzy Parser ze Scannera.
@param s użyty Scanner */
  Parser(Scanner* s);

/** Parsuje kolejne komórki drzewa.
@return wskaźnik utworzonej komórki */
  std::shared_ptr<AbstractNode> id();
/** Parsuje kolejne komórki drzewa.
@return wskaźnik utworzonej komórki */
  std::shared_ptr<AbstractNode> variable();
/** Parsuje kolejne komórki drzewa.
@return wskaźnik utworzonej komórki */
  std::shared_ptr<AbstractNode> factor();
/** Parsuje kolejne komórki drzewa.
@return wskaźnik utworzonej komórki */
  std::shared_ptr<AbstractNode> expression();
/** Parsuje kolejne komórki drzewa.
@return wskaźnik utworzonej komórki */
  std::shared_ptr<AbstractNode> logic_expr();
/** Parsuje kolejne komórki drzewa.
@return wskaźnik utworzonej komórki */
  std::shared_ptr<AbstractNode> arguments();
/** Parsuje kolejne komórki drzewa.
@return wskaźnik utworzonej komórki */
  std::shared_ptr<AbstractNode> end();
/** Parsuje kolejne komórki drzewa.
@return wskaźnik utworzonej komórki */
  std::shared_ptr<AbstractNode> block();
/** Parsuje kolejne komórki drzewa.
@param token token if
@return wskaźnik utworzonej komórki */
  std::shared_ptr<AbstractNode> if_block(std::shared_ptr<Token> token);
/** Parsuje kolejne komórki drzewa.
@param token nazwa polecenia
@return wskaźnik utworzonej komórki */
  std::shared_ptr<AbstractNode> key_state(std::shared_ptr<Token> token);
/** Parsuje kolejne komórki drzewa.
@param head argumenty procedury
@return wskaźnik utworzonej komórki */
  std::shared_ptr<AbstractNode> proc_def(std::shared_ptr<AbstractNode> head);
/** Parsuje kolejne komórki drzewa.
@param token nazwa procedury
@return wskaźnik utworzonej komórki */
  std::shared_ptr<AbstractNode> proc_call(std::shared_ptr<Token> token);
/** Parsuje kolejne komórki drzewa.
@return wskaźnik utworzonej komórki */
  std::shared_ptr<AbstractNode> statement();
/** Parsuje kolejne komórki drzewa.
@return wskaźnik utworzonej komórki */
  std::shared_ptr<AbstractNode> program();

/** Parsuje kod źródłowy i zwraca utworzone AST.
@return początek drzewa */
  std::shared_ptr<AbstractNode> parse();
};

#endif
