#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
using namespace std;
//////////////////////////////////////////////////////
typedef unsigned long long int UL;
class Plansza {
public:
  vector<vector<UL>> pola;
  pair<int, int> pozycja_pionka = { 50,50 };
  Plansza() {
    pola.resize(101);
    for (auto& wiersz : pola) wiersz.resize(101, 0);
    pola[50][50]++; // pole startowe odwiedzone przez pionek
  }
  // ruch z pozycji w kierunku, zwraca nową pozycję
  pair<int,int> ruch(int kierunek) {
    auto [x, y] = pozycja_pionka;
    if (y % 2 == 0) {
      switch (kierunek) {
        case 1: y--; x++;  break;
        case 2: x++; break;
        case 3: y++; x++;  break;
        case 4: y++; break;
        case 5: x--; break;
        case 6: y--; break;
      }
    }
    else if (y % 2 == 1) {
      switch (kierunek) {
        case 1: y--; break;
        case 2: x++; break;
        case 3: y++; break;
        case 4: y++; x--; break;
        case 5: x--; break;
        case 6: y--; x--; break;
      }
    }
    if (x < 0 or y < 0 or x>100 or y>100) {
      // cout << "ruch poza planszą!\n";
      return { -1,-1 }; // poza planszą !
    }
    pozycja_pionka = { x,y };
    pola[x][y]++;    
    // cout << "ruch na pole " << x << ":" << y << endl;
    return { x,y };
  }
  // ruch w kolejnych kierunkach, zwraca wektor z kolejnymi pozycjami
  vector<pair<int,int>> seriaRuchow(vector<int> v) {
    vector<pair<int, int>> pomoc;
    for (auto& r : v) pomoc.push_back(ruch(r));
    return pomoc;
  }
};
int main() {
  setlocale(LC_ALL, "");
  Plansza p1,p2;
  vector<int> ruchy;
  ifstream plik("26_ruch.txt");
  int r;
  while (plik >> r) {
    ruchy.push_back(r);    
  }
  plik.close();
  auto pozycje1 = p1.seriaRuchow(ruchy);
  cout << "Pozycja pionka start 50,50:" << p1.pozycja_pionka.first << ":" << p1.pozycja_pionka.second << endl;
  p2.pozycja_pionka = { 87,90 };
  p2.seriaRuchow(ruchy);
  cout << "Pozycja pionka start 87,90:" << p2.pozycja_pionka.first << ":" << p2.pozycja_pionka.second << endl;

  UL m=0; // maks. liczba odwiedzeń pola
  int pozx=-1, pozy=-1;
  for (int x = 0; x < p1.pola.size(); x++) {
    for (int y = 0; y < p1.pola[x].size(); y++) {
      if (p1.pola[x][y] > 0 and m < p1.pola[x][y]) {
        m = p1.pola[x][y];
        pozx = x; pozy = y;
      }
    }
  }
  cout << "Pole " << pozx << ":" << pozy << " odwiedzono największą liczbę razy = " << m << endl;
  map<int, int> ile_w_wierszach;
  UL mw = 0, ilosc=0; // ruchy maksymalne w wierszu
  for (auto& [x, y] : pozycje1) {
    if (y == -1) continue; // nieudany ruch
    ile_w_wierszach[y]++;
    if (ilosc < ile_w_wierszach[y]) {
      ilosc = ile_w_wierszach[y];
      mw = y;
    } 
  }    
  cout << "Wiersz o maksymalnej liczbie odwiedzin = " << ilosc << " to wiersz = " << mw << endl;
 }
