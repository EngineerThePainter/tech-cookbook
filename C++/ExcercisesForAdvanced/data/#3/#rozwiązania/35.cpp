#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>

typedef long long int L;
typedef unsigned long long int UL;
using namespace std;
//////////////////////////////////////////////////////
void ekstraktor_slow(string& linia, map<string, unsigned>& baza) {
  string separatory = "!,.;:-()?0123456789\t\n ";
  string s;
  char znak;
  while (linia.begin() != linia.end()) {
    znak = linia[0];
    linia.erase(0, 1);
    if (separatory.find(znak) != string::npos) { // znak to separator  
      if (s.size()) {
        baza[s]++;
      }
      s.clear();
    }
    else s += znak;
  }
  if (s.size()) baza[s]++; // zostało jakieś słowo niedodane?
}
int main() {
  /* Przydatne:
  * Polecenie system("chcp 65001") pozwoli zmienić kodowanie konsoli
  * na UTF-8 (w takim kodowaniu jest plik 35_opowiadanie.txt).
  * Można wykorzystać: setlocale(LC_ALL, "pl_PL.UTF-8"); setlocale(LC_ALL,"").
  * Zwróć uwagę, że kodowanie pliku źródłowego .cpp może być inne niż kodowanie
  * pliku do zadania (UTF-8).
  */
  // Rozwiązanie zadania
  system("chcp 65001");

  ifstream opowiadanie("35_opowiadanie.txt");
  map<string, unsigned> baza; // słowo -> liczba wystąpień
  string linia;
  while (!opowiadanie.eof()) {
    if (opowiadanie >> linia) {
      ekstraktor_slow(linia, baza);
    }
  }
  unsigned ile_wyrazow = 0;
  unsigned cols = 0;
  for (auto& [slowo, ilosc] : baza) {
    cout.fill('.'); cout.width(50);
    cout << left << slowo + " => " + to_string(ilosc);
    if (++cols % 2 == 0) cout << endl;
    ile_wyrazow += ilosc;
  }
  cout << endl;

  cout << baza.size() << endl; // tyle jest różnych słów
  cout << ile_wyrazow << endl; // tyle jest słów w całym tekście

  opowiadanie.close();
}
