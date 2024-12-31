#include <iostream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;
//////////////////////////////////////////////////////
class Uczen {
public:
  string imie;
  string nazwisko;
  int rokUr;
  bool m; // true -> mężczyzna, false -> kobieta
  string zespol; // np. "1A"
  int nr = -1; // dziennik, -1 brak numeru
  // linia z pliku, zawiera wszystkie dane o jednym uczniu
  Uczen(string zpliku) {
    stringstream s(zpliku);
    s >> imie;
    s >> nazwisko;
    s >> rokUr;
    s >> m; // 0/1
    s >> zespol; // "1A" itp.
  }
  bool operator<(Uczen& u) {
    return (nazwisko < u.nazwisko);
  }
};

class Klasa {
public:
  // zastosowałem map, gdyż można przerobić klasę Klasa tak, by 
  // mogła przechowywać różne klasy: Klasa.dane["1A"], Klasa.dane["1B"] itp.
  map<string, vector<Uczen>> dane;
  void load(string plik) {
    ifstream p(plik);
    string d;
    while (getline(p, d) and d != "") {
      Uczen u(d);
      dane[u.zespol].push_back(u);
    }
  }
  void sortujInumeruj(string klasa) {
    sort(dane[klasa].begin(), dane[klasa].end(), [](auto& a, auto& b) {
      return (a < b); // operator < zdefiniowany w klasie Uczen
      });
    int poz = 1;
    for (auto& u : dane[klasa]) u.nr = poz++;
  }
  void drukuj(string klasa) {
    for (auto& uczen : dane[klasa]) {
      // powiedzmy, że poniższy kod to estetyczne wyświetlenie :)
      cout << uczen.nr << ". " << uczen.imie << " " << uczen.nazwisko;
      cout << " [ur. " << uczen.rokUr << "]";
      cout << ((uczen.m) ? ", mężczyzna" : ", kobieta") << endl;
    }
  }
};
int main() {
  setlocale(LC_ALL, "");
  srand(time(0));

  Klasa k;
  k.load("3_klasa1A.txt");
  k.sortujInumeruj("1A");
  k.drukuj("1A");
}
