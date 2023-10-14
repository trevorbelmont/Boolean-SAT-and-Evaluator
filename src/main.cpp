#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "utils.hpp"

// carrega todas as bibliotecas necessárias

using namespace std;

int main(int argc, char** argv) {
  string function = argv[1];

  string exp = argv[2];
  string entrada = argv[3];

  if (argc < 4) {
    cout << "Sintaxe inválida!" << endl;
    exit(1);
  }
  Fila f = infix2Postfix(exp);

  // Função avaliadora
  if (function == "-a") {
    cout << solvePostfix(f, entrada) << endl;
  }

  // Função de satifatibilidade
  else if (function == "-s") {
    sat(f, entrada);
  }
}