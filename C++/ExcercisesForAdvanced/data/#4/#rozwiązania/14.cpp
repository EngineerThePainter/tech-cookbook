#include <iostream>
#include <fstream>
#include <map>
#include <bitset>
#include <string>
#include <set>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;
//////////////////////////////////////////////////////
typedef unsigned long long int UL;
class Obiekt {
public:
  string ID;
  bool poprawny = true;
  bitset<32> bity;
  int ile_w_zwiazku;
  // lista obiektów w interakcji z tym (ale niekoniecznie między sobą!)
  set<shared_ptr<Obiekt>> interakcyjni;

  UL mozliwe_zwiazki() {
    if (ile_w_zwiazku == 2) {
      return UL(interakcyjni.size());
    }
    else if (ile_w_zwiazku == 3) {
      UL trojki = 0;
      // sprawdzam, czy para dodatkowa jest ze sobą w interakcji
      for (auto it = interakcyjni.begin(); it != interakcyjni.end(); it++) {
        auto next(it);
        next++;
        for (; next != interakcyjni.end(); next++) {
          if (**it == **next) {
            trojki++;
          }
        }
      }
      return trojki;
    }
    return 0;
  }

  Obiekt(string dane) {    
    stringstream s;
    s.str(dane);
    s >> ID >> bity >> ile_w_zwiazku;
  }
  // gdy obiekty są "porównywalne", to znaczy, że są w interakcji
  bool operator==(Obiekt& drugi) {
    return ((bity ^ drugi.bity).count() <= 8); // >=24 takich samych bitów na pozycjach
  }
};

int main() {
  setlocale(LC_ALL, "");
  ifstream plik("14_dane_we.txt");
  map<string, shared_ptr<Obiekt>> dane;
  set<string> niepoprawne;
  string temp;
  while (getline(plik, temp)) {
    shared_ptr<Obiekt> obiekt = make_shared<Obiekt>(temp);
    if (dane.find(obiekt->ID) == dane.end())
      dane[obiekt->ID] = obiekt;
    else { // obiekt istnieje, jest niepoprawny!
      dane[obiekt->ID]->poprawny = false;
      niepoprawne.insert(obiekt->ID);
    }
  }
  for (auto& e : niepoprawne) cout << e << " niepoprawny!\n";
  // usuwam niepoprawne 
  erase_if(dane, [](auto& o) {
    return (o.second->poprawny == false);
    });
  cout << "Poprawnych = " << dane.size() << endl;
  plik.close();
  // szukam interakcyjnych obiektów (dla każdego szukam innych)
  cout << "Szukam obiektów wchodzących w interakcję.\n"
    "Trochę to potrwa... Postęp:\n";
  unsigned long long int i = 0;
  for (auto& [k1, v1] : dane) {
    if (++i % 1000 == 0) cout << i++ << "/" << dane.size() << endl;
    for (auto& [k2, v2] : dane) {
      if (k1 == k2) continue;
      if (*v1 == *v2) {
        v1->interakcyjni.insert(v2);
        v2->interakcyjni.insert(v1);
      }
    }
  }
  ofstream zapis("14_dane_wy.txt");
  for (auto& e : niepoprawne)
    zapis << e << endl;
  cout << "Obliczam liczbę interakcyjnych obiektów i liczbę możliwych związków.\n";
  for (auto& [id, o] : dane) {
    zapis << o->ID << " " << o->interakcyjni.size() << " " << o->mozliwe_zwiazki() << endl;
  }
  zapis.close();
}
