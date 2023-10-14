#include "utils.hpp"

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

Fila infix2Postfix(string infix) {
  Pilha<string> pOp;  // pilha que armazena operadores temporáriamente
  Fila fPostfix;      // Fila que comporta a expressão PÓSFIXA resultante

  Fila exp = string2qeuee(infix);
  // guarda o número de parênteses. Será incrementado a cada "(" e decrementado a cada ")". Deve resultar zero ao fim do carregamento..
  int par = 0;

  while (!exp.empty()) {
    string s = exp.pop();  // lê o próximo elemento da fila de string contendo a expressão

    if (checkDigits(s)) {  // checa se é um número
      fPostfix.push(s);
    } else if (checkOperator(s)) {  // Se for um operador, empilha ou adiciona na fila

      // Dá flush na pilha de operadores enquanto eles tiverem maior prioridade que o próximo operador lido da expressão.
      while (!pOp.empty() && priority(pOp.top()) > priority(s)) {
        fPostfix.push(pOp.pop());
      }
      pOp.push(s);
    } else if (s == "(") {  // Incrementa par e empilha o "(" na fila de operadores
      par++;
      pOp.push(s);
    } else if (s == ")") {  // Decrementa par e enfileira os operadores da fila de oP* até achar um "("
      par--;
      // Adiciona os operadores na fila pósfixa até que este operador seja um "("
      while (!pOp.empty() && pOp.top() != "(") {
        fPostfix.push(pOp.pop());
      }
      if (!pOp.empty()) pOp.pop();  // Se a pilha de operadores não estiver vazia, desempilha o abre parênteses.
    }
    // Se for um caso não previsto a expressão não é válida
    else {
      Fila e;
      e.push("NAO VALIDA! Não previsto");  // ¬ resolver exceção
      return e;
    }
  }

  // Aqui todas as entradas da fila contendo a expressão já foram lidas.
  // Caso o número de "(" seja diferente do número de ")", retorna NÂO VALIDO
  if (par != 0) {
    Fila e;
    e.push("NAO VALIDA! Parêntesis não pares");  // ¬ resolver exceção
    return e;
  }

  // Adiciona operadores restantes na pilha na fila
  while (!pOp.empty()) {
    fPostfix.push(pOp.pop());
  }
  return fPostfix;
}

string replaceBooleans(string exp, string entry) {
  for (int i = 0; i < exp.size(); i++) {
    string c = "";
    c += exp[i];
    if (checkDigits(c) && stoi(c) < entry.length()) {
      exp[i] = entry[stoi(c)];
    }
  }
  return exp;
}

void variations(string values, char quantifier, int i, Fila &out) {
  if (i == values.length()) {
    out.push(values);

    return;
  }
  if (values[i] == quantifier) {
    values[i] = '0';
    variations(values, quantifier, i + 1, out);

    values[i] = '1';
    variations(values, quantifier, i + 1, out);
  } else {
    variations(values, quantifier, i + 1, out);
  }
}

bool satE(Fila exp, Fila var) {
  int i = 0;
  int sat = 0;
  string s[var.size()];  // vetor que guarda apenas as configurações que deram positivas.

  // Itera pelas possibilidades e checa se é satisfazível
  while (i < var.size()) {
    bool res = solvePostfix(exp, var.at(i));
    if (res) {
      s[sat] = var.at(i);
      sat++;
    }
    i++;
  }
  if (sat == 0) {
    cout << false << endl;
    return sat;
  } else {
    cout << true << " " << solution(s, sat) << endl;
    return sat;
  }
}

bool satA(Fila exp, string values) {
  int i = 0;
  int sat = 0;

  Fila var;
  variations(values, 'a', 0, var);

  // Itera pelas possibilidades e checa se é satisfazível
  while (i < var.size()) {
    bool res = solvePostfix(exp, var.at(i));
    if (res) {
      sat++;
    } else {
      break;
    }
    i++;
  }
  if (sat == var.size()) {
    return true;
  } else {
    return false;
  }
}

string solution(string sol[], int n) {
  string solution = sol[0];
  // for que passa por todos os caracteres das soluções
  for (int i = 0; i < sol[0].length(); i++) {
    char c = sol[0][i];
    // for que compara cada solução.
    for (int s = 0; s < n; s++) {
      if (c != sol[s][i]) {
        solution[i] = 'a';
        break;
      }
    }
  }
  return solution;
}

