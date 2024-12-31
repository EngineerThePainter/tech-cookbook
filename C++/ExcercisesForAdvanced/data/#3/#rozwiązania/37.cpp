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
  map<shared_ptr<wgr>, int> sciezki; // {wskaźnik do wierzchołka, waga połączenia między obecnym wierzchołkiem a wskazywanym}
};

struct G { // graf
  unsigned N = 0; // liczba wierzchołków w grafie
  map<unsigned, shared_ptr<wgr>> wierzcholki; // N == wierzcholki.size()
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
  if (w1 > graf.N or w2 > graf.N) return; // nie da się połączyć - nie ma wierzchołków o tym numerze
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

// zastosuję mój pomysł (rekurencyjny)
map<list<unsigned>, unsigned> wszystkie;

// jeżeli true, mogę iść tą trasą (nie byłem tu wcześniej w ramach ścieżki t)
bool idz(list<unsigned>& t, unsigned tu) {
  for (auto& e : t) if (e == tu) return false;  
  return true;
}
void przeszukiwanie(G& graf, unsigned w_od, unsigned w_do, list<unsigned>& sciezka, unsigned wagaRazem=0) {    
  sciezka.push_back(w_od); // start
  if (w_od == w_do) {
    wszystkie.insert({ sciezka, wagaRazem }); 
    return; // warunek stopu - jest ścieżka!
  }
  for (auto& [sasiad, waga] : graf.wierzcholki[w_od]->sciezki) {
    if (idz(sciezka, sasiad->nr)) {
      list<unsigned> nowa{ sciezka };
      przeszukiwanie(graf, sasiad->nr, w_do, nowa, wagaRazem+waga);      
    }    
  }
}

int main() {
  setlocale(LC_ALL, "");
  G graf;
  add(graf, 6);
  polacz(graf, 1, 2, 7); // pierwszy z drugim, waga połączenia 7
  polacz(graf, 3, 2, 2);
  polacz(graf, 4, 2, 4);
  polacz(graf, 3, 6, 8);
  polacz(graf, 4, 6, 1);
  polacz(graf, 1, 5, 10);
  polacz(graf, 4, 5, 1);

  list<unsigned> sciezka;  
  przeszukiwanie(graf, 1, 6, sciezka);

  for (auto& [s, w] : wszystkie) {    
    for (auto& nr : s) {
      cout << nr << " -> ";      
    }
    cout << " = " << w << endl;
  }
}
