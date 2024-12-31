#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
typedef long long int L;
typedef unsigned long long int UL;
using namespace std;
//////////////////////////////////////////////////////
struct czas {
  L start;
  L koniec;
  UL nr_papugi;
};
L ile(czas& c) { return c.koniec - c.start; }
// czy w podanej sekundzie papuga gada?
bool czy_gada(UL sekunda, pair<czas, czas>& p) {
  return ((p.first.start <= sekunda and p.first.koniec > sekunda) or
    (p.second.start <= sekunda and p.second.koniec > sekunda));
}

int main() {
  setlocale(LC_ALL, "");
  vector<pair<czas, czas>> papugi; // papugi[0]={czas, czas} // papuga nr 1
  ifstream ppapugi("24_papugi.txt");
  string temp;
  L ostatnia_sekunda = 0;
  L najdluzsze_gderanie = 0;
  getline(ppapugi, temp); // ignoruję pierwszy wiersz z nagłówkami
  while (!ppapugi.eof()) {
    L numer, s1, k1, s2, k2;
    ppapugi >> numer >> s1 >> k1 >> s2 >> k2;
    papugi.push_back({ {s1,k1,papugi.size() + 1},{s2,k2,papugi.size() + 1} });
    if (k2 > ostatnia_sekunda) ostatnia_sekunda = k2;
    L gderanie = ile(papugi.back().first) + ile(papugi.back().second);
    if (najdluzsze_gderanie < gderanie) najdluzsze_gderanie = gderanie;
  }
  ppapugi.close();
  // a) Która papuga gderała łącznie najdłuższą ilość sekund? [1,] (może być ich więcej, więc szukam wielu)
  vector<UL> nr_papugi;
  for (auto& p : papugi) {
    auto& [c1, c2] = p;
    if (ile(c1) + ile(c2) == najdluzsze_gderanie) nr_papugi.push_back(c1.nr_papugi);
  }
  cout << "a) Najdłużej, bo aż " << najdluzsze_gderanie << " sekund darła się papuga nr: ";
  for (auto c : nr_papugi) cout << c << " ";
  cout << "\n\n";
  // b) Ile papug wydawało nieprzerwanie dźwięk od 120. do 130. sekundy badań (włącznie ze 130. sekundą) ? [2,]
  UL ile_120130 = 0;
  for (auto& p : papugi) {
    auto& [c1, c2] = p;
    if ((c1.start <= 120 and c1.koniec > 130) or (c2.start <= 120 and c2.koniec > 130)) ile_120130++;
  }
  cout << "b) " << ile_120130 << " papug wydawało nieprzerwanie głos między 120. a 130. sekundą.\n";
  // c) Podaj sekundy pomiaru, podczas których największa liczba papug wydawała dźwięki równocześnie ? [4,],
  // zrobię to poprzez symulację upływu sekund i sprawdzanie, ile papug śpiewa w tym momencie
  UL ile_papug = 0;
  vector<UL> ile_w_sekundzie;
  for (UL sekunda = 1; sekunda <= ostatnia_sekunda; sekunda++) {
    UL ile_papug_w_sekundzie = 0;
    for (auto& p : papugi) {      
      if (czy_gada(sekunda, p)) {
        ile_papug_w_sekundzie++;
      }
    }
    if (ile_papug_w_sekundzie > ile_papug) { // więcej papug się drze
      ile_papug = ile_papug_w_sekundzie;
    }
    ile_w_sekundzie.push_back(ile_papug_w_sekundzie);
  }

  cout << "c) ";
  for (UL sek = 0; sek < ile_w_sekundzie.size(); sek++) {
    if (ile_w_sekundzie[sek] == ile_papug) {
      cout << sek + 1 << " s " << ile_w_sekundzie[sek] << " papug,\n";
    }
  }

  // d) Ile papug skrzeczało krócej za drugim wydanym głosem? [1]
  UL ile_krocej = 0;
  for (auto& p : papugi) {
    if (ile(p.first) > ile(p.second)) ile_krocej++;
  }
  cout << "d) Krócej za drugim skrzeczeniem darło się " << ile_krocej << " papug.\n";
}
