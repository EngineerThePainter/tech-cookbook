#include <iostream>
#include <vector>
#include <fstream>
#include <map>
using namespace std;
typedef long long int L;
typedef unsigned long long int UL;
//////////////////////////////////////////////////////
bool pierwsza(L p) {
  for (L dzielnik = 2; dzielnik <= sqrt(p); dzielnik++)
    if (p % dzielnik == 0) return false;
  return true;
}
int main() {
  setlocale(LC_ALL, "");
  ifstream plik("8_dane.txt");
  // korzystam z multimap, który sortuje klucze i załatwia za mnie porządkowanie
  multimap<L, L> dane;
  L umiejetnosc, gracz;
  while (!plik.eof()) {
    if (plik >> umiejetnosc >> gracz) { // odczyt się udał
      dane.insert({ umiejetnosc,gracz });
    }
    else break;
  }
  plik.close();
  cout << "Odczytano " << dane.size() << " wpisów.\n";
  // kody graczy
  L ostatni_max = 0;
  int dziesiec = 0;
  for (auto it = dane.rbegin(); it != dane.rend() and dziesiec < 10; it++) {
    if (ostatni_max != it->first) {
      dziesiec++;
      cout << "\nNajwyższa wartość nr: " << dziesiec << " wynosząca " << it->first << ", gracze:";
    }
    cout << it->second << " ";
    ostatni_max = it->first;
  }
  // średnia
  double srednia = 0;
  for (auto [um, gr] : dane) srednia += um;
  cout << "\n\nŚrednia graczy = " << srednia / dane.size() << endl;
  // gracze z Polski o trzech najgorszych umiejętnościach
  multimap<L, L> polska;
  for (auto [um, gr] : dane) if (pierwsza(gr)) polska.insert({ um,gr });
  L ostatni_min = 0;
  int trzy = 0;
  for (auto it = polska.begin(); it != polska.end() and trzy < 3; it++) {
    if (ostatni_min != it->first) {
      trzy++;
      cout << "\nNajniższa wartość nr: " << trzy << " wynosząca " << it->first << ", gracze:";
    }
    cout << it->second << " ";
    ostatni_min = it->first;
  }
}
