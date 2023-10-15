#include <iostream>
#include <sstream>
#include <string>

#include "utils.hpp"

// carrega todas as bibliotecas necessárias

using namespace std;

int main2() {
  Fila<string> f = string2qeuee("   9 9 9 ");
  Fila<string> ff(99999);

  infix2Postfix("~ ( 1 & 2 )", ff);

  cout << ff.at(0) << ff.at(1) << ff.at(2);
}
int main(int argc, char** argv) {
  string function = argv[1];

  string exp = argv[2];
  string entrada = argv[3];

  if (argc < 4) {
    // cout << "Sintaxe inválida!" << endl;
    exit(1);
  }
  Fila<string> f;
  infix2Postfix(exp, f);

  // Função avaliadora
  if (function == "-a") {
    cout << solvePostfix(f, entrada) << endl;
  }

  // Função de satifatibilidade
  else if (function == "-s") {
    sat(f, entrada);
  }
}