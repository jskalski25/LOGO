/** @file */

#ifndef AST_H
#define AST_H

#include "common.h"
#include "token.h"
#include "visitor.h"

/** Komórka AST */
class AbstractNode {
public:

/** Wywołuje metodę visitora visit na samej siebie.
@param visitor wskaźnik do visitora */
  virtual void accept(Visitor* visitor) = 0;

/** Tworzy komórkę z tokena.
@param token wskaźnik do tokena */
  AbstractNode(std::shared_ptr<Token> token)
    : token(token) {}

/** Dodaje dziecko do vectora.
@param child komórka do dodania */
  void add_child(std::shared_ptr<AbstractNode> child) {
    children.push_back(child);
  }

  std::shared_ptr<Token> token;                         ///< token komórki
  std::vector<std::shared_ptr<AbstractNode>> children;  ///< vector dzieci
};

/** Komórka typu Program, początek drzewa. */
class Program : public AbstractNode {
public:
/** Implementacja schematu visitora.
@param visitor wskaźnik do visitora */
  void accept(Visitor* visitor);
/** Tworzy komórkę z pustym tokenem. */
  Program()
    : AbstractNode(std::make_shared<Token>()) {}
};

/** Komórka typu KeyStatement, polecenie dla żółwia. */
class KeyStatement : public AbstractNode {
public:
/** Implementacja schematu visitora.
@param visitor wskaźnik do visitora */
  void accept(Visitor*);
/** Tworzy komórkę z tokena.
@param token treść polecenia dla żółwia */
  KeyStatement(std::shared_ptr<Token> token)
    : AbstractNode(token) {}
};

/** Komórka typu ProcCall, wywołanie procedury lub początek definicji. */
class ProcCall : public AbstractNode {
public:
/** Implementacja schematu visitora.
@param visitor wskaźnik do visitora */
  void accept(Visitor*);
/** Tworzy komórkę z tokena.
@param token nazwa procedury */
  ProcCall(std::shared_ptr<Token> token)
    : AbstractNode(token) {}
};

/** Komórka typu ProcDef, definicja funkcji. */
class ProcDef : public AbstractNode {
public:
/** Implementacja schematu visitora.
@param visitor wskaźnik do visitora */
  void accept(Visitor*);
/** Tworzy komórkę z tokena.
@param token nazwa procedury */
  ProcDef(std::shared_ptr<Token> token)
    : AbstractNode(token) {}
};

/** Komórka typu IfBlock, połączenie kondycji jeżeli oraz jej bloku.  */
class IfBlock : public AbstractNode {
public:
/** Implementacja schematu visitora.
@param visitor wskaźnik do visitora */
  void accept(Visitor*);
/** Tworzy komórkę z tokena.
@param token token if */
  IfBlock(std::shared_ptr<Token> token)
    : AbstractNode(token) {}
};

/** Komórka typu Block, lista poleceń zakończona przez End. */
class Block : public AbstractNode {
public:
/** Implementacja schematu visitora.
@param visitor wskaźnik do visitora */
  void accept(Visitor*);
/** Tworzy komórkę z pustym tokenem. */
  Block()
    : AbstractNode(std::make_shared<Token>()) {}
};

/** Komórka typu End, zakończenie bloku. */
class End : public AbstractNode {
public:
/** Implementacja schematu visitora.
@param visitor wskaźnik do visitora */
  void accept(Visitor*);
/** Tworzy komórkę z tokena.
@param token nazwa zakończonej definicji lub if */
  End(std::shared_ptr<Token> token)
    : AbstractNode(token) {}
};

/** Komórka typu Arguments, lista argumentów podzielonych przecinkami. */
class Arguments : public AbstractNode {
public:
/** Implementacja schematu visitora.
@param visitor wskaźnik do visitora */
  void accept(Visitor*);
/** Tworzy komórkę z pustym tokenem. */
  Arguments()
    : AbstractNode(std::make_shared<Token>()) {}
};

/** Komórka typu LogicExpr, działanie logiczne spośród <, >, =, <>. */
class LogicExpr : public AbstractNode {
public:
/** Implementacja schematu visitora.
@param visitor wskaźnik do visitora */
  void accept(Visitor*);
/** Tworzy komórkę z tokena.
@param token typ działania */
  LogicExpr(std::shared_ptr<Token> token)
    : AbstractNode(token) {}
};

/** Komórka typu BinaryExpr, działania spośród +, -, *. */
class BinaryExpr : public AbstractNode {
public:
/** Implementacja schematu visitora.
@param visitor wskaźnik do visitora */
  void accept(Visitor*);
/** Tworzy komórkę z tokena.
@param token typ działania */
  BinaryExpr(std::shared_ptr<Token> token)
    : AbstractNode(token) {}
};

/** Komórka typu Number, liczba zmiennoprzecinkowa. */
class Number : public AbstractNode {
public:
/** Implementacja schematu visitora.
@param visitor wskaźnik do visitora */
  void accept(Visitor*);
/** Tworzy komórkę z tokena.
@param token liczba w postaci tekstu */
  Number(std::shared_ptr<Token> token)
    : AbstractNode(token) {}
};

/** Komórka typu Variable, zmienna. */
class Variable : public AbstractNode {
public:
/** Implementacja schematu visitora.
@param visitor wskaźnik do visitora */
  void accept(Visitor*);
/** Tworzy komórkę z tokena.
@param token nazwa zmiennej */
  Variable(std::shared_ptr<Token> token)
    : AbstractNode(token) {}
};

/** Komórka typu Identifier, nazwa procedury. */
class Identifier : public AbstractNode {
public:
/** Implementacja schematu visitora.
@param visitor wskaźnik do visitora */
  void accept(Visitor*);
/** Tworzy komórkę z tokena.
@param token nazwa procedury */
  Identifier(std::shared_ptr<Token> token)
    : AbstractNode(token) {}
};

#endif