bool sat(Fila exp, string values) {
  Fila exist;
  // a fila exist recebe todos os valores possíveis de existem.
  variations(values, 'e', 0, exist);
  string solutions[exist.size()];

  int solved = 0;

  // for que checa todos os valores possiveis de para-todo em todos os valores possíveis de exitem.
  for (int i = 0; i < exist.size(); i++) {
    bool res = satA(exp, exist.at(i));
    if (res) {
      solutions[solved] = exist.at(i);
      solved++;
    }
  }

  cout << bool(solved) << " " << solution(solutions, solved) << endl;

  return solved;
}

Fila string2qeuee(string exp) {
  string *tempSplitted = new string[500];
  int tam = split(exp, ' ', tempSplitted);
  Fila aux(tam);
  aux = aux.loadQueue(tempSplitted, tam);
  delete[] tempSplitted;
  return aux;
}

int split(string mono, char delim, string *splitted) {
  stringstream ss(mono);
  string s;
  int i = 0;
  while (getline(ss, s, delim)) {
    // Ignora strings vazias ou espaços em branco. Útil, uma vez que a entrada contém espaços duplos.
    if (s != " " && s != "") {
      splitted[i] = s;
      i++;
    }
  }
  return i;
}

bool checkDigits(string s) {
  // Passa por todas os caractere da string
  for (char c : s) {
    int cint = int(c);  // cast c para int

    // Se c algum carectere de s NÃO está entre '0' (48) e '9' (57),
    // retorna falso - pois s não está no formato numérico esperado
    if (!(cint >= 48 && cint <= 57)) {
      return false;
    }
  }
  return true;
}

int priority(string s) {
  if (s == "~")
    return 3;
  if (s == "&")
    return 2;
  else if (s == "|")
    return 1;
  else
    return 0;
}

bool checkOperator(string s) {
  return (s == "~" || s == "&" || s == "|");
}

int calculate(int a, char op, int b) {
  switch (op) {
    case '~':
      return !a;
      break;
    case '&':
      return a && b;
      break;
    case '|':
      return a || b;
      break;

    default:
      error e;

      e.message = "Erro!!! O operador ";
      e.message += op;
      e.message += " é inválido ou não previsto.";
      throw e;
      break;
  }
}

bool solvePostfix(Fila postFix, string entry) {
  Pilha<int> pNumbers;  // pilha auxiliar que comporta os valores das variáveis para resolver a expressão

  // Desinfileira fila com expressão pósfixa.
  // Fila.at(i) poderia ser usado para evitar desinfileirar a lista, caso a avaliação não fosse a última chamada no trabalho.
  for (int i = 0; i < postFix.size(); i++) {
    string s = postFix.at(i);

    // Se a entrada for um número, empilha na pilha de inteiros
    if (checkDigits(s)) {
      // adciona na pilha de inteiros o valor da variável apontada pela variável - de acordo com seu índice.
      pNumbers.push(entry[stoi(s)] - int('0'));
    }
    // Se não for um número e for um operador previsto.
    else if (checkOperator(s)) {
      // Lança exceção se não houverem operandos suficientes na pilha para calcular.
      if (pNumbers.size() < 2 && (s == "|" || s == "&")) {
        error e;
        e.message = "Erro!!! A expressão pósfixa armazenada não é válida!";
        cout << e.message;
        throw e;
      } else if (pNumbers.size() < 1 && s == "~") {
        error e;
        e.message = "Erro!!! A expressão pósfixa armazenada não é válida!";
        cout << e.message;
        throw e;
      }

      if (s == "|" || s == "&") {
        // desempilha e armazena os dois números no topo da pilha de floats
        int b = pNumbers.pop();
        int a = pNumbers.pop();
        // Calcula a operação indicada pelo operador e empilha o resultado na pilha de floats
        pNumbers.push(calculate(a, s[0], b));
      }

      else if (s == "~") {
        int a = pNumbers.pop();
        pNumbers.push(calculate(a, s[0], a));
      }
    }
    // Se a entrada não for um operador previsto ou operando, lança exceção.
    else {
      error e;
      e.message = "Erro!!! A expressão pósfixa armazenada contem operador inválido ou não previsto!";
      throw e;
    }
  }  // Fecha o loop para prosseguir com os retornos da função.

  // Lança exceção se não houver apenas um valor (o resultado) na pilha de números.
  if (pNumbers.size() != 1) {
    error e;
    e.message = "Erro!!! A expressão pósfixa armazenada é inválida!";
    cout << e.message;
    throw e;
  }
  // Retorna o único valor da pilha de int: o resultado da expressão.
  return pNumbers.pop();
}
