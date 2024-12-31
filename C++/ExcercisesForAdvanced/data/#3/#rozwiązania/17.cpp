#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <set>
using namespace std;
typedef long long int L;
typedef unsigned long long int UL;
//////////////////////////////////////////////////////
set<UL> algorytm; // liczby z algorytmu weryfikującego
set<UL> generacja; // liczby z generatora
string cyfry = "0123456789";
UL ile = 0;
bool palindromiczna(UL n) {
  list<UL> cyfry;
  UL temp = n;
  while (temp) {
    cyfry.push_back(temp % 10);
    temp /= 10;
  }
  UL odwrotna = 0;
  UL dzielnik = 1;
  for (auto it = cyfry.rbegin(); it != cyfry.rend(); it++) {
    odwrotna += *it * dzielnik;
    dzielnik *= 10;
  }
  return (odwrotna == n);
}
string reverse_string(string temp, int p = 0) {
  if (!temp.size()) return temp;
  if (p) temp.pop_back();
  return string(temp.rbegin(), temp.rend());
}
void generator(string prefix = "") {
  if (prefix.size() > 3) return;
  for (string palindromiczna : vector<string>({ prefix + reverse_string(prefix),
    prefix + reverse_string(prefix,1) })) {
    // >=2 to >= "10", <=5 to <= "99999"
    if (palindromiczna.size() <= 5 and palindromiczna.size() >= 2) {
      cout << stoul(palindromiczna) << " ";
      ile++;
      // liczby z generatora
      generacja.insert(stoul(palindromiczna));
    }
  }
  for (auto c : cyfry) {
    if (prefix == "" and c == '0') continue;
    generator(prefix + string(1, c));
  }
}

int main() {
  setlocale(LC_ALL, "");

  // algorytm sprawdzania po kolei, które są palindromiczne
  ile = 0;
  cout << "Liczby palindromiczne:";
  for (UL liczba = 10; liczba <= 99999; liczba++) {
    if (palindromiczna(liczba)) {
      cout << liczba << " ";
      algorytm.insert(liczba); // liczby z algorytmu
      ile++;
    }
  }
  cout << "\n" << ile << " liczb palindromicznych znalezionych metodami weryfikacji.\n\n\n";

  // liczby palindromiczne wygenerowane na podstawie odkrytych własności tych liczb
  ile = 0;
  generator();
  cout << "\n" << ile << "  wygenerowanych liczb palindromicznych.\n\n\n";

  // przy okazji drobny test, czy generator działa  
  if (generacja == algorytm) // porównanie zbiorów set<>
    cout << "Zbiory liczb palidromicznych uzyskane na dwa sposoby są identyczne.\n";
}
