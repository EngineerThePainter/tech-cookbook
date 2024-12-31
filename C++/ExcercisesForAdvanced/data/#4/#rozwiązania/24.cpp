#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <regex>
#include <map>
using namespace std;
//////////////////////////////////////////////////////
typedef unsigned long long int UL;

// Stwórz mechanikę, w której: każdy wiersz to samodzielny obiekt; 
// każdy obiekt powinien udostępniać informacje o tym, ile ma znaków będących cyfrą,
// i ile wynosi suma tych cyfr; każdy obiekt może być równy innemu obiektowi, 
// o ile liczba cyfr i suma tych cyfr są sobie równe.
class Obiekt {
public:
  string dane;
  Obiekt(string wiersz) : dane(wiersz) {}
  UL info(UL& suma) {
    return count_if(dane.begin(), dane.end(),
      [&suma](auto& e) {
        if (e + 0 >= 48 and e + 0 <= 57) // znak e jest cyfrą '0'=>48, '9'=>57
        {
          suma += e - 48;
          return true;
        }
        return false;
      });
  }
  bool operator==(Obiekt& drugi) {
    UL s1, s2;
    return ((this->info(s1) == drugi.info(s2)) and (s1 == s2));
  }
};
int main() {
  setlocale(LC_ALL, "");
  ifstream p("24_dane_znaki_litery.txt");
  vector<string> wiersze;
  string txt;
  while (p >> txt) {
    wiersze.push_back(txt);
  }
  p.close();
  // Ile jest podciągów w pierwszym wierszu przynajmniej pięcioelementowych, 
  // nie dłuższych niż 10-el., które kończą się i zaczynają cyfrą? [1,]  
  map<string, unsigned> ilosci;
  for (int dl = 3; dl <= 8; dl++) { // 3-8 :wnętrza podciągów 
    txt = wiersze[0]; // pierwszy wiersz  
    regex szablon("[0-9].{" + to_string(dl) + "}[0-9]"); // dopasowanie o długości dl=5...10
    smatch znalezione;
    while (txt != "" and regex_search(txt, znalezione, szablon)) {
      // cout << znalezione.str() << endl; // podciągi znalezione
      ilosci[znalezione.str()]++; // zliczam wystąpienia podciągów
      // skracam txt i szukam kolejnego podciągu o znak dalej niż pozycja wcześniejszego znalezionego
      txt = txt.substr(znalezione.position() + 1);
    }
  }
  unsigned ilosc = 0;
  vector<string> powtarzane;
  for (auto& [k, v] : ilosci) {
    ilosc += v;
    cout << k << "=" << v << endl;
    if (v >= 2) powtarzane.push_back(k);
  }
  cout << "!" << powtarzane.size() << endl;
  cout << "W pierwszym wierszu znajduje się " << ilosc << " podciągów zgodnych z poleceniem.\n";
  cout << "Ciągi w pierwszym wierszu, które się powtarzają:\n";
  for (auto& e : powtarzane) cout << e << endl;
  cout << string(30, '*') << endl;
  // Sprawdź, które spośród wszystkich podciągów z pierwszego wiersza powtarzają się w pozostałym tekście. 
  string wszystek; // jeden wielki napis z pozostałych wierszy
  for (int poz = 1; poz < wiersze.size(); poz++) wszystek += wiersze[poz];
  for (auto& [podciag, ile] : ilosci) {
    if (wszystek.find(podciag) != string::npos) cout << podciag << "\n";
  }
  // OBIEKTY
  vector<Obiekt> obiekty;
  for (auto& e : wiersze) {
    obiekty.push_back(Obiekt(e));
  }
  // obiekt trzeci to obiekty[2]
  vector<string> rowne;
  for (int poz = 0; poz < obiekty.size(); poz++) {
    if (poz == 2) continue; // nie porównuje ze sobą samym
    if (obiekty[poz] == obiekty[2])
      rowne.push_back(obiekty[poz].dane);
  }
  cout << "Obiektów równych obiektowi trzeciemu jest = " << rowne.size() << endl;
  cout << "Oto one: ";
  for (auto& e : rowne) cout << e << endl;
}
