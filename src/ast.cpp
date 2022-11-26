#include "ast.h"

void Program::accept(Visitor* visitor) {
  visitor->visit(this);
}

void KeyStatement::accept(Visitor* visitor) {
  visitor->visit(this);
}

void ProcCall::accept(Visitor* visitor) {
  visitor->visit(this);
}

void ProcDef::accept(Visitor* visitor) {
  visitor->visit(this);
}

void IfBlock::accept(Visitor* visitor) {
  visitor->visit(this);
}

void Block::accept(Visitor* visitor) {
  visitor->visit(this);
}

void End::accept(Visitor* visitor) {
  visitor->visit(this);
}

void Arguments::accept(Visitor* visitor) {
  visitor->visit(this);
}

void LogicExpr::accept(Visitor* visitor) {
  visitor->visit(this);
}

void BinaryExpr::accept(Visitor* visitor) {
  visitor->visit(this);
}

void Number::accept(Visitor* visitor) {
  visitor->visit(this);
}

void Variable::accept(Visitor* visitor) {
  visitor->visit(this);
}

void Identifier::accept(Visitor* visitor) {
  visitor->visit(this);
}
