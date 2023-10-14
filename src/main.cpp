#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "utils.hpp"

// carrega todas as bibliotecas necessárias

using namespace std;

Fila buildExpression(string infix);

int main(int argc, char** argv) {
  string function = argv[1];

  string exp = argv[2];
  string entrada = argv[3];

  if (argc < 4) {
    cout << "Sintaxe inválida!" << endl;
    exit(1);
  }
  Fila f = buildExpression(exp);

  if (function == "-a") {
    cout << " size: " << f.size() << "  :" << solvePostfix(f, entrada);
    cout << endl;
    cout << " size: " << f.size() << "  :" << solvePostfix(f, "0100000000000000000");
    cout << endl;
  }

  Fila var;

  variations("e10", 'e', 0, var);
  for (int i = 0; i < var.size(); i++) {
    cout << var.at(i) << endl;
  }

  f = buildExpression("0 |  1 & ~ 2");
  cout << "aqui: " << satA(f, "11a") << endl;
  cout << endl;
  cout << endl;

  f = buildExpression("0 | ( 1 & ~ 2 | 3 & 4 )");
  cout << "Teste Sat:" << endl;
  cout << sat(f, "e1a1e");
}

Fila buildExpression(string infix) {
  Fila f;
  try {
    f = infix2Postfix(infix);
    cout << infix << endl;
    for (int i = 0; i < f.size(); i++) {
      cout << f.at(i) << " ";
    }

    cout << endl;

  } catch (error e) {
    cout << e.message << endl;
  }
  return f;
}
