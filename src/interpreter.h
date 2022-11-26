/** @file */

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "visitor.h"
#include "parser.h"
#include "scanner.h"
#include "char_stream.h"
#include "procedures.h"
#include "variables.h"

/** Interpreter kodu w postaci AST.
  * Tworzy obiekt ProcCallera przy wywołaniu procedury. */
class Interpreter : public Visitor {
private:
  double res;                     ///< wynik ostatniego działania
  bool con;                       ///< wartość ostatniej kondycji
  std::shared_ptr<Procedures> p;  ///< vector zdefiniowanych procedur
  ICode* prog;                    ///< trasa żółwia
  InputValues ivalues;            ///< vector wartości parametrów procedury
public:
/** Copy constructor.
  * Kopiuje liste procedur i przekazuje wskaźnik żółwia
@param old źródłowy interpreter */
  Interpreter(const Interpreter& old)
    : p(std::make_shared<Procedures>(*old.p))
    , prog(old.prog) {}
/** Constructor. */
  Interpreter() {}
/** Odwiedza po kolei wszystkie dzieci programu.
@param program komórka drzewa */
  void visit(Program* program);
/** Wykonuje polecenie dla żółwia.
@param statement komórka drzewa */
  void visit(KeyStatement* statement);
/** Tworzy ProcCallera dla procedury.
@param proccall komórka drzewa */
  void visit(ProcCall* proccall);
/** Zapisuje procedure do vectora.
@param procdef komórka drzewa */
  void visit(ProcDef* procdef);
/** Jeżeli kondycja się sprawdzi to przechodzi do bloku.
@param ifblock komórka drzewa */
  void visit(IfBlock* ifblock);
/** Odwiedza po kolei wszystkie dzieci bloku.
@param block komórka drzewa */
  void visit(Block* block);
/** Nic nie robi.
@param end komórka drzewa */
  void visit(End* end);
/** Wypełnia vector wartości parametrów procedury.
@param args komórka drzewa */
  void visit(Arguments* args);
/** Interpretuje dzialania logiczne, rezultat zapisuje do zmiennej con.
@param logexp komórka drzewa */
  void visit(LogicExpr* logexp);
/** Interpretuje dzialania, rezultat zapisuje do zmiennej res.
@param binexp komórka drzewa */
  void visit(BinaryExpr* binexp);
/** Rzutuje zawartosc tokena do typu double, rezultat zapisuje do res.
@param factor komórka drzewa */
  void visit(Number* number);
/** Nic nie robi. Powinno powodować błąd.
@param variable komórka drzewa */
  void visit(Variable* variable);
/** Nic nie robi.
@param identifier komórka drzewa */
  void visit(Identifier* identifier);

/** Zwraca wynik ostatniego działania.
@return wynik ostatniego działania */
  double get_res() { return res; }

/** Zmienia wynik ostatniego działania.
@param r nowy wynik */
  void set_res(double r) { res = r; }

/** Zwraca wynik ostatniego działania.
@return wynik ostatniego działania */
  bool get_con() { return con; }

/** Zmienia wynik ostatniego działania.
@param b nowy wynik */
  void set_con(bool b) { con = b; }

/** Parsuje kod źródłowy następnie intepretuje zbudowane AST
  * mapując trasę żółwia do struktury.
@param input kod źródłowy
@param program trasa żółwia */
  void interpret(std::istream* input, ICode* program);
};

/** Interpreter który służy do porównywania wartości i nazw argumentów. */
class VarWalker : public Interpreter {
private:
  VarNames names; ///< vector nazw argumentów
  std::string id; ///< nazwa ostatniego argumentu
public:
/** Przechodzi po argumentach i zapisuje ich wartości.
@param node początel definicji procedury
@param iv vector wartości argumentów
@return sparowane nazwy i wartości argumentów */
  std::shared_ptr<Variables> walk(AbstractNode* node, InputValues* iv);

/** Odwiedza listę argumentów, oczekuje nazw zamiast wartości.
@param args komórka drzewa */
  void visit(Arguments* args);
/** Odwiedza nazwy zmiennych i ustawia zmienną id.
@param var komórka drzewa */
  void visit(Variable* var);
};

/** Interpreter wyspecjalizowany dla procedur. */
class ProcCaller : public Interpreter {
private:
  std::shared_ptr<Variables> locals; ///< argumenty procedury
public:
/** Kopiuje wartości z poprzedniego interpretera
@param old poprzedni interpreter */
  ProcCaller(const Interpreter& old)
    : Interpreter(old) {}
/** Wywołuje procedurę.
@params node definicja procedury
@params iv wartości argumentów */
  void call(AbstractNode* node, InputValues* iv);
/** Przy odwiedzeniu zmiennej wstawia jej wartość na jej miejsce.
@param variable komórka drzewa */
  void visit(Variable* variable);
};

// program.h
extern void forward(ICode*, double);
extern void back(ICode*, double);
extern void left(ICode*, double);
extern void right(ICode*, double);

#endif
