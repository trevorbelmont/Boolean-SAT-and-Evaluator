#include "fila.hpp"

#include <sstream>
#include <string>

using namespace std;

Fila::Fila() {
  // s_ = new char[1000];
  size_ = 0;
  max_size_ = MAX;
  first_ = 0;
  last_ = 0;
  ;
}

Fila::Fila(int tam) {
  if (tam > MAX) {
    cout << "Excpetion e: the required Fila size (" << tam << ") is beyond permited maximum (" << MAX << "! " << endl;
    tam = MAX;
  }
  // s_ = new char[tam];
  max_size_ = tam;
  size_ = 0;
  first_ = last_ = 0;
}

bool Fila::push(string k) {
  if (full()) {
    return false;
  }
  for (int i = 0; i < LENGTH && i < k.length(); i++) {
    s_[size_][i] = k[i];
  }
  size_++;
  last_++;
  return true;
}

string Fila::pop() {
  if (empty()) {
    return "!";  // Tratar a Exceção ¬
  }
  size_--;
  return s_[first_++];
}

bool Fila::empty() {
  return size_ == 0;
}

bool Fila::full() {
  return last_ == max_size_;
}

int Fila::size() {
  return size_;
}

string Fila::front() {
  if (empty()) {
    return "!error!";  // Tratar exceção. ¬
  }
  return s_[first_];
}

string Fila::at(int i) {
  if (empty() || (first_ + i) > last_ - 1) {
    return "!error!";  // /¬ resolver exceção
  }
  return s_[i];
}

Fila Fila::loadQueue(string *s, int tam) {
  Fila aux(tam);

  for (int i = 0; i < tam; i++) {
    aux.push(s[i]);
  }

  return aux;
}

string Fila::toString(string separator) {
  string aux = "";
  for (int i = first_; i < last_; i++) {
    aux += s_[i];
    if (i != last_ - 1) aux += separator;
  }
  return aux;
}

void Fila::clear() {
  for (int i = 0; i < size_; i++) {
    int k = 0;
    while (k < LENGTH) {
      s_[i][k] = ' ';
    }
  }
  first_ = size_ = 0;
}

Fila::~Fila() {
  // delete[] s_;
}
