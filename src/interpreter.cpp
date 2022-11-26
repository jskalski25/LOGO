#include "interpreter.h"

void Interpreter::visit(Program* program) {
  std::cout << "visited program" << "\n";

  for (auto& child : program->children) {
    child->accept(this);
  }
}

void Interpreter::visit(KeyStatement* statement) {
  std::cout << "visited " << statement->token->text << "\n";

  statement->children[0]->accept(this);

  std::cout << "executing " << statement->token->text << " (" << res << ")\n";

  if (statement->token->text == "forward") {
    forward(prog, res);
  } else if (statement->token->text == "back") {
    back(prog, res);
  } else if (statement->token->text == "left") {
    left(prog, res);
  } else if (statement->token->text == "right") {
    right(prog, res);
  }
}

void Interpreter::visit(ProcCall* proccall) {
  std::cout << "visited " << proccall->token->text << " call\n";

  proccall->children[0]->accept(this);

  ProcCaller pcaller(*this);
  pcaller.call(p->get_proc(proccall->token->text), &ivalues);
}

void Interpreter::visit(ProcDef* procdef) {
  std::cout << "visited " << procdef->token->text << " definition\n";

  p->add_proc(procdef->token->text, procdef);
}

void Interpreter::visit(IfBlock* ifblock) {
  std::cout << "visited " << ifblock->token->text << "\n";

  ifblock->children[0]->accept(this);

  if (con) {
    ifblock->children[1]->accept(this);
  }
}

void Interpreter::visit(Block* block) {
  std::cout << "visited block" << "\n";

  for (auto& child : block->children) {
    child->accept(this);
  }
}

void Interpreter::visit(End* end) {
  std::cout << "visited " << end->token->text
    << " of " << end->children[0]->token->text << "\n";
}

void Interpreter::visit(Arguments* args) {
  std::cout << "visited arguments\n";

  ivalues.clear();
  for (auto& child : args->children) {
    child->accept(this);
    ivalues.push_back(res);
  }
}

void Interpreter::visit(LogicExpr* logexp) {
  std::cout << "visited " << logexp->token->text << "\n";

  logexp->children[0]->accept(this);
  double a = res;
  logexp->children[1]->accept(this);
  double b = res;

  if (logexp->token->type == Token::GSign) {
    con = a > b;
  } else if (logexp->token->type == Token::LSign) {
    con = a < b;
  } else if (logexp->token->type == Token::ESign) {
    con = a == b;
  } else if (logexp->token->type == Token::DSign) {
    con = a != b;
  }
}

void Interpreter::visit(BinaryExpr* binexp) {
  std::cout << "visited " << binexp->token->text << "\n";

  binexp->children[0]->accept(this);
  double a = res;
  binexp->children[1]->accept(this);
  double b = res;

  if (binexp->token->type == Token::Plus) {
    res = a + b;
  } else if (binexp->token->type == Token::Minus) {
    res = a - b;
  } else if (binexp->token->type == Token::Mul) {
    res = a * b;
  }

  std::cout << "evaluated " << a << " " << binexp->token->text
    << " " << b << " to " << res << "\n";
}

void Interpreter::visit(Number* number) {
  std::cout << "visited " << number->token->text << "\n";

  res = std::stod(number->token->text);
}

void Interpreter::visit(Variable* variable) {
  std::cout << "visited " << variable->token->text << "\n";
}

void Interpreter::visit(Identifier* identifier) {
  std::cout << "visited " << identifier->token->text << "\n";
}

void Interpreter::interpret(std::istream* input, ICode* program) {
  std::cout << "parsing input...\n";
  CharStream char_stream(input);
  Scanner scanner(&char_stream);
  Parser parser(&scanner);

  p = std::make_shared<Procedures>();

  prog = program;

  std::shared_ptr<AbstractNode> root = parser.parse();
  std::cout << "\n";

  std::cout << "interpreting abstract syntax tree...\n";
  root.get()->accept(this);

  std::cout << "procedure names: ";
  p->read_names();

  std::cout << "DONE\n";
}

std::shared_ptr<Variables> VarWalker::walk(AbstractNode* node, InputValues* iv) {
  std::cout << "walking " << node->token->text << " args\n";

  node->children[0]->accept(this);

  std::shared_ptr<Variables> vars = std::make_shared<Variables>(iv, &names);

  return vars;
}

void VarWalker::visit(Arguments* args) {
  std::cout << "visited arg names\n";

  names.clear();
  for (auto& child : args->children) {
    child->accept(this);
    names.push_back(id);
  }
}

void VarWalker::visit(Variable* var) {
  std::cout << "visited " << var->token->text << "\n";
  id = var->token->text;
}

void ProcCaller::call(AbstractNode* node, InputValues* iv) {
  std::cout << "calling " << node->token->text << "\n";

  VarWalker vwalker;
  locals = vwalker.walk(node->children[0].get(), iv);

  std::cout << "with args ";

  locals->read_vars();

  node->children[1]->accept(this);
}

void ProcCaller::visit(Variable* variable) {
  std::cout << "visited " << variable->token->text << "\n";

  set_res(locals->get(variable->token->text));

  std::cout << "matched " << variable->token->text << " with "
    << get_res() << "\n";
}
