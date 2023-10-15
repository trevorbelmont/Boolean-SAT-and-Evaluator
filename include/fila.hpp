#ifndef FILA_HPP
#define FILA_HPP
#include <iostream>
#include <string>

#define LENGTH 2
#define MAX 1000000

using namespace std;

template <typename Tipo>
class Fila {
 private:
  Tipo *s_;  // s_[MAX];  // vetor que comporta a fila de strings;
             //  ¬ resolver questão do alocamento dinâmico

  int size_;      // o tamanho utilizado da fila. É também o próximo índice disponível - se a fila não estiver cheia.
  int max_size_;  // o tamanho máximo da fila.
  int first_;     // o índice para o primeiro elemento da fila;
  int last_;

 public:
  // Cria fila padrão (máximo 1000 strings).
  Fila();

  // Cria fila com máximo de tamz strings.
  Fila(int tam);

  // Retorna e remove o primeiro string da fila.
  Tipo pop();

  // Enfileira um elemento. Retorna true se enfileirou com êxito
  bool push(Tipo x);

  // Retorna o próximo elemento sem removê-lo.
  Tipo front();

  // Retorna a string na posição especificada sem destruí-la.
  // Anlálogo ao método deque.at(i) (método "at" da double ended queue) da stl.
  Tipo at(int i);

  // Retorna true se a fila estiver vazia.
  bool empty();

  // Retorna true se a fila tiver alcançado o tamanho máximo.
  bool full();

  // Retorna o tamanho atual da fila.
  int size();

  // Lê um array de strings e os enfileira
  void loadQueue(Tipo *s, int tam);

  // Retorna uma string contendo todas as entradas da fila interpoladas pelo "separator".
  // Caso nenhuma string separadora seja especificada, um espaço em branco será utilizado.
  string toString(string separator = " ");

  // Limpa e reinicia a fila.
  void clear();

  // Desaloca memória e Destrói a fila.
  ~Fila();
};

template <typename Tipo>
Fila<Tipo>::Fila() {
  s_ = new Tipo[1000];
  size_ = 0;
  max_size_ = MAX;
  first_ = 0;
  last_ = 0;
  ;
}

template <typename Tipo>
Fila<Tipo>::Fila(int tam) {
  if (tam > MAX) {
    cout << "Excpetion e: the required Fila size (" << tam << ") is beyond permited maximum (" << MAX << "! " << endl;
    tam = MAX;
  }
  s_ = new Tipo[tam];
  max_size_ = tam;
  size_ = 0;
  first_ = last_ = 0;
}

template <typename Tipo>
bool Fila<Tipo>::push(Tipo k) {
  if (full()) {
    return false;
  }
  s_[size_] = k;
  size_++;
  last_++;
  return true;
}

template <typename Tipo>
Tipo Fila<Tipo>::pop() {
  if (empty()) {
    return "!";  // Tratar a Exceção ¬
  }
  size_--;
  return s_[first_++];
}

template <typename Tipo>
bool Fila<Tipo>::empty() {
  return size_ == 0;
}

template <typename Tipo>
bool Fila<Tipo>::full() {
  return last_ == max_size_;
}

template <typename Tipo>
int Fila<Tipo>::size() {
  return size_;
}

template <typename Tipo>
Tipo Fila<Tipo>::front() {
  if (empty()) {
    return NULL;  // Tratar exceção. ¬
  }
  return s_[first_];
}

template <typename Tipo>
Tipo Fila<Tipo>::at(int i) {
  if (empty() || (first_ + i) > last_ - 1) {
    return NULL;  // /¬ resolver exceção
  }
  return s_[i];
}

template <typename Tipo>
void Fila<Tipo>::loadQueue(Tipo *s, int tam) {
  delete[] s_;
  s_ = new Tipo[tam];

  for (int i = 0; i < tam; i++) {
    this->push(s[i]);
  }
}

template <typename Tipo>
string Fila<Tipo>::toString(string separator) {
  string aux = "";
  for (int i = first_; i < last_; i++) {
    aux += s_[i];
    if (i != last_ - 1) aux += separator;
  }
  return aux;
}

template <typename Tipo>
void Fila<Tipo>::clear() {
  first_ = size_ = 0;
  delete[] s_;
  s_ = new Tipo[max_size_];
}
template <typename Tipo>
Fila<Tipo>::~Fila() {
   delete[] s_;
}

#endif