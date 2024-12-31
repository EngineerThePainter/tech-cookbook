#include <iostream>
#include <list>
#include <map>
#include <string>
typedef long long int L;
typedef unsigned long long int UL;
using namespace std;
//////////////////////////////////////////////////////
struct wgr { // wierzchołek grafu
  unsigned nr{ 0 };
  map<shared_ptr<wgr>, int> sciezki;
};

struct G { // graf
  unsigned N = 0; // liczba wierzchołków w grafie
  map<unsigned, shared_ptr<wgr>> wierzcholki; // N === wierzcholki.size()
  map<unsigned, L> koszty;
  map<unsigned, L> poprzednik;
  list<unsigned> ZbiorQ;
  list<unsigned> ZbiorS;
};

// dodaje wierzchołek/wierzchołki bez połączeń
void add(G& graf, unsigned ile = 1) {
  while (ile--) {
    auto nr = graf.wierzcholki.size() + 1;
    graf.wierzcholki.insert({ nr ,make_shared<wgr>() });
    graf.wierzcholki[nr]->nr = nr;
    graf.N++;
  }
}

// łączy dwa wierzchołki (po numerach), nadając wagę połączeniu
void polacz(G& graf, unsigned w1, unsigned w2, int waga) {
  if (w1 > graf.N or w2 > graf.N) return; // nie da się połączyć - nie ma wierzchołków o tym numerze.
  auto wgr1{ graf.wierzcholki[w1] };
  auto wgr2{ graf.wierzcholki[w2] };
  wgr1->sciezki.insert({ wgr2, waga });
  wgr2->sciezki.insert({ wgr1, waga });
}

// rozłącza dwa wierzchołki
void rozlacz(G& graf, unsigned w1, unsigned w2) {
  if (w1 > graf.N or w2 > graf.N) return;
  auto wgr1{ graf.wierzcholki[w1] };
  auto wgr2{ graf.wierzcholki[w2] };
  wgr1->sciezki.erase(wgr2);
  wgr2->sciezki.erase(wgr1);
}


// przygotowanie grafu do poszukiwań
void przygotowanie(G& graf) {
  for (auto& [nr, w] : graf.wierzcholki) {
    graf.koszty[nr] = -1; // -1 to koszt nieskończony
    graf.poprzednik[nr] = -1; // -1 to niezidentyfikowany poprzednik
    graf.ZbiorQ.push_back(nr); // zbiór wierzchołków
  }
}

// zwraca wierzchołek o najmniejszym koszcie dojścia
unsigned min_koszt(G& graf) {
  L koszt = 1000;
  unsigned m = 0; // numer wierzchołka o najmniejszym koszcie dojścia
  for (auto& nr : graf.ZbiorQ) {
    if (graf.koszty[nr] != -1 and koszt > graf.koszty[nr]) {
      koszt = graf.koszty[nr];
      m = nr;
    }
  }
  return m;
}

// sprawdzam, czy element jest na liście
bool jestWSrodku(unsigned n, list<unsigned>& lista) {
  // szukanie jest tutaj liniowe, ale można zastosować inne
  // mechanizmy, np. kolejki priorytetowe o strukturze kopca
  for (auto e : lista) if (e == n) return true;
  return false;
}

// dojście od wierzchołka do wierzchołka
void dijkstra(G& graf, unsigned w_od, unsigned w_do) {
  graf.koszty[w_od] = 0; // zerujemy koszt dojścia dla punktu w_od (reszta nieskończoność -1)
  while (graf.ZbiorQ.size()) {
    auto minkosztnr = min_koszt(graf); // początkowo to w_od
    graf.ZbiorQ.remove(minkosztnr); // zabierz z Q
    graf.ZbiorS.push_back(minkosztnr); // i dodaj do S
    for (auto& [sasiad, waga] : graf.wierzcholki[minkosztnr]->sciezki) {
      if (jestWSrodku(sasiad->nr, graf.ZbiorQ)) {
        if (graf.koszty[sasiad->nr] == -1 or graf.koszty[sasiad->nr] > graf.koszty[minkosztnr] + waga) {
          graf.koszty[sasiad->nr] = graf.koszty[minkosztnr] + waga; // pamiętam koszty dojścia
          graf.poprzednik[sasiad->nr] = minkosztnr; // poprzednikiem sąsiada jest minkosztnr
        }
      }
    }
  }
  // najkrótsza trasa od argumentu w_od do argumentu w_do
  unsigned sciezka = w_do;
  string s = "";
  while (true) {
    s = to_string(sciezka) + " " + s;
    if (graf.poprzednik[sciezka] == -1) break;
    sciezka = graf.poprzednik[sciezka];
  }
  cout << s << endl;
}


int main() {
  setlocale(LC_ALL, "");
  G graf;
  add(graf, 6);
  polacz(graf, 1, 2, 7);
  polacz(graf, 3, 2, 2);
  polacz(graf, 4, 2, 4);
  polacz(graf, 3, 6, 8);
  polacz(graf, 4, 6, 1);
  polacz(graf, 1, 5, 10);
  polacz(graf, 4, 5, 1);

  przygotowanie(graf);
  dijkstra(graf, 1, 6);
}
