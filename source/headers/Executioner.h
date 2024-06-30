#pragma once
#include <string>
#include <memory>
#include <map>
#include "headers/TokenLiteral.h"
class Interpreter;

class Executioner {
public:
  Executioner();
  void runFile(std::string path);
  void runScript(std::string script, std::map<std::string, TokenLiteral> context = {});
  void runPromt();
  /**
   * So fucking hard to name things.
   * this function called setInterpreterToRenew
   * supposed to be setter for variable of Executioner
   * that will be checked before every run command 
   * and if it is true then before run command
   * interpreter will be recreated with new environment
  */
  void setInterpreterToRenew(bool renew = true);
  std::string getError();
  TokenLiteral getContextValue(std::string name);
private:
  void run(std::string module, std::string path);
  std::string lastError;
  bool interpreterMustBeRenewed = false;
  std::shared_ptr<Interpreter> interpreter;
};