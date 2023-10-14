#include "fila.hpp"

#include <sstream>
#include <string>

using namespace std;

Fila::Fila() {
  // s_ = new char[1000];
  size_ = 0;
  max_size_ = 200000;
  first_ = 0;
  last_ = 0;
}

Fila::Fila(int tam) {
  // s_ = new char[tam];
  max_size_ = tam;
  size_ = 0;
  first_ = last_ = 0;
}

bool Fila::push(int k) {
  if (full()) {
    return false;
  }
  s_[size_] = k;
  size_++;
  last_++;
  return true;
}

int Fila::pop() {
  if (empty()) {
    return -404;  // Tratar a Exceção ¬
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

int Fila::front() {
  if (empty()) {
    return -404;  // Tratar exceção. ¬
  }
  return s_[first_];
}

int Fila::at(int i) {
  if (empty() || (first_ + i) > last_ - 1) {
    return -404;  // /¬ resolver exceção
  }
  return s_[i];
}

Fila Fila::loadQueue(int *s, int tam) {
  Fila aux(tam);

  for (int i = 0; i < tam; i++) {
    aux.push(s[i]);
  }

  return aux;
}

string Fila::toString(string separator) {
  string aux = "";
  for (int i = first_; i < last_; i++) {
    aux += to_string(s_[i]);
    if (i != last_ - 1) aux += separator;
  }
  return aux;
}

void Fila::clear() {
  for (int i = 0; i < size_; i++) {
    s_[i] = 0;
  }
  first_ = size_ = 0;
}

Fila::~Fila() {
  // delete[] s_;
}
