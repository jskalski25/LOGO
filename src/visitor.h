/** @file */

#ifndef VISITOR_H
#define VISITOR_H

class Program;
class KeyStatement;
class ProcCall;
class ProcDef;
class IfBlock;
class Block;
class End;
class Arguments;
class LogicExpr;
class BinaryExpr;
class Number;
class Variable;
class Identifier;

/** Abstrakcyjna klasa visitora, ktory odwiedza kolejne elementy AST
  * metodą w głąb. */
class Visitor {
public:
/** Odwiedza komórkę drzewa. */
  virtual void visit(Program*)      = 0;
/** Odwiedza komórkę drzewa. */
  virtual void visit(KeyStatement*) = 0;
/** Odwiedza komórkę drzewa. */
  virtual void visit(ProcCall*)     = 0;
/** Odwiedza komórkę drzewa. */
  virtual void visit(ProcDef*)      = 0;
/** Odwiedza komórkę drzewa. */
  virtual void visit(IfBlock*)      = 0;
/** Odwiedza komórkę drzewa. */
  virtual void visit(Block*)        = 0;
/** Odwiedza komórkę drzewa. */
  virtual void visit(End*)          = 0;
/** Odwiedza komórkę drzewa. */
  virtual void visit(Arguments*)    = 0;
/** Odwiedza komórkę drzewa. */
  virtual void visit(LogicExpr*)    = 0;
/** Odwiedza komórkę drzewa. */
  virtual void visit(BinaryExpr*)   = 0;
/** Odwiedza komórkę drzewa. */
  virtual void visit(Number*)       = 0;
/** Odwiedza komórkę drzewa. */
  virtual void visit(Variable*)     = 0;
/** Odwiedza komórkę drzewa. */
  virtual void visit(Identifier*)   = 0;
};

#endif
