#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
typedef long long int L;
typedef unsigned long long int UL;
using namespace std;
//////////////////////////////////////////////////////
void bez0(string& b) { // usuwam 0 z początku liczby
  while (b[0] == '0') b.erase(0, 1);
}
string dalej(int& i, int dodaj) {
  i += dodaj;
  if (i == 0) {
    return "0";
  }
  else if (i == 1) {
    i = 0;
    return "1";
  }
  else if (i == 2) {
    i = 1;
    return "0";
  }
  else if (i == 3) {
    i = 1;
    return "1";
  }
  else {
    cout << "Jakiś dramat, źle dodajemy?\n";
    return "X";
  }
}
string dodaj(string b1, string b2) {
  bez0(b1);   bez0(b2);
  string suma = "";
  int d = 0;
  int s = 0;
  L poz1 = b1.size() - 1;
  L poz2 = b2.size() - 1;
  while (poz1 >= 0 and poz2 >= 0) {
    suma = dalej(d, b1[poz1] - 48 + b2[poz2] - 48) + suma;
    if (poz1 >= 0) poz1--;
    if (poz2 >= 0) poz2--;
  }
  while (poz1 >= 0) {
    suma = dalej(d, b1[poz1--] - 48) + suma;
  }
  while (poz2 >= 0) {
    suma = dalej(d, b2[poz2--] - 48) + suma;
  }
  while (d) suma = dalej(d, 0) + suma;
  return suma;
}
string binarne_mnozenie(string b1, string b2) {
  cout << b1 << " * " << b2;
  vector<string> dododania;
  for (auto it2 = b2.rbegin(); it2 != b2.rend(); it2++) {
    dododania.push_back("");
    for (auto it1 = b1.rbegin(); it1 != b1.rend(); it1++) {
      int cyfra = (*it1 - 48) * (*it2 - 48);
      dododania.back() = string(1, cyfra + 48) + dododania.back();
    }
    if (dododania.size() > 1)
      dododania.back() += string(dododania.size() - 1, '0');
  }
  while (dododania.size() > 1) {
    string a = dododania.back();
    dododania.pop_back();
    string b = dododania.back();
    dododania.back() = dodaj(a, b);
  }
  return dododania.back();
}
int main() {
  setlocale(LC_ALL, "");
  cout << " = " << binarne_mnozenie("101", "111") << endl;
  cout << " = " << binarne_mnozenie("101111", "1") << endl;
  cout << " = " << binarne_mnozenie("10001011", "10001010111") << endl;
}
