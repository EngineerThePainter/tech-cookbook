#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef long long int L;
typedef unsigned long long int UL;
//////////////////////////////////////////////////////
struct wierzcholek {
  wierzcholek* rodzic = nullptr;
  wierzcholek* lewy = nullptr;
  wierzcholek* prawy = nullptr;
  L dane = 0;
};
struct Drzewo {
  wierzcholek* root = nullptr; // wierzchołek początkowy
  wierzcholek* aktualny = nullptr; // obecnie stoimy na tym wierzchołku
  UL size = 0;
  // użycie zmiennej d typu Drzewo jak funkcji: d() zwraca aktualnie wskazywaną wartość elementu
  L operator()() {
    return aktualny->dane;
  }
};
// dodawanie elementu 
void wstaw(wierzcholek* w, wierzcholek* nowy) {
  if (w->dane > nowy->dane) { // idź do lewego potomka
    if (w->lewy == nullptr) {
      nowy->rodzic = w;
      w->lewy = nowy;
    }
    else {
      wstaw(w->lewy, nowy);
    }
  }
  else if (w->dane < nowy->dane) { // do prawego
    if (w->prawy == nullptr) {
      nowy->rodzic = w;
      w->prawy = nowy;
    }
    else {
      wstaw(w->prawy, nowy);
    }
  }
  else { // równy (wstawiam go w miejsce wierzchołka)
    if (w->lewy == nullptr) {
      nowy->rodzic = w;
      w->lewy = nowy;
    }
    else { // wklejam na lewo i przepinam dotychczasowe wierzchołki
      // nowy ma za rodzica stary w
      nowy->rodzic = w;
      // przepięcie lewego
      nowy->lewy = w->lewy;
      if (w->lewy) w->lewy->rodzic = nowy;
      w->lewy = nowy;
    }
  }
}
// dodawanie elementu do drzewa z zachowaniem reguł
void operator+(Drzewo& d, L dane) {
  wierzcholek* nowy = new wierzcholek;
  nowy->dane = dane;
  if (d.size == 0) {
    d.root = d.aktualny = nowy;
  }
  else {
    wstaw(d.root, nowy);
  }
  d.size++;
}

void pokaz(wierzcholek* w, string prefix = "") {
  static vector<vector<string>*> poziomy;
  L poz = prefix.size();
  if (poziomy.size() < poz + 1) {
    poziomy.push_back(new vector<string>());
  }
  if (w != nullptr) {
    poziomy[poz]->push_back(prefix + to_string(w->dane));
    pokaz(w->lewy, prefix + "L");
    pokaz(w->prawy, prefix + "P");
  }
  if (prefix == "") {
    for (auto& v : poziomy) {
      for (auto& e : *v) {
        cout << e << " ";
      }
      cout << endl;
      v->clear();
      delete v;
    }
    poziomy.clear();
  }
}
void pokaz(Drzewo& d) { pokaz(d.root); }
void operator--(Drzewo& d) {   // prefix
  if (d.aktualny and d.aktualny->lewy) d.aktualny = d.aktualny->lewy;
}
void operator++(Drzewo& d, int) { // postfix
  if (d.aktualny and d.aktualny->prawy) d.aktualny = d.aktualny->prawy;
}
void operator^(Drzewo& d, L up) { // do góry idź
  while (d.aktualny and d.aktualny->rodzic and up) {
    d.aktualny = d.aktualny->rodzic;
    up--;
  }
}
bool szukaj(Drzewo& d, L x) {
  wierzcholek* temp = d.root;
  while (temp) {
    if (temp->dane == x) return true;
    if (temp->dane > x) temp = temp->lewy;
    else temp = temp->prawy;
  }
  return false;
}
bool testowanie(wierzcholek* temp = nullptr) {
  if (temp) {
    if (temp->lewy and temp->dane < temp->lewy->dane) return false;
    if (temp->prawy and temp->dane >= temp->prawy->dane) return false;
    return (testowanie(temp->lewy) and testowanie(temp->prawy));
  }
  return true;
}
int main() {
  setlocale(LC_ALL, "");
  Drzewo D;
  // dodam do drzewa wierzchołeczki
  D + 5;   D + 10;   D + 2;   D + 5;   D + 3;
  D + 12;   D + 7;  D + 6;   D + 4;   D + 8;
  D + 12; D + 9; D + 13; D + 12; D + 0;
  pokaz(D);
  cout << D.size << endl; // 15 elementów
  cout << D() << " "; // aktualnie wskazywany
  D++; // idź do prawego
  cout << D() << " "; // aktualnie wskazywany
  --D; // idź do lewego
  cout << D() << " "; // aktualnie wskazywany
  D ^ 4; // idź 4 razy do góry (o ile się da)
  cout << D() << " "; // aktualnie wskazywany
  cout << endl;
  cout << szukaj(D, 100) << " " << szukaj(D, 13) << endl;
  cout << endl << testowanie(D.root) << endl << endl;
  // ręcznie psuję Drzewo, by sprawdzić funkcję: testowanie
  D.root->prawy->prawy->dane = 0; // 0 nie powinno być w tym miejscu
  pokaz(D);
  cout << testowanie(D.root) << endl; // fałsz
}
