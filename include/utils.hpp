#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

#include "fila.hpp"
#include "pilha.hpp"

using namespace std;

struct error {
  string message;
};

// Calcula a operação binária definida pelo char "operador".
// Lança exceções se houver operador não previsto.
int calculate(int a, char operador, int b);
// Retorna o resulado da expressão pósfixa carregada na fila sem desinfileirar ela.
// Lança exceções caso a expressão seja inválida.
bool solvePostfix(Fila<string> &postFix, string entry);

// Método que recebe uma string contendo uma expressão INFIXA e retorna uma fila carregada com uma expressão PÓSFIXA.
// Esse método também checa a validade dos operandos e dos operadores previstos, bem como se o disposição de parênteses é válido.
// Baseado no Shunting Yard Algorithm de Dijkstra.
void infix2Postfix(string infix, Fila<string> &out);

// Separa uma string monolítica, "mono", em múltiplas substrings delimitadas pelo character 'delim' e às armazena no vetor "splitted".
// Ignora espaços em branco. Retorna o número de strings carregadas.
int split(string monolitica, char delim, string *splitted);

// Retorna uma fila carregada com as subsrings de "exp"
Fila<string> string2qeuee(string exp);

// Checa se todos os caracteres da string de números, s, são dígitos.
bool checkDigits(string s);

// Retorna a prioridade do operador (retorna 0 se não for um operador previsto).
int priority(string s);

// Verifica se a string s carrega um operador previsto (&|~).
bool checkOperator(string s);

// Troca as variáveis na expressão, por seus respectivos valores.
string replaceBooleans(string exp, string entradas);

// Gera strings de variação da entrada substituindo o quantifier por 1s e 0s
void variations(string values, char quantifier, int i, Fila<string> &out);

// Método que testa expressões que possuem apenas 'existe'
bool satE(Fila<string> &exp, Fila<string> var);

// Método que testa expressões com quantificadores 'para todo'
bool satA(Fila<string> &exp, string values);

// Método que recebe soluções e devolve uma única solução com don't care
string solution(string sol[], int n);

// Método que testa Satifatibilidade completa.
bool sat(Fila<string> &exp, string values);

#endif