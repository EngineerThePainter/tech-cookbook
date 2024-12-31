#include <iostream>
#include <map>
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
  map<unsigned, shared_ptr<wgr>> wierzcholki; // N === wierzcholki.size()
};

// funkcja ukazująca połączenia wierzchołka o podanym numerze dla podanego grafu
void raport(G& graf, unsigned nr) {
  if (nr > graf.N) return; // nie ma takiego wierzchołka
  auto wgrroot{ graf.wierzcholki[nr] };
  cout << "Połączenia z wierzchołka nr " << nr << endl;
  for (auto& [toWgr, waga] : wgrroot->sciezki) {
    cout << "\t" << "wierzchołek nr=" << toWgr->nr << " połączenie waga=" << waga << endl;
  }
}

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

int main() {
  setlocale(LC_ALL, "");
  G graf;
  add(graf, 6);
  polacz(graf, 1, 2, 7); // pierwszy z drugim, waga połączenia 7
  polacz(graf, 1, 5, 10);
  polacz(graf, 2, 3, 2);
  polacz(graf, 3, 6, 8);
  polacz(graf, 4, 2, 4);
  polacz(graf, 4, 6, 1);
  polacz(graf, 4, 5, 1);

  cout << "Liczba wierzchołków: " << graf.N << endl;
  raport(graf, 1);
  raport(graf, 2);
  raport(graf, 3);
  raport(graf, 4);
  raport(graf, 5);
  raport(graf, 6);

  rozlacz(graf, 2, 4);
  cout << "Po rozłączeniu:\n";
  raport(graf, 2);
  raport(graf, 4);
}
