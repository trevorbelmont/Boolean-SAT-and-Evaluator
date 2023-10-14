
#include <iostream>
#include <sstream>
#include <string>

// carrega todas as bibliotecas necessárias

using namespace std;

#define n 2000000

class isso {
 public:
  int s[n];
};

int main() {
  isso s;
  for (int i = 0; i < n; i++)
    cout << s.s[i] << endl;
}