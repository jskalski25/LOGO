#include "parser.h"

Parser::Parser(Scanner* s) {
  scanner = s;
}

std::shared_ptr<Token> Parser::current_token() {
  return scanner->current_token();
}

std::shared_ptr<Token> Parser::next_token() {
  return scanner->next_token();
}

void Parser::match(int type) {
  if (current_token()->type == type) {
    next_token();
  } else {
    syntax_error();
  }
}

void Parser::syntax_error() {
  std::shared_ptr<Token> token = current_token();
  std::cerr << "\nParser error at " << token->row
    << ":" << token->col << " unexpected token \""
    << token->text << "\".\n";
  std::cerr << "Full line:\n" << scanner->current_line() << "\n";
  for (int i = 0; i < token->col-1; ++i) {
    std::cout << '~';
  }
  std::cout << "^\n";
  exit(1);
}

std::shared_ptr<AbstractNode> Parser::id() {
  std::shared_ptr<Token> token = current_token();
  match(Token::Alpha);
  return std::make_shared<Identifier>(token);
}

std::shared_ptr<AbstractNode> Parser::variable() {
  std::shared_ptr<Token> token = current_token();
  match(Token::Alpha);
  return std::make_shared<Variable>(token);
}

std::shared_ptr<AbstractNode> Parser::factor() {
  std::shared_ptr<Token> token = current_token();
  if (token->type == Token::Number) {
    match(Token::Number);
    return std::make_shared<Number>(token);
  }
  else {
    return variable();
  }
}

std::shared_ptr<AbstractNode> Parser::expression() {
  std::shared_ptr<AbstractNode> root = factor();

  std::shared_ptr<Token> op = current_token();
  if (op->type == Token::Plus || op->type == Token::Minus ||
    op->type == Token::Mul) {
    match(op->type);
    auto left = root;
    auto right = factor();
    root = std::make_shared<BinaryExpr>(op);
    root->add_child(left);
    root->add_child(right);
  }

  return root;
}

std::shared_ptr<AbstractNode> Parser::logic_expr() {
  std::shared_ptr<AbstractNode> root = factor();

  std::shared_ptr<Token> op = current_token();
  if (op->type == Token::GSign
    || op->type == Token::LSign
    || op->type == Token::ESign
    || op->type == Token::DSign) {
    match(op->type);
  } else {
    syntax_error();
  }

  auto left = root;
  auto right = factor();
  root = std::make_shared<LogicExpr>(op);
  root->add_child(left);
  root->add_child(right);

  return root;
}

std::shared_ptr<AbstractNode> Parser::arguments() {
  std::shared_ptr<AbstractNode> root = std::make_shared<Arguments>();
  if (current_token()->type == Token::Number
    || current_token()->type == Token::Alpha) {
    root->add_child(expression());
    while (current_token()->type == Token::Comma) {
      match(Token::Comma);
      root->add_child(expression());
    }
  }
  return root;
}

std::shared_ptr<AbstractNode> Parser::end() {
  std::shared_ptr<Token> token = current_token();
  match(Token::Alpha);
  std::shared_ptr<AbstractNode> root = std::make_shared<End>(token);
  root->add_child(id());
  return root;
}

std::shared_ptr<AbstractNode> Parser::block() {
  std::shared_ptr<AbstractNode> root = std::make_shared<Block>();
  while (current_token()->text != "end") {
    root->add_child(statement());
  }
  root->add_child(end());
  return root;
}

std::shared_ptr<AbstractNode> Parser::if_block(std::shared_ptr<Token> token) {
  std::shared_ptr<AbstractNode> root = std::make_shared<IfBlock>(token);
  match(Token::LParen);
  root->add_child(logic_expr());
  match(Token::RParen);
  root->add_child(block());
  return root;
}

std::shared_ptr<AbstractNode> Parser::key_state(std::shared_ptr<Token> token) {
  std::shared_ptr<AbstractNode> root = std::make_shared<KeyStatement>(token);
  match(Token::LParen);
  root->add_child(expression());
  match(Token::RParen);
  return root;
}

std::shared_ptr<AbstractNode> Parser::proc_def(
  std::shared_ptr<AbstractNode> head) {
  std::shared_ptr<AbstractNode> root = std::make_shared<ProcDef>(head->token);
  root->add_child(head);
  root->add_child(block());
  return root;
}

std::shared_ptr<AbstractNode> Parser::proc_call(std::shared_ptr<Token> token) {
  std::shared_ptr<AbstractNode> root = std::make_shared<ProcCall>(token);
  match(Token::LParen);
  root->add_child(arguments());
  match(Token::RParen);
  return root;
}

std::shared_ptr<AbstractNode> Parser::statement() {
  std::shared_ptr<Token> token = current_token();
  std::shared_ptr<AbstractNode> root;
  if (token->text == "end") {
    syntax_error();
  }
  else {
    match(Token::Alpha);
    if (token->text == "if") {
      root = if_block(token);
    }
    else if (token->text == "forward" || token->text == "back" ||
      token->text == "left" || token->text == "right") {
      root = key_state(token);
    }
    else {
      root = proc_call(token);
      if (current_token()->type != Token::Semi) {
        root = proc_def(root);
      }
    }
  }
  match(Token::Semi);
  return root;
}

std::shared_ptr<AbstractNode> Parser::program() {
  std::shared_ptr<AbstractNode> root = std::make_shared<Program>();
  while (current_token()->type != EOF) {
    root->add_child(statement());
  }
  return root;
}

std::shared_ptr<AbstractNode> Parser::parse() {
  std::shared_ptr<AbstractNode> root = program();
  return root;
}
