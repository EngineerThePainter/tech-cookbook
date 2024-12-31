#include <iostream>
#include <vector>
#include <map>
using namespace std;
typedef long long int L;
typedef unsigned long long int UL;
//////////////////////////////////////////////////////
UL suma_dzielnikow(UL n) {
  UL s = 1;
  for (UL dzielnik = 2; dzielnik <= n / 2 + 1; dzielnik++)
    if (n % dzielnik == 0) s += dzielnik;
  return s;
}
int main() {
  setlocale(LC_ALL, "");
  map<UL, UL> Z;
  map<UL, UL> zaprzyjaznione;

  for (UL liczba = 2; liczba <= 20000; liczba++)
    Z[liczba] = suma_dzielnikow(liczba);

  for (auto& [liczba, suma] : Z)
    if (Z[suma] and Z[suma] == liczba and liczba != suma)
      zaprzyjaznione.insert({ min(suma,liczba),max(suma,liczba) });
  // prezentacja zaprzyjaźnionych + sumy dzielników tych liczb
  for (auto& [p1, p2] : zaprzyjaznione) 
    cout << "[zaprzyjaźnione " << p1 << "->" << p2 << "] " <<
      " [sumy dzielników:  " << suma_dzielnikow(p1) << " " <<
      suma_dzielnikow(p2) << "]" << endl;
}
