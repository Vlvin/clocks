#include "headers/Executioner.h"
#include "headers/Interpreter.h"
#include "headers/Clockswork.h"
#include "headers/Parser.h"
#include "headers/Scanner.h"
#include "headers/Resolver.h"
#include "headers/Token.h"

#include <fstream>
#include <strstream>

Executioner::Executioner() : interpreter(std::make_shared<Interpreter>()) {
  this->interpreterMustBeRenewed = true;
  this->lastError = "";
}

void Executioner::runFile(std::string path) {
  fstream file(path, ios::in);
    
  if (!file.is_open()) {
      cout << "LoxError: no such file\n";
      return;
  }
  string text( (std::istreambuf_iterator<char>(file) ),
                (std::istreambuf_iterator<char>()    ) );;

  if (interpreterMustBeRenewed) 
    this->interpreter = std::make_shared<Interpreter>();
  run(path, text);
  if (Clockwork::hadError) return;
  if (Clockwork::hadRuntimeError) return;
}

void Executioner::runPromt() {
  char cline[64];
  if (interpreterMustBeRenewed) 
    this->interpreter = std::make_shared<Interpreter>();
  for(;;) {
    cout << "\nlox >> ";
    cin.getline(cline,64);
    if (!std::string("exit").compare(cline)) break;
    run("promt", cline);
    if (Clockwork::hadError || Clockwork::hadRuntimeError) 
      std::cout << "Error: " << lastError << '\n';
    Clockwork::hadError = false;
    Clockwork::hadRuntimeError = false;
  }
  Clockwork::hadError = false;
  Clockwork::hadRuntimeError = false;
}

void Executioner::run(std::string modulename, std::string source) {
  Scanner scanner(source);
  vector<Token> tokens = scanner.scanTokens(modulename);
  vector<Stmt*> statements = {};
  Parser parser(tokens);

  try {
    statements = parser.parse(modulename);
  } catch (ParseError error) {
    std::strstream errorstr;
    errorstr << "In [" << modulename << "]: Failed to parse source code";
    lastError = errorstr.str();
  }

  if (Clockwork::hadError) return;
  if (std::weak_ptr<Interpreter>(interpreter).lock()) {
    Resolver resolver(interpreter.get());
    resolver.resolve(modulename, statements);    
    try {
      interpreter->interpret(modulename, statements);
    } catch (RuntimeException error) {
      std::strstream errorstr;
      errorstr << "In [" << error.modulename << "]: [line " << error.token.line << "]";
      lastError = errorstr.str();
    }
  }
}

void Executioner::runScript(std::string script, std::map<std::string, TokenLiteral> context) {
  if (interpreterMustBeRenewed) 
    this->interpreter = std::make_shared<Interpreter>();
  for (auto mi = context.begin(); mi != context.end(); mi++) {
    try {
      if (interpreter->globals->isExists(mi->first))
        interpreter->globals->assign(mi->first, mi->second);
      else
        interpreter->globals->define(mi->first, mi->second);
    } catch (RuntimeException exception) {
      std::cout << "Can't use " << mi->first << " variable, perhaps it is defined as const\n";
    }
  }
  run("script", script);
}

void Executioner::setInterpreterToRenew(bool renew) {
  interpreterMustBeRenewed = renew;
}


std::string Executioner::getError() {
  return lastError;
}

TokenLiteral Executioner::getContextValue(std::string name) {
  if (interpreter->globals->isExists(name))
    return interpreter->globals->get(name);
  return TokenLiteral();
}